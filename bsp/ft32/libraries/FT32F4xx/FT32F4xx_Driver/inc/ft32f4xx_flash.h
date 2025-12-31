/**
  ******************************************************************************
  * @file               ft32f4xx_flash.h
  * @author             FMD AE
  * @brief              This file contains all the functions prototypes for the FLASH
  *                     firmware library.
  * @version            V1.0.0
  * @data                   2025-03-13
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __FT32F4XX_FLASH_H
#define __FT32F4XX_FLASH_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "ft32f4xx.h"


#define   FLASH_KEY1          0x45670123
#define   FLASH_KEY2          0xCDEF89AB

#define   FLASH_OPTKEY1       0x08192A3B
#define   FLASH_OPTKEY2       0x4C5D6E7F

#define  HW32_REG(ADDRESS)  (*((volatile unsigned long  *)(ADDRESS)))
#define  HW16_REG(ADDRESS)  (*((volatile unsigned short *)(ADDRESS)))
#define  HW8_REG(ADDRESS)   (*((volatile unsigned char  *)(ADDRESS)))
/** @addtogroup FLASH
  * @{
  */
/* Exported types ------------------------------------------------------------*/

/**
  * @brief  FLASH Status
  */
typedef enum
{
    FLASH_BUSY = 1,
    FLASH_ERROR_WRP,            //write portect error
    FLASH_ERROR_PROGRAM,        //program error
    FLASH_ERROR_PGSERR,         //program sequence error
    FLASH_COMPLETE,             //FLASH idle status
    FLASH_TIMEOUT
} FLASH_Status;

/* Exported constants --------------------------------------------------------*/

/** @defgroup FLASH_Exported_Constants
  * @{
  */

/** @defgroup FLASH_Latency
  * @{
  */
#define FLASH_Latency_0                 ((uint32_t)0x00000000)  /*!< FLASH Zero Latency cycle */
#define FLASH_Latency_1                 ((uint32_t)0x00000001)  /*!< FLASH One Latency cycle */
#define FLASH_Latency_2                 ((uint32_t)0x00000002)
#define FLASH_Latency_3                 ((uint32_t)0x00000003)
#define FLASH_Latency_4                 ((uint32_t)0x00000004)
#define FLASH_Latency_5                 ((uint32_t)0x00000005)
#define FLASH_Latency_6                 ((uint32_t)0x00000006)
#define FLASH_Latency_7                 ((uint32_t)0x00000007)//max latency value 
/* Other latency value (8-15) not be used*/
#define FLASH_Latency_8                 ((uint32_t)0x00000008)
#define FLASH_Latency_9                 ((uint32_t)0x00000009)
#define FLASH_Latency_10                ((uint32_t)0x0000000a)
#define FLASH_Latency_11                ((uint32_t)0x0000000b)
#define FLASH_Latency_12                ((uint32_t)0x0000000c)
#define FLASH_Latency_13                ((uint32_t)0x0000000d)
#define FLASH_Latency_14                ((uint32_t)0x0000000e)
#define FLASH_Latency_15                ((uint32_t)0x0000000f)

#define IS_FLASH_LATENCY(LATENCY) ( \
                  ((LATENCY) == FLASH_Latency_0) || \
                  ((LATENCY) == FLASH_Latency_1) || \
                                    ((LATENCY) == FLASH_Latency_2 ) || \
                                    ((LATENCY) == FLASH_Latency_3 ) || \
                                    ((LATENCY) == FLASH_Latency_4 ) || \
                                    ((LATENCY) == FLASH_Latency_5 ) || \
                                    ((LATENCY) == FLASH_Latency_6 ) || \
                                    ((LATENCY) == FLASH_Latency_7 ) || \
                                    ((LATENCY) == FLASH_Latency_8 ) || \
                                    ((LATENCY) == FLASH_Latency_9 ) || \
                                    ((LATENCY) == FLASH_Latency_10) || \
                                    ((LATENCY) == FLASH_Latency_11) || \
                                    ((LATENCY) == FLASH_Latency_12) || \
                                    ((LATENCY) == FLASH_Latency_13) || \
                                    ((LATENCY) == FLASH_Latency_14) || \
                                    ((LATENCY) == FLASH_Latency_15))
