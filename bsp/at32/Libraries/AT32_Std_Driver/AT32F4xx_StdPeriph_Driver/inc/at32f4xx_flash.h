/**
 **************************************************************************
 * File Name    : at32f4xx_flash.h
 * Description  : at32f4xx FMC header file
 * Date         : 2018-10-08
 * Version      : V1.0.5
 **************************************************************************
 */


/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __AT32F4xx_FLASH_H
#define __AT32F4xx_FLASH_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "at32f4xx.h"

/** @addtogroup at32f4xx_StdPeriph_Driver
  * @{
  */

/** @addtogroup FLASH
  * @{
  */

/** @defgroup FLASH_Exported_Types
  * @{
  */

/**
  * @brief  FLASH Status
  */

typedef enum
{
    FLASH_BSY = 1,
    FLASH_PGRM_FLR,
    FLASH_WRPRT_FLR,
    FLASH_PRC_DONE,
    FLASH_TIMEOUT
} FLASH_Status;

/**
  * @brief  BANK3 SEL
  */

typedef enum
{
    E_BANK3_SEL_ESMT_SP=0,
    E_BANK3_SEL_GENERAL_CFGQE,
    E_BANK3_SEL_GENERAL,
}T_BANK3_SEL;

/**
  * @}
  */

/** @defgroup FLASH_Exported_Constants
  * @{
  */

/** @defgroup Option_Bytes_Write_Protection
  * @{
  */

