/**
  ******************************************************************************
  * @brief   DMA header file of the firmware library.
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __GD32F10X_DMA_H
#define __GD32F10X_DMA_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "gd32f10x.h"

/** @addtogroup GD32F10x_Firmware
  * @{
  */

/** @addtogroup DMA
  * @{
  */

/** @defgroup DMA_Exported_Types
  * @{
  */

/**
  * @brief  DMA Initial Parameters
  */

typedef struct {
    uint32_t DMA_PeripheralBaseAddr;              /*!< The base address of the peripheral. */

    uint32_t DMA_MemoryBaseAddr;                  /*!< The base address of the memory. */

    uint32_t DMA_DIR;                             /*!< The direction of data transmission.
                                                       detailed in @ref DMA_data_transfer_direction */

    uint32_t DMA_BufferSize;                      /*!< The buffer size of data transmission. */

    uint32_t DMA_PeripheralInc;                   /*!< The incremented_mode of the Peripheral address register.
                                                       detailed in @ref DMA_peripheral_Address_incremented_mode */

    uint32_t DMA_MemoryInc;                       /*!< The incremented_mode of the memory address register.
                                                       detailed in @ref DMA_memory_Address_incremented_mode */

    uint32_t DMA_PeripheralDataSize;              /*!< The data transmission width of Peripheral.
                                                       detailed in @ref DMA_peripheral_data_size */

    uint32_t DMA_MemoryDataSize;                  /*!< The data transmission width of Memory.
                                                       detailed in @ref DMA_memory_data_size */

    uint32_t DMA_Mode;                            /*!< The mode of circular transmission.
                                                       detailed in @ref DMA_circular_normal_mode */

    uint32_t DMA_Priority;                        /*!< The software priority for the DMAy Channelx.
                                                       detailed in @ref DMA_priority_level */
    uint32_t DMA_MTOM;                            /*!< The mode of memory-to-memory transfer.
                                                       detailed in @ref DMA_memory_to_memory */
} DMA_InitPara;

/**
  * @}
  */

/** @defgroup DMA_Exported_Constants
  * @{
  */

/** @defgroup DMA_data_transfer_direction
  * @{
  */

#define DMA_DIR_PERIPHERALDST              DMA_CTLR_DIR
#define DMA_DIR_PERIPHERALSRC              ((uint32_t)0x00000000)
/**
  * @}
  */

/** @defgroup DMA_peripheral_Address_Increasing_mode
  * @{
  */

#define DMA_PERIPHERALINC_ENABLE           DMA_CTLR_PNAGA
#define DMA_PERIPHERALINC_DISABLE          ((uint32_t)0x00000000)
/**
  * @}
  */

/** @defgroup DMA_memory_Address_Increasing_mode
  * @{
  */

#define DMA_MEMORYINC_ENABLE               DMA_CTLR_MNAGA
#define DMA_MEMORYINC_DISABLE              ((uint32_t)0x00000000)
/**
  * @}
  */

/** @defgroup DMA_peripheral_data_size
  * @{
  */

#define DMA_PERIPHERALDATASIZE_BYTE        ((uint32_t)0x00000000)
#define DMA_PERIPHERALDATASIZE_HALFWORD    DMA_CTLR_PSIZE_0
#define DMA_PERIPHERALDATASIZE_WORD        DMA_CTLR_PSIZE_1
/**
  * @}
  */

/** @defgroup DMA_memory_data_size
  * @{
  */

#define DMA_MEMORYDATASIZE_BYTE            ((uint32_t)0x00000000)
#define DMA_MEMORYDATASIZE_HALFWORD        DMA_CTLR_MSIZE_0
#define DMA_MEMORYDATASIZE_WORD            DMA_CTLR_MSIZE_1
/**
  * @}
  */

/** @defgroup DMA_circular_normal_mode
  * @{
  */

#define DMA_MODE_CIRCULAR                  DMA_CTLR_CIRC
#define DMA_MODE_NORMAL                    ((uint32_t)0x00000000)
/**
  * @}
  */

/** @defgroup DMA_priority_level
  * @{
  */

#define DMA_PRIORITY_VERYHIGH              DMA_CTLR_PRIO
#define DMA_PRIORITY_HIGH                  DMA_CTLR_PRIO_1
#define DMA_PRIORITY_MEDIUM                DMA_CTLR_PRIO_0
#define DMA_PRIORITY_LOW                   ((uint32_t)0x00000000)
/**
  * @}
  */

/** @defgroup DMA_memory_to_memory
  * @{
  */

#define DMA_MEMTOMEM_ENABLE                DMA_CTLR_MEMTOMEM
#define DMA_MEMTOMEM_DISABLE               ((uint32_t)0x00000000)
/**
  * @}
  */

