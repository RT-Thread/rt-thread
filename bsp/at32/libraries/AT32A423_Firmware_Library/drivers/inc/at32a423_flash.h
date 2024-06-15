/**
  **************************************************************************
  * @file     at32a423_flash.h
  * @brief    at32a423 flash header file
  **************************************************************************
  *                       Copyright notice & Disclaimer
  *
  * The software Board Support Package (BSP) that is made available to
  * download from Artery official website is the copyrighted work of Artery.
  * Artery authorizes customers to use, copy, and distribute the BSP
  * software and its related documentation for the purpose of design and
  * development in conjunction with Artery microcontrollers. Use of the
  * software is governed by this copyright notice and the following disclaimer.
  *
  * THIS SOFTWARE IS PROVIDED ON "AS IS" BASIS WITHOUT WARRANTIES,
  * GUARANTEES OR REPRESENTATIONS OF ANY KIND. ARTERY EXPRESSLY DISCLAIMS,
  * TO THE FULLEST EXTENT PERMITTED BY LAW, ALL EXPRESS, IMPLIED OR
  * STATUTORY OR OTHER WARRANTIES, GUARANTEES OR REPRESENTATIONS,
  * INCLUDING BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY,
  * FITNESS FOR A PARTICULAR PURPOSE, OR NON-INFRINGEMENT.
  *
  **************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __AT32A423_FLASH_H
#define __AT32A423_FLASH_H

#ifdef __cplusplus
extern "C" {
#endif


/* Includes ------------------------------------------------------------------*/
#include "at32a423.h"

/** @addtogroup AT32A423_periph_driver
  * @{
  */

/** @addtogroup FLASH
  * @{
  */

/** @defgroup FLASH_exported_constants
  * @{
  */

/**
  * @brief flash unlock keys
  */
#define FLASH_UNLOCK_KEY1                ((uint32_t)0x45670123) /*!< flash operation unlock order key1 */
#define FLASH_UNLOCK_KEY2                ((uint32_t)0xCDEF89AB) /*!< flash operation unlock order key2 */
#define FAP_RELIEVE_KEY                  ((uint16_t)0x00A5)     /*!< flash fap relieve key val */
#define FAP_HIGH_LEVEL_KEY               ((uint16_t)0x00CC)     /*!< flash fap high level enable key val */
#define SLIB_UNLOCK_KEY                  ((uint32_t)0xA35F6D24) /*!< flash slib operation unlock order key */

/**
  * @}
  */

/** @defgroup FLASH_flags
  * @brief flash flag
  * @{
  */

#define FLASH_OBF_FLAG                   ((uint32_t)0x00000001)   /*!< flash operate busy flag */
#define FLASH_ODF_FLAG                   ((uint32_t)0x00000020)   /*!< flash operate done flag */
#define FLASH_PRGMERR_FLAG               ((uint32_t)0x00000004)   /*!< flash program error flag */
#define FLASH_EPPERR_FLAG                ((uint32_t)0x00000010)   /*!< flash erase/program protection error flag */
#define FLASH_USDERR_FLAG                ((uint32_t)0x40000001)   /*!< flash user system data error flag */

/**
  * @}
  */

/** @defgroup FLASH_interrupts
  * @brief flash interrupts
  * @{
  */

#define FLASH_ERR_INT                    ((uint32_t)0x00000001) /*!< flash error interrupt */
#define FLASH_ODF_INT                    ((uint32_t)0x00000002) /*!< flash operate done interrupt */

/**
  * @}
  */

/** @defgroup FLASH_slib_mask
  * @brief flash slib mask
  * @{
  */

#define FLASH_SLIB_START_SECTOR          ((uint32_t)0x000007FF) /*!< flash slib start sector */
#define FLASH_SLIB_INST_START_SECTOR     ((uint32_t)0x003FF800) /*!< flash slib i-bus area start sector */
#define FLASH_SLIB_END_SECTOR            ((uint32_t)0xFFC00000) /*!< flash slib end sector */

/**
  * @}
  */

/** @defgroup FLASH_user_system_data
  * @brief flash user system data
  * @{
  */

#define USD_WDT_ATO_DISABLE              ((uint16_t)0x0001) /*!< wdt auto start disabled  */
#define USD_WDT_ATO_ENABLE               ((uint16_t)0x0000) /*!< wdt auto start enabled */

#define USD_DEPSLP_NO_RST                ((uint16_t)0x0002) /*!< no reset generated when entering in deepsleep */
#define USD_DEPSLP_RST                   ((uint16_t)0x0000) /*!< reset generated when entering in deepsleep */

#define USD_STDBY_NO_RST                 ((uint16_t)0x0004) /*!< no reset generated when entering in standby */
#define USD_STDBY_RST                    ((uint16_t)0x0000) /*!< reset generated when entering in standby */

#define USD_BOOT1_LOW                    ((uint16_t)0x0010) /*!< when boot0 is high level, boot from bootmem */
#define USD_BOOT1_HIGH                   ((uint16_t)0x0000) /*!< when boot0 is high level, boot from sram */

#define USD_DEPSLP_WDT_CONTINUE          ((uint16_t)0x0020) /*!< wdt continue count when entering in deepsleep */
#define USD_DEPSLP_WDT_STOP              ((uint16_t)0x0000) /*!< wdt stop count when entering in deepsleep */

#define USD_STDBY_WDT_CONTINUE           ((uint16_t)0x0040) /*!< wdt continue count when entering in standby */
#define USD_STDBY_WDT_STOP               ((uint16_t)0x0000) /*!< wdt stop count when entering in standby */

/**
  * @}
  */

/** @defgroup FLASH_timeout_definition
  * @brief flash timeout definition
  * @{
  */

#define ERASE_TIMEOUT                    ((uint32_t)0x40000000) /*!< internal flash erase operation timeout */
#define PROGRAMMING_TIMEOUT              ((uint32_t)0x00100000) /*!< internal flash program operation timeout */
#define OPERATION_TIMEOUT                ((uint32_t)0x10000000) /*!< flash common operation timeout */

/**
  * @}
  */

/**
  * @brief  set the flash psr register
  * @param  wtcyc: the flash wait cycle.
  *         this parameter can be one of the following values:
  *         - FLASH_WAIT_CYCLE_0
  *         - FLASH_WAIT_CYCLE_1
  *         - FLASH_WAIT_CYCLE_2
  *         - FLASH_WAIT_CYCLE_3
  *         - FLASH_WAIT_CYCLE_4
  */
#define flash_psr_set(wtcyc)     (FLASH->psr = (uint32_t)(0x150 | wtcyc))

/** @defgroup FLASH_exported_types
  * @{
  */

/**
  * @brief  flash status type
  */
typedef enum
{
  FLASH_OPERATE_BUSY                     = 0x00, /*!< flash status is operate busy */
  FLASH_PROGRAM_ERROR                    = 0x01, /*!< flash status is program error */
  FLASH_EPP_ERROR                        = 0x02, /*!< flash status is epp error */
  FLASH_OPERATE_DONE                     = 0x03, /*!< flash status is operate done */
  FLASH_OPERATE_TIMEOUT                  = 0x04  /*!< flash status is operate timeout */
} flash_status_type;

/**
  * @brief  flash wait cycle type
  */
typedef enum
{
  FLASH_WAIT_CYCLE_0                     = 0x00, /*!< sysclk 1~32mhz */
  FLASH_WAIT_CYCLE_1                     = 0x01, /*!< sysclk 33~64mhz */
  FLASH_WAIT_CYCLE_2                     = 0x02, /*!< sysclk 65~96mhz */
  FLASH_WAIT_CYCLE_3                     = 0x03, /*!< sysclk 97~128mhz */
  FLASH_WAIT_CYCLE_4                     = 0x04  /*!< sysclk 129~150mhz */
} flash_wait_cycle_type;

/**
  * @brief type define flash register all
  */
