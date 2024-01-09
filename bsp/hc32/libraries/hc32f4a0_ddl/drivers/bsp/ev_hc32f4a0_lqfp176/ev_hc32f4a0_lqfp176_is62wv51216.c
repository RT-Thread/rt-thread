/**
 *******************************************************************************
 * @file  ev_hc32f4a0_lqfp176_is62wv51216.c
 * @brief This file provides configure functions for is62wv51216 of the board
 *        EV_HC32F4A0_LQFP176.
 @verbatim
   Change Logs:
   Date             Author          Notes
   2022-03-31       CDT             First version
   2022-10-31       CDT             Add timing comments
   2023-09-30       CDT             Modify SMC timing parameter: EXCLK 60MHz -> 30MHz
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
#include "ev_hc32f4a0_lqfp176_is62wv51216.h"

/**
 * @addtogroup BSP
 * @{
 */

/**
 * @addtogroup EV_HC32F4A0_LQFP176
 * @{
 */

/**
 * @defgroup EV_HC32F4A0_LQFP176_IS62WV51216 EV_HC32F4A0_LQFP176 IS62WV51216
 * @{
 */

#if ((DDL_ON == BSP_IS62WV51216_ENABLE) && (BSP_EV_HC32F4A0_LQFP176 == BSP_EV_HC32F4XX))

/*******************************************************************************
 * Local type definitions ('typedef')
 ******************************************************************************/

/*******************************************************************************
 * Local pre-processor symbols/macros ('#define')
 ******************************************************************************/
/**
 * @defgroup EV_HC32F4A0_LQFP176_IS62WV51216_Local_Macros  EV_HC32F4A0_LQFP176 IS62WV51216 Local Macros
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
 * @addtogroup EV_HC32F4A0_LQFP176_IS62WV51216_Local_Functions
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
 * @defgroup EV_HC32F4A0_LQFP176_IS62WV51216_Global_Functions EV_HC32F4A0_LQFP176 IS62WV51216 Global Functions
 * @{
 */

/**
 * @brief  Initialize SMC for IS62WV51216.
 * @param  None
 * @retval int32_t:
 *           - LL_OK:                   Initialize successfully.
 *           - LL_ERR:                  Initialize unsuccessfully.
 */
