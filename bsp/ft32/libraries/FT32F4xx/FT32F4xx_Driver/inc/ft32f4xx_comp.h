/**
  ******************************************************************************
  * @file               ft32f4xx_comp.h
  * @author             FMD AE
  * @brief              This file contains all the functions prototypes for the comparator
  *                     firmware library.
  * @version            V1.0.0
  * @date                   2025-03-20
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __FT32F4XX_COMP_H
#define __FT32F4XX_COMP_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "ft32f4xx.h"
/* Exported types ------------------------------------------------------------*/
/** @defgroup COMP_Exported_Types COMP Exported Types
  * @{
  */

/**
  * @brief  COMP Init structure definition
  */
typedef struct
{

    uint32_t COMP_VipSel;         /*!< Select the positive input of the comparator.
                                    This parameter can be a value of @ref COMP_VipSel */

    uint32_t COMP_VinSel;        /*!< Select the negative input of the comparator.
                                    This parameter can be a value of @ref COMP_VinSel */

    uint32_t COMP_Hysteresis_Sel;     /*!< Set comparator COMP_hysteresis mode of the input minus.
                                    This parameter can be a value of @ref COMP_Hysteresis */

    uint32_t COMP_Blanking_Sel;       /*!< Set comparator blanking source.
                                    This parameter can be a value of @ref COMP_BlankingSrce */

    uint32_t COMP_Pol;                        /*!< Select the output polarity of the comparator.
                                          This parameter can be a value of @ref COMP_Pol */
} COMP_InitTypeDef;

/**
  * @brief  HAL COMP state machine: HAL COMP states definition
  */




/* Exported constants --------------------------------------------------------*/

/** @defgroup COMP_Exported_Constants
  * @{
  */

/** @defgroup COMP_Selection
  * @{
  */
#define COMP_Selection_COMP1                    ((uint32_t)0x00000001) /*!< COMP1 Selection */
#define COMP_Selection_COMP2                    ((uint32_t)0x00000002) /*!< COMP2 Selection */
#define COMP_Selection_COMP3                    ((uint32_t)0x00000003) /*!< COMP3 Selection */
#define COMP_Selection_COMP4                    ((uint32_t)0x00000004) /*!< COMP4 Selection */
#define COMP_Selection_COMP5                    ((uint32_t)0x00000005) /*!< COMP5 Selection */
#define COMP_Selection_COMP6                    ((uint32_t)0x00000006) /*!< COMP6 Selection */

#define IS_COMP_ALL_PERIPH(PERIPH) (((PERIPH) == COMP_Selection_COMP1) || \
                                    ((PERIPH) == COMP_Selection_COMP2) || \
                                    ((PERIPH) == COMP_Selection_COMP3) || \
                                    ((PERIPH) == COMP_Selection_COMP4) || \
                                    ((PERIPH) == COMP_Selection_COMP5) || \
                                    ((PERIPH) == COMP_Selection_COMP6))

/** @defgroup COMP_WIN_Selection
  * @{comp3 comp4 comp5 comp6
  */
#define COMP_WIN_Selection_COMP3                  ((uint32_t)0x00000003) /*!< COMP3 Selection */
#define COMP_WIN_Selection_COMP4                  ((uint32_t)0x00000004) /*!< COMP4 Selection */
#define COMP_WIN_Selection_COMP5                  ((uint32_t)0x00000005) /*!< COMP5 Selection */
#define COMP_WIN_Selection_COMP6                  ((uint32_t)0x00000006) /*!< COMP6 Selection */

#define IS_COMP_WIN_PERIPH(PERIPH) (((PERIPH) == COMP_WIN_Selection_COMP3) || \
                                    ((PERIPH) == COMP_WIN_Selection_COMP4) || \
                                    ((PERIPH) == COMP_WIN_Selection_COMP5) || \
                                    ((PERIPH) == COMP_WIN_Selection_COMP6))


/** @defgroup COMP_1_2_Selection
  * @{comp1 comp2
  */
#define COMP_1_2_Selection_COMP1                  ((uint32_t)0x00000001) /*!< COMP3 Selection */
#define COMP_1_2_Selection_COMP2                  ((uint32_t)0x00000002) /*!< COMP4 Selection */

