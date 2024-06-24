/*
 * Copyright 2021 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

#ifndef FSL_FLASH_FFR_H_
#define FSL_FLASH_FFR_H_

#include "fsl_flash.h"

/*!
 * @addtogroup flash_ffr_driver
 * @{
 */

/*! @file */

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*! @brief Alignment(down) utility. */
#if !defined(ALIGN_DOWN)
#define ALIGN_DOWN(x, a) ((x) & (uint32_t)(-((int32_t)(a))))
#endif

/*! @brief Alignment(up) utility. */
#if !defined(ALIGN_UP)
#define ALIGN_UP(x, a) (-((int32_t)((uint32_t)(-((int32_t)(x))) & (uint32_t)(-((int32_t)(a))))))
#endif

#define FLASH_FFR_MAX_PAGE_SIZE    (512u)
#define FLASH_FFR_CUST_ADDRESS     (0x200U)
#define FLASH_FFR_CUST_PAGE_NUMBER (15u)

#define FLASH_FFR_HASH_DIGEST_SIZE (32u)
#define FLASH_FFR_IV_CODE_SIZE     (52u)
#define FLASH_FFR_KETBLOB_OFFSET   (0x160u)
#define FLASH_FFR_KETBLOB_SIZE     (0x30u)
#define CFPA_HEADER_MARKER         (0x9635u)
#define CMPA_HEADER_MARKER         (0x5963u)
#define FLASH_FFR_UUID_SIZE        (16u)
enum flash_ffr_page_offset
{
    kFfrPageOffset_CFPA            = 0,   /*!< Customer In-Field programmed area*/
    kFfrPageOffset_CFPA_CfgPing    = 0,   /*!< CFPA Configuration area (Ping page)*/
    kFfrPageOffset_CFPA_CfgPong    = 1,   /*!< Same as CFPA page (Pong page)*/
    kFfrPageOffset_CMPA_Cfg        = 2,   /*!< Customer Manufacturing programmed area*/
    kFfrPageOffset_NMPA_Cfg        = 3,   /*!< Customer Manufacturing programmed area*/
    kFfrPageOffset_SBL_Cfg         = 4,   /*!< SBL recovery programmed area*/
    kFfrPageOffset_B0_IFR1_Visible = 128, /*!< Trim programmed area*/

};

enum flash_ffr_page_num
{
    kFfrSectorNum_CFPA  = 2, /*!< Customer In-Field programmed area*/
    kFfrSectorNum_CMPA  = 1, /*!< Customer Manufacturing programmed area*/
    kFfrSectorNum_NMPA  = 1, /*!< NXP Manufacturing programmed area*/
    kFfrSectorNum_SBL   = 4, /*!< SBL Cus programmed area*/
    kFfrSectorNum_Total = (kFfrSectorNum_CFPA + kFfrSectorNum_CMPA + kFfrSectorNum_NMPA + kFfrSectorNum_SBL),
};

enum flash_ffr_block_size
{
    kFfrBlockSize_Key            = 52u,
    kFfrBlockSize_ActivationCode = 1000u,
};

enum cfpa_cfg_cmpa_prog_status
{
    kFfrCmpaProgStatus_Idle       = 0x0u,
    kFfrCmpaProgStatus_InProgress = 0x5CC55AA5u,
};

typedef enum
{
    kFfrCmpaProgProcess_Pre  = 0x0u,
    kFfrCmpaProgProcess_Post = 0xFFFFFFFFu,
} cmpa_prog_process_t;

