/**
  *********************************************************************************
  *
  * @file    ald_ebi.c
  * @brief   EBI module driver.
  *
  * @version V1.0
  * @date    20 Jan 2019
  * @author  AE Team
  * @note
  *
  * Copyright (C) Shanghai Eastsoft Microelectronics Co. Ltd. All rights reserved.
  ******************************************************************************
  */

#include "ald_ebi.h"

/** @addtogroup ES32FXXX_ALD
  * @{
  */

/** @defgroup EBI EBI
  * @brief EBI module driver
  * @{
  */  
#ifdef ALD_EBI

/** @defgroup EBI_Public_Functions EBI Public Functions
  * @{
  */

/** @defgroup EBI_Public_Functions_Group1 NOR-FLASH SRAM initialize functions
  * @brief NOR-FLASH SRAM initialize functions
  * @{
  */  
/**
  * @brief  Initialize the EBI_NOR_SRAM device according to the specified
  *         control parameters in the EBI_NOR_SRAM_InitTypeDef
  * @param  dev: Pointer to NOR_SRAM device instance
  * @param  init: Pointer to NOR_SRAM Initialization structure
  * @retval None
  */
void ald_ebi_nor_sram_init(EBI_NOR_SRAM_TypeDef *dev, ald_ebi_nor_sram_init_t *init)
{
	assert_param(IS_EBI_NORSRAM_DEVICE(dev));
	assert_param(IS_EBI_NORSRAM_BANK(init->bank));
	assert_param(IS_EBI_MUX(init->mux));
	assert_param(IS_EBI_MEMORY(init->type));
	assert_param(IS_EBI_NORSRAM_MEMORY_WIDTH(init->width));
	assert_param(IS_EBI_BURSTMODE(init->acc_mode));
	assert_param(IS_EBI_WAIT_POLARITY(init->polarity));
	assert_param(IS_EBI_WRAP_MODE(init->wrap_mode));
	assert_param(IS_EBI_WAIT_SIGNAL_ACTIVE(init->active));
	assert_param(IS_EBI_WRITE_OPERATION(init->write));
	assert_param(IS_EBI_WAITE_SIGNAL(init->signal));
	assert_param(IS_EBI_EXTENDED_MODE(init->ext_mode));
	assert_param(IS_EBI_ASYNWAIT(init->wait));
	assert_param(IS_EBI_WRITE_BURST(init->burst));

	/* Disable NORSRAM device */
	ald_ebi_nor_sram_disable(dev, init->bank);

	/* Set NORSRAM device control parameters */
	if (init->type == EBI_MEMORY_TYPE_NOR) {
		MODIFY_REG(dev->BTCR[init->bank], BCTRLR_CLEAR_MASK, (uint32_t)((uint32_t)EBI_NORSRAM_FLASH_ACCESS_ENABLE
		       | (uint32_t)init->mux
		       | (uint32_t)init->type
		       | (uint32_t)init->width
		       | (uint32_t)init->acc_mode
		       | (uint32_t)init->polarity
		       | (uint32_t)init->wrap_mode
		       | (uint32_t)init->active
		       | (uint32_t)init->write
		       | (uint32_t)init->signal
		       | (uint32_t)init->ext_mode
		       | (uint32_t)init->wait
		       | (uint32_t)init->burst));
	}
	else {
		MODIFY_REG(dev->BTCR[init->bank], BCTRLR_CLEAR_MASK, (uint32_t)(EBI_NORSRAM_FLASH_ACCESS_DISABLE
		       | (uint32_t)init->mux
		       | (uint32_t)init->type
		       | (uint32_t)init->width
		       | (uint32_t)init->acc_mode
		       | (uint32_t)init->polarity
		       | (uint32_t)init->wrap_mode
		       | (uint32_t)init->active
		       | (uint32_t)init->write
		       | (uint32_t)init->signal
		       | (uint32_t)init->ext_mode
		       | (uint32_t)init->wait
		       | (uint32_t)init->burst));
	}
}

