/**
 *******************************************************************************
 * @file  ev_hc32f448_lqfp80_is61lv6416.c
 * @brief This file provides configure functions for is61lv6416 of the board
 *        EV_HC32F448_LQFP80.
 @verbatim
   Change Logs:
   Date             Author          Notes
   2023-05-31       CDT             First version
   2023-12-15       CDT             Modify the timing: EXCLK 100MHz -> 40MHz
 @endverbatim
 *******************************************************************************
 * Copyright (C) 2022-2023, Xiaohua Semiconductor Co., Ltd. All rights reserved.
 *
 * This software component is licensed by XHSC under BSD 3-Clause license
 * (the "License"); You may not use this file except in compliance with the
 * License. You may obtain a copy of the License at:
 *                    opensource.org/licenses/BSD-3-Clause
 *
 *******************************************************************************
 */

/*******************************************************************************
 * Include files
 ******************************************************************************/
#include <string.h>

#include "hc32_ll_fcg.h"
#include "ev_hc32f448_lqfp80_is61lv6416.h"

/**
 * @addtogroup BSP
 * @{
 */

/**
 * @addtogroup EV_HC32F448_LQFP80
 * @{
 */

/**
 * @defgroup EV_HC32F448_LQFP80_IS61LV6416 EV_HC32F448_LQFP80 IS61LV6416
 * @{
 */

#if ((DDL_ON == BSP_IS61LV6416_ENABLE) && (BSP_EV_HC32F448_LQFP80 == BSP_EV_HC32F4XX))

/*******************************************************************************
 * Local type definitions ('typedef')
 ******************************************************************************/

/*******************************************************************************
 * Local pre-processor symbols/macros ('#define')
 ******************************************************************************/
/**
 * @defgroup EV_HC32F448_LQFP80_IS61LV6416_Local_Macros  EV_HC32F448_LQFP80 IS61LV6416 Local Macros
 * @{
 */

/**
 * @defgroup SMC_Max_Timeout SMC Max Timeout
 * @{
 */
#define SMC_MAX_TIMEOUT                 (0x100000UL)
/**
 * @}
 */

/**
 * @}
 */

/*******************************************************************************
 * Global variable definitions (declared in header file with 'extern')
 ******************************************************************************/

/*******************************************************************************
 * Local function prototypes ('static')
 ******************************************************************************/

/*******************************************************************************
 * Local variable definitions ('static')
 ******************************************************************************/
/**
 * @addtogroup EV_HC32F448_LQFP80_IS61LV6416_Local_Functions
 * @{
 */
static void BSP_SMC_PortInit(void);
/**
 * @}
 */

/*******************************************************************************
 * Function implementation - global ('extern') and local ('static')
 ******************************************************************************/
/**
 * @defgroup EV_HC32F448_LQFP80_IS61LV6416_Global_Functions EV_HC32F448_LQFP80 IS61LV6416 Global Functions
 * @{
 */

/**
 * @brief  Initialize SMC for IS61LV6416.
 * @param  None
 * @retval int32_t:
 *           - LL_OK:                   Initialize successfully.
 *           - LL_ERR:                  Initialize unsuccessfully.
 */
