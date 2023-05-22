/**
  ******************************************************************************
  * @file    bl616_ef_ctrl.h
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
#ifndef __BL616_EF_CTRL_H__
#define __BL616_EF_CTRL_H__

#include "ef_ctrl_reg.h"
#include "bl616_common.h"

/** @addtogroup  BL616_Peripheral_Driver
 *  @{
 */

/** @addtogroup  EF_CTRL
 *  @{
 */

/** @defgroup  EF_CTRL_Public_Types
 *  @{
 */

/**
 *  @brief Efuse Ctrl key slot type definition
 */
typedef enum {
    EF_CTRL_KEY_SLOT0, /*!< key slot 0 */
    EF_CTRL_KEY_SLOT1, /*!< key slot 1 */
    EF_CTRL_KEY_SLOT2, /*!< key slot 2 */
    EF_CTRL_KEY_SLOT3, /*!< key slot 3 */
    EF_CTRL_KEY_SLOT4, /*!< key slot 4 */
    EF_CTRL_KEY_SLOT5, /*!< key slot 5 */
    EF_CTRL_KEY_MAX,   /*!<  */
} EF_Ctrl_Key_Type;

/**
 *  @brief Efuse Ctrl sign type definition
 */
typedef enum {
    EF_CTRL_SIGN_NONE, /*!< no sign */
    EF_CTRL_SIGN_RSA,  /*!< use RSA to sign */
    EF_CTRL_SIGN_ECC,  /*!< use ECC to sign */
} EF_Ctrl_Sign_Type;

/**
 *  @brief Efuse Ctrl flash AES type definition
 */
typedef enum {
    EF_CTRL_SF_AES_NONE, /*!< No AES */
    EF_CTRL_SF_AES_128,  /*!< AES 128 */
    EF_CTRL_SF_AES_192,  /*!< AES 192 */
    EF_CTRL_SF_AES_256,  /*!< AES 256 */
} EF_Ctrl_SF_AES_Type;

/**
 *  @brief Efuse Ctrl Dbg type definition
 */
typedef enum {
    EF_CTRL_DBG_OPEN = 0,  /*!< Open debug */
    EF_CTRL_DBG_PASSWORD,  /*!< Open debug with password */
    EF_CTRL_DBG_CLOSE = 4, /*!< Close debug */
} EF_Ctrl_Dbg_Mode_Type;

/**
 *  @brief Efuse Ctrl clock type definition
 */
typedef enum {
    EF_CTRL_EF_CLK,   /*!< Select efuse clock */
    EF_CTRL_SAHB_CLK, /*!< Select SAHB clock */
} EF_Ctrl_CLK_Type;

/**
 *  @brief Efuse Ctrl clock type definition
 */
typedef enum {
    EF_CTRL_PARA_DFT,    /*!< Select default cyc parameter */
    EF_CTRL_PARA_MANUAL, /*!< Select manual cyc parameter */
} EF_Ctrl_CYC_PARA_Type;

/**
 *  @brief Efuse Ctrl clock type definition
 */
typedef enum {
    EF_CTRL_OP_MODE_AUTO,   /*!< Select efuse program auto mode */
    EF_CTRL_OP_MODE_MANUAL, /*!< Select efuse program manual mode */
} EF_Ctrl_OP_MODE_Type;

/**
 *  @brief Efuse Ctrl secure configuration structure type definition
 */
typedef struct
{
    EF_Ctrl_Dbg_Mode_Type ef_dbg_mode; /*!< Efuse debug mode */
    uint8_t ef_dbg_jtag_0_dis;         /*!< Jtag debug disable config value */
    uint8_t ef_dbg_jtag_1_dis;         /*!< Jtag debug disable config value */
    uint8_t ef_sboot_en;               /*!< Secure boot enable config value */
} EF_Ctrl_Sec_Param_Type;

/**
 *  @brief Efuse analog DcdcDis type definition
 */
typedef struct
{
    uint32_t dcdcDisAonEn     : 1;  /*!< Efuse analog dcdc_dis_aon_en */
    uint32_t dcdcDisAonParity : 1;  /*!< Efuse analog dcdc_dis_aon_parity */
    uint32_t dcdcDisAon       : 1;  /*!< Efuse analog dcdc_dis_aon */
    uint32_t reserved         : 29; /*!< Efuse analog reserved */
} Efuse_Ana_DcdcDis_Type;

/**
 *  @brief Efuse analog DcdcVoutSel type definition
 */