/* Values to be used with AT32F4xx Medium-density devices */
#define FLASH_WRPRT_PAGE_0to3               ((uint32_t)0x00000001) /*!< AT32F4xx Medium-density devices: Write protection of page 0 to 3 */
#define FLASH_WRPRT_PAGE_4to7               ((uint32_t)0x00000002) /*!< AT32F4xx Medium-density devices: Write protection of page 4 to 7 */
#define FLASH_WRPRT_PAGE_8to11              ((uint32_t)0x00000004) /*!< AT32F4xx Medium-density devices: Write protection of page 8 to 11 */
#define FLASH_WRPRT_PAGE_12to15             ((uint32_t)0x00000008) /*!< AT32F4xx Medium-density devices: Write protection of page 12 to 15 */
#define FLASH_WRPRT_PAGE_16to19             ((uint32_t)0x00000010) /*!< AT32F4xx Medium-density devices: Write protection of page 16 to 19 */
#define FLASH_WRPRT_PAGE_20to23             ((uint32_t)0x00000020) /*!< AT32F4xx Medium-density devices: Write protection of page 20 to 23 */
#define FLASH_WRPRT_PAGE_24to27             ((uint32_t)0x00000040) /*!< AT32F4xx Medium-density devices: Write protection of page 24 to 27 */
#define FLASH_WRPRT_PAGE_28to31             ((uint32_t)0x00000080) /*!< AT32F4xx Medium-density devices: Write protection of page 28 to 31 */
#define FLASH_WRPRT_PAGE_32to35             ((uint32_t)0x00000100) /*!< AT32F4xx Medium-density devices: Write protection of page 32 to 35 */
#define FLASH_WRPRT_PAGE_36to39             ((uint32_t)0x00000200) /*!< AT32F4xx Medium-density devices: Write protection of page 36 to 39 */
#define FLASH_WRPRT_PAGE_40to43             ((uint32_t)0x00000400) /*!< AT32F4xx Medium-density devices: Write protection of page 40 to 43 */
#define FLASH_WRPRT_PAGE_44to47             ((uint32_t)0x00000800) /*!< AT32F4xx Medium-density devices: Write protection of page 44 to 47 */
#define FLASH_WRPRT_PAGE_48to51             ((uint32_t)0x00001000) /*!< AT32F4xx Medium-density devices: Write protection of page 48 to 51 */
#define FLASH_WRPRT_PAGE_52to55             ((uint32_t)0x00002000) /*!< AT32F4xx Medium-density devices: Write protection of page 52 to 55 */
#define FLASH_WRPRT_PAGE_56to59             ((uint32_t)0x00004000) /*!< AT32F4xx Medium-density devices: Write protection of page 56 to 59 */
#define FLASH_WRPRT_PAGE_60to63             ((uint32_t)0x00008000) /*!< AT32F4xx Medium-density devices: Write protection of page 60 to 63 */
#define FLASH_WRPRT_PAGE_64to67             ((uint32_t)0x00010000) /*!< AT32F4xx Medium-density devices: Write protection of page 64 to 67 */
#define FLASH_WRPRT_PAGE_68to71             ((uint32_t)0x00020000) /*!< AT32F4xx Medium-density devices: Write protection of page 68 to 71 */
#define FLASH_WRPRT_PAGE_72to75             ((uint32_t)0x00040000) /*!< AT32F4xx Medium-density devices: Write protection of page 72 to 75 */
#define FLASH_WRPRT_PAGE_76to79             ((uint32_t)0x00080000) /*!< AT32F4xx Medium-density devices: Write protection of page 76 to 79 */
#define FLASH_WRPRT_PAGE_80to83             ((uint32_t)0x00100000) /*!< AT32F4xx Medium-density devices: Write protection of page 80 to 83 */
#define FLASH_WRPRT_PAGE_84to87             ((uint32_t)0x00200000) /*!< AT32F4xx Medium-density devices: Write protection of page 84 to 87 */
#define FLASH_WRPRT_PAGE_88to91             ((uint32_t)0x00400000) /*!< AT32F4xx Medium-density devices: Write protection of page 88 to 91 */
#define FLASH_WRPRT_PAGE_92to95             ((uint32_t)0x00800000) /*!< AT32F4xx Medium-density devices: Write protection of page 92 to 95 */
#define FLASH_WRPRT_PAGE_96to99             ((uint32_t)0x01000000) /*!< AT32F4xx Medium-density devices: Write protection of page 96 to 99 */
#define FLASH_WRPRT_PAGE_100to103           ((uint32_t)0x02000000) /*!< AT32F4xx Medium-density devices: Write protection of page 100 to 103 */
#define FLASH_WRPRT_PAGE_104to107           ((uint32_t)0x04000000) /*!< AT32F4xx Medium-density devices: Write protection of page 104 to 107 */
#define FLASH_WRPRT_PAGE_108to111           ((uint32_t)0x08000000) /*!< AT32F4xx Medium-density devices: Write protection of page 108 to 111 */
#define FLASH_WRPRT_PAGE_112to115           ((uint32_t)0x10000000) /*!< AT32F4xx Medium-density devices: Write protection of page 112 to 115 */
#define FLASH_WRPRT_PAGE_116to119           ((uint32_t)0x20000000) /*!< AT32F4xx Medium-density devices: Write protection of page 115 to 119 */
#define FLASH_WRPRT_PAGE_120to123           ((uint32_t)0x40000000) /*!< AT32F4xx Medium-density devices: Write protection of page 120 to 123 */
#define FLASH_WRPRT_PAGE_124to127           ((uint32_t)0x80000000) /*!< AT32F4xx Medium-density devices: Write protection of page 124 to 127 */

/* Values to be used with AT32F4xx High-density, XL-density and AT32F415xx devices */
#define FLASH_WRPRT_PAGE_0to1               ((uint32_t)0x00000001) /*!< AT32F4xx High-density, XL-density and AT32F415xx devices:
                                                                         Write protection of page 0 to 1 */
#define FLASH_WRPRT_PAGE_2to3               ((uint32_t)0x00000002) /*!< AT32F4xx High-density, XL-density and AT32F415xx devices:
                                                                         Write protection of page 2 to 3 */
#define FLASH_WRPRT_PAGE_4to5               ((uint32_t)0x00000004) /*!< AT32F4xx High-density, XL-density and AT32F415xx devices:
                                                                         Write protection of page 4 to 5 */