typedef struct
{
  /**
    * @brief flash psr register, offset:0x00
    */
  union
  {
    __IO uint32_t psr;
    struct
    {
      __IO uint32_t wtcyc                : 3; /* [2:0] */
      __IO uint32_t reserved1            : 1; /* [3] */
      __IO uint32_t pft_en               : 1; /* [4] */
      __IO uint32_t pft_enf              : 1; /* [5] */
      __IO uint32_t pft_en2              : 1; /* [6] */
      __IO uint32_t pft_enf2             : 1; /* [7] */
      __IO uint32_t pft_lat_dis          : 1; /* [8] */
      __IO uint32_t reserved2            : 23;/* [31:9] */
    } psr_bit;
  };

  /**
    * @brief flash unlock register, offset:0x04
    */
  union
  {
    __IO uint32_t unlock;
    struct
    {
      __IO uint32_t ukval                : 32;/* [31:0] */
    } unlock_bit;
  };

  /**
    * @brief flash usd unlock register, offset:0x08
    */
  union
  {
    __IO uint32_t usd_unlock;
    struct
    {
      __IO uint32_t usd_ukval            : 32;/* [31:0] */
    } usd_unlock_bit;
  };

  /**
    * @brief flash sts register, offset:0x0C
    */
  union
  {
    __IO uint32_t sts;
    struct
    {
      __IO uint32_t obf                  : 1; /* [0] */
      __IO uint32_t reserved1            : 1; /* [1] */
      __IO uint32_t prgmerr              : 1; /* [2] */
      __IO uint32_t reserved2            : 1; /* [3] */
      __IO uint32_t epperr               : 1; /* [4] */
      __IO uint32_t odf                  : 1; /* [5] */
      __IO uint32_t reserved3            : 26;/* [31:6] */
    } sts_bit;
  };

  /**
    * @brief flash ctrl register, offset:0x10
    */
  union
  {
    __IO uint32_t ctrl;
    struct
    {
      __IO uint32_t fprgm                : 1; /* [0] */
      __IO uint32_t secers               : 1; /* [1] */
      __IO uint32_t bankers              : 1; /* [2] */
      __IO uint32_t reserved1            : 1; /* [3] */
      __IO uint32_t usdprgm              : 1; /* [4] */
      __IO uint32_t usders               : 1; /* [5] */
      __IO uint32_t erstr                : 1; /* [6] */
      __IO uint32_t oplk                 : 1; /* [7] */
      __IO uint32_t reserved2            : 1; /* [8] */
      __IO uint32_t usdulks              : 1; /* [9] */
      __IO uint32_t errie                : 1; /* [10] */
      __IO uint32_t reserved3            : 1; /* [11] */
      __IO uint32_t odfie                : 1; /* [12] */
      __IO uint32_t reserved4            : 19;/* [31:13] */
    } ctrl_bit;
  };

  /**
    * @brief flash addr register, offset:0x14
    */
  union
  {
    __IO uint32_t addr;
    struct
    {
      __IO uint32_t fa                   : 32;/* [31:0] */
    } addr_bit;
  };

  /**
    * @brief flash reserved1 register, offset:0x18
    */
  __IO uint32_t reserved1;

  /**
    * @brief flash usd register, offset:0x1C
    */
  union
  {
    __IO uint32_t usd;
    struct
    {
      __IO uint32_t usderr               : 1; /* [0] */
      __IO uint32_t fap                  : 1; /* [1] */
      __IO uint32_t wdt_ato_en           : 1; /* [2] */
      __IO uint32_t depslp_rst           : 1; /* [3] */
      __IO uint32_t stdby_rst            : 1; /* [4] */
      __IO uint32_t reserved1            : 1; /* [5] */
      __IO uint32_t boot1                : 1; /* [6] */
      __IO uint32_t depslp_wdt           : 1; /* [7] */
      __IO uint32_t stdby_wdt            : 1; /* [8] */
      __IO uint32_t reserved2            : 1; /* [9] */
      __IO uint32_t user_d0              : 8; /* [17:10] */
      __IO uint32_t user_d1              : 8; /* [25:18] */
      __IO uint32_t fap_hl               : 1; /* [26] */
      __IO uint32_t reserved3            : 5; /* [31:27] */
    } usd_bit;
  };

  /**
    * @brief flash epps register, offset:0x20
    */
  union
  {
    __IO uint32_t epps;
    struct
    {
      __IO uint32_t epps                 : 32;/* [31:0] */
    } epps_bit;
  };

  /**
    * @brief flash reserved2 register, offset:0x70~0x24
    */
  __IO uint32_t reserved2[20];

  /**
    * @brief flash slib_sts0 register, offset:0x74
    */
  union
  {
    __IO uint32_t slib_sts0;
    struct
    {
      __IO uint32_t btm_ap_enf           : 1; /* [0] */
      __IO uint32_t reserved1            : 1; /* [1] */
      __IO uint32_t em_slib_enf          : 1; /* [2] */
      __IO uint32_t slib_enf             : 1; /* [3] */
      __IO uint32_t reserved2            : 12;/* [15:4] */
      __IO uint32_t em_slib_inst_ss      : 8; /* [23:16] */
      __IO uint32_t reserved3            : 8; /* [31:24] */
    } slib_sts0_bit;
  };

  /**
    * @brief flash slib_sts1 register, offset:0x78
    */
  union
  {
    __IO uint32_t slib_sts1;
    struct
    {
      __IO uint32_t slib_ss              : 11;/* [10:0] */
      __IO uint32_t slib_inst_ss         : 11;/* [21:11] */
      __IO uint32_t slib_es              : 10;/* [31:22] */
    } slib_sts1_bit;
  };

  /**
    * @brief flash slib_pwd_clr register, offset:0x7C
    */
  union
  {
    __IO uint32_t slib_pwd_clr;
    struct
    {
      __IO uint32_t slib_pclr_val        : 32;/* [31:0] */
    } slib_pwd_clr_bit;
  };

  /**
    * @brief flash slib_misc_sts register, offset:0x80
    */
  union
  {
    __IO uint32_t slib_misc_sts;
    struct
    {
      __IO uint32_t slib_pwd_err         : 1; /* [0] */
      __IO uint32_t slib_pwd_ok          : 1; /* [1] */
      __IO uint32_t slib_ulkf            : 1; /* [2] */
      __IO uint32_t reserved1            : 29;/* [31:3] */
    } slib_misc_sts_bit;
  };

  /**
    * @brief flash crc_addr register, offset:0x84
    */
  union
  {
    __IO uint32_t crc_addr;
    struct
    {
      __IO uint32_t crc_addr             : 32;/* [31:0] */
    } crc_addr_bit;
  };

  /**
    * @brief flash crc_ctrl register, offset:0x88
    */
  union
  {
    __IO uint32_t crc_ctrl;
    struct
    {
      __IO uint32_t crc_sn               : 16;/* [15:0] */
      __IO uint32_t crc_strt             : 1; /* [16] */
      __IO uint32_t reserved1            : 15;/* [31:17] */
    } crc_ctrl_bit;
  };

  /**
    * @brief flash crc_chkr register, offset:0x8C
    */
  union
  {
    __IO uint32_t crc_chkr;
    struct
    {
      __IO uint32_t crc_chkr             : 32;/* [31:0] */
    } crc_chkr_bit;
  };

  /**
    * @brief flash reserved3 register, offset:0x15C~0x90
    */
  __IO uint32_t reserved3[52];

  /**
    * @brief flash slib_set_pwd register, offset:0x160
    */
  union
  {
    __IO uint32_t slib_set_pwd;
    struct
    {
      __IO uint32_t slib_pset_val        : 32;/* [31:0] */
    } slib_set_pwd_bit;
  };

  /**
    * @brief flash slib_set_range register, offset:0x164
    */
  union
  {
    __IO uint32_t slib_set_range;
    struct
    {
      __IO uint32_t slib_ss_set          : 11;/* [10:0] */
      __IO uint32_t slib_iss_set         : 11;/* [21:11] */
      __IO uint32_t slib_es_set          : 10;/* [31:22] */
    } slib_set_range_bit;
  };

  /**
    * @brief flash em_slib_set register, offset:0x168
    */
  union
  {
    __IO uint32_t em_slib_set;
    struct
    {
      __IO uint32_t em_slib_set          : 16;/* [15:0] */
      __IO uint32_t em_slib_iss_set      : 8; /* [23:16] */
      __IO uint32_t reserved1            : 8; /* [31:24] */
    } em_slib_set_bit;
  };

  /**
    * @brief flash btm_mode_set register, offset:0x16C
    */
  union
  {
    __IO uint32_t btm_mode_set;
    struct
    {
      __IO uint32_t btm_mode_set         : 8; /* [7:0] */
      __IO uint32_t reserved1            : 24;/* [31:8] */
    } btm_mode_set_bit;
  };

  /**
    * @brief flash slib_unlock register, offset:0x170
    */
  union
  {
    __IO uint32_t slib_unlock;
    struct
    {
      __IO uint32_t slib_ukval           : 32;/* [31:0] */
    } slib_unlock_bit;
  };

} flash_type;

