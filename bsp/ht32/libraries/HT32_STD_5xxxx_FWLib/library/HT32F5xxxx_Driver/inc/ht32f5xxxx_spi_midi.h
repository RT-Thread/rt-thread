/*********************************************************************************************************//**
 * @file    ht32f5xxxx_spi_midi.h
 * @version $Rev:: 7075         $
 * @date    $Date:: 2023-07-31 #$
 * @brief   The header file of SPI library (MIDI Control).
 *************************************************************************************************************
 * @attention
 *
 * Firmware Disclaimer Information
 *
 * 1. The customer hereby acknowledges and agrees that the program technical documentation, including the
 *    code, which is supplied by Holtek Semiconductor Inc., (hereinafter referred to as "HOLTEK") is the
 *    proprietary and confidential intellectual property of HOLTEK, and is protected by copyright law and
 *    other intellectual property laws.
 *
 * 2. The customer hereby acknowledges and agrees that the program technical documentation, including the
 *    code, is confidential information belonging to HOLTEK, and must not be disclosed to any third parties
 *    other than HOLTEK and the customer.
 *
 * 3. The program technical documentation, including the code, is provided "as is" and for customer reference
 *    only. After delivery by HOLTEK, the customer shall use the program technical documentation, including
 *    the code, at their own risk. HOLTEK disclaims any expressed, implied or statutory warranties, including
 *    the warranties of merchantability, satisfactory quality and fitness for a particular purpose.
 *
 * <h2><center>Copyright (C) Holtek Semiconductor Inc. All rights reserved</center></h2>
 ************************************************************************************************************/
/* Define to prevent recursive inclusion -------------------------------------------------------------------*/
#ifndef __HT32F5XXXX_SPI_MIDI_H
#define __HT32F5XXXX_SPI_MIDI_H