/**
  * @brief  Initialize the EBI_NOR_SRAM Timing according to the specified
  *         parameters in the EBI_NOR_SRAM_TimingTypeDef
  * @param  dev: Pointer to NOR_SRAM device instance
  * @param  timing: Pointer to NOR_SRAM Timing structure
  * @param  bank: NOR_SRAM bank number
  * @retval None
  */
void ald_ebi_nor_sram_timing_init(EBI_NOR_SRAM_TypeDef *dev, ald_ebi_nor_sram_timing_t *timing, uint32_t bank)
{
	assert_param(IS_EBI_NORSRAM_DEVICE(dev));
	assert_param(IS_EBI_ADDRESS_SETUP_TIME(timing->addr_setup));
	assert_param(IS_EBI_ADDRESS_HOLD_TIME(timing->addr_hold));
	assert_param(IS_EBI_DATASETUP_TIME(timing->data_setup));
	assert_param(IS_EBI_TURNAROUND_TIME(timing->bus_dur));
	assert_param(IS_EBI_DATA_LATENCY(timing->latency));
	assert_param(IS_EBI_ACCESS_MODE(timing->mode));
	assert_param(IS_EBI_NORSRAM_BANK(bank));

	/* Set EBI_NORSRAM device timing parameters */
	MODIFY_REG(dev->BTCR[bank + 1U], BTR_CLEAR_MASK,                       \
		(uint32_t)(timing->addr_setup                                | \
			((timing->addr_hold)      << EBI_BTRx_ADDHOLD_POSS)  | \
			((timing->data_setup)     << EBI_BTRx_DATAHOLD_POSS) | \
			((timing->bus_dur)	  << EBI_BTRx_BUSTURN_POSS)  | \
			(((timing->div) - 1U)     << EBI_BTRx_CLKDIV_POSS)   | \
			(((timing->latency) - 1U) << EBI_BTRx_DATALAT_POSS)  | \
			(timing->mode)));
}

/**
  * @brief  Initialize the EBI_NOR_SRAM Extended mode Timing according to the specified
  *         parameters in the EBI_NOR_SRAM_TimingTypeDef
  * @param  dev: Pointer to NOR_SRAM device instance
  * @param  timing: Pointer to NOR_SRAM Timing structure
  * @param  bank: NOR_SRAM bank number
  * @param  mode EBI Extended Mode
  *         This parameter can be one of the following values:
  *            @arg EBI_EXTENDED_MODE_DISABLE
  *            @arg EBI_EXTENDED_MODE_ENABLE
  * @retval None
  */
void ald_ebi_nor_sram_ext_timing_init(EBI_NOR_SRAM_EXTENDED_TypeDef *dev, ald_ebi_nor_sram_timing_t *timing, uint32_t bank, uint32_t mode)
{
	assert_param(IS_EBI_EXTENDED_MODE(mode));

	/* Set NORSRAM device timing register for write configuration, if extended mode is used */
	if (mode == EBI_EXTENDED_MODE_ENABLE) {
		assert_param(IS_EBI_NORSRAM_EXTENDED_DEVICE(dev));
		assert_param(IS_EBI_ADDRESS_SETUP_TIME(timing->addr_setup));
		assert_param(IS_EBI_ADDRESS_HOLD_TIME(timing->addr_hold));
		assert_param(IS_EBI_DATASETUP_TIME(timing->data_setup));
		assert_param(IS_EBI_TURNAROUND_TIME(timing->bus_dur));
		assert_param(IS_EBI_ACCESS_MODE(timing->mode));
		assert_param(IS_EBI_NORSRAM_BANK(bank));

		/* Set NORSRAM device timing register for write configuration, if extended mode is used */
		MODIFY_REG(dev->BWTR[bank], BWTR_CLEAR_MASK,                              \
		       (uint32_t)(timing->addr_setup                                    | \
				  ((timing->addr_hold)  << EBI_BWRTRx_ADDHOLD_POSS)	 | \
				  ((timing->data_setup) << EBI_BWRTRx_DATAHOLD_POSS)	 | \
				  timing->mode                                          | \
				  ((timing->bus_dur)    << EBI_BWRTRx_BUSTURN_POSS)));
	}
	else {
		dev->BWTR[bank] = 0x0FFFFFFFU;
	}
}

