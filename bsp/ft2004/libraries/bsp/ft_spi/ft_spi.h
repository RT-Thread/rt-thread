/*
 * @ : Copyright (c) 2021 Phytium Information Technology, Inc.
 *
 * SPDX-License-Identifier: Apache-2.0.
 *
 * @Date: 2021-04-25 13:59:05
 * @LastEditTime: 2021-04-30 16:11:46
 * @Description:  This files is for
 *
 * @Modify History:
 *  Ver   Who        Date         Changes
 * ----- ------     --------    --------------------------------------
 */

#ifndef FT_BSP_SPI_H
#define FT_BSP_SPI_H

#ifdef __cplusplus
extern "C"
{
#endif

#include "ft_types.h"
#include "ft_spi_hw.h"
#include "ft_error_code.h"
#include "ft_debug.h"

        typedef struct
        {
                u8 WorkMode;
#define SPI_CTRL_MASTER_MODE (u8)0x0
#define SPI_CTRL_SLAVE_MODE (u8)0x1
                u8 DevAddrLen;
#define SPI_3_BYTE_ADDR (u8)0x3
#define SPI_4_BYTE_ADDR (u8)0x4
                u8 Cpol;
#define SPI_CTRL_CPOL_LOW (u8)0x0
#define SPI_CTRL_CPOL_HIGH (u8)0x1
                u8 Cpha;
#define SPI_CTRL_CPHA_1EDGE (u8)0x0
#define SPI_CTRL_CPHA_2EDGE (u8)0x1
                u8 DevAddr[4];
                u32 BaudRDiv;
        } FSpi_Conf_t;

        typedef struct
        {
                FSpi_Conf_t Config;
                FSpi_CtrlId_t CtrlId;
                FSpi_DevId_t DevId; /* support only one slave at the moment */
                bool_t IsReady;
                u16 CsPin; /* cs pin in gpio group A */
        } FSpi_Ctrl_t;

/* misc marco */
#define SPI_TIMEOUT 5000
#define SPI_DUMMY_TX_DATA 0xFF

/* ctrl member shortcut */
#define FSPI_DEV_ADDR_LEN(pCtrl) (pCtrl->Config.DevAddrLen)
#define FSPI_IS_3_BYTE_ADDR(pCtrl) (SPI_3_BYTE_ADDR == FSPI_DEV_ADDR_LEN(pCtrl))
#define FSPI_DEV_ADDR(pCtrl) (pCtrl->Config.DevAddr)

/* define error code */
#define ERR_SPI_OK ERR_SUCCESS
#define ERR_SPI_GENERAL FT_CODE_ERR(ERR_MODE_SPI, 0, 1)
#define ERR_SPI_NOT_READY FT_CODE_ERR(ERR_MODE_SPI, 0, 2)
#define ERR_SPI_TX_TIMEOUT FT_CODE_ERR(ERR_MODE_SPI, 0, 3)
#define ERR_SPI_RX_TIMEOUT FT_CODE_ERR(ERR_MODE_SPI, 0, 4)

/* spi flash error code */
#define ERR_SPI_WAIT_TIMEOUT FT_CODE_ERR(ERR_MODE_SPI, 1, 1)

/* define debug utilities */
#define FT_SPI_DEBUG_TAG "FT_SPI"
#define FT_SPI_ENABLE_DEBUG
#define FT_SPI_ERROR(format, ...) FT_DEBUG_PRINT_E(FT_SPI_DEBUG_TAG, format, ##__VA_ARGS__)
#ifdef FT_SPI_ENABLE_DEBUG
#define FT_SPI_DEBUG_I(format, ...) FT_DEBUG_PRINT_I(FT_SPI_DEBUG_TAG, format, ##__VA_ARGS__)
#define FT_SPI_DEBUG_W(format, ...) FT_DEBUG_PRINT_W(FT_SPI_DEBUG_TAG, format, ##__VA_ARGS__)
#else
#define FT_SPI_DEBUG_I(format, ...)
#define FT_SPI_DEBUG_W(format, ...)
#endif

        u32 FSpi_Init(FT_INOUT FSpi_Ctrl_t *pCtrl);
        u32 FSpi_ReadWriteByte(FT_INOUT FSpi_Ctrl_t *pCtrl, FT_IN u8 TxData,
                               FT_OUT u8 *pRxData);
        void FSpi_SelectSlave(FT_INOUT FSpi_Ctrl_t *pCtrl, FT_IN FSpi_DevId_t DevId,
                              FT_IN bool_t select);
#ifdef __cplusplus
}
#endif

#endif