/**
  * @}
  */

/** @defgroup FLASH_Interrupts
  * @{
  */
#define FLASH_IT_EOP                   FLASH_WRC_EOPIE  /*!< End of programming interrupt source */
#define FLASH_IT_ERR                   FLASH_WRC_ERRIE /*!< Error interrupt source */
//#define IS_FLASH_IT(IT) ((((IT) & (uint32_t)0xFFF3FFFF) == 0x00000000) && (((IT) != 0x00000000)))
#define IS_FLASH_IT(IT) (((IT) == FLASH_IT_EOP) ||\
                        ((IT) == FLASH_IT_ERR))

/** @defgroup FLASH_FR clear bit
  * @{
  */
#define FLASH_FR_CLEAR                ((uint32_t) 0x0000003F)

/** @defgroup FLASH_Address
  * @{
  */
//#if defined(FT32F4xx)  /*512K devices */
#define IS_FLASH_PROGRAM_ADDRESS(ADDRESS) (((ADDRESS) >= 0x08000000) && ((ADDRESS) <= 0x0807FFFF))

/** @defgroup FLASH_PAGE_number
  * @{
  */
//#if defined(FT32F4xx)  /*1023 page */
#define IS_FLASH_ERASE_PAGE_NUM(PAGE_NUM) (((PAGE_NUM) >= 0x00000000) && ((PAGE_NUM) <= 0x000003FF))

/** @defgroup FLASH_Option_Bytes_Write_Protection
  * @{
  */
#define ERASE_SIZE_0        FLASH_WRC_ESIZE//((uint32_t)0x00000000)  /* Erase size:512B   */
#define ERASE_SIZE_1        FLASH_WRC_ESIZE_0//((uint32_t)0x00000010)  /* Erase size:2KB   */
#define ERASE_SIZE_2        FLASH_WRC_ESIZE_1//((uint32_t)0x00000020)  /* Erase size:16KB   */
#define IS_ERASE_SIZE(SIZE) (((SIZE) == ERASE_SIZE_0  ) ||\
                            ((SIZE) == ERASE_SIZE_1   ) || \
                            ((SIZE) == ERASE_SIZE_2   ))


/** @defgroup FLASH_Option_Bytes_Write_Protection
  * @{
  */
#define WRP_PAGE0_31          ((uint32_t)0xfffffffe)  /* Write protection of page 0_31    */
#define WRP_PAGE32_63         ((uint32_t)0xfffffffd)  /* Write protection of page 32_63   */
#define WRP_PAGE64_95         ((uint32_t)0xfffffffb)  /* Write protection of page 64_95   */
#define WRP_PAGE96_127        ((uint32_t)0xfffffff7)  /* Write protection of page 96_127  */
#define WRP_PAGE128_159       ((uint32_t)0xffffffef)  /* Write protection of page 128_159 */
#define WRP_PAGE160_191       ((uint32_t)0xffffffdf)  /* Write protection of page 160_191 */
#define WRP_PAGE192_223       ((uint32_t)0xffffffbf)  /* Write protection of page 192_223 */
#define WRP_PAGE224_255       ((uint32_t)0xffffff7f)  /* Write protection of page 224_255 */
#define WRP_PAGE256_287       ((uint32_t)0xfffffeff)  /* Write protection of page 256_287 */
#define WRP_PAGE288_319       ((uint32_t)0xfffffdff)  /* Write protection of page 288_319 */
#define WRP_PAGE320_351       ((uint32_t)0xfffffbff)  /* Write protection of page 320_351 */
#define WRP_PAGE352_383       ((uint32_t)0xfffff7ff)  /* Write protection of page 352_383 */
#define WRP_PAGE384_415       ((uint32_t)0xffffefff)  /* Write protection of page 384_415 */
#define WRP_PAGE416_447       ((uint32_t)0xffffdfff)  /* Write protection of page 416_447 */
#define WRP_PAGE448_479       ((uint32_t)0xffffbfff)  /* Write protection of page 448_479 */
#define WRP_PAGE480_511       ((uint32_t)0xffff7fff)  /* Write protection of page 480_511 */
#define WRP_PAGE512_543       ((uint32_t)0xfffeffff)  /* Write protection of page 512_543 */
#define WRP_PAGE544_575       ((uint32_t)0xfffdffff)  /* Write protection of page 544_575 */
#define WRP_PAGE576_607       ((uint32_t)0xfffbffff)  /* Write protection of page 576_607 */
#define WRP_PAGE608_639       ((uint32_t)0xfff7ffff)  /* Write protection of page 608_639 */
#define WRP_PAGE640_671       ((uint32_t)0xffefffff)  /* Write protection of page 640_671 */
#define WRP_PAGE672_703       ((uint32_t)0xffdfffff)  /* Write protection of page 672_703 */
#define WRP_PAGE704_735       ((uint32_t)0xffbfffff)  /* Write protection of page 704_735 */
#define WRP_PAGE736_767       ((uint32_t)0xff7fffff)  /* Write protection of page 736_767 */
#define WRP_PAGE768_799       ((uint32_t)0xfeffffff)  /* Write protection of page 768_799 */
#define WRP_PAGE800_831       ((uint32_t)0xfdffffff)  /* Write protection of page 800_831 */
#define WRP_PAGE832_863       ((uint32_t)0xfbffffff)  /* Write protection of page 832_863 */
#define WRP_PAGE864_895       ((uint32_t)0xf7ffffff)  /* Write protection of page 864_895 */
#define WRP_PAGE896_927       ((uint32_t)0xefffffff)  /* Write protection of page 896_927 */
#define WRP_PAGE928_959       ((uint32_t)0xdfffffff)  /* Write protection of page 928_959 */
#define WRP_PAGE960_991       ((uint32_t)0xbfffffff)  /* Write protection of page 960_991 */
#define WRP_PAGE992_1023      ((uint32_t)0x7fffffff)  /* Write protection of page 992_1023*/

#define WRP_ALLPAGES          ((uint32_t)0x00000000)  /* Write protection of page 0_1023*/

#define IS_WRPR_WRP(PAGE) (((PAGE) == WRP_PAGE0_31      ) ||\
                           ((PAGE) ==WRP_PAGE32_63    ) || \
                           ((PAGE) ==WRP_PAGE64_95    ) || \
                           ((PAGE) ==WRP_PAGE96_127   ) || \
                           ((PAGE) ==WRP_PAGE128_159  ) || \
                           ((PAGE) ==WRP_PAGE160_191  ) || \
                           ((PAGE) ==WRP_PAGE192_223  ) || \
                           ((PAGE) ==WRP_PAGE224_255  ) || \
                           ((PAGE) ==WRP_PAGE256_287  ) || \
                           ((PAGE) ==WRP_PAGE288_319  ) || \
                           ((PAGE) ==WRP_PAGE320_351  ) || \
                           ((PAGE) ==WRP_PAGE352_383  ) || \
                           ((PAGE) ==WRP_PAGE384_415  ) || \
                           ((PAGE) ==WRP_PAGE416_447  ) || \
                           ((PAGE) ==WRP_PAGE448_479  ) || \
                           ((PAGE) ==WRP_PAGE480_511  ) || \
                           ((PAGE) ==WRP_PAGE512_543  ) || \
                           ((PAGE) ==WRP_PAGE544_575  ) || \
                           ((PAGE) ==WRP_PAGE576_607  ) || \
                           ((PAGE) ==WRP_PAGE608_639  ) || \
                           ((PAGE) ==WRP_PAGE640_671  ) || \
                           ((PAGE) ==WRP_PAGE672_703  ) || \
                           ((PAGE) ==WRP_PAGE704_735  ) || \
                           ((PAGE) ==WRP_PAGE736_767  ) || \
                           ((PAGE) ==WRP_PAGE768_799  ) || \
                           ((PAGE) ==WRP_PAGE800_831  ) || \
                           ((PAGE) ==WRP_PAGE832_863  ) || \
                           ((PAGE) ==WRP_PAGE864_895  ) || \
                           ((PAGE) ==WRP_PAGE896_927  ) || \
                           ((PAGE) ==WRP_PAGE928_959  ) || \
                           ((PAGE) ==WRP_PAGE960_991  ) || \
                           ((PAGE) ==WRP_PAGE992_1023  ) || \
                           ((PAGE) ==WRP_ALLPAGES ))