/**
  * @brief  DeInitialize the EBI_NOR_SRAM peripheral 
  * @param  dev: Pointer to NOR_SRAM device instance
  * @param  e_dev: Pointer to NOR_SRAM extended mode device instance
  * @param  bank: NOR_SRAM bank number  
  * @retval ald status
  */
ald_status_t ald_ebi_nor_sram_deinit(EBI_NOR_SRAM_TypeDef *dev, EBI_NOR_SRAM_EXTENDED_TypeDef *e_dev, uint32_t bank)
{
	assert_param(IS_EBI_NORSRAM_DEVICE(dev));
	assert_param(IS_EBI_NORSRAM_EXTENDED_DEVICE(e_dev));
	assert_param(IS_EBI_NORSRAM_BANK(bank));

	/* Disable the EBI_NOR/SRAM device */
	ald_ebi_nor_sram_disable(dev, bank);

	/* De-initialize the EBI_NOR/SRAM device */
	if (bank == EBI_NORSRAM_BANK1)
		dev->BTCR[bank] = 0x000030DBU;
	else
		dev->BTCR[bank] = 0x000030D2U;

	dev->BTCR[bank + 1U] = 0x0FFFFFFFU;
	e_dev->BWTR[bank]    = 0x0FFFFFFFU;

	return OK;
}
/**
  * @}
  */

/** @defgroup EBI_Public_Functions_Group2 NOR-FLASH SRAM control functions
  * @brief NOR-FLASH SRAM control functions
  * @{
  */
/**
  * @brief  Enable the NOR/SRAM device access.
  * @param  dev: NOR/SRAM Instance
  * @param  bank: NOR/SRAM Bank
  * @retval none
  */
void ald_ebi_nor_sram_enable(EBI_NOR_SRAM_TypeDef *dev, uint32_t bank)
{
	assert_param(IS_EBI_NORSRAM_DEVICE(dev));
	assert_param(IS_EBI_NORSRAM_BANK(bank));

	SET_BIT(dev->BTCR[bank], EBI_BCTRLRx_MEMBKEN_MSK);
}

/**
  * @brief  Disable the NORSRAM device access.
  * @param  dev: EBI_NORSRAM Instance
  * @param  bank: EBI_NORSRAM Bank
  * @retval none
  */
void ald_ebi_nor_sram_disable(EBI_NOR_SRAM_TypeDef *dev, uint32_t bank)
{
	assert_param(IS_EBI_NORSRAM_DEVICE(dev));
	assert_param(IS_EBI_NORSRAM_BANK(bank));

	CLEAR_BIT(dev->BTCR[bank], EBI_BCTRLRx_MEMBKEN_MSK);
}

/**
  * @brief  Enables dynamically NOR-FLASH/SRAM write operation.
  * @param  dev: Pointer to NOR/SRAM device instance
  * @param  bank: NOR/SRAM bank number
  * @retval void
  */
void ald_ebi_nor_sram_write_enable(EBI_NOR_SRAM_TypeDef *dev, uint32_t bank)
{
	assert_param(IS_EBI_NORSRAM_DEVICE(dev));
	assert_param(IS_EBI_NORSRAM_BANK(bank));

	/* Enable write operation */
	SET_BIT(dev->BTCR[bank], EBI_WRITE_OPERATION_ENABLE);
}

/**
  * @brief  Disables dynamically EBI_NORSRAM write operation.
  * @param  dev: Pointer to NORSRAM device instance
  * @param  bank: NORSRAM bank number
  * @retval None
  */