#define IS_COMP_1_2_PERIPH(PERIPH) (((PERIPH) == COMP_1_2_Selection_COMP1) || \
                                    ((PERIPH) == COMP_1_2_Selection_COMP2))


/** @defgroup COMP_qualsel
  * @{ x= 1/2 (comp1 comp2)
  */
#define COMPx_QUALSEL_NONE                ((uint32_t)0x00000000) /*!< COMPx_QUALICIFATION */
#define COMPx_QUALSEL_1C                  ((uint32_t)0x00000200) /*!< COMPx_QUALICIFATION */
#define COMPx_QUALSEL_2C                  ((uint32_t)0x00000400) /*!< COMPx_QUALICIFATION */
#define COMPx_QUALSEL_3C                  ((uint32_t)0x00000600) /*!< COMPx_QUALICIFATION */
#define COMPx_QUALSEL_4C                  ((uint32_t)0x00000800) /*!< COMPx_QUALICIFATION */
#define COMPx_QUALSEL_5C                  ((uint32_t)0x00000a00) /*!< COMPx_QUALICIFATION */
#define COMPx_QUALSEL_6C                  ((uint32_t)0x00000c00) /*!< COMPx_QUALICIFATION */
#define COMPx_QUALSEL_7C                  ((uint32_t)0x00000e00) /*!< COMPx_QUALICIFATION */
#define COMPx_QUALSEL_8C                  ((uint32_t)0x00001000) /*!< COMPx_QUALICIFATION */
#define COMPx_QUALSEL_9C                  ((uint32_t)0x00001200) /*!< COMPx_QUALICIFATION */
#define COMPx_QUALSEL_10C                 ((uint32_t)0x00001400) /*!< COMPx_QUALICIFATION */
#define COMPx_QUALSEL_11C                 ((uint32_t)0x00001600) /*!< COMPx_QUALICIFATION */
#define COMPx_QUALSEL_12C                 ((uint32_t)0x00001800) /*!< COMPx_QUALICIFATION */
#define COMPx_QUALSEL_13C                 ((uint32_t)0x00001a00) /*!< COMPx_QUALICIFATION */
#define COMPx_QUALSEL_14C                 ((uint32_t)0x00001c00) /*!< COMPx_QUALICIFATION */
#define COMPx_QUALSEL_15C                 ((uint32_t)0x00001e00) /*!< COMPx_QUALICIFATION */
#define COMPx_QUALSEL_16C                 ((uint32_t)0x00002000) /*!< COMPx_QUALICIFATION */
#define COMPx_QUALSEL_17C                 ((uint32_t)0x00002200) /*!< COMPx_QUALICIFATION */
#define COMPx_QUALSEL_18C                 ((uint32_t)0x00002400) /*!< COMPx_QUALICIFATION */
#define COMPx_QUALSEL_19C                 ((uint32_t)0x00002600) /*!< COMPx_QUALICIFATION */
#define COMPx_QUALSEL_20C                 ((uint32_t)0x00002800) /*!< COMPx_QUALICIFATION */
#define COMPx_QUALSEL_21C                 ((uint32_t)0x00002a00) /*!< COMPx_QUALICIFATION */
#define COMPx_QUALSEL_22C                 ((uint32_t)0x00002c00) /*!< COMPx_QUALICIFATION */
#define COMPx_QUALSEL_23C                 ((uint32_t)0x00002e00) /*!< COMPx_QUALICIFATION */
#define COMPx_QUALSEL_24C                 ((uint32_t)0x00003000) /*!< COMPx_QUALICIFATION */
#define COMPx_QUALSEL_25C                 ((uint32_t)0x00003200) /*!< COMPx_QUALICIFATION */
#define COMPx_QUALSEL_26C                 ((uint32_t)0x00003400) /*!< COMPx_QUALICIFATION */
#define COMPx_QUALSEL_27C                 ((uint32_t)0x00003600) /*!< COMPx_QUALICIFATION */
#define COMPx_QUALSEL_28C                 ((uint32_t)0x00003800) /*!< COMPx_QUALICIFATION */
#define COMPx_QUALSEL_29C                 ((uint32_t)0x00003a00) /*!< COMPx_QUALICIFATION */
#define COMPx_QUALSEL_30C                 ((uint32_t)0x00003c00) /*!< COMPx_QUALICIFATION */
#define COMPx_QUALSEL_31C                 ((uint32_t)0x00003e00) /*!< COMPx_QUALICIFATION */

