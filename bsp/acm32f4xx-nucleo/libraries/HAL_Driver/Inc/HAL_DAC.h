/*
  ******************************************************************************
  * @file    HAL_Can.h
  * @version V1.0.0
  * @date    2020
  * @brief   Header file of CAN HAL module.
  ******************************************************************************
*/
#ifndef __HAL_DAC_H__
#define __HAL_DAC_H__

#include "ACM32Fxx_HAL.h"

/**
  * @}
  */
	
/******************************************************************************/
/*                    Peripheral Registers Bits Definition                    */
/******************************************************************************/
/******************************************************************************/
/*                                    (DAC)                                   */
/******************************************************************************/

/****************  Bit definition for DAC CR register  ***********************/
#define DAC_CR_EN1_Pos              (0U)
#define DAC_CR_EN1_Msk              (0x1UL << DAC_CR_EN1_Pos)                  /*!< 0x00000001 */
#define DAC_CR_EN1                  DAC_CR_EN1_Msk                             /*!<DAC channel1 enable */

#define DAC_CR_TEN1_Pos             (2U)
#define DAC_CR_TEN1_Msk             (0x1UL << DAC_CR_TEN1_Pos)                 /*!< 0x00000002 */
#define DAC_CR_TEN1                 DAC_CR_TEN1_Msk                            /*!<DAC channel1 Trigger enable */

#define DAC_CR_TSEL1_Pos            (3U)
#define DAC_CR_TSEL1_Msk            (0x7UL << DAC_CR_TSEL1_Pos)                /*!< 0x0000003C */
#define DAC_CR_TSEL1                DAC_CR_TSEL1_Msk                           /*!<TSEL1[3:0] (DAC channel1 Trigger selection) */
#define DAC_CR_TSEL1_0              (0x1UL << DAC_CR_TSEL1_Pos)                /*!< 0x00000004 */
#define DAC_CR_TSEL1_1              (0x2UL << DAC_CR_TSEL1_Pos)                /*!< 0x00000008 */
#define DAC_CR_TSEL1_2              (0x4UL << DAC_CR_TSEL1_Pos)                /*!< 0x00000010 */

#define DAC_CR_WAVE1_Pos            (6U)
#define DAC_CR_WAVE1_Msk            (0x3UL << DAC_CR_WAVE1_Pos)                /*!< 0x000000C0 */
#define DAC_CR_WAVE1                DAC_CR_WAVE1_Msk                           /*!<WAVE1[1:0] (DAC channel1 noise/triangle wave generation enable) */
#define DAC_CR_WAVE1_0              (0x1UL << DAC_CR_WAVE1_Pos)                /*!< 0x00000040 */
#define DAC_CR_WAVE1_1              (0x2UL << DAC_CR_WAVE1_Pos)                /*!< 0x00000080 */

#define DAC_CR_MAMP1_Pos            (8U)
#define DAC_CR_MAMP1_Msk            (0xFUL << DAC_CR_MAMP1_Pos)                /*!< 0x00000F00 */
#define DAC_CR_MAMP1                DAC_CR_MAMP1_Msk                           /*!<MAMP1[3:0] (DAC channel1 Mask/Amplitude selector) */
#define DAC_CR_MAMP1_0              (0x1UL << DAC_CR_MAMP1_Pos)                /*!< 0x00000100 */
#define DAC_CR_MAMP1_1              (0x2UL << DAC_CR_MAMP1_Pos)                /*!< 0x00000200 */
#define DAC_CR_MAMP1_2              (0x4UL << DAC_CR_MAMP1_Pos)                /*!< 0x00000400 */
#define DAC_CR_MAMP1_3              (0x8UL << DAC_CR_MAMP1_Pos)                /*!< 0x00000800 */

#define DAC_CR_DMAEN1_Pos           (12U)
#define DAC_CR_DMAEN1_Msk           (0x1UL << DAC_CR_DMAEN1_Pos)               /*!< 0x00001000 */
#define DAC_CR_DMAEN1               DAC_CR_DMAEN1_Msk                          /*!<DAC channel1 DMA enable */

#define DAC_CR_DMAUDRIE1_Pos        (13U)
#define DAC_CR_DMAUDRIE1_Msk        (0x1UL << DAC_CR_DMAUDRIE1_Pos)            /*!< 0x00002000 */
#define DAC_CR_DMAUDRIE1            DAC_CR_DMAUDRIE1_Msk                       /*!<DAC channel 1 DMA underrun interrupt enable  >*/

#define DAC_CR_CEN1_Pos             (14U)
#define DAC_CR_CEN1_Msk             (0x1UL << DAC_CR_CEN1_Pos)                 /*!< 0x00004000 */
#define DAC_CR_CEN1                 DAC_CR_CEN1_Msk                            /*!<DAC channel 1 calibration enable >*/

#define DAC_CR_EN2_Pos              (16U)
#define DAC_CR_EN2_Msk              (0x1UL << DAC_CR_EN2_Pos)                  /*!< 0x00010000 */
#define DAC_CR_EN2                  DAC_CR_EN2_Msk                             /*!<DAC channel2 enable */

#define DAC_CR_TEN2_Pos             (18U)
#define DAC_CR_TEN2_Msk             (0x1UL << DAC_CR_TEN2_Pos)                 /*!< 0x00020000 */
#define DAC_CR_TEN2                 DAC_CR_TEN2_Msk                            /*!<DAC channel2 Trigger enable */

#define DAC_CR_TSEL2_Pos            (19U)
#define DAC_CR_TSEL2_Msk            (0x7UL << DAC_CR_TSEL2_Pos)                /*!< 0x003C0000 */
#define DAC_CR_TSEL2                DAC_CR_TSEL2_Msk                           /*!<TSEL2[2:0] (DAC channel2 Trigger selection) */
#define DAC_CR_TSEL2_0              (0x1UL << DAC_CR_TSEL2_Pos)                /*!< 0x00040000 */
#define DAC_CR_TSEL2_1              (0x2UL << DAC_CR_TSEL2_Pos)                /*!< 0x00080000 */
#define DAC_CR_TSEL2_2              (0x4UL << DAC_CR_TSEL2_Pos)                /*!< 0x00100000 */