void ald_ebi_nor_sram_write_disable(EBI_NOR_SRAM_TypeDef *dev, uint32_t bank)
{
	assert_param(IS_EBI_NORSRAM_DEVICE(dev));
	assert_param(IS_EBI_NORSRAM_BANK(bank));

	/* Disable write operation */
	CLEAR_BIT(dev->BTCR[bank], EBI_WRITE_OPERATION_ENABLE);
}
/**
  * @}
  */

/** @defgroup EBI_Public_Functions_Group3 NAND-FLASH initialize functions
  * @brief NAND-FLASH initialize functions
  * @{
  */
/**
  * @brief  Initializes the EBI_NAND device according to the specified
  *         control parameters in the EBI_NAND_HandleTypeDef
  * @param  dev: Pointer to NAND device instance
  * @param  init: Pointer to NAND Initialization structure
  * @retval None
  */
void ald_ebi_nand_init(EBI_NAND_TypeDef *dev, ald_ebi_nand_init_t *init)
{
	assert_param(IS_EBI_NAND_DEVICE(dev));
	assert_param(IS_EBI_NAND_BANK(init->bank));
	assert_param(IS_EBI_WAIT_FEATURE(init->wait));
	assert_param(IS_EBI_NAND_MEMORY_WIDTH(init->width));
	assert_param(IS_EBI_ECC_STATE(init->ecc));
	assert_param(IS_EBI_ECCPAGE_SIZE(init->size));
	assert_param(IS_EBI_TCLR_TIME(init->cle_time));
	assert_param(IS_EBI_TAR_TIME(init->ale_time));

	/* Set NAND device control parameters */
	if (init->bank == EBI_NAND_BANK2) {
		MODIFY_REG(dev->PCTRLR2, PCTRLR_CLEAR_MASK, ((uint32_t)init->wait      |
				(uint32_t)EBI_PCTRLR_MEMORY_TYPE_NAND                  |
				(uint32_t)init->width                                  |
				(uint32_t)init->ecc                                    |
				(uint32_t)init->size                                   |
				(uint32_t)((init->cle_time) << EBI_PCTRLRx_CRDLY_POSS) |
				(uint32_t)((init->ale_time) << EBI_PCTRLRx_ARDLY_POSS)));
	}
	else {
		MODIFY_REG(dev->PCTRLR3, PCTRLR_CLEAR_MASK, ((uint32_t)init->wait      |
				(uint32_t)EBI_PCTRLR_MEMORY_TYPE_NAND                  |
				(uint32_t)init->width                                  |
				(uint32_t)init->ecc                                    |
				(uint32_t)init->size                                   |
				(uint32_t)((init->cle_time) << EBI_PCTRLRx_CRDLY_POSS) |
				(uint32_t)((init->ale_time) << EBI_PCTRLRx_ARDLY_POSS)));
	}
}

/**
  * @brief  Initializes the EBI_NAND Common space Timing according to the specified
  *         parameters in the EBI_NAND_TimingTypeDef
  * @param  dev: Pointer to NAND device instance
  * @param  timing: Pointer to NAND timing structure
  * @param  bank: NAND bank number
  * @retval None
  */
void ald_ebi_nand_comm_timing_init(EBI_NAND_TypeDef *dev, ald_ebi_nand_timing_t *timing, uint32_t bank)
{
	assert_param(IS_EBI_NAND_DEVICE(dev));
	assert_param(IS_EBI_SETUP_TIME(timing->time));
	assert_param(IS_EBI_WAIT_TIME(timing->wait_time));
	assert_param(IS_EBI_HOLD_TIME(timing->hold_time));
	assert_param(IS_EBI_HIZ_TIME(timing->hiz_time));
	assert_param(IS_EBI_NAND_BANK(bank));

	/* Set EBI_NAND device timing parameters */
	if (bank == EBI_NAND_BANK2) {
		MODIFY_REG(dev->PMEMR2, PMEMR_CLEAR_MASK, (timing->time          | \
				((timing->wait_time) << EBI_PMEMRx_MEMWAIT_POSS) | \
				((timing->hold_time) << EBI_PMEMRx_MEMHOLD_POSS) | \
				((timing->hiz_time)  << EBI_PMEMRx_MEMHIZT_POSS)));
	}
	else {
		MODIFY_REG(dev->PMEMR3, PMEMR_CLEAR_MASK, (timing->time          | \
				((timing->wait_time) << EBI_PMEMRx_MEMWAIT_POSS) | \
				((timing->hold_time) << EBI_PMEMRx_MEMHOLD_POSS) | \
				((timing->hiz_time)  << EBI_PMEMRx_MEMHIZT_POSS)));
	}
}

