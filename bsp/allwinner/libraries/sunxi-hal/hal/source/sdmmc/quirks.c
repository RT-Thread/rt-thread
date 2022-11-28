/*
 * Copyright (C) 2017 ALLWINNERTECH TECHNOLOGY CO., LTD. All rights reserved.
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions
 *  are met:
 *    1. Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *    2. Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the
 *       distribution.
 *    3. Neither the name of ALLWINNERTECH TECHNOLOGY CO., LTD. nor the names of
 *       its contributors may be used to endorse or promote products derived
 *       from this software without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 *  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 *  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 *  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 *  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 *  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 *  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 *  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 *  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 *  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 *  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include "string.h" /* for strncmp() */

#include "card.h"

#include "_core.h"

#ifdef CONFIG_USE_MMC_QUIRK

#ifndef SDIO_VENDOR_ID_TI
#define SDIO_VENDOR_ID_TI       0x0097
#endif

#ifndef SDIO_DEVICE_ID_TI_WL1271
#define SDIO_DEVICE_ID_TI_WL1271    0x4076
#endif

#ifndef SDIO_VENDOR_ID_XR
#define SDIO_VENDOR_ID_XR       0x0020
#endif

#ifndef SDIO_DEVICE_ID_XRADIO
#define SDIO_DEVICE_ID_XRADIO   0x2281
#endif

static const struct mmc_fixup mmc_fixup_methods[] = {
    /* by default sdio devices are considered CLK_GATING broken */
    /* good cards will be whitelisted as they are tested */
    SDIO_FIXUP(SDIO_ANY_ID, SDIO_ANY_ID, add_quirk_for_sdio_devices,
           MMC_QUIRK_BROKEN_CLK_GATING),

    SDIO_FIXUP(SDIO_VENDOR_ID_TI, SDIO_DEVICE_ID_TI_WL1271,
           remove_quirk, MMC_QUIRK_BROKEN_CLK_GATING),

    SDIO_FIXUP(SDIO_VENDOR_ID_TI, SDIO_DEVICE_ID_TI_WL1271,
           add_quirk, MMC_QUIRK_NONSTD_FUNC_IF),

    SDIO_FIXUP(SDIO_VENDOR_ID_TI, SDIO_DEVICE_ID_TI_WL1271,
           add_quirk, MMC_QUIRK_DISABLE_CD),

    SDIO_FIXUP(SDIO_VENDOR_ID_XR, SDIO_DEVICE_ID_XRADIO,
           add_quirk, MMC_QUIRK_BROKEN_BYTE_MODE_512),

    END_FIXUP
};

void mmc_fixup_device(struct mmc_card *card, const struct mmc_fixup *table)
{
    const struct mmc_fixup *f;
    uint64_t rev = cid_rev_card(card);

    /* Non-core specific workarounds. */
    if (!table)
        table = mmc_fixup_methods;

    for (f = table; f->vendor_fixup; f++) {
        if ((f->manfid == CID_MANFID_ANY ||
             f->manfid == card->cid.manfid) &&
            (f->oemid == CID_OEMID_ANY ||
             f->oemid == card->cid.oemid) &&
            (f->name == CID_NAME_ANY ||
             !strncmp(f->name, card->cid.prod_name,
                  sizeof(card->cid.prod_name))) &&
            (f->cis_vendor == card->cis.vendor ||
             f->cis_vendor == (uint16_t) SDIO_ANY_ID) &&
            (f->cis_device == card->cis.device ||
             f->cis_device == (uint16_t) SDIO_ANY_ID) &&
            rev >= f->rev_start && rev <= f->rev_end) {
            SD_LOGD("%s calling %pF\n", __func__, f->vendor_fixup);
            f->vendor_fixup(card, f->data);
        }
    }
}
#endif
