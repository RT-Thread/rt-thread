/**
    *****************************************************************************
    * @file     cmem7_misc.h
    *
    * @brief    CMEM7 miscellaneous header file
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

#ifndef __CMEM7_MISC_H
#define __CMEM7_MISC_H

#ifdef __cplusplus
 extern "C" {
#endif

#include "cmem7.h"
#include "cmem7_conf.h"

/**
  * @brief  NVIC initialization structure
    */
/**
@code
    The table below gives the allowed values of the pre-emption priority and subpriority according
    to the Priority Grouping configuration performed by NVIC_PriorityGroupConfig function
    ============================================================================================================================
        NVIC_PriorityGroup   | NVIC_IRQChannelPreemptionPriority | NVIC_IRQChannelSubPriority  | Description
    ============================================================================================================================
     NVIC_PriorityGroup_0  |                0                  |            0-15             |   0 bits for pre-emption priority
                                                 |                                   |                             |   4 bits for subpriority
    ----------------------------------------------------------------------------------------------------------------------------
     NVIC_PriorityGroup_1  |                0-1                |            0-7              |   1 bits for pre-emption priority
                                                 |                                   |                             |   3 bits for subpriority
    ----------------------------------------------------------------------------------------------------------------------------
     NVIC_PriorityGroup_2  |                0-3                |            0-3              |   2 bits for pre-emption priority
                                                 |                                   |                             |   2 bits for subpriority
    ----------------------------------------------------------------------------------------------------------------------------
     NVIC_PriorityGroup_3  |                0-7                |            0-1              |   3 bits for pre-emption priority
                                                 |                                   |                             |   1 bits for subpriority
    ----------------------------------------------------------------------------------------------------------------------------
     NVIC_PriorityGroup_4  |                0-15               |            0                |   4 bits for pre-emption priority
                                                 |                                   |                             |   0 bits for subpriority
    ============================================================================================================================
@endcode
    */

typedef struct
{
  uint8_t NVIC_IRQChannel;                    /*!< Specifies the IRQ channel to be enabled or disabled.
                                                   This parameter can be a value of @ref IRQn_Type
                                                   (For the complete Capital-micro Devices IRQ Channels list, please
                                                    refer to cmem7.h file) */

  uint8_t NVIC_IRQChannelPreemptionPriority;  /*!< Specifies the pre-emption priority for the IRQ channel
                                                   specified in NVIC_IRQChannel. This parameter can be a value
                                                   between 0 and 15 as described in the table @ref NVIC_Priority_Table */

  uint8_t NVIC_IRQChannelSubPriority;         /*!< Specifies the subpriority level for the IRQ channel specified
                                                   in NVIC_IRQChannel. This parameter can be a value
                                                   between 0 and 15 as described in the table @ref NVIC_Priority_Table */

  BOOL NVIC_IRQChannelCmd;                    /*!< Specifies whether the IRQ channel defined in NVIC_IRQChannel
                                                   will be enabled or disabled.
                                                   This parameter can be set either to ENABLE or DISABLE */
} NVIC_InitTypeDef;


/** @defgroup NVIC_VectTab
  * @{
  */

#define NVIC_VectTab_CME_CODE        ((uint32_t)0x00000000)
#define NVIC_VectTab_RAM             ((uint32_t)0x20000000)
#define NVIC_VectTab_FLASH           ((uint32_t)0x08000000)
#define IS_NVIC_VECTTAB(VECTTAB) (((VECTTAB) == NVIC_VectTab_CME_CODE) || \
                                  ((VECTTAB) == NVIC_VectTab_RAM) || \
                                  ((VECTTAB) == NVIC_VectTab_FLASH))
/**
  * @}
  */

/** @defgroup NVIC_LP
  * @{
  */
#define NVIC_LP_SEVONPEND            ((uint8_t)0x10)
#define NVIC_LP_SLEEPDEEP            ((uint8_t)0x04)
#define NVIC_LP_SLEEPONEXIT          ((uint8_t)0x02)
#define IS_NVIC_LP(LP) (((LP) == NVIC_LP_SEVONPEND) || \
                        ((LP) == NVIC_LP_SLEEPDEEP) || \
                        ((LP) == NVIC_LP_SLEEPONEXIT))
/**
  * @}
  */

/** @defgroup NVIC_PriorityGroup
  * @{
  */
#define NVIC_PriorityGroup_0         ((uint32_t)0x700) /*!< 0 bits for pre-emption priority
                                                            4 bits for subpriority */
#define NVIC_PriorityGroup_1         ((uint32_t)0x600) /*!< 1 bits for pre-emption priority
                                                            3 bits for subpriority */
#define NVIC_PriorityGroup_2         ((uint32_t)0x500) /*!< 2 bits for pre-emption priority
                                                            2 bits for subpriority */
#define NVIC_PriorityGroup_3         ((uint32_t)0x400) /*!< 3 bits for pre-emption priority
                                                            1 bits for subpriority */
#define NVIC_PriorityGroup_4         ((uint32_t)0x300) /*!< 4 bits for pre-emption priority
                                                            0 bits for subpriority */

#define IS_NVIC_PRIORITY_GROUP(GROUP) (((GROUP) == NVIC_PriorityGroup_0) || \
                                       ((GROUP) == NVIC_PriorityGroup_1) || \
                                       ((GROUP) == NVIC_PriorityGroup_2) || \
                                       ((GROUP) == NVIC_PriorityGroup_3) || \
                                       ((GROUP) == NVIC_PriorityGroup_4))
/**
  * @}
  */

#define IS_NVIC_PREEMPTION_PRIORITY(PRIORITY)  ((PRIORITY) < 0x10)