#define DAC_CR_WAVE2_Pos            (22U)
#define DAC_CR_WAVE2_Msk            (0x3UL << DAC_CR_WAVE2_Pos)                /*!< 0x00C00000 */
#define DAC_CR_WAVE2                DAC_CR_WAVE2_Msk                           /*!<WAVE2[1:0] (DAC channel2 noise/triangle wave generation enable) */
#define DAC_CR_WAVE2_0              (0x1UL << DAC_CR_WAVE2_Pos)                /*!< 0x00400000 */
#define DAC_CR_WAVE2_1              (0x2UL << DAC_CR_WAVE2_Pos)                /*!< 0x00800000 */

#define DAC_CR_MAMP2_Pos            (24U)
#define DAC_CR_MAMP2_Msk            (0xFUL << DAC_CR_MAMP2_Pos)                /*!< 0x0F000000 */
#define DAC_CR_MAMP2                DAC_CR_MAMP2_Msk                           /*!<MAMP2[3:0] (DAC channel2 Mask/Amplitude selector) */
#define DAC_CR_MAMP2_0              (0x1UL << DAC_CR_MAMP2_Pos)                /*!< 0x01000000 */
#define DAC_CR_MAMP2_1              (0x2UL << DAC_CR_MAMP2_Pos)                /*!< 0x02000000 */
#define DAC_CR_MAMP2_2              (0x4UL << DAC_CR_MAMP2_Pos)                /*!< 0x04000000 */
#define DAC_CR_MAMP2_3              (0x8UL << DAC_CR_MAMP2_Pos)                /*!< 0x08000000 */

#define DAC_CR_DMAEN2_Pos           (28U)
#define DAC_CR_DMAEN2_Msk           (0x1UL << DAC_CR_DMAEN2_Pos)               /*!< 0x10000000 */
#define DAC_CR_DMAEN2               DAC_CR_DMAEN2_Msk                          /*!<DAC channel2 DMA enabled */

#define DAC_CR_DMAUDRIE2_Pos        (29U)
#define DAC_CR_DMAUDRIE2_Msk        (0x1UL << DAC_CR_DMAUDRIE2_Pos)            /*!< 0x20000000 */
#define DAC_CR_DMAUDRIE2            DAC_CR_DMAUDRIE2_Msk                       /*!<DAC channel2 DMA underrun interrupt enable  >*/

#define DAC_CR_CEN2_Pos             (30U)
#define DAC_CR_CEN2_Msk             (0x1UL << DAC_CR_CEN2_Pos)                 /*!< 0x40000000 */
#define DAC_CR_CEN2                 DAC_CR_CEN2_Msk                            /*!<DAC channel2 calibration enable >*/

/****************  Bit definition for DAC SWTRIGR register  ***********************/
#define DAC_SWTRIGR_SWTRIG1_Pos     (0U)
#define DAC_SWTRIGR_SWTRIG1_Msk     (0x1UL << DAC_SWTRIGR_SWTRIG1_Pos)         /*!< 0x00000001 */
#define DAC_SWTRIGR_SWTRIG1         DAC_SWTRIGR_SWTRIG1_Msk                    /*!<DAC channel1 software trigger */
#define DAC_SWTRIGR_SWTRIG2_Pos     (1U)
#define DAC_SWTRIGR_SWTRIG2_Msk     (0x1UL << DAC_SWTRIGR_SWTRIG2_Pos)         /*!< 0x00000002 */
#define DAC_SWTRIGR_SWTRIG2         DAC_SWTRIGR_SWTRIG2_Msk                    /*!<DAC channel2 software trigger */

/*****************  Bit definition for DAC_DHR12R1 register  ******************/
#define DAC_DHR12R1_DACC1DHR_Pos    (0U)
#define DAC_DHR12R1_DACC1DHR_Msk    (0xFFFUL << DAC_DHR12R1_DACC1DHR_Pos)      /*!< 0x00000FFF */
#define DAC_DHR12R1_DACC1DHR        DAC_DHR12R1_DACC1DHR_Msk                   /*!<DAC channel1 12-bit Right aligned data */

/*****************  Bit definition for DAC_DHR12L1 register  ******************/
#define DAC_DHR12L1_DACC1DHR_Pos    (4U)
#define DAC_DHR12L1_DACC1DHR_Msk    (0xFFFUL << DAC_DHR12L1_DACC1DHR_Pos)      /*!< 0x0000FFF0 */
#define DAC_DHR12L1_DACC1DHR        DAC_DHR12L1_DACC1DHR_Msk                   /*!<DAC channel1 12-bit Left aligned data */

/******************  Bit definition for DAC_DHR8R1 register  ******************/
#define DAC_DHR8R1_DACC1DHR_Pos     (0U)
#define DAC_DHR8R1_DACC1DHR_Msk     (0xFFUL << DAC_DHR8R1_DACC1DHR_Pos)        /*!< 0x000000FF */
#define DAC_DHR8R1_DACC1DHR         DAC_DHR8R1_DACC1DHR_Msk                    /*!<DAC channel1 8-bit Right aligned data */

/*****************  Bit definition for DAC_DHR12R2 register  ******************/
#define DAC_DHR12R2_DACC2DHR_Pos    (0U)
#define DAC_DHR12R2_DACC2DHR_Msk    (0xFFFUL << DAC_DHR12R2_DACC2DHR_Pos)      /*!< 0x00000FFF */
#define DAC_DHR12R2_DACC2DHR        DAC_DHR12R2_DACC2DHR_Msk                   /*!<DAC channel2 12-bit Right aligned data */