#define IS_COMP_QUALSER_PERIPH(QUALSEL) (((QUALSEL) == COMPx_QUALSEL_NONE) || \
                                         ((QUALSEL) == COMPx_QUALSEL_1C ) || \
                                         ((QUALSEL) == COMPx_QUALSEL_2C ) || \
                                         ((QUALSEL) == COMPx_QUALSEL_3C ) || \
                                         ((QUALSEL) == COMPx_QUALSEL_4C ) || \
                                         ((QUALSEL) == COMPx_QUALSEL_5C ) || \
                                         ((QUALSEL) == COMPx_QUALSEL_6C ) || \
                                         ((QUALSEL) == COMPx_QUALSEL_7C ) || \
                                         ((QUALSEL) == COMPx_QUALSEL_8C ) || \
                                         ((QUALSEL) == COMPx_QUALSEL_9C ) || \
                                         ((QUALSEL) == COMPx_QUALSEL_10C ) || \
                                         ((QUALSEL) == COMPx_QUALSEL_11C ) || \
                                         ((QUALSEL) == COMPx_QUALSEL_12C ) || \
                                         ((QUALSEL) == COMPx_QUALSEL_13C ) || \
                                         ((QUALSEL) == COMPx_QUALSEL_14C ) || \
                                         ((QUALSEL) == COMPx_QUALSEL_15C ) || \
                                         ((QUALSEL) == COMPx_QUALSEL_16C ) || \
                                         ((QUALSEL) == COMPx_QUALSEL_17C ) || \
                                         ((QUALSEL) == COMPx_QUALSEL_18C ) || \
                                         ((QUALSEL) == COMPx_QUALSEL_19C ) || \
                                         ((QUALSEL) == COMPx_QUALSEL_20C ) || \
                                         ((QUALSEL) == COMPx_QUALSEL_21C ) || \
                                         ((QUALSEL) == COMPx_QUALSEL_22C ) || \
                                         ((QUALSEL) == COMPx_QUALSEL_23C ) || \
                                         ((QUALSEL) == COMPx_QUALSEL_24C ) || \
                                         ((QUALSEL) == COMPx_QUALSEL_25C ) || \
                                         ((QUALSEL) == COMPx_QUALSEL_26C ) || \
                                         ((QUALSEL) == COMPx_QUALSEL_27C ) || \
                                         ((QUALSEL) == COMPx_QUALSEL_28C ) || \
                                         ((QUALSEL) == COMPx_QUALSEL_29C ) || \
                                         ((QUALSEL) == COMPx_QUALSEL_30C ) || \
                                         ((QUALSEL) == COMPx_QUALSEL_31C ) )


/** @defgroup COMP_VipSel
  * @{
  */
#define COMP1_VIP_SEL_PAD_PC5           ((uint32_t)0x00000000)
#define COMP1_VIP_SEL_PAD_PB2           ((uint32_t)0x00000100)

#define COMP2_VIP_SEL_PAD_PB4           ((uint32_t)0x00000000)
#define COMP2_VIP_SEL_PAD_PB6           ((uint32_t)0x00000100)

#define COMP3_VIP_SEL_PAD_PA0           ((uint32_t)0x00000000)
#define COMP3_VIP_SEL_PAD_PC1           ((uint32_t)0x00000100)
#define COMP3_VIP_SEL_PAD_PA2           ((uint32_t)0x00000200)
#define COMP3_VIP_SEL_PAD_PA5           ((uint32_t)0x00000300)

#define COMP4_VIP_SEL_PAD_PA2           ((uint32_t)0x00000000)
#define COMP4_VIP_SEL_PAD_PA5           ((uint32_t)0x00000100)
#define COMP4_VIP_SEL_PAD_PA0           ((uint32_t)0x00000200)
#define COMP4_VIP_SEL_PAD_PC1           ((uint32_t)0x00000300)

