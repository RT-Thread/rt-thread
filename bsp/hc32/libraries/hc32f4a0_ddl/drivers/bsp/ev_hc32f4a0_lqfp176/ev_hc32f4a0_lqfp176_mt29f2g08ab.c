/**
 *******************************************************************************
 * @file  ev_hc32f4a0_lqfp176_mt29f2g08ab.c
 * @brief This file provides configure functions for mt29f2g08ab of the board
 *        EV_HC32F4A0_LQFP176.
 @verbatim
   Change Logs:
   Date             Author          Notes
   2022-03-31       CDT             First version
   2022-10-31       CDT             Optimize timing parameters
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
#include "ev_hc32f4a0_lqfp176_mt29f2g08ab.h"

/**
 * @addtogroup BSP
 * @{
 */

/**
 * @addtogroup EV_HC32F4A0_LQFP176
 * @{
 */

/**
 * @defgroup EV_HC32F4A0_LQFP176_MT29F2G08AB EV_HC32F4A0_LQFP176 MT29F2G08AB
 * @{
 */

#if ((BSP_MT29F2G08AB_ENABLE == DDL_ON) && (BSP_EV_HC32F4A0_LQFP176 == BSP_EV_HC32F4XX))

/*******************************************************************************
 * Local type definitions ('typedef')
 ******************************************************************************/

/*******************************************************************************
 * Local pre-processor symbols/macros ('#define')
 ******************************************************************************/
/**
 * @defgroup EV_HC32F4A0_LQFP176_MT29F2G08AB_Local_Macros EV_HC32F4A0_LQFP176 MT29F2G08AB Local Macros
 * @{
 */

/**
 * @defgroup EV_EXMC_NFC_Operation_Timeout EXMC_NFC Operation Timeout
 * @{
 */
#define BSP_NFC_ERASE_TIMEOUT           (2000000UL)
#define BSP_NFC_READ_TIMEOUT            (2000000UL)
#define BSP_NFC_READ_HWECC_TIMEOUT      (9000000UL)
#define BSP_NFC_WRITE_TIMEOUT           (2000000UL)
#define BSP_NFC_WRITE_HWECC_TIMEOUT     (2000000UL)
#define BSP_NFC_RESET_TIMEOUT           (2000000UL)
/**
 * @}
 */

/**
 * @defgroup MT29F2G08AB_Map_NFC_Bank MT29F2G08AB Map NFC Bank
 * @{
 */
#define BSP_MT29F2G08AB_BYTES_PER_PAGE  (EXMC_NFC_PAGE_SIZE_2KBYTE)
#define BSP_MT29F2G08AB_CAPACITY_BITS   (EXMC_NFC_BANK_CAPACITY_2GBIT)
/**
 * @}
 */

/**
 * @defgroup MT29F2G08AB_Status_Register_Field MT29F2G08AB Status Register Field
 * @{
 */
/* MT29F2G08AB Status Register: bit0-FAIL */
#define BSP_MT29F2G08AB_SR_FAIL         (1UL << 0)

/* MT29F2G08AB Status Register: bit6-RDY */
#define BSP_MT29F2G08AB_SR_READY        (1UL << 6)
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

/*******************************************************************************
 * Function implementation - global ('extern') and local ('static')
 ******************************************************************************/
/**
 * @defgroup EV_HC32F4A0_LQFP176_MT29F2G08AB_Local_Functions EV_HC32F4A0_LQFP176 MT29F2G08AB Local Functions
 * @{
 */

/**
 * @brief  Initialize NFC port.
 * @param  None
 * @retval None
 */