typedef struct
{
    struct
    {
        uint32_t cfpa_lc_state : 8;
        uint32_t cfpa_lc_state_inv : 8;
        uint32_t header_marker : 16;
    } header; /*!< [0x000-0x003]*/

    struct /*!< [0x004-0x007]*/
    {
        uint32_t version : 24; /*!< cfpa version*/
        uint32_t img_upd : 2;  /*!< image cmac update*/
        uint32_t reserved0 : 1;
        uint32_t cmpa_update : 3; /*!< CFPA page updated through SB command.*/
        uint32_t reserved1 : 1;
        uint32_t dice_en : 1; /*!< Update DICE certificate during next boot*/
    } cfpa_page_version;

    uint32_t secureFwVersion; /*!< [0x008-0x00b]*/
    uint32_t nsFwVersion;     /*!< [0x00c-0x00f]*/
    uint32_t recFwVersion;    /*!< [0x010-0x013]*/
    uint32_t secBootFlags;    /*!< [0x014-0x01f]*/
    uint32_t imageKeyRevoke;  /*!< [0x018-0x01b]*/
    uint32_t lpVectorAddr;    /*!< [0x01c-0x01f]*/
    uint32_t vendorUsage;     /*!< [0x020-0x02f]*/
    uint32_t dcfgNsPin;       /*!< [0x024-0x027]*/
    uint32_t dcfgNsDflt;      /*!< [0x028-0x02b]*/
    uint32_t reserved0;       /*!< [0x02c-0x02f]*/
    uint32_t ivPrince[4];     /*!< [0x030-0x03f]*/
    uint32_t ivIped[8];       /*!< [0x040-0x05f]*/

    uint32_t errCnt[8]; /*!< [0x060-0x07f]*/

    uint32_t custCtr[8];     /*!< [0x080-0x09f]*/
    uint32_t mflagCtr[8];    /*!< [0x0a0-0x0bf]*/
    uint32_t flashAcl[8];    /*!< [0x0C0-0x0Df]*/
    uint32_t sblImg0Cmac[4]; /*!< [0x0E0-0x0Ef]*/
    uint32_t img1Cmac[4];    /*!< [0x0F0-0x0Ff]*/
    uint32_t diceCert[36];   /*!< [0x100-0x18f]*/
    uint32_t reserved2[23];  /*!< [0x190-0x1eb]*/
    uint32_t cfpaCrc;        /*!< [0x1ec-0x1ef]*/
    uint32_t cfpaCmac[4];    /*!< [0x1f0-0x1ff]*/
} cfpa_cfg_info_t;

#define FFR_BOOTCFG_USBSPEED_SHIFT    (9U)
#define FFR_BOOTCFG_USBSPEED_MASK     (0x3u << FFR_BOOTCFG_USBSPEED_SHIFT)
#define FFR_BOOTCFG_USBSPEED_NMPASEL0 (0x0U)
#define FFR_BOOTCFG_USBSPEED_FS       (0x1U)
#define FFR_BOOTCFG_USBSPEED_HS       (0x2U)
#define FFR_BOOTCFG_USBSPEED_NMPASEL3 (0x3U)

#define FFR_BOOTCFG_BOOTSPEED_MASK    (0x18U)
#define FFR_BOOTCFG_BOOTSPEED_SHIFT   (7U)
#define FFR_BOOTCFG_BOOTSPEED_NMPASEL (0x0U)
#define FFR_BOOTCFG_BOOTSPEED_48MHZ   (0x1U)
#define FFR_BOOTCFG_BOOTSPEED_96MHZ   (0x2U)

#define FFR_USBID_VENDORID_MASK   (0xFFFFU)
#define FFR_USBID_VENDORID_SHIFT  (0U)
#define FFR_USBID_PRODUCTID_MASK  (0xFFFF0000U)
#define FFR_USBID_PRODUCTID_SHIFT (16U)

#define FFR_IMAGE0_CMAC_UPDATE_MASK (0x1)
#define FFR_IMAGE1_CMAC_UPDATE_MASK (0x2)

#define FFR_IFR1_PUF_AC_CODE_ADDR (0x01100200UL)
#define FFR_IFR1_PUF_AC_CODE_LEN  (1024UL)

#define FFR_IFR1_NXP_CERT_ADDR (0x01100600UL)
#define FFR_IFR1_NXP_CERT_LEN  (1448UL)

