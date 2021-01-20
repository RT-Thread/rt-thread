/**
  *********************************************************************************
  *
  * @file    ald_iap.h
  * @brief   Header file of IAP module driver.
  *
  * @version V1.0
  * @date    04 Dec 2017
  * @author  AE Team
  * @note
  *
  * Copyright (C) Shanghai Eastsoft Microelectronics Co. Ltd. All rights reserved.
  *
  ********************************************************************************
  */

#ifndef __ALD_IAP_H__
#define __ALD_IAP_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "utils.h"


/** @addtogroup ES32FXXX_ALD
  * @{
  */

/** @addtogroup IAP
  * @{
  */

/**
  * @defgroup IAP_Private_Macros IAP Private Macros
  * @{
  */
#define IAP_WSP_ADDR	0x10000000U
#define IAP_PE_ADDR	0x10000004U
#define IAP_WP_ADDR	0x10000008U
#define IAP_DWP_ADDR	0x1000000cU
/**
  * @}
  */

/** @defgroup IAP_Private_Types IAP Private Types
  * @{
  */
typedef uint32_t (*IAP_PE)(uint32_t addr);
typedef uint32_t (*IAP_WP)(uint32_t addr, uint32_t data);
typedef uint32_t (*IAP_DWP)(uint32_t addr, uint32_t data_l, uint32_t data_h);
typedef uint32_t (*IAP_WSP)(uint32_t addr, uint8_t *data, uint32_t len, uint32_t erase);
/**
  * @}
  */

/** @addtogroup IAP_Public_Functions
  * @{
  */
uint32_t ald_iap_erase_page(uint32_t addr);
uint32_t ald_iap_program_word(uint32_t addr, uint32_t data);
uint32_t ald_iap_program_dword(uint32_t addr, uint32_t data_l, uint32_t data_h);
uint32_t ald_iap_program_words(uint32_t addr, uint8_t *data, uint32_t len, uint32_t erase);
/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */
#ifdef __cplusplus
}
#endif

#endif /* __ALD_IAP_H__ */