#ifdef __cplusplus
 extern "C" {
#endif

/** @addtogroup HT32F5xxxx_Peripheral_Driver HT32F5xxxx Peripheral Driver
  * @{
  */

/** @addtogroup SPI
  * @{
  */


/* Exported typedef ----------------------------------------------------------------------------------------*/
/** @defgroup SPI_MIDI_Exported_Types QSPI MIDI exported types
  * @{
  */
typedef struct
{
  u32 MIDICTRL_MODE;
  u32 MIDICTRL_CommandLength;
  u32 MIDICTRL_AddressLength;
  u32 MIDICTRL_ModeLength;
  u32 MIDICTRL_DummyLength;
  u32 MIDICTRL_DataLength;
  u32 MIDICTRL_CommandValue;
  u32 MIDICTRL_ModeValue;
} MIDICTRL_InitTypeDef;
/**
  * @}
  */

/* Exported constants --------------------------------------------------------------------------------------*/
/** @defgroup SPI_Exported_Constants SPI exported constants
  * @{
  */
#define QDIOEN_POS                              (22)
#define SMDEL_POS                               (6)

#define DOR_MODE                                (0UL << QDIOEN_POS | 1UL << SMDEL_POS )
#define DIOR_MODE                               (1UL << QDIOEN_POS | 1UL << SMDEL_POS )
#define QOR_MODE                                (0UL << QDIOEN_POS | 2UL << SMDEL_POS )
#define QIOR_MODE                               (1UL << QDIOEN_POS | 2UL << SMDEL_POS )
#define QPI_MODE                                (3UL << SMDEL_POS )
#define SERIAL_MODE                             (0UL << SMDEL_POS )

/* QSPI Flash Command Field Length -------------------------------------------------------------------------*/
#define MIDICTRL_CMDLENGTH_0                    ((u32)0x00000000)
#define MIDICTRL_CMDLENGTH_1                    ((u32)0x01000000)
#define MIDICTRL_CMDLENGTH_2                    ((u32)0x02000000)
#define MIDICTRL_CMDLENGTH_3                    ((u32)0x03000000)
#define MIDICTRL_CMDLENGTH_4                    ((u32)0x04000000)
#define MIDICTRL_CMDLENGTH_5                    ((u32)0x05000000)
#define MIDICTRL_CMDLENGTH_6                    ((u32)0x06000000)
#define MIDICTRL_CMDLENGTH_7                    ((u32)0x07000000)
#define MIDICTRL_CMDLENGTH_8                    ((u32)0x08000000)

/* QSPI FlashAddress Field Length --------------------------------------------------------------------------*/
#define MIDICTRL_ADLENGTH_0                     ((u32)0x00000000)
#define MIDICTRL_ADLENGTH_1                     ((u32)0x00010000)
#define MIDICTRL_ADLENGTH_2                     ((u32)0x00020000)
#define MIDICTRL_ADLENGTH_3                     ((u32)0x00030000)
#define MIDICTRL_ADLENGTH_4                     ((u32)0x00040000)
#define MIDICTRL_ADLENGTH_5                     ((u32)0x00050000)
#define MIDICTRL_ADLENGTH_6                     ((u32)0x00060000)
#define MIDICTRL_ADLENGTH_7                     ((u32)0x00070000)
#define MIDICTRL_ADLENGTH_8                     ((u32)0x00080000)
#define MIDICTRL_ADLENGTH_9                     ((u32)0x00090000)
#define MIDICTRL_ADLENGTH_10                    ((u32)0x000A0000)
#define MIDICTRL_ADLENGTH_11                    ((u32)0x000B0000)
#define MIDICTRL_ADLENGTH_12                    ((u32)0x000C0000)
#define MIDICTRL_ADLENGTH_13                    ((u32)0x000D0000)
#define MIDICTRL_ADLENGTH_14                    ((u32)0x000E0000)
#define MIDICTRL_ADLENGTH_15                    ((u32)0x000F0000)
#define MIDICTRL_ADLENGTH_16                    ((u32)0x00100000)
#define MIDICTRL_ADLENGTH_17                    ((u32)0x00110000)
#define MIDICTRL_ADLENGTH_18                    ((u32)0x00120000)
#define MIDICTRL_ADLENGTH_19                    ((u32)0x00130000)
#define MIDICTRL_ADLENGTH_20                    ((u32)0x00140000)
#define MIDICTRL_ADLENGTH_21                    ((u32)0x00150000)
#define MIDICTRL_ADLENGTH_22                    ((u32)0x00160000)
#define MIDICTRL_ADLENGTH_23                    ((u32)0x00170000)
#define MIDICTRL_ADLENGTH_24                    ((u32)0x00180000)

/* QSPI Flash Command Field Length -------------------------------------------------------------------------*/
#define MIDICTRL_MODELENGTH_0                   ((u32)0x00000000)
#define MIDICTRL_MODELENGTH_1                   ((u32)0x00001000)
#define MIDICTRL_MODELENGTH_2                   ((u32)0x00002000)
#define MIDICTRL_MODELENGTH_3                   ((u32)0x00003000)
#define MIDICTRL_MODELENGTH_4                   ((u32)0x00004000)
#define MIDICTRL_MODELENGTH_5                   ((u32)0x00005000)
#define MIDICTRL_MODELENGTH_6                   ((u32)0x00006000)
#define MIDICTRL_MODELENGTH_7                   ((u32)0x00007000)
#define MIDICTRL_MODELENGTH_8                   ((u32)0x00008000)

/* QSPI Flash Dummy Field Length ---------------------------------------------------------------------------*/
#define MIDICTRL_DUMMYLENGTH_0                  ((u32)0x00000000)
#define MIDICTRL_DUMMYLENGTH_1                  ((u32)0x00000100)
#define MIDICTRL_DUMMYLENGTH_2                  ((u32)0x00000200)
#define MIDICTRL_DUMMYLENGTH_3                  ((u32)0x00000300)
#define MIDICTRL_DUMMYLENGTH_4                  ((u32)0x00000400)
#define MIDICTRL_DUMMYLENGTH_5                  ((u32)0x00000500)
#define MIDICTRL_DUMMYLENGTH_6                  ((u32)0x00000600)
#define MIDICTRL_DUMMYLENGTH_7                  ((u32)0x00000700)
#define MIDICTRL_DUMMYLENGTH_8                  ((u32)0x00000800)

/* QSPI Flash Data Field Length ----------------------------------------------------------------------------*/
#define MIDICTRL_DATALENGTH_0                   ((u32)0x00000000)
#define MIDICTRL_DATALENGTH_1                   ((u32)0x00000001)
#define MIDICTRL_DATALENGTH_2                   ((u32)0x00000002)
#define MIDICTRL_DATALENGTH_3                   ((u32)0x00000003)
#define MIDICTRL_DATALENGTH_4                   ((u32)0x00000004)
#define MIDICTRL_DATALENGTH_5                   ((u32)0x00000005)
#define MIDICTRL_DATALENGTH_6                   ((u32)0x00000006)
#define MIDICTRL_DATALENGTH_7                   ((u32)0x00000007)
#define MIDICTRL_DATALENGTH_8                   ((u32)0x00000008)
#define MIDICTRL_DATALENGTH_9                   ((u32)0x00000009)
#define MIDICTRL_DATALENGTH_10                  ((u32)0x0000000A)
#define MIDICTRL_DATALENGTH_11                  ((u32)0x0000000B)
#define MIDICTRL_DATALENGTH_12                  ((u32)0x0000000C)
#define MIDICTRL_DATALENGTH_13                  ((u32)0x0000000D)
#define MIDICTRL_DATALENGTH_14                  ((u32)0x0000000E)
#define MIDICTRL_DATALENGTH_15                  ((u32)0x0000000F)
#define MIDICTRL_DATALENGTH_16                  ((u32)0x00000010)
#define MIDICTRL_DATALENGTH_17                  ((u32)0x00000011)
#define MIDICTRL_DATALENGTH_18                  ((u32)0x00000012)
#define MIDICTRL_DATALENGTH_19                  ((u32)0x00000013)
#define MIDICTRL_DATALENGTH_20                  ((u32)0x00000014)
#define MIDICTRL_DATALENGTH_21                  ((u32)0x00000015)
#define MIDICTRL_DATALENGTH_22                  ((u32)0x00000016)
#define MIDICTRL_DATALENGTH_23                  ((u32)0x00000017)
#define MIDICTRL_DATALENGTH_24                  ((u32)0x00000018)
#define MIDICTRL_DATALENGTH_25                  ((u32)0x00000019)
#define MIDICTRL_DATALENGTH_26                  ((u32)0x0000001A)
#define MIDICTRL_DATALENGTH_27                  ((u32)0x0000001B)
#define MIDICTRL_DATALENGTH_28                  ((u32)0x0000001C)
#define MIDICTRL_DATALENGTH_29                  ((u32)0x0000001D)
#define MIDICTRL_DATALENGTH_30                  ((u32)0x0000001E)
#define MIDICTRL_DATALENGTH_31                  ((u32)0x0000001F)
#define MIDICTRL_DATALENGTH_32                  ((u32)0x00000020)

#define MIDICTRL_ON                             ((u32)0x00800000)
#define MIDICTRL_OFF                            ((u32)0xFF7FFFFF)

#define CMDVALUE_POS                            (8)
#define MDVALUE_POS                             (0)
/**
  * @}
  */

/* Exported functions --------------------------------------------------------------------------------------*/
/** @defgroup SPI_Exported_Functions SPI exported functions
  * @{
  */
void MIDICTRL_Cmd(HT_SPI_TypeDef* QSPIx ,ControlStatus NewState);
void MIDICTRL_Init(HT_SPI_TypeDef* QSPIx, MIDICTRL_InitTypeDef* MIDICTRL_InitStruct);
/**
  * @}
  */


/**
  * @}
  */

/**
  * @}
  */

#ifdef __cplusplus
}
#endif

#endif
