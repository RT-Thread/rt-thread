/**************************************************************************//**
 * @file     nu_sdh.h
 * @version  V1.00
 * @brief    SDH driver header file
 *
 * SPDX-License-Identifier: Apache-2.0
 * @copyright (C) 2021 Nuvoton Technology Corp. All rights reserved.
*****************************************************************************/
#include <stdio.h>

#ifndef __NU_SDH_H__
#define __NU_SDH_H__

#ifdef __cplusplus
extern "C"
{
#endif


/** @addtogroup Standard_Driver Standard Driver
  @{
*/

/** @addtogroup SDH_Driver SDH Driver
  @{
*/


/** @addtogroup SDH_EXPORTED_CONSTANTS SDH Exported Constants
  @{
*/

#define SDH_ERR_ID       0xFFFF0100ul /*!< SDH error ID  \hideinitializer */

#define SDH_TIMEOUT      (SDH_ERR_ID|0x01ul) /*!< Timeout  \hideinitializer */
#define SDH_NO_MEMORY    (SDH_ERR_ID|0x02ul) /*!< OOM  \hideinitializer */

/*-- function return value */
#define    Successful  0ul   /*!< Success  \hideinitializer */
#define    Fail        1ul   /*!< Failed  \hideinitializer */

/*--- define type of SD card or MMC */
#define SDH_TYPE_UNKNOWN     0ul /*!< Unknown card type  \hideinitializer */
#define SDH_TYPE_SD_HIGH     1ul /*!< SDHC card  \hideinitializer */
#define SDH_TYPE_SD_LOW      2ul /*!< SD card  \hideinitializer */
#define SDH_TYPE_MMC         3ul /*!< MMC card  \hideinitializer */
#define SDH_TYPE_EMMC        4ul /*!< eMMC card  \hideinitializer */

/* SD error */
#define SDH_NO_SD_CARD       (SDH_ERR_ID|0x10ul) /*!< Card removed  \hideinitializer */
#define SDH_ERR_DEVICE       (SDH_ERR_ID|0x11ul) /*!< Device error  \hideinitializer */
#define SDH_INIT_TIMEOUT     (SDH_ERR_ID|0x12ul) /*!< Card init timeout  \hideinitializer */
#define SDH_SELECT_ERROR     (SDH_ERR_ID|0x13ul) /*!< Card select error  \hideinitializer */
#define SDH_WRITE_PROTECT    (SDH_ERR_ID|0x14ul) /*!< Card write protect  \hideinitializer */
#define SDH_INIT_ERROR       (SDH_ERR_ID|0x15ul) /*!< Card init error  \hideinitializer */
#define SDH_CRC7_ERROR       (SDH_ERR_ID|0x16ul) /*!< CRC 7 error  \hideinitializer */
#define SDH_CRC16_ERROR      (SDH_ERR_ID|0x17ul) /*!< CRC 16 error  \hideinitializer */
#define SDH_CRC_ERROR        (SDH_ERR_ID|0x18ul) /*!< CRC error  \hideinitializer */
#define SDH_CMD8_ERROR       (SDH_ERR_ID|0x19ul) /*!< Command 8 error  \hideinitializer */

#define MMC_FREQ        20000ul   /*!< output 20MHz to MMC  \hideinitializer */
#define SD_FREQ         25000ul   /*!< output 25MHz to SD  \hideinitializer */
#define SDHC_FREQ       50000ul   /*!< output 50MHz to SDH \hideinitializer */

#define SD_PORT0        (1 << 0)  /*!< Card select SD0 \hideinitializer */
#define SD_PORT1        (1 << 2)  /*!< Card select SD1 \hideinitializer */
#define CardDetect_From_GPIO  (1ul << 8)   /*!< Card detection pin is GPIO \hideinitializer */
#define CardDetect_From_DAT3  (1ul << 9)   /*!< Card detection pin is DAT3 \hideinitializer */

#define TIMEOUT_SDH     SystemCoreClock /*!< 1 second time-out \hideinitializer */
#define SDH_TIMEOUT_ERR (-1L)           /*!< SDH operation abort due to timeout error \hideinitializer */

/*@}*/ /* end of group SDH_EXPORTED_CONSTANTS */

/** @addtogroup SDH_EXPORTED_TYPEDEF SDH Exported Type Defines
  @{
*/
typedef struct SDH_info_t
{
    unsigned char   IsCardInsert;   /*!< Card insert state */
    unsigned char   R3Flag;
    unsigned char   R7Flag;
    unsigned char volatile DataReadyFlag;
    unsigned int    CardType;       /*!< SDHC, SD, or MMC */
    unsigned int    RCA;            /*!< Relative card address */
    unsigned int    totalSectorN;   /*!< Total sector number */
    unsigned int    diskSize;       /*!< Disk size in K bytes */
    int             sectorSize;     /*!< Sector size in bytes */
    unsigned char   *dmabuf;
} SDH_INFO_T;                       /*!< Structure holds SD card info */

/*@}*/ /* end of group SDH_EXPORTED_TYPEDEF */

/** @cond HIDDEN_SYMBOLS */
extern SDH_INFO_T SD0, SD1;
extern int32_t g_SDH_i32ErrCode;
/** @endcond HIDDEN_SYMBOLS */

/** @addtogroup SDH_EXPORTED_FUNCTIONS SDH Exported Functions
  @{
*/

/**
 *  @brief    Enable specified interrupt.
 *
 *  @param[in]    sdh    Select SDH0 or SDH1.
 *  @param[in]    u32IntMask    Interrupt type mask:
 *                           \ref SDH_INTEN_BLKDIEN_Msk / \ref SDH_INTEN_CRCIEN_Msk / \ref SDH_INTEN_CDIEN_Msk /
 *                           \ref SDH_INTEN_CDSRC_Msk \ref SDH_INTEN_RTOIEN_Msk / \ref SDH_INTEN_DITOIEN_Msk /
 *                           \ref SDH_INTEN_WKIEN_Msk
 *
 *  @return   None.
 * \hideinitializer
 */
#define SDH_ENABLE_INT(sdh, u32IntMask)    ((sdh)->INTEN |= (u32IntMask))

/**
 *  @brief    Disable specified interrupt.
 *
 *  @param[in]    sdh    Select SDH0 or SDH1.
 *  @param[in]    u32IntMask    Interrupt type mask:
 *                           \ref SDH_INTEN_BLKDIEN_Msk / \ref SDH_INTEN_CRCIEN_Msk / \ref SDH_INTEN_CDIEN_Msk /
 *                           \ref SDH_INTEN_RTOIEN_Msk / \ref SDH_INTEN_DITOIEN_Msk / \ref SDH_INTEN_WKIEN_Msk / \ref SDH_INTEN_CDSRC_Msk /
 *
 *  @return   None.
 * \hideinitializer
 */
#define SDH_DISABLE_INT(sdh, u32IntMask)    ((sdh)->INTEN &= ~(u32IntMask))

/**
 *  @brief    Get specified interrupt flag/status.
 *
 *  @param[in]    sdh    Select SDH0 or SDH1.
 *  @param[in]    u32IntMask    Interrupt type mask:
 *                           \ref SDH_INTSTS_BLKDIF_Msk / \ref SDH_INTSTS_CRCIF_Msk / \ref SDH_INTSTS_CRC7_Msk /
 *                           \ref SDH_INTSTS_CRC16_Msk / \ref SDH_INTSTS_CRCSTS_Msk / \ref SDH_INTSTS_DAT0STS_Msk /
 *                           \ref SDH_INTSTS_CDIF_Msk \ref SDH_INTSTS_RTOIF_Msk /
 *                           \ref SDH_INTSTS_DITOIF_Msk / \ref SDH_INTSTS_CDSTS_Msk /
 *                           \ref SDH_INTSTS_DAT1STS_Msk
 *
 *
 *  @return  0 = The specified interrupt is not happened.
 *            1 = The specified interrupt is happened.
 * \hideinitializer
 */
#define SDH_GET_INT_FLAG(sdh, u32IntMask) (((sdh)->INTSTS & (u32IntMask))?1:0)


/**
 *  @brief    Clear specified interrupt flag/status.
 *
 *  @param[in]    sdh    Select SDH0 or SDH1.
 *  @param[in]    u32IntMask    Interrupt type mask:
 *                           \ref SDH_INTSTS_BLKDIF_Msk / \ref SDH_INTSTS_CRCIF_Msk / \ref SDH_INTSTS_CDIF_Msk /
 *                           \ref SDH_INTSTS_RTOIF_Msk / \ref SDH_INTSTS_DITOIF_Msk
 *
 *
 *  @return   None.
 * \hideinitializer
 */
#define SDH_CLR_INT_FLAG(sdh, u32IntMask) ((sdh)->INTSTS = (u32IntMask))


/**
 *  @brief    Check SD Card inserted or removed.
 *
 *  @param[in]    sdh    Select SDH0 or SDH1.
 *
 *  @return   1: Card inserted.
 *            0: Card removed.
 * \hideinitializer
 */
#define SDH_IS_CARD_PRESENT(sdh) (((sdh) == SDH0)? SD0.IsCardInsert : SD1.IsCardInsert)

/**
 *  @brief    Get SD Card capacity.
 *
 *  @param[in]    sdh    Select SDH0 or SDH1.
 *
 *  @return   SD Card capacity. (unit: KByte)
 * \hideinitializer
 */
#define SDH_GET_CARD_CAPACITY(sdh)  (((sdh) == SDH0)? SD0.diskSize : SD1.diskSize)


void SDH_Open(SDH_T *sdh, uint32_t u32CardDetSrc);
uint32_t SDH_Probe(SDH_T *sdh);
uint32_t SDH_Read(SDH_T *sdh, uint8_t *pu8BufAddr, uint32_t u32StartSec, uint32_t u32SecCount);
uint32_t SDH_Write(SDH_T *sdh, uint8_t *pu8BufAddr, uint32_t u32StartSec, uint32_t u32SecCount);
void SDH_Set_clock(SDH_T *sdh, uint32_t sd_clock_khz);

uint32_t SDH_CardDetection(SDH_T *sdh);
void SDH_Open_Disk(SDH_T *sdh, uint32_t u32CardDetSrc);
void SDH_Close_Disk(SDH_T *sdh);


/*@}*/ /* end of group SDH_EXPORTED_FUNCTIONS */

/*@}*/ /* end of group SDH_Driver */

/*@}*/ /* end of group Standard_Driver */

#ifdef __cplusplus
}
#endif

#endif  /* __NU_SDH_H__ */
