/**
  ******************************************************************************
  * @file               ft32f4xx_qspi.h
  * @author             FMD AE
  * @brief              This file contains all the functions prototypes for the QSPI
  *                     firmware library.
  * @version            V1.0.0
  * @data                   2025-03-06
  ******************************************************************************
  */


/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __FT32F4XX_QSPI_H
#define __FT32F4XX_QSPI_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "ft32f4xx.h"


/** @addtogroup QSPI
  * @{
  */

/* Exported types ------------------------------------------------------------*/

/**
  * @brief  QSPI Init structure definition
  */

typedef struct
{

    uint32_t QSPI_Protocol;            /*!< Specifies which QSPI serial proptocol is selected.
                                         This parameter can be a value of @ref QSPI_Protocol_Sel . */

    uint32_t QSPI_Direction;           /*!< Specifies the QSPI transfer mode.
                                         This parameter can be a value of @ref QSPI_data_direction. */

    uint32_t QSPI_SSTE;                /*!< Specifies the QSPI NCSX Toggle Enable.
                                         This parameter can be a value of @ref QSPI_SSTE_Enable . */

    uint32_t QSPI_DataSize;            /*!< Specifies the QSPI data size.
                                         This parameter can be a value of @ref QSPI_data_size. */

    uint32_t QSPI_SCPOL;               /*!< Specifies the serial clock steady state.
                                         This parameter can be a value of @ref QSPI_Clock_Polarity. */

    uint32_t QSPI_SCPHA;               /*!< Specifies the clock active edge for the bit capture.
                                         This parameter can be a value of @ref QSPI_Clock_Phase */

    uint32_t QSPI_SER;                 /*!< Specifies which NCSx line is selected.
                                         This parameter can be a value of @ref QSPI_SER_SEL. */

    uint32_t QSPI_BaudRatePrescaler;   /*!< Specifies the Baud Rate prescaler value which will be
                                         used to configure the transmit and receive SCK clock.
                                         This parameter can be a value (15-bits) between 0x0 and 0xEFFF.
                                         @note The communication clock is derived from the master
                                         clock. The slave clock does not need to be set. */

    uint32_t QSPI_CS_MIN_HIGH;         /*!< Specifies the CS mini high time
                                        This parameter can be a value (8 bits) between 0x0 and 0xF. */

    uint32_t QSPI_DataMode;            /* Specifies the Data Mode (used for dummy cycles and data phases)
                                       This parameter can be a value of @ref QSPI_DataMode */

} QSPI_InitTypeDef;


/* Exported constants --------------------------------------------------------*/
/** @defgroup SPI_Exported_Constants
  * @{
  */


/** @defgroup
  * @{
  */

#define QSPI_STANDARD                    ((uint32_t)0x00000000)
#define QSPI_DUAL                        ((uint32_t)0x00400000)
#define QSPI_QUAD                        ((uint32_t)0x00800000)
#define IS_QSPI_DATA_MODE(MODE)  (((MODE) == QSPI_STANDARD) || \
                                   ((MODE) == QSPI_DUAL) || \
                                   ((MODE) == QSPI_QUAD))
/**
  * @}
  */

/** @defgroup QSPI_SER_SEL
  * @{
  */

#define QSPI_NCS0                        ((uint32_t)0x00000001)
#define QSPI_NCS1                        ((uint32_t)0x00000002)
#define IS_QSPI_SER_SEL(MODE)     (((MODE) == QSPI_NCS0) || \
                                   ((MODE) == QSPI_NCS1))
/**
  * @}
  */

/** @defgroup QSPI_data_direction
  * @{
  */

#define QSPI_DIRECTION_Tx_AND_Rx         ((uint32_t)0x00000000)
#define QSPI_DIRECTION_Tx_ONLY           ((uint32_t)0x00000400)
#define QSPI_DIRECTION_Rx_ONLY           ((uint32_t)0x00000800)
#define QSPI_DIRECTION_EEPROM_READ       ((uint32_t)0x00000C00)
#define IS_QSPI_DIRECTION_MODE(MODE) (((MODE) == QSPI_DIRECTION_Tx_AND_Rx) || \
                                      ((MODE) == QSPI_DIRECTION_Tx_ONLY) || \
                                      ((MODE) == QSPI_DIRECTION_Rx_ONLY) || \
                                      ((MODE) == QSPI_DIRECTION_EEPROM_READ))
/**
  * @}
  */

/** @defgroup QSPI_SSTE_Enable
  * @{
  */

