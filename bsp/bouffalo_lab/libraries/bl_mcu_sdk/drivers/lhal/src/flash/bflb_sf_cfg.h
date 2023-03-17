/**
  ******************************************************************************
  * @file    bflb_sf_cfg.h
  * @version V1.0
  * @date
  * @brief   This file is the standard driver header file
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT(c) 2020 Bouffalo Lab</center></h2>
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of Bouffalo Lab nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */
#ifndef __BL628_SF_CFG_H__
#define __BL628_SF_CFG_H__

#include "bflb_gpio.h"
#include "bflb_sflash.h"

/** @addtogroup  BL628_Peripheral_Driver
 *  @{
 */

/** @addtogroup  SF_CFG
 *  @{
 */

/** @defgroup  SF_CFG_Public_Types
 *  @{
 */

/*@} end of group SF_CFG_Public_Types */

/** @defgroup  SF_CFG_Public_Constants
 *  @{
 */

/*@} end of group SF_CFG_Public_Constants */

/** @defgroup  SF_CFG_Public_Macros
 *  @{
 */
#define BFLB_GPIO_FUNC_SF             2
#if defined(BL628) || defined(BL616)
/* Flash option sf2 */
/* Flash CLK */
#define BFLB_EXTFLASH_CLK0_GPIO       GPIO_PIN_8
/* FLASH CS */
#define BFLB_EXTFLASH_CS0_GPIO        GPIO_PIN_4
/* FLASH DATA */
#define BFLB_EXTFLASH_DATA00_GPIO     GPIO_PIN_7
#define BFLB_EXTFLASH_DATA10_GPIO     GPIO_PIN_5
#define BFLB_EXTFLASH_DATA20_GPIO     GPIO_PIN_6
#define BFLB_EXTFLASH_DATA30_GPIO     GPIO_PIN_9
/* Flash option sf3 */
/* Flash CLK */
#define BFLB_EXTFLASH_CLK1_GPIO       GPIO_PIN_15
/* FLASH CS */
#define BFLB_EXTFLASH_CS1_GPIO        GPIO_PIN_20
/* FLASH DATA */
#define BFLB_EXTFLASH_DATA01_GPIO     GPIO_PIN_16
#define BFLB_EXTFLASH_DATA11_GPIO     GPIO_PIN_19
#define BFLB_EXTFLASH_DATA21_GPIO     GPIO_PIN_18
#define BFLB_EXTFLASH_DATA31_GPIO     GPIO_PIN_14
#elif defined(BL808) || defined(BL606P)
/* Flash option sf2 */
/* Flash CLK */
#define BFLB_EXTFLASH_CLK0_GPIO       GPIO_PIN_34
/* FLASH CS */
#define BFLB_EXTFLASH_CS0_GPIO        GPIO_PIN_35
/* FLASH DATA */
#define BFLB_EXTFLASH_DATA00_GPIO     GPIO_PIN_36
#define BFLB_EXTFLASH_DATA10_GPIO     GPIO_PIN_37
#define BFLB_EXTFLASH_DATA20_GPIO     GPIO_PIN_38
#define BFLB_EXTFLASH_DATA30_GPIO     GPIO_PIN_39
#elif defined(BL702L)
/* Flash option */
/* Flash CLK */
#define BFLB_EXTFLASH_CLK0_GPIO       GPIO_PIN_27
/* FLASH CS */
#define BFLB_EXTFLASH_CS0_GPIO        GPIO_PIN_26
/* FLASH DATA */
#define BFLB_EXTFLASH_DATA00_GPIO     GPIO_PIN_23
#define BFLB_EXTFLASH_DATA10_GPIO     GPIO_PIN_25
#define BFLB_EXTFLASH_DATA20_GPIO     GPIO_PIN_24
#define BFLB_EXTFLASH_DATA30_GPIO     GPIO_PIN_28
#elif defined(BL702)
/* Flash option 0 */
/* Flash CLK */
#define BFLB_EXTFLASH_CLK0_GPIO       GPIO_PIN_21
/* FLASH CS */
#define BFLB_EXTFLASH_CS0_GPIO        GPIO_PIN_19
/* FLASH DATA */
#define BFLB_EXTFLASH_DATA00_GPIO     GPIO_PIN_17
#define BFLB_EXTFLASH_DATA10_GPIO     GPIO_PIN_18
#define BFLB_EXTFLASH_DATA20_GPIO     GPIO_PIN_22
#define BFLB_EXTFLASH_DATA30_GPIO     GPIO_PIN_20
/* Flash option 1 */
/* Flash CLK */
#define BFLB_EXTFLASH_CLK1_GPIO       GPIO_PIN_27
/* FLASH CS */
#define BFLB_EXTFLASH_CS1_GPIO        GPIO_PIN_25
/* FLASH DATA */
#define BFLB_EXTFLASH_DATA01_GPIO     GPIO_PIN_28
#define BFLB_EXTFLASH_DATA11_GPIO     GPIO_PIN_24
#define BFLB_EXTFLASH_DATA21_GPIO     GPIO_PIN_23
#define BFLB_EXTFLASH_DATA31_GPIO     GPIO_PIN_26
/* Flash option 2 */
/* Flash CLK */
#define BFLB_EXTFLASH_CLK2_GPIO       GPIO_PIN_36
/* FLASH CS */
#define BFLB_EXTFLASH_CS2_GPIO        GPIO_PIN_35
/* FLASH DATA */
#define BFLB_EXTFLASH_DATA02_GPIO     GPIO_PIN_32
#define BFLB_EXTFLASH_DATA12_GPIO     GPIO_PIN_34
#define BFLB_EXTFLASH_DATA22_GPIO     GPIO_PIN_33
#define BFLB_EXTFLASH_DATA32_GPIO     GPIO_PIN_37
#define BFLB_FLASH_CFG_SF2_EXT_23_28  0
#define BFLB_FLASH_CFG_SF2_INT_512K   1
#define BFLB_FLASH_CFG_SF2_INT_1M     2
#define BFLB_FLASH_CFG_SF1_EXT_17_22  3
#define BFLB_SF2_SWAP_NONE            0
#define BFLB_SF2_SWAP_CS_IO2          1
#define BFLB_SF2_SWAP_IO0_IO3         2
#define BFLB_SF2_SWAP_BOTH            3
#elif defined(BL602)
/*Flash option 0*/
/*Flash CLK*/
#define BFLB_EXTFLASH_CLK0_GPIO       GPIO_PIN_22
/*FLASH CS*/
#define BFLB_EXTFLASH_CS0_GPIO        GPIO_PIN_21
/*FLASH DATA*/
#define BFLB_EXTFLASH_DATA00_GPIO     GPIO_PIN_20
#define BFLB_EXTFLASH_DATA10_GPIO     GPIO_PIN_19
#define BFLB_EXTFLASH_DATA20_GPIO     GPIO_PIN_18
#define BFLB_EXTFLASH_DATA30_GPIO     GPIO_PIN_17
/*Flash option 1*/
/*Flash CLK*/
#define BFLB_EXTFLASH_CLK1_GPIO       GPIO_PIN_22
/*FLASH CS*/
#define BFLB_EXTFLASH_CS1_GPIO        GPIO_PIN_21
/*FLASH DATA*/
#define BFLB_EXTFLASH_DATA01_GPIO     GPIO_PIN_20
#define BFLB_EXTFLASH_DATA11_GPIO     GPIO_PIN_0
#define BFLB_EXTFLASH_DATA21_GPIO     GPIO_PIN_1
#define BFLB_EXTFLASH_DATA31_GPIO     GPIO_PIN_2
#define BFLB_FLASH_CFG_DESWAP         1
#define BFLB_FLASH_CFG_EXT0_17_22     2
#define BFLB_FLASH_CFG_EXT1_0_2_20_22 3
#endif
#define BFLB_FLASH_ID_VALID_FLAG      0x80000000
#define BFLB_FLASH_ID_VALID_MASK      0x7FFFFFFF