#define IS_NVIC_SUB_PRIORITY(PRIORITY)  ((PRIORITY) < 0x10)

#define IS_NVIC_OFFSET(OFFSET)  ((OFFSET) < 0x000FFFFF)

/**
  * @brief  Configures the priority grouping: pre-emption priority and subpriority.
  * @param  NVIC_PriorityGroup: specifies the priority grouping bits length.
  *   This parameter can be one of the following values, ref as @ref NVIC_PriorityGroup:
  *     @arg NVIC_PriorityGroup_0: 0 bits for pre-emption priority
  *                                4 bits for subpriority
  *     @arg NVIC_PriorityGroup_1: 1 bits for pre-emption priority
  *                                3 bits for subpriority
  *     @arg NVIC_PriorityGroup_2: 2 bits for pre-emption priority
  *                                2 bits for subpriority
  *     @arg NVIC_PriorityGroup_3: 3 bits for pre-emption priority
  *                                1 bits for subpriority
  *     @arg NVIC_PriorityGroup_4: 4 bits for pre-emption priority
  *                                0 bits for subpriority
  * @retval None
  */
void NVIC_PriorityGroupConfig(uint32_t NVIC_PriorityGroup);

/**
  * @brief  Initializes the NVIC peripheral according to the specified
  *         parameters in the NVIC_InitStruct.
  * @param  NVIC_InitStruct: pointer to a NVIC_InitTypeDef structure that contains
  *         the configuration information for the specified NVIC peripheral.
  * @retval None
  */
void NVIC_Init(NVIC_InitTypeDef* NVIC_InitStruct);

/**
  * @brief  Sets the vector table location and Offset.
  * @param  NVIC_VectTab: specifies if the vector table is in RAM or FLASH memory.
  *   This parameter can be one of the following values, ref as @ref NVIC_VectTab:
  *     @arg NVIC_VectTab_RAM
  *     @arg NVIC_VectTab_FLASH
  * @param  Offset: Vector Table base offset field. This value must be a multiple
  *         of 0x200.
  * @retval None
  */
void NVIC_SetVectorTable(uint32_t NVIC_VectTab, uint32_t Offset);

/**
  * @brief  Selects the condition for the system to enter low power mode.
  * @param  LowPowerMode: Specifies the new mode for the system to enter low power mode.
  *   This parameter can be one of the following values, ref as @ref NVIC_LP:
  *     @arg NVIC_LP_SEVONPEND
  *     @arg NVIC_LP_SLEEPDEEP
  *     @arg NVIC_LP_SLEEPONEXIT
  * @param  NewState: new state of LP condition. This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void NVIC_SystemLPConfig(uint8_t LowPowerMode, BOOL NewState);

/**
  * @brief  Memory map from address 'from' to 'address 'to' and open icache or not
    * @param[in] from address to be mapped from
    * @param[in] to address to be mapped to
    * @param[in] isIcacheOn icache is on or off
  * @retval None
    */
void GLB_MMAP(uint32_t from, uint32_t to, BOOL isIcacheOn);

/**
  * @brief  Convert the mapping destination address to source address
    * @param[in] to address to be mapped to
  * @retval uint32_t address to be mapped from
    */
uint32_t GLB_ConvertToMappingFromAddr(uint32_t to);

/**
  * @brief  Convert the mapping source address to destination address
    * @param[in] from address to be mapped from
  * @retval uint32_t address to be mapped to
    */
uint32_t GLB_ConvertToMappingToAddr(uint32_t from);

/**
  * @brief  Set NMI irq number, it should be one of @ref IRQn_Type.
    * @Note     You can assign any valid IRQn_Type to NMI. After that, you will enter NMI
    *                   interrupt routine if the specific 'irq' occurs. By default, NMI irq number
    *                   is 0, same as ETH_INT_IRQn
    * @param[in] irq irq number
  * @retval None
    */
void GLB_SetNmiIrqNum(uint32_t irq);

/** @defgroup SYS_CLK_SEL
  * @{
  */
#define SYS_CLK_SEL_OSC                 0x0
#define SYS_CLK_SEL_DLL                 0x1
#define SYS_CLK_SEL_CRYSTAL         0x2
#define SYS_CLK_SEL_EXTERNAL        0x3
/**
  * @}
  */

/**
  * @brief  Select system clock source, it should be one of @ref SYS_CLK_SEL.
    * @Note     You MUST make sure externel clock has been stabled if clock
    *                 source is external before call this function.
    *               Default value is SYS_CLK_SEL_OSC
    * @param[in] irq irq number
  * @retval None
    */
void GLB_SelectSysClkSource(uint8_t source);

/**
  * @brief  Simulate instruction 'STRB' or 'STRH' with 'BFI'
    * @Note     In M7, you have to write a register in 32-bit alignment,
    *                 not in 8-bit or 16-bit.
    * @param[in] addr register address to be written
  * @param[in] value value to be written
  * @param[in] lsb LSB in register to be written
  * @param[in] len bit length to be written
  * @retval None
    */


//#define aaaa(len) __asm("LDR len, 11")

#define CMEM7_BFI(addr, value, lsb, len)        \
  do {                                          \
    unsigned long tmp;                          \
    unsigned long tmp1 = (unsigned long)addr;   \
                                                \
    __asm("LDR tmp, [tmp1]\n"                   \
      "BFI tmp, "#value", "#lsb", "#len" \n"    \
      "STR tmp, [tmp1]\n");                     \
        } while (0)

#ifdef __cplusplus
}
#endif

#endif /* __CMEM7_MISC_H */