/*****************  Bit definition for DAC_DHR12L2 register  ******************/
#define DAC_DHR12L2_DACC2DHR_Pos    (4U)
#define DAC_DHR12L2_DACC2DHR_Msk    (0xFFFUL << DAC_DHR12L2_DACC2DHR_Pos)      /*!< 0x0000FFF0 */
#define DAC_DHR12L2_DACC2DHR        DAC_DHR12L2_DACC2DHR_Msk                   /*!<DAC channel2 12-bit Left aligned data */

/******************  Bit definition for DAC_DHR8R2 register  ******************/
#define DAC_DHR8R2_DACC2DHR_Pos     (0U)
#define DAC_DHR8R2_DACC2DHR_Msk     (0xFFUL << DAC_DHR8R2_DACC2DHR_Pos)        /*!< 0x000000FF */
#define DAC_DHR8R2_DACC2DHR         DAC_DHR8R2_DACC2DHR_Msk                    /*!<DAC channel2 8-bit Right aligned data */

/*****************  Bit definition for DAC_DHR12RD register  ******************/
#define DAC_DHR12RD_DACC1DHR_Pos    (0U)
#define DAC_DHR12RD_DACC1DHR_Msk    (0xFFFUL << DAC_DHR12RD_DACC1DHR_Pos)      /*!< 0x00000FFF */
#define DAC_DHR12RD_DACC1DHR        DAC_DHR12RD_DACC1DHR_Msk                   /*!<DAC channel1 12-bit Right aligned data */
#define DAC_DHR12RD_DACC2DHR_Pos    (16U)
#define DAC_DHR12RD_DACC2DHR_Msk    (0xFFFUL << DAC_DHR12RD_DACC2DHR_Pos)      /*!< 0x0FFF0000 */
#define DAC_DHR12RD_DACC2DHR        DAC_DHR12RD_DACC2DHR_Msk                   /*!<DAC channel2 12-bit Right aligned data */

/*****************  Bit definition for DAC_DHR12LD register  ******************/
#define DAC_DHR12LD_DACC1DHR_Pos    (4U)
#define DAC_DHR12LD_DACC1DHR_Msk    (0xFFFUL << DAC_DHR12LD_DACC1DHR_Pos)      /*!< 0x0000FFF0 */
#define DAC_DHR12LD_DACC1DHR        DAC_DHR12LD_DACC1DHR_Msk                   /*!<DAC channel1 12-bit Left aligned data */
#define DAC_DHR12LD_DACC2DHR_Pos    (20U)
#define DAC_DHR12LD_DACC2DHR_Msk    (0xFFFUL << DAC_DHR12LD_DACC2DHR_Pos)      /*!< 0xFFF00000 */
#define DAC_DHR12LD_DACC2DHR        DAC_DHR12LD_DACC2DHR_Msk                   /*!<DAC channel2 12-bit Left aligned data */

/******************  Bit definition for DAC_DHR8RD register  ******************/
#define DAC_DHR8RD_DACC1DHR_Pos     (0U)
#define DAC_DHR8RD_DACC1DHR_Msk     (0xFFUL << DAC_DHR8RD_DACC1DHR_Pos)        /*!< 0x000000FF */
#define DAC_DHR8RD_DACC1DHR         DAC_DHR8RD_DACC1DHR_Msk                    /*!<DAC channel1 8-bit Right aligned data */
#define DAC_DHR8RD_DACC2DHR_Pos     (8U)
#define DAC_DHR8RD_DACC2DHR_Msk     (0xFFUL << DAC_DHR8RD_DACC2DHR_Pos)        /*!< 0x0000FF00 */
#define DAC_DHR8RD_DACC2DHR         DAC_DHR8RD_DACC2DHR_Msk                    /*!<DAC channel2 8-bit Right aligned data */

/*******************  Bit definition for DAC_DOR1 register  *******************/
#define DAC_DOR1_DACC1DOR_Pos       (0U)
#define DAC_DOR1_DACC1DOR_Msk       (0xFFFUL << DAC_DOR1_DACC1DOR_Pos)         /*!< 0x00000FFF */
#define DAC_DOR1_DACC1DOR           DAC_DOR1_DACC1DOR_Msk                      /*!<DAC channel1 data output */

/*******************  Bit definition for DAC_DOR2 register  *******************/
#define DAC_DOR2_DACC2DOR_Pos       (0U)
#define DAC_DOR2_DACC2DOR_Msk       (0xFFFUL << DAC_DOR2_DACC2DOR_Pos)         /*!< 0x00000FFF */
#define DAC_DOR2_DACC2DOR           DAC_DOR2_DACC2DOR_Msk                      /*!<DAC channel2 data output */

/********************  Bit definition for DAC_SR register  ********************/
#define DAC_SR_SAMOV1_Pos          (8U)
#define DAC_SR_SAMOV1_Msk          (0x1UL << DAC_SR_SAMOV1_Pos)              /*!< 0x00002000 */
#define DAC_SR_SAMOV1               DAC_SR_SAMOV1_Msk                         /*!<DAC channel1 DMA SAMOV1 flag */

#define DAC_SR_DMAUDR1_Pos          (13U)
#define DAC_SR_DMAUDR1_Msk          (0x1UL << DAC_SR_DMAUDR1_Pos)              /*!< 0x00002000 */
#define DAC_SR_DMAUDR1              DAC_SR_DMAUDR1_Msk                         /*!<DAC channel1 DMA underrun flag */

#define DAC_SR_CAL_FLAG1_Pos        (14U)
#define DAC_SR_CAL_FLAG1_Msk        (0x1UL << DAC_SR_CAL_FLAG1_Pos)            /*!< 0x00004000 */
#define DAC_SR_CAL_FLAG1            DAC_SR_CAL_FLAG1_Msk                       /*!<DAC channel1 calibration offset status */