int32_t BSP_IS61LV6416_Init(void)
{
    __IO uint32_t u32To = 0UL;
    int32_t i32Ret = LL_OK;
    stc_exmc_smc_init_t stcSmcInit;
    stc_exmc_smc_chip_config_t stcChipConfig;
    stc_exmc_smc_timing_config_t stcTimingConfig;
    en_flag_status_t enChipStatus = RESET;
    en_flag_status_t enTimingStatus = RESET;

    /* Initialize SMC port. */
    BSP_SMC_PortInit();

    /* Enable SMC clock */
    FCG_Fcg3PeriphClockCmd(FCG3_PERIPH_SMC, ENABLE);

    /* Enable SMC. */
    EXMC_SMC_Cmd(ENABLE);

    EXMC_SMC_ExitLowPower();

    while (EXMC_SMC_READY != EXMC_SMC_GetStatus()) {
        if (u32To > SMC_MAX_TIMEOUT) {
            i32Ret = LL_ERR;
            break;
        }
        u32To++;
    }

    if (LL_OK == i32Ret) {
        /* Configure SMC width && CS &chip & timing. */
        (void)EXMC_SMC_StructInit(&stcSmcInit);
        stcSmcInit.stcChipConfig.u32ReadMode = EXMC_SMC_READ_ASYNC;
        stcSmcInit.stcChipConfig.u32WriteMode = EXMC_SMC_WRITE_ASYNC;
        stcSmcInit.stcChipConfig.u32MemoryWidth = EXMC_SMC_MEMORY_WIDTH_16BIT;
        stcSmcInit.stcChipConfig.u32BAA = EXMC_SMC_BAA_PORT_DISABLE;
        stcSmcInit.stcChipConfig.u32ADV = EXMC_SMC_ADV_PORT_ENABLE;
        stcSmcInit.stcChipConfig.u32BLS = EXMC_SMC_BLS_SYNC_CS;
        stcSmcInit.stcChipConfig.u32AddrMatch = BSP_IS61LV6416_MATCH_ADDR;
        stcSmcInit.stcChipConfig.u32AddrMask = BSP_IS61LV6416_MASK_ADDR;

        /* EXCLK bus frequency@40MHz: 3.3V */
        stcSmcInit.stcTimingConfig.u8RC = 5U;
        stcSmcInit.stcTimingConfig.u8WC = 4U;
        stcSmcInit.stcTimingConfig.u8CEOE = 3U;
        stcSmcInit.stcTimingConfig.u8WP = 1U;
        stcSmcInit.stcTimingConfig.u8TR = 1U;
        stcSmcInit.stcTimingConfig.u8ADV = 1U;
        (void)EXMC_SMC_Init(BSP_IS61LV6416_CHIP, &stcSmcInit);

        /* Set DATA/ADD Pin mux */
        EXMC_SMC_PinMuxCmd(ENABLE);

        /* Set command: updateregs */
        EXMC_SMC_SetCommand(BSP_IS61LV6416_CHIP, EXMC_SMC_CMD_UPDATEREGS, 0UL, 0UL);

        /* Check timing status */
        u32To = 0UL;
        while ((enChipStatus != SET) || (enTimingStatus != SET)) {
            (void)EXMC_SMC_GetTimingConfig(BSP_IS61LV6416_CHIP, &stcTimingConfig);
            if (0 == memcmp(&stcTimingConfig, &stcSmcInit.stcTimingConfig, sizeof(stcTimingConfig))) {
                enTimingStatus = SET;
            }

            (void)EXMC_SMC_GetChipConfig(BSP_IS61LV6416_CHIP, &stcChipConfig);
            if (0 == memcmp(&stcChipConfig, &stcSmcInit.stcChipConfig, sizeof(stcChipConfig))) {
                enChipStatus = SET;
            }

            if (u32To > SMC_MAX_TIMEOUT) {
                i32Ret = LL_ERR;
                break;
            }
            u32To++;
        }
    }

    return i32Ret;
}

/**
 * @brief  Get memory information.
 * @param  [out] pu32MemoryStartAddr    Pointer to memory start address
 * @param  [out] pu32MemoryByteSize     Pointer to memory size(unit: Byte)
 * @retval None
 */
void BSP_IS61LV6416_GetMemInfo(uint32_t *pu32MemoryStartAddr, uint32_t *pu32MemoryByteSize)
{
    if (NULL != pu32MemoryStartAddr) {
        *pu32MemoryStartAddr = BSP_IS61LV6416_START_ADDR;
    }

    if (NULL != pu32MemoryByteSize) {
        *pu32MemoryByteSize = BSP_IS61LV6416_SIZE;
    }
}

/**
 * @}
 */

/**
 * @defgroup EV_HC32F448_LQFP80_IS61LV6416_Local_Functions EV_HC32F448_LQFP80 IS61LV6416 Local Functions
 * @{
 */

/**
 * @brief  Initialize SMC port.
 * @param  None
 * @retval None
 */
