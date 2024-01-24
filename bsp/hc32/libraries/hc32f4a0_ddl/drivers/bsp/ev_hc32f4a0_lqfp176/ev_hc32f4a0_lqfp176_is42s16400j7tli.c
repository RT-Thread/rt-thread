/**
 *******************************************************************************
 * @file  ev_hc32f4a0_lqfp176_is42s16400j7tli.c
 * @brief This file provides configure functions for is42s16400j7tli of the
 *        board EV_HC32F4A0_LQFP176.
 @verbatim
   Change Logs:
   Date             Author          Notes
   2022-03-31       CDT             First version
   2022-10-31       CDT             Add timing comments
   2023-09-30       CDT             Modify DMC timing for EXCLK frequency 60MHz -> 30MHz
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
#include "hc32_ll_fcg.h"
#include "ev_hc32f4a0_lqfp176_is42s16400j7tli.h"

/**
 * @addtogroup BSP
 * @{
 */

/**
 * @addtogroup EV_HC32F4A0_LQFP176
 * @{
 */

/**
 * @defgroup EV_HC32F4A0_LQFP176_IS42S16400J7TLI EV_HC32F4A0_LQFP176 IS42S16400J7TLI
 * @{
 */

#if ((BSP_IS42S16400J7TLI_ENABLE == DDL_ON) && (BSP_EV_HC32F4A0_LQFP176 == BSP_EV_HC32F4XX))

/*******************************************************************************
 * Local type definitions ('typedef')
 ******************************************************************************/

/*******************************************************************************
 * Local pre-processor symbols/macros ('#define')
 ******************************************************************************/
/**
 * @defgroup EV_HC32F4A0_LQFP176_IS42S16400J7TLI_Local_Macros EV_HC32F4A0_LQFP176 IS42S16400J7TLI Local Macros
 * @{
 */

/**
 * @defgroup DMC_Max_Timeout DMC Max Timeout
 * @{
 */
#define DMC_MAX_TIMEOUT                 (0x100000UL)
/**
 * @}
 */

/**
 * @defgroup IS42S16400J7TLI_Mode_Register_Field IS42S16400J7TLI Mode Register Field
 * @{
 */
/* IS42S16400J7TLI burst length definition */
#define IS42S16400J7TLI_MR_BURST_1BEAT                  (0UL)
#define IS42S16400J7TLI_MR_BURST_2BEAT                  (1UL)
#define IS42S16400J7TLI_MR_BURST_4BEAT                  (2UL)
#define IS42S16400J7TLI_MR_BURST_8BEAT                  (3UL)
#define IS42S16400J7TLI_MR_BURST_LEN_FULLPAGE           (7UL)

/* IS42S16400J7TLI burst type definition */
#define IS42S16400J7TLI_MR_BURST_TYPE_SEQUENTIAL        (0UL)
#define IS42S16400J7TLI_MR_BURST_TYPE_INTERLEAVED       (1UL << 3)

/* IS42S16400J7TLI CAS latency definition */
#define IS42S16400J7TLI_MR_CAS_LATENCY_2                (2UL << 4)
#define IS42S16400J7TLI_MR_CAS_LATENCY_3                (3UL << 4)

/* IS42S16400J7TLI write burst mode definition */
#define IS42S16400J7TLI_MR_WRITEBURST_PROGRAMMED        (0UL)
#define IS42S16400J7TLI_MR_WRITEBURST_SINGLE            (1UL << 9)

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
 * @addtogroup EV_HC32F4A0_LQFP176_IS42S16400J7TLI_Local_Functions
 * @{
 */
static void BSP_DMC_PortInit(void);
static void BSP_SDRAM_InitSequence(uint32_t u32Chip, uint32_t u32Bank, uint32_t u32MdRegValue);
/**
 * @}
 */

/*******************************************************************************
 * Function implementation - global ('extern') and local ('static')
 ******************************************************************************/
/**
 * @defgroup EV_HC32F4A0_LQFP176_IS42S16400J7TLI_Global_Functions EV_HC32F4A0_LQFP176 IS42S16400J7TLI Global Functions
 * @{
 */

/**
 * @brief  Initialize DMC for IS42S16400J7TLI.
 * @param  None
 * @retval int32_t:
 *           - LL_OK:                   Initialize successfully.
 *           - LL_ERR:                  Initialize unsuccessfully.
 */
int32_t BSP_IS42S16400J7TLI_Init(void)
{
    __IO uint32_t u32To = 0UL;
    uint32_t u32MdRegValue;
    int32_t i32Ret = LL_OK;
    stc_exmc_dmc_init_t stcDmcInit;
    stc_exmc_dmc_chip_config_t stcCsConfig;

    /* Initialization DMC port.*/
    BSP_DMC_PortInit();

    /* Enable DMC clock */
    FCG_Fcg3PeriphClockCmd(FCG3_PERIPH_DMC, ENABLE);

    /* Enable DMC. */
    EXMC_DMC_Cmd(ENABLE);

    /* Configure DMC width && refresh period & chip & timing. */
    (void)EXMC_DMC_StructInit(&stcDmcInit);
    stcDmcInit.u32RefreshPeriod = 450UL;
    stcDmcInit.u32ColumnBitsNumber = EXMC_DMC_COLUMN_BITS_NUM8;
    stcDmcInit.u32RowBitsNumber = EXMC_DMC_ROW_BITS_NUM12;
    stcDmcInit.u32MemBurst = EXMC_DMC_BURST_1BEAT;
    stcDmcInit.u32AutoRefreshChips = EXMC_DMC_AUTO_REFRESH_2CHIPS;

    /* EXCLK bus frequency@30MHz: 3.3V */
    stcDmcInit.stcTimingConfig.u8CASL = 2U;
    stcDmcInit.stcTimingConfig.u8DQSS = 0U;
    stcDmcInit.stcTimingConfig.u8MRD = 2U;      /* tMRD: 2CLK */
    stcDmcInit.stcTimingConfig.u8RAS = 2U;      /* tRAS: min=42ns */
    stcDmcInit.stcTimingConfig.u8RC = 2U;       /* tRC:  min=63ns */
    stcDmcInit.stcTimingConfig.u8RCD_B = 3U;    /* tRCD: min=15ns */
    stcDmcInit.stcTimingConfig.u8RCD_P = 0U;
    stcDmcInit.stcTimingConfig.u8RFC_B = 2U;    /* tRFC: min=63ns */
    stcDmcInit.stcTimingConfig.u8RFC_P = 0U;
    stcDmcInit.stcTimingConfig.u8RP_B = 1U;     /* tRP:  min=15ns */
    stcDmcInit.stcTimingConfig.u8RP_P = 0U;
    stcDmcInit.stcTimingConfig.u8RRD = 1U;      /* tRRD: min=14ns */
    stcDmcInit.stcTimingConfig.u8WR = 2U;       /* tWR:  2CLK */
    stcDmcInit.stcTimingConfig.u8WTR = 1U;
    stcDmcInit.stcTimingConfig.u8XP = 1U;
    stcDmcInit.stcTimingConfig.u8XSR = 3U;      /* tXSR: min=70ns */
    stcDmcInit.stcTimingConfig.u8ESR = 3U;
    (void)EXMC_DMC_Init(&stcDmcInit);

    /* Configure DMC address space. */
    stcCsConfig.u32AddrMask = BSP_IS42S16400J7TLI_ADDR_MASK;
    stcCsConfig.u32AddrMatch = BSP_IS42S16400J7TLI_ADDR_MATCH;
    stcCsConfig.u32AddrDecodeMode = EXMC_DMC_CS_DECODE_ROWBANKCOL;
    (void)EXMC_DMC_ChipConfig(BSP_IS42S16400J7TLI_CHIP, &stcCsConfig);

    /* SDRAM initialization sequence. */
    u32MdRegValue = (IS42S16400J7TLI_MR_BURST_TYPE_SEQUENTIAL | IS42S16400J7TLI_MR_WRITEBURST_PROGRAMMED);
    if (2U == stcDmcInit.stcTimingConfig.u8CASL) {
        u32MdRegValue |= IS42S16400J7TLI_MR_CAS_LATENCY_2;
    } else {
        u32MdRegValue |= IS42S16400J7TLI_MR_CAS_LATENCY_3;
    }

    if (EXMC_DMC_BURST_1BEAT == stcDmcInit.u32MemBurst) {
        u32MdRegValue |= IS42S16400J7TLI_MR_BURST_1BEAT;
    } else if (EXMC_DMC_BURST_2BEAT == stcDmcInit.u32MemBurst) {
        u32MdRegValue |= IS42S16400J7TLI_MR_BURST_2BEAT;
    } else if (EXMC_DMC_BURST_4BEAT == stcDmcInit.u32MemBurst) {
        u32MdRegValue |= IS42S16400J7TLI_MR_BURST_4BEAT;
    } else {
        u32MdRegValue |= IS42S16400J7TLI_MR_BURST_8BEAT;
    }

    BSP_SDRAM_InitSequence(BSP_IS42S16400J7TLI_CHIP, BSP_IS42S16400J7TLI_BANK, u32MdRegValue);

    /* Switch state from configure to ready */
    EXMC_DMC_SetState(EXMC_DMC_CTRL_STATE_GO);
    EXMC_DMC_SetState(EXMC_DMC_CTRL_STATE_WAKEUP);
    EXMC_DMC_SetState(EXMC_DMC_CTRL_STATE_GO);

    /* Check status */
    while (EXMC_DMC_CURR_STATUS_RDY != EXMC_DMC_GetStatus()) {
        if (u32To > DMC_MAX_TIMEOUT) {
            i32Ret = LL_ERR;
            break;
        }
        u32To++;
    }

    return i32Ret;
}

/**
 * @brief  Get memory information.
 * @param  [out] pu32MemoryStartAddr    The pointer for memory start address
 * @param  [out] pu32MemoryByteSize     The pointer for memory size(unit: Byte)
 * @retval None
 */
void BSP_IS42S16400J7TLI_GetMemInfo(uint32_t *pu32MemoryStartAddr, uint32_t *pu32MemoryByteSize)
{
    if (NULL != pu32MemoryStartAddr) {
        *pu32MemoryStartAddr = BSP_IS42S16400J7TLI_START_ADDR;
    }

    if (NULL != pu32MemoryByteSize) {
        *pu32MemoryByteSize = BSP_IS42S16400J7TLI_SIZE;
    }
}

/**
 * @}
 */

/**
 * @defgroup EV_HC32F4A0_LQFP176_IS42S16400J7TLI_Local_Functions EV_HC32F4A0_LQFP176 IS42S16400J7TLI Local Functions
 * @{
 */

/**
 * @brief  Initialize DMC port.
 * @param  None
 * @retval None
 */
static void BSP_DMC_PortInit(void)
{
    stc_gpio_init_t stcGpioInit;

    /************************* Set pin drive capacity *************************/
    (void)GPIO_StructInit(&stcGpioInit);
    stcGpioInit.u16PinDrv = PIN_HIGH_DRV;

    /* DMC_CKE */
    (void)GPIO_Init(BSP_IS42S16400J7TLI_CKE_PORT, BSP_IS42S16400J7TLI_CKE_PIN, &stcGpioInit);

    /* DMC_CLK */
    (void)GPIO_Init(BSP_IS42S16400J7TLI_CLK_PORT, BSP_IS42S16400J7TLI_CLK_PIN, &stcGpioInit);

    /* DMC_LDQM && DMC_UDQM */
    (void)GPIO_Init(BSP_IS42S16400J7TLI_DQM0_PORT, BSP_IS42S16400J7TLI_DQM0_PIN, &stcGpioInit);
    (void)GPIO_Init(BSP_IS42S16400J7TLI_DQM1_PORT, BSP_IS42S16400J7TLI_DQM1_PIN, &stcGpioInit);

    /* DMC_BA[0:1] */
    (void)GPIO_Init(BSP_IS42S16400J7TLI_BA0_PORT, BSP_IS42S16400J7TLI_BA0_PIN, &stcGpioInit);
    (void)GPIO_Init(BSP_IS42S16400J7TLI_BA1_PORT, BSP_IS42S16400J7TLI_BA1_PIN, &stcGpioInit);

    /* DMC_CAS && DMC_RAS */
    (void)GPIO_Init(BSP_IS42S16400J7TLI_CAS_PORT, BSP_IS42S16400J7TLI_CAS_PIN, &stcGpioInit);
    (void)GPIO_Init(BSP_IS42S16400J7TLI_RAS_PORT, BSP_IS42S16400J7TLI_RAS_PIN, &stcGpioInit);

    /* DMC_WE */
    (void)GPIO_Init(BSP_IS42S16400J7TLI_WE_PORT, BSP_IS42S16400J7TLI_WE_PIN, &stcGpioInit);

    /* DMC_DATA[0:15] */
    (void)GPIO_Init(BSP_IS42S16400J7TLI_DATA0_PORT, BSP_IS42S16400J7TLI_DATA0_PIN, &stcGpioInit);
    (void)GPIO_Init(BSP_IS42S16400J7TLI_DATA1_PORT, BSP_IS42S16400J7TLI_DATA1_PIN, &stcGpioInit);
    (void)GPIO_Init(BSP_IS42S16400J7TLI_DATA2_PORT, BSP_IS42S16400J7TLI_DATA2_PIN, &stcGpioInit);
    (void)GPIO_Init(BSP_IS42S16400J7TLI_DATA3_PORT, BSP_IS42S16400J7TLI_DATA3_PIN, &stcGpioInit);
    (void)GPIO_Init(BSP_IS42S16400J7TLI_DATA4_PORT, BSP_IS42S16400J7TLI_DATA4_PIN, &stcGpioInit);
    (void)GPIO_Init(BSP_IS42S16400J7TLI_DATA5_PORT, BSP_IS42S16400J7TLI_DATA5_PIN, &stcGpioInit);
    (void)GPIO_Init(BSP_IS42S16400J7TLI_DATA6_PORT, BSP_IS42S16400J7TLI_DATA6_PIN, &stcGpioInit);
    (void)GPIO_Init(BSP_IS42S16400J7TLI_DATA7_PORT, BSP_IS42S16400J7TLI_DATA7_PIN, &stcGpioInit);
    (void)GPIO_Init(BSP_IS42S16400J7TLI_DATA8_PORT, BSP_IS42S16400J7TLI_DATA8_PIN, &stcGpioInit);
    (void)GPIO_Init(BSP_IS42S16400J7TLI_DATA9_PORT, BSP_IS42S16400J7TLI_DATA9_PIN, &stcGpioInit);
    (void)GPIO_Init(BSP_IS42S16400J7TLI_DATA10_PORT, BSP_IS42S16400J7TLI_DATA10_PIN, &stcGpioInit);
    (void)GPIO_Init(BSP_IS42S16400J7TLI_DATA11_PORT, BSP_IS42S16400J7TLI_DATA11_PIN, &stcGpioInit);
    (void)GPIO_Init(BSP_IS42S16400J7TLI_DATA12_PORT, BSP_IS42S16400J7TLI_DATA12_PIN, &stcGpioInit);
    (void)GPIO_Init(BSP_IS42S16400J7TLI_DATA13_PORT, BSP_IS42S16400J7TLI_DATA13_PIN, &stcGpioInit);
    (void)GPIO_Init(BSP_IS42S16400J7TLI_DATA14_PORT, BSP_IS42S16400J7TLI_DATA14_PIN, &stcGpioInit);
    (void)GPIO_Init(BSP_IS42S16400J7TLI_DATA15_PORT, BSP_IS42S16400J7TLI_DATA15_PIN, &stcGpioInit);

    /* DMC_ADD[0:11]*/
    (void)GPIO_Init(BSP_IS42S16400J7TLI_ADD0_PORT, BSP_IS42S16400J7TLI_ADD0_PIN, &stcGpioInit);
    (void)GPIO_Init(BSP_IS42S16400J7TLI_ADD1_PORT, BSP_IS42S16400J7TLI_ADD1_PIN, &stcGpioInit);
    (void)GPIO_Init(BSP_IS42S16400J7TLI_ADD2_PORT, BSP_IS42S16400J7TLI_ADD2_PIN, &stcGpioInit);
    (void)GPIO_Init(BSP_IS42S16400J7TLI_ADD3_PORT, BSP_IS42S16400J7TLI_ADD3_PIN, &stcGpioInit);
    (void)GPIO_Init(BSP_IS42S16400J7TLI_ADD4_PORT, BSP_IS42S16400J7TLI_ADD4_PIN, &stcGpioInit);
    (void)GPIO_Init(BSP_IS42S16400J7TLI_ADD5_PORT, BSP_IS42S16400J7TLI_ADD5_PIN, &stcGpioInit);
    (void)GPIO_Init(BSP_IS42S16400J7TLI_ADD6_PORT, BSP_IS42S16400J7TLI_ADD6_PIN, &stcGpioInit);
    (void)GPIO_Init(BSP_IS42S16400J7TLI_ADD7_PORT, BSP_IS42S16400J7TLI_ADD7_PIN, &stcGpioInit);
    (void)GPIO_Init(BSP_IS42S16400J7TLI_ADD8_PORT, BSP_IS42S16400J7TLI_ADD8_PIN, &stcGpioInit);
    (void)GPIO_Init(BSP_IS42S16400J7TLI_ADD9_PORT, BSP_IS42S16400J7TLI_ADD9_PIN, &stcGpioInit);
    (void)GPIO_Init(BSP_IS42S16400J7TLI_ADD10_PORT, BSP_IS42S16400J7TLI_ADD10_PIN, &stcGpioInit);
    (void)GPIO_Init(BSP_IS42S16400J7TLI_ADD11_PORT, BSP_IS42S16400J7TLI_ADD11_PIN, &stcGpioInit);

    /************************** Set EXMC pin function *************************/
    /* DMC_CKE */
    GPIO_SetFunc(BSP_IS42S16400J7TLI_CKE_PORT, BSP_IS42S16400J7TLI_CKE_PIN, GPIO_FUNC_12);

    /* DMC_CLK */
    GPIO_SetFunc(BSP_IS42S16400J7TLI_CLK_PORT, BSP_IS42S16400J7TLI_CLK_PIN, GPIO_FUNC_12);

    /* DMC_LDQM && DMC_UDQM */
    GPIO_SetFunc(BSP_IS42S16400J7TLI_DQM0_PORT, BSP_IS42S16400J7TLI_DQM0_PIN, GPIO_FUNC_12);
    GPIO_SetFunc(BSP_IS42S16400J7TLI_DQM1_PORT, BSP_IS42S16400J7TLI_DQM1_PIN, GPIO_FUNC_12);

    /* DMC_BA[0:1] */
    GPIO_SetFunc(BSP_IS42S16400J7TLI_BA0_PORT, BSP_IS42S16400J7TLI_BA0_PIN, GPIO_FUNC_12);
    GPIO_SetFunc(BSP_IS42S16400J7TLI_BA1_PORT, BSP_IS42S16400J7TLI_BA1_PIN, GPIO_FUNC_12);

    /* DMC_CS */
    GPIO_SetFunc(BSP_IS42S16400J7TLI_CS1_PORT, BSP_IS42S16400J7TLI_CS1_PIN, GPIO_FUNC_12);

    /* DMC_CAS && DMC_RAS */
    GPIO_SetFunc(BSP_IS42S16400J7TLI_CAS_PORT, BSP_IS42S16400J7TLI_CAS_PIN, GPIO_FUNC_12);
    GPIO_SetFunc(BSP_IS42S16400J7TLI_RAS_PORT, BSP_IS42S16400J7TLI_RAS_PIN, GPIO_FUNC_12);

    /* DMC_WE */
    GPIO_SetFunc(BSP_IS42S16400J7TLI_WE_PORT, BSP_IS42S16400J7TLI_WE_PIN, GPIO_FUNC_12);

    /* DMC_DATA[0:15] */
    GPIO_SetFunc(BSP_IS42S16400J7TLI_DATA0_PORT, BSP_IS42S16400J7TLI_DATA0_PIN, GPIO_FUNC_12);
    GPIO_SetFunc(BSP_IS42S16400J7TLI_DATA1_PORT, BSP_IS42S16400J7TLI_DATA1_PIN, GPIO_FUNC_12);
    GPIO_SetFunc(BSP_IS42S16400J7TLI_DATA2_PORT, BSP_IS42S16400J7TLI_DATA2_PIN, GPIO_FUNC_12);
    GPIO_SetFunc(BSP_IS42S16400J7TLI_DATA3_PORT, BSP_IS42S16400J7TLI_DATA3_PIN, GPIO_FUNC_12);
    GPIO_SetFunc(BSP_IS42S16400J7TLI_DATA4_PORT, BSP_IS42S16400J7TLI_DATA4_PIN, GPIO_FUNC_12);
    GPIO_SetFunc(BSP_IS42S16400J7TLI_DATA5_PORT, BSP_IS42S16400J7TLI_DATA5_PIN, GPIO_FUNC_12);
    GPIO_SetFunc(BSP_IS42S16400J7TLI_DATA6_PORT, BSP_IS42S16400J7TLI_DATA6_PIN, GPIO_FUNC_12);
    GPIO_SetFunc(BSP_IS42S16400J7TLI_DATA7_PORT, BSP_IS42S16400J7TLI_DATA7_PIN, GPIO_FUNC_12);
    GPIO_SetFunc(BSP_IS42S16400J7TLI_DATA8_PORT, BSP_IS42S16400J7TLI_DATA8_PIN, GPIO_FUNC_12);
    GPIO_SetFunc(BSP_IS42S16400J7TLI_DATA9_PORT, BSP_IS42S16400J7TLI_DATA9_PIN, GPIO_FUNC_12);
    GPIO_SetFunc(BSP_IS42S16400J7TLI_DATA10_PORT, BSP_IS42S16400J7TLI_DATA10_PIN, GPIO_FUNC_12);
    GPIO_SetFunc(BSP_IS42S16400J7TLI_DATA11_PORT, BSP_IS42S16400J7TLI_DATA11_PIN, GPIO_FUNC_12);
    GPIO_SetFunc(BSP_IS42S16400J7TLI_DATA12_PORT, BSP_IS42S16400J7TLI_DATA12_PIN, GPIO_FUNC_12);
    GPIO_SetFunc(BSP_IS42S16400J7TLI_DATA13_PORT, BSP_IS42S16400J7TLI_DATA13_PIN, GPIO_FUNC_12);
    GPIO_SetFunc(BSP_IS42S16400J7TLI_DATA14_PORT, BSP_IS42S16400J7TLI_DATA14_PIN, GPIO_FUNC_12);
    GPIO_SetFunc(BSP_IS42S16400J7TLI_DATA15_PORT, BSP_IS42S16400J7TLI_DATA15_PIN, GPIO_FUNC_12);

    /* DMC_ADD[0:11]*/
    GPIO_SetFunc(BSP_IS42S16400J7TLI_ADD0_PORT, BSP_IS42S16400J7TLI_ADD0_PIN, GPIO_FUNC_12);
    GPIO_SetFunc(BSP_IS42S16400J7TLI_ADD1_PORT, BSP_IS42S16400J7TLI_ADD1_PIN, GPIO_FUNC_12);
    GPIO_SetFunc(BSP_IS42S16400J7TLI_ADD2_PORT, BSP_IS42S16400J7TLI_ADD2_PIN, GPIO_FUNC_12);
    GPIO_SetFunc(BSP_IS42S16400J7TLI_ADD3_PORT, BSP_IS42S16400J7TLI_ADD3_PIN, GPIO_FUNC_12);
    GPIO_SetFunc(BSP_IS42S16400J7TLI_ADD4_PORT, BSP_IS42S16400J7TLI_ADD4_PIN, GPIO_FUNC_12);
    GPIO_SetFunc(BSP_IS42S16400J7TLI_ADD5_PORT, BSP_IS42S16400J7TLI_ADD5_PIN, GPIO_FUNC_12);
    GPIO_SetFunc(BSP_IS42S16400J7TLI_ADD6_PORT, BSP_IS42S16400J7TLI_ADD6_PIN, GPIO_FUNC_12);
    GPIO_SetFunc(BSP_IS42S16400J7TLI_ADD7_PORT, BSP_IS42S16400J7TLI_ADD7_PIN, GPIO_FUNC_12);
    GPIO_SetFunc(BSP_IS42S16400J7TLI_ADD8_PORT, BSP_IS42S16400J7TLI_ADD8_PIN, GPIO_FUNC_12);
    GPIO_SetFunc(BSP_IS42S16400J7TLI_ADD9_PORT, BSP_IS42S16400J7TLI_ADD9_PIN, GPIO_FUNC_12);
    GPIO_SetFunc(BSP_IS42S16400J7TLI_ADD10_PORT, BSP_IS42S16400J7TLI_ADD10_PIN, GPIO_FUNC_12);
    GPIO_SetFunc(BSP_IS42S16400J7TLI_ADD11_PORT, BSP_IS42S16400J7TLI_ADD11_PIN, GPIO_FUNC_12);
}

/**
 * @brief  SDRAM IS42S16400J7TLI initialization sequence.
 * @param  [in] u32Chip                     The command chip number.
 *         This parameter can be one of the following values:
 *           @arg EXMC_DMC_CHIP0:           Chip 0
 *           @arg EXMC_DMC_CHIP1:           Chip 1
 *           @arg EXMC_DMC_CHIP2:           Chip 2
 *           @arg EXMC_DMC_CHIP3:           Chip 3
 * @param  [in] u32Bank                     The command bank.
 *         This parameter can be one of the following values:
 *           @arg EXMC_DMC_BANK0:           Bank 0
 *           @arg EXMC_DMC_BANK1:           Bank 1
 *           @arg EXMC_DMC_BANK2:           Bank 2
 *           @arg EXMC_DMC_BANK3:           Bank 3
 * @param  [in] u32MdRegValue               The SDRAM mode register value
 * @retval None
 */
static void BSP_SDRAM_InitSequence(uint32_t u32Chip, uint32_t u32Bank, uint32_t u32MdRegValue)
{
    /* SDRAM initialization sequence:
       CMD NOP->PrechargeAll->AutoRefresh->AutoRefresh->MdRegConfig->NOP */
    (void)EXMC_DMC_SetCommand(u32Chip, u32Bank, EXMC_DMC_CMD_NOP, 0UL);
    (void)EXMC_DMC_SetCommand(u32Chip, u32Bank, EXMC_DMC_CMD_PRECHARGE_ALL, 0UL);
    (void)EXMC_DMC_SetCommand(u32Chip, u32Bank, EXMC_DMC_CMD_AUTO_REFRESH, 0UL);
    (void)EXMC_DMC_SetCommand(u32Chip, u32Bank, EXMC_DMC_CMD_AUTO_REFRESH, 0UL);
    (void)EXMC_DMC_SetCommand(u32Chip, u32Bank, EXMC_DMC_CMD_MDREG_CONFIG, u32MdRegValue);
    (void)EXMC_DMC_SetCommand(u32Chip, u32Bank, EXMC_DMC_CMD_NOP, 0UL);
}

/**
 * @}
 */

#endif /* BSP_IS42S16400J7TLI_ENABLE && BSP_EV_HC32F4A0_LQFP176 */

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