#define DAC_SR_SAMOV2_Pos          (24U)
#define DAC_SR_SAMOV2_Msk          (0x1UL << DAC_SR_SAMOV2_Pos)              /*!< 0x00002000 */
#define DAC_SR_SAMOV2               DAC_SR_SAMOV2_Msk                         /*!<DAC channel1 DMA SAMOV1 flag */

#define DAC_SR_DMAUDR2_Pos          (29U)
#define DAC_SR_DMAUDR2_Msk          (0x1UL << DAC_SR_DMAUDR2_Pos)              /*!< 0x20000000 */
#define DAC_SR_DMAUDR2              DAC_SR_DMAUDR2_Msk                         /*!<DAC channel2 DMA underrun flag */
#define DAC_SR_CAL_FLAG2_Pos        (30U)
#define DAC_SR_CAL_FLAG2_Msk        (0x1UL << DAC_SR_CAL_FLAG2_Pos)            /*!< 0x40000000 */
#define DAC_SR_CAL_FLAG2            DAC_SR_CAL_FLAG2_Msk                       /*!<DAC channel2 calibration offset status */

/****************  Bit definition for DAC CCR register  ***********************/
#define DAC_CCR_OTRIM1_Pos          (0U)
#define DAC_CCR_OTRIM1_Msk          (0x1FUL << DAC_CCR_OTRIM1_Pos)             /*!< 0x0000001F */
#define DAC_CCR_OTRIM1              DAC_CCR_OTRIM1_Msk                         /*!<DAC channel1 offset trimming value */
#define DAC_CCR_OTRIM2_Pos          (16U)
#define DAC_CCR_OTRIM2_Msk          (0x1FUL << DAC_CCR_OTRIM2_Pos)             /*!< 0x001F0000 */
#define DAC_CCR_OTRIM2              DAC_CCR_OTRIM2_Msk                         /*!<DAC channel2 offset trimming value */

/*******************  Bit definition for DAC_MCR register  *******************/
#define DAC_MCR_MODE1_Pos           (0U)
#define DAC_MCR_MODE1_Msk           (0x7UL << DAC_MCR_MODE1_Pos)               /*!< 0x00000007 */
#define DAC_MCR_MODE1               DAC_MCR_MODE1_Msk                          /*!<MODE1[2:0] (DAC channel1 mode) */
#define DAC_MCR_MODE1_0             (0x1UL << DAC_MCR_MODE1_Pos)               /*!< 0x00000001 */
#define DAC_MCR_MODE1_1             (0x2UL << DAC_MCR_MODE1_Pos)               /*!< 0x00000002 */
#define DAC_MCR_MODE1_2             (0x4UL << DAC_MCR_MODE1_Pos)               /*!< 0x00000004 */

#define DAC_MCR_MODE2_Pos           (16U)
#define DAC_MCR_MODE2_Msk           (0x7UL << DAC_MCR_MODE2_Pos)               /*!< 0x00070000 */
#define DAC_MCR_MODE2               DAC_MCR_MODE2_Msk                          /*!<MODE2[2:0] (DAC channel2 mode) */
#define DAC_MCR_MODE2_0             (0x1UL << DAC_MCR_MODE2_Pos)               /*!< 0x00010000 */
#define DAC_MCR_MODE2_1             (0x2UL << DAC_MCR_MODE2_Pos)               /*!< 0x00020000 */
#define DAC_MCR_MODE2_2             (0x4UL << DAC_MCR_MODE2_Pos)               /*!< 0x00040000 */


/******************  Bit definition for DAC_SHSR1 register  ******************/
#define DAC_SHSR1_TSAMPLE1_Pos      (0U)
#define DAC_SHSR1_TSAMPLE1_Msk      (0x3FFUL << DAC_SHSR1_TSAMPLE1_Pos)        /*!< 0x000003FF */
#define DAC_SHSR1_TSAMPLE1          DAC_SHSR1_TSAMPLE1_Msk                     /*!<DAC channel1 sample time */

/******************  Bit definition for DAC_SHSR2 register  ******************/
#define DAC_SHSR2_TSAMPLE2_Pos      (0U)
#define DAC_SHSR2_TSAMPLE2_Msk      (0x3FFUL << DAC_SHSR2_TSAMPLE2_Pos)        /*!< 0x000003FF */
#define DAC_SHSR2_TSAMPLE2          DAC_SHSR2_TSAMPLE2_Msk                     /*!<DAC channel2 sample time */

/******************  Bit definition for DAC_SHHR register  ******************/
#define DAC_SHHR_THOLD1_Pos         (0U)
#define DAC_SHHR_THOLD1_Msk         (0x3FFUL << DAC_SHHR_THOLD1_Pos)           /*!< 0x000003FF */
#define DAC_SHHR_THOLD1             DAC_SHHR_THOLD1_Msk                        /*!<DAC channel1 hold time */
#define DAC_SHHR_THOLD2_Pos         (16U)
#define DAC_SHHR_THOLD2_Msk         (0x3FFUL << DAC_SHHR_THOLD2_Pos)           /*!< 0x03FF0000 */
#define DAC_SHHR_THOLD2             DAC_SHHR_THOLD2_Msk                        /*!<DAC channel2 hold time */

/******************  Bit definition for DAC_SHRR register  ******************/
#define DAC_SHRR_TREFRESH1_Pos      (0U)
#define DAC_SHRR_TREFRESH1_Msk      (0xFFUL << DAC_SHRR_TREFRESH1_Pos)         /*!< 0x000000FF */
#define DAC_SHRR_TREFRESH1          DAC_SHRR_TREFRESH1_Msk                     /*!<DAC channel1 refresh time */
#define DAC_SHRR_TREFRESH2_Pos      (16U)
#define DAC_SHRR_TREFRESH2_Msk      (0xFFUL << DAC_SHRR_TREFRESH2_Pos)         /*!< 0x00FF0000 */
#define DAC_SHRR_TREFRESH2          DAC_SHRR_TREFRESH2_Msk                     /*!<DAC channel2 refresh time */
/**
  * @brief   DAC Configuration sample and hold Channel structure definition
  */
typedef struct
{
  uint32_t DAC_SampleTime ;          /*!< Specifies the Sample time for the selected channel.
                                          This parameter applies when DAC_SampleAndHold is DAC_SAMPLEANDHOLD_ENABLE.
                                          This parameter must be a number between Min_Data = 0 and Max_Data = 1023 */

  uint32_t DAC_HoldTime ;            /*!< Specifies the hold time for the selected channel
                                          This parameter applies when DAC_SampleAndHold is DAC_SAMPLEANDHOLD_ENABLE.
                                          This parameter must be a number between Min_Data = 0 and Max_Data = 1023 */

  uint32_t DAC_RefreshTime ;         /*!< Specifies the refresh time for the selected channel
                                          This parameter applies when DAC_SampleAndHold is DAC_SAMPLEANDHOLD_ENABLE.
                                          This parameter must be a number between Min_Data = 0 and Max_Data = 255 */
}
DAC_SampleAndHoldConfTypeDef;

typedef struct
{
  uint32_t DAC_Calibration ;          /*!< Specifies the Sample time for the selected channel.
                                          This parameter can be a value of @ref DAC_Calibration */

  uint32_t DAC_Calibration_TRIM ;            /*!< Specifies the hold time for the selected channel
                                          This parameter applies when DAC_SampleAndHold is DAC_SAMPLEANDHOLD_ENABLE.
                                          This parameter must be a number between Min_Data = 0 and Max_Data = 1023 */
}
DAC_CalibrationConfTypeDef;

/**
  * @brief   DAC Configuration regular Channel structure definition
  */
typedef struct
{
  uint32_t DAC_SampleAndHold;            /*!< Specifies whether the DAC mode.
                                              This parameter can be a value of @ref DAC_SampleAndHold */

  uint32_t DAC_Trigger;                  /*!< Specifies the external trigger for the selected DAC channel.
                                              This parameter can be a value of @ref DAC_trigger_selection */

  uint32_t DAC_OutputBuffer;             /*!< Specifies whether the DAC channel output buffer is enabled or disabled.
                                               This parameter can be a value of @ref DAC_output_buffer */
  

  uint32_t DAC_ConnectOnChipPeripheral ; /*!< Specifies whether the DAC output is connected or not to on chip peripheral .
                                              This parameter can be a value of @ref DAC_ConnectOnChipPeripheral */

  uint32_t DAC_UserTrimming;             /*!< Specifies the trimming mode
                                              This parameter must be a value of @ref DAC_UserTrimming
                                              DAC_UserTrimming is either factory or user trimming */

  uint32_t DAC_TrimmingValue;             /*!< Specifies the offset trimming value
                                               i.e. when DAC_SampleAndHold is DAC_TRIMMING_USER.
                                               This parameter must be a number between Min_Data = 1 and Max_Data = 31 */

  DAC_SampleAndHoldConfTypeDef  DAC_SampleAndHoldConfig;  /*!< Sample and Hold settings */

} DAC_ChannelConfTypeDef;

/**
  * @brief  CAN handle Structure definition
  */
typedef struct 
{
  DAC_TypeDef                 *Instance;     /*!< Register base address             */
    
  DMA_HandleTypeDef           *DMA_Handle1;  /*!< Pointer DMA handler for channel 1 */

  DMA_HandleTypeDef           *DMA_Handle2;  /*!< Pointer DMA handler for channel 2 */
    

} DAC_HandleTypeDef;


#define IS_DAC_ALL_PERIPH(PERIPH) (((PERIPH) == DAC))



/** @defgroup DAC_SampleAndHold DAC power mode
  * @{
  */
#define IS_DAC_SAMPLETIME(TIME)                 ((TIME) <= 0x000003FFU)
#define IS_DAC_HOLDTIME(TIME)                   ((TIME) <= 0x000003FFU)
#define IS_DAC_REFRESHTIME(TIME)                 ((TIME) <= 0x000000FFU)


/** @defgroup DAC_CHANNEL 
  * @{
  */

#define DAC_CHANNEL_1                        0x00000000U
#define DAC_CHANNEL_2                        0x00000010U
#define DAC_CHANNEL_Dual                     0x00000020U
#define IS_DAC_CHANNEL(CHANNEL)             (((CHANNEL) == DAC_CHANNEL_1) || \
                                            ((CHANNEL) == DAC_CHANNEL_2) || \
                                            ((CHANNEL) == DAC_CHANNEL_Dual))
/**
  * @}
  */

  /** @defgroup DAC_trigger 
  * @{
  */                                             
