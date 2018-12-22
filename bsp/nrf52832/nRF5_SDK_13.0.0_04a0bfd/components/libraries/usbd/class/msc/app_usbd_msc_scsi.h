/**
 * Copyright (c) 2016 - 2017, Nordic Semiconductor ASA
 * 
 * All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 * 
 * 1. Redistributions of source code must retain the above copyright notice, this
 *    list of conditions and the following disclaimer.
 * 
 * 2. Redistributions in binary form, except as embedded into a Nordic
 *    Semiconductor ASA integrated circuit in a product or a software update for
 *    such product, must reproduce the above copyright notice, this list of
 *    conditions and the following disclaimer in the documentation and/or other
 *    materials provided with the distribution.
 * 
 * 3. Neither the name of Nordic Semiconductor ASA nor the names of its
 *    contributors may be used to endorse or promote products derived from this
 *    software without specific prior written permission.
 * 
 * 4. This software, with or without modification, must only be used with a
 *    Nordic Semiconductor ASA integrated circuit.
 * 
 * 5. Any software provided in binary form under this license must not be reverse
 *    engineered, decompiled, modified and/or disassembled.
 * 
 * THIS SOFTWARE IS PROVIDED BY NORDIC SEMICONDUCTOR ASA "AS IS" AND ANY EXPRESS
 * OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY, NONINFRINGEMENT, AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL NORDIC SEMICONDUCTOR ASA OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE
 * GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT
 * OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 * 
 */
#ifndef APP_USBD_MSC_SCSI_H__
#define APP_USBD_MSC_SCSI_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "app_util.h"

/**
 * @defgroup app_usbd_msc_scsi USB MSC SCSI data structures
 * @ingroup app_usbd_msc
 *
 * @brief @tagAPI52840 USB MSC SCSI data structures.
 *
 * @details Reference specifications:
 * - "Reduced Block Commands (Revision 10a)"  American National Standard
 *   for Information Technology, August 18, 1999
 * - "SCSI Primary Commands - 4 (SPC-4),"  American National Standard
 *   for Information Technology, July 19, 2008
 * - "SCSI Block Commands -2 (SBC-2)," American National Standard
 *   for Information Technology, November 13, 2004
 * - NuttX source code - Real-time Operating System: http://nuttx.org/
 *   Gregory Nutt <gnutt@nuttx.org>
 *
 * @{
 */

/**
 * @brief SCSI command set
 *
 * Mandatory (and some optional) commands required by SBC-2.
 *
 */
typedef enum {
    APP_USBD_SCSI_CMD_TESTUNITREADY       = 0x00, /**< TESTUNITREADY       */
    APP_USBD_SCSI_CMD_REQUESTSENSE        = 0x03, /**< REQUESTSENSE        */
    APP_USBD_SCSI_CMD_FORMAT_UNIT         = 0x04, /**< FORMAT_UNIT         */
    APP_USBD_SCSI_CMD_READ6               = 0x08, /**< READ6               */
    APP_USBD_SCSI_CMD_WRITE6              = 0x0a, /**< WRITE6              */
    APP_USBD_SCSI_CMD_INQUIRY             = 0x12, /**< INQUIRY             */
    APP_USBD_SCSI_CMD_MODESELECT6         = 0x15, /**< MODESELECT6         */
    APP_USBD_SCSI_CMD_MODESENSE6          = 0x1a, /**< MODESENSE6          */
    APP_USBD_SCSI_CMD_STARTSTOPUNIT       = 0x1b, /**< STARTSTOPUNIT       */
    APP_USBD_SCSI_CMD_SENDDIAGNOSTIC      = 0x1d, /**< SENDDIAGNOSTIC      */
    APP_USBD_SCSI_CMD_PREVENTMEDIAREMOVAL = 0x1e, /**< PREVENTMEDIAREMOVAL */
    APP_USBD_SCSI_CMD_READCAPACITY10      = 0x25, /**< READCAPACITY10      */
    APP_USBD_SCSI_CMD_READ10              = 0x28, /**< READ10              */
    APP_USBD_SCSI_CMD_WRITE10             = 0x2a, /**< WRITE10             */
    APP_USBD_SCSI_CMD_MODESELECT10        = 0x55, /**< MODESELECT10        */
    APP_USBD_SCSI_CMD_MODESENSE10         = 0x5a, /**< MODESENSE10         */
} app_usbd_scsi_cmd_t;