#define QSPI_SSTE_TOGGLE_DIS             ((uint32_t)0x00000000)
#define QSPI_SSTE_TOGGLE_EN              ((uint32_t)0x00004000)
#define IS_QSPI_SSTE(MODE)  (((MODE) == QSPI_TOGGLE_DIS) || \
                             ((MODE) == QSPI_TOGGLE_EN))
/**
  * @}
  */



/** @defgroup QSPI_data_size
  * @{
  */

#define QSPI_DATASIZE_4B                 ((uint32_t)0x00000003)
#define QSPI_DATASIZE_5B                 ((uint32_t)0x00000004)
#define QSPI_DATASIZE_6B                 ((uint32_t)0x00000005)
#define QSPI_DATASIZE_7B                 ((uint32_t)0x00000006)
#define QSPI_DATASIZE_8B                 ((uint32_t)0x00000007)
#define QSPI_DATASIZE_9B                 ((uint32_t)0x00000008)
#define QSPI_DATASIZE_10B                ((uint32_t)0x00000009)
#define QSPI_DATASIZE_11B                ((uint32_t)0x0000000a)
#define QSPI_DATASIZE_12B                ((uint32_t)0x0000000b)
#define QSPI_DATASIZE_13B                ((uint32_t)0x0000000c)
#define QSPI_DATASIZE_14B                ((uint32_t)0x0000000d)
#define QSPI_DATASIZE_15B                ((uint32_t)0x0000000e)
#define QSPI_DATASIZE_16B                ((uint32_t)0x0000000f)
#define QSPI_DATASIZE_17B                ((uint32_t)0x00000010)
#define QSPI_DATASIZE_18B                ((uint32_t)0x00000011)
#define QSPI_DATASIZE_19B                ((uint32_t)0x00000012)
#define QSPI_DATASIZE_20B                ((uint32_t)0x00000013)
#define QSPI_DATASIZE_21B                ((uint32_t)0x00000014)
#define QSPI_DATASIZE_22B                ((uint32_t)0x00000015)
#define QSPI_DATASIZE_23B                ((uint32_t)0x00000016)
#define QSPI_DATASIZE_24B                ((uint32_t)0x00000017)
#define QSPI_DATASIZE_25B                ((uint32_t)0x00000018)
#define QSPI_DATASIZE_26B                ((uint32_t)0x00000019)
#define QSPI_DATASIZE_27B                ((uint32_t)0x0000001a)
#define QSPI_DATASIZE_28B                ((uint32_t)0x0000001b)
#define QSPI_DATASIZE_29B                ((uint32_t)0x0000001c)
#define QSPI_DATASIZE_30B                ((uint32_t)0x0000001d)
#define QSPI_DATASIZE_31B                ((uint32_t)0x0000001e)
#define QSPI_DATASIZE_32B                ((uint32_t)0x0000001f)
#define IS_QSPI_DATA_SIZE(SIZE) (((SIZE) == QSPI_DATASIZE_4B) || \
                                 ((SIZE) == QSPI_DATASIZE_5B) || \
                                 ((SIZE) == QSPI_DATASIZE_6B) || \
                                 ((SIZE) == QSPI_DATASIZE_7B) || \
                                 ((SIZE) == QSPI_DATASIZE_8B) || \
                                 ((SIZE) == QSPI_DATASIZE_9B) || \
                                 ((SIZE) == QSPI_DATASIZE_10B) || \
                                 ((SIZE) == QSPI_DATASIZE_11B) || \
                                 ((SIZE) == QSPI_DATASIZE_12B) || \
                                 ((SIZE) == QSPI_DATASIZE_13B) || \
                                 ((SIZE) == QSPI_DATASIZE_14B) || \
                                 ((SIZE) == QSPI_DATASIZE_15B) || \
                                 ((SIZE) == QSPI_DATASIZE_16B) || \
                                 ((SIZE) == QSPI_DATASIZE_17B) || \
                                 ((SIZE) == QSPI_DATASIZE_18B) || \
                                 ((SIZE) == QSPI_DATASIZE_19B) || \
                                 ((SIZE) == QSPI_DATASIZE_20B) || \
                                 ((SIZE) == QSPI_DATASIZE_21B) || \
                                 ((SIZE) == QSPI_DATASIZE_22B) || \
                                 ((SIZE) == QSPI_DATASIZE_23B) || \
                                 ((SIZE) == QSPI_DATASIZE_24B) || \
                                 ((SIZE) == QSPI_DATASIZE_25B) || \
                                 ((SIZE) == QSPI_DATASIZE_26B) || \
                                 ((SIZE) == QSPI_DATASIZE_27B) || \
                                 ((SIZE) == QSPI_DATASIZE_28B) || \
                                 ((SIZE) == QSPI_DATASIZE_29B) || \
                                 ((SIZE) == QSPI_DATASIZE_30B) || \
                                 ((SIZE) == QSPI_DATASIZE_31B) || \
                                 ((SIZE) == QSPI_DATASIZE_32B))