#define FFR_IFR1_ROM_PATCH_ARRAY0_ADDR (0x01101900UL)
#define FFR_IFR1_ROM_PATCH_ARRAY0_LEN  (1792UL)

#define FFR_IFR1_ROM_PATCH_ARRAY1_ADDR (0x01102000UL)
#define FFR_IFR1_ROM_PATCH_ARRAY1_LEN  (3584UL)

#define FFR_IFR1_ROM_PATCH_ARRAY2_ADDR (0x01103000UL)
#define FFR_IFR1_ROM_PATCH_ARRAY2_LEN  (2048UL)

#define FFR_IFR1_ROM_PATCH_ARRAY3_ADDR (0x01103800UL)
#define FFR_IFR1_ROM_PATCH_ARRAY3_LEN  (2048UL)

#define FFR_IFR1_NXP_WRITEABLE_REGION0_START (FFR_IFR1_PUF_AC_CODE_ADDR)
#define FFR_IFR1_NXP_WRITEABLE_REGION0_END \
    (FFR_IFR1_PUF_AC_CODE_ADDR + FFR_IFR1_PUF_AC_CODE_LEN + FFR_IFR1_NXP_CERT_LEN)
#define FFR_IFR1_NXP_WRITEABLE_REGION1_START (FFR_IFR1_ROM_PATCH_ARRAY0_ADDR)
#define FFR_IFR1_NXP_WRITEABLE_REGION1_END \
    (FFR_IFR1_ROM_PATCH_ARRAY0_ADDR + FFR_IFR1_ROM_PATCH_ARRAY0_LEN + FFR_IFR1_ROM_PATCH_ARRAY1_LEN)
#define FFR_IFR1_NXP_WRITEABLE_REGION2_START (FFR_IFR1_ROM_PATCH_ARRAY2_ADDR)
#define FFR_IFR1_NXP_WRITEABLE_REGION2_END \
    (FFR_IFR1_ROM_PATCH_ARRAY2_ADDR + FFR_IFR1_ROM_PATCH_ARRAY2_LEN + FFR_IFR1_ROM_PATCH_ARRAY3_LEN)