typedef struct
{
    uint32_t dcdcVoutSelAonEn     : 1;  /*!< Efuse analog dcdc_vout_sel_aon_en */
    uint32_t dcdcVoutSelAonParity : 1;  /*!< Efuse analog dcdc_vout_sel_aon_parity */
    uint32_t dcdcVoutSelAon       : 5;  /*!< Efuse analog dcdc_vout_sel_aon[4:0] */
    uint32_t reserved             : 25; /*!< Efuse analog reserved */
} Efuse_Ana_DcdcVoutSel_Type;

/**
 *  @brief Efuse analog Ldo18ioVoutSel type definition
 */
typedef struct
{
    uint32_t ldo18ioVoutSelEn     : 1;  /*!< Efuse analog ldo18io_vout_sel_en */
    uint32_t ldo18ioVoutSelParity : 1;  /*!< Efuse analog ldo18io_vout_sel_parity */
    uint32_t ldo18ioVoutSelAon    : 4;  /*!< Efuse analog ldo18io_vout_sel_aon[3:0] */
    uint32_t reserved             : 26; /*!< Efuse analog reserved */
} Efuse_Ana_Ldo18ioVoutSel_Type;

/**
 *  @brief Efuse analog Ldo18ioBypass type definition
 */
typedef struct
{
    uint32_t ldo18ioBypassEn     : 1;  /*!< Efuse analog ldo18io_bypass_en */
    uint32_t ldo18ioBypassParity : 1;  /*!< Efuse analog ldo18io_bypass_parity */
    uint32_t ldo18ioBypassAon    : 1;  /*!< Efuse analog ldo18io_bypass_aon */
    uint32_t reserved            : 29; /*!< Efuse analog reserved */
} Efuse_Ana_Ldo18ioBypass_Type;

/**
 *  @brief Efuse analog Ldo33VoutTrim type definition
 */
typedef struct
{
    uint32_t ldo33VoutTrimAonEn     : 1;  /*!< Efuse analog ldo33_vout_trim_aon_en */
    uint32_t ldo33VoutTrimAonParity : 1;  /*!< Efuse analog ldo33_vout_trim_aon_parity */
    uint32_t ldo33VoutTrimAon       : 4;  /*!< Efuse analog ldo33_vout_trim_aon[3:0] */
    uint32_t reserved               : 26; /*!< Efuse analog reserved */
} Efuse_Ana_Ldo33VoutTrim_Type;

/**
 *  @brief Efuse analog Ldo18ioVoutTrim type definition
 */
typedef struct
{
    uint32_t ldo18ioVoutTrimEn     : 1;  /*!< Efuse analog ldo18io_vout_trim_en */
    uint32_t ldo18ioVoutTrimParity : 1;  /*!< Efuse analog ldo18io_vout_trim_parity */
    uint32_t ldo18ioVoutTrimAon    : 4;  /*!< Efuse analog ldo18io_vout_trim_aon[3:0] */
    uint32_t reserved              : 26; /*!< Efuse analog reserved */
} Efuse_Ana_Ldo18ioVoutTrim_Type;

/**
 *  @brief Efuse analog DcdcVoutTrim type definition
 */
typedef struct
{
    uint32_t dcdcVoutTrimAonEn     : 1;  /*!< Efuse analog dcdc_vout_trim_aon_en */
    uint32_t dcdcVoutTrimAonParity : 1;  /*!< Efuse analog dcdc_vout_trim_aon_parity */
    uint32_t dcdcVoutTrimAon       : 4;  /*!< Efuse analog dcdc_vout_trim_aon[3:0] */
    uint32_t reserved              : 26; /*!< Efuse analog reserved */
} Efuse_Ana_DcdcVoutTrim_Type;

/**
 *  @brief Efuse analog Ldo11socVoutTrim type definition
 */
typedef struct
{
    uint32_t ldo11socVoutTrimAonEn   : 1;  /*!< Efuse analog ldo11soc_vout_trim_aon_en */
    uint32_t ldo11socVoutTrimAonTrim : 1;  /*!< Efuse analog ldo11soc_vout_trim_aon_trim */
    uint32_t ldo11socVoutTrimAon     : 4;  /*!< Efuse analog ldo11soc_vout_trim_aon[3:0] */
    uint32_t reserved                : 26; /*!< Efuse analog reserved */
} Efuse_Ana_Ldo11socVoutTrim_Type;

/**
 *  @brief Efuse analog RC32M trim type definition
 */