#define COMP5_VIP_SEL_PAD_PB11      ((uint32_t)0x00000000)
#define COMP5_VIP_SEL_PAD_PB14      ((uint32_t)0x00000100)
#define COMP5_VIP_SEL_PAD_PA15      ((uint32_t)0x00000200)
#define COMP5_VIP_SEL_PAD_PC11      ((uint32_t)0x00000300)

#define COMP6_VIP_SEL_PAD_PA15      ((uint32_t)0x00000000)
#define COMP6_VIP_SEL_PAD_PC11      ((uint32_t)0x00000100)
#define COMP6_VIP_SEL_PAD_PB11      ((uint32_t)0x00000200)
#define COMP6_VIP_SEL_PAD_PB14      ((uint32_t)0x00000300)


#define IS_COMP1_VIP_SEL(INPUT)     (((INPUT) ==COMP1_VIP_SEL_PAD_PC5 ) || \
                                  ((INPUT) ==COMP1_VIP_SEL_PAD_PB2 )    )

#define IS_COMP2_VIP_SEL(INPUT)     (((INPUT) ==COMP2_VIP_SEL_PAD_PB4 ) || \
                                  ((INPUT) ==COMP2_VIP_SEL_PAD_PB6 )  )

#define IS_COMP3_VIP_SEL(INPUT)     (((INPUT) ==COMP3_VIP_SEL_PAD_PA0 ) || \
                                  ((INPUT) ==COMP3_VIP_SEL_PAD_PC1 )  || \
                                  ((INPUT) ==COMP3_VIP_SEL_PAD_PA2 )  || \
                                  ((INPUT) ==COMP3_VIP_SEL_PAD_PA5 )    )

#define IS_COMP4_VIP_SEL(INPUT)     (((INPUT) == COMP4_VIP_SEL_PAD_PA2) || \
                                  ((INPUT) ==COMP4_VIP_SEL_PAD_PA5 )    || \
                                  ((INPUT) ==COMP4_VIP_SEL_PAD_PA0 )    || \
                                  ((INPUT) ==COMP4_VIP_SEL_PAD_PC1 )    )

#define IS_COMP5_VIP_SEL(INPUT)     (((INPUT) ==COMP5_VIP_SEL_PAD_PB11 ) || \
                                  ((INPUT) ==COMP5_VIP_SEL_PAD_PB14 )   || \
                                  ((INPUT) ==COMP5_VIP_SEL_PAD_PA15 )   || \
                                  ((INPUT) ==COMP5_VIP_SEL_PAD_PC11 )   )

#define IS_COMP6_VIP_SEL(INPUT)     (((INPUT) == COMP6_VIP_SEL_PAD_PA15) || \
                                  ((INPUT) ==COMP6_VIP_SEL_PAD_PC11 )   || \
                                  ((INPUT) ==COMP6_VIP_SEL_PAD_PB11 )   || \
                                  ((INPUT) ==COMP6_VIP_SEL_PAD_PB14 )   )

/** @defgroup COMP_VinSel
  * @{
  */
#define COMP1_VIN_1_4VREFINT            ((uint32_t)0x00000000 | VREFEN)
#define COMP1_VIN_1_2VREFINT            ((uint32_t)0x00000010 | VREFEN)
#define COMP1_VIN_3_4VREFINT            ((uint32_t)0x00000020 | VREFEN)
#define COMP1_VIN_VREFINT               ((uint32_t)0x00000030 | VREFEN)
#define COMP1_VIN_DAC1_CH1              ((uint32_t)0x00000040)
#define COMP1_VIN_DAC2_CH1            ((uint32_t)0x00000050)
#define COMP1_VIN_SEL_PAD_PB1     ((uint32_t)0x00000060)
#define COMP1_VIN_SEL_PAD_PC4       ((uint32_t)0x00000070)

#define COMP2_VIN_1_4VREFINT            ((uint32_t)0x00000000 | VREFEN)
#define COMP2_VIN_1_2VREFINT            ((uint32_t)0x00000010 | VREFEN)
#define COMP2_VIN_3_4VREFINT            ((uint32_t)0x00000020 | VREFEN)
#define COMP2_VIN_VREFINT               ((uint32_t)0x00000030 | VREFEN)
#define COMP2_VIN_DAC1_CH1              ((uint32_t)0x00000040)
#define COMP2_VIN_DAC2_CH1            ((uint32_t)0x00000050)
#define COMP2_VIN_SEL_PAD_PB3     ((uint32_t)0x00000060)
#define COMP2_VIN_SEL_PAD_PB7       ((uint32_t)0x00000070)