/**
  * @}
  */

/** @defgroup QSPI_Microwire_CFS
  * @{
  */
#define QSPI_CFS_1B                      ((uint32_t)0x00000000)
#define QSPI_CFS_2B                      ((uint32_t)0x00010000)
#define QSPI_CFS_3B                      ((uint32_t)0x00020000)
#define QSPI_CFS_4B                      ((uint32_t)0x00030000)
#define QSPI_CFS_5B                      ((uint32_t)0x00040000)
#define QSPI_CFS_6B                      ((uint32_t)0x00050000)
#define QSPI_CFS_7B                      ((uint32_t)0x00060000)
#define QSPI_CFS_8B                      ((uint32_t)0x00070000)
#define QSPI_CFS_9B                      ((uint32_t)0x00080000)
#define QSPI_CFS_10B                     ((uint32_t)0x00090000)
#define QSPI_CFS_11B                     ((uint32_t)0x000a0000)
#define QSPI_CFS_12B                     ((uint32_t)0x000b0000)
#define QSPI_CFS_13B                     ((uint32_t)0x000c0000)
#define QSPI_CFS_14B                     ((uint32_t)0x000d0000)
#define QSPI_CFS_15B                     ((uint32_t)0x000e0000)
#define QSPI_CFS_16B                     ((uint32_t)0x000f0000)
#define IS_QSPI_CFS_SIZE(SIZE) (((SIZE) == QSPI_CFS_1B) || \
                                ((SIZE) == QSPI_CFS_2B) || \
                                ((SIZE) == QSPI_CFS_3B) || \
                                ((SIZE) == QSPI_CFS_4B) || \
                                ((SIZE) == QSPI_CFS_5B) || \
                                ((SIZE) == QSPI_CFS_6B) || \
                                ((SIZE) == QSPI_CFS_7B) || \
                                ((SIZE) == QSPI_CFS_8B) || \
                                ((SIZE) == QSPI_CFS_9B) || \
                                ((SIZE) == QSPI_CFS_10B) || \
                                ((SIZE) == QSPI_CFS_11B) || \
                                ((SIZE) == QSPI_CFS_12B) || \
                                ((SIZE) == QSPI_CFS_13B) || \
                                ((SIZE) == QSPI_CFS_14B) || \
                                ((SIZE) == QSPI_CFS_15B) || \
                                ((SIZE) == QSPI_CFS_16B))

/**
  * @}
  */


/** @defgroup QSPI_Clock_Polarity
  * @{
  */

#define QSPI_SCPOL_LOW                   ((uint32_t)0x00000000)
#define QSPI_SCPOL_HIGH                  ((uint32_t)0x00000200)
#define IS_QSPI_SCPOL(SCPOL) (((SCPOL) == QSPI_CPOL_LOW) || \
                             ((SCPOL) == QSPI_CPOL_HIGH))
/**
  * @}
  */

/** @defgroup QSPI_Clock_Phase
  * @{
  */

#define QSPI_SCPHA_1EDGE                 ((uint32_t)0x00000000)
#define QSPI_SCPHA_2EDGE                 ((uint32_t)0x00000100)
#define IS_QSPI_SCPHA(SCPHA) (((SCPHA) == QSPI_CPHA_1EDGE) || \
                             ((SCPHA) == QSPI_CPHA_2EDGE))
/**
  * @}
  */

/** @defgroup QSPI_Protocol_Sel
  * @{
  */

#define QSPI_PROTOCOL_SPI                ((uint32_t)0x00000000)
#define QSPI_PROTOCOL_SSP                ((uint32_t)0x00000040)
#define QSPI_PROTOCOL_MICROWIRE          ((uint32_t)0x00000080)
#define IS_QSPI_PROPTOCOL(PROTOCOL) (((PROTOCOL) == QSPI_PROTOCOL_QSPI) || \
                                    ((PROTOCOL) == QSPI_PROTOCOL_SSP) || \
                                    ((PROTOCOL) == QSPI_Protocol_MICROWIRE))
/**
  * @}
  */

/** @defgroup QSPI_Opration_Mode
  * @{
  */

