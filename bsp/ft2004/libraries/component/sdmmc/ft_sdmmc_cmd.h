/*
 * @ : Copyright (c) 2020 Phytium Information Technology, Inc. 
 * The right to copy, distribute, modify, or otherwise make use 
 * of this software may be licensed only pursuant to the terms
 * of an applicable Phytium license agreement.
 * @Date: 2021-04-08 13:27:51
 * @LastEditTime: 2021-04-14 10:44:46
 * @Description:  This files is for 
 * 
 * @Modify History: 
 *  Ver   Who        Date         Changes
 * ----- ------     --------    --------------------------------------
 */

#ifndef _FT_SDMMC_CMD_H_
#define _FT_SDMMC_CMD_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include "ft_error_code.h"
#include "ft_sdmmc_defs.h"
#include "ft_sdmmc.h"

#define FILE  void

/**
 * Probe and initialize SD/MMC card using given host
 *
 * @note Only SD cards (SDSC and SDHC/SDXC) are supported now.
 *       Support for MMC/eMMC cards will be added later.
 *
 * @param host  pointer to structure defining host controller
 * @param out_card  pointer to structure which will receive information
 *                  about the card when the function completes
 * @return
 *      - ESP_OK on success
 *      - One of the error codes from SDMMC host controller
 */
ft_error_t Sdmmc_CardInit(const Sdmmc_Host_t* host,
        Sdmmc_Card_t* out_card);

/**
 * @brief Print information about the card to a stream
 * @param stream  stream obtained using fopen or fdopen
 * @param card  card information structure initialized using Sdmmc_CardInit
 */
void Sdmmc_CardPrintInfo(FILE* stream, const Sdmmc_Card_t* card);

/**
 * Write given number of sectors to SD/MMC card
 *
 * @param card  pointer to card information structure previously initialized
 *              using Sdmmc_CardInit
 * @param src   pointer to data buffer to read data from; data size must be
 *              equal to sector_count * card->csd.sectorSize
 * @param start_sector  sector where to start writing
 * @param sector_count  number of sectors to write
 * @return
 *      - ESP_OK on success
 *      - One of the error codes from SDMMC host controller
 */
ft_error_t Sdmmc_WriteSectors(Sdmmc_Card_t* card, const void* src,
        size_t start_sector, size_t sector_count);

/**
 * Write given number of sectors to SD/MMC card
 *
 * @param card  pointer to card information structure previously initialized
 *              using Sdmmc_CardInit
 * @param dst   pointer to data buffer to write into; buffer size must be
 *              at least sector_count * card->csd.sectorSize
 * @param start_sector  sector where to start reading
 * @param sector_count  number of sectors to read
 * @return
 *      - ESP_OK on success
 *      - One of the error codes from SDMMC host controller
 */
ft_error_t Sdmmc_ReadSectors(Sdmmc_Card_t* card, void* dst,
        size_t start_sector, size_t sector_count);

#ifdef __cplusplus
}
#endif

#endif