#define COMP3_VIN_3_4VREFINT            ((uint32_t)0x00000020 | VREFEN)
#define COMP3_VIN_VREFINT               ((uint32_t)0x00000030 | VREFEN)
#define COMP3_VIN_DAC1_CH1              ((uint32_t)0x00000040)
#define COMP3_VIN_DAC2_CH1            ((uint32_t)0x00000050)
#define COMP3_VIN_SEL_PAD_PC3     ((uint32_t)0x00000060)
#define COMP3_VIN_SEL_PAD_PC0       ((uint32_t)0x00000070)

#define COMP4_VIN_1_4VREFINT            ((uint32_t)0x00000000 | VREFEN)
#define COMP4_VIN_1_2VREFINT            ((uint32_t)0x00000010 | VREFEN)
#define COMP4_VIN_3_4VREFINT            ((uint32_t)0x00000020 | VREFEN)
#define COMP4_VIN_VREFINT               ((uint32_t)0x00000030 | VREFEN)
#define COMP4_VIN_DAC1_CH1              ((uint32_t)0x00000040)
#define COMP4_VIN_DAC2_CH1            ((uint32_t)0x00000050)
#define COMP4_VIN_SEL_PAD_PA1     ((uint32_t)0x00000060)
#define COMP4_VIN_SEL_PAD_PA4       ((uint32_t)0x00000070)

#define COMP5_VIN_3_4VREFINT            ((uint32_t)0x00000020 | VREFEN)
#define COMP5_VIN_VREFINT               ((uint32_t)0x00000030 | VREFEN)
#define COMP5_VIN_DAC1_CH1              ((uint32_t)0x00000040)
#define COMP5_VIN_DAC2_CH1            ((uint32_t)0x00000050)
#define COMP5_VIN_SEL_PAD_PB10    ((uint32_t)0x00000060)
#define COMP5_VIN_SEL_PAD_PB15    ((uint32_t)0x00000070)

#define COMP6_VIN_1_4VREFINT            ((uint32_t)0x00000000 | VREFEN)
#define COMP6_VIN_1_2VREFINT            ((uint32_t)0x00000010 | VREFEN)
#define COMP6_VIN_3_4VREFINT            ((uint32_t)0x00000020 | VREFEN)
#define COMP6_VIN_VREFINT               ((uint32_t)0x00000030 | VREFEN)
#define COMP6_VIN_DAC1_CH1              ((uint32_t)0x00000040)
#define COMP6_VIN_DAC2_CH1            ((uint32_t)0x00000050)
#define COMP6_VIN_SEL_PAD_PC10    ((uint32_t)0x00000060)
#define COMP6_VIN_SEL_PAD_PC12    ((uint32_t)0x00000070)


#define IS_COMP1_VIN_SEL(INPUT)     (((INPUT) ==COMP1_VIN_1_4VREFINT  ) || \
                                ((INPUT) == COMP1_VIN_1_2VREFINT )  || \
                                ((INPUT) == COMP1_VIN_3_4VREFINT )  || \
                                ((INPUT) == COMP1_VIN_VREFINT        )  || \
                                ((INPUT) == COMP1_VIN_DAC1_CH1   )  || \
                                ((INPUT) == COMP1_VIN_DAC2_CH1   )  || \
                                ((INPUT) == COMP1_VIN_SEL_PAD_PB1)  || \
                                ((INPUT) == COMP1_VIN_SEL_PAD_PC4)  )

#define IS_COMP2_VIN_SEL(INPUT)     (((INPUT) == COMP2_VIN_1_4VREFINT ) || \
                                ((INPUT) ==COMP2_VIN_1_2VREFINT  )  || \
                                ((INPUT) ==COMP2_VIN_3_4VREFINT  )  || \
                                ((INPUT) ==COMP2_VIN_VREFINT        )   || \
                                ((INPUT) ==COMP2_VIN_DAC1_CH1    )  || \
                                ((INPUT) ==COMP2_VIN_DAC2_CH1       )   || \
                                ((INPUT) ==COMP2_VIN_SEL_PAD_PB3 )  || \
                                ((INPUT) ==COMP2_VIN_SEL_PAD_PB7 )  )

