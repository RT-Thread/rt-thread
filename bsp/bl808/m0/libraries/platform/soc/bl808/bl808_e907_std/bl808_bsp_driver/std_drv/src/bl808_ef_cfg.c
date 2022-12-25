/**
  ******************************************************************************
  * @file    bl808_ef_cfg.c
  * @version V1.0
  * @date
  * @brief   This file is the standard driver c file
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

#include "string.h"
#include "bl808_ef_ctrl.h"
#include "bl808_ef_cfg.h"
#include "ef_data_0_reg.h"
#include "ef_data_1_reg.h"

/** @addtogroup  BL808_Peripheral_Driver
 *  @{
 */

/** @addtogroup  SEC_EF_CTRL
 *  @{
 */

/** @defgroup  SEC_EF_CTRL_Private_Macros
 *  @{
 */
#define EF_CTRL_LOAD_BEFORE_READ_R0 EF_Ctrl_Load_Efuse_R0()
#define EF_CTRL_LOAD_BEFORE_READ_R1 EF_Ctrl_Load_Efuse_R1()

/*@} end of group SEC_EF_CTRL_Private_Macros */

/** @defgroup  SEC_EF_CTRL_Private_Types
 *  @{
 */

/*@} end of group SEC_EF_CTRL_Private_Types */

/** @defgroup  SEC_EF_CTRL_Private_Variables
 *  @{
 */

/*@} end of group SEC_EF_CTRL_Private_Variables */

/** @defgroup  SEC_EF_CTRL_Global_Variables
 *  @{
 */

/*@} end of group SEC_EF_CTRL_Global_Variables */

/** @defgroup  SEC_EF_CTRL_Private_Fun_Declaration
 *  @{
 */

/*@} end of group SEC_EF_CTRL_Private_Fun_Declaration */

/** @defgroup  SEC_EF_CTRL_Private_Functions
 *  @{
 */

/****************************************************************************/ /**
 * @brief  Efuse get zero bit count
 *
 * @param  val: Value to count
 *
 * @return Zero bit count
 *
*******************************************************************************/
static uint32_t EF_Cfg_Get_Byte_Zero_Cnt(uint8_t val)
{
    uint32_t cnt = 0;
    uint32_t i = 0;

    for (i = 0; i < 8; i++) {
        if ((val & (1 << i)) == 0) {
            cnt += 1;
        }
    }

    return cnt;
}

/****************************************************************************/ /**
 * @brief  Efuse get chip info
 *
 * @param  chipInfo: info pointer
 *
 * @return None
 *
*******************************************************************************/
void EF_Ctrl_Get_Chip_Info(Efuse_Chip_Info_Type *chipInfo)
{
    uint32_t tmpVal;

    /* Trigger read data from efuse */
    EF_CTRL_LOAD_BEFORE_READ_R0;

    tmpVal = BL_RD_REG(EF_DATA_BASE, EF_DATA_0_EF_WIFI_MAC_HIGH);
    chipInfo->chipInfo = (tmpVal>>29)&0x7;
    chipInfo->memoryInfo = (tmpVal>>27)&0x3;
    chipInfo->psramInfo = (tmpVal>>25)&0x3;
    chipInfo->deviceInfo = (tmpVal>>22)&0x7;

    tmpVal = BL_RD_REG(EF_DATA_BASE, EF_DATA_0_EF_CFG_0);
    chipInfo->psramInfo |= ((tmpVal>>20)&0x1) << 2;
}

/****************************************************************************/ /**
 * @brief  Efuse read xtal trim rc32m configuration
 *
 * @param  trim: Trim data pointer
 *
 * @return None
 *
*******************************************************************************/
void EF_Ctrl_Read_LDO15RF_Vout_Sel(Efuse_Ana_LDO15RF_Vout_Sel_Type *trim)
{
    uint32_t tmpVal;

    /* Trigger read data from efuse */
    EF_CTRL_LOAD_BEFORE_READ_R0;

    tmpVal = BL_RD_REG(EF_DATA_BASE, EF_DATA_0_EF_SW_USAGE_3);
    trim->trimLDO15RFVoutAon = (tmpVal >> 27) & 0x07;
    trim->trimLDO15RFVoutAonParity = (tmpVal >> 30) & 0x01;
    trim->trimLDO15RFVoutAonEn = (tmpVal >> 31) & 0x01;
}


/****************************************************************************/ /**
 * @brief  Efuse read rcal iptat code configuration
 *
 * @param  trim: Trim data pointer
 *
 * @return None
 *
*******************************************************************************/
void EF_Ctrl_Read_Rcal_Iptat_Code(Efuse_Ana_Rcal_Iptat_Code_Type *trim)
{
    uint32_t tmpVal;

    /* Trigger read data from efuse */
    EF_CTRL_LOAD_BEFORE_READ_R0;

    tmpVal = BL_RD_REG(EF_DATA_BASE, EF_DATA_0_EF_SW_USAGE_3);
    trim->trimRcalIptatCode = (tmpVal >> 22) & 0x1f;

    tmpVal = BL_RD_REG(EF_DATA_BASE, EF_DATA_0_EF_KEY_SLOT_11_W2);
    trim->trimRcalIptatCodeParity = (tmpVal >> 30) & 0x01;
    trim->trimRcalIptatCodeEn = (tmpVal >> 31) & 0x01;
}

/****************************************************************************/ /**
 * @brief  Efuse read rcal icx code configuration
 *
 * @param  trim: Trim data pointer
 *
 * @return None
 *
*******************************************************************************/
void EF_Ctrl_Read_Rcal_Icx_Code(Efuse_Ana_Rcal_Icx_Code_Type *trim)
{
    uint32_t tmpVal;

    /* Trigger read data from efuse */
    EF_CTRL_LOAD_BEFORE_READ_R0;

    tmpVal = BL_RD_REG(EF_DATA_BASE, EF_DATA_0_EF_KEY_SLOT_11_W2);
    trim->trimRcalIcxCode = (tmpVal >> 22) & 0x3f;
    trim->trimRcalIcxCodeParity = (tmpVal >> 28) & 0x01;
    trim->trimRcalIcxCodeEn = (tmpVal >> 29) & 0x01;
}

/****************************************************************************/ /**
 * @brief  Efuse read LDO28CIS vout trim configuration
 *
 * @param  trim: Trim data pointer
 *
 * @return None
 *
*******************************************************************************/
void EF_Ctrl_Read_LDO28CIS_Vout_Trim(Efuse_Ana_LDO28CIS_Vout_Trim_Type *trim)
{
    uint32_t tmpVal;

    /* Trigger read data from efuse */
    EF_CTRL_LOAD_BEFORE_READ_R0;

    tmpVal = BL_RD_REG(EF_DATA_BASE, EF_DATA_0_EF_KEY_SLOT_11_W3);
    trim->trimLDO28CISVout = (tmpVal >> 8) & 0xf;
    trim->trimLDO28CISVoutParity = (tmpVal >> 12) & 0x01;
    trim->trimLDO28CISVoutEn = (tmpVal >> 13) & 0x01;
}

/****************************************************************************/ /**
 * @brief  Efuse read LDO15CIS vout trim configuration
 *
 * @param  trim: Trim data pointer
 *
 * @return None
 *
*******************************************************************************/
void EF_Ctrl_Read_LDO15CIS_Vout_Trim(Efuse_Ana_LDO15CIS_Vout_Trim_Type *trim)
{
    uint32_t tmpVal;

    /* Trigger read data from efuse */
    EF_CTRL_LOAD_BEFORE_READ_R0;

    tmpVal = BL_RD_REG(EF_DATA_BASE, EF_DATA_0_EF_KEY_SLOT_11_W3);
    trim->trimLDO15CISVout = (tmpVal >> 8) & 0xf;
    trim->trimLDO15CISVoutParity = (tmpVal >> 12) & 0x01;
    trim->trimLDO15CISVoutEn = (tmpVal >> 13) & 0x01;
}

/****************************************************************************/ /**
 * @brief  Efuse read LDO12UHS vout trim configuration
 *
 * @param  trim: Trim data pointer
 *
 * @return None
 *
*******************************************************************************/
void EF_Ctrl_Read_LDO12UHS_Vout_Trim(Efuse_Ana_LDO12UHS_Vout_Trim_Type *trim)
{
    uint32_t tmpVal;

    /* Trigger read data from efuse */
    EF_CTRL_LOAD_BEFORE_READ_R1;

    tmpVal = BL_RD_REG(EF_DATA_BASE, EF_DATA_1_EF_KEY_SLOT_10_W3);
    trim->trimLDO12UHSVout = (tmpVal >> 20) & 0xf;
    trim->trimLDO12UHSVoutParity = (tmpVal >> 24) & 0x01;
    trim->trimLDO12UHSVoutEn = (tmpVal >> 25) & 0x01;
}