#define QSPI_NORMAL_MODE                ((uint32_t)0x00000000)
#define QSPI_TESTING_MODE               ((uint32_t)0x00002000)
#define IS_QSPI_OPERATION_MODE(MODE) (((MODE) == QSPI_NORMAL_MODE) || \
                                     ((MODE) == QSPI_TESTING_MODE))
/**
  * @}
  */

/** @defgroup QSPI_TDMA_EN
  * @{
  */

#define QSPI_TDMA_DIS                   ((uint32_t)0x00000000)
#define QSPI_TDMA_EN                    ((uint32_t)0x00000002)
#define IS_QSPI_TDMA_MODE(MODE) (((MODE) == QSPI_TDMA_DIS) || \
                                 ((MODE) == QSPI_TDMA_EN))
/**
  * @}
  */

/** @defgroup QSPI_RDMA_EN
  * @{
  */

#define QSPI_RDMA_DIS                   ((uint32_t)0x00000000)
#define QSPI_RDMA_EN                    ((uint32_t)0x00000001)
#define IS_QSPI_RDMA_MODE(MODE) (((MODE) == QSPI_RDMA_DIS) || \
                                 ((MODE) == QSPI_RDMA_EN))
/**
  * @}
  */

/** @defgroup QSPI_Clk_Loop_EN
  * @{
  */

#define QSPI_CLK_LOOP_DIS               ((uint32_t)0x00000000)
#define QSPI_CLK_LOOP_EN                ((uint32_t)0x04000000)
#define IS_QSPI_CLK_LOOP_EN(MODE) (((MODE) == QSPI_CLK_LOOP_DIS) || \
                                   ((MODE) == QSPI_CLK_LOOP_EN))
/**
  * @}
  */

/** @defgroup QSPI_Read_strobe_En.
  * @{
  */
#define QSPI_READ_STROBE_DIS            ((uint32_t)0x00000000)
#define QSPI_READ_STROBE_EN             ((uint32_t)0x00040000)
#define IS_QSPI_RXDS_EN(MODE) (((MODE) == QSPI_READ_STROBE_DIS) || \
                               ((MODE) == QSPI_READ_STROBE_EN))

/**
  * @}
  */

/** @defgroup QSPI_Variable_Laten
  * @{
  */
#define QSPI_VARIABLE_LATEN_DIS         ((uint32_t)0x00000000)
#define QSPI_VARIABLE_LATEN_EN          ((uint32_t)0x00800000)
#define IS_QSPI_VL_EN(MODE) (((MODE) == QSPI_VARIABLE_LATEN_DIS) || \
                             ((MODE) == QSPI_VARIABLE_LATEN_EN))

/**
  * @}
  */

/** @defgroup QSPI_Sample_Edge.
  * @{
  */
#define QSPI_SAMPLE_POSEDGE             ((uint32_t)0x00000000)
#define QSPI_SAMPLE_NEGEDGE             ((uint32_t)0x00010000)
#define IS_QSPI_SAMPLE_DLY_EDGE(MODE) (((MODE) == QSPI_SAMPLE_POSEDGE) || \
                                       ((MODE) == QSPI_SAMPLE_NEGEDGE))
/**
  * @}
  */

/** @defgroup QSPI_InstructionSize
  * @{
  */
#define QSPI_INSTRUCTION_0B             ((uint32_t)0x00000000)
#define QSPI_INSTRUCTION_4B             ((uint32_t)0x00000100)
#define QSPI_INSTRUCTION_8B             ((uint32_t)0x00000200)
#define QSPI_INSTRUCTION_16B            ((uint32_t)0x00000300)
#define IS_QSPI_INSTRUCTIONSIZE(SIZE) (((SIZE) == QSPI_INSTRUCTION_0B) || \
                                       ((SIZE) == QSPI_INSTRUCTION_4B) || \
                                       ((SIZE) == QSPI_INSTRUCTION_8B) || \
                                       ((SIZE) == QSPI_INSTRUCTION_16B))
/**
  * @}
  */

/** @defgroup QSPI_AddressSize
  * @{
  */