#define IS_COMP3_VIN_SEL(INPUT)     (((INPUT) == COMP3_VIN_3_4VREFINT ) || \
                                ((INPUT) ==COMP3_VIN_VREFINT       )    || \
                                ((INPUT) ==COMP3_VIN_DAC1_CH1    )  || \
                                ((INPUT) ==COMP3_VIN_DAC2_CH1      )    || \
                                ((INPUT) ==COMP3_VIN_SEL_PAD_PC3 )  || \
                                ((INPUT) ==COMP3_VIN_SEL_PAD_PC0 )  )

#define IS_COMP4_VIN_SEL(INPUT)     (((INPUT) ==COMP4_VIN_1_4VREFINT  ) || \
                                ((INPUT) ==COMP4_VIN_1_2VREFINT  )  || \
                                ((INPUT) ==COMP4_VIN_3_4VREFINT  )  || \
                                ((INPUT) ==COMP4_VIN_VREFINT        )   || \
                                ((INPUT) ==COMP4_VIN_DAC1_CH1    )  || \
                                ((INPUT) ==COMP4_VIN_DAC2_CH1       )   || \
                                ((INPUT) ==COMP4_VIN_SEL_PAD_PA1 )  || \
                                ((INPUT) ==COMP4_VIN_SEL_PAD_PA4 )  )

#define IS_COMP5_VIN_SEL(INPUT)     (((INPUT) ==COMP5_VIN_3_4VREFINT  ) || \
                                ((INPUT) ==COMP5_VIN_VREFINT       )    || \
                                ((INPUT) ==COMP5_VIN_DAC1_CH1    )  || \
                                ((INPUT) ==COMP5_VIN_DAC2_CH1        )  || \
                                ((INPUT) ==COMP5_VIN_SEL_PAD_PB10 ) || \
                                ((INPUT) ==COMP5_VIN_SEL_PAD_PB15 ) )

#define IS_COMP6_VIN_SEL(INPUT)     (((INPUT) ==COMP6_VIN_1_4VREFINT  ) || \
                                ((INPUT) ==COMP6_VIN_1_2VREFINT  )  || \
                                ((INPUT) ==COMP6_VIN_3_4VREFINT  )  || \
                                ((INPUT) ==COMP6_VIN_VREFINT        )   || \
                                ((INPUT) ==COMP6_VIN_DAC1_CH1    )  || \
                                ((INPUT) ==COMP6_VIN_DAC2_CH1        )  || \
                                ((INPUT) ==COMP6_VIN_SEL_PAD_PC10 ) || \
                                ((INPUT) ==COMP6_VIN_SEL_PAD_PC12 ))

/** @defgroup COMP_Blanking_Sel
  * @{ COMPx = comp1 /comp2/ comp3/ comp4/ comp5 /comp6
  */
#define COMPx_BLANKING_NONE         ((uint32_t)0x00000000)
#define COMPx_BLANKING_TIM1         ((uint32_t)0x00100000)
#define COMPx_BLANKING_TIM2         ((uint32_t)0x00200000)
#define COMPx_BLANKING_TIM3     ((uint32_t)0x00300000)
#define COMPx_BLANKING_TIM4         ((uint32_t)0x00400000)
#define COMPx_BLANKING_TIM8         ((uint32_t)0x00700000)
#define IS_COMP_BLANKING(INPUT)        (((INPUT) == COMPx_BLANKING_NONE ) || \
                                     ((INPUT) == COMPx_BLANKING_TIM1 ) || \
                                     ((INPUT) == COMPx_BLANKING_TIM2 ) || \
                                     ((INPUT) == COMPx_BLANKING_TIM3 ) || \
                                     ((INPUT) == COMPx_BLANKING_TIM4 ) || \
                                     ((INPUT) == COMPx_BLANKING_TIM8 ))