/****************************************************************************/ /**
 * @brief  Efuse read xtal capcode 1 inout configuration
 *
 * @param  trim: Trim data pointer
 *
 * @return None
 *
*******************************************************************************/
void EF_Ctrl_Read_Xtal_Capcode1_Inout(Efuse_Ana_Xtal_Capcode_1_Type *trim)
{
    uint32_t tmpVal;

    /* Trigger read data from efuse */
    EF_CTRL_LOAD_BEFORE_READ_R1;

    tmpVal = BL_RD_REG(EF_DATA_BASE, EF_DATA_1_EF_KEY_SLOT_10_W3);
    trim->trimXtalCapcode1 = (tmpVal >> 0) & 0x3f;
    trim->trimXtalCapcode1Parity = (tmpVal >> 6) & 0x01;
    trim->trimXtalCapcode1En = (tmpVal >> 7) & 0x01;
}

/****************************************************************************/ /**
 * @brief  Efuse read xtal capcode 2 inout configuration
 *
 * @param  trim: Trim data pointer
 *
 * @return None
 *
*******************************************************************************/
void EF_Ctrl_Read_Xtal_Capcode2_Inout(Efuse_Ana_Xtal_Capcode_2_Type *trim)
{
    uint32_t tmpVal;

    /* Trigger read data from efuse */
    EF_CTRL_LOAD_BEFORE_READ_R1;

    tmpVal = BL_RD_REG(EF_DATA_BASE, EF_DATA_1_EF_DAT_1_RSVD_1);
    trim->trimXtalCapcode2 = (tmpVal >> 26) & 0x3f;

    tmpVal = BL_RD_REG(EF_DATA_BASE, EF_DATA_1_EF_DAT_1_RSVD_0);
    trim->trimXtalCapcode2Parity = (tmpVal >> 30) & 0x01;
    trim->trimXtalCapcode2En = (tmpVal >> 31) & 0x01;
}

/****************************************************************************/ /**
 * @brief  Efuse read xtal capcode 3 inout configuration
 *
 * @param  trim: Trim data pointer
 *
 * @return None
 *
*******************************************************************************/
void EF_Ctrl_Read_Xtal_Capcode3_Inout(Efuse_Ana_Xtal_Capcode_3_Type *trim)
{
    uint32_t tmpVal;

    /* Trigger read data from efuse */
    EF_CTRL_LOAD_BEFORE_READ_R1;

    tmpVal = BL_RD_REG(EF_DATA_BASE, EF_DATA_1_EF_DAT_1_RSVD_1);
    trim->trimXtalCapcode3 = (tmpVal >> 20) & 0x3f;

    tmpVal = BL_RD_REG(EF_DATA_BASE, EF_DATA_1_EF_DAT_1_RSVD_0);
    trim->trimXtalCapcode3Parity = (tmpVal >> 28) & 0x01;
    trim->trimXtalCapcode3En = (tmpVal >> 29) & 0x01;
}

/****************************************************************************/ /**
 * @brief  Efuse read gauge vpack offset configuration
 *
 * @param  trim: Trim data pointer
 *
 * @return None
 *
*******************************************************************************/
void EF_Ctrl_Read_Gauge_Vpack_Offset(Efuse_Ana_Gauge_Vpack_Offset_Type *trim)
{
    uint32_t tmpVal;

    /* Trigger read data from efuse */
    EF_CTRL_LOAD_BEFORE_READ_R1;

    tmpVal = BL_RD_REG(EF_DATA_BASE, EF_DATA_1_EF_DAT_1_RSVD_1);
    trim->trimGaugeVpackOffset = (tmpVal >> 2) & 0xffff;
    trim->trimGaugeVpackOffsetParity = (tmpVal >> 18) & 0x01;
    trim->trimGaugeVpackOffsetEn = (tmpVal >> 19) & 0x01;
}

/****************************************************************************/ /**
 * @brief  Efuse read gauge vtemp offset configuration
 *
 * @param  trim: Trim data pointer
 *
 * @return None
 *
*******************************************************************************/
void EF_Ctrl_Read_Gauge_Vtemp_Offset(Efuse_Ana_Gauge_Vtemp_Offset_Type *trim)
{
    uint32_t tmpVal;

    /* Trigger read data from efuse */
    EF_CTRL_LOAD_BEFORE_READ_R1;

    tmpVal = BL_RD_REG(EF_DATA_BASE, EF_DATA_1_EF_DAT_1_RSVD_2);
    trim->trimGaugeVtempOffset = (tmpVal >> 16) & 0xffff;

    tmpVal = BL_RD_REG(EF_DATA_BASE, EF_DATA_1_EF_DAT_1_RSVD_1);
    trim->trimGaugeVtempOffsetParity = (tmpVal >> 0) & 0x01;
    trim->trimGaugeVtempOffsetEn = (tmpVal >> 1) & 0x01;
}