#define FLASH_WRPRT_PAGE_6to7               ((uint32_t)0x00000008) /*!< AT32F4xx High-density, XL-density and AT32F415xx devices:
                                                                         Write protection of page 6 to 7 */
#define FLASH_WRPRT_PAGE_8to9               ((uint32_t)0x00000010) /*!< AT32F4xx High-density, XL-density and AT32F415xx devices:
                                                                         Write protection of page 8 to 9 */
#define FLASH_WRPRT_PAGE_10to11             ((uint32_t)0x00000020) /*!< AT32F4xx High-density, XL-density and AT32F415xx devices:
                                                                         Write protection of page 10 to 11 */
#define FLASH_WRPRT_PAGE_12to13             ((uint32_t)0x00000040) /*!< AT32F4xx High-density, XL-density and AT32F415xx devices:
                                                                         Write protection of page 12 to 13 */
#define FLASH_WRPRT_PAGE_14to15             ((uint32_t)0x00000080) /*!< AT32F4xx High-density, XL-density and AT32F415xx devices:
                                                                         Write protection of page 14 to 15 */
#define FLASH_WRPRT_PAGE_16to17             ((uint32_t)0x00000100) /*!< AT32F4xx High-density, XL-density and AT32F415xx devices:
                                                                         Write protection of page 16 to 17 */
#define FLASH_WRPRT_PAGE_18to19             ((uint32_t)0x00000200) /*!< AT32F4xx High-density, XL-density and AT32F415xx devices:
                                                                         Write protection of page 18 to 19 */
#define FLASH_WRPRT_PAGE_20to21             ((uint32_t)0x00000400) /*!< AT32F4xx High-density, XL-density and AT32F415xx devices:
                                                                         Write protection of page 20 to 21 */
#define FLASH_WRPRT_PAGE_22to23             ((uint32_t)0x00000800) /*!< AT32F4xx High-density, XL-density and AT32F415xx devices:
                                                                         Write protection of page 22 to 23 */
#define FLASH_WRPRT_PAGE_24to25             ((uint32_t)0x00001000) /*!< AT32F4xx High-density, XL-density and AT32F415xx devices:
                                                                         Write protection of page 24 to 25 */
#define FLASH_WRPRT_PAGE_26to27             ((uint32_t)0x00002000) /*!< AT32F4xx High-density, XL-density and AT32F415xx devices:
                                                                         Write protection of page 26 to 27 */
#define FLASH_WRPRT_PAGE_28to29             ((uint32_t)0x00004000) /*!< AT32F4xx High-density, XL-density and AT32F415xx devices:
                                                                         Write protection of page 28 to 29 */
#define FLASH_WRPRT_PAGE_30to31             ((uint32_t)0x00008000) /*!< AT32F4xx High-density, XL-density and AT32F415xx devices:
                                                                         Write protection of page 30 to 31 */
#define FLASH_WRPRT_PAGE_32to33             ((uint32_t)0x00010000) /*!< AT32F4xx High-density, XL-density and AT32F415xx devices:
                                                                         Write protection of page 32 to 33 */
#define FLASH_WRPRT_PAGE_34to35             ((uint32_t)0x00020000) /*!< AT32F4xx High-density, XL-density and AT32F415xx devices:
                                                                         Write protection of page 34 to 35 */
#define FLASH_WRPRT_PAGE_36to37             ((uint32_t)0x00040000) /*!< AT32F4xx High-density, XL-density and AT32F415xx devices:
                                                                         Write protection of page 36 to 37 */
#define FLASH_WRPRT_PAGE_38to39             ((uint32_t)0x00080000) /*!< AT32F4xx High-density, XL-density and AT32F415xx devices:
                                                                         Write protection of page 38 to 39 */
#define FLASH_WRPRT_PAGE_40to41             ((uint32_t)0x00100000) /*!< AT32F4xx High-density, XL-density and AT32F415xx devices:
                                                                         Write protection of page 40 to 41 */
