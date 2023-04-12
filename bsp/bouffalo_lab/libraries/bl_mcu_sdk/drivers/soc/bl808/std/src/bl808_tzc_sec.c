/**
  ******************************************************************************
  * @file    bl808_tzc_sec.c
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
#include "bl808_tzc_sec.h"
#include "bl808_glb.h"

/** @addtogroup  BL808_Peripheral_Driver
 *  @{
 */

/** @addtogroup  TZC_ENG
 *  @{
 */

/** @defgroup  TZC_ENG_Private_Macros
 *  @{
 */

/*@} end of group TZC_ENG_Private_Macros */

/** @defgroup  TZC_ENG_Private_Types
 *  @{
 */

/*@} end of group TZC_ENG_Private_Types */

/** @defgroup  TZC_ENG_Private_Variables
 *  @{
 */

/*@} end of group TZC_ENG_Private_Variables */

/** @defgroup  TZC_ENG_Global_Variables
 *  @{
 */

/*@} end of group TZC_ENG_Global_Variables */

/** @defgroup  TZC_ENG_Private_Fun_Declaration
 *  @{
 */

/*@} end of group TZC_ENG_Private_Fun_Declaration */

/** @defgroup  TZC_ENG_Private_Functions
 *  @{
 */

/*@} end of group TZC_ENG_Private_Functions */

/** @defgroup  TZC_ENG_Public_Functions
 *  @{
 */

/****************************************************************************/ /**
 * @brief  None
 *
 * @param  None
 *
 * @return None
 *
*******************************************************************************/
void Tzc_Sec_Set_Sboot_Done(void)
{
    uint32_t tmpVal;
    /* Set Sboot done */
    tmpVal = BL_RD_REG(TZ1_BASE, TZC_SEC_TZC_ROM_TZSRG_CTRL);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, TZC_SEC_TZC_SBOOT_DONE, 0xf);
    BL_WR_REG(TZ1_BASE, TZC_SEC_TZC_ROM_TZSRG_CTRL, tmpVal);
}

void Tzc_Sec_Set_Master_Group(TZC_SEC_Master_Type masterType, uint8_t group)
{
    uint32_t tmpVal;
    uint32_t tmpVal2;

    if (masterType < TZC_SEC_MASTER_D0) {
        tmpVal = BL_RD_REG(TZ1_BASE, TZC_SEC_TZC_BMX_TZMID);
        tmpVal2 = BL_RD_REG(TZ1_BASE, TZC_SEC_TZC_BMX_TZMID_LOCK);

        if (group == 0) {
            tmpVal &= (~(1 << masterType));
        } else {
            tmpVal |= (1 << masterType);
        }
        tmpVal |= (1 << (masterType + 16));
        tmpVal2 |= (1 << masterType);

        BL_WR_REG(TZ1_BASE, TZC_SEC_TZC_BMX_TZMID, tmpVal);
        BL_WR_REG(TZ1_BASE, TZC_SEC_TZC_BMX_TZMID_LOCK, tmpVal2);
    } else {
        masterType -= TZC_SEC_MASTER_D0;

        tmpVal = BL_RD_REG(TZ1_BASE, TZC_SEC_TZC_MM_BMX_TZMID);
        tmpVal2 = BL_RD_REG(TZ1_BASE, TZC_SEC_TZC_MM_BMX_TZMID_LOCK);

        if (group == 0) {
            tmpVal &= (~(1 << masterType));
        } else {
            tmpVal |= (1 << masterType);
        }
        tmpVal |= (1 << (masterType + 16));
        tmpVal2 |= (1 << masterType);

        BL_WR_REG(TZ1_BASE, TZC_SEC_TZC_MM_BMX_TZMID, tmpVal);
        BL_WR_REG(TZ1_BASE, TZC_SEC_TZC_MM_BMX_TZMID_LOCK, tmpVal2);
    }
}

void Tzc_Sec_Set_Slave_Group(TZC_SEC_Slave_Type slaveType, uint8_t group)
{
    uint32_t tmpVal;

    if (group > TZC_SEC_MAX_AUTH_GRP || slaveType >= TZC_SEC_SLAVE_MAX) {
        return;
    }
    group = 1 << (group);

    if (slaveType >= TZC_SEC_SLAVE_MM) {
        slaveType -= TZC_SEC_SLAVE_MM;
        tmpVal = BL_RD_REG(TZ1_BASE, TZC_SEC_TZC_BMX_S0);
        /* set group */
        tmpVal &= (~(3 << (slaveType * 2)));
        tmpVal |= (group << (slaveType * 2));
        /* set lock*/
        tmpVal |= (1 << (slaveType + 16));
        BL_WR_REG(TZ1_BASE, TZC_SEC_TZC_BMX_S0, tmpVal);
    } else if (slaveType < TZC_SEC_SLAVE_EMI_MISC) {
        slaveType -= TZC_SEC_SLAVE_GLB;
        tmpVal = BL_RD_REG(TZ1_BASE, TZC_SEC_TZC_BMX_S1);
        /* set group */
        tmpVal &= (~(3 << (slaveType * 2)));
        tmpVal |= (group << (slaveType * 2));
        BL_WR_REG(TZ1_BASE, TZC_SEC_TZC_BMX_S1, tmpVal);

        tmpVal = BL_RD_REG(TZ1_BASE, TZC_SEC_TZC_BMX_S_LOCK);
        /* set lock */
        tmpVal |= (1 << slaveType);
        BL_WR_REG(TZ1_BASE, TZC_SEC_TZC_BMX_S_LOCK, tmpVal);
    } else {
        slaveType -= TZC_SEC_SLAVE_EMI_MISC;

        tmpVal = BL_RD_REG(TZ1_BASE, TZC_SEC_TZC_BMX_S2);
        /* set group */
        tmpVal &= (~(3 << (slaveType * 2)));
        tmpVal |= (group << (slaveType * 2));
        BL_WR_REG(TZ1_BASE, TZC_SEC_TZC_BMX_S2, tmpVal);

        tmpVal = BL_RD_REG(TZ1_BASE, TZC_SEC_TZC_BMX_S_LOCK);
        /* set lock */
        tmpVal |= (1 << (slaveType + TZC_SEC_SLAVE_EMI_MISC));
        BL_WR_REG(TZ1_BASE, TZC_SEC_TZC_BMX_S_LOCK, tmpVal);
    }
}

