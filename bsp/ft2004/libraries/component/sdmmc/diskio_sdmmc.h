/*
 * @ : Copyright (c) 2020 Phytium Information Technology, Inc. 
 * The right to copy, distribute, modify, or otherwise make use 
 * of this software may be licensed only pursuant to the terms
 * of an applicable Phytium license agreement.
 * @Date: 2021-04-14 15:03:12
 * @LastEditTime: 2021-04-16 10:39:54
 * @Description:  This files is for 
 * 
 * @Modify History: 
 *  Ver   Who        Date         Changes
 * ----- ------     --------    --------------------------------------
 */

#ifndef _FT_DISKIO_FATFS_H_
#define _FT_DISKIO_FATFS_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include "ft_sdctrl.h"
#include "ft_types.h"
#include "ft_error_code.h"
#include "ft_sdmmc_defs.h"
#include "ft_sdmmc_common.h"
#include "ft_sdmmc.h"
#include "ft_debug.h"

#define FATFS_HOST_SLOT_0     0  ///< FATFS slot 0

#define FATFS_ERROR_HANDLE_RET(result, expression, msg) \
    { \
        if (ERR_SDMMC_OK == (result)) { \
            result = expression; \
            if (result != ERR_SDMMC_OK) { \
                FT_FATFS_DEBUG_E("sd mmc process failed when %s err 0x%x at %s", msg, result, __func__); \
                return result; \
            } \
        } \
    }
 
#define FATFS_ERROR_HANDLE_GOTO(result, expression, label, msg) \
    { \
        if (ERR_SDMMC_OK == (result)) { \
            result = expression; \
            if (result != ERR_SDMMC_OK) { \
                FT_FATFS_DEBUG_E("sd mmc process failed when %s err 0x%x at %s", msg, result, __func__); \
                goto label; \
            } \
        } \
    }

#define FATFS_ALLOC_HANDLE_RET(result, ptr) \
    {                                       \
        if (NULL == (ptr))                  \
        {                                   \
            result = ERR_FATFS_NO_MEM;      \
            FT_FATFS_DEBUG_E("sd mmc memory allocate failed err %d at %s", result, __func__); \
            return result; \
        }\
    }

#define FATFS_ALLOC_HANDLE_GOTO(result, ptr, label) \
    {                                       \
        if (NULL == (ptr))                  \
        {                                   \
            result = ERR_FATFS_NO_MEM;      \
            FT_FATFS_DEBUG_E("sd mmc memory allocate failed err %d at %s", result, __func__); \
            goto label; \
        }\
    }

ft_error_t FSdmmc_ProbeSd(int slot, int width, int freq_khz, bool_t ddr);
ft_error_t FSdmmc_InitSd();
ft_error_t FSdmmc_ReadSector(u32 startSector, u32 numSector, void *pBuf);
ft_error_t FSdmmc_WriteSector(u32 startSector, u32 numSector, void *pBuf);
bool_t FSdmmc_CardExist();
bool_t FSdmmc_IsSdmmcReady();

#define FT_FATFS_DEBUG_ENABLED
#define FT_FATFS_DEBUG_TAG "FT_FATFS"
#ifdef FT_FATFS_DEBUG_ENABLED
#define FT_FATFS_DEBUG_I(format, ...) FT_DEBUG_PRINT_I(FT_FATFS_DEBUG_TAG, format, ##__VA_ARGS__)
#define FT_FATFS_DEBUG_E(format, ...) FT_DEBUG_PRINT_E(FT_FATFS_DEBUG_TAG, format, ##__VA_ARGS__)
#define FT_FATFS_DEBUG_D(format, ...) FT_DEBUG_PRINT_D(FT_FATFS_DEBUG_TAG, format, ##__VA_ARGS__)
#define FT_FATFS_DEBUG_W(format, ...) FT_DEBUG_PRINT_W(FT_FATFS_DEBUG_TAG, format, ##__VA_ARGS__)
#define FT_FATFS_DEBUG_V(format, ...) FT_DEBUG_PRINT_V(FT_FATFS_DEBUG_TAG, format, ##__VA_ARGS__)
#else
#define FT_FATFS_DEBUG_I(format, ...) 
#define FT_FATFS_DEBUG_E(format, ...) 
#define FT_FATFS_DEBUG_D(format, ...) 
#define FT_FATFS_DEBUG_W(format, ...) 
#define FT_FATFS_DEBUG_V(format, ...) 
#endif

#ifdef __cplusplus
}
#endif

#endif