#define FLASH_WRPRT_PAGE_42to43             ((uint32_t)0x00200000) /*!< AT32F4xx High-density, XL-density and AT32F415xx devices:
                                                                         Write protection of page 42 to 43 */
#define FLASH_WRPRT_PAGE_44to45             ((uint32_t)0x00400000) /*!< AT32F4xx High-density, XL-density and AT32F415xx devices:
                                                                         Write protection of page 44 to 45 */
#define FLASH_WRPRT_PAGE_46to47             ((uint32_t)0x00800000) /*!< AT32F4xx High-density, XL-density and AT32F415xx devices:
                                                                         Write protection of page 46 to 47 */
#define FLASH_WRPRT_PAGE_48to49             ((uint32_t)0x01000000) /*!< AT32F4xx High-density, XL-density and AT32F415xx devices:
                                                                         Write protection of page 48 to 49 */
#define FLASH_WRPRT_PAGE_50to51             ((uint32_t)0x02000000) /*!< AT32F4xx High-density, XL-density and AT32F415xx devices:
                                                                         Write protection of page 50 to 51 */
#define FLASH_WRPRT_PAGE_52to53             ((uint32_t)0x04000000) /*!< AT32F4xx High-density, XL-density and AT32F415xx devices:
                                                                         Write protection of page 52 to 53 */
#define FLASH_WRPRT_PAGE_54to55             ((uint32_t)0x08000000) /*!< AT32F4xx High-density, XL-density and AT32F415xx devices:
                                                                         Write protection of page 54 to 55 */
#define FLASH_WRPRT_PAGE_56to57             ((uint32_t)0x10000000) /*!< AT32F4xx High-density, XL-density and AT32F415xx devices:
                                                                         Write protection of page 56 to 57 */
#define FLASH_WRPRT_PAGE_58to59             ((uint32_t)0x20000000) /*!< AT32F4xx High-density, XL-density and AT32F415xx devices:
                                                                         Write protection of page 58 to 59 */
#define FLASH_WRPRT_PAGE_60to61             ((uint32_t)0x40000000) /*!< AT32F4xx High-density, XL-density and AT32F415xx devices:
                                                                         Write protection of page 60 to 61 */
																		 
#define FLASH_WRPRT_PAGE_62to63             ((uint32_t)0x80000000) /*!< AT32F415xx Medium-density devices: Write protection of page 62 to 63 */                                                                         
#define FLASH_WRPRT_PAGE_62to127            ((uint32_t)0x80000000) /*!< AT32F4xx High-density, AT32F415xx Medium-density, High-density devices:
                                                                         Write protection of page 62 to 127 */
#define FLASH_WRPRT_PAGE_62to255            ((uint32_t)0x80000000) /*!< AT32F4xx High-density devices: Write protection of page 62 to 255 */                                                                         
#define FLASH_WRPRT_PAGE_62to511            ((uint32_t)0x80000000) /*!< AT32F4xx XL-density devices: Write protection of page 62 to 511 */
                                            
#define FLASH_WRPRT_AllPAGES                ((uint32_t)0xFFFFFFFF) /*!< Write protection of all Pages */
                                            
#define IS_FLASH_WRPRT_PAGES(PAGES)         (((PAGES) != 0x00000000))
                                            
#define IS_FLASH_ADDR(ADDR)                 (((ADDR) >= 0x08000000) && ((ADDR) <= FLASH_BANK3_ADDR_MAX))

/**
  * @}
  */

/** @defgroup Option_Bytes_IWatchdog
  * @{
  */

#define UOB_SW_IWDG                         ((uint16_t)0x0001)  /*!< Software IWDG selected */
#define UOB_HW_IWDG                         ((uint16_t)0x0000)  /*!< Hardware IWDG selected */
#define IS_UOB_IWDG_CFG(CFG)                (((CFG) == UOB_SW_IWDG) || ((CFG) == UOB_HW_IWDG))