static void BSP_SMC_PortInit(void)
{
    stc_gpio_init_t stcGpioInit;

    /************************* Set pin drive capacity *************************/
    (void)GPIO_StructInit(&stcGpioInit);
    stcGpioInit.u16PinDrv = PIN_HIGH_DRV;

    /* SMC_ADV */
    stcGpioInit.u16Invert = PIN_INVT_ON;
    (void)GPIO_Init(BSP_IS61LV6416_ADV_PORT, BSP_IS61LV6416_ADV_PIN, &stcGpioInit);

    /* Output invert off */
    stcGpioInit.u16Invert = PIN_INVT_OFF;

    /* SMC_CS */
    (void)GPIO_Init(BSP_IS61LV6416_CS_PORT, BSP_IS61LV6416_CS_PIN, &stcGpioInit);

    /* SMC_WE */
    (void)GPIO_Init(BSP_IS61LV6416_WE_PORT, BSP_IS61LV6416_WE_PIN, &stcGpioInit);

    /* SMC_BLS[0:1] */
    (void)GPIO_Init(BSP_IS61LV6416_BLS0_PORT, BSP_IS61LV6416_BLS0_PIN, &stcGpioInit);
    (void)GPIO_Init(BSP_IS61LV6416_BLS1_PORT, BSP_IS61LV6416_BLS1_PIN, &stcGpioInit);

    /* SMC_OE */
    (void)GPIO_Init(BSP_IS61LV6416_OE_PORT, BSP_IS61LV6416_OE_PIN, &stcGpioInit);

    /* SMC_DATA[0:15] */
    (void)GPIO_Init(BSP_IS61LV6416_DATA0_PORT, BSP_IS61LV6416_DATA0_PIN, &stcGpioInit);
    (void)GPIO_Init(BSP_IS61LV6416_DATA1_PORT, BSP_IS61LV6416_DATA1_PIN, &stcGpioInit);
    (void)GPIO_Init(BSP_IS61LV6416_DATA2_PORT, BSP_IS61LV6416_DATA2_PIN, &stcGpioInit);
    (void)GPIO_Init(BSP_IS61LV6416_DATA3_PORT, BSP_IS61LV6416_DATA3_PIN, &stcGpioInit);
    (void)GPIO_Init(BSP_IS61LV6416_DATA4_PORT, BSP_IS61LV6416_DATA4_PIN, &stcGpioInit);
    (void)GPIO_Init(BSP_IS61LV6416_DATA5_PORT, BSP_IS61LV6416_DATA5_PIN, &stcGpioInit);
    (void)GPIO_Init(BSP_IS61LV6416_DATA6_PORT, BSP_IS61LV6416_DATA6_PIN, &stcGpioInit);
    (void)GPIO_Init(BSP_IS61LV6416_DATA7_PORT, BSP_IS61LV6416_DATA7_PIN, &stcGpioInit);
    (void)GPIO_Init(BSP_IS61LV6416_DATA8_PORT, BSP_IS61LV6416_DATA8_PIN, &stcGpioInit);
    (void)GPIO_Init(BSP_IS61LV6416_DATA9_PORT, BSP_IS61LV6416_DATA9_PIN, &stcGpioInit);
    (void)GPIO_Init(BSP_IS61LV6416_DATA10_PORT, BSP_IS61LV6416_DATA10_PIN, &stcGpioInit);
    (void)GPIO_Init(BSP_IS61LV6416_DATA11_PORT, BSP_IS61LV6416_DATA11_PIN, &stcGpioInit);
    (void)GPIO_Init(BSP_IS61LV6416_DATA12_PORT, BSP_IS61LV6416_DATA12_PIN, &stcGpioInit);
    (void)GPIO_Init(BSP_IS61LV6416_DATA13_PORT, BSP_IS61LV6416_DATA13_PIN, &stcGpioInit);
    (void)GPIO_Init(BSP_IS61LV6416_DATA14_PORT, BSP_IS61LV6416_DATA14_PIN, &stcGpioInit);
    (void)GPIO_Init(BSP_IS61LV6416_DATA15_PORT, BSP_IS61LV6416_DATA15_PIN, &stcGpioInit);

    /************************** Set EXMC pin function *************************/
    /* SMC_CS */
    GPIO_SetFunc(BSP_IS61LV6416_CS_PORT, BSP_IS61LV6416_CS_PIN, GPIO_FUNC_12);

    /* SMC_WE */
    GPIO_SetFunc(BSP_IS61LV6416_WE_PORT, BSP_IS61LV6416_WE_PIN, GPIO_FUNC_12);

    /* SMC_BLS[0:1] */
    GPIO_SetFunc(BSP_IS61LV6416_BLS0_PORT, BSP_IS61LV6416_BLS0_PIN, GPIO_FUNC_12);
    GPIO_SetFunc(BSP_IS61LV6416_BLS1_PORT, BSP_IS61LV6416_BLS1_PIN, GPIO_FUNC_12);

    /* SMC_OE */
    GPIO_SetFunc(BSP_IS61LV6416_OE_PORT, BSP_IS61LV6416_OE_PIN, GPIO_FUNC_12);

    /* SMC_ADV */
    GPIO_SetFunc(BSP_IS61LV6416_ADV_PORT, BSP_IS61LV6416_ADV_PIN, GPIO_FUNC_12);

    /* SMC_DATA[0:15] */
    GPIO_SetFunc(BSP_IS61LV6416_DATA0_PORT, BSP_IS61LV6416_DATA0_PIN, GPIO_FUNC_12);
    GPIO_SetFunc(BSP_IS61LV6416_DATA1_PORT, BSP_IS61LV6416_DATA1_PIN, GPIO_FUNC_12);
    GPIO_SetFunc(BSP_IS61LV6416_DATA2_PORT, BSP_IS61LV6416_DATA2_PIN, GPIO_FUNC_12);
    GPIO_SetFunc(BSP_IS61LV6416_DATA3_PORT, BSP_IS61LV6416_DATA3_PIN, GPIO_FUNC_12);
    GPIO_SetFunc(BSP_IS61LV6416_DATA4_PORT, BSP_IS61LV6416_DATA4_PIN, GPIO_FUNC_12);
    GPIO_SetFunc(BSP_IS61LV6416_DATA5_PORT, BSP_IS61LV6416_DATA5_PIN, GPIO_FUNC_12);
    GPIO_SetFunc(BSP_IS61LV6416_DATA6_PORT, BSP_IS61LV6416_DATA6_PIN, GPIO_FUNC_12);
    GPIO_SetFunc(BSP_IS61LV6416_DATA7_PORT, BSP_IS61LV6416_DATA7_PIN, GPIO_FUNC_12);
    GPIO_SetFunc(BSP_IS61LV6416_DATA8_PORT, BSP_IS61LV6416_DATA8_PIN, GPIO_FUNC_12);
    GPIO_SetFunc(BSP_IS61LV6416_DATA9_PORT, BSP_IS61LV6416_DATA9_PIN, GPIO_FUNC_12);
    GPIO_SetFunc(BSP_IS61LV6416_DATA10_PORT, BSP_IS61LV6416_DATA10_PIN, GPIO_FUNC_12);
    GPIO_SetFunc(BSP_IS61LV6416_DATA11_PORT, BSP_IS61LV6416_DATA11_PIN, GPIO_FUNC_12);
    GPIO_SetFunc(BSP_IS61LV6416_DATA12_PORT, BSP_IS61LV6416_DATA12_PIN, GPIO_FUNC_12);
    GPIO_SetFunc(BSP_IS61LV6416_DATA13_PORT, BSP_IS61LV6416_DATA13_PIN, GPIO_FUNC_12);
    GPIO_SetFunc(BSP_IS61LV6416_DATA14_PORT, BSP_IS61LV6416_DATA14_PIN, GPIO_FUNC_12);
    GPIO_SetFunc(BSP_IS61LV6416_DATA15_PORT, BSP_IS61LV6416_DATA15_PIN, GPIO_FUNC_12);
}

/**
 * @}
 */

#endif /* BSP_IS61LV6416_ENABLE && BSP_EV_HC32F448_LQFP80 */

/**
 * @}
 */

/**
 * @}
 */

/**
 * @}
 */

/******************************************************************************
 * EOF (not truncated)
 *****************************************************************************/