/*@} end of group SF_CFG_Public_Macros */

/** @defgroup  SF_CFG_Public_Functions
 *  @{
 */
int bflb_sf_cfg_get_flash_cfg_need_lock(uint32_t flash_id, spi_flash_cfg_type *p_flash_cfg,
                                        uint8_t group, uint8_t bank);
int bflb_sf_cfg_get_flash_cfg_need_lock_ext(uint32_t flash_id, spi_flash_cfg_type *p_flash_cfg,
                                            uint8_t group, uint8_t bank);
#if defined(BL702L) || defined(BL702)
void bflb_sf_cfg_init_internal_flash_gpio(void);
#endif
#if defined(BL602)
void bflb_sf_cfg_restore_gpio17_fun(uint8_t fun);
#endif
int bflb_sf_cfg_init_flash_gpio(uint8_t flash_pin_cfg, uint8_t restore_default);
#ifdef BFLB_SF_CTRL_SBUS2_ENABLE
int bflb_sf_cfg_init_flash2_gpio(uint8_t swap);
#endif
int bflb_sf_cfg_init_ext_flash_gpio(uint8_t ext_flash_pin);
int bflb_sf_cfg_deinit_ext_flash_gpio(uint8_t ext_flash_pin);
uint32_t bflb_sf_cfg_flash_identify(uint8_t call_from_flash, uint8_t flash_pin_cfg, uint8_t restore_default,
                                    spi_flash_cfg_type *p_flash_cfg, uint8_t group, uint8_t bank);
uint32_t bflb_sf_cfg_flash_identify_ext(uint8_t callfromflash, uint8_t flash_pin_cfg, uint8_t restore_default,
                                        spi_flash_cfg_type *p_flash_cfg, uint8_t group, uint8_t bank);
#ifdef BFLB_SF_CTRL_SBUS2_ENABLE
int bflb_sf_cfg_flash_init(uint8_t sel, const struct sf_ctrl_cfg_type *p_sfctrl_cfg,
                               const struct sf_ctrl_bank2_cfg *p_bank2_cfg);
int bflb_sf_cfg_sbus2_flash_init(uint8_t sel, const struct sf_ctrl_bank2_cfg *p_bank2_cfg);
#else
int bflb_sf_cfg_flash_init(uint8_t sel, const struct sf_ctrl_cfg_type *p_sfctrl_cfg);
#endif

/*@} end of group SF_CFG_Public_Functions */

/*@} end of group SF_CFG */

/*@} end of group BL628_Peripheral_Driver */

#endif /* __BL628_SF_CFG_H__ */