#define DAC_TRIGGER_T6_TRGO          (0x00000000U| DAC_CR_TEN1)      
#define DAC_TRIGGER_T3_TRGO         ( DAC_CR_TSEL1_0| DAC_CR_TEN1)  
#define DAC_TRIGGER_T7_TRGO         ( DAC_CR_TSEL1_1| DAC_CR_TEN1 )  
#define DAC_TRIGGER_T15_TRGO        ( DAC_CR_TSEL1_1 | DAC_CR_TSEL1_0| DAC_CR_TEN1) 
#define DAC_TRIGGER_T2_TRGO         ( DAC_CR_TSEL1_2 | DAC_CR_TEN1)   
#define DAC_TRIGGER_T1_TRGO         ( DAC_CR_TSEL1_2  | DAC_CR_TSEL1_0| DAC_CR_TEN1)   
#define DAC_TRIGGER_EXT_IT9         ( DAC_CR_TSEL1_2 | DAC_CR_TSEL1_1| DAC_CR_TEN1 )   
#define DAC_TRIGGER_SOFTWARE        ( DAC_CR_TSEL1_2 | DAC_CR_TSEL1_1 | DAC_CR_TSEL1_0| DAC_CR_TEN1)   
#define IS_DAC_TRIGGER(TRIGGER)     (((TRIGGER) == DAC_TRIGGER_T6_TRGO) || \
                                    ((TRIGGER) == DAC_TRIGGER_T3_TRGO) || \
                                    ((TRIGGER) == DAC_TRIGGER_T7_TRGO) || \
                                    ((TRIGGER) == DAC_TRIGGER_T15_TRGO) || \
                                    ((TRIGGER) == DAC_TRIGGER_T2_TRGO) || \
                                     ((TRIGGER) == DAC_TRIGGER_T1_TRGO) || \
                                     ((TRIGGER) == DAC_TRIGGER_EXT_IT9) || \
                                     ((TRIGGER) == DAC_TRIGGER_SOFTWARE))
/**
  * @}
  */
  
/** @defgroup DAC_wave_generation 
  * @{
  */

#define DAC_WaveGeneration_None             0x00000000U
#define DAC_WaveGeneration_Noise            0x00000001U
#define DAC_WaveGeneration_Triangle         0x00000002U
#define IS_DAC_GENERATE_WAVE(WAVE)      (((WAVE) == DAC_WaveGeneration_None) || \
                                        ((WAVE) == DAC_WaveGeneration_Noise) || \
                                        ((WAVE) == DAC_WaveGeneration_Triangle))
/**
  * @}
  */
/** @defgroup DAC_lfsrunmask_triangleamplitude
  * @{
  */
#define DAC_LFSRUNMASK_BIT0                0x00000000U                                                         /*!< Unmask DAC channel LFSR bit0 for noise wave generation */
#define DAC_LFSRUNMASK_BITS1_0             (                                                   DAC_CR_MAMP1_0) /*!< Unmask DAC channel LFSR bit[1:0] for noise wave generation */
#define DAC_LFSRUNMASK_BITS2_0             (                                  DAC_CR_MAMP1_1                 ) /*!< Unmask DAC channel LFSR bit[2:0] for noise wave generation */
#define DAC_LFSRUNMASK_BITS3_0             (                                  DAC_CR_MAMP1_1 | DAC_CR_MAMP1_0) /*!< Unmask DAC channel LFSR bit[3:0] for noise wave generation */
#define DAC_LFSRUNMASK_BITS4_0             (                 DAC_CR_MAMP1_2                                  ) /*!< Unmask DAC channel LFSR bit[4:0] for noise wave generation */
#define DAC_LFSRUNMASK_BITS5_0             (                 DAC_CR_MAMP1_2                  | DAC_CR_MAMP1_0) /*!< Unmask DAC channel LFSR bit[5:0] for noise wave generation */
#define DAC_LFSRUNMASK_BITS6_0             (                 DAC_CR_MAMP1_2 | DAC_CR_MAMP1_1                 ) /*!< Unmask DAC channel LFSR bit[6:0] for noise wave generation */
#define DAC_LFSRUNMASK_BITS7_0             (                 DAC_CR_MAMP1_2 | DAC_CR_MAMP1_1 | DAC_CR_MAMP1_0) /*!< Unmask DAC channel LFSR bit[7:0] for noise wave generation */
#define DAC_LFSRUNMASK_BITS8_0             (DAC_CR_MAMP1_3                                                   ) /*!< Unmask DAC channel LFSR bit[8:0] for noise wave generation */
#define DAC_LFSRUNMASK_BITS9_0             (DAC_CR_MAMP1_3                                   | DAC_CR_MAMP1_0) /*!< Unmask DAC channel LFSR bit[9:0] for noise wave generation */
#define DAC_LFSRUNMASK_BITS10_0            (DAC_CR_MAMP1_3                  | DAC_CR_MAMP1_1                 ) /*!< Unmask DAC channel LFSR bit[10:0] for noise wave generation */
#define DAC_LFSRUNMASK_BITS11_0            (DAC_CR_MAMP1_3                  | DAC_CR_MAMP1_1 | DAC_CR_MAMP1_0) /*!< Unmask DAC channel LFSR bit[11:0] for noise wave generation */
#define DAC_TRIANGLEAMPLITUDE_1            0x00000000U                                                         /*!< Select max triangle amplitude of 1 */
#define DAC_TRIANGLEAMPLITUDE_3            (                                                   DAC_CR_MAMP1_0) /*!< Select max triangle amplitude of 3 */
#define DAC_TRIANGLEAMPLITUDE_7            (                                  DAC_CR_MAMP1_1                 ) /*!< Select max triangle amplitude of 7 */
#define DAC_TRIANGLEAMPLITUDE_15           (                                  DAC_CR_MAMP1_1 | DAC_CR_MAMP1_0) /*!< Select max triangle amplitude of 15 */
#define DAC_TRIANGLEAMPLITUDE_31           (                 DAC_CR_MAMP1_2                                  ) /*!< Select max triangle amplitude of 31 */
#define DAC_TRIANGLEAMPLITUDE_63           (                 DAC_CR_MAMP1_2                  | DAC_CR_MAMP1_0) /*!< Select max triangle amplitude of 63 */
#define DAC_TRIANGLEAMPLITUDE_127          (                 DAC_CR_MAMP1_2 | DAC_CR_MAMP1_1                 ) /*!< Select max triangle amplitude of 127 */
#define DAC_TRIANGLEAMPLITUDE_255          (                 DAC_CR_MAMP1_2 | DAC_CR_MAMP1_1 | DAC_CR_MAMP1_0) /*!< Select max triangle amplitude of 255 */
#define DAC_TRIANGLEAMPLITUDE_511          (DAC_CR_MAMP1_3                                                   ) /*!< Select max triangle amplitude of 511 */
#define DAC_TRIANGLEAMPLITUDE_1023         (DAC_CR_MAMP1_3                                   | DAC_CR_MAMP1_0) /*!< Select max triangle amplitude of 1023 */
#define DAC_TRIANGLEAMPLITUDE_2047         (DAC_CR_MAMP1_3                  | DAC_CR_MAMP1_1                 ) /*!< Select max triangle amplitude of 2047 */
#define DAC_TRIANGLEAMPLITUDE_4095         (DAC_CR_MAMP1_3                  | DAC_CR_MAMP1_1 | DAC_CR_MAMP1_0) /*!< Select max triangle amplitude of 4095 */

