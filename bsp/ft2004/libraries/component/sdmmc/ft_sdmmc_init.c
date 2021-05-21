/*
 * @ : Copyright (c) 2020 Phytium Information Technology, Inc. 
 * The right to copy, distribute, modify, or otherwise make use 
 * of this software may be licensed only pursuant to the terms
 * of an applicable Phytium license agreement.
 * @Date: 2021-04-08 11:51:14
 * @LastEditTime: 2021-04-14 15:49:12
 * @Description:  This files is for sdmmc init process
 * 
 * @Modify History: 
 *  Ver   Who        Date         Changes
 * ----- ------     --------    --------------------------------------
 */

#include <string.h>
#include "ft_assert.h"
#include "ft_sdmmc.h"
#include "ft_sdmmc_defs.h"
#include "ft_sdmmc_common.h"

#define SDMMC_INIT_STEP(condition, function) \
    do { \
        if ((condition)) { \
            ft_error_t err = (function)(card); \
            if (err != ERR_SDMMC_OK) { \
                FT_SDMMC_DEBUG_E("init failed at %s %d: returned 0x%x", #function, __LINE__, err); \
                return err; \
            } \
        } \
    } while(0);

void Sdmmc_cardSetSDMem(Sdmmc_Card_t* card)
{
    card->is_ddr = FALSE;
    card->is_mem = TRUE;
    card->is_mmc = FALSE;
    card->is_sdio = FALSE;
    card->log_bus_width = 2;
}

ft_error_t Sdmmc_CardInit(const Sdmmc_Host_t* config, Sdmmc_Card_t* card)
{
    memset(card, 0, sizeof(*card));
    memcpy(&card->host, config, sizeof(*config));
    const bool_t is_spi = FALSE/*Sdmmc_IsHostSpi(card)*/;
    const bool_t always = TRUE;
    const bool_t io_supported = FALSE;
    const bool_t is_mmc = FALSE;
    const bool_t is_sdmem = TRUE;
    const bool_t is_mem = TRUE;
    const bool_t is_sdio = FALSE;

    Sdmmc_cardSetSDMem(card);

    /* Check if host flags are compatible with slot configuration. */
    //SDMMC_INIT_STEP(!is_spi, Sdmmc_FixHostFlags);
    SDMMC_INIT_STEP(always, Sdmmc_FixHostFlags);

    /* Reset SDIO (CMD52, RES) before re-initializing IO (CMD5). */
    //SDMMC_INIT_STEP(io_supported, sdmmc_io_reset);

    /* GO_IDLE_STATE (CMD0) command resets the card */
    SDMMC_INIT_STEP(always, Sdmmc_SendCmdGoIdleState);

    /* SEND_IF_COND (CMD8) command is used to identify SDHC/SDXC cards. */
    SDMMC_INIT_STEP(always, Sdmmc_InitSdIfCond);

    /* IO_SEND_OP_COND(CMD5), Determine if the card is an IO card. */
    //SDMMC_INIT_STEP(io_supported, sdmmc_init_io);

    // const bool_t is_mem = card->is_mem;
    // const bool_t is_sdio = !is_mem;

    /* Enable CRC16 checks for data transfers in SPI mode */
    SDMMC_INIT_STEP(is_spi, Sdmmc_InitSpiCrc);

    /* Use SEND_OP_COND to set up card OCR */
    SDMMC_INIT_STEP(is_mem, Sdmmc_InitOCR);

    // const bool_t is_mmc = is_mem && card->is_mmc;
    // const bool_t is_sdmem = is_mem && !is_mmc;

    // FT_SDMMC_DEBUG_D("%s: card type is %s", __func__,
    //         is_sdio ? "SDIO" : is_mmc ? "MMC" : "SD");

    /* Read the contents of CID register*/
    SDMMC_INIT_STEP(is_mem, Sdmmc_InitCID);

    /* Assign RCA */
    SDMMC_INIT_STEP(!is_spi, Sdmmc_InitRCA);
    FT_SDMMC_DEBUG_D("finish assign rca!!");

    /* Read and decode the contents of CSD register */
    SDMMC_INIT_STEP(is_mem, Sdmmc_InitCSD);

    /* Decode the contents of mmc CID register */
    SDMMC_INIT_STEP(is_mmc && !is_spi, Sdmmc_InitMMCDecodeCID);

    /* Switch the card from stand-by mode to data transfer mode (not needed if
     * SPI interface is used). This is needed to issue SET_BLOCKLEN and
     * SEND_SCR commands.
     */
    SDMMC_INIT_STEP(!is_spi, Sdmmc_InitSelectCard);

    /* SD memory cards:
     * Set block len for SDSC cards to 512 bytes (same as SDHC)
     * Read SCR
     * Wait to enter data transfer state
     */
    SDMMC_INIT_STEP(is_sdmem, Sdmmc_InitSdBlkLen);

    /* Switch to high speed before one need to fetch data from SD Card */
    SDMMC_INIT_STEP(is_sdmem, Sdmmc_InitSwitchHs);

    SDMMC_INIT_STEP(is_sdmem, Sdmmc_InitSdSCR);
    //SDMMC_INIT_STEP(is_sdmem, Sdmmc_InitSdWaitDataReady);

    // /* MMC cards: read CXD */
    // SDMMC_INIT_STEP(is_mmc, Sdmmc_InitMMCReadExtCSD);

    // /* Try to switch card to HS mode if the card supports it.
    //  * Set card->max_freq_khz value accordingly.
    //  */
    SDMMC_INIT_STEP(always, Sdmmc_InitCardHsMode);

    // /* Set bus width. One call for every kind of card, then one for the host */
    if (!is_spi) {
        //SDMMC_INIT_STEP(is_sdmem, Sdmmc_InitSdBusWidth);
        //SDMMC_INIT_STEP(is_sdio, sdmmc_init_io_bus_width);
        //SDMMC_INIT_STEP(is_mmc, Sdmmc_InitMMCBusWidth);
        //SDMMC_INIT_STEP(always, Sdmmc_InitHostBusWidth);
    }

    // /* Switch to the host to use card->max_freq_khz frequency. */
    //SDMMC_INIT_STEP(always, Sdmmc_InitHostFreq);

    // /* Sanity check after switching the bus mode and frequency */
    // FT_SDMMC_DEBUG_D("before check sd scr");
    // SDMMC_INIT_STEP(is_sdmem, Sdmmc_CheckSCR);
    // FT_SDMMC_DEBUG_D("after check sd scr");
    // /* TODO: this is CMD line only, add data checks for eMMC */
    // //SDMMC_INIT_STEP(is_mmc, Sdmmc_InitMMCCheckCSD);
    // /* TODO: add similar checks for SDIO */

    return ERR_SDMMC_OK;
}