static void BSP_NFC_PortInit(void)
{
    stc_gpio_init_t stcGpioInit;

    /************************* Set pin drive capacity *************************/
    (void)GPIO_StructInit(&stcGpioInit);
    stcGpioInit.u16PinDrv = PIN_HIGH_DRV;

    /* NFC_CE */
    (void)GPIO_Init(BSP_MT29F2G08AB_CE_PORT, BSP_MT29F2G08AB_CE_PIN, &stcGpioInit);

    /* NFC_RE */
    (void)GPIO_Init(BSP_MT29F2G08AB_RE_PORT, BSP_MT29F2G08AB_RE_PIN, &stcGpioInit);

    /* NFC_WE */
    (void)GPIO_Init(BSP_MT29F2G08AB_WE_PORT, BSP_MT29F2G08AB_WE_PIN, &stcGpioInit);

    /* NFC_CLE */
    (void)GPIO_Init(BSP_MT29F2G08AB_CLE_PORT, BSP_MT29F2G08AB_CLE_PIN, &stcGpioInit);

    /* NFC_ALE */
    (void)GPIO_Init(BSP_MT29F2G08AB_ALE_PORT, BSP_MT29F2G08AB_ALE_PIN, &stcGpioInit);

    /* NFC_WP */
    (void)GPIO_Init(BSP_MT29F2G08AB_WP_PORT, BSP_MT29F2G08AB_WP_PIN, &stcGpioInit);
    GPIO_SetPins(BSP_MT29F2G08AB_WP_PORT, BSP_MT29F2G08AB_WP_PIN);

    /* NFC_DATA[0:7] */
    (void)GPIO_Init(BSP_MT29F2G08AB_DATA0_PORT, BSP_MT29F2G08AB_DATA0_PIN, &stcGpioInit);
    (void)GPIO_Init(BSP_MT29F2G08AB_DATA1_PORT, BSP_MT29F2G08AB_DATA1_PIN, &stcGpioInit);
    (void)GPIO_Init(BSP_MT29F2G08AB_DATA2_PORT, BSP_MT29F2G08AB_DATA2_PIN, &stcGpioInit);
    (void)GPIO_Init(BSP_MT29F2G08AB_DATA3_PORT, BSP_MT29F2G08AB_DATA3_PIN, &stcGpioInit);
    (void)GPIO_Init(BSP_MT29F2G08AB_DATA4_PORT, BSP_MT29F2G08AB_DATA4_PIN, &stcGpioInit);
    (void)GPIO_Init(BSP_MT29F2G08AB_DATA5_PORT, BSP_MT29F2G08AB_DATA5_PIN, &stcGpioInit);
    (void)GPIO_Init(BSP_MT29F2G08AB_DATA6_PORT, BSP_MT29F2G08AB_DATA6_PIN, &stcGpioInit);
    (void)GPIO_Init(BSP_MT29F2G08AB_DATA7_PORT, BSP_MT29F2G08AB_DATA7_PIN, &stcGpioInit);

    /* NFC_RB */
    (void)GPIO_Init(BSP_MT29F2G08AB_RB_PORT, BSP_MT29F2G08AB_RB_PIN, &stcGpioInit);

    /************************** Set EXMC pin function *************************/
    /* NFC_CE */
    GPIO_SetFunc(BSP_MT29F2G08AB_CE_PORT, BSP_MT29F2G08AB_CE_PIN, GPIO_FUNC_12);

    /* NFC_RE */
    GPIO_SetFunc(BSP_MT29F2G08AB_RE_PORT, BSP_MT29F2G08AB_RE_PIN, GPIO_FUNC_12);

    /* NFC_WE */
    GPIO_SetFunc(BSP_MT29F2G08AB_WE_PORT, BSP_MT29F2G08AB_WE_PIN, GPIO_FUNC_12);

    /* NFC_CLE */
    GPIO_SetFunc(BSP_MT29F2G08AB_CLE_PORT, BSP_MT29F2G08AB_CLE_PIN, GPIO_FUNC_12);

    /* NFC_ALE */
    GPIO_SetFunc(BSP_MT29F2G08AB_ALE_PORT, BSP_MT29F2G08AB_ALE_PIN, GPIO_FUNC_12);

    /* NFC_WP */
    GPIO_SetFunc(BSP_MT29F2G08AB_WP_PORT, BSP_MT29F2G08AB_WP_PIN, GPIO_FUNC_12);

    /* NFC_RB */
    GPIO_SetFunc(BSP_MT29F2G08AB_RB_PORT, BSP_MT29F2G08AB_RB_PIN, GPIO_FUNC_12);

    /* NFC_DATA[0:7] */
    GPIO_SetFunc(BSP_MT29F2G08AB_DATA0_PORT, BSP_MT29F2G08AB_DATA0_PIN, GPIO_FUNC_12);
    GPIO_SetFunc(BSP_MT29F2G08AB_DATA1_PORT, BSP_MT29F2G08AB_DATA1_PIN, GPIO_FUNC_12);
    GPIO_SetFunc(BSP_MT29F2G08AB_DATA2_PORT, BSP_MT29F2G08AB_DATA2_PIN, GPIO_FUNC_12);
    GPIO_SetFunc(BSP_MT29F2G08AB_DATA3_PORT, BSP_MT29F2G08AB_DATA3_PIN, GPIO_FUNC_12);
    GPIO_SetFunc(BSP_MT29F2G08AB_DATA4_PORT, BSP_MT29F2G08AB_DATA4_PIN, GPIO_FUNC_12);
    GPIO_SetFunc(BSP_MT29F2G08AB_DATA5_PORT, BSP_MT29F2G08AB_DATA5_PIN, GPIO_FUNC_12);
    GPIO_SetFunc(BSP_MT29F2G08AB_DATA6_PORT, BSP_MT29F2G08AB_DATA6_PIN, GPIO_FUNC_12);
    GPIO_SetFunc(BSP_MT29F2G08AB_DATA7_PORT, BSP_MT29F2G08AB_DATA7_PIN, GPIO_FUNC_12);
}