/** @defgroup DMA_interrupts_definition
  * @{
  */

#define DMA_INT_TC                          DMA_CTLR_TCIE
#define DMA_INT_HT                          DMA_CTLR_HTIE
#define DMA_INT_ERR                         DMA_CTLR_ERRIE

#define DMA1_INT_GL1                        DMA_IFR_GIF1
#define DMA1_INT_TC1                        DMA_IFR_TCIF1
#define DMA1_INT_HT1                        DMA_IFR_HTIF1
#define DMA1_INT_ERR1                       DMA_IFR_ERRIF1
#define DMA1_INT_GL2                        DMA_IFR_GIF2
#define DMA1_INT_TC2                        DMA_IFR_TCIF2
#define DMA1_INT_HT2                        DMA_IFR_HTIF2
#define DMA1_INT_ERR2                       DMA_IFR_ERRIF2
#define DMA1_INT_GL3                        DMA_IFR_GIF3
#define DMA1_INT_TC3                        DMA_IFR_TCIF3
#define DMA1_INT_HT3                        DMA_IFR_HTIF3
#define DMA1_INT_ERR3                       DMA_IFR_ERRIF3
#define DMA1_INT_GL4                        DMA_IFR_GIF4
#define DMA1_INT_TC4                        DMA_IFR_TCIF4
#define DMA1_INT_HT4                        DMA_IFR_HTIF4
#define DMA1_INT_ERR4                       DMA_IFR_ERRIF4
#define DMA1_INT_GL5                        DMA_IFR_GIF5
#define DMA1_INT_TC5                        DMA_IFR_TCIF5
#define DMA1_INT_HT5                        DMA_IFR_HTIF5
#define DMA1_INT_ERR5                       DMA_IFR_ERRIF5
#define DMA1_INT_GL6                        DMA_IFR_GIF6
#define DMA1_INT_TC6                        DMA_IFR_TCIF6
#define DMA1_INT_HT6                        DMA_IFR_HTIF6
#define DMA1_INT_ERR6                       DMA_IFR_ERRIF6
#define DMA1_INT_GL7                        DMA_IFR_GIF7
#define DMA1_INT_TC7                        DMA_IFR_TCIF7
#define DMA1_INT_HT7                        DMA_IFR_HTIF7
#define DMA1_INT_ERR7                       DMA_IFR_ERRIF7

#define DMA2_INT_GL1                        ((uint32_t)0x10000001)
#define DMA2_INT_TC1                        ((uint32_t)0x10000002)
#define DMA2_INT_HT1                        ((uint32_t)0x10000004)
#define DMA2_INT_TE1                        ((uint32_t)0x10000008)
#define DMA2_INT_GL2                        ((uint32_t)0x10000010)
#define DMA2_INT_TC2                        ((uint32_t)0x10000020)
#define DMA2_INT_HT2                        ((uint32_t)0x10000040)
#define DMA2_INT_TE2                        ((uint32_t)0x10000080)
#define DMA2_INT_GL3                        ((uint32_t)0x10000100)
#define DMA2_INT_TC3                        ((uint32_t)0x10000200)
#define DMA2_INT_HT3                        ((uint32_t)0x10000400)
#define DMA2_INT_TE3                        ((uint32_t)0x10000800)
#define DMA2_INT_GL4                        ((uint32_t)0x10001000)
#define DMA2_INT_TC4                        ((uint32_t)0x10002000)
#define DMA2_INT_HT4                        ((uint32_t)0x10004000)
#define DMA2_INT_TE4                        ((uint32_t)0x10008000)
#define DMA2_INT_GL5                        ((uint32_t)0x10010000)
#define DMA2_INT_TC5                        ((uint32_t)0x10020000)
#define DMA2_INT_HT5                        ((uint32_t)0x10040000)
#define DMA2_INT_TE5                        ((uint32_t)0x10080000)


/**
  * @}
  */

/** @defgroup DMA_flags_definition
  * @{
  */