/** @defgroup  COMP_Hysteresis_Sel
  * @{ COMPx = comp1 /comp2/ comp3/ comp4/ comp5 /comp6
  */
#define COMPx_HYST_NONE              ((uint32_t)0x00000000)
#define COMPx_HYST_18MV              ((uint32_t)0x00020000)
#define COMPx_HYST_36MV              ((uint32_t)0x00040000)
#define COMPx_HYST_54MV              ((uint32_t)0x00060000)
#define IS_COMP_HYSTERESIS(INPUT)   (((INPUT) == COMPx_HYST_NONE ) || \
                                     ((INPUT) == COMPx_HYST_18MV ) || \
                                     ((INPUT) == COMPx_HYST_36MV ) || \
                                     ((INPUT) == COMPx_HYST_54MV ))

/** @defgroup COMP_Pol
  * @{COMPx = comp1 /comp2/ comp3/ comp4/ comp5 /comp6
  */
#define COMPx_POL_NOT_INVERT                ((uint32_t)0x00000000)
#define COMPx_POL_INVERT                      ((uint32_t)0x00008000)

#define IS_COMP_POL(POL)                 (((POL) == COMPx_POL_NOT_INVERT)|| \
                                                         ( (POL) == COMPx_POL_INVERT)       )

/** @defgroup COMP_RAMP_SEL
  * @{COMPx = comp1 /comp2
  */
#define COMPx_RAMPSRC_PWM1              ((uint32_t)0x00000000)
#define COMPx_RAMPSRC_PWM2              ((uint32_t)0x01000000)
#define COMPx_RAMPSRC_PWM3              ((uint32_t)0x02000000)
#define COMPx_RAMPSRC_PWM4              ((uint32_t)0x03000000)

#define IS_COMP_RAMPSRC(EPWM)                    (((EPWM) == COMPx_RAMPSRC_PWM1)|| \
                                          ((EPWM) == COMPx_RAMPSRC_PWM2)|| \
                                          ((EPWM) == COMPx_RAMPSRC_PWM3)|| \
                                                                ((EPWM) == COMPx_RAMPSRC_PWM4))



/** @defgroup COMP_OutputLevel
  * @{
  */
/* When output polarity is not inverted, comparator output is high when
   the non-inverting input is at a higher voltage than the inverting input */
#define COMP_OutputLevel_High                   ((uint32_t)0x40000000)
/* When output polarity is not inverted, comparator output is low when
   the non-inverting input is at a lower voltage than the inverting input*/
#define COMP_OutputLevel_Low                    ((uint32_t)0x00000000)


#define IS_COMP_OUTPUT_LEVEL(LEVEL)         (((LEVEL) == COMP_CSR_COMP1OUT) || \
                                                              ((LEVEL) == COMP_CSR_COMP2OUT))





/* Initialization and Configuration functions *********************************/
void COMP_Init(uint32_t COMP_Selection, COMP_InitTypeDef* COMP_InitStruct);
void COMP_DeInit(uint32_t COMP_Selection);

/*  Function used to set the COMP configuration to the default reset state ****/
void COMP_Cmd(uint32_t COMP_Selection, FunctionalState NewState);
void COMP_WindowCmd(FunctionalState NewState, uint32_t COMP_Selection);
void COMPx_RAMP_EPWM_SEL(uint32_t COMP_1_2_Selection, uint32_t COMP_RAMP_SEL);
void COMPx_RAMP_RMPRLDIS(FunctionalState NewState, uint32_t COMP_1_2_Selection);
void COMP_RAMPVAL_SHADOW_LOAD(uint32_t COMP_1_2_Selection, uint16_t COMPx_RAMPDECVAL_SHADOW, uint16_t COMPx_RAMPMAXREF_SHADOW);

void COMPx_QUALIFICATION(FunctionalState NewState, uint32_t COMP_1_2_Selection, uint32_t COMP_qualsel);
void COMPx_Resistor(FunctionalState NewState, uint32_t COMP_1_2_Selection);
void COMP_LockConfig(uint32_t COMP_Selection);
uint32_t COMP_GetOutputLevel(uint32_t COMP_Selection);

#ifdef __cplusplus
}
#endif

#endif /* __FT32F0XX_COMP_H */

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT FMD *****END OF FILE****/








