/**
  *********************************************************************************
  *
  * @file    ald_dma.c
  * @brief   DMA module driver.
  *
  * @version V1.0
  * @date    09 Nov 2019
  * @author  AE Team
  * @note
  *
  * Copyright (C) Shanghai Eastsoft Microelectronics Co. Ltd. All rights reserved.
  *
  *********************************************************************************
  * @verbatim
  ==============================================================================
                        ##### How to use this driver #####
  ==============================================================================
  [..]
    The DMA driver can be used as follows:

    (#) System initialization invokes ald_dma_init(), ald_cmu_init() --> ald_dma_init().

    (#) Declare a dma_handle_t handle structure.

    (#) Configure the dma_handle_t structure, you can configure the
        dma_config_t structure with the help of ald_dma_config_struct().

    (#) Enable the DMA Configure:
        (##) Memory     -- memory: call ald_dma_config_auto().
	(##) Peripheral -- memory: call ald_dma_config_basic().
	(##) If you want use the dma easily, you can do this:
	    (+++) Memory     -- memory: call ald_dma_config_auto_easy().
	    (+++) Peripheral -- memory: call ald_dma_config_basic_easy().

    (#) Enable the DMA request signal:
        (##) Memory     -- memory: the DMA request signal is request automatic.
	(##) Peripheral -- memory: you need enable peripheral request signal.

    (#) If you enable DMA interrupt, the callback will be invoked:
        (##) When DMA transfer is completed, the cplt_cbk() will be invoked.
	(##) When DMA bus occurs error, the err_cbk() will be invoked.

    (#) If you don't enable the DMA interrupt, you need do this:
        (##) Polling the ald_dma_get_flag_status(), this function's parameter is channel
	     or DMA_ERR.
	    (+++) When the function's Parameter is channel, if retval is SET, it means
	          the DMA transfer is completed. at this moment, you can do something,
		  and then, you need invoke ald_dma_clear_flag_status() to clear flag.

	    (+++) When the function's Parameter is DMA_ERR, if retval is SET, it means
	          the DMA bus occurs error. at this moment, you can do something,
		  and then, you need invoke ald_dma_clear_flag_status() to clear flag.

    @endverbatim
  */

#include <string.h>
#include "ald_conf.h"
#include "ald_dma.h"


/** @addtogroup ES32FXXX_ALD
  * @{
  */

/** @defgroup DMA DMA
  * @brief DMA module driver
  * @{
  */

#ifdef ALD_DMA
/** @defgroup DMA_Private_Variables DMA Private Variables
  * @{
  */
dma_descriptor_t dma0_ctrl_base[28] __attribute__ ((aligned(512)));
dma_call_back_t dma0_cbk[12];
/**
  * @}
  */

/** @defgroup DMA_Private_Functions DMA Private Functions
  * @{
  */

/**
  * @brief  Configure DMA channel using dma_config_t structure
  * @param  DMAx: Pointer to DMA peripheral
  * @param  mode: DMA transfer mode. see @ref dma_cycle_ctrl_t
  * @param  p: Pointer to dma_cycle_ctrl_t which contains
  *            DMA channel parameter. see @ref dma_config_t
  * @retval None
  */
static void dma_config_base(DMA_TypeDef *DMAx, dma_cycle_ctrl_t mode, dma_config_t *p)
{
	dma_descriptor_t *descr;

	assert_param(IS_DMA(DMAx));
	assert_param(IS_CYCLECTRL_TYPE(mode));
	assert_param(p->src != NULL);
	assert_param(p->dst != NULL);
	assert_param(IS_DMA_DATA_SIZE(p->size));
	assert_param(IS_DMA_DATASIZE_TYPE(p->data_width));
	assert_param(IS_DMA_DATAINC_TYPE(p->src_inc));
	assert_param(IS_DMA_DATAINC_TYPE(p->dst_inc));
	assert_param(IS_DMA_ARBITERCONFIG_TYPE(p->R_power));
	assert_param(IS_FUNC_STATE(p->primary));
	assert_param(IS_FUNC_STATE(p->burst));
	assert_param(IS_FUNC_STATE(p->high_prio));
	assert_param(IS_FUNC_STATE(p->interrupt));
	assert_param(IS_DMA_MSEL_TYPE(p->msel));
	assert_param(IS_DMA_MSIGSEL_TYPE(p->msigsel));
	assert_param(IS_DMA_CHANNEL(p->channel));

	if (p->primary)
		descr = (dma_descriptor_t *)(DMAx->CTRLBASE) + p->channel;
	else
		descr = (dma_descriptor_t *)(DMAx->ALTCTRLBASE) + p->channel;

	if (p->src_inc == DMA_DATA_INC_NONE)
		descr->src = p->src;
	else
		descr->src = (void *)((uint32_t)p->src + ((p->size - 1) << (uint32_t)p->src_inc));

	if (p->dst_inc == DMA_DATA_INC_NONE)
		descr->dst = p->dst;
	else
		descr->dst = (void *)((uint32_t)p->dst + ((p->size - 1) << (uint32_t)p->dst_inc));

	descr->ctrl.cycle_ctrl    = mode;
	descr->ctrl.next_useburst = 0;
	descr->ctrl.n_minus_1     = p->size - 1;
	descr->ctrl.R_power       = p->R_power;
	descr->ctrl.src_prot_ctrl = 0,
	descr->ctrl.dst_prot_ctrl = 0,
	descr->ctrl.src_size      = p->data_width;
	descr->ctrl.src_inc       = p->src_inc;
	descr->ctrl.dst_size      = p->data_width;
	descr->ctrl.dst_inc       = p->dst_inc;

	if (p->primary)
		WRITE_REG(DMAx->CHPRIALTCLR, (1 << p->channel));
	else
		WRITE_REG(DMAx->CHPRIALTSET, (1 << p->channel));

	if (p->burst)
		WRITE_REG(DMAx->CHUSEBURSTSET, (1 << p->channel));
	else
		WRITE_REG(DMAx->CHUSEBURSTCLR, (1 << p->channel));

	if (p->high_prio)
		WRITE_REG(DMAx->CHPRSET, (1 << p->channel));
	else
		WRITE_REG(DMAx->CHPRCLR, (1 << p->channel));

	if (p->interrupt)
		SET_BIT(DMAx->IER, (1 << p->channel));
	else
		CLEAR_BIT(DMAx->IER, (1 << p->channel));

	MODIFY_REG(DMAx->CH_SELCON[p->channel], DMA_CH0_SELCON_MSEL_MSK, p->msel << DMA_CH0_SELCON_MSEL_POSS);
	MODIFY_REG(DMAx->CH_SELCON[p->channel], DMA_CH0_SELCON_MSIGSEL_MSK, p->msigsel << DMA_CH0_SELCON_MSIGSEL_POSS);
	return;
}