typedef struct
{
    struct
    {
        uint32_t boot_src : 2;
        uint32_t rsv0 : 2;
        uint32_t isp_boot_if : 3;
        uint32_t rsv1 : 1;
        uint32_t rec_boot_src : 2;
        uint32_t rsv2 : 2;
        uint32_t boot_speed : 2;
        uint32_t rsv3 : 2;
        uint32_t header_marker : 16;
    } bootCfg; /*!< [0x000-0x003]*/

    struct
    {
        uint32_t flash_remap_size : 5;
        uint32_t bank1_ifr0_usage : 3;
        uint32_t reserved : 24;
    } FlashCfg; /*!< [0x004-0x007]*/

    struct
    {
        uint8_t recLed;
        uint8_t ispLed;
        uint8_t bootFailLed;
        uint8_t resv0;
    } bootLedStatus; /*!< [0x008-0x00b]*/

    struct
    {
        uint16_t powerDnTimeout;
        uint16_t wdogTimeout;
    } bootTimers; /*!< [0x00c-0x00f]*/

    uint32_t resv2; /*!< [0x010-0x013]*/
    uint32_t resv3; /*!< [0x014-0x017]*/

    uint32_t recSpiFlashCfg0; /*!< [0x018-0x01b]*/
    uint32_t recSpiFlashCfg1; /*!< [0x01c-0x01f]*/

    uint32_t isp_uart_cfg; /*!< [0x020-0x023]*/
    uint32_t isp_i2c_cfg;  /*!< [0x024-0x027]*/
    uint32_t isp_can_cfg;  /*!< [0x028-0x02b]*/
    uint32_t isp_spi_cfg0; /*!< [0x02c-0x02f]*/
    uint32_t isp_spi_cfg1; /*!< [0x030-0x034]*/

    struct
    {
        uint16_t vid;
        uint16_t pid;
    } usbId; /*!< [0x034-0x037]*/

    uint32_t isp_usb_cfg;    /*!< [0x038-0x038]*/
    uint32_t isp_misc_cfg;   /*!< [0x03c-0x03f]*/
    uint32_t dcfgPin;        /*!< [0x040-0x043]*/
    uint32_t dcfgDflt;       /*!< [0x044-0x047]*/
    uint32_t dapVendorUsage; /*!< [0x048-0x04b]*/
    uint32_t resv1;          /*!< [0x04c-0x04f]*/
    uint32_t secureBootCfg;  /*!< [0x050-0x053]*/
    uint32_t rokthUsage;     /*!< [0x054-0x057]*/
    uint32_t resv4;          /*!< [0x058-0x05b]*/
    uint32_t resv5;          /*!< [0x05c-0x05f]*/
    uint32_t rotkh[12];      /*!< [0x060-0x08f]*/

    struct
    {
        uint32_t npx_w0;
        uint32_t npx_w1;
    } princeSr[4]; /*!< [0x090-0x0af]*/

    struct
    {
        uint32_t ipedStartAddr;
        uint32_t ipedEndAddr;
    } ipedRegions[8]; /*!< [0x0b0-0x11f]*/

    uint32_t rec_img_exit0;
    uint32_t rec_img_exit1;

    uint32_t resv6[10];

    struct
    {
        uint32_t set0;
        uint32_t clr0;
    } quickSetGpio[6]; /*!< [0x120-0x14f]*/

    uint32_t resv7[4];          /*!< [0x150-0x15f]*/
    uint32_t cust_key_blob[12]; /*!< [0x160-0x18f]*/

    uint32_t resv8[23];   /*!< [0x190-0x1eb]*/
    uint32_t cmpaCrc;     /*!< [0x1ec-0x1ef]*/
    uint32_t cmpaCmac[4]; /*!< [0x1f0-0x1ff]*/

} cmpa_cfg_info_t;

typedef struct
{
    uint32_t header;
    uint8_t reserved[4];
} cmpa_key_store_header_t;

#define FFR_SYSTEM_SPEED_CODE_MASK             (0x3U)
#define FFR_SYSTEM_SPEED_CODE_SHIFT            (0U)
#define FFR_SYSTEM_SPEED_CODE_FRO12MHZ_12MHZ   (0x0U)
#define FFR_SYSTEM_SPEED_CODE_FROHF96MHZ_24MHZ (0x1U)
#define FFR_SYSTEM_SPEED_CODE_FROHF96MHZ_48MHZ (0x2U)
#define FFR_SYSTEM_SPEED_CODE_FROHF96MHZ_96MHZ (0x3U)

#define FFR_USBCFG_USBSPEED_HS (0x0U)
#define FFR_USBCFG_USBSPEED_FS (0x1U)
#define FFR_USBCFG_USBSPEED_NO (0x2U)

#define FFR_MCAN_BAUDRATE_MASK  (0xF0000U)
#define FFR_MCAN_BAUDRATE_SHIFT (16U)

#define FFR_PERIPHERALCFG_PERI_MASK    (0x7FFFFFFFU)
#define FFR_PERIPHERALCFG_PERI_SHIFT   (0U)
#define FFR_PERIPHERALCFG_COREEN_MASK  (0x10000000U)
#define FFR_PERIPHERALCFG_COREEN_SHIFT (31U)