void Tzc_Sec_Set_MM_Slave_Group(TZC_SEC_MM_Slave_Type slaveType, uint8_t group)
{
    uint32_t tmpVal;

    if (group > TZC_SEC_MAX_AUTH_GRP || slaveType >= TZC_SEC_MM_SLAVE_MAX) {
        return;
    }
    group = 1 << (group);

    if (slaveType < TZC_SEC_MM_SLAVE_ISP_MISC) {
        /* set group */
        tmpVal = BL_RD_REG(TZ1_BASE, TZC_SEC_TZC_MM_BMX_S0);
        tmpVal &= (~(3 << (slaveType * 2)));
        tmpVal |= (group << (slaveType * 2));
        BL_WR_REG(TZ1_BASE, TZC_SEC_TZC_MM_BMX_S0, tmpVal);

        /* set lock */
        tmpVal = BL_RD_REG(TZ1_BASE, TZC_SEC_TZC_MM_BMX_S_LOCK0);
        tmpVal |= (1 << slaveType);
        BL_WR_REG(TZ1_BASE, TZC_SEC_TZC_MM_BMX_S_LOCK0, tmpVal);

    } else if (slaveType < TZC_SEC_MM_SLAVE_CODEC_MISC) {
        slaveType -= TZC_SEC_MM_SLAVE_ISP_MISC;

        /* set group */
        tmpVal = BL_RD_REG(TZ1_BASE, TZC_SEC_TZC_MM_BMX_S1);
        tmpVal &= (~(3 << (slaveType * 2)));
        tmpVal |= (group << (slaveType * 2));
        BL_WR_REG(TZ1_BASE, TZC_SEC_TZC_MM_BMX_S1, tmpVal);

        /* set lock */
        tmpVal = BL_RD_REG(TZ1_BASE, TZC_SEC_TZC_MM_BMX_S_LOCK1);
        tmpVal |= (1 << (slaveType + 16));
        BL_WR_REG(TZ1_BASE, TZC_SEC_TZC_MM_BMX_S_LOCK1, tmpVal);
    } else {
        slaveType -= TZC_SEC_MM_SLAVE_CODEC_MISC;

        /* set group */
        tmpVal = BL_RD_REG(TZ1_BASE, TZC_SEC_TZC_MM_BMX_S2);
        tmpVal &= (~(3 << (slaveType * 2)));
        tmpVal |= (group << (slaveType * 2));
        BL_WR_REG(TZ1_BASE, TZC_SEC_TZC_MM_BMX_S2, tmpVal);

        /* set lock */
        tmpVal = BL_RD_REG(TZ1_BASE, TZC_SEC_TZC_MM_BMX_S_LOCK1);
        tmpVal |= (1 << slaveType);
        BL_WR_REG(TZ1_BASE, TZC_SEC_TZC_MM_BMX_S_LOCK1, tmpVal);
    }
}

void Tzc_Sec_Set_Glb_Ctrl_Group(TZC_SEC_GLB_Ctrl_Type slaveType, uint8_t group)
{
    uint32_t tmpVal;

    if (slaveType >= TZC_SEC_GLB_CTRL_MAX || group > TZC_SEC_MAX_AUTH_GRP) {
        return;
    }
    group = 1 << (group);

    tmpVal = BL_RD_REG(TZ1_BASE, TZC_SEC_TZC_GLB_CTRL_0);
    /* set group */
    tmpVal &= (~(3 << (slaveType * 2)));
    tmpVal |= (group << (slaveType * 2));
    BL_WR_REG(TZ1_BASE, TZC_SEC_TZC_GLB_CTRL_0, tmpVal);

    tmpVal = BL_RD_REG(TZ1_BASE, TZC_SEC_TZC_GLB_CTRL_2);
    /* set lock */
    tmpVal |= (1 << slaveType);
    BL_WR_REG(TZ1_BASE, TZC_SEC_TZC_GLB_CTRL_2, tmpVal);
}

