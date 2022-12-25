/**
  ******************************************************************************
  * @file    bl808_ef_ctrl.h
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
#ifndef __BL808_EF_CFG_H__
#define __BL808_EF_CFG_H__

#include "ef_ctrl_reg.h"
#include "bl808_common.h"

/** @addtogroup  BL808_Peripheral_Driver
 *  @{
 */

/** @addtogroup  EF_CTRL
 *  @{
 */

/** @defgroup  EF_CTRL_Public_Types
 *  @{
 */

/**
 *  @brief Efuse analog device info type definition
 */
typedef struct
{
    uint8_t chipInfo;      /*!< Efuse chip revision */
    uint8_t memoryInfo;    /*!< Efuse memory info 0:no memory, 8:1MB flash */
    uint8_t psramInfo;     /*!< Efuse psram info 0:no psram, 1:BW 4MB, 2:UHS 64MB */
    uint8_t deviceInfo;    /*!< Efuse device information */
} Efuse_Chip_Info_Type;

/**
 *  @brief Efuse analog ldo15rf vout sel aon type definition
 */
typedef struct
{
    uint32_t trimLDO15RFVoutAon         :  3;  /*!< Efuse analog trim:ldo15rf_vout_sel_aon */
    uint32_t trimLDO15RFVoutAonParity   :  1;  /*!< Efuse analog trim:ldo15rf_vout_sel_aon_parity */
    uint32_t trimLDO15RFVoutAonEn       :  1;  /*!< Efuse analog trim:ldo15rf_vout_sel_aon_en */
    uint32_t reserved                   : 27;  /*!< Efuse analog trim:reserved */
} Efuse_Ana_LDO15RF_Vout_Sel_Type;

/**
 *  @brief Efuse analog rcal iptat code type definition
 */
typedef struct
{
    uint32_t trimRcalIptatCode          :  5;  /*!< Efuse analog trim:rcal_iptat_code */
    uint32_t trimRcalIptatCodeParity    :  1;  /*!< Efuse analog trim:rcal_iptat_code_parity */
    uint32_t trimRcalIptatCodeEn        :  1;  /*!< Efuse analog trim:rcal_iptat_code_en */
    uint32_t reserved                   : 25;  /*!< Efuse analog trim:reserved */
} Efuse_Ana_Rcal_Iptat_Code_Type;

/**
 *  @brief Efuse analog rcal icx code type definition
 */
typedef struct
{
    uint32_t trimRcalIcxCode            :  6;  /*!< Efuse analog trim:rcal_icx_code */
    uint32_t trimRcalIcxCodeParity      :  1;  /*!< Efuse analog trim:rcal_icx_code_parity */
    uint32_t trimRcalIcxCodeEn          :  1;  /*!< Efuse analog trim:rcal_icx_code_en */
    uint32_t reserved                   : 24;  /*!< Efuse analog trim:reserved */
} Efuse_Ana_Rcal_Icx_Code_Type;

/**
 *  @brief Efuse analog LDO28CIS vout trim type definition
 */
typedef struct
{
    uint32_t trimLDO28CISVout           :  4;  /*!< Efuse analog trim:ldo28cis_vout_trim */
    uint32_t trimLDO28CISVoutParity     :  1;  /*!< Efuse analog trim:ldo28cis_vout_trim_parity */
    uint32_t trimLDO28CISVoutEn         :  1;  /*!< Efuse analog trim:ldo28cis_vout_trim_en */
    uint32_t reserved                   : 26;  /*!< Efuse analog trim:reserved */
} Efuse_Ana_LDO28CIS_Vout_Trim_Type;

/**
 *  @brief Efuse analog LDO15CIS vout trim type definition
 */
typedef struct
{
    uint32_t trimLDO15CISVout           :  4;  /*!< Efuse analog trim:ldo15cis_vout_trim */
    uint32_t trimLDO15CISVoutParity     :  1;  /*!< Efuse analog trim:ldo15cis_vout_trim_parity */
    uint32_t trimLDO15CISVoutEn         :  1;  /*!< Efuse analog trim:ldo15cis_vout_trim_en */
    uint32_t reserved                   : 26;  /*!< Efuse analog trim:reserved */
} Efuse_Ana_LDO15CIS_Vout_Trim_Type;

/**
 *  @brief Efuse analog LDO12UHS vout trim type definition
 */
typedef struct
{
    uint32_t trimLDO12UHSVout           :  4;  /*!< Efuse analog trim:ldo12uhs_vout_trim */
    uint32_t trimLDO12UHSVoutParity     :  1;  /*!< Efuse analog trim:ldo12uhs_vout_trim_parity */
    uint32_t trimLDO12UHSVoutEn         :  1;  /*!< Efuse analog trim:ldo12uhs_vout_trim_en */
    uint32_t reserved                   : 26;  /*!< Efuse analog trim:reserved */
} Efuse_Ana_LDO12UHS_Vout_Trim_Type;

/**
 *  @brief Efuse analog xtal capcode 1 inout type definition
 */
typedef struct
{
    uint32_t trimXtalCapcode1           :  6;  /*!< Efuse analog trim:ctal_capcode_1_inout */
    uint32_t trimXtalCapcode1Parity     :  1;  /*!< Efuse analog trim:ctal_capcode_1_inout_parity */
    uint32_t trimXtalCapcode1En         :  1;  /*!< Efuse analog trim:ctal_capcode_1_inout_en */
    uint32_t reserved                   : 24;  /*!< Efuse analog trim:reserved */
} Efuse_Ana_Xtal_Capcode_1_Type;

/**
 *  @brief Efuse analog xtal capcode 2 inout type definition
 */
typedef struct
{
    uint32_t trimXtalCapcode2           :  6;  /*!< Efuse analog trim:ctal_capcode_2_inout */
    uint32_t trimXtalCapcode2Parity     :  1;  /*!< Efuse analog trim:ctal_capcode_2_inout_parity */
    uint32_t trimXtalCapcode2En         :  1;  /*!< Efuse analog trim:ctal_capcode_2_inout_en */
    uint32_t reserved                   : 24;  /*!< Efuse analog trim:reserved */
} Efuse_Ana_Xtal_Capcode_2_Type;

/**
 *  @brief Efuse analog xtal capcode 3 inout type definition
 */
typedef struct
{
    uint32_t trimXtalCapcode3           :  6;  /*!< Efuse analog trim:ctal_capcode_3_inout */
    uint32_t trimXtalCapcode3Parity     :  1;  /*!< Efuse analog trim:ctal_capcode_3_inout_parity */
    uint32_t trimXtalCapcode3En         :  1;  /*!< Efuse analog trim:ctal_capcode_3_inout_en */
    uint32_t reserved                   : 24;  /*!< Efuse analog trim:reserved */
} Efuse_Ana_Xtal_Capcode_3_Type;

/**
 *  @brief Efuse analog gauge vpack offset type definition
 */
typedef struct
{
    uint32_t trimGaugeVpackOffset       : 16;  /*!< Efuse analog trim:gauge_vpack_offset */
    uint32_t trimGaugeVpackOffsetParity :  1;  /*!< Efuse analog trim:gauge_vpack_offset_parity */
    uint32_t trimGaugeVpackOffsetEn     :  1;  /*!< Efuse analog trim:gauge_vpack_offset_en */
    uint32_t reserved                   : 14;  /*!< Efuse analog trim:reserved */
} Efuse_Ana_Gauge_Vpack_Offset_Type;

/**
 *  @brief Efuse analog gauge vtemp offset type definition
 */