#define FFR_PUF_SRAM_CONFIG_MASK       (0x3FFFF07)
#define FFR_PUF_SRAM_CONFIG_MASK_SHIFT (0U)
#define FFR_PUF_SRAM_VALID_MASK        (0x1U)
#define FFR_PUF_SRAM_VALID_SHIFT       (0U)
#define FFR_PUF_SRAM_MODE_MASK         (0x2U)
#define FFR_PUF_SRAM_MODE_SHIFT        (1U)
#define FFR_PUF_SRAM_CKGATING_MASK     (0x4U)
#define FFR_PUF_SRAM_CKGATING_SHIFT    (2)
#define FFR_PUF_SRAM_SMB_MASK          (0x300U)
#define FFR_PUF_SRAM_SMB_SHIFT         (8U)
#define FFR_PUF_SRAM_RM_MASK           (0x1C00U)
#define FFR_PUF_SRAM_RM_SHIFT          (10U)
#define FFR_PUF_SRAM_WM_MASK           (0xE000U)
#define FFR_PUF_SRAM_WM_SHIFT          (13U)
#define FFR_PUF_SRAM_WRME_MASK         (0x10000U)
#define FFR_PUF_SRAM_WRME_SHIFT        (16U)
#define FFR_PUF_SRAM_RAEN_MASK         (0x20000U)
#define FFR_PUF_SRAM_RAEN_SHIFT        (17U)
#define FFR_PUF_SRAM_RAM_MASK          (0x3C0000U)
#define FFR_PUF_SRAM_RAM_SHIFT         (18U)
#define FFR_PUF_SRAM_WAEN_MASK         (0x400000U)
#define FFR_PUF_SRAM_WAEN_SHIFT        (22U)
#define FFR_PUF_SRAM_WAM_MASK          (0x1800000U)
#define FFR_PUF_SRAM_WAM_SHIFT         (23U)
#define FFR_PUF_SRAM_STBP_MASK         (0x2000000U)
#define FFR_PUF_SRAM_STBP_SHIFT        (25U)

typedef struct
{
    uint32_t fro32kCfg;             /*!< [0x000-0x003]*/
    uint32_t puf_cfg;               /*!< [0x004-0x007]*/
    uint32_t bod;                   /*!< [0x008-0x00b]*/
    uint32_t trim;                  /*!< [0x00c-0x00f]*/
    uint32_t deviceID;              /*!< [0x010-0x03f]*/
    uint32_t peripheralCfg;         /*!< [0x014-0x017]*/
    uint32_t dcdPowerProFileLOW[2]; /*!< [0x018-0x01f]*/
    uint32_t deviceType;            /*!< [0x020-0x023]*/
    uint32_t ldo_ao;                /*!< [0x024-0x027]*/
    uint32_t gdetDelayCfg;          /*!< [0x028-0x02b]*/
    uint32_t gdetMargin;            /*!< [0x02c-0x02f]*/
    uint32_t gdetTrim1;             /*!< [0x030-0x033]*/
    uint32_t gdetEanble1;           /*!< [0x034-0x037]*/
    uint32_t gdetCtrl1;             /*!< [0x038-0x03b]*/
    uint32_t gdetUpdateTimer;       /*!< [0x03c-0x03f]*/
    uint32_t GpoDataChecksum[4];    /*!< [0x040-0x04f]*/
    uint32_t finalTestBatchId[4];   /*!< [0x050-0x05f]*/
    uint32_t ecidBackup[4];         /*!< [0x060-0x06f]*/
    uint32_t uuid[4];               /*!< [0x070-0x07f]*/
    uint32_t reserved1[7];          /*!< [0x080-0x09b]*/
    struct
    {
        uint8_t xo32mReadyTimeoutInMs;
        uint8_t usbSpeed;
        uint8_t reserved[2];
    } usbCfg;                 /*!< [0x09c-0x09f]*/
    uint32_t reserved2[80];   /*!< [0x0a0-0x1df]*/
    uint8_t cmac[16];         /*!< [0x1e0-0x1ef]*/
    uint32_t pageChecksum[4]; /*!< [0x1f0-0x1ff]*/
} nmpa_cfg_info_t;

typedef struct
{
    uint8_t reserved[1][FLASH_FFR_MAX_PAGE_SIZE];
} ffr_key_store_t;