void Tzc_Sec_Set_MM_Glb_Ctrl_Group(TZC_SEC_MM_GLB_Ctrl_Type slaveType, uint8_t group)
{
    uint32_t tmpVal;

    if (slaveType >= TZC_SEC_MM_GLB_CTRL_MAX || group > TZC_SEC_MAX_AUTH_GRP) {
        return;
    }
    group = 1 << (group);

    tmpVal = BL_RD_REG(TZ1_BASE, TZC_SEC_TZC_MM_CTRL_0);
    /* set group */
    tmpVal &= (~(3 << (slaveType * 2)));
    tmpVal |= (group << (slaveType * 2));
    BL_WR_REG(TZ1_BASE, TZC_SEC_TZC_MM_CTRL_0, tmpVal);

    tmpVal = BL_RD_REG(TZ1_BASE, TZC_SEC_TZC_MM_CTRL_2);
    /* set lock */
    tmpVal |= (1 << slaveType);
    BL_WR_REG(TZ1_BASE, TZC_SEC_TZC_MM_CTRL_2, tmpVal);
}

void Tzc_Sec_Set_CPU_Group(uint8_t cpu, uint8_t group)
{
    uint32_t tmpVal;
    uint32_t tmpVal2;

    if (cpu == GLB_CORE_ID_M0) {
        tmpVal = BL_RD_REG(TZ1_BASE, TZC_SEC_TZC_BMX_TZMID);
        tmpVal2 = BL_RD_REG(TZ1_BASE, TZC_SEC_TZC_BMX_TZMID_LOCK);

        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, TZC_SEC_TZC_CPU_TZMID, group);
        tmpVal2 = BL_SET_REG_BITS_VAL(tmpVal2, TZC_SEC_TZC_CPU_TZMID_LOCK, 1);

        BL_WR_REG(TZ1_BASE, TZC_SEC_TZC_BMX_TZMID, tmpVal);
        BL_WR_REG(TZ1_BASE, TZC_SEC_TZC_BMX_TZMID_LOCK, tmpVal2);
    } else if (cpu == GLB_CORE_ID_D0) {
        tmpVal = BL_RD_REG(TZ1_BASE, TZC_SEC_TZC_MM_BMX_TZMID);
        tmpVal2 = BL_RD_REG(TZ1_BASE, TZC_SEC_TZC_MM_BMX_TZMID_LOCK);

        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, TZC_SEC_TZC_MMCPU_TZMID, group);
        tmpVal2 = BL_SET_REG_BITS_VAL(tmpVal2, TZC_SEC_TZC_MMCPU_TZMID, 1);

        BL_WR_REG(TZ1_BASE, TZC_SEC_TZC_MM_BMX_TZMID, tmpVal);
        BL_WR_REG(TZ1_BASE, TZC_SEC_TZC_MM_BMX_TZMID_LOCK, tmpVal2);

    } else if (cpu == GLB_CORE_ID_LP) {
        tmpVal = BL_RD_REG(TZ1_BASE, TZC_SEC_TZC_BMX_TZMID);
        tmpVal2 = BL_RD_REG(TZ1_BASE, TZC_SEC_TZC_BMX_TZMID_LOCK);

        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, TZC_SEC_TZC_PICO_TZMID, group);
        tmpVal2 = BL_SET_REG_BITS_VAL(tmpVal2, TZC_SEC_TZC_PICO_TZMID_LOCK, 1);

        BL_WR_REG(TZ1_BASE, TZC_SEC_TZC_BMX_TZMID, tmpVal);
        BL_WR_REG(TZ1_BASE, TZC_SEC_TZC_BMX_TZMID_LOCK, tmpVal2);
    }
}

/****************************************************************************/ /**
 * @brief  TrustZone Security set ROM region access configuration
 *
 * @param  region: ROM region index 0-2
 * @param  startAddr: ROM region start address
 * @param  length: ROM region length
 * @param  group: ROM region auth group type
 *
 * @return None
 *
*******************************************************************************/
void Tzc_Sec_ROM_Access_Set(uint8_t region, uint32_t startAddr, uint32_t length, uint8_t group)
{
    uint32_t tmpVal = 0;
    uint32_t alignEnd = (startAddr+length+1023)&~0x3FF;

    /* check the parameter */
    CHECK_PARAM(IS_TZC_SEC_GROUP_TYPE(group));
    if (region >= 3 || group > TZC_SEC_MAX_AUTH_GRP) {
        return;
    }
    group = 1 << (group);

    tmpVal = BL_RD_REG(TZC_SEC_BASE, TZC_SEC_TZC_ROM_TZSRG_CTRL);
    tmpVal &= (~(3 << (region * 2)));
    tmpVal |= (group << (region * 2));
    BL_WR_REG(TZC_SEC_BASE, TZC_SEC_TZC_ROM_TZSRG_CTRL, tmpVal);

    tmpVal = (((alignEnd >> 10) & 0xffff) - 1) | (((startAddr >> 10) & 0xffff) << 16);
    BL_WR_WORD(TZC_SEC_BASE + TZC_SEC_TZC_ROM_TZSRG_R0_OFFSET + region * 4, tmpVal);

    /* set enable and lock */
    tmpVal = BL_RD_REG(TZC_SEC_BASE, TZC_SEC_TZC_ROM_TZSRG_CTRL);
    tmpVal |= 1 << (region + 16);
    tmpVal |= 1 << (region + 24);
    BL_WR_REG(TZC_SEC_BASE, TZC_SEC_TZC_ROM_TZSRG_CTRL, tmpVal);
}