typedef struct
{
    uint32_t rc32mCodeFrExt2En     : 1;  /*!< Efuse analog rc32m_code_fr_ext2_en */
    uint32_t rc32mCodeFrExt2Parity : 1;  /*!< Efuse analog rc32m_code_fr_ext2_parity */
    uint32_t rc32mCodeFrExt2       : 8;  /*!< Efuse analog rc32m_code_fr_ext2[7:0] */
    uint32_t reserved              : 22; /*!< Efuse analog reserved */
} Efuse_Ana_RC32M_Trim_Type;

/**
 *  @brief Efuse analog RC32K trim type definition
 */
typedef struct
{
    uint32_t rc32kCodeFrExtEn     : 1;  /*!< Efuse analog rc32k_code_fr_ext_en */
    uint32_t rc32kCodeFrExtParity : 1;  /*!< Efuse analog rc32k_code_fr_ext_parity */
    uint32_t rc32kCodeFrExt       : 10; /*!< Efuse analog rc32k_code_fr_ext[9:0] */
    uint32_t reserved             : 20; /*!< Efuse analog reserved */
} Efuse_Ana_RC32K_Trim_Type;

/**
 *  @brief Efuse analog Usb20RcalCode type definition
 */
typedef struct
{
    uint32_t usb20RcalCodeAonEn     : 1;  /*!< Efuse analog usb20_rcal_code_aon_en */
    uint32_t usb20RcalCodeAonParity : 1;  /*!< Efuse analog usb20_rcal_code_aon_parity */
    uint32_t usb20RcalCodeAon       : 6;  /*!< Efuse analog usb20_rcal_code_aon[5:0] */
    uint32_t reserved               : 24; /*!< Efuse analog reserved */
} Efuse_Ana_Usb20RcalCode_Type;

/**
 *  @brief Efuse analog TSEN trim type definition
 */
typedef struct
{
    uint32_t tsenRefcodeCorner        : 12; /*!< TSEN refcode */
    uint32_t tsenRefcodeCornerParity  : 1;  /*!< TSEN refcode parity */
    uint32_t tsenRefcodeCornerEn      : 1;  /*!< TSEN refcode enable */
    uint32_t tsenRefcodeCornerVersion : 1;  /*!< TSEN refcode version */
    uint32_t reserved                 : 17; /*!< TSEN analog trim:reserved */
} Efuse_TSEN_Refcode_Corner_Type;

/**
 *  @brief Efuse analog ADC Gain trim type definition
 */
typedef struct
{
    uint32_t adcGainCoeff       : 12; /*!< ADC gain coeff */
    uint32_t adcGainCoeffParity : 1;  /*!< ADC gain coeff parity */
    uint32_t adcGainCoeffEn     : 1;  /*!< ADC gain coeff enable */
    uint32_t reserved           : 18; /*!< ADC gain coeff:reserved */
} Efuse_ADC_Gain_Coeff_Type;

/**
 *  @brief Efuse analog device info type definition
 */
typedef struct
{
    uint32_t rsvd       : 22; /*!< Reserved */
    uint32_t deviceInfo : 2;  /*!< Efuse device information */
    uint32_t psramInfo  : 2;  /*!< Efuse psram info 0:no psram, 1:WB 4MB*/
    uint32_t memoryInfo : 3;  /*!< Efuse memory info 0:no memory, 8:1MB flash */
    uint32_t chipInfo   : 3;  /*!< Efuse chip revision */
} Efuse_Device_Info_Type;

/**
 *  @brief Efuse Capcode type definition
 */
typedef struct
{
    uint32_t capCode : 6;  /*!< Cap code value */
    uint32_t parity  : 1;  /*!< Parity of capcode */
    uint32_t en      : 1;  /*!< Enable status */
    uint32_t rsvd    : 24; /*!< Reserved */
} Efuse_Capcode_Info_Type;

/**
 *  @brief Efuse common trim config definition
 */
typedef struct
{
    char *name;           /*!< trim anme */
    uint16_t en_addr;     /*!< enable address */
    uint16_t parity_addr; /*!< parity address */
    uint16_t value_addr;  /*!< value address */
    uint16_t value_len;   /*!< value length */
} Efuse_Common_Trim_Cfg;

/**
 *  @brief Efuse common trim type definition
 */
typedef struct
{
    uint8_t en;     /*!< Enable status */
    uint8_t parity; /*!< Trim parity */
    uint8_t empty;  /*!< Trim empty */
    uint8_t len;    /*!< Trim value len in bit */
    uint32_t value; /*!< Trim value */
} Efuse_Common_Trim_Type;

/*@} end of group EF_CTRL_Public_Types */

/** @defgroup  EF_CTRL_Public_Constants
 *  @{
 */

/** @defgroup  EF_CTRL_KEY_TYPE
 *  @{
 */
#define IS_EF_CTRL_KEY_TYPE(type) (((type) == EF_CTRL_KEY_SLOT0) || \
                                   ((type) == EF_CTRL_KEY_SLOT1) || \
                                   ((type) == EF_CTRL_KEY_SLOT2) || \
                                   ((type) == EF_CTRL_KEY_SLOT3) || \
                                   ((type) == EF_CTRL_KEY_SLOT4) || \
                                   ((type) == EF_CTRL_KEY_SLOT5) || \
                                   ((type) == EF_CTRL_KEY_MAX))

/** @defgroup  EF_CTRL_SIGN_TYPE
 *  @{
 */
#define IS_EF_CTRL_SIGN_TYPE(type) (((type) == EF_CTRL_SIGN_NONE) || \
                                    ((type) == EF_CTRL_SIGN_RSA) ||  \
                                    ((type) == EF_CTRL_SIGN_ECC))

/** @defgroup  EF_CTRL_SF_AES_TYPE
 *  @{
 */
#define IS_EF_CTRL_SF_AES_TYPE(type) (((type) == EF_CTRL_SF_AES_NONE) || \
                                      ((type) == EF_CTRL_SF_AES_128) ||  \
                                      ((type) == EF_CTRL_SF_AES_192) ||  \
                                      ((type) == EF_CTRL_SF_AES_256))

/** @defgroup  EF_CTRL_DBG_MODE_TYPE
 *  @{
 */
#define IS_EF_CTRL_DBG_MODE_TYPE(type) (((type) == EF_CTRL_DBG_OPEN) ||     \
                                        ((type) == EF_CTRL_DBG_PASSWORD) || \
                                        ((type) == EF_CTRL_DBG_CLOSE))

/** @defgroup  EF_CTRL_CLK_TYPE
 *  @{
 */
#define IS_EF_CTRL_CLK_TYPE(type) (((type) == EF_CTRL_EF_CLK) || \
                                   ((type) == EF_CTRL_SAHB_CLK))

/** @defgroup  EF_CTRL_CYC_PARA_TYPE
 *  @{
 */
#define IS_EF_CTRL_CYC_PARA_TYPE(type) (((type) == EF_CTRL_PARA_DFT) || \
                                        ((type) == EF_CTRL_PARA_MANUAL))

/** @defgroup  EF_CTRL_OP_MODE_TYPE
 *  @{
 */
#define IS_EF_CTRL_OP_MODE_TYPE(type) (((type) == EF_CTRL_OP_MODE_AUTO) || \
                                       ((type) == EF_CTRL_OP_MODE_MANUAL))

/*@} end of group EF_CTRL_Public_Constants */

/** @defgroup  EF_CTRL_Public_Macros
 *  @{
 */
#define EF_CTRL_EFUSE_R0_SIZE (128 * 4)

/*@} end of group EF_CTRL_Public_Macros */

/** @defgroup  EF_CTRL_Public_Functions
 *  @{
 */