/****************************************************************************/ /**
 * @brief  Efuse read psram trim configuration
 *
 * @param  trim: Trim data pointer
 *
 * @return None
 *
*******************************************************************************/
void EF_Ctrl_Read_Psram_Trim(Efuse_Psram_Trim_Type *trim)
{
    uint32_t tmpVal;

    /* Trigger read data from efuse */
    EF_CTRL_LOAD_BEFORE_READ_R1;

    tmpVal = BL_RD_REG(EF_DATA_BASE, EF_DATA_1_EF_KEY_SLOT_10_W2);
    trim->psramTrim = (tmpVal >> 0) & 0x7ff;
    trim->psramTrimParity = (tmpVal >> 11) & 0x01;
    trim->psramTrimEn = (tmpVal >> 12) & 0x01;
}

/****************************************************************************/ /**
 * @brief  Efuse write psram trim configuration
 *
 * @param  trim: Trim data pointer
 * @param  program: program to efuse entity or not
 *
 * @return None
 *
*******************************************************************************/
void EF_Ctrl_Write_Psram_Trim(Efuse_Psram_Trim_Type *trim, uint8_t program)
{
    uint32_t tmpVal;

    /* Switch to AHB clock */
    EF_Ctrl_Sw_AHB_Clk_1();

    tmpVal = BL_RD_REG(EF_DATA_BASE, EF_DATA_1_EF_KEY_SLOT_10_W2);
    tmpVal |= (trim->psramTrim<<0);
    tmpVal |= (trim->psramTrimParity<<11);
    tmpVal |= (trim->psramTrimEn<<12);
    BL_WR_REG(EF_DATA_BASE, EF_DATA_1_EF_KEY_SLOT_10_W2, tmpVal);

    if (program) {
        EF_Ctrl_Program_Efuse_1();
    }
}

/****************************************************************************/ /**
 * @brief  Whether MAC address slot is empty
 *
 * @param  slot: MAC address slot
 * @param  reload: whether  reload to check
 *
 * @return 0 for all slots full,1 for others
 *
*******************************************************************************/
uint8_t EF_Ctrl_Is_MAC_Address_Slot_Empty(uint8_t slot, uint8_t reload)
{
    uint32_t tmp1 = 0xffffffff, tmp2 = 0xffffffff;
    uint32_t part1Empty = 0, part2Empty = 0;

    if (slot == 0) {
        /* Switch to AHB clock */
        EF_Ctrl_Sw_AHB_Clk_0();

        if (reload) {
            EF_CTRL_LOAD_BEFORE_READ_R0;
        }

        tmp1 = BL_RD_REG(EF_DATA_BASE, EF_DATA_0_EF_WIFI_MAC_LOW);
        tmp2 = BL_RD_REG(EF_DATA_BASE, EF_DATA_0_EF_WIFI_MAC_HIGH);
    } else if (slot == 1) {
        /* Switch to AHB clock */
        EF_Ctrl_Sw_AHB_Clk_0();

        if (reload) {
            EF_CTRL_LOAD_BEFORE_READ_R0;
        }

        tmp1 = BL_RD_REG(EF_DATA_BASE, EF_DATA_0_EF_SW_USAGE_2);
        tmp2 = BL_RD_REG(EF_DATA_BASE, EF_DATA_0_EF_SW_USAGE_3);
    } else if (slot == 2) {
        /* Switch to AHB clock */
        EF_Ctrl_Sw_AHB_Clk_0();

        if (reload) {
            EF_CTRL_LOAD_BEFORE_READ_R0;
        }

        tmp1 = BL_RD_REG(EF_DATA_BASE, EF_DATA_0_EF_KEY_SLOT_11_W1);
        tmp2 = BL_RD_REG(EF_DATA_BASE, EF_DATA_0_EF_KEY_SLOT_11_W2);
    }

    part1Empty = (EF_Ctrl_Is_All_Bits_Zero(tmp1, 0, 32));
    part2Empty = (EF_Ctrl_Is_All_Bits_Zero(tmp2, 0, 22));

    return (part1Empty && part2Empty);
}