/**
  * @}
  */

/** @defgroup Option_Bytes_nRST_STOP
  * @{
  */

#define UOB_NO_RST_STP                      ((uint16_t)0x0002) /*!< No reset generated when entering in STOP */
#define UOB_RST_STP                         ((uint16_t)0x0000) /*!< Reset generated when entering in STOP */
#define IS_UOB_STOP_CFG(CFG)                (((CFG) == UOB_NO_RST_STP) || ((CFG) == UOB_RST_STP))

/**
  * @}
  */

/** @defgroup Option_Bytes_nRST_STDBY
  * @{
  */

#define UOB_NO_RST_STDBY                    ((uint16_t)0x0004) /*!< No reset generated when entering in STANDBY */
#define UOB_RST_STDBY                       ((uint16_t)0x0000) /*!< Reset generated when entering in STANDBY */
#define IS_UOB_STDBY_CFG(CFG)               (((CFG) == UOB_NO_RST_STDBY) || ((CFG) == UOB_RST_STDBY))

#if defined(AT32F403Cx_XL) || defined(AT32F403Rx_XL) || defined(AT32F403Vx_XL) || defined(AT32F403Zx_XL) || \
    defined(AT32F403ACGU7) || defined(AT32F403ACGT7) || defined(AT32F403ARGT7) || defined(AT32F403AVGT7) || \
    defined(AT32F407RGT7)  || defined(AT32F407VGT7)
/**
  * @}
  */
/** @defgroup FLASH_Boot
  * @{
  */
#define FLASH_BOOT_FROM_BANK1               ((uint16_t)0x0000) /*!< At startup, if boot pins are set in boot from user Flash position
                                                               and this parameter is selected the device will boot from Bank1(Default) */
#define FLASH_BOOT_FROM_BANK2               ((uint16_t)0x0001) /*!< At startup, if boot pins are set in boot from user Flash position
                                                               and this parameter is selected the device will boot from Bank 2 or Bank 1,
                                                               depending on the activation of the bank */
#define IS_FLASH_BOOT_CFG(CFG)              (((CFG) == FLASH_BOOT_FROM_BANK1) || ((CFG) == FLASH_BOOT_FROM_BANK2))
#endif
/**
  * @}
  */
/** @defgroup FLASH_Interrupts
  * @{
  */
#define FLASH_INT_FLR                       ((uint32_t)0x00000400)  /*!< FPEC error interrupt source */
#define FLASH_INT_PRCDN                     ((uint32_t)0x00001000)  /*!< End of FLASH Operation Interrupt source */
#define FLASH_INT_BANK1_FLR                 FLASH_INT_FLR           /*!< FPEC BANK1 error interrupt source */
#define FLASH_INT_BANK1_PRCDN               FLASH_INT_PRCDN         /*!< End of FLASH BANK1 Operation Interrupt source */
#define FLASH_INT_BANK3                     ((uint32_t)0x40000000)
#define FLASH_INT_BANK3_MASK                (~FLASH_INT_BANK3)
#define FLASH_INT_BANK3_FLR                 ((uint32_t)0x40000400)  /*!< FPEC BANK1 error interrupt source */
#define FLASH_INT_BANK3_PRCDN               ((uint32_t)0x40001000)  /*!< End of FLASH BANK1 Operation Interrupt source */



#if defined(AT32F403Cx_XL) || defined(AT32F403Rx_XL) || defined(AT32F403Vx_XL) || defined(AT32F403Zx_XL) || \
    defined(AT32F403ACGU7) || defined(AT32F403ACGT7) || defined(AT32F403ARGT7) || defined(AT32F403AVGT7) || \
    defined(AT32F407RGT7)  || defined(AT32F407VGT7)