#pragma pack(push, 1)

/**
 * @brief Payload of @ref APP_USBD_SCSI_CMD_REQUESTSENSE command
 */
typedef struct {
    uint8_t opcode;        //!< @ref APP_USBD_SCSI_CMD_REQUESTSENSE
    uint8_t flags;         //!< Flags
    uint8_t reserved[2];   //!< Reserved
    uint8_t alloclen;      //!< Allocation length
    uint8_t control;       //!< Control
} app_usbd_scsi_cmd_requestsense_t;

#define APP_USBD_SCSI_CMD_REQSENSE_CODE_VALID          0x80 /**< @ref app_usbd_scsi_cmd_requestsense_resp_t::code */
#define APP_USBD_SCSI_CMD_REQSENSE_CODE_CURRENT        0x70 /**< @ref app_usbd_scsi_cmd_requestsense_resp_t::code */
#define APP_USBD_SCSI_CMD_REQSENSE_CODE_DEFERRED       0x71 /**< @ref app_usbd_scsi_cmd_requestsense_resp_t::code */
#define APP_USBD_SCSI_CMD_REQSENSE_CODE_CURRENTDESC    0x72 /**< @ref app_usbd_scsi_cmd_requestsense_resp_t::code */
#define APP_USBD_SCSI_CMD_REQSENSE_CODE_DEFERREDDESC   0x73 /**< @ref app_usbd_scsi_cmd_requestsense_resp_t::code */

#define APP_USBD_SCSI_CMD_REQSENSE_FLAG_FILEMARK       0x80 /**< Bits 7 @ref app_usbd_scsi_cmd_requestsense_resp_t::flags */
#define APP_USBD_SCSI_CMD_REQSENSE_FLAG_EOM            0x40 /**< Bits 6 @ref app_usbd_scsi_cmd_requestsense_resp_t::flags */
#define APP_USBD_SCSI_CMD_REQSENSE_FLAG_ILI            0x20 /**< Bits 5 @ref app_usbd_scsi_cmd_requestsense_resp_t::flags */
#define APP_USBD_SCSI_CMD_REQSENSE_FLAG_RESERVED       0x10 /**< Bits 4 @ref app_usbd_scsi_cmd_requestsense_resp_t::flags */

#define APP_USBD_SCSI_CMD_REQSENSE_FLAG_NOSENSE        0x00 /**< Bits 3...0 @ref app_usbd_scsi_cmd_requestsense_resp_t::flags */
#define APP_USBD_SCSI_CMD_REQSENSE_FLAG_RECOVEREDERROR 0x01 /**< Bits 3...0 @ref app_usbd_scsi_cmd_requestsense_resp_t::flags */
#define APP_USBD_SCSI_CMD_REQSENSE_FLAG_NOTREADY       0x02 /**< Bits 3...0 @ref app_usbd_scsi_cmd_requestsense_resp_t::flags */
#define APP_USBD_SCSI_CMD_REQSENSE_FLAG_MEDIUMERROR    0x03 /**< Bits 3...0 @ref app_usbd_scsi_cmd_requestsense_resp_t::flags */
#define APP_USBD_SCSI_CMD_REQSENSE_FLAG_HARDWAREERROR  0x04 /**< Bits 3...0 @ref app_usbd_scsi_cmd_requestsense_resp_t::flags */
#define APP_USBD_SCSI_CMD_REQSENSE_FLAG_ILLEGALREQUEST 0x05 /**< Bits 3...0 @ref app_usbd_scsi_cmd_requestsense_resp_t::flags */
#define APP_USBD_SCSI_CMD_REQSENSE_FLAG_UNITATTENTION  0x06 /**< Bits 3...0 @ref app_usbd_scsi_cmd_requestsense_resp_t::flags */
#define APP_USBD_SCSI_CMD_REQSENSE_FLAG_DATAPROTECT    0x07 /**< Bits 3...0 @ref app_usbd_scsi_cmd_requestsense_resp_t::flags */
#define APP_USBD_SCSI_CMD_REQSENSE_FLAG_BLANKCHECK     0x08 /**< Bits 3...0 @ref app_usbd_scsi_cmd_requestsense_resp_t::flags */
#define APP_USBD_SCSI_CMD_REQSENSE_FLAG_VENDORSPECIFIC 0x09 /**< Bits 3...0 @ref app_usbd_scsi_cmd_requestsense_resp_t::flags */
#define APP_USBD_SCSI_CMD_REQSENSE_FLAG_ABORTEDCOMMAND 0x0b /**< Bits 3...0 @ref app_usbd_scsi_cmd_requestsense_resp_t::flags */