#define DMA1_FLAG_GL1                       DMA_IFR_GIF1
#define DMA1_FLAG_TC1                       DMA_IFR_TCIF1
#define DMA1_FLAG_HT1                       DMA_IFR_HTIF1
#define DMA1_FLAG_ERR1                      DMA_IFR_ERRIF1
#define DMA1_FLAG_GL2                       DMA_IFR_GIF2
#define DMA1_FLAG_TC2                       DMA_IFR_TCIF2
#define DMA1_FLAG_HT2                       DMA_IFR_HTIF2
#define DMA1_FLAG_ERR2                      DMA_IFR_ERRIF2
#define DMA1_FLAG_GL3                       DMA_IFR_GIF3
#define DMA1_FLAG_TC3                       DMA_IFR_TCIF3
#define DMA1_FLAG_HT3                       DMA_IFR_HTIF3
#define DMA1_FLAG_ERR3                      DMA_IFR_ERRIF3
#define DMA1_FLAG_GL4                       DMA_IFR_GIF4
#define DMA1_FLAG_TC4                       DMA_IFR_TCIF4
#define DMA1_FLAG_HT4                       DMA_IFR_HTIF4
#define DMA1_FLAG_ERR4                      DMA_IFR_ERRIF4
#define DMA1_FLAG_GL5                       DMA_IFR_GIF5
#define DMA1_FLAG_TC5                       DMA_IFR_TCIF5
#define DMA1_FLAG_HT5                       DMA_IFR_HTIF5
#define DMA1_FLAG_ERR5                      DMA_IFR_ERRIF5
#define DMA1_FLAG_GL6                       DMA_IFR_GIF6
#define DMA1_FLAG_TC6                       DMA_IFR_TCIF6
#define DMA1_FLAG_HT6                       DMA_IFR_HTIF6
#define DMA1_FLAG_ERR6                      DMA_IFR_ERRIF6
#define DMA1_FLAG_GL7                       DMA_IFR_GIF7
#define DMA1_FLAG_TC7                       DMA_IFR_TCIF7
#define DMA1_FLAG_HT7                       DMA_IFR_HTIF7
#define DMA1_FLAG_ERR7                      DMA_IFR_ERRIF7

#define DMA2_FLAG_GL1                      ((uint32_t)0x10000001)
#define DMA2_FLAG_TC1                      ((uint32_t)0x10000002)
#define DMA2_FLAG_HT1                      ((uint32_t)0x10000004)
#define DMA2_FLAG_TE1                      ((uint32_t)0x10000008)
#define DMA2_FLAG_GL2                      ((uint32_t)0x10000010)
#define DMA2_FLAG_TC2                      ((uint32_t)0x10000020)
#define DMA2_FLAG_HT2                      ((uint32_t)0x10000040)
#define DMA2_FLAG_TE2                      ((uint32_t)0x10000080)
#define DMA2_FLAG_GL3                      ((uint32_t)0x10000100)
#define DMA2_FLAG_TC3                      ((uint32_t)0x10000200)
#define DMA2_FLAG_HT3                      ((uint32_t)0x10000400)
#define DMA2_FLAG_TE3                      ((uint32_t)0x10000800)
#define DMA2_FLAG_GL4                      ((uint32_t)0x10001000)
#define DMA2_FLAG_TC4                      ((uint32_t)0x10002000)
#define DMA2_FLAG_HT4                      ((uint32_t)0x10004000)
#define DMA2_FLAG_TE4                      ((uint32_t)0x10008000)
#define DMA2_FLAG_GL5                      ((uint32_t)0x10010000)
#define DMA2_FLAG_TC5                      ((uint32_t)0x10020000)
#define DMA2_FLAG_HT5                      ((uint32_t)0x10040000)
#define DMA2_FLAG_TE5                      ((uint32_t)0x10080000)

/**
  * @}
  */

/**
  * @}
  */



/** @defgroup DMA_Exported_Functions
  * @{
  */

/* Function used to reset the DMA configuration */
void DMA_DeInit(DMA_Channel_TypeDef *DMAy_Channelx);

/* The functions of Initialization and Configuration */
void DMA_Init(DMA_Channel_TypeDef *DMAy_Channelx, DMA_InitPara *DMA_InitParaStruct);
void DMA_ParaInit(DMA_InitPara *DMA_InitParaStruct);
void DMA_Enable(DMA_Channel_TypeDef *DMAy_Channelx, TypeState NewValue);

/* The functions of Data Counter */
void DMA_SetCurrDataCounter(DMA_Channel_TypeDef *DMAy_Channelx, uint16_t DataNumber);
uint16_t DMA_GetCurrDataCounter(DMA_Channel_TypeDef *DMAy_Channelx);

/* The functions of Interrupts and flags management */
void DMA_INTConfig(DMA_Channel_TypeDef *DMAy_Channelx, uint32_t DMA_INT, TypeState NewValue);
TypeState DMA_GetBitState(uint32_t DMA_FLAG);
void DMA_ClearBitState(uint32_t DMA_FLAG);
TypeState DMA_GetIntBitState(uint32_t DMA_INT);
void DMA_ClearIntBitState(uint32_t DMA_INT);

#ifdef __cplusplus
}
#endif

#endif /*__GD32F10x_DMA_H */
/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */
