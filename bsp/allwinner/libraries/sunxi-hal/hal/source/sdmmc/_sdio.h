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

#ifndef _ROM_DRIVER_CHIP_SDMMC__SDIO_H_
#define _ROM_DRIVER_CHIP_SDMMC__SDIO_H_

#include "_core.h"

#ifdef __cplusplus
extern "C" {
#endif

/*
 * Standard SDIO Function Interfaces
 */

#define SDIO_CLASS_NONE     0x00    /* Not a SDIO standard interface */
#define SDIO_CLASS_UART     0x01    /* standard UART interface */
#define SDIO_CLASS_BT_A     0x02    /* Type-A BlueTooth std interface */
#define SDIO_CLASS_BT_B     0x03    /* Type-B BlueTooth std interface */
#define SDIO_CLASS_GPS      0x04    /* GPS standard interface */
#define SDIO_CLASS_CAMERA   0x05    /* Camera standard interface */
#define SDIO_CLASS_PHS      0x06    /* PHS standard interface */
#define SDIO_CLASS_WLAN     0x07    /* WLAN interface */
#define SDIO_CLASS_ATA      0x08    /* Embedded SDIO-ATA std interface */
#define SDIO_CLASS_BT_AMP   0x09    /* Type-A Bluetooth AMP interface */

extern uint32_t mmc_sdio_get_max_clock(struct mmc_card *card);
extern uint32_t sdio_reset(struct mmc_host *host);
extern int mmc_attach_sdio(struct mmc_card *card, struct mmc_host *host);
extern void mmc_deattach_sdio(struct mmc_card *card, struct mmc_host *host);

#ifdef __cplusplus
}
#endif

#endif /* _ROM_DRIVER_CHIP_SDMMC__SDIO_H_ */