/**
  * @brief  Initializes the EBI_NAND Attribute space Timing according to the specified
  *         parameters in the EBI_NAND_TimingTypeDef
  * @param  dev: Pointer to NAND device instance
  * @param  timing: Pointer to NAND timing structure
  * @param  bank: NAND bank number
  * @retval None
  */
void ald_ebi_nand_attr_timing_init(EBI_NAND_TypeDef *dev, ald_ebi_nand_timing_t *timing, uint32_t bank)
{
	assert_param(IS_EBI_NAND_DEVICE(dev));
	assert_param(IS_EBI_SETUP_TIME(timing->time));
	assert_param(IS_EBI_WAIT_TIME(timing->wait_time));
	assert_param(IS_EBI_HOLD_TIME(timing->hold_time));
	assert_param(IS_EBI_HIZ_TIME(timing->hiz_time));
	assert_param(IS_EBI_NAND_BANK(bank));

	/* Set FMC_NAND device timing parameters */
	if (bank == EBI_NAND_BANK2) {
		MODIFY_REG(dev->PATTR2, PATTR_CLEAR_MASK, (timing->time       | \
				((timing->wait_time) << EBI_PATTRx_ATTWAIT_POSS) | \
				((timing->hold_time) << EBI_PATTRx_ATTHOLD_POSS) | \
				((timing->hiz_time)  << EBI_PATTRx_ATTHIZT_POSS)));
	}
	else {
		MODIFY_REG(dev->PATTR3, PATTR_CLEAR_MASK, (timing->time       | \
				((timing->wait_time) << EBI_PATTRx_ATTWAIT_POSS) | \
				((timing->hold_time) << EBI_PATTRx_ATTHOLD_POSS) | \
				((timing->hiz_time)  << EBI_PATTRx_ATTHIZT_POSS)));
	}
}

/**
  * @brief  DeInitializes the EBI_NAND device 
  * @param  dev: Pointer to NAND device instance
  * @param  bank: NAND bank number
  * @retval None
  */
void ald_ebi_nand_deinit(EBI_NAND_TypeDef *dev, uint32_t bank)
{
	assert_param(IS_EBI_NAND_DEVICE(dev));
	assert_param(IS_EBI_NAND_BANK(bank));

	/* Disable the NAND Bank */
	ald_ebi_nand_disable(dev, bank);

	/* De-initialize the NAND Bank */
	if (bank == EBI_NAND_BANK2) {
		/* Set the EBI_NAND_BANK2 registers to their reset values */
		WRITE_REG(dev->PCTRLR2,  0x00000018U);
		WRITE_REG(dev->STAR2,    0x00000040U);
		WRITE_REG(dev->PMEMR2,   0xFCFCFCFCU);
		WRITE_REG(dev->PATTR2,   0xFCFCFCFCU);
	}
	/* EBI_Bank3_NAND */
	else {
		/* Set the EBI_NAND_BANK3 registers to their reset values */
		WRITE_REG(dev->PCTRLR3, 0x00000018U);
		WRITE_REG(dev->STAR3,   0x00000040U);
		WRITE_REG(dev->PMEMR3,  0xFCFCFCFCU);
		WRITE_REG(dev->PATTR3,  0xFCFCFCFCU);
	}
}
/**
  * @}
  */

