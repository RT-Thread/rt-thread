/*!
    \file    msc_bbb.h
    \brief   definitions for the USB MSC BBB(bulk/bulk/bulk) protocol

    \version 2024-07-31, V1.1.0, firmware for GD32F5xx
*/

/*
    Copyright (c) 2024, GigaDevice Semiconductor Inc.

    Redistribution and use in source and binary forms, with or without modification, 
are permitted provided that the following conditions are met:

    1. Redistributions of source code must retain the above copyright notice, this 
       list of conditions and the following disclaimer.
    2. Redistributions in binary form must reproduce the above copyright notice, 
       this list of conditions and the following disclaimer in the documentation 
       and/or other materials provided with the distribution.
    3. Neither the name of the copyright holder nor the names of its contributors 
       may be used to endorse or promote products derived from this software without 
       specific prior written permission.

    THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" 
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED 
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. 
IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, 
INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT 
NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR 
PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, 
WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) 
ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY 
OF SUCH DAMAGE.
*/

#ifndef MSC_BBB_H
#define MSC_BBB_H

#include "usb_ch9_std.h"

#define BBB_CBW_SIGNATURE                 0x43425355U             /*!< MSC BBB CBW signature */
#define BBB_CSW_SIGNATURE                 0x53425355U             /*!< MSC BBB CSW signature */
#define BBB_CBW_LENGTH                    31U                     /*!< MSC BBB CBW length */
#define BBB_CSW_LENGTH                    13U                     /*!< MSC BBB CSW length */

typedef struct {
    uint32_t dCBWSignature;                /*!< CBW signature */
    uint32_t dCBWTag;                      /*!< CBW tag */
    uint32_t dCBWDataTransferLength;       /*!< CBW signature */
    uint8_t  bmCBWFlags;                   /*!< CBW flags */
    uint8_t  bCBWLUN;                      /*!< CBW LUN */
    uint8_t  bCBWCBLength;                 /*!< CBW length */
    uint8_t  CBWCB[16];                    /*!< CBW CB */
} msc_bbb_cbw;

typedef struct {
    uint32_t dCSWSignature;                /*!< CSW signature  */
    uint32_t dCSWTag;                      /*!< CSW tag */
    uint32_t dCSWDataResidue;              /*!< CSW data residue */
    uint8_t  bCSWStatus;                   /*!< CSW status */
} msc_bbb_csw;

/* CSW command status */
enum msc_csw_status {
    CSW_CMD_PASSED = 0U,                  /*!< CSW passed command status */
    CSW_CMD_FAILED,                       /*!< CSW failed command status */
    CSW_PHASE_ERROR                       /*!< CSW phase error status */
};

#endif /* MSC_BBB_H */