#define QSPI_ADDRESS_0B                 ((uint32_t)0x00000000)
#define QSPI_ADDRESS_4B                 ((uint32_t)0x00000004)
#define QSPI_ADDRESS_8B                 ((uint32_t)0x00000008)
#define QSPI_ADDRESS_12B                ((uint32_t)0x0000000c)
#define QSPI_ADDRESS_16B                ((uint32_t)0x00000010)
#define QSPI_ADDRESS_20B                ((uint32_t)0x00000014)
#define QSPI_ADDRESS_24B                ((uint32_t)0x00000018)
#define QSPI_ADDRESS_28B                ((uint32_t)0x0000001c)
#define QSPI_ADDRESS_32B                ((uint32_t)0x00000020)
#define QSPI_ADDRESS_36B                ((uint32_t)0x00000024)
#define QSPI_ADDRESS_40B                ((uint32_t)0x00000028)
#define QSPI_ADDRESS_44B                ((uint32_t)0x0000002c)
#define QSPI_ADDRESS_48B                ((uint32_t)0x00000030)
#define QSPI_ADDRESS_52B                ((uint32_t)0x00000034)
#define QSPI_ADDRESS_56B                ((uint32_t)0x00000038)
#define QSPI_ADDRESS_60B                ((uint32_t)0x0000003c)
#define IS_QSPI_ADDRESSSIZE(SIZE) (((SIZE) == QSPI_ADDRESS_0B) || \
                                   ((SIZE) == QSPI_ADDRESS_4B) || \
                                   ((SIZE) == QSPI_ADDRESS_8B) || \
                                   ((SIZE) == QSPI_ADDRESS_12B) || \
                                   ((SIZE) == QSPI_ADDRESS_16B) || \
                                   ((SIZE) == QSPI_ADDRESS_20B) || \
                                   ((SIZE) == QSPI_ADDRESS_24B) || \
                                   ((SIZE) == QSPI_ADDRESS_28B) || \
                                   ((SIZE) == QSPI_ADDRESS_32B) || \
                                   ((SIZE) == QSPI_ADDRESS_36B) || \
                                   ((SIZE) == QSPI_ADDRESS_40B) || \
                                   ((SIZE) == QSPI_ADDRESS_44B) || \
                                   ((SIZE) == QSPI_ADDRESS_48B) || \
                                   ((SIZE) == QSPI_ADDRESS_52B) || \
                                   ((SIZE) == QSPI_ADDRESS_56B) || \
                                   ((SIZE) == QSPI_ADDRESS_60B))
/**
  * @}
  */

/** @defgroup QSPI_ModeBitsSize
  * @{
  */
#define QSPI_MODEBITS_2B             ((uint32_t)0x00000000)
#define QSPI_MODEBITS_4B             ((uint32_t)0x04000000)
#define QSPI_MODEBITS_8B             ((uint32_t)0x08000000)
#define QSPI_MODEBITS_16B            ((uint32_t)0x0c000000)
#define IS_QSPI_MODEBITSSIZE(SIZE) (((SIZE) == QSPI_MODEBITS_2B) || \
                                    ((SIZE) == QSPI_MODEBITS_4B) || \
                                    ((SIZE) == QSPI_MODEBITS_8B) || \
                                    ((SIZE) == QSPI_MODEBITS_16B))
/**
  * @}
  */
/** @defgroup QSPI_XIPInstructionEn
  * @{
  */
#define QSPI_INSTRUCTION_DIS         ((uint32_t)0x00000000)
#define QSPI_INSTRUCTION_EN          ((uint32_t)0x00100000)
#define IS_QSPI_INSTRUCTION(MODE) (((MODE) == QSPI_INSTRUCTION_DIS) || \
                                   ((MODE) == QSPI_INSTRUCTION_EN))
/**
  * @}
  */

/** @defgroup QSPI_ModeBitsEn
  * @{
  */
#define QSPI_MODEBITS_DIS            ((uint32_t)0x00000000)
#define QSPI_MODEBITS_EN             ((uint32_t)0x00000080)
#define IS_QSPI_MODEBITS(MODE) (((MODE) == QSPI_MODEBITS_DIS) || \
                                ((MODE) == QSPI_MODEBITS_EN))
/**
  * @}
  */

/** @defgroup QSPI_transType
  * @{
  */
#define QSPI_TRANSTYPE_STAND         ((uint32_t)0x00000000)
#define QSPI_TRANSTYPE_MIX           ((uint32_t)0x00000001)
#define QSPI_TRANSTYPE_FRF           ((uint32_t)0x00000002)
#define IS_QSPI_TRANSTYPE(MODE)   (((MODE) == QSPI_TRANSTYPE_STAND) || \
                                   ((MODE) == QSPI_TRANSTYPE_MIX) || \
                                   ((MODE) == QSPI_TRANSTYPE_FRF))
/**
  * @}
  */

/** @defgroup QSPI_ClkstretchEn
  * @{
  */
