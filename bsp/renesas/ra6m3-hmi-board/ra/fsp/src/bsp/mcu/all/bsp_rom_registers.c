/***********************************************************************************************************************
 * Copyright [2020-2023] Renesas Electronics Corporation and/or its affiliates.  All Rights Reserved.
 *
 * This software and documentation are supplied by Renesas Electronics America Inc. and may only be used with products
 * of Renesas Electronics Corp. and its affiliates ("Renesas").  No other uses are authorized.  Renesas products are
 * sold pursuant to Renesas terms and conditions of sale.  Purchasers are solely responsible for the selection and use
 * of Renesas products and Renesas assumes no liability.  No license, express or implied, to any intellectual property
 * right is granted by Renesas. This software is protected under all applicable laws, including copyright laws. Renesas
 * reserves the right to change or discontinue this software and/or this documentation. THE SOFTWARE AND DOCUMENTATION
 * IS DELIVERED TO YOU "AS IS," AND RENESAS MAKES NO REPRESENTATIONS OR WARRANTIES, AND TO THE FULLEST EXTENT
 * PERMISSIBLE UNDER APPLICABLE LAW, DISCLAIMS ALL WARRANTIES, WHETHER EXPLICITLY OR IMPLICITLY, INCLUDING WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE, AND NONINFRINGEMENT, WITH RESPECT TO THE SOFTWARE OR
 * DOCUMENTATION.  RENESAS SHALL HAVE NO LIABILITY ARISING OUT OF ANY SECURITY VULNERABILITY OR BREACH.  TO THE MAXIMUM
 * EXTENT PERMITTED BY LAW, IN NO EVENT WILL RENESAS BE LIABLE TO YOU IN CONNECTION WITH THE SOFTWARE OR DOCUMENTATION
 * (OR ANY PERSON OR ENTITY CLAIMING RIGHTS DERIVED FROM YOU) FOR ANY LOSS, DAMAGES, OR CLAIMS WHATSOEVER, INCLUDING,
 * WITHOUT LIMITATION, ANY DIRECT, CONSEQUENTIAL, SPECIAL, INDIRECT, PUNITIVE, OR INCIDENTAL DAMAGES; ANY LOST PROFITS,
 * OTHER ECONOMIC DAMAGE, PROPERTY DAMAGE, OR PERSONAL INJURY; AND EVEN IF RENESAS HAS BEEN ADVISED OF THE POSSIBILITY
 * OF SUCH LOSS, DAMAGES, CLAIMS OR COSTS.
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Includes   <System Includes> , "Project Includes"
 **********************************************************************************************************************/
#include "bsp_api.h"

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/
#define RA_NOT_DEFINED    (0)

/** OR in the HOCO frequency setting from bsp_clock_cfg.h with the OFS1 setting from bsp_cfg.h. */
#define BSP_ROM_REG_OFS1_SETTING                                             \
    (((uint32_t) BSP_CFG_ROM_REG_OFS1 & BSP_FEATURE_BSP_OFS1_HOCOFRQ_MASK) | \
     ((uint32_t) BSP_CFG_HOCO_FREQUENCY << BSP_FEATURE_BSP_OFS1_HOCOFRQ_OFFSET))

/** Build up SECMPUAC register based on MPU settings. */
#define BSP_ROM_REG_MPU_CONTROL_SETTING                     \
    ((0xFFFFFCF0U) |                                        \
     ((uint32_t) BSP_CFG_ROM_REG_MPU_PC0_ENABLE << 8) |     \
     ((uint32_t) BSP_CFG_ROM_REG_MPU_PC1_ENABLE << 9) |     \
     ((uint32_t) BSP_CFG_ROM_REG_MPU_REGION0_ENABLE) |      \
     ((uint32_t) BSP_CFG_ROM_REG_MPU_REGION1_ENABLE << 1) | \
     ((uint32_t) BSP_CFG_ROM_REG_MPU_REGION2_ENABLE << 2) | \
     ((uint32_t) BSP_CFG_ROM_REG_MPU_REGION3_ENABLE << 3))

/*******************************************************************************************************************//**
 * @addtogroup BSP_MCU
 * @{
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Exported global variables (to be accessed by other files)
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Private global variables and functions
 **********************************************************************************************************************/

#if !BSP_CFG_BOOT_IMAGE

 #if BSP_FEATURE_FLASH_SUPPORTS_ID_CODE == 1