#define APP_USBD_SCSI_CMD_TESTUNITREADY_LEN 6 /**< @ref APP_USBD_SCSI_CMD_TESTUNITREADY command length*/

/**
 * @brief Payload of @ref APP_USBD_SCSI_CMD_REQUESTSENSE response
 */
typedef struct {
    uint8_t code;          //!< Response code: APP_USBD_SCSI_CMD_REQSENSE_CODE_*
    uint8_t obsolete;      //!< Obsolete
    uint8_t flags;         //!< APP_USBD_SCSI_CMD_REQSENSE_FLAG_*
    uint8_t info[4];       //!< Information
    uint8_t len;           //!< Additional length
    uint8_t cmdinfo[4];    //!< Command-specific information
    uint8_t code2;         //!< Additional sense code
    uint8_t qual2;         //!< Additional sense code qualifier
    uint8_t fru;           //!< Field replacement unit code
    uint8_t key[3];        //!< Sense key specific
} app_usbd_scsi_cmd_requestsense_resp_t;

/**
 * @brief Payload of @ref APP_USBD_SCSI_CMD_INQUIRY command
 */
typedef struct {
    uint8_t opcode;        //!< @ref APP_USBD_SCSI_CMD_INQUIRY
    uint8_t flags;         //!< Command flags
    uint8_t pagecode;      //!< Page code
    uint8_t alloclen[2];   //!< Allocation length
    uint8_t control;       //!< Control
} app_usbd_scsi_cmd_inquiry_t;

#define  APP_USBD_MSC_SCSI_INQ_QUAL_CONNECTED   0x00   /**< Peripheral connected        */
#define  APP_USBD_MSC_SCSI_INQ_QUAL_NOT_CONN    0x20   /**< Peripheral not connected    */
#define  APP_USBD_MSC_SCSI_INQ_QUAL_NOT_SUPP    0x60   /**< Peripheral not supported    */

#define  APP_USBD_MSC_SCSI_INQ_TYPE_DIR_ACCESS  0x00   /**< Direct Access (SBC)         */
#define  APP_USBD_MSC_SCSI_INQ_TYPE_SEQ_ACCESS  0x01   /**< Sequential Access           */
#define  APP_USBD_MSC_SCSI_INQ_TYPE_PRINTER     0x02   /**< Printer                     */
#define  APP_USBD_MSC_SCSI_INQ_TYPE_PROCESSOR   0x03   /**< Processor device            */
#define  APP_USBD_MSC_SCSI_INQ_TYPE_WRITE_ONCE  0x04   /**< Write-once device           */
#define  APP_USBD_MSC_SCSI_INQ_TYPE_CD_DVD      0x05   /**< CD/DVD device               */
#define  APP_USBD_MSC_SCSI_INQ_TYPE_OPTICAL     0x07   /**< Optical Memory              */
#define  APP_USBD_MSC_SCSI_INQ_TYPE_MC          0x08   /**< Medium Changer              */
#define  APP_USBD_MSC_SCSI_INQ_TYPE_ARRAY       0x0c   /**< Storage Array Controller    */
#define  APP_USBD_MSC_SCSI_INQ_TYPE_ENCLOSURE   0x0d   /**< Enclosure Services          */
#define  APP_USBD_MSC_SCSI_INQ_TYPE_RBC         0x0e   /**< Simplified Direct Access    */
#define  APP_USBD_MSC_SCSI_INQ_TYPE_OCRW        0x0f   /**< Optical card reader/writer  */
#define  APP_USBD_MSC_SCSI_INQ_TYPE_BCC         0x10   /**< Bridge Controller Commands  */
#define  APP_USBD_MSC_SCSI_INQ_TYPE_OSD         0x11   /**< Object-based Storage        */
#define  APP_USBD_MSC_SCSI_INQ_TYPE_NONE        0x1f   /**< No Peripheral               */