/****************************************************************************/ /**
 * @brief  TrustZone Security set OCRAM region access configuration
 *
 * @param  region: OCRAM region index 0-2
 * @param  startAddr: OCRAM region start address
 * @param  length: OCRAM region length
 * @param  group: OCRAM region auth group type
 *
 * @return None
 *
*******************************************************************************/
void Tzc_Sec_OCRAM_Access_Set_Advance(uint8_t region, uint32_t startAddr, uint32_t length, uint8_t group)
{
    uint32_t tmpVal = 0;
    uint32_t alignEnd = (startAddr+length+1023)&~0x3FF;

    /* check the parameter */
    CHECK_PARAM(IS_TZC_SEC_GROUP_TYPE(group));
    if (region >= 3) {
        return;
    }
    group = group & 0xf;

    tmpVal = BL_RD_REG(TZC_SEC_BASE, TZC_SEC_TZC_OCRAM_TZSRG_CTRL);
    tmpVal &= (~(0xf << (region * 4)));
    tmpVal |= (group << (region * 4));
    BL_WR_REG(TZC_SEC_BASE, TZC_SEC_TZC_OCRAM_TZSRG_CTRL, tmpVal);

    tmpVal = (((alignEnd >> 10) & 0xffff) - 1) | (((startAddr >> 10) & 0xffff) << 16);
    BL_WR_WORD(TZC_SEC_BASE + TZC_SEC_TZC_OCRAM_TZSRG_R0_OFFSET + region * 4, tmpVal);

    /* set enable and lock */
    tmpVal = BL_RD_REG(TZC_SEC_BASE, TZC_SEC_TZC_OCRAM_TZSRG_CTRL);
    tmpVal |= 1 << (region + 16);
    tmpVal |= 1 << (region + 20);
    BL_WR_REG(TZC_SEC_BASE, TZC_SEC_TZC_OCRAM_TZSRG_CTRL, tmpVal);
}

/****************************************************************************/ /**
 * @brief  TrustZone Security set OCRAM regionx access configuration
 *
 * @param  group: OCRAM region auth group type
 *
 * @return None
 *
*******************************************************************************/
void Tzc_Sec_OCRAM_Access_Set_Regionx(uint8_t group)
{
    uint32_t tmpVal = 0;
    uint8_t region = 3;

    /* check the parameter */
    CHECK_PARAM(IS_TZC_SEC_GROUP_TYPE(group));
    if (group > TZC_SEC_MAX_AUTH_GRP) {
        return;
    }
    group = 1 << (group);

    tmpVal = BL_RD_REG(TZC_SEC_BASE, TZC_SEC_TZC_OCRAM_TZSRG_CTRL);
    tmpVal &= (~(3 << (region * 4)));
    tmpVal |= (group << (region * 4));
    BL_WR_REG(TZC_SEC_BASE, TZC_SEC_TZC_OCRAM_TZSRG_CTRL, tmpVal);

    /* set enable and lock */
    tmpVal = BL_RD_REG(TZC_SEC_BASE, TZC_SEC_TZC_OCRAM_TZSRG_CTRL);
    tmpVal |= 1 << (region + 16);
    tmpVal |= 1 << (region + 20);
    BL_WR_REG(TZC_SEC_BASE, TZC_SEC_TZC_OCRAM_TZSRG_CTRL, tmpVal);
}

/****************************************************************************/ /**
 * @brief  TrustZone Security set WRAM region access configuration
 *
 * @param  region: WRAM region index 0-2
 * @param  startAddr: WRAM region start address
 * @param  length: WRAM region length
 * @param  group: WRAM region auth group type
 *
 * @return None
 *
*******************************************************************************/
void Tzc_Sec_WRAM_Access_Set_Advance(uint8_t region, uint32_t startAddr, uint32_t length, uint8_t group)
{
    uint32_t tmpVal = 0;
    uint32_t alignEnd = (startAddr+length+1023)&~0x3FF;

    /* check the parameter */
    CHECK_PARAM(IS_TZC_SEC_GROUP_TYPE(group));
    if (region >= 3) {
        return;
    }
    group = group & 0xf;

    tmpVal = BL_RD_REG(TZC_SEC_BASE, TZC_SEC_TZC_WRAM_TZSRG_CTRL);
    tmpVal &= (~(0xf << (region * 4)));
    tmpVal |= (group << (region * 4));
    BL_WR_REG(TZC_SEC_BASE, TZC_SEC_TZC_WRAM_TZSRG_CTRL, tmpVal);

    tmpVal = (((alignEnd >> 10) & 0xffff) - 1) | (((startAddr >> 10) & 0xffff) << 16);
    BL_WR_WORD(TZC_SEC_BASE + TZC_SEC_TZC_WRAM_TZSRG_R0_OFFSET + region * 4, tmpVal);

    /* set enable and lock */
    tmpVal = BL_RD_REG(TZC_SEC_BASE, TZC_SEC_TZC_WRAM_TZSRG_CTRL);
    tmpVal |= 1 << (region + 16);
    tmpVal |= 1 << (region + 20);
    BL_WR_REG(TZC_SEC_BASE, TZC_SEC_TZC_WRAM_TZSRG_CTRL, tmpVal);
}

