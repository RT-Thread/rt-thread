/**
  *********************************************************************************
  *
  * @file    ald_bkpc.c
  * @brief   BKPC module driver.
  *
  * @version V1.0
  * @date    15 Dec 2017
  * @author  AE Team
  * @note
  *
  * Copyright (C) Shanghai Eastsoft Microelectronics Co. Ltd. All rights reserved.
  *
  *********************************************************************************
  */

#include "ald_bkpc.h"
#include "ald_rtc.h"


/** @addtogroup ES32FXXX_ALD
  * @{
  */

/** @defgroup BKPC BKPC
  * @brief BKPC module driver
  * @{
  */
#ifdef ALD_BKPC

/** @defgroup BKPC_Public_Functions BKPC Public Functions
  * @{
  */

/** @addtogroup BKPC_Public_Functions_Group1 Peripheral Control functions
  * @brief Peripheral Control functions
  *
  * @verbatim
  ==============================================================================
              ##### Peripheral Control functions #####
  ==============================================================================
  [..]  This section provides functions allowing to:
    (+) ald_bkpc_ldo_config() API can configure LDO in backup field.
    (+) ald_bkpc_bor_config() API can configure BOR in backup field.

    @endverbatim
  * @{
  */

/**
  * @brief  Configure ldo in backup field
  * @param  output: Output voltage select.
  * @param  state: DISABLE/ENABLE.
  * @retval None
  */
void ald_bkpc_ldo_config(bkpc_ldo_output_t output, type_func_t state)
{
    assert_param(IS_BKPC_LDO_OUTPUT(output));
    assert_param(IS_FUNC_STATE(state));

    BKPC_UNLOCK();
    MODIFY_REG(BKPC->CR, BKPC_CR_MT_STDB_MSK, state << BKPC_CR_MT_STDB_POS);

    if (state)
        MODIFY_REG(BKPC->CR, BKPC_CR_LDO_VSEL_MSK, output << BKPC_CR_LDO_VSEL_POSS);

    BKPC_LOCK();
    return;
}

/**
  * @brief  Configure bor voltage in backup field
  * @param  vol: Voltage select.
  * @param  state: DISABLE/ENABLE.
  * @retval None
  */
void ald_bkpc_bor_config(bkpc_bor_vol_t vol, type_func_t state)
{
    assert_param(IS_BKPC_BOR_VOL(vol));
    assert_param(IS_FUNC_STATE(state));

    BKPC_UNLOCK();
    MODIFY_REG(BKPC->PCR, BKPC_PCR_BOREN_MSK, state << BKPC_PCR_BOREN_POS);

    if (state)
        MODIFY_REG(BKPC->PCR, BKPC_PCR_BORS_MSK, vol << BKPC_PCR_BORS_POSS);

    BKPC_LOCK();
    return;


}
/**
  * @}
  */

/** @addtogroup BKPC_Public_Functions_Group2 IO operation functions
  * @brief IO operation functions
  *
  * @verbatim
  ==============================================================================
              ##### IO operation functions #####
  ==============================================================================
  [..]  This section provides functions allowing to:
    (+) ald_bkpc_write_ram() API can write data in backup ram.
    (+) ald_bkpc_read_ram() API can read data from backup ram.

    @endverbatim
  * @{
  */

/**
  * @brief  Write data into backup ram.
  * @param  idx: Index of backup word.
  * @param  value: Value which will be written to backup ram.
  * @retval None
  */
void ald_bkpc_write_ram(uint8_t idx, uint32_t value)
{
    assert_param(IS_BKPC_RAM_IDX(idx));

    RTC_UNLOCK();
    WRITE_REG(RTC->BKPR[idx], value);
    RTC_LOCK();

    return;
}

/**
  * @brief  Read data from backup ram.
  * @param  idx: Index of backup word.
  * @retval The data.
  */
uint32_t ald_bkpc_read_ram(uint8_t idx)
{
    assert_param(IS_BKPC_RAM_IDX(idx));

    return READ_REG(RTC->BKPR[idx]);
}
/**
  * @}
  */

/**
  * @}
  */
#endif /* ALD_BKPC */
/**
  * @}
  */

/**
  * @}
  */