/** @defgroup FLASH_Option_Bytes_Read_Protection
  * @{
  */

/**
  * @brief  FLASH_Read Protection Level
  */
#define OPBC_RDP_Level_0        ((uint8_t)0xaa)
#define OPBC_RDP_Level_1        ((uint8_t)0xbb)    //except "AA" or "CC" 
/*!!! Be CAREFUL to USE OPBC_RDP_Level_2!!!*/
#define OPBC_RDP_Level_2        ((uint8_t)0xcc)  //Warning: When enabling read protection level 2 
//it's no more possible to go back to level 1 or 0
#define IS_OPBC_RDP(LEVEL) (((LEVEL) == OPBC_RDP_Level_0)|| \
                           ((LEVEL) == OPBC_RDP_Level_1)|| \
                           ((LEVEL) == OPBC_RDP_Level_2))
/**
  * @}
  */
/** @defgroup FLASH_Option_Bytes_IWatchdog
  * @{
  */
#define OPBC_IWDG_SW                     ((uint8_t)0x20)  /*!< Software IWDG selected */
#define OPBC_IWDG_HW                     ((uint8_t)0x00)  /*!< Hardware IWDG selected */
#define IS_OPBC_IWDG_SOURCE(SOURCE) (((SOURCE) == OPBC_IWDG_SW) || ((SOURCE) == OPBC_IWDG_HW))

/**
  * @}
  */

/** @defgroup FLASH_Option_Bytes_nRST_STOP
  * @{
  */

#define OPBC_STOP_NoRST                  ((uint8_t)0x40) /*!< No Reset generated when entering in STOP */
#define OPBC_STOP_RST                    ((uint8_t)0x00) /*!< Reset generated when entering in STOP Automaticly*/
#define IS_OPBC_STOP_SOURCE(SOURCE) (((SOURCE) == OPBC_STOP_NoRST) || ((SOURCE) == OPBC_STOP_RST))

/**
  * @}
  */

/** @defgroup FLASH_Option_Bytes_nRST_STDBY
  * @{
  */

#define OPBC_STDBY_NoRST                 ((uint8_t)0x80) /*!< No reset generated when entering in STANDBY */
#define OPBC_STDBY_RST                   ((uint8_t)0x00) /*!< Reset generated when entering in STANDBY Automaticly*/
#define IS_OPBC_STDBY_SOURCE(SOURCE) (((SOURCE) == OPBC_STDBY_NoRST) || ((SOURCE) == OPBC_STDBY_RST))



/** @defgroup FLASH_Flags
  * @{
  */
#define FLASH_FLAG_BSY                  FLASH_FR_BSY       /*!< FLASH Busy flag */
#define FLASH_FLAG_PGERR                FLASH_FR_PGERR     /*!< FLASH Programming error flag */
#define FLASH_FLAG_PGSERR               FLASH_FR_PGSERR    /*!< FLASH Programming sequence error flag */
#define FLASH_FLAG_WRPERR               FLASH_FR_WRPRTERR  /*!< FLASH Write protected error flag */
#define FLASH_FLAG_EOP                  FLASH_FR_EOP      /*!< FLASH End of Programming flag */
#define FLASH_FLAG_OPBERR               FLASH_FR_OPBERR   /*!< user option and factory are not load correctly flag */

#define IS_FLASH_CLEAR_FLAG(FLAG) ((((FLAG) & (uint32_t)0xFFFFFFC1) == 0x00000000) && ((FLAG) != 0x00000000))

#define IS_FLASH_GET_FLAG(FLAG)  (((FLAG) == FLASH_FLAG_BSY) || ((FLAG) == FLASH_FLAG_PGERR) || \
                                  ((FLAG) == FLASH_FLAG_PGSERR) || ((FLAG) == FLASH_FLAG_WRPERR) || \
                                  ((FLAG) == FLASH_FLAG_EOP ) || ((FLAG) == FLASH_FLAG_OPBERR))

/** @defgroup FLASH_Timeout_definition
  * @{
  */
#define FLASH_ER_PRG_TIMEOUT         ((uint32_t)0x000B0000)       //TIM value is user define


/** @defgroup  BORR_Level
  * @{
  */
#define OPBC_BORR_LEVEL0               ((uint32_t)0x00000000)
#define OPBC_BORR_LEVEL1               ((uint32_t)0x00080000)
#define OPBC_BORR_LEVEL2               ((uint32_t)0x00100000)
#define OPBC_BORR_LEVEL3               ((uint32_t)0x00180000)

#define IS_OPBC_BORR_LEVEL(Level)         (((Level) ==OPBC_BORR_LEVEL0)||\
                                          ((Level) == OPBC_BORR_LEVEL1)||\
                                          ((Level) == OPBC_BORR_LEVEL2)||\
                                          ((Level) == OPBC_BORR_LEVEL3))

/** @defgroup  BORF_Level
  * @{
  */
#define OPBC_BORF_LEVEL0               ((uint32_t)0x00000000)
#define OPBC_BORF_LEVEL1               ((uint32_t)0x00020000)
#define OPBC_BORF_LEVEL2               ((uint32_t)0x00040000)
#define OPBC_BORF_LEVEL3               ((uint32_t)0x00060000)

#define IS_OPBC_BORF_LEVEL(Level)         (((Level) ==OPBC_BORF_LEVEL0)||\
                                          ((Level) == OPBC_BORF_LEVEL1)||\
                                          ((Level) == OPBC_BORF_LEVEL2)||\
                                          ((Level) == OPBC_BORF_LEVEL3))



/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */

/**
  * @brief  FLASH memory functions that can be executed from FLASH.
  */
/* FLASH Interface configuration functions ************************************/
void FLASH_SetLatency(uint32_t FLASH_Latency);
void FLASH_PrefetchBufferCmd(FunctionalState NewState);
FlagStatus FLASH_GetPrefetchBufferStatus(void);

/* FLASH Memory Programming functions *****************************************/
void FLASH_Unlock(void);
void FLASH_Lock(void);
FLASH_Status FLASH_ErasePage(uint32_t Page_Address, uint32_t erase_size);
FLASH_Status FLASH_EraseAllPages(void);
FLASH_Status FLASH_ProgramWord(uint32_t Address, uint32_t Data3, uint32_t Data2, uint32_t Data1, uint32_t Data0);
FLASH_Status FLASH_Program_oneWord(uint32_t Address, uint32_t Data0);
FLASH_Status FLASH_Program_HalfWord(uint32_t Address, uint16_t Data0);
FLASH_Status FLASH_Program_Byte(uint32_t Address, uint8_t Data0);

/* FLASH Option Bytes Programming functions *****************************************/
void FLASH_OPBC_Unlock(void);
void FLASH_OPBC_Lock(void);
FLASH_Status FLASH_WRPR_EnableWRP(uint32_t WRPR_WRP);
FLASH_Status FLASH_OPBC_RDPConfig(uint8_t OPBC_RDP);
FLASH_Status FLASH_OPBC_UserConfig(uint8_t OPBC_IWDG, uint8_t OPBC_STOP, uint8_t OPBC_STDBY);
FLASH_Status FLASH_OPBC_BOR_LevelConfig(uint32_t BORR_Level, uint32_t BORF_Level, FunctionalState NewState);
uint32_t FLASH_OPBC_GetWRP(void);
FlagStatus FLASH_OPBC_GetRDP(void);

/* FLASH Interrupts and flags management functions **********************************/
void FLASH_ITConfig(uint32_t FLASH_IT, FunctionalState NewState);
FlagStatus FLASH_GetFlagStatus(uint32_t FLASH_FLAG);
void FLASH_ClearFlag(uint32_t FLASH_FLAG);
FLASH_Status FLASH_GetStatus(void);
FLASH_Status FLASH_WaitForLastOperation(uint32_t Timeout);
/**
  * @}
  */

#ifdef __cplusplus
}
#endif

#endif /* __FT32F0XX_FLASH_H */

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT FMD *****END OF FILE****/