/****************************************************************************/ /**
 * @brief  TrustZone Security set WRAM regionx access configuration
 *
 * @param  group: WRAM region auth group type
 *
 * @return None
 *
*******************************************************************************/
void Tzc_Sec_WRAM_Access_Set_Regionx(uint8_t group)
{
    uint32_t tmpVal = 0;
    uint8_t region = 3;

    /* check the parameter */
    CHECK_PARAM(IS_TZC_SEC_GROUP_TYPE(group));
    if (group > TZC_SEC_MAX_AUTH_GRP) {
        return;
    }
    group = 1 << (group);

    tmpVal = BL_RD_REG(TZC_SEC_BASE, TZC_SEC_TZC_WRAM_TZSRG_CTRL);
    tmpVal &= (~(3 << (region * 4)));
    tmpVal |= (group << (region * 4));
    BL_WR_REG(TZC_SEC_BASE, TZC_SEC_TZC_WRAM_TZSRG_CTRL, tmpVal);

    /* set enable and lock */
    tmpVal = BL_RD_REG(TZC_SEC_BASE, TZC_SEC_TZC_WRAM_TZSRG_CTRL);
    tmpVal |= 1 << (region + 16);
    tmpVal |= 1 << (region + 20);
    BL_WR_REG(TZC_SEC_BASE, TZC_SEC_TZC_WRAM_TZSRG_CTRL, tmpVal);
}

/****************************************************************************/ /**
 * @brief  TrustZone Security set Flash region access configuration
 *
 * @param  region: Flash region index 0-2
 * @param  startAddr: Flash region start address
 * @param  length: Flash region length
 * @param  group: Flash region auth group type
 *
 * @return None
 *
*******************************************************************************/
void Tzc_Sec_Flash_Access_Set_Advance(uint8_t region, uint32_t startAddr, uint32_t length, uint8_t group)
{
    uint32_t tmpVal = 0;
    uint32_t tmpVal2 = 0;
    uint32_t alignEnd = (startAddr+length+1023)&~0x3FF;

    /* check the parameter */
    CHECK_PARAM(IS_TZC_SEC_GROUP_TYPE(group));
    if (region >= 4 || group > TZC_SEC_MAX_AUTH_GRP) {
        return;
    }
    group = 0xf & (group);

    tmpVal = BL_RD_REG(TZC_SEC_BASE, TZC_SEC_TZC_SF_TZSRG_CTRL);
    tmpVal &= (~(0xf << (region * 4)));
    tmpVal |= (group << (region * 4));
    BL_WR_REG(TZC_SEC_BASE, TZC_SEC_TZC_SF_TZSRG_CTRL, tmpVal);

    /* Set range */
    tmpVal = (((alignEnd >> 10) & 0xffff) - 1) | (((startAddr >> 10) & 0xffff) << 16);
    BL_WR_WORD(TZC_SEC_BASE + TZC_SEC_TZC_SF_TZSRG_R0_OFFSET + region * 4, tmpVal);

    /* Set range MSB */
    tmpVal = BL_RD_WORD(TZC_SEC_BASE + TZC_SEC_TZC_SF_TZSRG_MSB_OFFSET);
    tmpVal = tmpVal & (0xff << (8 * region));
    tmpVal2 = ((alignEnd >> 26) & 0x7) | (((startAddr >> 26) & 0x7) << 3);
    tmpVal2 = tmpVal2 << (8 * region);
    BL_WR_WORD(TZC_SEC_BASE + TZC_SEC_TZC_SF_TZSRG_MSB_OFFSET, tmpVal | tmpVal2);

    /* set enable and lock */
    tmpVal = BL_RD_REG(TZC_SEC_BASE, TZC_SEC_TZC_SF_TZSRG_CTRL);
    tmpVal |= 1 << (region + 20);
    tmpVal |= 1 << (region + 25);
    BL_WR_REG(TZC_SEC_BASE, TZC_SEC_TZC_SF_TZSRG_CTRL, tmpVal);
}

/****************************************************************************/ /**
 * @brief  TrustZone Security set Flash regionx access configuration
 *
 * @param  group: Flash region auth group type
 *
 * @return None
 *
*******************************************************************************/
void Tzc_Sec_Flash_Access_Set_Regionx(uint8_t group)
{
    uint32_t tmpVal = 0;
    uint8_t region = 4;

    /* check the parameter */
    CHECK_PARAM(IS_TZC_SEC_GROUP_TYPE(group));
    if (group > TZC_SEC_MAX_AUTH_GRP) {
        return;
    }
    group = 1 << (group);

    tmpVal = BL_RD_REG(TZC_SEC_BASE, TZC_SEC_TZC_SF_TZSRG_CTRL);
    tmpVal &= (~(3 << (region * 4)));
    tmpVal |= (group << (region * 4));
    BL_WR_REG(TZC_SEC_BASE, TZC_SEC_TZC_SF_TZSRG_CTRL, tmpVal);

    /* set enable and lock */
    tmpVal = BL_RD_REG(TZC_SEC_BASE, TZC_SEC_TZC_SF_TZSRG_CTRL);
    tmpVal |= 1 << (region + 20);
    tmpVal |= 1 << (region + 25);
    BL_WR_REG(TZC_SEC_BASE, TZC_SEC_TZC_SF_TZSRG_CTRL, tmpVal);
}