/**
 * @brief  Get status.
 * @param  [in] u32Bank                 The specified bank
 *         This parameter can be one of the macros group @ref EXMC_NFC_Bank
 *           @arg EXMC_NFC_BANK0:       NFC device bank 0
 *           @arg EXMC_NFC_BANK1:       NFC device bank 1
 *           @arg EXMC_NFC_BANK2:       NFC device bank 2
 *           @arg EXMC_NFC_BANK3:       NFC device bank 3
 *           @arg EXMC_NFC_BANK4:       NFC device bank 4
 *           @arg EXMC_NFC_BANK5:       NFC device bank 5
 *           @arg EXMC_NFC_BANK6:       NFC device bank 6
 *           @arg EXMC_NFC_BANK7:       NFC device bank 7
 * @param  [in] u32Timeout              The operation timeout value
 * @retval int32_t:
 *           - LL_OK:                   No errors occurred.
 *           - LL_ERR:                  Status error.
 *           - LL_ERR_TIMEOUT:          Get timeout.
 */
static int32_t MT29F2G08AB_GetStatus(uint32_t u32Bank, uint32_t u32Timeout)
{
    uint32_t u32To = 0UL;
    uint32_t u32Status = 0UL;
    int32_t i32Ret = LL_OK;

    do {
        /* Block checking flag if timeout value is EXMC_NFC_MAX_TIMEOUT */
        if ((u32To++ > u32Timeout) && (u32Timeout < EXMC_NFC_MAX_TIMEOUT)) {
            i32Ret = LL_ERR_TIMEOUT;
            break;
        }

        u32Status = EXMC_NFC_ReadStatus(u32Bank);
    } while (0UL == (u32Status & BSP_MT29F2G08AB_SR_READY));

    if (LL_ERR_TIMEOUT != i32Ret) {
        if (0UL != (u32Status & BSP_MT29F2G08AB_SR_FAIL)) {
            i32Ret = LL_ERR;
        }
    }

    return i32Ret;
}

/**
 * @}
 */

/**
 * @defgroup EV_HC32F4A0_LQFP176_MT29F2G08AB_Global_Functions EV_HC32F4A0_LQFP176 MT29F2G08AB Global Functions
 * @{
 */

/**
 * @brief  Initialize Flash.
 * @param  None
 * @retval int32_t:
 *           - LL_OK:                   Initialize successfully.
 *           - LL_ERR:                  Initialize unsuccessfully.
 */
int32_t BSP_MT29F2G08AB_Init(void)
{
    int32_t i32Ret = LL_ERR;
    stc_exmc_nfc_init_t stcNfcInit;

    /* Initialize NFC port.*/
    BSP_NFC_PortInit();

    /* Enable NFC module clk */
    FCG_Fcg3PeriphClockCmd(FCG3_PERIPH_NFC, ENABLE);

    /* Enable NFC. */
    EXMC_NFC_Cmd(ENABLE);

    /* Configure NFC width && refresh period & chip & timing. */
    stcNfcInit.u32OpenPage = EXMC_NFC_OPEN_PAGE_DISABLE;
    stcNfcInit.stcBaseConfig.u32CapacitySize = EXMC_NFC_BANK_CAPACITY_2GBIT;
    stcNfcInit.stcBaseConfig.u32MemoryWidth = EXMC_NFC_MEMORY_WIDTH_8BIT;
    stcNfcInit.stcBaseConfig.u32BankNum = EXMC_NFC_1BANK;
    stcNfcInit.stcBaseConfig.u32PageSize = EXMC_NFC_PAGE_SIZE_2KBYTE;
    stcNfcInit.stcBaseConfig.u32WriteProtect = EXMC_NFC_WR_PROTECT_DISABLE;
    stcNfcInit.stcBaseConfig.u32EccMode = EXMC_NFC_1BIT_ECC;
    stcNfcInit.stcBaseConfig.u32RowAddrCycle = EXMC_NFC_3_ROW_ADDR_CYCLE;
    stcNfcInit.stcBaseConfig.u8SpareSizeForUserData = 0U;

    /* EXCLK frequency @60MHz: 3.3V */
    stcNfcInit.stcTimingReg0.u32TS = 1UL;     /* ALE/CLE/CE setup time:  min=10ns */
    stcNfcInit.stcTimingReg0.u32TWP = 1UL;    /* WE# pulse width:        min=10ns */
    stcNfcInit.stcTimingReg0.u32TRP = 2UL;    /* RE# pulse width:        min=10ns
                                                 and EXMC t_data_s:      min=24ns */
    stcNfcInit.stcTimingReg0.u32TH = 1UL;     /* ALE/CLE/CE hold time    min=5ns */

    stcNfcInit.stcTimingReg1.u32TWH = 1UL;    /* WE# pulse width HIGH:   min=10ns */
    stcNfcInit.stcTimingReg1.u32TRH = 1UL;    /* RE# pulse width HIGH:   min=7ns */
    stcNfcInit.stcTimingReg1.u32TRR = 2UL;    /* Ready to RE# LOW:       min=20ns */
    stcNfcInit.stcTimingReg1.u32TWB = 1UL;    /* WE# HIGH to busy:       max=100ns */

    stcNfcInit.stcTimingReg2.u32TCCS = 5UL;
    stcNfcInit.stcTimingReg2.u32TWTR = 4UL;   /* WE# HIGH to RE# LOW:    min=60ns */
    stcNfcInit.stcTimingReg2.u32TRTW = 7UL;   /* RE# HIGH to WE# LOW:    min=100ns */
    stcNfcInit.stcTimingReg2.u32TADL = 5UL;   /* ALE to data start:      min=70ns */
    if (LL_OK == EXMC_NFC_Init(&stcNfcInit)) {
        /* Reset NFC device. */
        if (LL_OK == EXMC_NFC_Reset(BSP_MT29F2G08AB_BANK, BSP_NFC_RESET_TIMEOUT)) {
            i32Ret = LL_OK;
        }
    }

    return i32Ret;
}

/**
 * @brief  Read ID.
 * @param  [in] u32IdAddr               The ID address
 * @param  [in] au8DevId                The ID buffer
 * @param  [in] u32NumBytes             The number of bytes to read
 * @param  [in] u32Timeout              The operation timeout value
 * @retval int32_t:
 *           - LL_OK:                   No errors occurred.
 *           - LL_ERR_TIMEOUT:          Read timeout.
 *           - LL_ERR_INVD_PARAM:       The pointer au8DevId value is NULL or u8NumBytes value is 0.
 */
