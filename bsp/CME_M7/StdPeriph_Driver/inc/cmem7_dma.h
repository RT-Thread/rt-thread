/**
    *****************************************************************************
    * @file     cmem7_dma.h
    *
    * @brief    CMEM7 DMA header file
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

#ifndef __CMEM7_DMA_H
#define __CMEM7_DMA_H

#ifdef __cplusplus
 extern "C" {
#endif

#include "cmem7.h"
#include "cmem7_conf.h"

/** @defgroup DMA_Int
  * @{
  */
#define DMA_Int_TfrComplete                0x00000001
#define DMA_Int_Err                        0x00000002
#define DMA_Int_All                        0x00000003

#define IS_DMA_INT(INT)        (((INT) != 0) && (((INT) & ~DMA_Int_All) == 0))
/**
  * @}
  */

/**
  * @brief  Descriptor structure
    *   @note       DMA requires users provides a list of descriptors to operation.
    *                   Meanwhile, memory occupied by descriptors should be in physical
    *                   memory and keep valid during DMA transfer.
    */
typedef struct {
    uint32_t srcAddr;                  /*!< source address                                                      */
    uint32_t dstAddr;                  /*!< destination address                                             */
    uint32_t number;                   /*!< block byte number, no more than 2K Bytes    */
    uint32_t nextBlock;                /*!< next block descriptor                                       */
    uint32_t padding;                  /*!< Nonsense, only used to fill                             */
} BLOCK_DESC;

/**
  * @brief  DMA initialization
  * @note   This function should be called at first before any other interfaces.
    * @param  None
    * @retval None
    */
void DMA_Init(void);

/**
  * @brief  Enable or disable DMA interrupt.
    * @param[in] Int interrupt mask bits, which can be the combination of @ref DMA_Int
    * @param[in] Enable The bit indicates if specific interrupts are enable or not
  * @retval None
    */
void DMA_EnableInt(uint32_t Int, BOOL enable);

/**
  * @brief  Check specific interrupts are set or not
    * @param[in] Int interrupt mask bits, which can be the combination of @ref DMA_Int
  * @retval BOOL The bit indicates if specific interrupts are set or not
    */
BOOL DMA_GetIntStatus(uint32_t Int);

/**
  * @brief  Clear specific interrupts
    * @param[in] Int interrupt mask bits, which can be the combination of @ref DMA_Int
  * @retval None
    */
void DMA_ClearInt(uint32_t Int);

/**
  * @brief  DMA transfer
    * @note     Make sure that memory occupied by descriptors should be in physical
    *                   memory and keep valid before DMA transfer is finished (Return false by
    *                   calling DMA_IsBusy after DMA transfer started).
    * @param[in] blockList A pointer to header of list of BLOCK_DESC
  * @retval BOOL The bit indicates if DMA begins to transfer
    * @see      DMA_IsBusy
    */
BOOL DMA_Transfer(BLOCK_DESC *blockList);

/**
  * @brief  DMA is busy or not
  * @param  None
    * @retval BOOL The bit indicates if DMA is busy or not
    */
BOOL DMA_IsBusy(void);

#ifdef __cplusplus
}
#endif

#endif /* __CMEM7_DMA_H */