#define FLASH_INT_BANK2                     ((uint32_t)0x80000000)
#define FLASH_INT_BANK2_MASK                (~FLASH_INT_BANK2)
#define FLASH_INT_BANK2_FLR                 ((uint32_t)0x80000400)  /*!< FPEC BANK2 error interrupt source */
#define FLASH_INT_BANK2_PRCDN               ((uint32_t)0x80001000)  /*!< End of FLASH BANK2 Operation Interrupt source */
#define IS_FLASH_INT(INT)                   ((((INT) & (uint32_t)0x3FFFEBFF) == 0x00000000) && (((INT) != 0x00000000)))
#else
#define IS_FLASH_INT(INT) ((((INT) & (uint32_t)0xBFFFEBFF) == 0x00000000) && (((INT) != 0x00000000)))
#endif

/**
  * @}
  */

/** @defgroup FLASH_Flags
  * @{
  */

#define FLASH_FLAG_BSY                      ((uint32_t)0x00000001)  /*!< FLASH Busy flag */
#define FLASH_FLAG_PRCDN                    ((uint32_t)0x00000020)  /*!< FLASH End of Operation flag */
#define FLASH_FLAG_PRGMFLR                  ((uint32_t)0x00000004)  /*!< FLASH Program error flag */
#define FLASH_FLAG_WRPRTFLR                 ((uint32_t)0x00000010)  /*!< FLASH Write protected error flag */
#define FLASH_FLAG_UOBFLR                   ((uint32_t)0x00000001)  /*!< FLASH Option Byte error flag */

#define FLASH_FLAG_BNK1_BSY                 FLASH_FLAG_BSY          /*!< FLASH BANK1 Busy flag*/
#define FLASH_FLAG_BNK1_PRCDN               FLASH_FLAG_PRCDN        /*!< FLASH BANK1 End of Operation flag */
#define FLASH_FLAG_BNK1_PRGMFLR             FLASH_FLAG_PRGMFLR      /*!< FLASH BANK1 Program error flag */
#define FLASH_FLAG_BNK1_WRPRTFLR            FLASH_FLAG_WRPRTFLR     /*!< FLASH BANK1 Write protected error flag */

#define FLASH_FLAG_BANK3                    ((uint32_t)0x40000000)
#define FLASH_FLAG_BNK3_BSY                 ((uint32_t)0x40000001)  /*!< FLASH BANK3 Busy flag*/
#define FLASH_FLAG_BNK3_PRCDN               ((uint32_t)0x40000020)  /*!< FLASH BANK3 End of Operation flag */
#define FLASH_FLAG_BNK3_PRGMFLR             ((uint32_t)0x40000004)  /*!< FLASH BANK3 Program error flag */
#define FLASH_FLAG_BNK3_WRPRTFLR            ((uint32_t)0x40000010)  /*!< FLASH BANK3 Write protected error flag */


#if defined(AT32F403Cx_XL) || defined(AT32F403Rx_XL) || defined(AT32F403Vx_XL) || defined(AT32F403Zx_XL) || \
    defined(AT32F403ACGU7) || defined(AT32F403ACGT7) || defined(AT32F403ARGT7) || defined(AT32F403AVGT7) || \
    defined(AT32F407RGT7)  || defined(AT32F407VGT7)
#define FLASH_FLAG_BANK2                    ((uint32_t)0x80000000)
#define FLASH_FLAG_BNK2_BSY                 ((uint32_t)0x80000001)  /*!< FLASH BANK2 Busy flag */
#define FLASH_FLAG_BNK2_PRCDN               ((uint32_t)0x80000020)  /*!< FLASH BANK2 End of Operation flag */
#define FLASH_FLAG_BNK2_PRGMFLR             ((uint32_t)0x80000004)  /*!< FLASH BANK2 Program error flag */
#define FLASH_FLAG_BNK2_WRPRTFLR            ((uint32_t)0x80000010)  /*!< FLASH BANK2 Write protected error flag */

#define IS_FLASH_CLEAR_FLAG(FLAG)           ((((FLAG) & (uint32_t)0x3FFFFFCA) == 0x00000000) && ((FLAG) != 0x00000000))
#define IS_FLASH_GET_FLAG(FLAG)             (((FLAG) == FLASH_FLAG_BSY) || ((FLAG) == FLASH_FLAG_PRCDN) || \
                                             ((FLAG) == FLASH_FLAG_PRGMFLR) || ((FLAG) == FLASH_FLAG_WRPRTFLR) || \
                                             ((FLAG) == FLASH_FLAG_UOBFLR)|| \
                                             ((FLAG) == FLASH_FLAG_BNK1_BSY) || ((FLAG) == FLASH_FLAG_BNK1_PRCDN) || \
                                             ((FLAG) == FLASH_FLAG_BNK1_PRGMFLR) || ((FLAG) == FLASH_FLAG_BNK1_WRPRTFLR) || \
                                             ((FLAG) == FLASH_FLAG_BNK2_BSY) || ((FLAG) == FLASH_FLAG_BNK2_PRCDN) || \
                                             ((FLAG) == FLASH_FLAG_BNK2_PRGMFLR) || ((FLAG) == FLASH_FLAG_BNK2_WRPRTFLR) || \
                                             ((FLAG) == FLASH_FLAG_BNK3_BSY) || ((FLAG) == FLASH_FLAG_BNK3_PRCDN) || \
                                             ((FLAG) == FLASH_FLAG_BNK3_PRGMFLR) || ((FLAG) == FLASH_FLAG_BNK3_WRPRTFLR))
#else
#define IS_FLASH_CLEAR_FLAG(FLAG)           ((((FLAG) & (uint32_t)0xBFFFFFCA) == 0x00000000) && ((FLAG) != 0x00000000))
#define IS_FLASH_GET_FLAG(FLAG)             (((FLAG) == FLASH_FLAG_BSY) || ((FLAG) == FLASH_FLAG_PRCDN) || \
                                             ((FLAG) == FLASH_FLAG_PRGMFLR) || ((FLAG) == FLASH_FLAG_WRPRTFLR) || \
                                             ((FLAG) == FLASH_FLAG_BNK1_BSY) || ((FLAG) == FLASH_FLAG_BNK1_PRCDN) || \
                                             ((FLAG) == FLASH_FLAG_BNK1_PRGMFLR) || ((FLAG) == FLASH_FLAG_BNK1_WRPRTFLR) || \
                                             ((FLAG) == FLASH_FLAG_UOBFLR) || \
                                             ((FLAG) == FLASH_FLAG_BNK3_BSY) || ((FLAG) == FLASH_FLAG_BNK3_PRCDN) || \
                                             ((FLAG) == FLASH_FLAG_BNK3_PRGMFLR) || ((FLAG) == FLASH_FLAG_BNK3_WRPRTFLR))
#endif

#define FLASH_BANK3_ADDR_MAX                  ((uint32_t)0x1FFEFFFF)
#define IS_IN_FLASH_BANK3_RANGE(ADDR)         (((ADDR) >=EXT_FLASH_BASE) && ((ADDR) <= FLASH_BANK3_ADDR_MAX))

/**
  * @}
  */

/**
  * @}
  */

/** @defgroup FLASH_Exported_Macros
  * @{
  */

/**
  * @}
  */

/** @defgroup FLASH_Exported_Functions
  * @{
  */

/*------------ Functions used for all at32f4xx devices -----*/
void FLASH_Unlock(void);
void FLASH_Lock(void);
FLASH_Status FLASH_ErasePage(uint32_t Page_Address);
FLASH_Status FLASH_EraseAllPages(void);
FLASH_Status FLASH_EraseUserOptionBytes(void);
FLASH_Status FLASH_ProgramWord(uint32_t Address, uint32_t Data);
FLASH_Status FLASH_ProgramHalfWord(uint32_t Address, uint16_t Data);
FLASH_Status FLASH_ProgramByte(uint32_t Address, uint8_t Data);
FLASH_Status FLASH_ProgramUserOptionByteData(uint32_t Address, uint8_t Data);
FLASH_Status FLASH_EnableWriteProtect(uint32_t FLASH_Pages);
FLASH_Status FLASH_ReadProtectConfig(FunctionalState NewState);
FLASH_Status FLASH_UserOptionByteConfig(uint16_t UOB_IWDG, uint16_t UOB_STOP, uint16_t UOB_STDBY);
uint32_t FLASH_GetUserOptionByte(void);
uint32_t FLASH_GetWriteProtectStatus(void);
FlagStatus FLASH_GetReadProtectStatus(void);
FlagStatus FLASH_GetPrefetchBufferStatus(void);
void FLASH_INTConfig(uint32_t FLASH_INT, FunctionalState NewState);
FlagStatus FLASH_GetFlagStatus(uint32_t FLASH_FLAG);
void FLASH_ClearFlag(uint32_t FLASH_FLAG);
FLASH_Status FLASH_GetStatus(void);
FLASH_Status FLASH_WaitForProcess(uint32_t Timeout);

#if defined (AT32F415xx)
/*------------ Functions used only for at32f415 devices -----*/
FLASH_Status FLASH_SYS_AP(void);
FLASH_Status FLASH_SlibSysEnable(uint32_t Psw,uint8_t data_start_page);
FlagStatus FLASH_GetOptionByteProtectStatus(void);
FLASH_Status FLASH_RDPandOptionByteProtectEnable(void);
void FLASH_OptionByteProtectDisable(void);
#endif /* AT32F415xx */

/*------------ New function used for all at32f4xx devices -----*/
void FLASH_UnlockBank1(void);
void FLASH_LockBank1(void);
FLASH_Status FLASH_EraseBank1AllPages(void);
FLASH_Status FLASH_GetBank1Status(void);
FLASH_Status FLASH_WaitForBank1Process(uint32_t Timeout);

#if defined(AT32F403Cx_XL) || defined(AT32F403Rx_XL) || defined(AT32F403Vx_XL) || defined(AT32F403Zx_XL) || \
    defined(AT32F403ACGU7) || defined(AT32F403ACGT7) || defined(AT32F403ARGT7) || defined(AT32F403AVGT7) || \
    defined(AT32F407RGT7)  || defined(AT32F407VGT7)
/*---- New Functions used only with at32f403_XL density devices -----*/
void FLASH_UnlockBank2(void);
void FLASH_LockBank2(void);
FLASH_Status FLASH_EraseBank2AllPages(void);
FLASH_Status FLASH_GetBank2Status(void);
FLASH_Status FLASH_WaitForBank2Process(uint32_t Timeout);
FLASH_Status FLASH_BootOptConfig(uint16_t FLASH_BOOT);
#endif

#if !defined (AT32F415xx)
/*---- New Functions for extrenal flash -----*/
void FLASH_UnlockBank3(void);
void FLASH_LockBank3(void);
FLASH_Status FLASH_EraseBank3AllPages(void);
FLASH_Status FLASH_GetBank3Status(void);
FLASH_Status FLASH_WaitForBank3Process(uint32_t Timeout);
void FLASH_Bank3EncEndAddrConfig(uint32_t EndAddress);
#endif

/*---- New Functions for SLIB -----*/
FLASH_Status FLASH_SlibMainEnable(uint32_t Psw, uint16_t StartPage, uint16_t DataPage, uint16_t EndPage);
uint32_t FLASH_SlibDisable(uint32_t dwPsw);
#if !defined (AT32F415xx)
uint32_t FLASH_GetSlibCurCnt(void);
#endif
uint8_t FLASH_GetSlibState(void);
uint16_t FLASH_GetSlibStartPage(void);
uint16_t FLASH_GetSlibDataStartPage(void);
uint16_t FLASH_GetSlibEndPage(void);
#ifdef __cplusplus
}
#endif

#endif /* __AT32F4xx_FLASH_H */
/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */


