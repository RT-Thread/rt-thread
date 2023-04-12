/**
    *****************************************************************************
    * @file     cmem7_flash.h
    *
    * @brief    CMEM7 flash controller source file
    *
    *
    * @version  V1.0
    * @date     3. September 2013
    *
    * @note
    *
    *****************************************************************************
    * @attention
    *
    * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
    * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
    * TIME. AS A RESULT, CAPITAL-MICRO SHALL NOT BE HELD LIABLE FOR ANY DIRECT,
    * INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
    * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
    * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
    *
    * <h2><center>&copy; COPYRIGHT 2013 Capital-micro </center></h2>
    *****************************************************************************
    */

#ifndef __CMEM7_FLASH_H
#define __CMEM7_FLASH_H

#ifdef __cplusplus
 extern "C" {
#endif

#include "cmem7.h"
#include "cmem7_conf.h"

/** @defgroup FLASH_PROTECT_MODE
  * @{
  */
#define FLASH_PROTECT_MODE_SW           0       /*!< The Status Register can be written to after a Write
                                                     Enable command.(Default) */
#define FLASH_PROTECT_MODE_HW           1       /*!< WP pin decides if the Status Register can be written
                                                     WP#=0, the Status Register locked
                                                                                                       WP#=1, the Status Register is unlocked and can be written to
                                                     after a Write Enable command */
#define FLASH_PROTECT_MODE_POWERDOWN    2               /*!< Status Register is protected and can not be written to again
                                                     until the next Power-Down, Power-Up cycle */
#define FLASH_PROTECT_MODE_OTP          3       /*!< Status Register is permanently protected */

#define IS_FLASH_PROTECT_MODE(MODE)     (((MODE) == FLASH_PROTECT_MODE_SW) || \
                                         ((MODE) == FLASH_PROTECT_MODE_HW) || \
                                         ((MODE) == FLASH_PROTECT_MODE_POWERDOWN) || \
                                         ((MODE) == FLASH_PROTECT_MODE_OTP))
/**
  * @}
  */

/** @defgroup FLASH_PROTECT_REGION
  * @{
  */
#define FLASH_PROTECT_REGION_NONE       0x00    /*!< no region is protected */
#define FLASH_PROTECT_REGION_UP_64K     0x01    /*!< region(0F0000H-0FFFFFH) is protected */
#define FLASH_PROTECT_REGION_UP_128K    0x02    /*!< region(0E0000H-0FFFFFH) is protected */
#define FLASH_PROTECT_REGION_UP_256K    0x03    /*!< region(0C0000H-0FFFFFH) is protected */
#define FLASH_PROTECT_REGION_UP_512K    0x04    /*!< region(080000H-0FFFFFH) is protected */
#define FLASH_PROTECT_REGION_LOW_64K    0x09    /*!< region(000000H-00FFFFH) is protected */
#define FLASH_PROTECT_REGION_LOW_128K   0x0A    /*!< region(000000H-01FFFFH) is protected */
#define FLASH_PROTECT_REGION_LOW_256K   0x0B    /*!< region(000000H-03FFFFH) is protected */
#define FLASH_PROTECT_REGION_LOW_512K   0x0C    /*!< region(000000H-07FFFFH) is protected */
#define FLASH_PROTECT_REGION_ALL        0x0D    /*!< region(000000H-0FFFFFH) is protected */
#define FLASH_PROTECT_REGION_UP_4K      0x11    /*!< region(0FF000H-0FFFFFH) is protected */
#define FLASH_PROTECT_REGION_UP_8K      0x12    /*!< region(0FE000H-0FFFFFH) is protected */
#define FLASH_PROTECT_REGION_UP_16K     0x13    /*!< region(0FC000H-0FFFFFH) is protected */
#define FLASH_PROTECT_REGION_UP_32K     0x14    /*!< region(0F8000H-0FFFFFH) is protected */
#define FLASH_PROTECT_REGION_LOW_4K     0x19    /*!< region(000000H-000FFFH) is protected */
#define FLASH_PROTECT_REGION_LOW_8K     0x1A    /*!< region(000000H-001FFFH) is protected */
#define FLASH_PROTECT_REGION_LOW_16K    0x1B    /*!< region(000000H-003FFFH) is protected */
#define FLASH_PROTECT_REGION_LOW_32K    0x1C    /*!< region(000000H-007FFFH) is protected */