int32_t BSP_MT29F2G08AB_ReadId(uint32_t u32IdAddr, uint8_t au8DevId[], uint32_t u32NumBytes, uint32_t u32Timeout)
{
    int32_t i32Ret = LL_ERR_INVD_PARAM;

    if ((NULL != au8DevId) && (u32NumBytes > 0UL)) {
        i32Ret = EXMC_NFC_ReadId(BSP_MT29F2G08AB_BANK, u32IdAddr, au8DevId, u32NumBytes, u32Timeout);
    }

    return i32Ret;
}

/**
 * @brief  Erase block.
 * @param  [in] u32BlockRowAddr         The specified block row address
 * @param  [in] u32Timeout              The operation timeout value
 * @retval int32_t:
 *           - LL_OK:                   No errors occurred.
 *           - LL_ERR:                  Nand flash status is abnormal.
 *           - LL_ERR_TIMEOUT:          Erase timeout.
 */
int32_t BSP_MT29F2G08AB_EraseBlock(uint32_t u32BlockRowAddr, uint32_t u32Timeout)
{
    int32_t i32Ret;

    i32Ret = EXMC_NFC_EraseBlock(BSP_MT29F2G08AB_BANK,  u32BlockRowAddr, u32Timeout);
    if (LL_OK == i32Ret) {
        i32Ret = MT29F2G08AB_GetStatus(BSP_MT29F2G08AB_BANK, u32Timeout);
    }

    return i32Ret;
}

/**
 * @brief  Read page.
 * @param  [in] u32Page                 The specified page
 * @param  [out] pu8Data                The buffer for reading
 * @param  [in] u32NumBytes             The buffer size for bytes
 * @param  [in] u32Timeout              The operation timeout value
 * @retval int32_t:
 *           - LL_OK:                   No errors occurred.
 *           - LL_ERR:                  Nand flash status is abnormal.
 *           - LL_ERR_TIMEOUT:          Read timeout.
 *           - LL_ERR_INVD_PARAM:       If one of following cases matches:
 *                                      - u32Page value is out of range.
 *                                      - The pointer pu8Data value is NULL.
 *                                      - u32NumBytes value is out of range.
 */
int32_t BSP_MT29F2G08AB_ReadPage(uint32_t u32Page, uint8_t *pu8Data,
                                 uint32_t u32NumBytes, uint32_t u32Timeout)
{
    int32_t i32Ret = LL_ERR_INVD_PARAM;

    if ((NULL != pu8Data) && \
        (u32Page < BSP_MT29F2G08AB_DEVICE_PAGES) && \
        ((u32NumBytes > 0UL) && (u32NumBytes <= BSP_MT29F2G08AB_PAGE_SIZE_WITH_SPARE))) {
        i32Ret = EXMC_NFC_ReadPageMeta(BSP_MT29F2G08AB_BANK, u32Page, pu8Data, u32NumBytes, u32Timeout);
        if (LL_OK == i32Ret) {
            i32Ret = MT29F2G08AB_GetStatus(BSP_MT29F2G08AB_BANK, u32Timeout);
        }
    }

    return i32Ret;
}

/**
 * @brief  Write page.
 * @param  [in] u32Page                 The specified page
 * @param  [in] pu8Data                 The buffer for writing
 * @param  [in] u32NumBytes             The buffer size for bytes
 * @param  [in] u32Timeout              The operation timeout value
 * @retval int32_t:
 *           - LL_OK:                   No errors occurred.
 *           - LL_ERR:                  Nand flash status is abnormal.
 *           - LL_ERR_TIMEOUT:          Read timeout.
 *           - LL_ERR_INVD_PARAM:       If one of following cases matches:
 *                                      - u32Page value is out of range.
 *                                      - The pointer pu8Data value is NULL.
 *                                      - u32NumBytes value is out of range.
 */