/****************************************************************************/ /**
 * @brief  Efuse write optional MAC address
 *
 * @param  slot: MAC address slot
 * @param  mac[6]: MAC address buffer
 * @param  program: Whether program
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type EF_Ctrl_Write_MAC_Address_Opt(uint8_t slot, uint8_t mac[6], uint8_t program)
{
    uint8_t *maclow = (uint8_t *)mac;
    uint8_t *machigh = (uint8_t *)(mac + 4);
    uint32_t tmpVal;
    uint32_t i = 0, cnt;

    if (slot >= 3) {
        return ERROR;
    }

    /* Change to local order */
    for (i = 0; i < 3; i++) {
        tmpVal = mac[i];
        mac[i] = mac[5 - i];
        mac[5 - i] = tmpVal;
    }

    /* Switch to AHB clock */
    EF_Ctrl_Sw_AHB_Clk_0();

    /* The low 32 bits */
    if (slot == 0) {
        BL_WR_REG(EF_DATA_BASE, EF_DATA_0_EF_WIFI_MAC_LOW, BL_RDWD_FRM_BYTEP(maclow));
    } else if (slot == 1) {
        BL_WR_REG(EF_DATA_BASE, EF_DATA_0_EF_SW_USAGE_2, BL_RDWD_FRM_BYTEP(maclow));
    } else if (slot == 2) {
        BL_WR_REG(EF_DATA_BASE, EF_DATA_0_EF_KEY_SLOT_11_W1, BL_RDWD_FRM_BYTEP(maclow));
    }

    /* The high 16 bits */
    tmpVal = machigh[0] + (machigh[1] << 8);
    cnt = 0;

    for (i = 0; i < 6; i++) {
        cnt += EF_Cfg_Get_Byte_Zero_Cnt(mac[i]);
    }

    tmpVal |= ((cnt & 0x3f) << 16);

    if (slot == 0) {
        BL_WR_REG(EF_DATA_BASE, EF_DATA_0_EF_WIFI_MAC_HIGH, tmpVal);
    } else if (slot == 1) {
        BL_WR_REG(EF_DATA_BASE, EF_DATA_0_EF_SW_USAGE_3, tmpVal);
    } else if (slot == 2) {
        BL_WR_REG(EF_DATA_BASE, EF_DATA_0_EF_KEY_SLOT_11_W2, tmpVal);
    }

    if (program) {
        EF_Ctrl_Program_Efuse_0();
    }

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  Efuse read optional MAC address
 *
 * @param  slot: MAC address slot
 * @param  mac[6]: MAC address buffer
 * @param  reload: Whether reload
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type EF_Ctrl_Read_MAC_Address_Opt(uint8_t slot, uint8_t mac[6], uint8_t reload)
{
    uint8_t *maclow = (uint8_t *)mac;
    uint8_t *machigh = (uint8_t *)(mac + 4);
    uint32_t tmpVal = 0;
    uint32_t i = 0;
    uint32_t cnt = 0;

    if (slot >= 3) {
        return ERROR;
    }

    /* Trigger read data from efuse */
    if (reload) {
        EF_CTRL_LOAD_BEFORE_READ_R0;
    }

    if (slot == 0) {
        tmpVal = BL_RD_REG(EF_DATA_BASE, EF_DATA_0_EF_WIFI_MAC_LOW);
    } else if (slot == 1) {
        tmpVal = BL_RD_REG(EF_DATA_BASE, EF_DATA_0_EF_SW_USAGE_2);
    } else if (slot == 2) {
        tmpVal = BL_RD_REG(EF_DATA_BASE, EF_DATA_0_EF_KEY_SLOT_11_W1);
    }

    BL_WRWD_TO_BYTEP(maclow, tmpVal);

    if (slot == 0) {
        tmpVal = BL_RD_REG(EF_DATA_BASE, EF_DATA_0_EF_WIFI_MAC_HIGH);
    } else if (slot == 1) {
        tmpVal = BL_RD_REG(EF_DATA_BASE, EF_DATA_0_EF_SW_USAGE_3);
    } else if (slot == 2) {
        tmpVal = BL_RD_REG(EF_DATA_BASE, EF_DATA_0_EF_KEY_SLOT_11_W2);
    }

    machigh[0] = tmpVal & 0xff;
    machigh[1] = (tmpVal >> 8) & 0xff;

    /* Check parity */
    for (i = 0; i < 6; i++) {
        cnt += EF_Cfg_Get_Byte_Zero_Cnt(mac[i]);
    }

    if ((cnt & 0x3f) == ((tmpVal >> 16) & 0x3f)) {
        /* Change to network order */
        for (i = 0; i < 3; i++) {
            tmpVal = mac[i];
            mac[i] = mac[5 - i];
            mac[5 - i] = tmpVal;
        }

        return SUCCESS;
    } else {
        return ERROR;
    }
}

/*@} end of group SEC_EF_CTRL_Public_Functions */

/*@} end of group SEC_EF_CTRL */

/*@} end of group BL808_Peripheral_Driver */