#define IS_FLASH_PROTECT_REGION(REGION) (((REGION) == FLASH_PROTECT_REGION_NONE) || \
                                         ((REGION) == FLASH_PROTECT_REGION_UP_64K) || \
                                         ((REGION) == FLASH_PROTECT_REGION_UP_128K) || \
                                                                                 ((REGION) == FLASH_PROTECT_REGION_UP_256K) || \
                                                                                 ((REGION) == FLASH_PROTECT_REGION_UP_512K) || \
                                                                                 ((REGION) == FLASH_PROTECT_REGION_LOW_64K) || \
                                         ((REGION) == FLASH_PROTECT_REGION_LOW_128K) || \
                                                                                 ((REGION) == FLASH_PROTECT_REGION_LOW_256K) || \
                                                                                 ((REGION) == FLASH_PROTECT_REGION_LOW_512K) || \
                                                                                 ((REGION) == FLASH_PROTECT_REGION_ALL) || \
                                         ((REGION) == FLASH_PROTECT_REGION_UP_4K) || \
                                         ((REGION) == FLASH_PROTECT_REGION_UP_8K) || \
                                                                                 ((REGION) == FLASH_PROTECT_REGION_UP_16K) || \
                                                                                 ((REGION) == FLASH_PROTECT_REGION_UP_32K) || \
                                                                                 ((REGION) == FLASH_PROTECT_REGION_LOW_4K) || \
                                         ((REGION) == FLASH_PROTECT_REGION_LOW_8K) || \
                                                                                 ((REGION) == FLASH_PROTECT_REGION_LOW_16K) || \
                                                                                 ((REGION) == FLASH_PROTECT_REGION_LOW_32K))
/**
  * @}
  */

/** @defgroup FLASH_READ_MODE
  * @{
  */
#define FLASH_READ_MODE_NORMAL         0        /*!< normal read, 1 bitwidth, highest freqency is 90MHz */
#define FLASH_READ_MODE_FAST           1        /*!< fast read, 1 bitwidth, highest freqency is 120MHz */
#define FLASH_READ_MODE_FAST_DUAL      2        /*!< fast read, 2 bitwidth, highest freqency is 120MHz */
#define FLASH_READ_MODE_FAST_QUAD      3        /*!< fast read, 4 bitwidth, highest freqency is 90MHz */

#define IS_FLASH_READ_MODE(MODE)       (((MODE) == FLASH_READ_MODE_NORMAL) || \
                                        ((MODE) == FLASH_READ_MODE_FAST) || \
                                        ((MODE) == FLASH_READ_MODE_FAST_DUAL) || \
                                                                                ((MODE) == FLASH_READ_MODE_FAST_QUAD))
/**
  * @}
  */

/**
  * @brief  UART initialization structure
    */
typedef struct
{
  uint8_t FLASH_ClockDividor;       /*!< flash clock dividor, 2 in n times */
    uint8_t FLASH_ProtectMode;        /*!< Status Register protection mode */
    uint8_t FLASH_ProtectRegion;      /*!< flash protection region */
    BOOL FLASH_QuadEnable;            /*!< if allows Quad operation */
    void (*FLASH_Wait)(void);         /*!< When the former read or write operation is excuting,
                                           Flash has to call a callback to wait it finish.
                                           If null, Flash will wait forever until finish */
} FLASH_InitTypeDef;

/**
  * @brief  flash initialization
  * @note   This function should be called at first before any other interfaces.
    *                   Users should make sure that doesn't erase or write data in a
    *                   write-protected region.
    * @param[in] init A pointer to structure FLASH_InitTypeDef
  * @retval None
    */
void FLASH_Init(FLASH_InitTypeDef* init);

/**
  * @brief  Get flash status
  * @param[out] ProtectMode flash protect mode, ref as @ref FLASH_PROTECT_MODE
  * @param[out] ProtectRegion flash protect region, ref as @ref FLASH_PROTECT_REGION
    * @param[out] QuadEnable quad speed mode enable bit
    * @retval None
    */
void FLASH_GetStatus(uint8_t* ProtectMode, uint8_t* ProtectRegion, BOOL* QuadEnable);

/**
  * @brief  Erase a sector, which is 4K bytes large.
  * @param[in] addr Start address of a sector
    * @retval None
    */
void FLASH_EraseSector(uint32_t addr);

/**
  * @brief  Erase a block, which is 32K bytes large.
  * @param[in] addr Start address of a block
    * @retval None
    */
void FLASH_Erase32kBlock(uint32_t addr);

/**
  * @brief  Erase a block, which is 64K bytes large.
  * @param[in] addr Start address of a block
    * @retval None
    */
void FLASH_Erase64kBlock(uint32_t addr);

/**
  * @brief  Erase all chip
  * @param  None
    * @retval None
    */
void FLASH_EraseChip(void);

/**
  * @brief  Enable flash power down mode or not
  * @param[in] enable The bit indicates if flash power down mode is enable or not
    * @retval None
    */
void FLASH_EnableDeepPowerDown(BOOL enable);

/**
  * @brief  Read data from flash
    * @param[in] ReadMode Normal or fast read, ref as @ref FLASH_READ_MODE
    * @param[in] addr Start address to be read
    * @param[in] size Expected data size to be read
    * @param[out] data A user-allocated buffer to fetch data to be read
  * @retval None
    */
void FLASH_Read(uint8_t ReadMode, uint32_t addr, uint16_t size, uint8_t* data);

/**
  * @brief  Write data to flash
    * @param[in] addr Start address to be read
    * @param[in] size Expected data size to be read
    * @param[out] data A pointer to the data to be written
  * @retval None
    */
void FLASH_Write(uint32_t addr, uint16_t size, uint8_t* data);


void flash_WaitInWritting(void) ;

void flash_WaitReadFifoNotEmpty(void);

uint16_t flash_ReadFifo(uint16_t size, uint8_t* data) ;


#ifdef __cplusplus
}
#endif

#endif /* __CMEM7_FLASH_H */