/**
  * @brief  Handle DMA interrupt
  * @retval None
  */
void ald_dma_irq_handler(void)
{
	uint32_t i, reg = DMA0->IFLAG;

	for (i = 0; i < DMA_CH_COUNT; ++i) {
		if (READ_BIT(reg, (1 << i))) {
			if (dma0_cbk[i].cplt_cbk != NULL)
				dma0_cbk[i].cplt_cbk(dma0_cbk[i].cplt_arg);

			ald_dma_clear_flag_status(DMA0, i);
		}
	}

	if (READ_BIT(reg, (1U << DMA_ERR))) {
		ald_dma_clear_flag_status(DMA0, DMA_ERR);

		for (i = 0; i < DMA_CH_COUNT; ++i) {
			if (((DMA0->CHENSET >> i) & 0x1) && (dma0_cbk[i].err_cbk != NULL))
				dma0_cbk[i].err_cbk(dma0_cbk[i].err_arg);
		}
	}

	return;
}
/**
  * @}
  */

/** @defgroup DMA_Public_Functions DMA Public Functions
  * @{
  */

/** @defgroup DMA_Public_Functions_Group1 Initialization functions
  * @brief Initialization functions
  *
  * @verbatim
    ===================================================================

                    #### Initialization functions ####

    ===================================================================
    [..]
    This subsection provides two functions to Initilizate DMA:
    (+) ald_dma_reset(): Reset the DMA register.

    (+) ald_dma_init(): Initializate the DMA module. this function is
        invoked by ald_cmu_init().
	this function do this:
	(++) Initializte private variable dma_ctrl_base and dma_cbk.
	(++) Reset DMA register.
	(++) Set DMA interrupt priority: preempt_prio=1, sub_priority=1
	(++) Enable DMA interrupt.
	(++) Enable DMA bus error interrupt.
	(++) Configure CTRLBASE resigter.
	(++) Enable DMA module.

    (+) ald_dma_config_struct(): Configure dma_config_t
        structure using default parameter.

    (+) ald_dma_config_sg_alt_desc(): Configure dma_descriptor_t 
        structure using specified parameter. This function used
	in scatter-gather mode(memory or peripheral).

    @endverbatim
  * @{
  */

/**
  * @brief  Reset the DMA register
  * @param  DMAx: Pointer to DMA peripheral
  * @retval None
  */
void ald_dma_reset(DMA_TypeDef *DMAx)
{
	uint32_t i;

	assert_param(IS_DMA(DMAx));

	WRITE_REG(DMAx->CFG, 0x0);
	WRITE_REG(DMAx->CHUSEBURSTCLR, 0xFFF);
	WRITE_REG(DMAx->CHREQMASKCLR, 0xFFF);
	WRITE_REG(DMAx->CHENCLR, 0xFFF);
	WRITE_REG(DMAx->CHPRIALTCLR, 0xFFF);
	WRITE_REG(DMAx->CHPRCLR, 0xFFF);
	WRITE_REG(DMAx->ERRCLR, 0x1);
	WRITE_REG(DMAx->IER, 0x0);
	WRITE_REG(DMAx->ICFR, 0x80000FFF);

	for (i = 0; i < DMA_CH_COUNT; ++i)
		WRITE_REG(DMAx->CH_SELCON[i], 0x0);

	return;
}

/**
  * @brief  DMA module initialization, this function
  *         is invoked by ald_cmu_init().
  * @param  DMAx: Pointer to DMA peripheral
  * @retval None
  */
void ald_dma_init(DMA_TypeDef *DMAx)
{
	assert_param(IS_DMA(DMAx));

	memset(dma0_ctrl_base, 0x0, sizeof(dma0_ctrl_base));
	memset(dma0_cbk, 0x0, sizeof(dma0_cbk));

	ald_dma_reset(DMAx);
	NVIC_SetPriority(DMA_IRQn, 2);
	NVIC_EnableIRQ(DMA_IRQn);
	SET_BIT(DMAx->IER, DMA_IER_DMAERRIE_MSK);

	WRITE_REG(DMAx->CTRLBASE, (uint32_t)&dma0_ctrl_base);
	SET_BIT(DMAx->CFG, DMA_CFG_MASTER_ENABLE_MSK);

	return;
}

/**
  * @brief  Configure dma_config_t structure using default parameter.
  *         User can invoked this function, before configure dma_config_t
  * @param  p: Pointer to dma_config_t structure, see @ref dma_config_t
  * @retval None
  */
void ald_dma_config_struct(dma_config_t *p)
{
	p->data_width = DMA_DATA_SIZE_BYTE;
	p->src_inc    = DMA_DATA_INC_BYTE;
	p->dst_inc    = DMA_DATA_INC_BYTE;
	p->R_power    = DMA_R_POWER_1;
	p->primary    = ENABLE;
	p->burst      = DISABLE;
	p->high_prio  = DISABLE;
	p->interrupt  = ENABLE;

	return;
}

/**
  * @brief  Configure dma_descriptor_t structure using specified parameter.
  * @note   This function used in scatter-gather mode(memory or peripheral).
  * @param  desc: Address of the alternate descriptor.
  * @param  config: Pointer to the dma_config_t structure.
  * @param  memory: Memory or peripheral scatter-gather.
  * @retval None
  */
void ald_dma_config_sg_alt_desc(dma_descriptor_t *desc, dma_config_t *config, uint8_t memory)
{
	if ((desc == NULL) || (config == NULL))
		return;

	if (config->src_inc == DMA_DATA_INC_NONE)
		desc->src = config->src;
	else
		desc->src = (void *)((uint32_t)config->src + ((config->size - 1) << (uint32_t)config->data_width));

	if (config->dst_inc == DMA_DATA_INC_NONE)
		desc->dst = config->dst;
	else
		desc->dst = (void *)((uint32_t)config->dst + ((config->size - 1) << (uint32_t)config->data_width));

	desc->ctrl.cycle_ctrl    = memory ? DMA_CYCLE_CTRL_MEM_SG_ALTERNATE : DMA_CYCLE_CTRL_PER_SG_ALTERNATE;
	desc->ctrl.next_useburst = memory ? 0 : 1;
	desc->ctrl.n_minus_1     = config->size - 1;
	desc->ctrl.R_power       = config->R_power;
	desc->ctrl.src_prot_ctrl = 0;
	desc->ctrl.dst_prot_ctrl = 0;
	desc->ctrl.src_size      = config->data_width;
	desc->ctrl.src_inc       = config->src_inc;
	desc->ctrl.dst_size      = config->data_width;
	desc->ctrl.dst_inc       = config->dst_inc;

	return;
}

/**
  * @}
  */

/** @defgroup DMA_Public_Functions_Group2 Configure DMA channel functions
  * @brief Configure DMA channel functions
  *
  * @verbatim
    ===================================================================

                    #### Configure DMA channel functions ####

    ===================================================================
    [..]
    This subsection provides some functions allowing to configure
    DMA channel. Include two type DMA transfer:
    (+) Carry data from memory to memory, this mode APIs are:
        (++) ald_dma_config_auto(): Configure DMA channel according to
	     the specified parameter in the dma_handle_t structure.
	(++) ald_dma_restart_auto(): Restart DMA transmitted.
        (++) ald_dma_config_auto_easy(): Configure DMA channel according
	     to the specified parameter. If you want use the dma easily,
             you can invoke this function.
        (++) ald_dma_config_sg_mem(): Carry data used scatter-gather mode.
    (+) Carry data from peripheral to memory or from memory to peripheral,
        this mode APIs are:
	(++) ald_dma_config_basic(): Configure DMA channel according to
	     the specified parameter in the dma_handle_t structure.
	(++) ald_dma_restart_basic(): Restart DMA transmitted.
        (++) ald_dma_config_basic_easy(): Configure DMA channel according
	     to the specified parameter. If you want use the dma easily,
             you can invoke this function.
        (++) ald_dma_ping_pong(): Carry data used ping-pong mode.
        (++) ald_dma_config_sg_per(): Carry data used scatter-gather mode.

    @endverbatim
  * @{
  */

/**
  * @brief  Configure DMA channel according to the specified parameter
  *         in the dma_handle_t structure. The DMA mode is automatic.
  *         This mode is used to carry data from memory to memory.
  * @param  hperh: Pointer to DMA_handle_t structure that contains
  *               configuration information for specified DMA channel.
  * @retval None
  */