int32_t BSP_IS62WV51216_Init(void)
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
        stcSmcInit.stcChipConfig.u32ReadBurstLen = EXMC_SMC_READ_BURST_1BEAT;
        stcSmcInit.stcChipConfig.u32WriteMode = EXMC_SMC_WRITE_ASYNC;
        stcSmcInit.stcChipConfig.u32WriteBurstLen = EXMC_SMC_WRITE_BURST_1BEAT;
        stcSmcInit.stcChipConfig.u32MemoryWidth = EXMC_SMC_MEMORY_WIDTH_16BIT;
        stcSmcInit.stcChipConfig.u32BAA = EXMC_SMC_BAA_PORT_DISABLE;
        stcSmcInit.stcChipConfig.u32ADV = EXMC_SMC_ADV_PORT_DISABLE;
        stcSmcInit.stcChipConfig.u32BLS = EXMC_SMC_BLS_SYNC_CS;
        stcSmcInit.stcChipConfig.u32AddrMatch = BSP_IS62WV51216_MATCH_ADDR;
        stcSmcInit.stcChipConfig.u32AddrMask = BSP_IS62WV51216_MASK_ADDR;

        /* EXCLK bus frequency@30MHz: 3.3V */
        stcSmcInit.stcTimingConfig.u8RC = 4U;   /* tRC: min=55ns */
        stcSmcInit.stcTimingConfig.u8WC = 4U;   /* tWC: min=55ns */
        stcSmcInit.stcTimingConfig.u8CEOE = 1U;
        stcSmcInit.stcTimingConfig.u8WP = 2U;   /* tWP: min=40ns */
        stcSmcInit.stcTimingConfig.u8PC = 1U;
        stcSmcInit.stcTimingConfig.u8TR = 1U;
        (void)EXMC_SMC_Init(BSP_IS62WV51216_CHIP, &stcSmcInit);

        /* Set command: updateregs */
        EXMC_SMC_SetCommand(BSP_IS62WV51216_CHIP, EXMC_SMC_CMD_UPDATEREGS, 0UL, 0UL);

        /* Check timing status */
        u32To = 0UL;
        while ((enChipStatus != SET) || (enTimingStatus != SET)) {
            (void)EXMC_SMC_GetTimingConfig(BSP_IS62WV51216_CHIP, &stcTimingConfig);
            if (0 == memcmp(&stcTimingConfig, &stcSmcInit.stcTimingConfig, sizeof(stcTimingConfig))) {
                enTimingStatus = SET;
            }

            (void)EXMC_SMC_GetChipConfig(BSP_IS62WV51216_CHIP, &stcChipConfig);
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
void BSP_IS62WV51216_GetMemInfo(uint32_t *pu32MemoryStartAddr, uint32_t *pu32MemoryByteSize)
{
    if (NULL != pu32MemoryStartAddr) {
        *pu32MemoryStartAddr = BSP_IS62WV51216_START_ADDR;
    }

    if (NULL != pu32MemoryByteSize) {
        *pu32MemoryByteSize = BSP_IS62WV51216_SIZE;
    }
}

/**
 * @}
 */

/**
 * @defgroup EV_HC32F4A0_LQFP176_IS62WV51216_Local_Functions EV_HC32F4A0_LQFP176 IS62WV51216 Local Functions
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

    /* SMC_CS */
    (void)GPIO_Init(BSP_IS62WV51216_CS_PORT, BSP_IS62WV51216_CS_PIN, &stcGpioInit);

    /* SMC_WE */
    (void)GPIO_Init(BSP_IS62WV51216_WE_PORT, BSP_IS62WV51216_WE_PIN, &stcGpioInit);

    /* SMC_BLS[0:1] */
    (void)GPIO_Init(BSP_IS62WV51216_BLS0_PORT, BSP_IS62WV51216_BLS0_PIN, &stcGpioInit);
    (void)GPIO_Init(BSP_IS62WV51216_BLS1_PORT, BSP_IS62WV51216_BLS1_PIN, &stcGpioInit);

    /* SMC_OE */
    (void)GPIO_Init(BSP_IS62WV51216_OE_PORT, BSP_IS62WV51216_OE_PIN, &stcGpioInit);

    /* SMC_DATA[0:15] */
    (void)GPIO_Init(BSP_IS62WV51216_DATA0_PORT, BSP_IS62WV51216_DATA0_PIN, &stcGpioInit);
    (void)GPIO_Init(BSP_IS62WV51216_DATA1_PORT, BSP_IS62WV51216_DATA1_PIN, &stcGpioInit);
    (void)GPIO_Init(BSP_IS62WV51216_DATA2_PORT, BSP_IS62WV51216_DATA2_PIN, &stcGpioInit);
    (void)GPIO_Init(BSP_IS62WV51216_DATA3_PORT, BSP_IS62WV51216_DATA3_PIN, &stcGpioInit);
    (void)GPIO_Init(BSP_IS62WV51216_DATA4_PORT, BSP_IS62WV51216_DATA4_PIN, &stcGpioInit);
    (void)GPIO_Init(BSP_IS62WV51216_DATA5_PORT, BSP_IS62WV51216_DATA5_PIN, &stcGpioInit);
    (void)GPIO_Init(BSP_IS62WV51216_DATA6_PORT, BSP_IS62WV51216_DATA6_PIN, &stcGpioInit);
    (void)GPIO_Init(BSP_IS62WV51216_DATA7_PORT, BSP_IS62WV51216_DATA7_PIN, &stcGpioInit);
    (void)GPIO_Init(BSP_IS62WV51216_DATA8_PORT, BSP_IS62WV51216_DATA8_PIN, &stcGpioInit);
    (void)GPIO_Init(BSP_IS62WV51216_DATA9_PORT, BSP_IS62WV51216_DATA9_PIN, &stcGpioInit);
    (void)GPIO_Init(BSP_IS62WV51216_DATA10_PORT, BSP_IS62WV51216_DATA10_PIN, &stcGpioInit);
    (void)GPIO_Init(BSP_IS62WV51216_DATA11_PORT, BSP_IS62WV51216_DATA11_PIN, &stcGpioInit);
    (void)GPIO_Init(BSP_IS62WV51216_DATA12_PORT, BSP_IS62WV51216_DATA12_PIN, &stcGpioInit);
    (void)GPIO_Init(BSP_IS62WV51216_DATA13_PORT, BSP_IS62WV51216_DATA13_PIN, &stcGpioInit);
    (void)GPIO_Init(BSP_IS62WV51216_DATA14_PORT, BSP_IS62WV51216_DATA14_PIN, &stcGpioInit);
    (void)GPIO_Init(BSP_IS62WV51216_DATA15_PORT, BSP_IS62WV51216_DATA15_PIN, &stcGpioInit);

    /* SMC_ADD[0:18]*/
    (void)GPIO_Init(BSP_IS62WV51216_ADD0_PORT, BSP_IS62WV51216_ADD0_PIN, &stcGpioInit);
    (void)GPIO_Init(BSP_IS62WV51216_ADD1_PORT, BSP_IS62WV51216_ADD1_PIN, &stcGpioInit);
    (void)GPIO_Init(BSP_IS62WV51216_ADD2_PORT, BSP_IS62WV51216_ADD2_PIN, &stcGpioInit);
    (void)GPIO_Init(BSP_IS62WV51216_ADD3_PORT, BSP_IS62WV51216_ADD3_PIN, &stcGpioInit);
    (void)GPIO_Init(BSP_IS62WV51216_ADD4_PORT, BSP_IS62WV51216_ADD4_PIN, &stcGpioInit);
    (void)GPIO_Init(BSP_IS62WV51216_ADD5_PORT, BSP_IS62WV51216_ADD5_PIN, &stcGpioInit);
    (void)GPIO_Init(BSP_IS62WV51216_ADD6_PORT, BSP_IS62WV51216_ADD6_PIN, &stcGpioInit);
    (void)GPIO_Init(BSP_IS62WV51216_ADD7_PORT, BSP_IS62WV51216_ADD7_PIN, &stcGpioInit);
    (void)GPIO_Init(BSP_IS62WV51216_ADD8_PORT, BSP_IS62WV51216_ADD8_PIN, &stcGpioInit);
    (void)GPIO_Init(BSP_IS62WV51216_ADD9_PORT, BSP_IS62WV51216_ADD9_PIN, &stcGpioInit);
    (void)GPIO_Init(BSP_IS62WV51216_ADD10_PORT, BSP_IS62WV51216_ADD10_PIN, &stcGpioInit);
    (void)GPIO_Init(BSP_IS62WV51216_ADD11_PORT, BSP_IS62WV51216_ADD11_PIN, &stcGpioInit);
    (void)GPIO_Init(BSP_IS62WV51216_ADD12_PORT, BSP_IS62WV51216_ADD12_PIN, &stcGpioInit);
    (void)GPIO_Init(BSP_IS62WV51216_ADD13_PORT, BSP_IS62WV51216_ADD13_PIN, &stcGpioInit);
    (void)GPIO_Init(BSP_IS62WV51216_ADD14_PORT, BSP_IS62WV51216_ADD14_PIN, &stcGpioInit);
    (void)GPIO_Init(BSP_IS62WV51216_ADD15_PORT, BSP_IS62WV51216_ADD15_PIN, &stcGpioInit);
    (void)GPIO_Init(BSP_IS62WV51216_ADD16_PORT, BSP_IS62WV51216_ADD16_PIN, &stcGpioInit);
    (void)GPIO_Init(BSP_IS62WV51216_ADD17_PORT, BSP_IS62WV51216_ADD17_PIN, &stcGpioInit);
    (void)GPIO_Init(BSP_IS62WV51216_ADD18_PORT, BSP_IS62WV51216_ADD18_PIN, &stcGpioInit);

    /************************** Set EXMC pin function *************************/
    /* SMC_CS */
    GPIO_SetFunc(BSP_IS62WV51216_CS_PORT, BSP_IS62WV51216_CS_PIN, GPIO_FUNC_12);

    /* SMC_WE */
    GPIO_SetFunc(BSP_IS62WV51216_WE_PORT, BSP_IS62WV51216_WE_PIN, GPIO_FUNC_12);

    /* SMC_BLS[0:1] */
    GPIO_SetFunc(BSP_IS62WV51216_BLS0_PORT, BSP_IS62WV51216_BLS0_PIN, GPIO_FUNC_12);
    GPIO_SetFunc(BSP_IS62WV51216_BLS1_PORT, BSP_IS62WV51216_BLS1_PIN, GPIO_FUNC_12);

    /* SMC_OE */
    GPIO_SetFunc(BSP_IS62WV51216_OE_PORT, BSP_IS62WV51216_OE_PIN, GPIO_FUNC_12);

    /* SMC_DATA[0:15] */
    GPIO_SetFunc(BSP_IS62WV51216_DATA0_PORT, BSP_IS62WV51216_DATA0_PIN, GPIO_FUNC_12);
    GPIO_SetFunc(BSP_IS62WV51216_DATA1_PORT, BSP_IS62WV51216_DATA1_PIN, GPIO_FUNC_12);
    GPIO_SetFunc(BSP_IS62WV51216_DATA2_PORT, BSP_IS62WV51216_DATA2_PIN, GPIO_FUNC_12);
    GPIO_SetFunc(BSP_IS62WV51216_DATA3_PORT, BSP_IS62WV51216_DATA3_PIN, GPIO_FUNC_12);
    GPIO_SetFunc(BSP_IS62WV51216_DATA4_PORT, BSP_IS62WV51216_DATA4_PIN, GPIO_FUNC_12);
    GPIO_SetFunc(BSP_IS62WV51216_DATA5_PORT, BSP_IS62WV51216_DATA5_PIN, GPIO_FUNC_12);
    GPIO_SetFunc(BSP_IS62WV51216_DATA6_PORT, BSP_IS62WV51216_DATA6_PIN, GPIO_FUNC_12);
    GPIO_SetFunc(BSP_IS62WV51216_DATA7_PORT, BSP_IS62WV51216_DATA7_PIN, GPIO_FUNC_12);
    GPIO_SetFunc(BSP_IS62WV51216_DATA8_PORT, BSP_IS62WV51216_DATA8_PIN, GPIO_FUNC_12);
    GPIO_SetFunc(BSP_IS62WV51216_DATA9_PORT, BSP_IS62WV51216_DATA9_PIN, GPIO_FUNC_12);
    GPIO_SetFunc(BSP_IS62WV51216_DATA10_PORT, BSP_IS62WV51216_DATA10_PIN, GPIO_FUNC_12);
    GPIO_SetFunc(BSP_IS62WV51216_DATA11_PORT, BSP_IS62WV51216_DATA11_PIN, GPIO_FUNC_12);
    GPIO_SetFunc(BSP_IS62WV51216_DATA12_PORT, BSP_IS62WV51216_DATA12_PIN, GPIO_FUNC_12);
    GPIO_SetFunc(BSP_IS62WV51216_DATA13_PORT, BSP_IS62WV51216_DATA13_PIN, GPIO_FUNC_12);
    GPIO_SetFunc(BSP_IS62WV51216_DATA14_PORT, BSP_IS62WV51216_DATA14_PIN, GPIO_FUNC_12);
    GPIO_SetFunc(BSP_IS62WV51216_DATA15_PORT, BSP_IS62WV51216_DATA15_PIN, GPIO_FUNC_12);

    /* SMC_ADD[0:18]*/
    GPIO_SetFunc(BSP_IS62WV51216_ADD0_PORT, BSP_IS62WV51216_ADD0_PIN, GPIO_FUNC_12);
    GPIO_SetFunc(BSP_IS62WV51216_ADD1_PORT, BSP_IS62WV51216_ADD1_PIN, GPIO_FUNC_12);
    GPIO_SetFunc(BSP_IS62WV51216_ADD2_PORT, BSP_IS62WV51216_ADD2_PIN, GPIO_FUNC_12);
    GPIO_SetFunc(BSP_IS62WV51216_ADD3_PORT, BSP_IS62WV51216_ADD3_PIN, GPIO_FUNC_12);
    GPIO_SetFunc(BSP_IS62WV51216_ADD4_PORT, BSP_IS62WV51216_ADD4_PIN, GPIO_FUNC_12);
    GPIO_SetFunc(BSP_IS62WV51216_ADD5_PORT, BSP_IS62WV51216_ADD5_PIN, GPIO_FUNC_12);
    GPIO_SetFunc(BSP_IS62WV51216_ADD6_PORT, BSP_IS62WV51216_ADD6_PIN, GPIO_FUNC_12);
    GPIO_SetFunc(BSP_IS62WV51216_ADD7_PORT, BSP_IS62WV51216_ADD7_PIN, GPIO_FUNC_12);
    GPIO_SetFunc(BSP_IS62WV51216_ADD8_PORT, BSP_IS62WV51216_ADD8_PIN, GPIO_FUNC_12);
    GPIO_SetFunc(BSP_IS62WV51216_ADD9_PORT, BSP_IS62WV51216_ADD9_PIN, GPIO_FUNC_12);
    GPIO_SetFunc(BSP_IS62WV51216_ADD10_PORT, BSP_IS62WV51216_ADD10_PIN, GPIO_FUNC_12);
    GPIO_SetFunc(BSP_IS62WV51216_ADD11_PORT, BSP_IS62WV51216_ADD11_PIN, GPIO_FUNC_12);
    GPIO_SetFunc(BSP_IS62WV51216_ADD12_PORT, BSP_IS62WV51216_ADD12_PIN, GPIO_FUNC_12);
    GPIO_SetFunc(BSP_IS62WV51216_ADD13_PORT, BSP_IS62WV51216_ADD13_PIN, GPIO_FUNC_12);
    GPIO_SetFunc(BSP_IS62WV51216_ADD14_PORT, BSP_IS62WV51216_ADD14_PIN, GPIO_FUNC_12);
    GPIO_SetFunc(BSP_IS62WV51216_ADD15_PORT, BSP_IS62WV51216_ADD15_PIN, GPIO_FUNC_12);
    GPIO_SetFunc(BSP_IS62WV51216_ADD16_PORT, BSP_IS62WV51216_ADD16_PIN, GPIO_FUNC_12);
    GPIO_SetFunc(BSP_IS62WV51216_ADD17_PORT, BSP_IS62WV51216_ADD17_PIN, GPIO_FUNC_12);
    GPIO_SetFunc(BSP_IS62WV51216_ADD18_PORT, BSP_IS62WV51216_ADD18_PIN, GPIO_FUNC_12);
}

/**
 * @}
 */

#endif /* BSP_IS62WV51216_ENABLE && BSP_EV_HC32F4A0_LQFP176 */

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