/** @defgroup EBI_Public_Functions_Group4 NAND-FLASH control functions
  * @brief NAND-FLASH control functions
  * @{
  */ 
/**
  * @brief  Enable the NAND device access
  * @param  dev: EBI_NAND Instance
  * @param  bank: EBI_NAND Bank
  * @retval None
  */
void ald_ebi_nand_enable(EBI_NAND_TypeDef *dev, uint32_t bank)
{
	assert_param(IS_EBI_NAND_DEVICE(dev));
	assert_param(IS_EBI_NAND_BANK(bank));

	if (bank == EBI_NAND_BANK2)
		SET_BIT(dev->PCTRLR2, EBI_PCTRLRx_MEMBKEN_MSK);
	else
		SET_BIT(dev->PCTRLR3, EBI_PCTRLRx_MEMBKEN_MSK);
}

/**
  * @brief  Disable the NAND device access.
  * @param  dev: EBI_NAND Instance
  * @param  bank: EBI_NAND Bank
  * @retval None
  */
void ald_ebi_nand_disable(EBI_NAND_TypeDef *dev, uint32_t bank)
{
	assert_param(IS_EBI_NAND_DEVICE(dev));
	assert_param(IS_EBI_NAND_BANK(bank));

	if (bank == EBI_NAND_BANK2)
		CLEAR_BIT(dev->PCTRLR2, EBI_PCTRLRx_MEMBKEN_MSK);
	else
		CLEAR_BIT(dev->PCTRLR3, EBI_PCTRLRx_MEMBKEN_MSK);
}

/**
  * @brief  Enable the NAND device interrupt.
  * @param  dev: EBI_NAND Instance
  * @param  bank: EBI_NAND Bank
  * @param  it: EBI_NAND interrupt
  *         This parameter can be any combination of the following values:
  *            @arg EBI_IT_RISING_EDGE: Interrupt rising edge.
  *            @arg EBI_IT_LEVEL: Interrupt level.
  *            @arg EBI_IT_FALLING_EDGE: Interrupt falling edge.
  * @retval None
  */
void ald_ebi_nand_enable_it(EBI_NAND_TypeDef *dev, uint32_t bank, ebi_it_t it)
{
	assert_param(IS_EBI_NAND_DEVICE(dev));
	assert_param(IS_EBI_NAND_BANK(bank));

	if (bank == EBI_NAND_BANK2)
		SET_BIT(dev->STAR2, it);
	else
		SET_BIT(dev->STAR3, it);
}

/**
  * @brief  Disable the NAND device interrupt.
  * @param  dev: EBI_NAND Instance
  * @param  bank: EBI_NAND Bank
  * @param  it: EBI_NAND interrupt
  *         This parameter can be any combination of the following values:
  *            @arg EBI_IT_RISING_EDGE: Interrupt rising edge.
  *            @arg EBI_IT_LEVEL: Interrupt level.
  *            @arg EBI_IT_FALLING_EDGE: Interrupt falling edge.
  * @retval None
  */
void ald_ebi_nand_disable_it(EBI_NAND_TypeDef *dev, uint32_t bank, ebi_it_t it)
{
	assert_param(IS_EBI_NAND_DEVICE(dev));
	assert_param(IS_EBI_NAND_BANK(bank));

	if (bank == EBI_NAND_BANK2)
		CLEAR_BIT(dev->STAR2, it);
	else
		CLEAR_BIT(dev->STAR3, it);
}

/**
  * @brief  Enables dynamically EBI_NAND ECC feature.
  * @param  dev: Pointer to NAND device instance
  * @param  bank: NAND bank number
  * @retval None
  */