#define IS_DAC_LFSR_UNMASK_TRIANGLE_AMPLITUDE(VALUE)      (((VALUE) == DAC_LFSRUNMASK_BIT0) || \
                                                          ((VALUE) == DAC_LFSRUNMASK_BITS1_0) || \
                                                          ((VALUE) == DAC_LFSRUNMASK_BITS2_0) || \
                                                          ((VALUE) == DAC_LFSRUNMASK_BITS3_0) || \
                                                          ((VALUE) == DAC_LFSRUNMASK_BITS4_0) || \
                                                          ((VALUE) == DAC_LFSRUNMASK_BITS5_0) || \
                                                          ((VALUE) == DAC_LFSRUNMASK_BITS6_0) || \
                                                          ((VALUE) == DAC_LFSRUNMASK_BITS7_0) || \
                                                          ((VALUE) == DAC_LFSRUNMASK_BITS8_0) || \
                                                          ((VALUE) == DAC_LFSRUNMASK_BITS9_0) || \
                                                          ((VALUE) == DAC_LFSRUNMASK_BITS10_0) || \
                                                          ((VALUE) == DAC_LFSRUNMASK_BITS11_0) || \
                                                          ((VALUE) == DAC_TRIANGLEAMPLITUDE_1) || \
                                                          ((VALUE) == DAC_TRIANGLEAMPLITUDE_3) || \
                                                          ((VALUE) == DAC_TRIANGLEAMPLITUDE_7) || \
                                                          ((VALUE) == DAC_TRIANGLEAMPLITUDE_15) || \
                                                          ((VALUE) == DAC_TRIANGLEAMPLITUDE_31) || \
                                                          ((VALUE) == DAC_TRIANGLEAMPLITUDE_63) || \
                                                          ((VALUE) == DAC_TRIANGLEAMPLITUDE_127) || \
                                                          ((VALUE) == DAC_TRIANGLEAMPLITUDE_255) || \
                                                          ((VALUE) == DAC_TRIANGLEAMPLITUDE_511) || \
                                                          ((VALUE) == DAC_TRIANGLEAMPLITUDE_1023) || \
                                                          ((VALUE) == DAC_TRIANGLEAMPLITUDE_2047) || \
                                                          ((VALUE) == DAC_TRIANGLEAMPLITUDE_4095))
/**
  * @}
  */
  
  /** @defgroup DAC_MODE
  * @{
  */

#define DAC_Mode_Normal_BufferEnable_OutPAD                                   0x00000000U
#define DAC_Mode_Normal_BufferEnable_OutPAD_OutInternal                       0x00000001U
#define DAC_Mode_Normal_BufferDisable_OutPAD                                  0x00000002U
#define DAC_Mode_Normal_BufferDisable_OutPAD_OutInternal                      0x00000003U

#define DAC_Mode_SampleAndHold_BufferEnable_OutPAD                            0x00000004U
#define DAC_Mode_SampleAndHold_BufferEnable_OutPAD_OutInternal                0x00000005U
#define DAC_Mode_SampleAndHold_BufferDisable_OutPAD_OutInternal               0x00000006U
#define DAC_Mode_SampleAndHold_BufferDisable_OutInternal                      0x00000007U
#define IS_DAC_MODE(MODE)               (((MODE) == DAC_Mode_Normal_BufferEnable_OutPAD) || \
                                        ((MODE) == DAC_Mode_Normal_BufferEnable_OutPAD_OutInternal) || \
                                        ((MODE) == DAC_Mode_Normal_BufferDisable_OutPAD)|| \
                                        ((MODE) == DAC_Mode_Normal_BufferDisable_OutPAD_OutInternal)|| \
                                        ((MODE) == DAC_Mode_SampleAndHold_BufferEnable_OutPAD)|| \
                                        ((MODE) == DAC_Mode_SampleAndHold_BufferEnable_OutPAD_OutInternal)|| \
                                        ((MODE) == DAC_Mode_SampleAndHold_BufferDisable_OutPAD_OutInternal)|| \
                                        ((MODE) == DAC_Mode_SampleAndHold_BufferDisable_OutInternal))
/**
  * @}
  */
  
  /** @defgroup DAC_SampleAndHold DAC power mode
  * @{
  */
#define DAC_SAMPLEANDHOLD_DISABLE     0x00000000U
#define DAC_SAMPLEANDHOLD_ENABLE      (DAC_MCR_MODE1_2)
  #define IS_DAC_SAMPLEANDHOLD(MODE) (((MODE) == DAC_SAMPLEANDHOLD_DISABLE) || \
                                    ((MODE) == DAC_SAMPLEANDHOLD_ENABLE))
/**
  * @}
  */

                                    
  /** @defgroup DAC_UserTrimming DAC User Trimming
* @{
*/

#define DAC_TRIMMING_FACTORY        0x00000000U           /*!< Factory trimming */
#define DAC_TRIMMING_USER           0x00000001U           /*!< User trimming */
#define IS_DAC_TRIMMING(TRIMMING) (((TRIMMING) == DAC_TRIMMING_FACTORY) || \
                                     ((TRIMMING) == DAC_TRIMMING_USER))