void ald_dma_config_auto(dma_handle_t *hperh)
{
	dma0_cbk[hperh->config.channel].cplt_cbk = hperh->cplt_cbk;
	dma0_cbk[hperh->config.channel].err_cbk  = hperh->err_cbk;
	dma0_cbk[hperh->config.channel].cplt_arg = hperh->cplt_arg;
	dma0_cbk[hperh->config.channel].err_arg  = hperh->err_arg;
	dma_config_base(hperh->perh, DMA_CYCLE_CTRL_AUTO, &hperh->config);

	ald_dma_clear_flag_status(hperh->perh, hperh->config.channel);
	WRITE_REG(hperh->perh->CHENSET, (1 << hperh->config.channel));
	SET_BIT(hperh->perh->CHSWREQ, (1 << hperh->config.channel));

	return;
}

/**
  * @brief  Restart DMA transmitted. The DMA mode is automatic.
  *         The other parameters have not changed except 'size' and 'addr'.
  * @param  hperh: Pointer to DMA_handle_t structure that contains
  *               configuration information for specified DMA channel.
  * @param  src: Source data begin pointer
  * @param  dst: Destination data begin pointer
  * @param  size: Size.
  * @retval None
  */
void ald_dma_restart_auto(dma_handle_t *hperh, void *src, void *dst, uint16_t size)
{
	dma_descriptor_t *descr;

	if (hperh->config.primary)
		descr = (dma_descriptor_t *)(hperh->perh->CTRLBASE) + hperh->config.channel;
	else
		descr = (dma_descriptor_t *)(hperh->perh->ALTCTRLBASE) + hperh->config.channel;

	if (src) {
		if (hperh->config.src_inc == DMA_DATA_INC_NONE)
			descr->src = src;
		else
			descr->src = (void *)((uint32_t)src + ((size - 1) << (uint32_t)hperh->config.data_width));
	}

	if (dst) {
		if (hperh->config.dst_inc == DMA_DATA_INC_NONE)
			descr->dst = dst;
		else
			descr->dst = (void *)((uint32_t)dst + ((size - 1) << (uint32_t)hperh->config.data_width));
	}

	ald_dma_clear_flag_status(hperh->perh, hperh->config.channel);
	descr->ctrl.cycle_ctrl = DMA_CYCLE_CTRL_AUTO;
	descr->ctrl.n_minus_1  = size - 1;
	WRITE_REG(hperh->perh->CHENSET, (1 << hperh->config.channel));
	SET_BIT(hperh->perh->CHSWREQ, (1 << hperh->config.channel));
	return;
}



/**
  * @brief  Configure DMA channel according to the specified parameter.
  *         The DMA mode is automatic. This mode is used to carry data
  *         from memory to memory. If User want use the dma easily,
  *         they can invoke this function.
  * @param  DMAx: Pointer to DMA peripheral
  * @param  src: Source data begin pointer
  * @param  dst: Destination data begin pointer
  * @param  size: The total number of DMA transfers that DMA cycle contains
  * @param  channel: Channel index which will be used.
  * @param  cbk: DMA complete callback function
  *
  * @retval None
  */
void ald_dma_config_auto_easy(DMA_TypeDef *DMAx, void *src, void *dst,
                       uint16_t size, uint8_t channel, void (*cbk)(void *arg))
{
	dma_handle_t hperh;

	assert_param(IS_DMA(DMAx));

	ald_dma_config_struct(&hperh.config);
	hperh.config.src     = src;
	hperh.config.dst     = dst;
	hperh.config.size    = size;
	hperh.config.msel    = DMA_MSEL_NONE;
	hperh.config.msigsel = DMA_MSIGSEL_NONE;
	hperh.config.channel = channel;

	hperh.perh     = DMAx;
	hperh.cplt_cbk = cbk;
	hperh.cplt_arg = NULL;
	hperh.err_cbk  = NULL;

	ald_dma_clear_flag_status(DMAx, channel);
	ald_dma_config_auto(&hperh);

	return;
}

/**
  * @brief  Configure DMA channel according to the specified parameter
  *         in the dma_handle_t structure. The DMA mode is basic.
  *         This mode is used to carry data from peripheral to memory
  *         or from memory to peripheral.
  * @param  hperh: Pointer to dma_handle_t structure that contains
  *         configuration information for specified DMA channel.
  * @retval None
  */
void ald_dma_config_basic(dma_handle_t *hperh)
{
	dma0_cbk[hperh->config.channel].cplt_cbk = hperh->cplt_cbk;
	dma0_cbk[hperh->config.channel].err_cbk  = hperh->err_cbk;
	dma0_cbk[hperh->config.channel].cplt_arg = hperh->cplt_arg;
	dma0_cbk[hperh->config.channel].err_arg  = hperh->err_arg;

	ald_dma_clear_flag_status(hperh->perh, hperh->config.channel);
	dma_config_base(hperh->perh, DMA_CYCLE_CTRL_BASIC, &hperh->config);
	WRITE_REG(hperh->perh->CHENSET, (1 << hperh->config.channel));

	return;
}

/**
  * @brief  Restart DMA transmitted. The DMA mode is basic.
  *         The other parameters have not changed except 'size' and 'addr'.
  * @param  hperh: Pointer to DMA_handle_t structure that contains
  *               configuration information for specified DMA channel.
  * @param  src: Source data begin pointer
  * @param  dst: Destination data begin pointer
  * @param  size: Size.
  * @retval None
  */