typedef enum
{
    kFFR_KeyTypeSbkek         = 0x00U,
    kFFR_KeyTypeUser          = 0x01U,
    kFFR_KeyTypeUds           = 0x02U,
    kFFR_KeyTypePrinceRegion0 = 0x03U,
    kFFR_KeyTypePrinceRegion1 = 0x04U,
    kFFR_KeyTypePrinceRegion2 = 0x05U,
} ffr_key_type_t;

typedef enum
{
    kFFR_BankTypeBank0_CFPA0 = 0x00u,
    kFFR_BankTypeBank0_CFPA1 = 0x01u,
    kFFR_BankTypeBank0_CMPA  = 0x02U,
    kFFR_BankTypeBank0_NMPA  = 0x03U,
    kFFR_BankTypeBank0_SBL   = 0x04U,

} ffr_bank_type_t;

/*******************************************************************************
 * API
 ******************************************************************************/

#if defined(__cplusplus)
extern "C" {
#endif

/*!
 * @name FFR APIs
 * @{
 */

/*!
 * @brief Initializes the global FFR properties structure members.
 *
 * @param config A pointer to the storage for the driver runtime state.
 *
 * @retval #kStatus_FLASH_Success API was executed successfully.
 */
status_t FFR_Init(flash_config_t *config);

/*!
 * @brief Enable firewall for all flash banks.
 *
 * CFPA, CMPA, and NMPA flash areas region will be locked, After this function executed;
 * Unless the board is reset again.
 *
 * @param config A pointer to the storage for the driver runtime state.
 *
 * @retval #kStatus_FLASH_Success An invalid argument is provided.
 */
status_t FFR_Lock(flash_config_t *config);

/*!
 * @brief APIs to access CFPA pages
 *
 * This routine will erase CFPA and program the CFPA page with passed data.
 *
 * @param config A pointer to the storage for the driver runtime state.
 * @param page_data A pointer to the source buffer of data that is to be programmed
 *        into the CFPA.
 * @param valid_len The length, given in bytes, to be programmed.
 *
 * @retval #kStatus_FLASH_Success The desire page-data were programed successfully into CFPA.
 * @retval #kStatus_FLASH_SizeError Error size
 * @retval #kStatus_FLASH_ReadHidingAreaDisallowed Flash hiding read is not allowed
 * @retval #kStatus_FLASH_AlignmentError Parameter is not aligned with the specified baseline
 * @retval #kStatus_FLASH_ModifyProtectedAreaDisallowed Flash firewall page locked erase and program are not allowed
 * @retval #kStatus_FLASH_InvalidArgument An invalid argument is provided.
 * @retval #kStatus_FTFx_AddressError Address is out of range.
 * @retval #kStatus_FLASH_FfrBankIsLocked The CFPA was locked.
 * @retval #kStatus_FLASH_OutOfDateCfpaPage It is not newest CFPA page.
 * @retval #kStatus_FLASH_CommandFailure access error.
 * @retval #kStatus_FLASH_CommandNotSupported Flash API is not supported
 * @retval #kStatus_FLASH_EccError A correctable or uncorrectable error during command execution.
 * @retval #kStatus_FLASH_RegulationLoss A loss of regulation during read.
 */
status_t FFR_InfieldPageWrite(flash_config_t *config, uint8_t *page_data, uint32_t valid_len);

/*!
 * @brief APIs to access CFPA pages
 *
 * Generic read function, used by customer to read data stored in 'Customer In-field Page'.
 *
 * @param config A pointer to the storage for the driver runtime state.
 * @param pData A pointer to the dest buffer of data that is to be read from 'Customer In-field Page'.
 * @param offset An offset from the 'Customer In-field Page' start address.
 * @param len The length, given in bytes, to be read.
 *
 * @retval #kStatus_FLASH_Success Get data from 'Customer In-field Page'.
 * @retval #kStatus_FLASH_InvalidArgument An invalid argument is provided.
 * @retval #kStatus_FTFx_AddressError Address is out of range.
 * @retval #kStatus_FLASH_AlignmentError Parameter is not aligned with the specified baseline.
 * @retval #kStatus_FLASH_ReadHidingAreaDisallowed Flash hiding read is not allowed
 * @retval #kStatus_FLASH_CommandFailure access error.
 * @retval #kStatus_FLASH_CommandNotSupported Flash API is not supported
 * @retval #kStatus_FLASH_EccError A correctable or uncorrectable error during command execution.
 * @retval #kStatus_FLASH_RegulationLoss A loss of regulation during read.
 */
status_t FFR_GetCustomerInfieldData(flash_config_t *config, uint8_t *pData, uint32_t offset, uint32_t len);

/*!
 * @brief APIs to access CMPA pages
 *
 * This routine will erase "customer factory page" and program the page with passed data.
 * If 'seal_part' parameter is TRUE then the routine will compute SHA256 hash of
 * the page contents and then programs the pages.
 * 1.During development customer code uses this API with 'seal_part' set to FALSE.
 * 2.During manufacturing this parameter should be set to TRUE to seal the part
 * from further modifications
 * 3.This routine checks if the page is sealed or not. A page is said to be sealed if
 * the SHA256 value in the page has non-zero value. On boot ROM locks the firewall for
 * the region if hash is programmed anyways. So, write/erase commands will fail eventually.
 *
 * @param config A pointer to the storage for the driver runtime state.
 * @param page_data A pointer to the source buffer of data that is to be programmed
 *        into the "customer factory page".
 * @param seal_part Set fasle for During development customer code.
 *
 * @retval #kStatus_FLASH_Success The desire page-data were programed successfully into CMPA.
 * @retval #kStatus_FLASH_InvalidArgument Parameter is not aligned with the specified baseline.
 * @retval #kStatus_FTFx_AddressError Address is out of range.
 * @retval #kStatus_FLASH_AlignmentError Parameter is not aligned with the specified baseline.
 * @retval #kStatus_FLASH_EraseKeyError API erase key is invalid.
 * @retval #kStatus_FLASH_ModifyProtectedAreaDisallowed Flash firewall page locked erase and program are not allowed
 * @retval #kStatus_Fail Generic status for Fail.
 * @retval #kStatus_FLASH_CommandFailure access error.
 * @retval #kStatus_FLASH_CommandNotSupported Flash API is not supported
 * @retval #kStatus_FLASH_EccError A correctable or uncorrectable error during command execution.
 * @retval #kStatus_FLASH_RegulationLoss A loss of regulation during read.
 */
status_t FFR_CustFactoryPageWrite(flash_config_t *config, uint8_t *page_data, bool seal_part);

/*!
 * @brief APIs to access CMPA page
 *
 * Read data stored in 'Customer Factory CFG Page'.
 *
 * @param config A pointer to the storage for the driver runtime state.
 * @param pData A pointer to the dest buffer of data that is to be read
 *            from the Customer Factory CFG Page.
 * @param offset Address offset relative to the CMPA area.
 * @param len The length, given in bytes to be read.
 *
 * @retval #kStatus_FLASH_Success Get data from 'Customer Factory CFG Page'.
 * @retval #kStatus_FLASH_InvalidArgument Parameter is not aligned with the specified baseline.
 * @retval #kStatus_FLASH_AlignmentError Parameter is not aligned with the specified baseline.
 * @retval #kStatus_FTFx_AddressError Address is out of range.
 * @retval #kStatus_FLASH_CommandFailure access error.
 * @retval #kStatus_FLASH_CommandNotSupported Flash API is not supported
 * @retval #kStatus_FLASH_EccError A correctable or uncorrectable error during command execution.
 * @retval #kStatus_FLASH_RegulationLoss A loss of regulation during read.
 * @retval #kStatus_FLASH_ReadHidingAreaDisallowed Flash hiding read is not allowed
 */
status_t FFR_GetCustomerData(flash_config_t *config, uint8_t *pData, uint32_t offset, uint32_t len);

/*!
 * @brief The API is used for getting the customer key store data from the customer key store region(0x3e400 ï¿½C
 * 0x3e600), and the API should be called after the FLASH_Init and FFR_Init.
 *
 * @param config A pointer to the storage for the driver runtime state.
 * @param pData A pointer to the dest buffer of data that is to be read
 *            from the Customer Factory CFG Page.
 * @param offset Address offset relative to the CMPA area.
 * @param len The length, given in bytes to be read.
 *
 * @retval #kStatus_FLASH_Success Get data from 'Customer Factory CFG Page'.
 * @retval #kStatus_FLASH_InvalidArgument Parameter is not aligned with the specified baseline.
 * @retval #kStatus_FTFx_AddressError Address is out of range.
 * @retval #kStatus_FLASH_AddressError Address is out of range
 * @retval #kStatus_FLASH_AlignmentError Parameter is not aligned with the specified baseline.
 * @retval #kStatus_FLASH_ReadHidingAreaDisallowed Flash hiding read is not allowed
 * @retval #kStatus_FLASH_CommandFailure access error.
 * @retval #kStatus_FLASH_CommandNotSupported Flash API is not supported
 * @retval #kStatus_FLASH_EccError A correctable or uncorrectable error during command execution.
 * @retval #kStatus_FLASH_RegulationLoss A loss of regulation during read.
 */
status_t FFR_GetCustKeystoreData(flash_config_t *config, uint8_t *pData, uint32_t offset, uint32_t len);

/*!
 * @brief This routine writes the 3 pages allocated for Key store data.
 *
 * @param config A pointer to the storage for the driver runtime state.
 * @param pKeyStore A pointer to the source buffer of data that is to be programmed
 *        into the "Key store".
 *
 * @retval #kStatus_FLASH_Success Get data from 'Customer Factory CFG Page'.
 * @retval #kStatus_FLASH_InvalidArgument Parameter is not aligned with the specified baseline.
 * @retval #kStatus_FLASH_CommandFailure access error.
 * @retval #kStatus_FLASH_CommandNotSupported Flash API is not supported
 * @retval #kStatus_FLASH_EccError A correctable or uncorrectable error during command execution.
 * @retval #kStatus_FLASH_RegulationLoss A loss of regulation during read.
 * @retval #kStatus_FLASH_SealedFfrRegion The FFR region is sealed.
 * @retval #kStatus_FLASH_FfrBankIsLocked The FFR bank region is locked.
 * @retval #kStatus_FLASH_AddressError Address is out of range
 * @retval #kStatus_FLASH_AlignmentError Parameter is not aligned with the specified baseline.
 * @retval #kStatus_FLASH_ModifyProtectedAreaDisallowed Flash firewall page locked erase and program are not allowed
 */
status_t FFR_CustKeystoreWrite(flash_config_t *config, ffr_key_store_t *pKeyStore);

/*!
 * @brief APIs to access CMPA page
 *
 * 1.SW should use this API routine to get the UUID of the chip.
 * 2.Calling routine should pass a pointer to buffer which can hold 128-bit value.
 *
 * @retval #kStatus_FLASH_Success Get data from 'Customer Factory CFG Page'.
 * @retval #kStatus_FLASH_InvalidArgument Parameter is not aligned with the specified baseline.
 * @retval #kStatus_FLASH_ReadHidingAreaDisallowed Flash hiding read is not allowed
 * @retval #kStatus_FLASH_CommandFailure Run-time error during command execution.
 * @retval #kStatus_FLASH_CommandNotSupported Flash API is not supported
 * @retval #kStatus_FLASH_RegulationLoss A loss of regulation during read.
 */
status_t FFR_GetUUID(flash_config_t *config, uint8_t *uuid);

/*@}*/

#ifdef __cplusplus
}
#endif

/*@}*/

#endif /*! FSL_FLASH_FFR_H_ */