int32_t BSP_MT29F2G08AB_WritePage(uint32_t u32Page, const uint8_t *pu8Data,
                                  uint32_t u32NumBytes, uint32_t u32Timeout)
{
    int32_t i32Ret = LL_ERR_INVD_PARAM;

    if ((NULL != pu8Data) && \
        (u32Page < BSP_MT29F2G08AB_DEVICE_PAGES) && \
        ((u32NumBytes > 0UL) && (u32NumBytes <= BSP_MT29F2G08AB_PAGE_SIZE_WITH_SPARE))) {
        i32Ret = EXMC_NFC_WritePageMeta(BSP_MT29F2G08AB_BANK, u32Page, pu8Data, u32NumBytes, u32Timeout);
        if (LL_OK == i32Ret) {
            i32Ret = MT29F2G08AB_GetStatus(BSP_MT29F2G08AB_BANK, u32Timeout);
        }
    }

    return i32Ret;
}

/**
 * @brief  Read page with hardware ECC 1Bit.
 * @param  [in] u32Page                 The specified page
 * @param  [out] pu8Data                The buffer for reading
 * @param  [in] u32NumBytes             The buffer size for bytes
 * @param  [in] u32Timeout              The operation timeout value
 * @retval int32_t:
 *           - LL_OK:                   No errors occurred.
 *           - LL_ERR:                  Nand flash status is abnormal.
 *           - LL_ERR_TIMEOUT:          Read timeout.
 *           - LL_ERR_INVD_PARAM:       If one of following cases matches:
 *                                      - u32Page value is out of range.
 *                                      - The pointer pu8Data value is NULL.
 *                                      - u32NumBytes value is out of range.
 */
int32_t BSP_MT29F2G08AB_1BitEccReadPage(uint32_t u32Page, uint8_t *pu8Data,
                                        uint32_t u32NumBytes, uint32_t u32Timeout)
{
    int32_t i32Ret = LL_ERR_INVD_PARAM;

    if ((NULL != pu8Data) && \
        (u32Page < BSP_MT29F2G08AB_DEVICE_PAGES) && \
        ((u32NumBytes > 0UL) && (u32NumBytes <= BSP_MT29F2G08AB_PAGE_SIZE_WITH_SPARE))) {
        EXMC_NFC_SetEccMode(EXMC_NFC_1BIT_ECC);
        i32Ret = EXMC_NFC_ReadPageHwEcc(BSP_MT29F2G08AB_BANK, u32Page, pu8Data, u32NumBytes, u32Timeout);
        if (LL_OK == i32Ret) {
            i32Ret = MT29F2G08AB_GetStatus(BSP_MT29F2G08AB_BANK, u32Timeout);
        }
    }

    return i32Ret;
}

/**
 * @brief  Write page with hardware ECC 1Bit.
 * @param  [in] u32Page                 The specified page
 * @param  [in] pu8Data                 The buffer for writing
 * @param  [in] u32NumBytes             The buffer size for bytes
 * @param  [in] u32Timeout              The operation timeout value
 * @retval int32_t:
 *           - LL_OK:                   No errors occurred.
 *           - LL_ERR:                  Nand flash status is abnormal.
 *           - LL_ERR_TIMEOUT:          Read timeout.
 *           - LL_ERR_INVD_PARAM:       If one of following cases matches:
 *                                      - u32Page value is out of range.
 *                                      - The pointer pu8Data value is NULL.
 *                                      - u32NumBytes value is out of range.
 */
int32_t BSP_MT29F2G08AB_1BitEccWritePage(uint32_t u32Page, const uint8_t *pu8Data,
                                         uint32_t u32NumBytes, uint32_t u32Timeout)
{
    int32_t i32Ret = LL_ERR_INVD_PARAM;

    if ((NULL != pu8Data) && \
        (u32Page < BSP_MT29F2G08AB_DEVICE_PAGES) && \
        ((u32NumBytes > 0UL) && (u32NumBytes <= BSP_MT29F2G08AB_PAGE_SIZE_WITH_SPARE))) {
        EXMC_NFC_SetEccMode(EXMC_NFC_1BIT_ECC);
        i32Ret = EXMC_NFC_WritePageHwEcc(BSP_MT29F2G08AB_BANK, u32Page, pu8Data, u32NumBytes, u32Timeout);
        if (LL_OK == i32Ret) {
            i32Ret = MT29F2G08AB_GetStatus(BSP_MT29F2G08AB_BANK, u32Timeout);
        }
    }

    return i32Ret;
}