#define QSPI_CLKSTRETCH_DIS          ((uint32_t)0x00000000)
#define QSPI_CLKSTRETCH_EN           ((uint32_t)0x40000000)
#define IS_QSPI_CLKSTRETCH(MODE) (((MODE) == QSPI_CLKSTRETCH_DIS) || \
                                  ((MODE) == QSPI_CLKSTRETCH_EN))
/**
  * @}
  */

/** @defgroup QSPI_DdrMode
  * @{
  */
#define QSPI_DDRMODE_DIS             ((uint32_t)0x00000000)
#define QSPI_DDRMODE_EN              ((uint32_t)0x00010000)
#define IS_QSPI_DDRMODE(MODE) (((MODE) == QSPI_DDRMODE_DIS) || \
                               ((MODE) == QSPI_DDRMODE_EN))
/**
  * @}
  */

/** @defgroup QSPI_InstDdrMode
  * @{
  */
#define QSPI_INSTDDRMODE_DIS         ((uint32_t)0x00000000)
#define QSPI_INSTDDRMODE_EN          ((uint32_t)0x00020000)
#define IS_QSPI_INSTDDRMODE(MODE) (((MODE) == QSPI_INSTDDRMODE_DIS) || \
                                   ((MODE) == QSPI_INSTDDRMODE_EN))
/**
  * @}
  */

/** @defgroup QSPI_XIP_DFS
  * @{
  */
#define QSPI_XIP_DFS_DIS             ((uint32_t)0x00000000)
#define QSPI_XIP_DFS_EN              ((uint32_t)0x00080000)
#define IS_QSPI_XIP_DFS(MODE) (((MODE) == QSPI_XIP_DFS_DIS) || \
                               ((MODE) == QSPI_XIP_DFS_EN))
/**
  * @}
  */

/** @defgroup QSPI_XIP_Cont
  * @{
  */
#define QSPI_XIP_CONT_DIS            ((uint32_t)0x00000000)
#define QSPI_XIP_CONT_EN             ((uint32_t)0x00200000)
#define IS_QSPI_XIP_CONT(MODE) (((MODE) == QSPI_XIP_CONT_DIS) || \
                                ((MODE) == QSPI_XIP_CONT_EN))
/**
  * @}
  */

/** @defgroup QSPI_MicroHand
  * @{
  */
#define QSPI_MICROHAND_DIS             ((uint32_t)0x00000000)
#define QSPI_MICROHAND_EN              ((uint32_t)0x00000004)
#define IS_QSPI_MICROHAND(MODE) (((MODE) == QSPI_MICROHAND_DIS) || \
                                 ((MODE) == QSPI_MICROHAND_EN))
/**
  * @}
  */

/** @defgroup QSPI_MicroDir
  * @{
  */
#define QSPI_MICRODIR_Rx               ((uint32_t)0x00000000)
#define QSPI_MICRODIR_Tx               ((uint32_t)0x00000002)
#define IS_QSPI_MICRODIR(MODE)  (((MODE) == QSPI_MICRODIR_Rx) || \
                                 ((MODE) == QSPI_MICRODIR_Tx))
/**
  * @}
  */

/** @defgroup QSPI_MicroTrans
  * @{
  */
#define QSPI_MICROTRANS_NSEQ           ((uint32_t)0x00000000)
#define QSPI_MICROTRANS_SEQ            ((uint32_t)0x00000001)
#define IS_QSPI_MICROTRANS(MODE)  (((MODE) == QSPI_MICROTRANS_NSE) || \
                                   ((MODE) == QSPI_MICROTRANS_SEQ))
/**
  * @}
  */

/** @defgroup QSPI_DMAReq
  * @{
  */
#define QSPI_DMAReq_Tx                 ((uint32_t)0x00000002)
#define QSPI_DMAReq_Rx                 ((uint32_t)0x00000001)
#define IS_QSPI_DMA_REQ(MODE)  (((MODE) == QSPI_DMAReq_Tx) || \
                                ((MODE) == QSPI_DMAReq_Rx))
/**
  * @}
  */


#define IS_QSPI_DATANUMBER(SIZE) ((SIZE) <= 0xFFFFFFFF)
#define IS_QSPI_BR(BR) ((BR) <= 0x7FFF)


#define IS_QSPI_RX_FIFO_THRESHOLD(RFT)   ((RFT) <= 0xFU)
#define IS_QSPI_TX_FIFO_THRESHOLD(TFT)   ((TFT) <= 0xFU)
#define IS_QSPI_TX_FIFO_STARTLEVEL(TST)  ((TST) <= 0xFU)