/*----------*/
BL_Err_Type EF_Ctrl_Get_Customer_PIDVID(uint16_t pid[1], uint16_t vid[1]);
/*----------*/
void EF_Ctrl_Load_Efuse_R0(void);
void EF_Ctrl_Program_Efuse_0(void);
BL_Sts_Type EF_Ctrl_Busy(void);
BL_Sts_Type EF_Ctrl_AutoLoad_Done(void);
void EF_Ctrl_Write_Dbg_Pwd(uint8_t slot, uint32_t passWdLow, uint32_t passWdHigh, uint8_t program);
void EF_Ctrl_Read_Dbg_Pwd(uint8_t slot, uint32_t *passWdLow, uint32_t *passWdHigh);
void EF_Ctrl_Readlock_Dbg_Pwd(uint8_t program);
void EF_Ctrl_Writelock_Dbg_Pwd(uint8_t program);
void EF_Ctrl_Write_Secure_Cfg(EF_Ctrl_Sec_Param_Type *cfg, uint8_t program);
void EF_Ctrl_Read_Secure_Cfg(EF_Ctrl_Sec_Param_Type *cfg);
void EF_Ctrl_Write_Secure_Boot(EF_Ctrl_Sign_Type sign[1], EF_Ctrl_SF_AES_Type aes[1], uint8_t program);
void EF_Ctrl_Read_Secure_Boot(EF_Ctrl_SF_AES_Type aes[2]);
BL_Fun_Type EF_Ctrl_Read_Bus_Remap(void);
void EF_Ctrl_Set_sf_key_re_sel(uint8_t ef_sf_key_re_sel);
/*----------*/
uint8_t EF_Ctrl_Get_Trim_Parity(uint32_t val, uint8_t len);
void EF_Ctrl_Read_DcdcDis_Trim(Efuse_Ana_DcdcDis_Type *trim);
void EF_Ctrl_Read_DcdcVoutSel_Trim(Efuse_Ana_DcdcVoutSel_Type *trim);
void EF_Ctrl_Read_Ldo18ioVoutSel_Trim(Efuse_Ana_Ldo18ioVoutSel_Type *trim);
void EF_Ctrl_Read_Ldo18ioBypass_Trim(Efuse_Ana_Ldo18ioBypass_Type *trim);
void EF_Ctrl_Read_Ldo33VoutTrim_Trim(Efuse_Ana_Ldo33VoutTrim_Type *trim);
void EF_Ctrl_Read_Ldo18ioVoutTrim_Trim(Efuse_Ana_Ldo18ioVoutTrim_Type *trim);
void EF_Ctrl_Read_DcdcVoutTrim_Trim(Efuse_Ana_DcdcVoutTrim_Type *trim);
void EF_Ctrl_Read_Ldo11socVoutTrim_Trim(Efuse_Ana_Ldo11socVoutTrim_Type *trim);
void EF_Ctrl_Read_RC32M_Trim(Efuse_Ana_RC32M_Trim_Type *trim);
void EF_Ctrl_Read_RC32K_Trim(Efuse_Ana_RC32K_Trim_Type *trim);
void EF_Ctrl_Read_Usb20RcalCode_Trim(Efuse_Ana_Usb20RcalCode_Type *trim);
/*----------*/
void EF_Ctrl_Read_TSEN_Trim(Efuse_TSEN_Refcode_Corner_Type *trim);
void EF_Ctrl_Read_ADC_Gain_Trim(Efuse_ADC_Gain_Coeff_Type *trim);
void EF_Ctrl_Write_Sw_Usage(uint32_t index, uint32_t usage, uint8_t program);
void EF_Ctrl_Read_Sw_Usage(uint32_t index, uint32_t *usage);
void EF_Ctrl_Writelock_Sw_Usage(uint32_t index, uint8_t program);
void EF_Ctrl_Write_MAC_Address(uint8_t mac[6], uint8_t program);
BL_Err_Type EF_Ctrl_Read_MAC_Address(uint8_t mac[6]);
BL_Err_Type EF_Ctrl_Read_MAC_Address_Raw(uint8_t mac[7]);
BL_Err_Type EF_Ctrl_Read_ZiggBee_MAC_Address(uint8_t mac[8]);
void EF_Ctrl_Writelock_MAC_Address(uint8_t program);
BL_Err_Type EF_Ctrl_Read_Chip_ID(uint8_t id[8]);
void EF_Ctrl_Write_AES_Key(uint8_t index, uint32_t *keyData, uint32_t len, uint8_t program);
void EF_Ctrl_Read_AES_Key(uint8_t index, uint32_t *keyData, uint32_t len);
void EF_Ctrl_Writelock_AES_Key(uint8_t index, uint8_t program);
void EF_Ctrl_Readlock_AES_Key(uint8_t index, uint8_t program);
void EF_Ctrl_Program_Direct(uint32_t offset, uint32_t *data, uint32_t len);
void EF_Ctrl_Read_Direct(uint32_t offset, uint32_t *data, uint32_t len);
void EF_Ctrl_Clear(uint32_t index, uint32_t len);
void EF_Ctrl_Crc_Enable(void);
BL_Sts_Type EF_Ctrl_Crc_Is_Busy(void);
void EF_Ctrl_Crc_Set_Golden(uint32_t goldenValue);
BL_Err_Type EF_Ctrl_Crc_Result(void);
void EF_Ctrl_Sw_AHB_Clk_0(void);
uint8_t EF_Ctrl_Is_All_Bits_Zero(uint32_t val, uint8_t start, uint8_t len);
uint8_t EF_Ctrl_Read_FlashDlyCoe(void);

uint32_t EF_Ctrl_Get_Common_Trim_List(Efuse_Common_Trim_Cfg **trim_list);
void EF_Ctrl_Read_Common_Trim(char *name, Efuse_Common_Trim_Type *trim, uint8_t reload);
void EF_Ctrl_Write_Common_Trim(char *name, uint32_t value, uint8_t program);

/*@} end of group EF_CTRL_Public_Functions */

/*@} end of group EF_CTRL */

/*@} end of group BL616_Peripheral_Driver */

#endif /* __BL616_EF_CTRL_H__ */