/**
  * @brief user system data
  */
typedef struct
{
  __IO uint16_t fap;
  __IO uint16_t ssb;
  __IO uint16_t data0;
  __IO uint16_t data1;
  __IO uint16_t epp0;
  __IO uint16_t epp1;
  __IO uint16_t epp2;
  __IO uint16_t epp3;
} usd_type;

/**
  * @}
  */

#define FLASH                            ((flash_type *) FLASH_REG_BASE)
#define USD                              ((usd_type *) USD_BASE)

/** @defgroup FLASH_exported_functions
  * @{
  */

flag_status flash_flag_get(uint32_t flash_flag);
void flash_flag_clear(uint32_t flash_flag);
flash_status_type flash_operation_status_get(void);
flash_status_type flash_operation_wait_for(uint32_t time_out);
void flash_unlock(void);
void flash_lock(void);
flash_status_type flash_sector_erase(uint32_t sector_address);
flash_status_type flash_internal_all_erase(void);
flash_status_type flash_user_system_data_erase(void);
flash_status_type flash_word_program(uint32_t address, uint32_t data);
flash_status_type flash_halfword_program(uint32_t address, uint16_t data);
flash_status_type flash_byte_program(uint32_t address, uint8_t data);
flash_status_type flash_user_system_data_program(uint32_t address, uint8_t data);
flash_status_type flash_epp_set(uint32_t *sector_bits);
void flash_epp_status_get(uint32_t *sector_bits);
flash_status_type flash_fap_enable(confirm_state new_state);
flag_status flash_fap_status_get(void);
flash_status_type flash_fap_high_level_enable(void);
flag_status flash_fap_high_level_status_get(void);
flash_status_type flash_ssb_set(uint8_t usd_ssb);
uint8_t flash_ssb_status_get(void);
void flash_interrupt_enable(uint32_t flash_int, confirm_state new_state);
flash_status_type flash_slib_enable(uint32_t pwd, uint16_t start_sector, uint16_t inst_start_sector, uint16_t end_sector);
error_status flash_slib_disable(uint32_t pwd);
flag_status flash_slib_state_get(void);
uint16_t flash_slib_start_sector_get(void);
uint16_t flash_slib_inststart_sector_get(void);
uint16_t flash_slib_end_sector_get(void);
uint32_t flash_crc_calibrate(uint32_t start_addr, uint32_t sector_cnt);
void flash_boot_memory_extension_mode_enable(void);
flash_status_type flash_extension_memory_slib_enable(uint32_t pwd, uint16_t inst_start_sector);
flag_status flash_extension_memory_slib_state_get(void);
uint16_t flash_em_slib_inststart_sector_get(void);

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

#endif