/**
 * @brief  Read page with hardware ECC 4Bit.
 * @param  [in] u32Page                 The specified page
 * @param  [out] pu8Data                The buffer for reading
 * @param  [in] u32NumBytes             The buffer size for bytes
 * @param  [in] u32Timeout              The operation timeout value
 * @retval int32_t:
 *           - ECC status               ECC status if return value non-negative numbers.
 *           - LL_ERR:                  Nand flash status is abnormal.
 *           - LL_ERR_TIMEOUT:          Read timeout.
 *           - LL_ERR_INVD_PARAM:       If one of following cases matches:
 *                                      - u32Page value is out of range.
 *                                      - The pointer pu8Data value is NULL.
 *                                      - u32NumBytes value is out of range.
 */
int32_t BSP_MT29F2G08AB_4BitEccReadPage(uint32_t u32Page, uint8_t *pu8Data,
                                        uint32_t u32NumBytes, uint32_t u32Timeout)
{
    uint16_t u16EccStatus;
    int32_t i32Ret = LL_ERR_INVD_PARAM;

    if ((NULL != pu8Data) && \
        (u32Page < BSP_MT29F2G08AB_DEVICE_PAGES) && \
        ((u32NumBytes > 0UL) && (u32NumBytes <= BSP_MT29F2G08AB_PAGE_SIZE_WITH_SPARE))) {
        EXMC_NFC_SetEccMode(EXMC_NFC_4BIT_ECC);
        i32Ret = EXMC_NFC_ReadPageHwEcc(BSP_MT29F2G08AB_BANK, u32Page, pu8Data, u32NumBytes, u32Timeout);
        if (LL_OK == i32Ret) {
            u16EccStatus = EXMC_NFC_Get4BitEccErrSection();
            i32Ret = MT29F2G08AB_GetStatus(BSP_MT29F2G08AB_BANK, u32Timeout);
            if (LL_OK == i32Ret) {
                i32Ret = (int32_t)u16EccStatus;
            }
        }
    }

    return i32Ret;
}

/**
 * @brief  Write page with hardware ECC 4Bit.
 * @param  [in] u32Page                 The specified page
 * @param  [in] pu8Data                 The buffer for writing
 * @param  [in] u32NumBytes             The buffer size for bytes
 * @param  [in] u32Timeout              The operation timeout value
 * @retval int32_t:
 *           - LL_OK:                   No errors occurred.
 *           - LL_ERR:                  Nand flash status is abnormal.
 *           - LL_ERR_TIMEOUT:          Read timeout.
 *           - LL_ERR_INVD_PARAM:       If one of following cases matches:
 *                                      - u32Page value is out of range.
 *                                      - The pointer pu8Data value is NULL.
 *                                      - u32NumBytes value is out of range.
 */
int32_t BSP_MT29F2G08AB_4BitEccWritePage(uint32_t u32Page, const uint8_t *pu8Data,
                                         uint32_t u32NumBytes, uint32_t u32Timeout)
{
    int32_t i32Ret = LL_ERR_INVD_PARAM;

    if ((NULL != pu8Data) && \
        (u32Page < BSP_MT29F2G08AB_DEVICE_PAGES) && \
        ((u32NumBytes > 0UL) && (u32NumBytes <= BSP_MT29F2G08AB_PAGE_SIZE_WITH_SPARE))) {
        EXMC_NFC_SetEccMode(EXMC_NFC_4BIT_ECC);
        i32Ret = EXMC_NFC_WritePageHwEcc(BSP_MT29F2G08AB_BANK, u32Page, pu8Data, u32NumBytes, u32Timeout);
        if (LL_OK == i32Ret) {
            i32Ret = MT29F2G08AB_GetStatus(BSP_MT29F2G08AB_BANK, u32Timeout);
        }
    }

    return i32Ret;
}

/**
 * @}
 */

#endif /* BSP_MT29F2G08AB_ENABLE && BSP_EV_HC32F4A0_LQFP176 */

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