#define IS_QSPI_DMA_RX_DATA_LEVEL(LEVEL) ((LEVEL) <= 0xFU)
#define IS_QSPI_DMA_TX_DATA_LEVEL(LEVEL) ((LEVEL) <= 0xFU)

#define IS_QSPI_WAITCYCLES(NUM) ((NUM) <= 0x1FU)

#define IS_QSPI_XIP_INST(INST) ((INST) <= 0xFFFF)
#define IS_QSPI_XIP_MODEBITS(MODE) ((MODE) <= 0xFFFF)
#define IS_QSPI_XIP_TIMOUT(TIME) ((TIME) <= 0xFFU)
#define IS_QSPI_DDR_DRIVE_EDGE(TDE) ((TDE) <= 0xFFU)
#define IS_QSPI_SAMPLE_DLY(DLY) ((DLY) <= 0xFFU)
/** @defgroup QSPI_interrupts_definition
  * @{
  */

#define QSPI_IT_TXEIM                ((uint8_t)0x01)
#define QSPI_IT_TXOIM                ((uint8_t)0x02)
#define QSPI_IT_RXUIM                ((uint8_t)0x04)
#define QSPI_IT_RXOIM                ((uint8_t)0x08)
#define QSPI_IT_RXFIM                ((uint8_t)0x10)
#define QSPI_IT_TXUIM                ((uint8_t)0x80)

#define IS_QSPI_CONFIG_IT(IT) (((IT) == QSPI_IT_TXEIM) || \
                               ((IT) == QSPI_IT_TXOIM) || \
                               ((IT) == QSPI_IT_RXUIM) || \
                               ((IT) == QSPI_IT_RXOIM) || \
                               ((IT) == QSPI_IT_RXFIM) || \
                               ((IT) == QSPI_IT_TXUIM))

/**
  * @}
  */


/** @defgroup QSPI_flags_definition
  * @{
  */
#define QSPI_STATE_BUSY                ((uint8_t) 0x01)
#define QSPI_STATE_TFNF                ((uint8_t) 0x02)
#define QSPI_STATE_TFE                 ((uint8_t) 0x04)
#define QSPI_STATE_RFNE                ((uint8_t) 0x08)
#define QSPI_STATE_RFF                 ((uint8_t) 0x10)

#define QSPI_FLAG_TXEIS                ((uint8_t)0x01)
#define QSPI_FLAG_TXOIS                ((uint8_t)0x02)
#define QSPI_FLAG_RXUIS                ((uint8_t)0x04)
#define QSPI_FLAG_RXOIS                ((uint8_t)0x08)
#define QSPI_FLAG_RXFIS                ((uint8_t)0x10)
#define QSPI_FLAG_TXUIS                ((uint8_t)0x80)

#define QSPI_FLAG_TXEIR                ((uint8_t)0x01)
#define QSPI_FLAG_TXOIR                ((uint8_t)0x02)
#define QSPI_FLAG_RXUIR                ((uint8_t)0x04)
#define QSPI_FLAG_RXOIR                ((uint8_t)0x08)
#define QSPI_FLAG_RXFIR                ((uint8_t)0x10)
#define QSPI_FLAG_TXUIR                ((uint8_t)0x80)

#define QSPI_FLAG_TXEICR               ((uint8_t)0x01)
#define QSPI_FLAG_RXOICR               ((uint8_t)0x01)
#define QSPI_FLAG_RXUICR               ((uint8_t)0x01)
#define QSPI_FLAG_ICR                  ((uint8_t)0x01)


#define IS_QSPI_TXE_CLEAR_FLAG(FLAG) (((FLAG) == QSPI_FLAG_TXEICR))
#define IS_QSPI_RXO_CLEAR_FLAG(FLAG) (((FLAG) == QSPI_FLAG_RXOICR))
#define IS_QSPI_RXU_CLEAR_FLAG(FLAG) (((FLAG) == QSPI_FLAG_RXUICR))
#define IS_QSPI_CLEAR_FLAG(FLAG)     (((FLAG) == QSPI_FLAG_ICR))

#define IS_QSPI_BeforMaskInterruptStatus(ST) (((ST) == QSPI_FLAG_TXEIR) || ((ST) == QSPI_FLAG_TXOIR) || \
                                              ((ST) == QSPI_FLAG_RXUIR) || ((ST) == QSPI_FLAG_RXOIR) || \
                                              ((ST) == QSPI_FLAG_RXFIR) || ((ST) == QSPI_FLAG_TXUIR))