void ald_ebi_nand_ecc_enable(EBI_NAND_TypeDef *dev, uint32_t bank)
{
	assert_param(IS_EBI_NAND_DEVICE(dev));
	assert_param(IS_EBI_NAND_BANK(bank));

	/* Enable ECC feature */
	if (bank == EBI_NAND_BANK2)
		SET_BIT(dev->PCTRLR2, EBI_PCTRLRx_ECCEN_MSK);
	else
		SET_BIT(dev->PCTRLR3, EBI_PCTRLRx_ECCEN_MSK);
}

/**
  * @brief  Disables dynamically EBI_NAND ECC feature.
  * @param  dev: Pointer to NAND device instance
  * @param  bank: NAND bank number
  * @retval None
  */
void ald_ebi_nand_ecc_disable(EBI_NAND_TypeDef *dev, uint32_t bank)
{
	assert_param(IS_EBI_NAND_DEVICE(dev));
	assert_param(IS_EBI_NAND_BANK(bank));

	/* Disable ECC feature */
	if (bank == EBI_NAND_BANK2)
		CLEAR_BIT(dev->PCTRLR2, EBI_PCTRLRx_ECCEN_MSK);
	else
		CLEAR_BIT(dev->PCTRLR3, EBI_PCTRLRx_ECCEN_MSK);
}

/**
  * @brief  Disables dynamically EBI_NAND ECC feature.
  * @param  dev: Pointer to NAND device instance
  * @param  val: Pointer to ECC value
  * @param  bank: NAND bank number
  * @param  timeout: Timeout wait value  
  * @retval ALD status
  */
ald_status_t ald_ebi_nand_get_ecc(EBI_NAND_TypeDef *dev, uint32_t *val, uint32_t bank, uint32_t timeout)
{
	uint32_t tick;

	assert_param(IS_EBI_NAND_DEVICE(dev));
	assert_param(IS_EBI_NAND_BANK(bank));

	tick = ald_get_tick();

	/* Wait until FIFO is empty */
	while (ald_ebi_nand_get_flag(dev, bank, EBI_FLAG_FEMPT) == RESET) {
		if (timeout != ALD_MAX_DELAY) {
			if ((timeout == 0U) || ((ald_get_tick() - tick) > timeout))
				return TIMEOUT;
		}
	}

	if (bank == EBI_NAND_BANK2)
		*val = (uint32_t)dev->ECCRESULT2;
	else
		*val = (uint32_t)dev->ECCRESULT3;

	return OK;
}

/**
  * @brief  Get flag status of the NAND device.
  * @param  dev: EBI_NAND Instance
  * @param  bank  : EBI_NAND Bank
  * @param  flag  : EBI_NAND flag
  *         This parameter can be any combination of the following values:
  *            @arg EBI_FLAG_RISING_EDGE: Interrupt rising edge flag.
  *            @arg EBI_FLAG_LEVEL: Interrupt level edge flag.
  *            @arg EBI_FLAG_FALLING_EDGE: Interrupt falling edge flag.
  *            @arg EBI_FLAG_FEMPT: FIFO empty flag.
  * @retval Status:
  *           - 0: RESET
  *           - 1: SET
  */
flag_status_t ald_ebi_nand_get_flag(EBI_NAND_TypeDef *dev, uint32_t bank, ebi_flag_t flag)
{
	assert_param(IS_EBI_NAND_DEVICE(dev));
	assert_param(IS_EBI_NAND_BANK(bank));

	if (bank == EBI_NAND_BANK2) {
		if (dev->STAR2 & flag)
			return SET;
	} else {
		if (dev->STAR3 & flag)
			return SET;
	}

	return RESET;
}

/**
  * @brief  Clear flag status of the NAND device.
  * @param  dev: EBI_NAND Instance
  * @param  bank: EBI_NAND Bank
  * @param  flag: EBI_NAND flag
  *         This parameter can be any combination of the following values:
  *            @arg EBI_FLAG_RISING_EDGE: Interrupt rising edge flag.
  *            @arg EBI_FLAG_LEVEL: Interrupt level edge flag.
  *            @arg EBI_FLAG_FALLING_EDGE: Interrupt falling edge flag.
  *            @arg EBI_FLAG_FEMPT: FIFO empty flag.
  * @retval None
  */