#define  APP_USBD_MSC_SCSI_INQ_FLAG1_RMB        0x80   /**< Removable Medium */

#define  APP_USBD_SCSI_INQ_VER_NONE       0x00   /**< No standards conformance                 */
#define  APP_USBD_SCSI_INQ_VER_SPC        0x03   /**< SCSI Primary Commands     (link to SBC)  */
#define  APP_USBD_SCSI_INQ_VER_SPC2       0x04   /**< SCSI Primary Commands - 2 (link to SBC-2)*/
#define  APP_USBD_SCSI_INQ_VER_SPC3       0x05   /**< SCSI Primary Commands - 3 (link to SBC-2)*/
#define  APP_USBD_SCSI_INQ_VER_SPC4       0x06   /**< SCSI Primary Commands - 4 (link to SBC-3)*/

#define  APP_USBD_MSC_SCSI_INQ_FLAG2_NORMACA        0x20   /**< Normal ACA Supported         */
#define  APP_USBD_MSC_SCSI_INQ_FLAG2_HISUP          0x10   /**< Hierarchal LUN addressing    */
#define  APP_USBD_MSC_SCSI_INQ_FLAG2_RSP_SPC2       0x02   /**< SPC-2 / SPC-3 response format*/
/**
 * @brief Payload of @ref APP_USBD_SCSI_CMD_INQUIRY response
 */
typedef struct {
    uint8_t qualtype;      //!< Bits 5-7: Peripheral qualifier; Bits 0-4: Peripheral device type
    uint8_t flags1;        //!< Flags 1
    uint8_t version;       //!< Version
    uint8_t flags2;        //!< Flags 2
    uint8_t len;           //!< Additional length
    uint8_t flags3;        //!< Flags 3
    uint8_t flags4;        //!< Flags 4
    uint8_t flags5;        //!< Flags 5
    uint8_t vendorid[8];   //!< T10 Vendor Identification
    uint8_t productid[16]; //!< Product Identification
    uint8_t revision[4];   //!< Product Revision Level
} app_usbd_scsi_cmd_inquiry_resp_t;

/**
 * @brief Payload of @ref APP_USBD_SCSI_CMD_READ6 command
 */
typedef struct {
    uint8_t opcode;        //!< @ref APP_USBD_SCSI_CMD_READ6
    uint8_t mslba;         //!< Bits 5-7: reserved; Bits 0-6: MS Logical Block Address (LBA)
    uint8_t lslba[2];      //!< LS Logical Block Address (LBA)
    uint8_t xfrlen;        //!< Transfer length (in contiguous logical blocks)
    uint8_t control;       //!< Control
} app_usbd_scsi_cmd_read6_t;

/**
 * @brief Payload of @ref APP_USBD_SCSI_CMD_WRITE6 command
 */
typedef struct {
    uint8_t opcode;        //!< @ref APP_USBD_SCSI_CMD_WRITE6
    uint8_t mslba;         //!< Bits 5-7: reserved; Bits 0-6: MS Logical Block Address (LBA)
    uint8_t lslba[2];      //!< LS Logical Block Address (LBA)
    uint8_t xfrlen;        //!< Transfer length (in contiguous logical blocks)
    uint8_t control;       //!< Control
} app_usbd_scsi_cmd_write6_t;

/**
 * @brief Payload of @ref APP_USBD_SCSI_CMD_MODESENSE6 command
 */
typedef struct {
    uint8_t opcode;        //!<* @ref APP_USBD_SCSI_CMD_MODESENSE6
    uint8_t flags;         //!<* Flags
    uint8_t pcpgcode;      //!<* Bits 6-7: PC, bits 0-5: page code
    uint8_t subpgcode;     //!<* subpage code
    uint8_t alloclen;      //!<* Allocation length
    uint8_t control;       //!<* Control
} app_usbd_scsi_cmd_modesense6_t;

/**
 * @brief Payload of @ref APP_USBD_SCSI_CMD_MODESENSE6 response
 */
typedef struct {
    uint8_t mdlen;         //!< Mode data length
    uint8_t type;          //!< Medium type
    uint8_t param;         //!< Device-specific parameter
    uint8_t bdlen;         //!< Block descriptor length
} app_usbd_scsi_cmd_modesense6_resp_t;

/**
 * @brief Payload of @ref APP_USBD_SCSI_CMD_READCAPACITY10 command
 */
typedef struct {
    uint8_t opcode;        //!< @ref APP_USBD_SCSI_CMD_READCAPACITY10
    uint8_t reserved1;     //!< Reserved field
    uint8_t lba[4];        //!< Logical block address (LBA)
    uint8_t reserved2[2];  //!< Reserved field
    uint8_t pmi;           //!< Bits 1-7 Reserved; Bit 0: PMI
    uint8_t control;       //!< Control
} app_usbd_scsi_cmd_readcapacity10_t;

/**
 * @brief Payload of @ref APP_USBD_SCSI_CMD_READCAPACITY10 response
 */
typedef struct {
    uint8_t lba[4];        //!< Returned logical block address (LBA)
    uint8_t blklen[4];     //!< Logical block length (in bytes)
} app_usbd_scsi_cmd_readcapacity10_resp_t;

/**
 * @brief Payload of @ref APP_USBD_SCSI_CMD_READ10 command
 */
typedef struct {
    uint8_t opcode;        //!< @ref APP_USBD_SCSI_CMD_READ10
    uint8_t flags;         //!< Command flags
    uint8_t lba[4];        //!< Logical Block Address (LBA)
    uint8_t groupno;       //!< Bits 5-7: reserved; Bits 0-6: group number
    uint8_t xfrlen[2];     //!< Transfer length (in contiguous logical blocks)
    uint8_t control;       //!< Control
} app_usbd_scsi_cmd_read10_t;

/**
 * @brief Payload of @ref APP_USBD_SCSI_CMD_WRITE10 command
 */
typedef struct {
    uint8_t opcode;        //!< @ref APP_USBD_SCSI_CMD_WRITE10
    uint8_t flags;         //!< Command flags
    uint8_t lba[4];        //!< Logical Block Address (LBA)
    uint8_t groupno;       //!< Bits 5-7: reserved; Bits 0-6: group number
    uint8_t xfrlen[2];     //!< Transfer length (in contiguous logical blocks)
    uint8_t control;       //!< Control
} app_usbd_scsi_cmd_write10_t;

/**
 * @brief Payload of @ref APP_USBD_SCSI_CMD_MODESENSE10 command
 */
typedef struct {
  uint8_t opcode;        //!< @ref APP_USBD_SCSI_CMD_MODESENSE10
  uint8_t flags;         //!< Flags
  uint8_t pcpgcode;      //!< Bits 6-7: PC, bits 0-5: page code
  uint8_t subpgcode;     //!< Subpage code
  uint8_t reserved[3];   //!< Reserved
  uint8_t alloclen[2];   //!< Allocation length
  uint8_t control;       //!< Control
} app_usbd_scsi_cmd_modesense10_t;

/**
 * @brief Payload of @ref APP_USBD_SCSI_CMD_MODESENSE10 response
 */
typedef struct {
  uint8_t mdlen[2];      //!< Mode data length
  uint8_t type;          //!< Medium type
  uint8_t param;         //!< Device-specific parameter
  uint8_t reserved[2];   //!< Reserved
  uint8_t bdlen[2];      //!< Block descriptor length
} app_usbd_scsi_cmd_modesense10_resp_t;

#pragma pack(pop)

/** @} */

#ifdef __cplusplus
}
#endif

#endif /* APP_USBD_MSC_SCSI_H__ */