void ald_dma_restart_basic(dma_handle_t *hperh, void *src, void *dst, uint16_t size)
{
	dma_descriptor_t *descr;

	if (hperh->config.primary)
		descr = (dma_descriptor_t *)(hperh->perh->CTRLBASE) + hperh->config.channel;
	else
		descr = (dma_descriptor_t *)(hperh->perh->ALTCTRLBASE) + hperh->config.channel;

	if (src) {
		if (hperh->config.src_inc == DMA_DATA_INC_NONE)
			descr->src = src;
		else
			descr->src = (void *)((uint32_t)src + ((size - 1) << (uint32_t)hperh->config.data_width));
	}

	if (dst) {
		if (hperh->config.dst_inc == DMA_DATA_INC_NONE)
			descr->dst = dst;
		else
			descr->dst = (void *)((uint32_t)dst + ((size - 1) << (uint32_t)hperh->config.data_width));
	}

	ald_dma_clear_flag_status(hperh->perh, hperh->config.channel);
	descr->ctrl.cycle_ctrl = DMA_CYCLE_CTRL_BASIC;
	descr->ctrl.n_minus_1  = size - 1;
	WRITE_REG(hperh->perh->CHENSET, (1 << hperh->config.channel));

	return;
}

/**
  * @brief  Configure DMA channel according to the specified parameter.
  *         The DMA mode is basic. This mode is used to carry data
  *         from peripheral to memory or negative direction. If user want
  *         use the dma easily, they can invoke this function.
  * @param  DMAx: Pointer to DMA peripheral
  * @param  src: Source data begin pointer
  * @param  dst: Destination data begin pointer
  * @param  size: The total number of DMA transfers that DMA cycle contains
  * @param  msel: Input source to DMA channel @ref dma_msel_t
  * @param  msigsel: Input signal to DMA channel @ref dma_msigsel_t
  * @param  channel: Channel index which will be used
  * @param  cbk: DMA complete callback function
  *
  * @retval None
  *
 */
void ald_dma_config_basic_easy(DMA_TypeDef *DMAx, void *src, void *dst, uint16_t size, dma_msel_t msel,
		dma_msigsel_t msigsel, uint8_t channel, void (*cbk)(void *arg))
{
	dma_handle_t hperh;

	assert_param(IS_DMA(DMAx));
	ald_dma_config_struct(&hperh.config);

	if (((uint32_t)src) >= 0x40000000)
		hperh.config.src_inc = DMA_DATA_INC_NONE;

	if (((uint32_t)dst) >= 0x40000000)
		hperh.config.dst_inc = DMA_DATA_INC_NONE;

	hperh.config.src     = src;
	hperh.config.dst     = dst;
	hperh.config.size    = size;
	hperh.config.msel    = msel;
	hperh.config.msigsel = msigsel;
	hperh.config.channel = channel;

	hperh.perh     = DMAx;
	hperh.cplt_cbk = cbk;
	hperh.cplt_arg = NULL;
	hperh.err_cbk  = NULL;

	ald_dma_clear_flag_status(DMAx, channel);
	ald_dma_config_basic(&hperh);

	return;
}

/**
  * @brief  Configure DMA channel according to the specified parameter.
  *         The DMA mode is ping-pong.
  * @note   The ping-pong mode does not support memory to memory.
  * @param  DMAx: Pointer to DMA peripheral.
  * @param  config: Pointer to the dma_config_t structure which contains
  *         the specified parameters.
  * @param  first: Whether it is the first transmission. 1-first, 0-not first.
  * @param  cbk: DMA complete callback function.
  * @retval None
  */