void ald_ebi_nand_clear_flag(EBI_NAND_TypeDef *dev, uint32_t bank, ebi_flag_t flag)
{
	assert_param(IS_EBI_NAND_DEVICE(dev));
	assert_param(IS_EBI_NAND_BANK(bank));

	/* Enable ECC feature */
	if (bank == EBI_NAND_BANK2)
		CLEAR_BIT(dev->STAR2, flag);
	else
		CLEAR_BIT(dev->STAR3, flag);
}
/**
  * @}
  */

/** @defgroup EBI_Public_Functions_Group5 LCD initialize functions
  * @brief LCD initialize functions
  * @{
  */ 
/**
  * @brief  Initializes the EBI_LCD device according to the specified
  *         control parameters in the nor_lcd_handle_t
  * @param  hlcd: Pointer to LCD device instance
  * @retval None
  */
void ald_ebi_lcd_init(ebi_lcd_handle_t *hlcd)
{
	assert_param(IS_EBI_LCD_DEVICE(hlcd->inst));
	assert_param(IS_EBI_BANK_NUMBER(hlcd->init.bank));
	assert_param(IS_EBI_HORIZONTAL_SYNCH(hlcd->init.h_polarity));
	assert_param(IS_EBI_VERTICAL_SYNCH(hlcd->init.v_polarity));
	assert_param(IS_EBI_DATA_ENABLE(hlcd->init.data_polarity));
	assert_param(IS_EBI_LCD_ENABLE(hlcd->init.enable));
	assert_param(IS_EBI_DATA_CLOCK(hlcd->init.clk_polarity));
	assert_param(IS_EBI_LCD_DATASETUP_TIME(hlcd->init.setup));
	assert_param(IS_EBI_HYSNC_PULSE_WIDTH(hlcd->init.h_width));
	assert_param(IS_EBI_VSYNC_PULSE_WIDTH(hlcd->init.v_width));
	assert_param(IS_EBI_FRAME_LINE_NUMBER(hlcd->init.nr_line));
	assert_param(IS_EBI_FRAME_PIXEL_NUMBER(hlcd->init.nr_pixel));

	MODIFY_REG(hlcd->inst->LCDCRCFGS[(hlcd->init.bank - 1)*4], LCDCTRL_CLEAR_MASK,
				((uint32_t)hlcd->init.h_polarity                  |
				(uint32_t)hlcd->init.v_polarity                   |
				hlcd->init.data_polarity                          |
				hlcd->init.enable                                 |
				hlcd->init.clk_polarity                           |
				hlcd->init.setup   << EBI_LCDCTRLx_DATASETUP_POSS |
				hlcd->init.h_width << EBI_LCDCTRLx_VSYNCWID_POSS  |
				hlcd->init.v_width << EBI_LCDCTRLx_HSYNCWID_POSS));

	WRITE_REG(hlcd->inst->LCDCRCFGS[(hlcd->init.bank - 1)*4 + 1],
						 (hlcd->init.nr_line  << EBI_LCDSTx_LINECNT_POSS |
						  hlcd->init.nr_pixel << EBI_LCDSTx_PXLCNT_POSS));
}

/**
  * @brief  Reset the EBI_LCD 
  * @param  hlcd: Pointer to LCD device instance
  * @retval None
  */
void ald_ebi_lcd_reset(ebi_lcd_handle_t *hlcd)
{
	assert_param(IS_EBI_LCD_RESET(hlcd->init.reset));
	assert_param(IS_EBI_BANK_NUMBER(hlcd->init.bank));

	SET_BIT(hlcd->inst->LCDCRCFGS[(hlcd->init.bank - 1)*4], hlcd->init.reset);
}

/**
  * @}
  */
/**
  * @}
  */												    
#endif
/**
 * @}
 */
/**
 * @}
 */