#define IS_DAC_TRIMMINGVALUE(TRIMMINGVALUE) ((TRIMMINGVALUE) <= 0x1FU)
/**
  * @}
  */
  
  /** @defgroup DAC_Calibration 
  * @{
  */

#define DAC_Calibration_Disable                  0x00000000U
#define DAC_Calibration_Enable                   0x00000001U
#define IS_DAC_Calibration(Calibration)         (((Calibration) == DAC_Calibration_Disable) || \
                                                ((Calibration) == DAC_Calibration_Enable))
                                    
#define IS_DAC_Calibration_TRIM(TRIM)            ((TRIM) <= 0x1FU)                                  
/**
  * @}
  */
  /** @defgroup DAC_output_buffer DAC output buffer
  * @{
  */
#define DAC_OUTPUTBUFFER_ENABLE            0x00000000U
#define DAC_OUTPUTBUFFER_DISABLE           (DAC_MCR_MODE1_1)
 #define IS_DAC_OUTPUT_BUFFER_STATE(STATE) (((STATE) == DAC_OUTPUTBUFFER_ENABLE) || \
                                           ((STATE) == DAC_OUTPUTBUFFER_DISABLE))
/**
  * @}
  */
/** @defgroup DAC_ConnectOnChipPeripheral DAC ConnectOnChipPeripheral
  * @{
  */
#define DAC_CHIPCONNECT_DISABLE    0x00000000U
#define DAC_CHIPCONNECT_ENABLE     (DAC_MCR_MODE1_0)
#define IS_DAC_CHIP_CONNECTION(CONNECT) (((CONNECT) == DAC_CHIPCONNECT_DISABLE) || \
                                         ((CONNECT) == DAC_CHIPCONNECT_ENABLE))     
/**
  * @}
  */
                          
                                           
  /** @defgroup DAC_data_alignment DAC data alignment
  * @{
  */

#define DAC_DHR12R1_ALIGNMENT(__ALIGNMENT__)        (0x00000008U + (__ALIGNMENT__))
#define DAC_DHR12R2_ALIGNMENT(__ALIGNMENT__)        (0x00000014U + (__ALIGNMENT__))



#define DAC_DHR12RD_ALIGNMENT(__ALIGNMENT__)        (0x00000020U + (__ALIGNMENT__))

#define DAC_ALIGN_12B_R                    0x00000000U
#define DAC_ALIGN_12B_L                    0x00000004U
#define DAC_ALIGN_8B_R                     0x00000008U
#define IS_DAC_ALIGN(ALIGN)               (((ALIGN) == DAC_ALIGN_12B_R) || \
                                         ((ALIGN) == DAC_ALIGN_12B_L) || \
                                         ((ALIGN) == DAC_ALIGN_8B_R))
/**
  * @}
  */
  
  
  
  
/* Initialization/de-initialization functions *********************************/
void HAL_DAC_IRQHandler(DAC_HandleTypeDef *hdac);

void HAL_DAC_MspInit(DAC_HandleTypeDef *hdac);
void HAL_DAC_MspDeInit(DAC_HandleTypeDef* hdac);

HAL_StatusTypeDef HAL_DAC_Init(DAC_HandleTypeDef *hdac);  
HAL_StatusTypeDef HAL_DAC_DeInit(DAC_HandleTypeDef* hdac); 

HAL_StatusTypeDef HAL_DAC_ConfigChannel(DAC_HandleTypeDef* hdac, DAC_ChannelConfTypeDef* sConfig, uint32_t Channel);

/* I/O operation functions ****************************************************/ 
HAL_StatusTypeDef HAL_DAC_Start(DAC_HandleTypeDef *hdac, uint32_t Channel);
HAL_StatusTypeDef HAL_DAC_Stop(DAC_HandleTypeDef* hdac, uint32_t Channel);

HAL_StatusTypeDef HAL_DAC_Start_DMA(DAC_HandleTypeDef *hdac, uint32_t Channel, uint32_t *pData, uint32_t Length, uint32_t Alignment);
HAL_StatusTypeDef HAL_DAC_Stop_DMA(DAC_HandleTypeDef* hdac, uint32_t Channel);

/* Peripheral Control functions ***********************************************/
HAL_StatusTypeDef HAL_DAC_SetValue(DAC_HandleTypeDef *hdac, uint32_t Channel, uint32_t Alignment, uint32_t Data);
HAL_StatusTypeDef HAL_DACEx_DualSetValue(DAC_HandleTypeDef *hdac, uint32_t Alignment, uint32_t Data1, uint32_t Data2);

uint32_t HAL_DAC_GetValue(DAC_HandleTypeDef* hdac, uint32_t Channel);
uint32_t HAL_DACEx_DualGetValue(DAC_HandleTypeDef *hdac);

HAL_StatusTypeDef HAL_DACEx_TriangleWaveGenerate(DAC_HandleTypeDef *hdac, uint32_t Channel, uint32_t Amplitude);
HAL_StatusTypeDef HAL_DACEx_NoiseWaveGenerate(DAC_HandleTypeDef *hdac, uint32_t Channel, uint32_t Amplitude) ;
 
 
HAL_StatusTypeDef HAL_DACEx_SelfCalibrate(DAC_HandleTypeDef *hdac, DAC_ChannelConfTypeDef *sConfig, uint32_t Channel);
HAL_StatusTypeDef HAL_DACEx_SetUserTrimming(DAC_HandleTypeDef *hdac, DAC_ChannelConfTypeDef *sConfig, uint32_t Channel, uint32_t NewTrimmingValue);
uint32_t HAL_DACEx_GetTrimOffset(DAC_HandleTypeDef *hdac, uint32_t Channel);

 
#endif