void ald_dma_config_ping_pong(DMA_TypeDef *DMAx, dma_config_t *config,
                                      uint8_t first, void (*cbk)(void *arg))
{
	dma_descriptor_t *desc;

	assert_param(IS_DMA(DMAx));
	assert_param(config->src != NULL);
	assert_param(config->dst != NULL);
	assert_param(IS_DMA_DATA_SIZE(config->size));
	assert_param(IS_DMA_DATASIZE_TYPE(config->data_width));
	assert_param(IS_DMA_DATAINC_TYPE(config->src_inc));
	assert_param(IS_DMA_DATAINC_TYPE(config->dst_inc));
	assert_param(IS_DMA_ARBITERCONFIG_TYPE(config->R_power));
	assert_param(IS_FUNC_STATE(config->primary));
	assert_param(IS_FUNC_STATE(config->burst));
	assert_param(IS_FUNC_STATE(config->high_prio));
	assert_param(IS_FUNC_STATE(config->interrupt));
	assert_param(IS_DMA_MSEL_TYPE(config->msel));
	assert_param(IS_DMA_MSIGSEL_TYPE(config->msigsel));
	assert_param(IS_DMA_CHANNEL(config->channel));

	dma0_cbk[config->channel].cplt_cbk = cbk;
	dma0_cbk[config->channel].err_cbk  = NULL;
	dma0_cbk[config->channel].cplt_arg = NULL;
	dma0_cbk[config->channel].err_arg  = NULL;

	if (config->primary)
		desc = (dma_descriptor_t *)(DMAx->CTRLBASE) + config->channel;
	else
		desc = (dma_descriptor_t *)(DMAx->ALTCTRLBASE) + config->channel;

	if (config->src_inc == DMA_DATA_INC_NONE)
		desc->src = config->src;
	else
		desc->src = (void *)((uint32_t)config->src + ((config->size - 1) << (uint32_t)config->data_width));

	if (config->dst_inc == DMA_DATA_INC_NONE)
		desc->dst = config->dst;
	else
		desc->dst = (void *)((uint32_t)config->dst + ((config->size - 1) << (uint32_t)config->data_width));

	desc->ctrl.cycle_ctrl    = DMA_CYCLE_CTRL_PINGPONG;
	desc->ctrl.next_useburst = 0;
	desc->ctrl.n_minus_1     = config->size - 1;
	desc->ctrl.R_power       = config->R_power;
	desc->ctrl.src_prot_ctrl = 0,
	desc->ctrl.dst_prot_ctrl = 0,
	desc->ctrl.src_size      = config->data_width;
	desc->ctrl.src_inc       = config->src_inc;
	desc->ctrl.dst_size      = config->data_width;
	desc->ctrl.dst_inc       = config->dst_inc;

	if (!first)
		return;

	if (config->primary)
		WRITE_REG(DMAx->CHPRIALTCLR, (1 << config->channel));
	else
		WRITE_REG(DMAx->CHPRIALTSET, (1 << config->channel));

	if (config->burst)
		WRITE_REG(DMAx->CHUSEBURSTSET, (1 << config->channel));
	else
		WRITE_REG(DMAx->CHUSEBURSTCLR, (1 << config->channel));

	if (config->high_prio)
		WRITE_REG(DMAx->CHPRSET, (1 << config->channel));
	else
		WRITE_REG(DMAx->CHPRCLR, (1 << config->channel));

	if (config->interrupt)
		SET_BIT(DMAx->IER, (1 << config->channel));
	else
		CLEAR_BIT(DMAx->IER, (1 << config->channel));

	MODIFY_REG(DMAx->CH_SELCON[config->channel], DMA_CH0_SELCON_MSEL_MSK, config->msel << DMA_CH0_SELCON_MSEL_POSS);
	MODIFY_REG(DMAx->CH_SELCON[config->channel], DMA_CH0_SELCON_MSIGSEL_MSK, config->msigsel << DMA_CH0_SELCON_MSIGSEL_POSS);

	WRITE_REG(DMAx->ICFR, (1 << config->channel));
	WRITE_REG(DMAx->CHENSET, (1 << config->channel));

	return;
}

/**
  * @brief  Configure DMA channel according to the specified parameter.
  *         The DMA mode is memory scatter-gather.
  * @param  DMAx: Pointer to DMA peripheral.
  * @param  desc: Pointer to first alternate descriptor.
  * @param  nr: Number of the alternate descriptor.
  * @param  channel: Channel index which will be used.
  * @param  cbk: DMA complete callback function.
  * @retval None
 */
void ald_dma_config_sg_mem(DMA_TypeDef *DMAx, dma_descriptor_t *desc, uint32_t nr,
	                          uint8_t channel, void (*cbk)(void *arg))
{
	dma_descriptor_t *tmp  = (dma_descriptor_t *)(DMAx->CTRLBASE) + channel;
	dma_descriptor_t *_tmp = (dma_descriptor_t *)(DMAx->ALTCTRLBASE) + channel;

	assert_param(IS_DMA(DMAx));
	assert_param(IS_DMA_CHANNEL(channel));

	if ((desc == NULL) || (nr == 0))
		return;

	dma0_cbk[channel].cplt_cbk = cbk;
	dma0_cbk[channel].err_cbk  = NULL;
	dma0_cbk[channel].cplt_arg = NULL;
	dma0_cbk[channel].err_arg  = NULL;

	tmp->src = (void *)((uint32_t)desc + (((nr << 2) - 1) << DMA_DATA_INC_WORD));
	tmp->dst = (void *)((uint32_t)_tmp + ((4 - 1) << DMA_DATA_INC_WORD));
	tmp->ctrl.cycle_ctrl    = DMA_CYCLE_CTRL_MEM_SG_PRIMARY;
	tmp->ctrl.next_useburst = 0;
	tmp->ctrl.n_minus_1     = (nr << 2) - 1;
	tmp->ctrl.R_power       = DMA_R_POWER_4;
	tmp->ctrl.src_prot_ctrl = 0,
	tmp->ctrl.dst_prot_ctrl = 0,
	tmp->ctrl.src_size      = DMA_DATA_SIZE_WORD;
	tmp->ctrl.src_inc       = DMA_DATA_INC_WORD;
	tmp->ctrl.dst_size      = DMA_DATA_SIZE_WORD;
	tmp->ctrl.dst_inc       = DMA_DATA_INC_WORD;

	desc[nr - 1].ctrl.cycle_ctrl = DMA_CYCLE_CTRL_AUTO;
	WRITE_REG(DMAx->CHPRIALTCLR, (1 << channel));
	WRITE_REG(DMAx->CHUSEBURSTCLR, (1 << channel));
	WRITE_REG(DMAx->CHPRCLR, (1 << channel));

	WRITE_REG(DMAx->ICFR, (1 << channel));
	SET_BIT(DMAx->IER, (1 << channel));
	WRITE_REG(DMAx->CHENSET, (1 << channel));
	SET_BIT(DMAx->CHSWREQ, (1 << channel));

	return;
}

/**
  * @brief  Configure DMA channel according to the specified parameter.
  *         The DMA mode is peripheral scatter-gather.
  * @note   The size of the first transmission must be 5.
  * @param  DMAx: Pointer to DMA peripheral.
  * @param  desc: Pointer to first alternate descriptor.
  * @param  nr: Number of the alternate descriptor.
  * @param  burst: 1-Enable burst, 0-Disable burst.
  * @param  msel: Input source to DMA channel @ref dma_msel_t
  * @param  msigsel: Input signal to DMA channel @ref dma_msigsel_t
  * @param  channel: Channel index which will be used.
  * @param  cbk: DMA complete callback function.
  * @retval None
 */
void ald_dma_config_sg_per(DMA_TypeDef *DMAx, dma_descriptor_t *desc, uint32_t nr, uint8_t burst,
                    dma_msel_t msel, dma_msigsel_t msigsel, uint8_t channel, void (*cbk)(void *arg))
{
	dma_descriptor_t *tmp  = (dma_descriptor_t *)(DMAx->CTRLBASE) + channel;
	dma_descriptor_t *_tmp = (dma_descriptor_t *)(DMAx->ALTCTRLBASE) + channel;

	assert_param(IS_DMA(DMAx));
	assert_param(IS_DMA_MSEL_TYPE(msel));
	assert_param(IS_DMA_MSIGSEL_TYPE(msigsel));
	assert_param(IS_DMA_CHANNEL(channel));

	if ((desc == NULL) || (nr == 0))
		return;

	dma0_cbk[channel].cplt_cbk = cbk;
	dma0_cbk[channel].err_cbk  = NULL;
	dma0_cbk[channel].cplt_arg = NULL;
	dma0_cbk[channel].err_arg  = NULL;

	tmp->src = (void *)((uint32_t)desc + (((nr << 2) - 1) << DMA_DATA_INC_WORD));
	tmp->dst = (void *)((uint32_t)_tmp + ((4 - 1) << DMA_DATA_INC_WORD));
	tmp->ctrl.cycle_ctrl    = DMA_CYCLE_CTRL_PER_SG_PRIMARY;
	tmp->ctrl.next_useburst = 0;
	tmp->ctrl.n_minus_1     = (nr << 2) - 1;
	tmp->ctrl.R_power       = DMA_R_POWER_4;
	tmp->ctrl.src_prot_ctrl = 0,
	tmp->ctrl.dst_prot_ctrl = 0,
	tmp->ctrl.src_size      = DMA_DATA_SIZE_WORD;
	tmp->ctrl.src_inc       = DMA_DATA_INC_WORD;
	tmp->ctrl.dst_size      = DMA_DATA_SIZE_WORD;
	tmp->ctrl.dst_inc       = DMA_DATA_INC_WORD;

	desc[nr - 1].ctrl.cycle_ctrl = DMA_CYCLE_CTRL_BASIC;
	WRITE_REG(DMAx->CHPRIALTCLR, (1 << channel));
	burst ? (DMAx->CHUSEBURSTSET = (1 << channel)) : (DMAx->CHUSEBURSTCLR, (1 << channel));
	WRITE_REG(DMAx->CHPRCLR, (1 << channel));

	MODIFY_REG(DMAx->CH_SELCON[channel], DMA_CH0_SELCON_MSEL_MSK, msel << DMA_CH0_SELCON_MSEL_POSS);
	MODIFY_REG(DMAx->CH_SELCON[channel], DMA_CH0_SELCON_MSIGSEL_MSK, msigsel << DMA_CH0_SELCON_MSIGSEL_POSS);

	WRITE_REG(DMAx->ICFR, (1 << channel));
	SET_BIT(DMAx->IER, (1 << channel));
	WRITE_REG(DMAx->CHENSET, (1 << channel));

	return;
}
/**
  * @}
  */

/** @defgroup DMA_Public_Functions_Group3 DMA Control functions
  * @brief DMA control functions
  *
  * @verbatim
    ===================================================================

                    #### DMA control functions ####

    ===================================================================
    [..]
    This subsection provides some functions allowing to control DMA:
    (+) ald_dma_channel_config(): Control DMA channel ENABLE/DISABLE.
    (+) ald_dma_interrupt_config(): Control DMA channel interrupt ENABLE or
        DISABLE.
    (+) ald_dma_get_it_status(): Check whether the specified channel
        interrupt is SET or RESET.
    (+) ald_dma_get_flag_status(): Check whether the specified channel
        flag is SET or RESET.
    (+) ald_dma_clear_flag_status(): Clear the specified channel
        pending flag

    @endverbatim
  * @{
  */

/**
  * @brief  Configure channel enable or disable. It will unbind descriptor with
  *         channel, when channel has been disable.
  * @param  DMAx: Pointer to DMA peripheral
  * @param  channel: channel index
  * @param  state: status of channel:
  *           @arg ENABLE: Enable the channel
  *           @arg DISABLE: Disable the channel
  * @retval None
  */
void ald_dma_channel_config(DMA_TypeDef *DMAx, uint8_t channel, type_func_t state)
{
	dma_descriptor_t *descr, *alt_descr;

	assert_param(IS_DMA(DMAx));
	assert_param(IS_DMA_CHANNEL(channel));
	assert_param(IS_FUNC_STATE(state));

	descr     = (dma_descriptor_t *)(DMAx->CTRLBASE) + channel;
	alt_descr = (dma_descriptor_t *)(DMAx->ALTCTRLBASE) + channel;

	if (state) {
		WRITE_REG(DMAx->CHENSET, (1 << channel));
	}
	else {
		memset(descr, 0x00, sizeof(dma_descriptor_t));
		memset(alt_descr, 0x00, sizeof(dma_descriptor_t));
		WRITE_REG(DMAx->CH_SELCON[channel], 0x0);
		WRITE_REG(DMAx->CHENCLR, (1 << channel));
	}

	return;
}

/**
  * @brief  Configure the interrupt enable or disable
  * @param  DMAx: Pointer to DMA peripheral
  * @param  channel: Channel index or DMA_ERR.
  *           @arg 0~11: Channel index
  *           @arg DMA_ERR: DMA bus error
  * @param  state: status of channel:
  *           @arg ENABLE: Enable the channel
  *           @arg DISABLE: Disable the channel
  *
  * @retval None
  */
void ald_dma_interrupt_config(DMA_TypeDef *DMAx, uint8_t channel, type_func_t state)
{
	assert_param(IS_DMA(DMAx));
	assert_param(IS_DMA_IT_TYPE(channel));
	assert_param(IS_FUNC_STATE(state));

	if (state)
		SET_BIT(DMAx->IER, (1 << channel));
	else
		CLEAR_BIT(DMAx->IER, (1 << channel));

	return;
}

/**
  * @brief  Check whether the specified channel interrupt
  *         is set or reset
  * @param  DMAx: Pointer to DMA peripheral
  * @param  channel: Channel index or DMA_ERR
  *           @arg 0~11: Channel index
  *           @arg DMA_ERR: DMA bus error
  * @retval Status:
  *           - SET: Channel interrupt is set
  *           - RESET: Channel interrupt is reset
  */
it_status_t ald_dma_get_it_status(DMA_TypeDef *DMAx, uint8_t channel)
{
	assert_param(IS_DMA(DMAx));
	assert_param(IS_DMA_IT_TYPE(channel));

	if (READ_BIT(DMAx->IER, (1 << channel)))
		return SET;

	return RESET;
}

/**
  * @brief  Check whether the specified channel flag
  *         is set or reset
  * @param  DMAx: Pointer to DMA peripheral
  * @param  channel: Channel index or DMA_ERR
  *           @arg 0~11: Channel index
  *           @arg DMA_ERR: DMA bus error
  * @retval Status:
  *           - SET: Channel flag is set
  *           - RESET: Channel flag is reset
  */
flag_status_t ald_dma_get_flag_status(DMA_TypeDef *DMAx, uint8_t channel)
{
	assert_param(IS_DMA(DMAx));
	assert_param(IS_DMA_IT_TYPE(channel));

	if (READ_BIT(DMAx->IFLAG, (1 << channel)))
		return SET;

	return RESET;
}

/**
  * @brief  Clear the specified channel pending flag
  * @param  DMAx: Pointer to DMA peripheral
  * @param  channel: Channel index or DMA_ERR
  *           @arg 0~11: Channel index
  *           @arg DMA_ERR: DMA bus error
  * @retval None
  */
void ald_dma_clear_flag_status(DMA_TypeDef *DMAx, uint8_t channel)
{
	assert_param(IS_DMA(DMAx));
	assert_param(IS_DMA_IT_TYPE(channel));

	WRITE_REG(DMAx->ICFR, (1 << channel));
	return;
}

/**
  * @brief  Get the completion status of the descriptor
  * @param  DMAx: Pointer to DMA peripheral
  * @param  channel: Channel index
  * @retval Completion status:
  *           - DMA_DESCP_CPLT_PRI: Primary descriptor has been completed
  *           - DMA_DESCP_CPLT_ALT: Alternate descriptor has been completed
  *           - DMA_DESCP_CPLT_ALL: Both primary and alternate descriptors have been completed
  */
dma_descrp_cplt_t ald_dma_descriptor_cplt_get(DMA_TypeDef *DMAx, uint8_t channel)
{
	uint8_t pri, alt;
	dma_descriptor_t *desc;

	assert_param(IS_DMA(DMAx));
	assert_param(IS_DMA_IT_TYPE(channel));

	desc = (dma_descriptor_t *)(DMAx->CTRLBASE) + channel;
	pri  = desc->ctrl.cycle_ctrl;
	desc = (dma_descriptor_t *)(DMAx->ALTCTRLBASE) + channel;
	alt  = desc->ctrl.cycle_ctrl;

	if ((pri == 0) && (alt == 0))
		return DMA_DESCP_CPLT_ALL;

	if (pri == 0)
		return DMA_DESCP_CPLT_PRI;
	else
		return DMA_DESCP_CPLT_ALT;
}
/**
  * @}
  */

/**
  * @}
  */
#endif /* ALD_DMA */
/**
  * @}
  */

/**
  * @}
  */