#define IS_QSPI_AfterMaskInterruptStatus(ST) (((ST) == QSPI_FLAG_TXEIS) || ((ST) == QSPI_FLAG_TXEIS) || \
                                              ((ST) == QSPI_FLAG_RXUIS) || ((ST) == QSPI_FLAG_RXOIS) || \
                                              ((ST) == QSPI_FLAG_RXFIS) || ((ST) == QSPI_FLAG_TXUIS))

/**
  * @}
  */


/**
  * @}
  */

/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */

/* Initialization and Configuration functions *********************************/
void QSPI_DeInit(void);
void QSPI_Init(QSPI_InitTypeDef *QSPI_InitStruct, uint16_t Br);
void QSPI_StructInit(QSPI_InitTypeDef *QSPI_InitStruct);

/* QSPI Mode Configuration functions ******************************************/
void QSPI_TestMode_Enable(FunctionalState NewState);
void QSPI_MicroWireMode_Config(uint32_t MHS, uint32_t MDD, uint32_t MWMOD, uint32_t FrameSize, FunctionalState NewState);
void QSPI_EnCmd(FunctionalState NewState);
void QSPI_TIModeCmd(FunctionalState NewState);
void QSPI_SSTEModeCmd(FunctionalState NewState);
void QSPI_LineCfg(uint32_t LINE);
void QSPI_TransMode(uint32_t TRANS);
void QSPI_WaitCyclesConfig(uint32_t NUMBER);
void QSPI_TransTypeConfig(uint32_t TRANSTYPE);

/* Data transfers functions ***************************************************/
void QSPI_SendData(uint32_t Data);
uint32_t QSPI_ReceiveData(void);
void QSPI_DataSizeConfig(uint16_t QSPI_DataSize);
void QSPI_DataNumberConfig(uint32_t QSPI_NDF);

void QSPI_RxFIFOThresholdConfig(uint16_t QSPI_RxFIFOThreshold);
void QSPI_TxFIFOThresholdConfig(uint16_t QSPI_TxFIFOStart, uint16_t QSPI_TxFIFOThreshold);

/* DMA transfers management functions *****************************************/
void QSPI_DMACmd(uint32_t QSPI_DMAReq, FunctionalState NewState);
void QSPI_DMA_Tx_DATALEVELCmd(uint32_t QSPI_DMATxDLevel);
void QSPI_DMA_Rx_DATALEVELCmd(uint32_t QSPI_DMARxDLevel);

/* XIP transfers functions ****************************************************/
void QSPI_XIP_INSTCmd(uint32_t INSTRUCTION_L, FunctionalState NewState);
void QSPI_XIP_INST_Config(uint32_t QSPI_XIP_INSTCfg);
void QSPI_ADDRCfg(uint32_t ADDR_L);
void QSPI_XIP_ModeBitsCmd(uint32_t MODEBITS, uint32_t MD_SIZE, FunctionalState NewState);
void QSPI_Ddrcmd(uint32_t Ddr_TXD, FunctionalState NewState);
void QSPI_InstDdrcmd(FunctionalState NewState);
void QSPI_XIP_ContinuousCmd(uint32_t TIMOUT, FunctionalState NewState);
void QSPI_XIP_DFSHCCmd(FunctionalState NewState);

/* other receive data fonfigure function **************************************/
void QSPI_CLK_LOOPCmd(FunctionalState NewState);
void QSPI_RX_SAMPLEDLYConfig(uint32_t SE, uint32_t RSD);
void QSPI_RXDSConfig(uint32_t RXDS_VL_EN, FunctionalState NewState);
void QSPI_CLK_StretchCmd(FunctionalState NewState);

/* Interrupts and flags management functions **********************************/
void QSPI_ITConfig(uint32_t QSPI_IT, FunctionalState NewState);
uint32_t QSPI_GetStatus(uint16_t QSPI_SR_FLAG);
uint32_t QSPI_GetAfterMaskInterruptStatus(uint16_t QSPI_ISR_FLAG);
uint32_t QSPI_GetBeforeMaskInterruptStatus(uint16_t QSPI_RISR_FLAG);
void QSPI_ClearTxFIFOErrorInterrupt(void);
void QSPI_ClearRxFIFOOverflowInterrupt(void);
void QSPI_ClearRxFIFOUnderflowInterrupt(void);
void QSPI_ClearFIFOFlowInterrupt(void);

#ifdef __cplusplus
}
#endif

#endif /*__FT32F4XX_QSPI_H */

/**
  * @}
  */

/**
  * @}
  */