/** ID code definitions defined here. */
BSP_DONT_REMOVE static const uint32_t g_bsp_id_codes[] BSP_PLACE_IN_SECTION (BSP_SECTION_ID_CODE) =
{
    BSP_CFG_ID_CODE_LONG_1,
  #if BSP_FEATURE_BSP_OSIS_PADDING
    0xFFFFFFFFU,
  #endif
    BSP_CFG_ID_CODE_LONG_2,
  #if BSP_FEATURE_BSP_OSIS_PADDING
    0xFFFFFFFFU,
  #endif
    BSP_CFG_ID_CODE_LONG_3,
  #if BSP_FEATURE_BSP_OSIS_PADDING
    0xFFFFFFFFU,
  #endif
    BSP_CFG_ID_CODE_LONG_4
};
 #endif

 #if 33U != __CORTEX_M && 85U != __CORTEX_M // NOLINT(readability-magic-numbers)

/** ROM registers defined here. Some have masks to make sure reserved bits are set appropriately. */
BSP_DONT_REMOVE static const uint32_t g_bsp_rom_registers[] BSP_PLACE_IN_SECTION (BSP_SECTION_ROM_REGISTERS) =
{
    (uint32_t) BSP_CFG_ROM_REG_OFS0,
    (uint32_t) BSP_ROM_REG_OFS1_SETTING,
    ((uint32_t) BSP_CFG_ROM_REG_MPU_PC0_START & 0xFFFFFFFCU),
    ((uint32_t) BSP_CFG_ROM_REG_MPU_PC0_END | 0x00000003U),
    ((uint32_t) BSP_CFG_ROM_REG_MPU_PC1_START & 0xFFFFFFFCU),
    ((uint32_t) BSP_CFG_ROM_REG_MPU_PC1_END | 0x00000003U),
    ((uint32_t) BSP_CFG_ROM_REG_MPU_REGION0_START & BSP_FEATURE_BSP_MPU_REGION0_MASK & 0xFFFFFFFCU),
    (((uint32_t) BSP_CFG_ROM_REG_MPU_REGION0_END & BSP_FEATURE_BSP_MPU_REGION0_MASK) | 0x00000003U),
    ((uint32_t) BSP_CFG_ROM_REG_MPU_REGION1_START & 0xFFFFFFFCU),
    ((uint32_t) BSP_CFG_ROM_REG_MPU_REGION1_END | 0x00000003U),
    (((uint32_t) BSP_CFG_ROM_REG_MPU_REGION2_START & 0x407FFFFCU) | 0x40000000U),
    (((uint32_t) BSP_CFG_ROM_REG_MPU_REGION2_END & 0x407FFFFCU) | 0x40000003U),
    (((uint32_t) BSP_CFG_ROM_REG_MPU_REGION3_START & 0x407FFFFCU) | 0x40000000U),
    (((uint32_t) BSP_CFG_ROM_REG_MPU_REGION3_END & 0x407FFFFCU) | 0x40000003U),
    (uint32_t) BSP_ROM_REG_MPU_CONTROL_SETTING
};

 #elif BSP_FEATURE_FLASH_SUPPORTS_ID_CODE == 1

  #if !BSP_TZ_NONSECURE_BUILD
BSP_DONT_REMOVE static const uint32_t BSP_PLACE_IN_SECTION(".option_setting_ofs0") g_bsp_rom_ofs0 =
    BSP_CFG_ROM_REG_OFS0;

BSP_DONT_REMOVE static const uint32_t BSP_PLACE_IN_SECTION(".option_setting_sas") g_bsp_rom_sas =
    0xFFFFFFFF;

BSP_DONT_REMOVE static const uint32_t BSP_PLACE_IN_SECTION(".option_setting_ofs1_sec") g_bsp_rom_ofs1 =
    BSP_ROM_REG_OFS1_SETTING;

BSP_DONT_REMOVE static const uint32_t BSP_PLACE_IN_SECTION(".option_setting_bps_sec0") g_bsp_rom_bps0 =
    BSP_CFG_ROM_REG_BPS0;

BSP_DONT_REMOVE static const uint32_t BSP_PLACE_IN_SECTION(".option_setting_pbps_sec0") g_bsp_rom_pbps0 =
    BSP_CFG_ROM_REG_PBPS0;

  #endif

 #else                                 /* CM33 & CM85 parts */

  #if !BSP_TZ_NONSECURE_BUILD

BSP_DONT_REMOVE static const uint32_t BSP_PLACE_IN_SECTION(".option_setting_ofs0") g_bsp_rom_ofs0 =
    BSP_CFG_ROM_REG_OFS0;

   #if BSP_FEATURE_BSP_HAS_OFS2
BSP_DONT_REMOVE static const uint32_t BSP_PLACE_IN_SECTION(".option_setting_ofs2") g_bsp_rom_ofs2 =
    BSP_CFG_ROM_REG_OFS2;

   #endif
   #if BSP_FEATURE_FLASH_HP_SUPPORTS_DUAL_BANK
BSP_DONT_REMOVE static const uint32_t BSP_PLACE_IN_SECTION(".option_setting_dualsel") g_bsp_rom_dualsel =
    BSP_CFG_ROM_REG_DUALSEL;

   #endif
BSP_DONT_REMOVE static const uint32_t BSP_PLACE_IN_SECTION(".option_setting_sas") g_bsp_rom_sas =
    0xFFFFFFFF;

  #else

BSP_DONT_REMOVE static const uint32_t BSP_PLACE_IN_SECTION(".option_setting_ofs1") g_bsp_rom_ofs1 =
    BSP_ROM_REG_OFS1_SETTING;

   #if BSP_FEATURE_BSP_HAS_OFS3
BSP_DONT_REMOVE static const uint32_t BSP_PLACE_IN_SECTION(".option_setting_ofs3") g_bsp_rom_ofs3 =
    BSP_CFG_ROM_REG_OFS3;

   #endif
BSP_DONT_REMOVE static const uint32_t BSP_PLACE_IN_SECTION(".option_setting_banksel") g_bsp_rom_banksel =
    0xFFFFFFFF;
BSP_DONT_REMOVE static const uint32_t BSP_PLACE_IN_SECTION(".option_setting_bps0") g_bsp_rom_bps0 =
    BSP_CFG_ROM_REG_BPS0;
BSP_DONT_REMOVE static const uint32_t BSP_PLACE_IN_SECTION(".option_setting_bps1") g_bsp_rom_bps1 =
    BSP_CFG_ROM_REG_BPS1;
BSP_DONT_REMOVE static const uint32_t BSP_PLACE_IN_SECTION(".option_setting_bps2") g_bsp_rom_bps2 =
    BSP_CFG_ROM_REG_BPS2;
BSP_DONT_REMOVE static const uint32_t BSP_PLACE_IN_SECTION(".option_setting_bps3") g_bsp_rom_bps3 =
    BSP_CFG_ROM_REG_BPS3;
BSP_DONT_REMOVE static const uint32_t BSP_PLACE_IN_SECTION(".option_setting_pbps0") g_bsp_rom_pbps0 =
    BSP_CFG_ROM_REG_PBPS0;
BSP_DONT_REMOVE static const uint32_t BSP_PLACE_IN_SECTION(".option_setting_pbps1") g_bsp_rom_pbps1 =
    BSP_CFG_ROM_REG_PBPS1;
BSP_DONT_REMOVE static const uint32_t BSP_PLACE_IN_SECTION(".option_setting_pbps2") g_bsp_rom_pbps2 =
    BSP_CFG_ROM_REG_PBPS2;
BSP_DONT_REMOVE static const uint32_t BSP_PLACE_IN_SECTION(".option_setting_pbps3") g_bsp_rom_pbps3 =
    BSP_CFG_ROM_REG_PBPS3;

  #endif

  #if !BSP_TZ_NONSECURE_BUILD

BSP_DONT_REMOVE static const uint32_t BSP_PLACE_IN_SECTION(".option_setting_ofs1_sec") g_bsp_rom_ofs1_sec =
    BSP_ROM_REG_OFS1_SETTING;

   #if BSP_FEATURE_BSP_HAS_OFS3
BSP_DONT_REMOVE static const uint32_t BSP_PLACE_IN_SECTION(".option_setting_ofs3_sec") g_bsp_rom_ofs3_sec =
    BSP_CFG_ROM_REG_OFS3;

   #endif
BSP_DONT_REMOVE static const uint32_t BSP_PLACE_IN_SECTION(".option_setting_banksel_sec") g_bsp_rom_banksel_sec =
    0xFFFFFFFF;
BSP_DONT_REMOVE static const uint32_t BSP_PLACE_IN_SECTION(".option_setting_bps_sec0") g_bsp_rom_bps_sec0 =
    BSP_CFG_ROM_REG_BPS0;
BSP_DONT_REMOVE static const uint32_t BSP_PLACE_IN_SECTION(".option_setting_bps_sec1") g_bsp_rom_bps_sec1 =
    BSP_CFG_ROM_REG_BPS1;
BSP_DONT_REMOVE static const uint32_t BSP_PLACE_IN_SECTION(".option_setting_bps_sec2") g_bsp_rom_bps_sec2 =
    BSP_CFG_ROM_REG_BPS2;
BSP_DONT_REMOVE static const uint32_t BSP_PLACE_IN_SECTION(".option_setting_bps_sec3") g_bsp_rom_bps_sec3 =
    BSP_CFG_ROM_REG_BPS3;
BSP_DONT_REMOVE static const uint32_t BSP_PLACE_IN_SECTION(".option_setting_pbps_sec0") g_bsp_rom_pbps_sec0 =
    BSP_CFG_ROM_REG_PBPS0;
BSP_DONT_REMOVE static const uint32_t BSP_PLACE_IN_SECTION(".option_setting_pbps_sec1") g_bsp_rom_pbps_sec1 =
    BSP_CFG_ROM_REG_PBPS1;
BSP_DONT_REMOVE static const uint32_t BSP_PLACE_IN_SECTION(".option_setting_pbps_sec2") g_bsp_rom_pbps_sec2 =
    BSP_CFG_ROM_REG_PBPS2;
BSP_DONT_REMOVE static const uint32_t BSP_PLACE_IN_SECTION(".option_setting_pbps_sec3") g_bsp_rom_pbps_sec3 =
    BSP_CFG_ROM_REG_PBPS3;
BSP_DONT_REMOVE static const uint32_t BSP_PLACE_IN_SECTION(".option_setting_ofs1_sel") g_bsp_rom_ofs1_sel =
    BSP_CFG_ROM_REG_OFS1_SEL;

   #if BSP_FEATURE_BSP_HAS_OFS3
BSP_DONT_REMOVE static const uint32_t BSP_PLACE_IN_SECTION(".option_setting_ofs3_sel") g_bsp_rom_ofs3_sel =
    BSP_CFG_ROM_REG_OFS3_SEL;

   #endif
   #if BSP_FEATURE_FLASH_HP_SUPPORTS_DUAL_BANK
BSP_DONT_REMOVE static const uint32_t BSP_PLACE_IN_SECTION(".option_setting_banksel_sel") g_bsp_rom_banksel_sel =
    BSP_CFG_ROM_REG_BANKSEL_SEL;

   #endif
BSP_DONT_REMOVE static const uint32_t BSP_PLACE_IN_SECTION(".option_setting_bps_sel0") g_bsp_rom_bps_sel0 =
    BSP_CFG_ROM_REG_BPS_SEL0;
BSP_DONT_REMOVE static const uint32_t BSP_PLACE_IN_SECTION(".option_setting_bps_sel1") g_bsp_rom_bps_sel1 =
    BSP_CFG_ROM_REG_BPS_SEL1;
BSP_DONT_REMOVE static const uint32_t BSP_PLACE_IN_SECTION(".option_setting_bps_sel2") g_bsp_rom_bps_sel2 =
    BSP_CFG_ROM_REG_BPS_SEL2;
BSP_DONT_REMOVE static const uint32_t BSP_PLACE_IN_SECTION(".option_setting_bps_sel3") g_bsp_rom_bps_sel3 =
    BSP_CFG_ROM_REG_BPS_SEL3;

  #endif

  #if 85U == __CORTEX_M && !BSP_TZ_NONSECURE_BUILD
BSP_DONT_REMOVE static const uint32_t BSP_PLACE_IN_SECTION(".option_setting_data_flash_fsblctrl0") g_bsp_rom_fsblctrl0 =
    BSP_CFG_ROM_REG_FSBLCTRL0;

BSP_DONT_REMOVE static const uint32_t BSP_PLACE_IN_SECTION(".option_setting_data_flash_fsblctrl1") g_bsp_rom_fsblctrl1 =
    BSP_CFG_ROM_REG_FSBLCTRL1;

BSP_DONT_REMOVE static const uint32_t BSP_PLACE_IN_SECTION(".option_setting_data_flash_fsblctrl2") g_bsp_rom_fsblctrl2 =
    BSP_CFG_ROM_REG_FSBLCTRL2;

BSP_DONT_REMOVE static const uint32_t BSP_PLACE_IN_SECTION(".option_setting_data_flash_sacc0") g_bsp_rom_sacc0 =
    BSP_CFG_ROM_REG_SACC0;

BSP_DONT_REMOVE static const uint32_t BSP_PLACE_IN_SECTION(".option_setting_data_flash_sacc1") g_bsp_rom_sacc1 =
    BSP_CFG_ROM_REG_SACC1;

BSP_DONT_REMOVE static const uint32_t BSP_PLACE_IN_SECTION(".option_setting_data_flash_samr") g_bsp_rom_samr =
    BSP_CFG_ROM_REG_SAMR;

  #endif

 #endif

#endif

/** @} (end addtogroup BSP_MCU) */