/****************************************************************************/ /**
 * @brief  TrustZone Security set L2SRAM region access configuration
 *
 * @param  region: L2SRAM region index 0-2
 * @param  startAddr: L2SRAM region start address
 * @param  length: L2SRAM region length
 * @param  group: L2SRAM region auth group type
 *
 * @return None
 *
*******************************************************************************/
void Tzc_Sec_L2SRAM_Access_Set(uint8_t region, uint32_t startAddr, uint32_t length, uint8_t group)
{
    uint32_t tmpVal = 0;
    uint32_t alignEnd = (startAddr+length+1023)&~0x3FF;

    /* check the parameter */
    CHECK_PARAM(IS_TZC_SEC_GROUP_TYPE(group));
    if (region >= 3 || group > TZC_SEC_MAX_AUTH_GRP) {
        return;
    }
    group = 1 << (group);

    tmpVal = BL_RD_REG(TZC_SEC_BASE, TZC_SEC_TZC_L2SRAM_TZSRG_CTRL);
    tmpVal &= (~(3 << (region * 2)));
    tmpVal |= (group << (region * 2));
    BL_WR_REG(TZC_SEC_BASE, TZC_SEC_TZC_L2SRAM_TZSRG_CTRL, tmpVal);

    tmpVal = (((alignEnd >> 10) & 0xffff) - 1) | (((startAddr >> 10) & 0xffff) << 16);
    BL_WR_WORD(TZC_SEC_BASE + TZC_SEC_TZC_L2SRAM_TZSRG_R0_OFFSET + region * 4, tmpVal);

    /* set enable and lock */
    tmpVal = BL_RD_REG(TZC_SEC_BASE, TZC_SEC_TZC_L2SRAM_TZSRG_CTRL);
    tmpVal |= 1 << (region + 16);
    tmpVal |= 1 << (region + 24);
    BL_WR_REG(TZC_SEC_BASE, TZC_SEC_TZC_L2SRAM_TZSRG_CTRL, tmpVal);
}

/****************************************************************************/ /**
 * @brief  TrustZone Security set VRAM region access configuration
 *
 * @param  region: VRAM region index 0-2
 * @param  startAddr: VRAM region start address
 * @param  length: VRAM region length
 * @param  group: VRAM region auth group type
 *
 * @return None
 *
*******************************************************************************/
void Tzc_Sec_VRAM_Access_Set(uint8_t region, uint32_t startAddr, uint32_t length, uint8_t group)
{
    uint32_t tmpVal = 0;
    uint32_t alignEnd = (startAddr+length+1023)&~0x3FF;

    /* check the parameter */
    CHECK_PARAM(IS_TZC_SEC_GROUP_TYPE(group));
    if (region >= 3 || group > TZC_SEC_MAX_AUTH_GRP) {
        return;
    }
    group = 1 << (group);

    tmpVal = BL_RD_REG(TZC_SEC_BASE, TZC_SEC_TZC_VRAM_TZSRG_CTRL);
    tmpVal &= (~(3 << (region * 2)));
    tmpVal |= (group << (region * 2));
    BL_WR_REG(TZC_SEC_BASE, TZC_SEC_TZC_VRAM_TZSRG_CTRL, tmpVal);

    tmpVal = (((alignEnd >> 10) & 0xffff) - 1) | (((startAddr >> 10) & 0xffff) << 16);
    BL_WR_WORD(TZC_SEC_BASE + TZC_SEC_TZC_VRAM_TZSRG_R0_OFFSET + region * 4, tmpVal);

    /* set enable lock */
    tmpVal = BL_RD_REG(TZC_SEC_BASE, TZC_SEC_TZC_VRAM_TZSRG_CTRL);
    tmpVal |= 1 << (region + 16);
    tmpVal |= 1 << (region + 24);
    BL_WR_REG(TZC_SEC_BASE, TZC_SEC_TZC_VRAM_TZSRG_CTRL, tmpVal);
}

/****************************************************************************/ /**
 * @brief  TrustZone Security set PSRAMA region access configuration
 *
 * @param  region: PSRAMA region index 0-2
 * @param  startAddr: PSRAMA region start address
 * @param  length: PSRAMA region length
 * @param  group: PSRAMA region auth group type
 *
 * @return None
 *
*******************************************************************************/
void Tzc_Sec_PSRAMA_Access_Set(uint8_t region, uint32_t startAddr, uint32_t length, uint8_t group)
{
    uint32_t tmpVal = 0;
    uint32_t alignEnd = (startAddr+length+1023)&~0x3FF;

    /* check the parameter */
    CHECK_PARAM(IS_TZC_SEC_GROUP_TYPE(group));
    if (region >= 3 || group > TZC_SEC_MAX_AUTH_GRP) {
        return;
    }
    group = 1 << (group);

    tmpVal = BL_RD_REG(TZC_SEC_BASE, TZC_SEC_TZC_PSRAMA_TZSRG_CTRL);
    tmpVal &= (~(3 << (region * 2)));
    tmpVal |= (group << (region * 2));
    BL_WR_REG(TZC_SEC_BASE, TZC_SEC_TZC_PSRAMA_TZSRG_CTRL, tmpVal);

    tmpVal = (((alignEnd >> 10) & 0xffff) - 1) | (((startAddr >> 10) & 0xffff) << 16);
    BL_WR_WORD(TZC_SEC_BASE + TZC_SEC_TZC_PSRAMA_TZSRG_R0_OFFSET + region * 4, tmpVal);

    /* set enable and lock */
    tmpVal = BL_RD_REG(TZC_SEC_BASE, TZC_SEC_TZC_PSRAMA_TZSRG_CTRL);
    tmpVal |= 1 << (region + 16);
    tmpVal |= 1 << (region + 24);
    BL_WR_REG(TZC_SEC_BASE, TZC_SEC_TZC_PSRAMA_TZSRG_CTRL, tmpVal);
}

/**
 * @brief TrustZone Security set Release PSRAMA region access
 *
 */
void Tzc_Sec_PSRAMA_Access_Release(void)
{
    uint32_t tmpVal = 0;
    uint32_t region = 0;
    /* set disable */
    tmpVal = BL_RD_REG(TZC_SEC_BASE, TZC_SEC_TZC_PSRAMA_TZSRG_CTRL);
    tmpVal &= (~(1 << (region + 16)));
    BL_WR_REG(TZC_SEC_BASE, TZC_SEC_TZC_PSRAMA_TZSRG_CTRL, tmpVal);
}

/****************************************************************************/ /**
 * @brief  TrustZone Security set PSRAMB region access configuration
 *
 * @param  region: PSRAMB region index 0-2
 * @param  startAddr: PSRAMB region start address
 * @param  length: PSRAMB region length
 * @param  group: PSRAMB region auth group type
 *
 * @return None
 *
*******************************************************************************/
void Tzc_Sec_PSRAMB_Access_Set(uint8_t region, uint32_t startAddr, uint32_t length, uint8_t group)
{
    uint32_t tmpVal = 0;
    uint32_t alignEnd = (startAddr+length+1023)&~0x3FF;

    /* check the parameter */
    CHECK_PARAM(IS_TZC_SEC_GROUP_TYPE(group));
    if (region >= 3 || group > TZC_SEC_MAX_AUTH_GRP) {
        return;
    }
    group = 1 << (group);

    tmpVal = BL_RD_REG(TZC_SEC_BASE, TZC_SEC_TZC_PSRAMB_TZSRG_CTRL);
    tmpVal &= (~(3 << (region * 2)));
    tmpVal |= (group << (region * 2));
    BL_WR_REG(TZC_SEC_BASE, TZC_SEC_TZC_PSRAMB_TZSRG_CTRL, tmpVal);

    tmpVal = (((alignEnd >> 10) & 0xffff) - 1) | (((startAddr >> 10) & 0xffff) << 16);
    BL_WR_WORD(TZC_SEC_BASE + TZC_SEC_TZC_PSRAMB_TZSRG_R0_OFFSET + region * 4, tmpVal);

    /* set enable and lock */
    tmpVal = BL_RD_REG(TZC_SEC_BASE, TZC_SEC_TZC_PSRAMB_TZSRG_CTRL);
    tmpVal |= 1 << (region + 16);
    tmpVal |= 1 << (region + 24);
    BL_WR_REG(TZC_SEC_BASE, TZC_SEC_TZC_PSRAMB_TZSRG_CTRL, tmpVal);
}
/**
 * @brief TrustZone Security set Release PSRAMB region access
 *
 */
void Tzc_Sec_PSRAMB_Access_Release(void)
{
    uint32_t tmpVal = 0;
    uint32_t region = 0;
    /* set disable */
    tmpVal = BL_RD_REG(TZC_SEC_BASE, TZC_SEC_TZC_PSRAMB_TZSRG_CTRL);
    tmpVal &= (~(1 << (region + 16)));
    BL_WR_REG(TZC_SEC_BASE, TZC_SEC_TZC_PSRAMB_TZSRG_CTRL, tmpVal);
}
/****************************************************************************/ /**
 * @brief  TrustZone Security set XRAM region access configuration
 *
 * @param  region: XRAM region index 0-2
 * @param  startAddr: XRAM region start address
 * @param  length: XRAM region length
 * @param  group: XRAM region auth group type
 *
 * @return None
 *
*******************************************************************************/
void Tzc_Sec_XRAM_Access_Set(uint8_t region, uint32_t startAddr, uint32_t length, uint8_t group)
{
    uint32_t tmpVal = 0;
    uint32_t alignEnd = (startAddr+length+1023)&~0x3FF;

    /* check the parameter */
    CHECK_PARAM(IS_TZC_SEC_GROUP_TYPE(group));
    if (region >= 3 || group > TZC_SEC_MAX_AUTH_GRP) {
        return;
    }
    group = 1 << (group);

    tmpVal = BL_RD_REG(TZC_SEC_BASE, TZC_SEC_TZC_XRAM_TZSRG_CTRL);
    tmpVal &= (~(3 << (region * 2)));
    tmpVal |= (group << (region * 2));
    BL_WR_REG(TZC_SEC_BASE, TZC_SEC_TZC_XRAM_TZSRG_CTRL, tmpVal);

    tmpVal = (((alignEnd >> 10) & 0xffff) - 1) | (((startAddr >> 10) & 0xffff) << 16);
    BL_WR_WORD(TZC_SEC_BASE + TZC_SEC_TZC_XRAM_TZSRG_R0_OFFSET + region * 4, tmpVal);

    /* set enable and lock */
    tmpVal = BL_RD_REG(TZC_SEC_BASE, TZC_SEC_TZC_XRAM_TZSRG_CTRL);
    tmpVal |= 1 << (region + 16);
    tmpVal |= 1 << (region + 24);
    BL_WR_REG(TZC_SEC_BASE, TZC_SEC_TZC_XRAM_TZSRG_CTRL, tmpVal);
}

/****************************************************************************/ /**
 * @brief  TrustZone Security set sec_eng module config
 *
 * @param  mode: sec_eng control mode
 *
 * @return None
 *
*******************************************************************************/
void Tzc_Sec_Set_Se_Ctrl_Mode(TZC_SEC_SE_Ctrl_Mode mode)
{
    uint32_t tmpVal = 0;

    tmpVal = BL_RD_REG(TZC_SEC_BASE, TZC_SEC_TZC_SE_CTRL_0);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, TZC_SEC_TZC_SE_TZSID_CRMD, mode);
    BL_WR_REG(TZC_SEC_BASE, TZC_SEC_TZC_SE_CTRL_0, tmpVal);

    tmpVal = BL_RD_REG(TZ1_BASE, TZC_SEC_TZC_SE_CTRL_2);
    /* set lock */
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, TZC_SEC_TZC_SE_TZSID_CRMD_LOCK, 1);
    BL_WR_REG(TZ1_BASE, TZC_SEC_TZC_SE_CTRL_2, tmpVal);
}

/****************************************************************************/ /**
 * @brief  TrustZone Security set sf_ctrl module config
 *
 * @param  mode: sf_ctrl control mode
 *
 * @return None
 *
*******************************************************************************/
void Tzc_Sec_Set_Sf_Ctrl_Mode(TZC_SEC_SE_Ctrl_Mode mode)
{
    uint32_t tmpVal = 0;

    tmpVal = BL_RD_REG(TZC_SEC_BASE, TZC_SEC_TZC_SE_CTRL_1);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, TZC_SEC_TZC_SF_TZSID_CRMD, mode);
    BL_WR_REG(TZC_SEC_BASE, TZC_SEC_TZC_SE_CTRL_1, tmpVal);

    tmpVal = BL_RD_REG(TZ1_BASE, TZC_SEC_TZC_SE_CTRL_2);
    /* set lock */
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, TZC_SEC_TZC_SF_TZSID_CRMD_LOCK, 1);
    BL_WR_REG(TZ1_BASE, TZC_SEC_TZC_SE_CTRL_2, tmpVal);
}

void Tzc_Sec_Set_Se_Group(TZC_SEC_SE_Ctrl_Type slaveType, uint8_t group)
{
    uint32_t tmpVal;

    if (group > TZC_SEC_MAX_AUTH_GRP || slaveType >= TZC_SEC_SE_CTRL_MAX) {
        return;
    }
    group = 1 << (group);

    tmpVal = BL_RD_REG(TZ1_BASE, TZC_SEC_TZC_SE_CTRL_0);
    /* set group */
    tmpVal &= (~(3 << (slaveType * 2)));
    tmpVal |= (group << (slaveType * 2));
    BL_WR_REG(TZ1_BASE, TZC_SEC_TZC_SE_CTRL_0, tmpVal);

    tmpVal = BL_RD_REG(TZ1_BASE, TZC_SEC_TZC_SE_CTRL_2);
    /* set lock */
    tmpVal |= (1 << (slaveType));
    BL_WR_REG(TZ1_BASE, TZC_SEC_TZC_SE_CTRL_2, tmpVal);
}

void Tzc_Sec_Set_Sf_Group(TZC_SEC_SF_Ctrl_Type slaveType, uint8_t group)
{
    uint32_t tmpVal;

    if (group > TZC_SEC_MAX_AUTH_GRP || slaveType >= TZC_SEC_SF_CTRL_MAX) {
        return;
    }
    group = 1 << (group);

    tmpVal = BL_RD_REG(TZ1_BASE, TZC_SEC_TZC_SE_CTRL_1);
    /* set group */
    tmpVal &= (~(3 << (slaveType * 2)));
    tmpVal |= (group << (slaveType * 2));
    BL_WR_REG(TZ1_BASE, TZC_SEC_TZC_SE_CTRL_1, tmpVal);

    tmpVal = BL_RD_REG(TZ1_BASE, TZC_SEC_TZC_SE_CTRL_2);
    /* set lock */
    tmpVal |= (1 << (slaveType + 16));
    BL_WR_REG(TZ1_BASE, TZC_SEC_TZC_SE_CTRL_2, tmpVal);
}

/****************************************************************************/ /**
 * @brief  TrustZone Security set watchdog reset delay value
 *
 * @param  mode: sec_eng control mode
 *
 * @return None
 *
*******************************************************************************/
void Tzc_Sec_Set_WTD_Rst_Delay(uint16_t delayValue)
{
    uint32_t tmpVal = 0;

    tmpVal = BL_RD_REG(TZC_SEC_BASE, TZC_SEC_TZC_SE_CTRL_0);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, TZC_SEC_TZC_SE_WDT_DLY, delayValue);
    BL_WR_REG(TZC_SEC_BASE, TZC_SEC_TZC_SE_CTRL_0, tmpVal);
}

/*@} end of group TZC_ENG_Public_Functions */

/*@} end of group TZC_ENG */

/*@} end of group BL808_Peripheral_Driver */