typedef struct
{
    uint32_t trimGaugeVtempOffset       : 16;  /*!< Efuse analog trim:gauge_vtemp_offset */
    uint32_t trimGaugeVtempOffsetParity :  1;  /*!< Efuse analog trim:gauge_vtemp_offset_parity */
    uint32_t trimGaugeVtempOffsetEn     :  1;  /*!< Efuse analog trim:gauge_vtemp_offset_en */
    uint32_t reserved                   : 14;  /*!< Efuse analog trim:reserved */
} Efuse_Ana_Gauge_Vtemp_Offset_Type;

/**
 *  @brief Efuse psram trim type definition
 */
typedef struct
{
    uint32_t psramTrim                  : 11;  /*!< Efuse analog trim:psram trim date */
    uint32_t psramTrimParity            :  1;  /*!< Efuse analog trim:psram trim_parity */
    uint32_t psramTrimEn                :  1;  /*!< Efuse analog trim:psram trim_en */
    uint32_t reserved                   : 19;  /*!< Efuse analog trim:reserved */
} Efuse_Psram_Trim_Type;

/*@} end of group EF_CTRL_Public_Types */

/** @defgroup  EF_CTRL_Public_Constants
 *  @{
 */

/*@} end of group EF_CTRL_Public_Constants */

/** @defgroup  EF_CTRL_Public_Macros
 *  @{
 */

/*@} end of group EF_CTRL_Public_Macros */

/** @defgroup  EF_CTRL_Public_Functions
 *  @{
 */
void EF_Ctrl_Get_Chip_Info(Efuse_Chip_Info_Type *chipInfo);
void EF_Ctrl_Read_LDO15RF_Vout_Sel(Efuse_Ana_LDO15RF_Vout_Sel_Type *trim);
void EF_Ctrl_Read_Rcal_Iptat_Code(Efuse_Ana_Rcal_Iptat_Code_Type *trim);
void EF_Ctrl_Read_Rcal_Icx_Code(Efuse_Ana_Rcal_Icx_Code_Type *trim);
void EF_Ctrl_Read_LDO28CIS_Vout_Trim(Efuse_Ana_LDO28CIS_Vout_Trim_Type *trim);
void EF_Ctrl_Read_LDO15CIS_Vout_Trim(Efuse_Ana_LDO15CIS_Vout_Trim_Type *trim);
void EF_Ctrl_Read_LDO12UHS_Vout_Trim(Efuse_Ana_LDO12UHS_Vout_Trim_Type *trim);
void EF_Ctrl_Read_Xtal_Capcode1_Inout(Efuse_Ana_Xtal_Capcode_1_Type *trim);
void EF_Ctrl_Read_Xtal_Capcode2_Inout(Efuse_Ana_Xtal_Capcode_2_Type *trim);
void EF_Ctrl_Read_Xtal_Capcode3_Inout(Efuse_Ana_Xtal_Capcode_3_Type *trim);
void EF_Ctrl_Read_Gauge_Vpack_Offset(Efuse_Ana_Gauge_Vpack_Offset_Type *trim);
void EF_Ctrl_Read_Gauge_Vtemp_Offset(Efuse_Ana_Gauge_Vtemp_Offset_Type *trim);
void EF_Ctrl_Read_Psram_Trim(Efuse_Psram_Trim_Type *trim);
void EF_Ctrl_Write_Psram_Trim(Efuse_Psram_Trim_Type *trim, uint8_t program);
uint8_t EF_Ctrl_Is_MAC_Address_Slot_Empty(uint8_t slot, uint8_t reload);
BL_Err_Type EF_Ctrl_Write_MAC_Address_Opt(uint8_t slot, uint8_t mac[6], uint8_t program);
BL_Err_Type EF_Ctrl_Read_MAC_Address_Opt(uint8_t slot, uint8_t mac[6], uint8_t reload);

/*@} end of group EF_CTRL_Public_Functions */

/*@} end of group EF_CTRL */

/*@} end of group BL808_Peripheral_Driver */

#endif /* __BL808_EF_CFG_H__ */
