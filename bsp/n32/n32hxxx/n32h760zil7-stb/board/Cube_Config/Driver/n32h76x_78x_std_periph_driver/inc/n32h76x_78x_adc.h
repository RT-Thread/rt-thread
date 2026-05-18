/**
*     Copyright (c) 2025, Nations Technologies Inc.
* 
*     All rights reserved.
*
*     This software is the exclusive property of Nations Technologies Inc. (Hereinafter 
* referred to as NATIONS). This software, and the product of NATIONS described herein 
* (Hereinafter referred to as the Product) are owned by NATIONS under the laws and treaties
* of the People's Republic of China and other applicable jurisdictions worldwide.
*
*     NATIONS does not grant any license under its patents, copyrights, trademarks, or other 
* intellectual property rights. Names and brands of third party may be mentioned or referred 
* thereto (if any) for identification purposes only.
*
*     NATIONS reserves the right to make changes, corrections, enhancements, modifications, and 
* improvements to this software at any time without notice. Please contact NATIONS and obtain 
* the latest version of this software before placing orders.

*     Although NATIONS has attempted to provide accurate and reliable information, NATIONS assumes 
* no responsibility for the accuracy and reliability of this software.
* 
*     It is the responsibility of the user of this software to properly design, program, and test 
* the functionality and safety of any application made of this information and any resulting product. 
* In no event shall NATIONS be liable for any direct, indirect, incidental, special,exemplary, or 
* consequential damages arising in any way out of the use of this software or the Product.
*
*     NATIONS Products are neither intended nor warranted for usage in systems or equipment, any
* malfunction or failure of which may cause loss of human life, bodily injury or severe property 
* damage. Such applications are deemed, "Insecure Usage".
*
*     All Insecure Usage shall be made at user's risk. User shall indemnify NATIONS and hold NATIONS 
* harmless from and against all claims, costs, damages, and other liabilities, arising from or related 
* to any customer's Insecure Usage.

*     Any express or implied warranty with regard to this software or the Product, including,but not 
* limited to, the warranties of merchantability, fitness for a particular purpose and non-infringement
* are disclaimed to the fullest extent permitted by law.

*     Unless otherwise explicitly permitted by NATIONS, anyone may not duplicate, modify, transcribe
* or otherwise distribute this software for any purposes, in whole or in part.
*
*     NATIONS products and technologies shall not be used for or incorporated into any products or systems
* whose manufacture, use, or sale is prohibited under any applicable domestic or foreign laws or regulations. 
* User shall comply with any applicable export control laws and regulations promulgated and administered by 
* the governments of any countries asserting jurisdiction over the parties or transactions.
**/

/**
 * @file n32h76x_78x_adc.h
 * @author Nations
 * @version v1.0.0
 *
 * @copyright Copyright (c) 2025, Nations Technologies Inc. All rights reserved.
 */#ifndef __N32H76X_78X_ADC_H__
#define __N32H76X_78X_ADC_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "n32h76x_78x.h"
#include <stdbool.h>



/** ADC_Exported_Types **/


/** ADC Init structure definition **/
typedef struct
{
    uint32_t WorkMode;  /* Configures the ADC to operate in independent or  dual mode.*/
                           
    FunctionalState MultiChEn; /* Specifies whether the conversion is performed in
                                  Scan (multichannels) or Single (one channel) mode.  */

    FunctionalState ContinueConvEn; /* Specifies whether the conversion is performed in
                                       Continuous or Single mode. */
    uint32_t ExtTrigSelect;  /*Set ADC group regular conversion trigger source: internal (SW start) or from external peripheral */

    uint32_t DataTransferMode; /*Set ADC group regular conversion data transfer mode: no transfer, transfer by DMA  or DFSDM.*/

    uint32_t DatAlign;   /* Set ADC conversion data alignment.*/

    uint8_t  ChsNumber;  /* Set ADC group regular sequencer length*/

    uint32_t Resolution; /* Set ADC resolution*/

} ADC_InitType;

/** ADC offset structure definition **/
typedef struct
{
    FunctionalState OffsetEn;       /* Set Offset enable or disable*/
    FunctionalState OffsetSatenEn;  /* Set Offset satera*/
    FunctionalState OffsetDirPositiveEn;
    uint8_t  OffsetChannel;
    uint16_t OffsetData;
} ADC_OffsetType;

 
typedef enum
{
    ADC_CTRL3_CKMOD_AHB = 0,
    ADC_CTRL3_CKMOD_PLL = 1,
} ADC_CTRL3_CKMOD;

typedef enum
{
    ADC_AWDG1  = 0,
    ADC_AWDG2  = 1,
    ADC_AWDG3  = 2,  
} ADC_AWDG;

 /**  Multimode - Delay between two sampling phases **/
#define ADC_ADC_MULTI_TWOSMP_DELAY_MASK           (ADC_DLYSMP_INTLEADVAL)
#define ADC_ADC_MULTI_TWOSMP_DELAY_CYCLE_1        ((uint32_t)0x00000000U << 28U) /**1 ADC clock cycle */
#define ADC_ADC_MULTI_TWOSMP_DELAY_CYCLE_2        ((uint32_t)0x00000001U << 28U) /**2 ADC clock cycle */
#define ADC_ADC_MULTI_TWOSMP_DELAY_CYCLE_3        ((uint32_t)0x00000002U << 28U) /**3 ADC clock cycle */
#define ADC_ADC_MULTI_TWOSMP_DELAY_CYCLE_4        ((uint32_t)0x00000003U << 28U) /**4 ADC clock cycle */
#define ADC_ADC_MULTI_TWOSMP_DELAY_CYCLE_5        ((uint32_t)0x00000004U << 28U) /**5 ADC clock cycle */
#define ADC_ADC_MULTI_TWOSMP_DELAY_CYCLE_6        ((uint32_t)0x00000005U << 28U) /**6 ADC clock cycle */
#define ADC_ADC_MULTI_TWOSMP_DELAY_CYCLE_7        ((uint32_t)0x00000006U << 28U) /**7 ADC clock cycle */
#define ADC_ADC_MULTI_TWOSMP_DELAY_CYCLE_8        ((uint32_t)0x00000007U << 28U) /**8 ADC clock cycle */
#define ADC_ADC_MULTI_TWOSMP_DELAY_CYCLE_9        ((uint32_t)0x00000008U << 28U) /**9 ADC clock cycle */
#define ADC_ADC_MULTI_TWOSMP_DELAY_CYCLE_10       ((uint32_t)0x00000009U << 28U) /**0 ADC clock cycle */
#define ADC_ADC_MULTI_TWOSMP_DELAY_CYCLE_11       ((uint32_t)0x0000000AU << 28U) /**11 ADC clock cycle */
#define ADC_ADC_MULTI_TWOSMP_DELAY_CYCLE_12       ((uint32_t)0x0000000BU << 28U) /**12 ADC clock cycle */
#define ADC_ADC_MULTI_TWOSMP_DELAY_CYCLE_13       ((uint32_t)0x0000000CU << 28U) /**13 ADC clock cycle */
#define ADC_ADC_MULTI_TWOSMP_DELAY_CYCLE_14       ((uint32_t)0x0000000DU << 28U) /**14 ADC clock cycle */
#define ADC_ADC_MULTI_TWOSMP_DELAY_CYCLE_15       ((uint32_t)0x0000000EU << 28U) /**15 ADC clock cycle */
#define ADC_ADC_MULTI_TWOSMP_DELAY_CYCLE_16       ((uint32_t)0x0000000FU << 28U) /**16 ADC clock cycle */


 /**  Indenpent mode - Delay between two sampling phases **/
#define ADC_INDENPENT_TWOSMP_DELAY_EN_MASK        (ADC_DLYSMP_DLYSAMPEN)

#define ADC_INDENPENT_TWOSMP_DELAY_MASK           (ADC_DLYSMP_DLYVAL | ADC_INDENPENT_TWOSMP_DELAY_EN_MASK)
#define ADC_INDENPENT_TWOSMP_DELAY_CYCLE_1        (((uint32_t)0x00000000U << 24U)|ADC_INDENPENT_TWOSMP_DELAY_EN_MASK) /**1 ADC clock cycle */
#define ADC_INDENPENT_TWOSMP_DELAY_CYCLE_2        (((uint32_t)0x00000001U << 24U)|ADC_INDENPENT_TWOSMP_DELAY_EN_MASK) /**2 ADC clock cycle */
#define ADC_INDENPENT_TWOSMP_DELAY_CYCLE_3        (((uint32_t)0x00000002U << 24U)|ADC_INDENPENT_TWOSMP_DELAY_EN_MASK) /**3 ADC clock cycle */
#define ADC_INDENPENT_TWOSMP_DELAY_CYCLE_4        (((uint32_t)0x00000003U << 24U)|ADC_INDENPENT_TWOSMP_DELAY_EN_MASK) /**4 ADC clock cycle */
#define ADC_INDENPENT_TWOSMP_DELAY_CYCLE_5        (((uint32_t)0x00000004U << 24U)|ADC_INDENPENT_TWOSMP_DELAY_EN_MASK) /**5 ADC clock cycle */
#define ADC_INDENPENT_TWOSMP_DELAY_CYCLE_6        (((uint32_t)0x00000005U << 24U)|ADC_INDENPENT_TWOSMP_DELAY_EN_MASK) /**6 ADC clock cycle */
#define ADC_INDENPENT_TWOSMP_DELAY_CYCLE_7        (((uint32_t)0x00000006U << 24U)|ADC_INDENPENT_TWOSMP_DELAY_EN_MASK) /**7 ADC clock cycle */
#define ADC_INDENPENT_TWOSMP_DELAY_CYCLE_8        (((uint32_t)0x00000007U << 24U)|ADC_INDENPENT_TWOSMP_DELAY_EN_MASK) /**8 ADC clock cycle */
#define ADC_INDENPENT_TWOSMP_DELAY_CYCLE_9        (((uint32_t)0x00000008U << 24U)|ADC_INDENPENT_TWOSMP_DELAY_EN_MASK) /**9 ADC clock cycle */
#define ADC_INDENPENT_TWOSMP_DELAY_CYCLE_10       (((uint32_t)0x00000009U << 24U)|ADC_INDENPENT_TWOSMP_DELAY_EN_MASK) /**10 ADC clock cycle */
#define ADC_INDENPENT_TWOSMP_DELAY_CYCLE_11       (((uint32_t)0x0000000AU << 24U)|ADC_INDENPENT_TWOSMP_DELAY_EN_MASK) /**11 ADC clock cycle */
#define ADC_INDENPENT_TWOSMP_DELAY_CYCLE_12       (((uint32_t)0x0000000BU << 24U)|ADC_INDENPENT_TWOSMP_DELAY_EN_MASK) /**12 ADC clock cycle */
#define ADC_INDENPENT_TWOSMP_DELAY_CYCLE_13       (((uint32_t)0x0000000CU << 24U)|ADC_INDENPENT_TWOSMP_DELAY_EN_MASK) /**13 ADC clock cycle */
#define ADC_INDENPENT_TWOSMP_DELAY_CYCLE_14       (((uint32_t)0x0000000DU << 24U)|ADC_INDENPENT_TWOSMP_DELAY_EN_MASK) /**14 ADC clock cycle */
#define ADC_INDENPENT_TWOSMP_DELAY_CYCLE_15       (((uint32_t)0x0000000EU << 24U)|ADC_INDENPENT_TWOSMP_DELAY_EN_MASK) /**15 ADC clock cycle */
#define ADC_INDENPENT_TWOSMP_DELAY_CYCLE_16       (((uint32_t)0x0000000FU << 24U)|ADC_INDENPENT_TWOSMP_DELAY_EN_MASK) /**16 ADC clock cycle */

/**  ADC_muli_mode ,including dual-ADC mode and tripple-ADC mode **/
#define ADC_WORKMODE_MULT_MASK                    (ADC_CTRL1_MULTMODE)
#define ADC_WORKMODE_INDEPENDENT                  ((uint32_t)0x00000000U << 11U)
/**  Dual-ADC mode **/
#define ADC_WORKMODE_DUAL_REG_INJECT_SIMULT       ((uint32_t)0x00000001U << 11U)
#define ADC_WORKMODE_DUAL_REG_SIMULT_ALTER_TRIG   ((uint32_t)0x00000002U << 11U)
#define ADC_WORKMODE_DUAL_INJ_SIMULT_INTERL       ((uint32_t)0x00000003U << 11U)
#define ADC_WORKMODE_DUAL_INJ_SIMULT              ((uint32_t)0x00000005U << 11U)
#define ADC_WORKMODE_DUAL_REG_SIMULT              ((uint32_t)0x00000006U << 11U)
#define ADC_WORKMODE_DUAL_INTERL                  ((uint32_t)0x00000007U << 11U)
#define ADC_WORKMODE_DUAL_ALTER_TRIG              ((uint32_t)0x00000009U << 11U)
/**  Tripple-ADC mode **/
#define ADC_WORKMODE_TRIPPLE_REG_INJECT_SIMULT    ((uint32_t)0x00000011U  << 11U)
#define ADC_WORKMODE_TRIPPLE_REG_SIMULT_ALTER_TRIG ((uint32_t)0x00000012U << 11U)
#define ADC_WORKMODE_TRIPPLE_INJ_SIMULT_INTERL    ((uint32_t)0x00000013U  << 11U)
#define ADC_WORKMODE_TRIPPLE_INJ_SIMULT           ((uint32_t)0x00000015U  << 11U)
#define ADC_WORKMODE_TRIPPLE_REG_SIMULT           ((uint32_t)0x00000016U  << 11U)
#define ADC_WORKMODE_TRIPPLE_INTERL               ((uint32_t)0x00000017U  << 11U)
#define ADC_WORKMODE_TRIPPLE_ALTER_TRIG           ((uint32_t)0x00000019U  << 11U)


/** ADC CTRL1 MASK **/
#define ADC_SCANMD_EN_MASK                        (ADC_CTRL1_SCANMD) /* Muti-channels enable mask */
#define ADC_JAUTO_EN_MASK                         (ADC_CTRL1_AUTOJC) /* Automatic injected group conversion enable mask */

#define ADC_DISC_REG_EN_MASK                      (ADC_CTRL1_DREGCH) /* ADC Discontinous mode enable on regluar channels mask */
#define ADC_DISC_INJ_EN_MASK                      (ADC_CTRL1_DJCH) /* ADC Discontinous mode enable on injected channels mask */

#define ADC_DISC_NUM_MASK                         (ADC_CTRL1_DCTU) /* ADC Discontinuous mode channel count */
/**  ADC_channels_definition **/
#define ADC_CH_MASK                               (ADC_CTRL1_AWD1CH)
#define ADC_CH_0                                  ((uint8_t)0x00U)
#define ADC_CH_1                                  ((uint8_t)0x01U)
#define ADC_CH_2                                  ((uint8_t)0x02U)
#define ADC_CH_3                                  ((uint8_t)0x03U)
#define ADC_CH_4                                  ((uint8_t)0x04U)
#define ADC_CH_5                                  ((uint8_t)0x05U)
#define ADC_CH_6                                  ((uint8_t)0x06U)
#define ADC_CH_7                                  ((uint8_t)0x07U)
#define ADC_CH_8                                  ((uint8_t)0x08U)
#define ADC_CH_9                                  ((uint8_t)0x09U)
#define ADC_CH_10                                 ((uint8_t)0x0AU)
#define ADC_CH_11                                 ((uint8_t)0x0BU)
#define ADC_CH_12                                 ((uint8_t)0x0CU)
#define ADC_CH_13                                 ((uint8_t)0x0DU)
#define ADC_CH_14                                 ((uint8_t)0x0EU)
#define ADC_CH_15                                 ((uint8_t)0x0FU)
#define ADC_CH_16                                 ((uint8_t)0x10U)
#define ADC_CH_17                                 ((uint8_t)0x11U)
#define ADC_CH_18                                 ((uint8_t)0x12U)
#define ADC_CH_19                                 ((uint8_t)0x13U)

/**  ADC_analog_watchdog_channels_Mask_definition **/
#define ADC_AWD1CH_MASK                           (ADC_CTRL1_AWD1CH)

/**  ADC_analog_watchdog_selection **/
#define ADC_ANALOG_WTDG_SINGLEREG_ENABLE          (ADC_CTRL1_AWD1SGLEN | ADC_CTRL1_AWD1ERCH)
#define ADC_ANALOG_WTDG_SINGLEINJEC_ENABLE        (ADC_CTRL1_AWD1SGLEN | ADC_CTRL1_AWD1EJCH)
#define ADC_ANALOG_WTDG_SINGLEREG_OR_INJEC_ENABLE (ADC_CTRL1_AWD1SGLEN | ADC_CTRL1_AWD1ERCH | ADC_CTRL1_AWD1EJCH)
#define ADC_ANALOG_WTDG_ALLREG_ENABLE             (ADC_CTRL1_AWD1ERCH)
#define ADC_ANALOG_WTDG_ALLINJEC_ENABLE           (ADC_CTRL1_AWD1EJCH)
#define ADC_ANALOG_WTDG_ALLREG_ALLINJEC_ENABLE    (ADC_CTRL1_AWD1ERCH | ADC_CTRL1_AWD1EJCH)
#define ADC_ANALOG_WTDG_NONE                      ((uint32_t)0x00000000U)

/** ADC CTRL2 MASK **/
#define ADC_ON_EN_MASK                            (ADC_CTRL2_ON) /* ADC enable mask */
#define ADC_CONT_EN_MASK                          (ADC_CTRL2_CTU) /* ADC continuous conversion mask */
#define ADC_CALI_EN_MASK                          (ADC_CTRL2_ENCAL) /* A/D start calibration mask */
#define ADC_MUTI_ADC_DSMU_MASK                    (ADC_CTRL2_MDSMU) /* Multi-adc DSMU mode mask */

/** ADC_Regular_Group_Trigger_Edge_Configuration **/
#define ADC_REG_TRIG_EXT_MASK                     (ADC_CTRL2_EXTPRSEL) 
#define ADC_REG_TRIG_EXT_SOFTWARE                 ((uint32_t)0x00000000U) 
#define ADC_REG_TRIG_EXT_RISING                   (ADC_CTRL2_EXTPRSEL_0)                          /* rising edge */
#define ADC_REG_TRIG_EXT_FALLING                  (ADC_CTRL2_EXTPRSEL_1)                          /* falling edge */
#define ADC_REG_TRIG_EXT_RISINGFALLING            (ADC_CTRL2_EXTPRSEL_1 | ADC_CTRL2_EXTPRSEL_0)   /* rising and falling edges */

#define ADC_REG_TRIG_EXT_EDGE_DEFAULT             (ADC_REG_TRIG_EXT_RISING)                       /* default trigger rising edge */ 
/** ADC_Injected_Group_Trigger_Edge_Configuration **/
#define ADC_INJ_TRIG_EXT_MASK                     (ADC_CTRL2_EXTPJSEL)
#define ADC_INJ_TRIG_EXT_SOFTWARE                 ((uint32_t)0x00000000U) 
#define ADC_INJ_TRIG_EXT_RISING                   (ADC_CTRL2_EXTPJSEL_0)                          /* rising edge */
#define ADC_INJ_TRIG_EXT_FALLING                  (ADC_CTRL2_EXTPJSEL_1)                          /* falling edge */
#define ADC_INJ_TRIG_EXT_RISINGFALLING            (ADC_CTRL2_EXTPJSEL_1 | ADC_CTRL2_EXTPJSEL_0)   /* rising and falling edges */

#define ADC_INJ_TRIG_EXT_EDGE_DEFAULT             (ADC_INJ_TRIG_EXT_RISING)                       /* default trigger rising edge */

/**  ADC_external_trigger_sources_for_injected_channels_conversion **/
#define ADC_EXT_TRIG_INJ_CONV_MASK                (ADC_CTRL2_EXTJSEL | ADC_INJ_TRIG_EXT_MASK) 
#define ADC_EXT_TRIG_INJ_CONV_ATIM1_CC1           (((uint32_t)0x00000000U << 13U) | ADC_INJ_TRIG_EXT_EDGE_DEFAULT) 
#define ADC_EXT_TRIG_INJ_CONV_ATIM1_CC2           (((uint32_t)0x00000001U << 13U) | ADC_INJ_TRIG_EXT_EDGE_DEFAULT) 
#define ADC_EXT_TRIG_INJ_CONV_ATIM1_CC3           (((uint32_t)0x00000002U << 13U) | ADC_INJ_TRIG_EXT_EDGE_DEFAULT) 
#define ADC_EXT_TRIG_INJ_CONV_ATIM1_CC4           (((uint32_t)0x00000003U << 13U) | ADC_INJ_TRIG_EXT_EDGE_DEFAULT) 
#define ADC_EXT_TRIG_INJ_CONV_ATIM1_TRGO          (((uint32_t)0x00000004U << 13U) | ADC_INJ_TRIG_EXT_EDGE_DEFAULT) 
#define ADC_EXT_TRIG_INJ_CONV_ATIM2_CC1           (((uint32_t)0x00000005U << 13U) | ADC_INJ_TRIG_EXT_EDGE_DEFAULT) 
#define ADC_EXT_TRIG_INJ_CONV_ATIM2_CC2           (((uint32_t)0x00000006U << 13U) | ADC_INJ_TRIG_EXT_EDGE_DEFAULT) 
#define ADC_EXT_TRIG_INJ_CONV_ATIM2_CC3           (((uint32_t)0x00000007U << 13U) | ADC_INJ_TRIG_EXT_EDGE_DEFAULT) 
#define ADC_EXT_TRIG_INJ_CONV_ATIM1_TRGO2         (((uint32_t)0x00000008U << 13U) | ADC_INJ_TRIG_EXT_EDGE_DEFAULT) 
#define ADC_EXT_TRIG_INJ_CONV_ATIM2_TRGO          (((uint32_t)0x00000009U << 13U) | ADC_INJ_TRIG_EXT_EDGE_DEFAULT) 
#define ADC_EXT_TRIG_INJ_CONV_ATIM3_CC1           (((uint32_t)0x0000000AU << 13U) | ADC_INJ_TRIG_EXT_EDGE_DEFAULT) 
#define ADC_EXT_TRIG_INJ_CONV_ATIM3_CC2           (((uint32_t)0x0000000BU << 13U) | ADC_INJ_TRIG_EXT_EDGE_DEFAULT) 
#define ADC_EXT_TRIG_INJ_CONV_ATIM3_CC3           (((uint32_t)0x0000000CU << 13U) | ADC_INJ_TRIG_EXT_EDGE_DEFAULT) 
#define ADC_EXT_TRIG_INJ_CONV_ATIM3_CC4           (((uint32_t)0x0000000DU << 13U) | ADC_INJ_TRIG_EXT_EDGE_DEFAULT) 
#define ADC_EXT_TRIG_INJ_CONV_ATIM2_TRGO2         (((uint32_t)0x0000000EU << 13U) | ADC_INJ_TRIG_EXT_EDGE_DEFAULT) 
#define ADC_EXT_TRIG_INJ_CONV_ATIM3_TRGO          (((uint32_t)0x0000000FU << 13U) | ADC_INJ_TRIG_EXT_EDGE_DEFAULT) 
#define ADC_EXT_TRIG_INJ_CONV_ATIM4_TRGO2         (((uint32_t)0x00000010U << 13U) | ADC_INJ_TRIG_EXT_EDGE_DEFAULT) 
#define ADC_EXT_TRIG_INJ_CONV_ATIM3_TRGO2         (((uint32_t)0x00000011U << 13U) | ADC_INJ_TRIG_EXT_EDGE_DEFAULT) 
#define ADC_EXT_TRIG_INJ_CONV_ATIM4_TRGO          (((uint32_t)0x00000012U << 13U) | ADC_INJ_TRIG_EXT_EDGE_DEFAULT) 
#define ADC_EXT_TRIG_INJ_CONV_GTIMB1_TRGO         (((uint32_t)0x00000013U << 13U) | ADC_INJ_TRIG_EXT_EDGE_DEFAULT) 
#define ADC_EXT_TRIG_INJ_CONV_GTIMB2_TRGO         (((uint32_t)0x00000014U << 13U) | ADC_INJ_TRIG_EXT_EDGE_DEFAULT) 
#define ADC_EXT_TRIG_INJ_CONV_GTIMB3_TRGO         (((uint32_t)0x00000015U << 13U) | ADC_INJ_TRIG_EXT_EDGE_DEFAULT) 
#define ADC_EXT_TRIG_INJ_CONV_GTIMA1_TRGO         (((uint32_t)0x00000016U << 13U) | ADC_INJ_TRIG_EXT_EDGE_DEFAULT) 
#define ADC_EXT_TRIG_INJ_CONV_GTIMB1_CC1          (((uint32_t)0x00000017U << 13U) | ADC_INJ_TRIG_EXT_EDGE_DEFAULT) 
#define ADC_EXT_TRIG_INJ_CONV_GTIMB2_CC4          (((uint32_t)0x00000018U << 13U) | ADC_INJ_TRIG_EXT_EDGE_DEFAULT) 
#define ADC_EXT_TRIG_INJ_CONV_GTIMB3_CC1          (((uint32_t)0x00000019U << 13U) | ADC_INJ_TRIG_EXT_EDGE_DEFAULT) 
#define ADC_EXT_TRIG_INJ_CONV_GTIMA1_CC3          (((uint32_t)0x0000001AU << 13U) | ADC_INJ_TRIG_EXT_EDGE_DEFAULT) 
#define ADC_EXT_TRIG_INJ_CONV_SHRTIM1_TRGO2       (((uint32_t)0x0000001BU << 13U) | ADC_INJ_TRIG_EXT_EDGE_DEFAULT) 
#define ADC_EXT_TRIG_INJ_CONV_SHRTIM1_TRGO4       (((uint32_t)0x0000001CU << 13U) | ADC_INJ_TRIG_EXT_EDGE_DEFAULT) 
#define ADC_EXT_TRIG_INJ_CONV_SHRTIM2_TRGO2       (((uint32_t)0x0000001DU << 13U) | ADC_INJ_TRIG_EXT_EDGE_DEFAULT) 
#define ADC_EXT_TRIG_INJ_CONV_SHRTIM2_TRGO4       (((uint32_t)0x0000001EU << 13U) | ADC_INJ_TRIG_EXT_EDGE_DEFAULT) 
#define ADC_EXT_TRIG_INJ_CONV_EXT_INT0_15         (((uint32_t)0x0000001FU << 13U) | ADC_INJ_TRIG_EXT_EDGE_DEFAULT) 
#define ADC_EXT_TRIG_INJ_CONV_SOFTWARE            (((uint32_t)0x00000000U << 13U))

/**  ADC_external_trigger_sources_for_regular_channels_conversion **/
#define ADC_EXT_TRIG_REG_CONV_MASK                (ADC_CTRL2_EXTRSEL | ADC_REG_TRIG_EXT_MASK) 
#define ADC_EXT_TRIG_REG_CONV_ATIM1_CC1           (((uint32_t)0x00000000U << 24U) | ADC_REG_TRIG_EXT_EDGE_DEFAULT) 
#define ADC_EXT_TRIG_REG_CONV_ATIM1_CC2           (((uint32_t)0x00000001U << 24U) | ADC_REG_TRIG_EXT_EDGE_DEFAULT)
#define ADC_EXT_TRIG_REG_CONV_ATIM1_CC3           (((uint32_t)0x00000002U << 24U) | ADC_REG_TRIG_EXT_EDGE_DEFAULT)
#define ADC_EXT_TRIG_REG_CONV_ATIM1_CC4           (((uint32_t)0x00000003U << 24U) | ADC_REG_TRIG_EXT_EDGE_DEFAULT)
#define ADC_EXT_TRIG_REG_CONV_ATIM1_TRGO          (((uint32_t)0x00000004U << 24U) | ADC_REG_TRIG_EXT_EDGE_DEFAULT)
#define ADC_EXT_TRIG_REG_CONV_ATIM2_CC1           (((uint32_t)0x00000005U << 24U) | ADC_REG_TRIG_EXT_EDGE_DEFAULT)
#define ADC_EXT_TRIG_REG_CONV_ATIM2_CC2           (((uint32_t)0x00000006U << 24U) | ADC_REG_TRIG_EXT_EDGE_DEFAULT)
#define ADC_EXT_TRIG_REG_CONV_ATIM2_CC3           (((uint32_t)0x00000007U << 24U) | ADC_REG_TRIG_EXT_EDGE_DEFAULT)
#define ADC_EXT_TRIG_REG_CONV_ATIM1_TRGO2         (((uint32_t)0x00000008U << 24U) | ADC_REG_TRIG_EXT_EDGE_DEFAULT)
#define ADC_EXT_TRIG_REG_CONV_ATIM2_TRGO          (((uint32_t)0x00000009U << 24U) | ADC_REG_TRIG_EXT_EDGE_DEFAULT)
#define ADC_EXT_TRIG_REG_CONV_ATIM3_CC1           (((uint32_t)0x0000000AU << 24U) | ADC_REG_TRIG_EXT_EDGE_DEFAULT)
#define ADC_EXT_TRIG_REG_CONV_ATIM3_CC2           (((uint32_t)0x0000000BU << 24U) | ADC_REG_TRIG_EXT_EDGE_DEFAULT)
#define ADC_EXT_TRIG_REG_CONV_ATIM3_CC3           (((uint32_t)0x0000000CU << 24U) | ADC_REG_TRIG_EXT_EDGE_DEFAULT)
#define ADC_EXT_TRIG_REG_CONV_ATIM3_CC4           (((uint32_t)0x0000000DU << 24U) | ADC_REG_TRIG_EXT_EDGE_DEFAULT)
#define ADC_EXT_TRIG_REG_CONV_ATIM2_TRGO2         (((uint32_t)0x0000000EU << 24U) | ADC_REG_TRIG_EXT_EDGE_DEFAULT)
#define ADC_EXT_TRIG_REG_CONV_ATIM3_TRGO          (((uint32_t)0x0000000FU << 24U) | ADC_REG_TRIG_EXT_EDGE_DEFAULT)
#define ADC_EXT_TRIG_REG_CONV_ATIM4_TRGO2         (((uint32_t)0x00000010U << 24U) | ADC_REG_TRIG_EXT_EDGE_DEFAULT)
#define ADC_EXT_TRIG_REG_CONV_ATIM3_TRGO2         (((uint32_t)0x00000011U << 24U) | ADC_REG_TRIG_EXT_EDGE_DEFAULT)
#define ADC_EXT_TRIG_REG_CONV_ATIM4_TRGO          (((uint32_t)0x00000012U << 24U) | ADC_REG_TRIG_EXT_EDGE_DEFAULT)
#define ADC_EXT_TRIG_REG_CONV_GTIMB1_TRGO         (((uint32_t)0x00000013U << 24U) | ADC_REG_TRIG_EXT_EDGE_DEFAULT)
#define ADC_EXT_TRIG_REG_CONV_GTIMB2_TRGO         (((uint32_t)0x00000014U << 24U) | ADC_REG_TRIG_EXT_EDGE_DEFAULT)
#define ADC_EXT_TRIG_REG_CONV_GTIMB3_TRGO         (((uint32_t)0x00000015U << 24U) | ADC_REG_TRIG_EXT_EDGE_DEFAULT)
#define ADC_EXT_TRIG_REG_CONV_GTIMA1_TRGO         (((uint32_t)0x00000016U << 24U) | ADC_REG_TRIG_EXT_EDGE_DEFAULT)
#define ADC_EXT_TRIG_REG_CONV_GTIMB1_CC2          (((uint32_t)0x00000017U << 24U) | ADC_REG_TRIG_EXT_EDGE_DEFAULT)
#define ADC_EXT_TRIG_REG_CONV_GTIMB2_CC4          (((uint32_t)0x00000018U << 24U) | ADC_REG_TRIG_EXT_EDGE_DEFAULT)
#define ADC_EXT_TRIG_REG_CONV_GTIMB3_CC2          (((uint32_t)0x00000019U << 24U) | ADC_REG_TRIG_EXT_EDGE_DEFAULT)
#define ADC_EXT_TRIG_REG_CONV_GTIMA1_CC4          (((uint32_t)0x0000001AU << 24U) | ADC_REG_TRIG_EXT_EDGE_DEFAULT)
#define ADC_EXT_TRIG_REG_CONV_SHRTIM1_TRGO1       (((uint32_t)0x0000001BU << 24U) | ADC_REG_TRIG_EXT_EDGE_DEFAULT)
#define ADC_EXT_TRIG_REG_CONV_SHRTIM1_TRGO3       (((uint32_t)0x0000001CU << 24U) | ADC_REG_TRIG_EXT_EDGE_DEFAULT)
#define ADC_EXT_TRIG_REG_CONV_SHRTIM2_TRGO1       (((uint32_t)0x0000001DU << 24U) | ADC_REG_TRIG_EXT_EDGE_DEFAULT)
#define ADC_EXT_TRIG_REG_CONV_SHRTIM2_TRGO3       (((uint32_t)0x0000001EU << 24U) | ADC_REG_TRIG_EXT_EDGE_DEFAULT)
#define ADC_EXT_TRIG_REG_CONV_EXT_INT0_15         (((uint32_t)0x0000001FU << 24U) | ADC_REG_TRIG_EXT_EDGE_DEFAULT)
#define ADC_EXT_TRIG_REG_CONV_SOFTWARE            (((uint32_t)0x00000000U << 24U))

/**  ADC DMA Mode **/
#define ADC_MULTI_REG_DMA_MODE_MASK               (ADC_CTRL2_DMAMD) 
#define ADC_MULTI_REG_DMA_DISABLE                 (0x00000000UL) 
#define ADC_MULTI_REG_DMA_EACH_ADC                (ADC_CTRL2_DMAMD_0) /* each ADC uses its own DMA channel, with its individual DMA transfer settings */
#define ADC_MULTI_REG_DMA_LIMIT_RES12_10B         (ADC_CTRL2_DMAMD_1) /* one DMA channel for muti ADC (DMA of ADC master). Setting for ADC resolution of 12 and 10 bits */

/**  ADC_data_align **/
#define ADC_DAT_ALIGN_MASK                        (ADC_CTRL2_ALIG)
#define ADC_DAT_ALIGN_R                           ((uint32_t)0x00000000U)
#define ADC_DAT_ALIGN_L                           (ADC_CTRL2_ALIG)

#define ADC_TS_EN_MASK                            (ADC_CTRL2_TEMPEN)   /**  ADC temper sensor  enable  **/
#define ADC_VREFINT_EN_MASK                       (ADC_CTRL3_VREFINTEN) /**  ADC vreint enable  **/
#define ADC_INJ_SWSTART_MASK                      (ADC_CTRL2_SWSTRJCH)/**  Start conversion of injected channels  **/
#define ADC_REG_SWSTART_MASK                      (ADC_CTRL2_SWSTRRCH)/**  Start conversion of regular channels  **/

/** DataTransferMode **/
#define ADC_DATA_TRANS_Mode_MASK                  (ADC_CTRL2_DMNGT | ADC_CTRL2_MDSMU )
#define ADC_REG_DR_TRANSFER                       (0x00000000U )                         /** ADC conversions are transferred to DR rigister **/
#define ADC_REG_DSMU_TRANSFER                     (ADC_CTRL2_DMNGT_1)                    /** ADC conversion data are transferred to DSMU ,using for single-ADC**/
#define ADC_REG_MUTI_DSMU_TRANSFER                (ADC_CTRL2_DMNGT_1 | ADC_CTRL2_MDSMU)  /** ADC conversion data are transferred to DSMU ,using for muti-ADC**/
#define ADC_REG_DMA_TRANSFER                      (ADC_CTRL2_DMNGT_1 | ADC_CTRL2_DMNGT_0)/** ADC conversion data are transferred by DMA  **/

/** ADC CTRL3 MASK **/
#define ADC_DATA_RES_MASK                         (ADC_CTRL3_RES)
#define ADC_DATA_RES_10BIT                        (~ADC_DATA_RES_MASK)
#define ADC_DATA_RES_12BIT                        (ADC_DATA_RES_MASK)

#define ADC_CAL_DIFF_MODE_MASK                    (ADC_CTRL3_CALDIF) /** ADC differential mode bit mask **/
#define ADC_CAL_AUTO_LOAD_MASK                    (ADC_CTRL3_CALALD) /** ADC auto calibration bit mask **/
#define ADC_CLOCK_MODE_MASK                       (ADC_CTRL3_CLOCKMOD)  /** ADC clock mode bit mask **/
#define ADC_BYPASS_CAL_MASK                       (ADC_CTRL3_BPCAL)  /** ADC bypass calibration mode bit mask **/
#define ADC_VOLT_MONITOR_EN_MASK                  (ADC_CTRL3_VBATMEN)/** ADCVbat monitor enable bit mask **/

#define ADC_GAIN_COMPENSATION_MODE_MASK           (ADC_CTRL3_GCOMPEN | ADC_CTRL3_GCOMP_SATEN) 
#define ADC_GAIN_COMPENSATION_MODE0               (ADC_CTRL3_GCOMPEN) /**  ADC gain compensation enable and the Saturation range is max 0x0-0xFFFU  **/
#define ADC_GAIN_COMPENSATION_MODE1               (ADC_CTRL3_GCOMPEN | ADC_CTRL3_GCOMP_SATEN) /**  ADC gain compensation enable and the Saturation range is max 0x0-0x3FFFU  **/

#define ADC_GAIN_COMPENSATION_VALUE_MASK          (ADC_GCOMP_GCOMPDAT)

#define ADC_INJ_SWSTOP_MASK                       (ADC_CTRL3_SWJSTOP) /**  Stop conversion of injected channels  **/
#define ADC_REG_SWSTOP_MASK                       (ADC_CTRL3_SWRSTOP) /**  Stop conversion of regular channels  **/
#define ADC_INJ_START_MASK                        (ADC_CTRL3_JSTART ) /**  Start conversion of injected channels  **/
#define ADC_REG_START_MASK                        (ADC_CTRL3_RSTART ) /**  Start conversion of regular channels  **/

#define ADC_CLOCK_MODE_PLL                        (ADC_CLOCK_MODE_MASK)
#define ADC_CLOCK_MODE_AHB                        (~ADC_CLOCK_MODE_MASK)

#define ADC_OVERSAMPE_RATE_TIMES_MASK             (ADC_OSCFG_OSR)    /**ADC oversampling ratio times bit mask **/
#define ADC_OVERSAMPE_RATE_TIMES_1                (((uint32_t)0x00000000U) << 14)   
#define ADC_OVERSAMPE_RATE_TIMES_2                (((uint32_t)0x00000001U) << 14)   
#define ADC_OVERSAMPE_RATE_TIMES_4                (((uint32_t)0x00000002U) << 14)   
#define ADC_OVERSAMPE_RATE_TIMES_8                (((uint32_t)0x00000003U) << 14)   
#define ADC_OVERSAMPE_RATE_TIMES_16               (((uint32_t)0x00000004U) << 14) 
#define ADC_OVERSAMPE_RATE_TIMES_32               (((uint32_t)0x00000005U) << 14) 
#define ADC_OVERSAMPE_RATE_TIMES_64               (((uint32_t)0x00000006U) << 14) 
#define ADC_OVERSAMPE_RATE_TIMES_128              (((uint32_t)0x00000007U) << 14) 
#define ADC_OVERSAMPE_RATE_TIMES_256              (((uint32_t)0x00000008U) << 14) 
#define ADC_OVERSAMPE_RATE_TIMES_512              (((uint32_t)0x00000009U) << 14)
#define ADC_OVERSAMPE_RATE_TIMES_1024             (((uint32_t)0x0000000AU) << 14)

#define ADC_OVERSAMPE_DATA_SHIFT_MASK             (ADC_OSCFG_OSS)    /**ADC oversampling data right shift bit mask **/
#define ADC_OVERSAMPE_DATA_SHIFT_0                (((uint32_t)0x00000000U) << 18)   
#define ADC_OVERSAMPE_DATA_SHIFT_1                (((uint32_t)0x00000001U) << 18)   
#define ADC_OVERSAMPE_DATA_SHIFT_2                (((uint32_t)0x00000002U) << 18)   
#define ADC_OVERSAMPE_DATA_SHIFT_3                (((uint32_t)0x00000003U) << 18)   
#define ADC_OVERSAMPE_DATA_SHIFT_4                (((uint32_t)0x00000004U) << 18) 
#define ADC_OVERSAMPE_DATA_SHIFT_5                (((uint32_t)0x00000005U) << 18) 
#define ADC_OVERSAMPE_DATA_SHIFT_6                (((uint32_t)0x00000006U) << 18) 
#define ADC_OVERSAMPE_DATA_SHIFT_7                (((uint32_t)0x00000007U) << 18) 
#define ADC_OVERSAMPE_DATA_SHIFT_8                (((uint32_t)0x00000008U) << 18) 
#define ADC_OVERSAMPE_DATA_SHIFT_9                (((uint32_t)0x00000009U) << 18)
#define ADC_OVERSAMPE_DATA_SHIFT_10               (((uint32_t)0x0000000AU) << 18)

#define ADC_OVERSAMPE_REG_EN_MASK                 (ADC_OSCFG_OSRE)    /**ADC oversampling on regular channels **/
#define ADC_OVERSAMPE_INJ_EN_MASK                 (ADC_OSCFG_OSJE)    /**ADC oversampling on injected channels **/
#define ADC_OVERSAMPE_TRIG_REG_MASK               (ADC_OSCFG_OSRTRIG) /**ADC oversampling trigger mode on regular channels **/
#define ADC_OVERSAMPE_MODE_MASK                   (ADC_OSCFG_OSRMD)   /**ADC oversampling mode on regular channels **/
/**Oversample scope **/
#define ADC_OVERSAMPE_DISABLE                     ((uint32_t)0x00000000U)
#define ADC_OVERSAMPE_REGULAR_CONTINUED           (ADC_OVERSAMPE_REG_EN_MASK)
#define ADC_OVERSAMPE_REGULAR_RESUMED             (ADC_OVERSAMPE_MODE_MASK | ADC_OVERSAMPE_REG_EN_MASK)
#define ADC_OVERSAMPE_INJECTED                    (ADC_OVERSAMPE_INJ_EN_MASK)
#define ADC_OVERSAMPE_REGULAR_INJECTED            (ADC_OVERSAMPE_REG_EN_MASK | ADC_OVERSAMPE_INJ_EN_MASK)

/**  ADC_sampling_time **/
#define ADC_SAMP_TIME_CYCLES_MASK                 (ADC_SAMPT1_SAMP0)
#define ADC_SAMP_TIME_CYCLES_1                    ((uint8_t)0x00U)
#define ADC_SAMP_TIME_CYCLES_2                    ((uint8_t)0x01U)
#define ADC_SAMP_TIME_CYCLES_3                    ((uint8_t)0x02U)
#define ADC_SAMP_TIME_CYCLES_4                    ((uint8_t)0x03U)
#define ADC_SAMP_TIME_CYCLES_5                    ((uint8_t)0x04U)
#define ADC_SAMP_TIME_CYCLES_6                    ((uint8_t)0x05U)
#define ADC_SAMP_TIME_CYCLES_7                    ((uint8_t)0x06U)
#define ADC_SAMP_TIME_CYCLES_10                   ((uint8_t)0x07U)
#define ADC_SAMP_TIME_CYCLES_13                   ((uint8_t)0x08U)
#define ADC_SAMP_TIME_CYCLES_17                   ((uint8_t)0x09U)
#define ADC_SAMP_TIME_CYCLES_24                   ((uint8_t)0x0AU)
#define ADC_SAMP_TIME_CYCLES_32                   ((uint8_t)0x0BU)
#define ADC_SAMP_TIME_CYCLES_83                   ((uint8_t)0x0CU)
#define ADC_SAMP_TIME_CYCLES_93                   ((uint8_t)0x0DU)
#define ADC_SAMP_TIME_CYCLES_215                  ((uint8_t)0x0EU)
#define ADC_SAMP_TIME_CYCLES_397                  ((uint8_t)0x0FU)


/**  ADC_offset_channel_offset **/
#define ADC_REGESTER_OFFSET_1                     ((uint8_t)0x24U)
#define ADC_REGESTER_OFFSET_2                     ((uint8_t)0x28U)
#define ADC_REGESTER_OFFSET_3                     ((uint8_t)0x2CU)
#define ADC_REGESTER_OFFSET_4                     ((uint8_t)0x30U)

#define ADC_OFFSET_EN_MASK                        (ADC_OFFSET1_OFFSCH1EN)
#define ADC_OFFSET_CH_MASK                        (ADC_OFFSET1_OFFSCH1CH)
#define ADC_OFFSET_SATEN_EN_MASK                  (ADC_OFFSET1_OFFSCH1SATEN)
#define ADC_OFFSET_DIR_MASK                       (ADC_OFFSET1_OFFSCH1DIR)
#define ADC_OFFSET_DATA_MASK                      (ADC_OFFSET1_OFFSCH1DAT)

/** AWDG 1 Filtering Definition **/
#define ADC_AWDG1_FILTERING_MASK                  (ADC_AWD1LOW_AWDFIL)
#define ADC_AWDG1_FILTERING_NONE                  (0x00000000U)
#define ADC_AWDG1_FILTERING_2SAMPLES              (ADC_AWD1LOW_AWDFIL_0)
#define ADC_AWDG1_FILTERING_3SAMPLES              (ADC_AWD1LOW_AWDFIL_1)
#define ADC_AWDG1_FILTERING_4SAMPLES              (ADC_AWD1LOW_AWDFIL_1 | ADC_AWD1LOW_AWDFIL_0)
#define ADC_AWDG1_FILTERING_5SAMPLES              (ADC_AWD1LOW_AWDFIL_2)
#define ADC_AWDG1_FILTERING_6SAMPLES              (ADC_AWD1LOW_AWDFIL_2 | ADC_AWD1LOW_AWDFIL_0)
#define ADC_AWDG1_FILTERING_7SAMPLES              (ADC_AWD1LOW_AWDFIL_2 | ADC_AWD1LOW_AWDFIL_1)
#define ADC_AWDG1_FILTERING_8SAMPLES              (ADC_AWD1LOW_AWDFIL_2 | ADC_AWD1LOW_AWDFIL_1 | ADC_AWD1LOW_AWDFIL_0)

/** AWDG 2/3 Enable Definition **/
#define ADC_AWDG2_EN_OFFSET                       ((uint8_t)0x4CU)
#define ADC_AWDG3_EN_OFFSET                       ((uint8_t)0x50U)
#define ADC_AWDG23_EN_MASK                        (ADC_AWD2EN_AWD2EN)
/** AWDG 2/3 Interrupt Enable Definition **/
#define ADC_AWDG2_INTEN_OFFSET                    ((uint8_t)0x54U)
#define ADC_AWDG3_INTEN_OFFSET                    ((uint8_t)0x58U)
#define ADC_AWDG23_INTEN_MASK                     (ADC_AWD2INTEN)
/** AWDG 2/3 Status Definition **/
#define ADC_AWDG2_STS_OFFSET                      ((uint8_t)0x5CU)
#define ADC_AWDG3_STS_OFFSET                      ((uint8_t)0x60U)
#define ADC_AWDG23_STATUS_MASK                    (ADC_AWD2STS)

/**  ADC regular sequence **/
#define ADC_RESQ_SEQ_MASK                         (ADC_RSEQ4_SEQ1)


/**  ADC inject sequence **/
#define ADC_JESQ_LEN_MASK                         (ADC_JSEQ_JLEN)
#define ADC_JESQ_SEQ_MASK                         (ADC_JSEQ_JSEQ1)


#define ADC_INJECT_DATA_OFFSET_1                  ((uint8_t)0x78U)
#define ADC_INJECT_DATA_OFFSET_2                  ((uint8_t)0x7CU)
#define ADC_INJECT_DATA_OFFSET_3                  ((uint8_t)0x80U)
#define ADC_INJECT_DATA_OFFSET_4                  ((uint8_t)0x84U)



/**  ADC_flags_definition **/
#define ADC_FLAG_ALL_MASK                         (ADC_STS_ALL)
#define ADC_FLAG_ENDC                             (ADC_STS_ENDC)
#define ADC_FLAG_EOC_ANY                          (ADC_STS_ENDCA)
#define ADC_FLAG_JSTR                             (ADC_STS_JSTR)
#define ADC_FLAG_JENDC                            (ADC_STS_JENDC)
#define ADC_FLAG_JEOC_ANY                         (ADC_STS_JENDCA)
#define ADC_FLAG_STR                              (ADC_STS_STR)
#define ADC_FLAG_AWDG1                            (ADC_STS_AWDG1)
#define ADC_FLAG_RDY                              (ADC_STS_RDY)
#define ADC_FLAG_PDRDY                            (ADC_STS_PDRDY)
#define ADC_FLAG_EOSAMP                           (ADC_STS_EOSAMP)
#define ADC_FLAG_ROSOVF                           (ADC_STS_ROSOVF)
#define ADC_FLAG_JOSOVF                           (ADC_STS_JOSOVF)
#define ADC_FLAG_ROSOVFDSMU                       (ADC_STS_ROSOVFDSMU)
#define ADC_FLAG_REFLAG                           (ADC_STS_REFLAG)
#define ADC_FLAG_WEFLAG                           (ADC_STS_WEFLAG)


/**  ADC_FIFO_flags_definition **/
#define ADC_FIFO_FLAG_FULL                        ((uint16_t)ADC_FIFOSTS_FFLAG)
#define ADC_FIFO_FLAG_EMPTY                       ((uint16_t)ADC_FIFOSTS_EFLAG)
#define ADC_FIFO_FLAG_HALF_FULL                   ((uint16_t)ADC_FIFOSTS_HFFLAG)
#define ADC_FIFO_FLAG_NOT_EMPTY                   ((uint16_t)ADC_FIFOSTS_NEFLAG)

/**  ADC_FIFO_Invailed_Data_definition **/
#define ADC_FIFO_INVALIED_DATA_COUNT_MASK         (ADC_FIFOSTS_DATCNT)

/**  ADC_FIFO_CFG_definition **/
#define ADC_FIFO_EN_MASK                          (ADC_FIFOCFG_EN)
#define ADC_FIFO_CLR_MASK                         (ADC_FIFOCFG_CLR)
#define ADC_FIFO_WATER_LEVEL_MASK                 (ADC_FIFOCFG_WL)

/**  ADC_FIFO_INTEN_definition **/
#define ADC_FIFO_INT_FULL                         ((uint16_t)ADC_FIFOCFG_FINTEN)
#define ADC_FIFO_INT_EMPTY                        ((uint16_t)ADC_FIFOCFG_EINTEN)
#define ADC_FIFO_INT_HALF_FULL                    ((uint16_t)ADC_FIFOCFG_HFINTEN)
#define ADC_FIFO_INT_NOT_EMPTY                    ((uint16_t)ADC_FIFOCFG_NEINTEN)


/**  ADC_interrupts_definition **/
#define ADC_INT_CONTROL_MASK                      (0x7C00003FU)    /*bit8 - bit25 insert ADC_STS Flag*/
#define ADC_INT_WRITEERR                          (ADC_CTRL1_WEIEN     | ((uint32_t)ADC_FLAG_WEFLAG   <<8U) )     
#define ADC_INT_READERR                           (ADC_CTRL1_REIEN     | ((uint32_t)ADC_FLAG_REFLAG   <<8U) )
#define ADC_INT_EOSAMP                            (ADC_CTRL1_EOSMPIEN  | ((uint32_t)ADC_FLAG_EOSAMP   <<8U) )
#define ADC_INT_PDRDY                             (ADC_CTRL1_PDRDYIEN  | ((uint32_t)ADC_FLAG_PDRDY    <<8U) )
#define ADC_INT_RDY                               (ADC_CTRL1_RDYIEN    | ((uint32_t)ADC_FLAG_RDY      <<8U) )
#define ADC_INT_AWD1                              (ADC_CTRL1_AWD1IEN   | ((uint32_t)ADC_FLAG_AWDG1    <<8U) )
#define ADC_INT_JENDC                             (ADC_CTRL1_JENDCIEN  | ((uint32_t)ADC_FLAG_JENDC    <<8U) )
#define ADC_INT_JENDCA                            (ADC_CTRL1_JENDCAIEN | ((uint32_t)ADC_FLAG_JEOC_ANY <<8U) )
#define ADC_INT_ENDC                              (ADC_CTRL1_ENDCIEN   | ((uint32_t)ADC_FLAG_ENDC     <<8U) )
#define ADC_INT_ENDCA                             (ADC_CTRL1_ENDCAIEN  | ((uint32_t)ADC_FLAG_EOC_ANY  <<8U) )

// /**  ADC1_channels_definition **/
#define ADC1_Channel_00_PA0_C                     (ADC_CH_0)
#define ADC1_Channel_01_PA1_C                     (ADC_CH_1)
#define ADC1_Channel_02_PF11                      (ADC_CH_2)
#define ADC1_Channel_03_PA6                       (ADC_CH_3)
#define ADC1_Channel_04_PC4                       (ADC_CH_4)
#define ADC1_Channel_05_PB1                       (ADC_CH_5)
#define ADC1_Channel_06_PF12                      (ADC_CH_6)
#define ADC1_Channel_07_PA7                       (ADC_CH_7)
#define ADC1_Channel_08_PC5                       (ADC_CH_8)
#define ADC1_Channel_09_PB0                       (ADC_CH_9)
#define ADC1_Channel_10_PC0                       (ADC_CH_10)
#define ADC1_Channel_11_PC1                       (ADC_CH_11)
#define ADC1_Channel_12_PC2                       (ADC_CH_12)
#define ADC1_Channel_13_PC3                       (ADC_CH_13)
#define ADC1_Channel_14_PA2                       (ADC_CH_14)
#define ADC1_Channel_15_PA3                       (ADC_CH_15)
#define ADC1_Channel_16_PA0                       (ADC_CH_16)
#define ADC1_Channel_17_PA1                       (ADC_CH_17)
#define ADC1_Channel_18_PA4                       (ADC_CH_18)
#define ADC1_Channel_19_PA5                       (ADC_CH_19)

// /**  ADC2_channels_definition **/
#define ADC2_Channel_00_PA0_C_PC2_C               (ADC_CH_0)   //this channel can be optionally conected to PA0_C or PC2_C;
#define ADC2_Channel_01_PA1_C_PC3_C               (ADC_CH_1)   //this channel can be optionally conected to PA1_C or PC3_C;
#define ADC2_Channel_02_PF13                      (ADC_CH_2)
#define ADC2_Channel_03_PA6                       (ADC_CH_3)
#define ADC2_Channel_04_PC4                       (ADC_CH_4)
#define ADC2_Channel_05_PB1                       (ADC_CH_5)
#define ADC2_Channel_06_PF14                      (ADC_CH_6)
#define ADC2_Channel_07_PA7                       (ADC_CH_7)
#define ADC2_Channel_08_PC5                       (ADC_CH_8)
#define ADC2_Channel_09_PB0                       (ADC_CH_9)
#define ADC2_Channel_10_PC0                       (ADC_CH_10)
#define ADC2_Channel_11_PC1                       (ADC_CH_11)
#define ADC2_Channel_12_PC2                       (ADC_CH_12)
#define ADC2_Channel_13_PC3                       (ADC_CH_13)
#define ADC2_Channel_14_PA2                       (ADC_CH_14)
#define ADC2_Channel_15_PA3                       (ADC_CH_15)
#define ADC2_Channel_16_DAC135                    (ADC_CH_16)
#define ADC2_Channel_17_DAC246                    (ADC_CH_17)
#define ADC2_Channel_18_PA4                       (ADC_CH_18)
#define ADC2_Channel_19_PA5                       (ADC_CH_19)

// /**  ADC3_channels_definition **/
#define ADC3_Channel_00_PC2_C                     (ADC_CH_0)
#define ADC3_Channel_01_PC3_C                     (ADC_CH_1)
#define ADC3_Channel_02_PF9                       (ADC_CH_2)
#define ADC3_Channel_03_PF7                       (ADC_CH_3)
#define ADC3_Channel_04_PF5                       (ADC_CH_4)
#define ADC3_Channel_05_PF3                       (ADC_CH_5)
#define ADC3_Channel_06_PF10                      (ADC_CH_6)
#define ADC3_Channel_07_PF8                       (ADC_CH_7)
#define ADC3_Channel_08_PF6                       (ADC_CH_8)
#define ADC3_Channel_09_PF4                       (ADC_CH_9)
#define ADC3_Channel_10_PC0                       (ADC_CH_10)
#define ADC3_Channel_11_PC1                       (ADC_CH_11)
#define ADC3_Channel_12_PC2                       (ADC_CH_12)
#define ADC3_Channel_13_PH2                       (ADC_CH_13)
#define ADC3_Channel_14_PH3                       (ADC_CH_14)
#define ADC3_Channel_15_PH4                       (ADC_CH_15)
#define ADC3_Channel_16_PH5                       (ADC_CH_16)
#define ADC3_Channel_17_Battery_DIV4              (ADC_CH_17)
#define ADC3_Channel_18_Temperture_Sensor         (ADC_CH_18)
#define ADC3_Channel_19_VREFINT                   (ADC_CH_19)

/**  ADC_differential_selection_channnels_definition **/
#define ADC_DIFSEL_CHS_MASK                       (ADC_DIFSEL_DIFSEL)
#define ADC_DIFSEL_CHS_1                          (ADC_DIFSEL_DIFSEL_CH1)
#define ADC_DIFSEL_CHS_2                          (ADC_DIFSEL_DIFSEL_CH2)
#define ADC_DIFSEL_CHS_3                          (ADC_DIFSEL_DIFSEL_CH3)
#define ADC_DIFSEL_CHS_4                          (ADC_DIFSEL_DIFSEL_CH4)
#define ADC_DIFSEL_CHS_5                          (ADC_DIFSEL_DIFSEL_CH5)
#define ADC_DIFSEL_CHS_6                          (ADC_DIFSEL_DIFSEL_CH6)
#define ADC_DIFSEL_CHS_7                          (ADC_DIFSEL_DIFSEL_CH7)
#define ADC_DIFSEL_CHS_8                          (ADC_DIFSEL_DIFSEL_CH8)
#define ADC_DIFSEL_CHS_9                          (ADC_DIFSEL_DIFSEL_CH9)
#define ADC_DIFSEL_CHS_10                         (ADC_DIFSEL_DIFSEL_CH10)
#define ADC_DIFSEL_CHS_11                         (ADC_DIFSEL_DIFSEL_CH11)
#define ADC_DIFSEL_CHS_12                         (ADC_DIFSEL_DIFSEL_CH12)
#define ADC_DIFSEL_CHS_13                         (ADC_DIFSEL_DIFSEL_CH13)
#define ADC_DIFSEL_CHS_14                         (ADC_DIFSEL_DIFSEL_CH14)
#define ADC_DIFSEL_CHS_15                         (ADC_DIFSEL_DIFSEL_CH15)
#define ADC_DIFSEL_CHS_16                         (ADC_DIFSEL_DIFSEL_CH16)
#define ADC_DIFSEL_CHS_17                         (ADC_DIFSEL_DIFSEL_CH17)
#define ADC_DIFSEL_CHS_18                         (ADC_DIFSEL_DIFSEL_CH18)
#define ADC_DIFSEL_CHS_19                         (ADC_DIFSEL_DIFSEL_CH19)


/**  ADC_channel_mode_definition **/
#define ADC_SINGLE_ENDED                          ((uint32_t)0x00LU)     /**  signal-ended mode **/
#define ADC_DIFFERENTIAL_ENDED                    ((uint32_t)0x01LU)     /**  differential mode **/

/**  ADC_Write/Read_Internal_Register_definition **/

#define ADC_WRITE_READ_TIMEOUT_CYCLE              ((uint32_t)0xFFLU) 

#define ADC_WRITE_REG_MASK                        (ADC_INTLRCFG_WEN | ADC_INTLRCFG_ADDR | ADC_INTLRCFG_WDATA | ADC_INTLRCFG_RWSTART) 
#define ADC_WRITE_READ_START                      (ADC_INTLRCFG_RWSTART) 
#define ADC_WRITE_READ_RDY                        (ADC_INTLRCFG_DONE) 
#define ADC_READ_REG_MASK                         (ADC_INTLRCFG_WEN | ADC_INTLRCFG_ADDR | ADC_INTLRCFG_RWSTART) 
#define ADC_RDATA_MASK                            (ADC_INTLRCFG_RDATA)

#define ADC_CALIBRATION_ADDR                      ((uint8_t)0x05U)
#define ADC_CALIBRATION_RDY                       ((uint8_t)0x40U)
#define ADC_CALIBRATION_RDY                       ((uint8_t)0x40U)
/**  ADC_Gain_Compensation_definition **/
#define ADC_GAIN_COMPENSATION_EN_MASK             (ADC_GCOMP_GCOMPDAT)  



/** ADC_Exported_Functions **/

void ADC_DeInit(ADC_Module* ADCx);
void ADC_Init(ADC_Module* ADCx, ADC_InitType* ADC_InitStruct);
void ADC_InitStruct(ADC_InitType* ADC_InitStruct);
void ADC_Enable(ADC_Module* ADCx, FunctionalState Cmd);
void ADC_SetDMATransferMode(ADC_Module *ADCx, uint32_t DMAMode);
void ADC_CalibrationOperation(ADC_Module* ADCx);
void ADC_CalibrationReset(ADC_Module* ADCx);
FlagStatus ADC_GetCalibrationStatus(ADC_Module* ADCx);

void ADC_EnableSoftwareStartConv(ADC_Module* ADCx, FunctionalState Cmd);
FlagStatus ADC_GetSoftwareStartConvStatus(ADC_Module* ADCx);
void ADC_EnableSoftwareStartInjectedConv(ADC_Module* ADCx, FunctionalState Cmd);
FlagStatus ADC_GetSoftwareStartInjectedConvCmdStatus(ADC_Module* ADCx);
FlagStatus ADC_GetGainCompensationCmdStatus(ADC_Module* ADCx);
void ADC_EnableTempSensor(FunctionalState Cmd);
void ADC_EnableVrefint(FunctionalState Cmd);
void ADC_StopRegularConv(ADC_Module* ADCx);
void ADC_StopInjectedConv(ADC_Module* ADCx);
void ADC_StartInjectedConv(ADC_Module *ADCx);
void ADC_StartRegularConv(ADC_Module *ADCx);
void ADC_SetRegularDataTransferMode(ADC_Module *ADCx, uint32_t DataTransferMode);
void ADC_EnableMutiAdcDSMU(ADC_Module *ADCx, FunctionalState Cmd);

void ADC_SetRegularTriggerEdge(ADC_Module* ADCx, uint32_t ExternalRegularTriggerEdge);
void ADC_SetInjectTriggerEdge(ADC_Module* ADCx, uint32_t ExternalInjectTriggerEdge);

void ADC_SetIndenpentSamplingDelay(ADC_Module* ADCx, uint32_t IndenpentSamplingDelay);
void ADC_SetMultiTwoSamplingDelay(ADC_Module* ADCx, uint32_t MultiTwoSamplingDelay);

void ADC_ConfigDiscModeChannelCount(ADC_Module* ADCx, uint8_t Number);
void ADC_EnableDiscMode(ADC_Module* ADCx, FunctionalState Cmd);
void ADC_ConfigRegularChannel(ADC_Module* ADCx, uint8_t ADC_Channel, uint8_t Rank, uint8_t ADC_SampleTime);
uint16_t ADC_GetDat(ADC_Module* ADCx);
uint32_t ADC_GetMutiModeConversionDat(ADC_Module* ADCx);   
void ADC_EnableAutoInjectedConv(ADC_Module* ADCx, FunctionalState Cmd);
void ADC_EnableInjectedDiscMode(ADC_Module* ADCx, FunctionalState Cmd);
void ADC_ConfigExternalTrigInjectedConv(ADC_Module* ADCx, uint32_t ADC_ExternalTrigInjecConv);
void ADC_ConfigExternalTrigRegularConv(ADC_Module* ADCx, uint32_t ADC_ExternalTrigRegularConv);

void ADC_ConfigInjectedChannel(ADC_Module* ADCx, uint8_t ADC_Channel, uint8_t Rank, uint8_t ADC_SampleTime);
void ADC_ConfigInjectedSequencerLength(ADC_Module* ADCx, uint8_t Length);
uint16_t ADC_GetInjectedConversionDat(ADC_Module* ADCx, uint8_t ADC_InjectedChannel);
void ADC_ConfigAnalogWatchdog1WorkChannelType(ADC_Module* ADCx, uint32_t ADC_AnalogWatchdog);
void ADC_SetAWDG1FilteringConfig(ADC_Module *ADCx,  uint32_t FilteringCount);
void ADC_ConfigAnalogWatchdogThresholds(ADC_Module* ADCx, ADC_AWDG Awdg, uint16_t HighThreshold, uint16_t LowThreshold);
void ADC_ConfigAnalogWatchdog1SingleChannel(ADC_Module* ADCx, uint8_t ADC_Channel);
void ADC_SetAnalogWatchdog23MonitChannels(ADC_Module* ADCx, uint8_t AWDG_RegEnOffset, uint32_t AWDG_ChannelGroup);
uint32_t ADC_GetAnalogWatchdog23MonitChannels(ADC_Module* ADCx, uint8_t AWDG_RegEnOffset);
void ADC_SetAnalogWatchdog23IntConfig(ADC_Module* ADCx, uint8_t AWDG_RegIntEnOffset, uint32_t AWDG_ChannelEn);
uint32_t ADC_GetAnalogWatchdog23IntConfig(ADC_Module* ADCx, uint8_t AWDG_RegEnOffset);
uint32_t ADC_GetAnalogWatchdog23StatusFlag(ADC_Module* ADCx, uint8_t AWDG_RegSTSOffset);
void ADC_ClearAnalogWatchdog23StatusFlag(ADC_Module* ADCx, uint8_t AWDG_RegSTSOffset, uint32_t AWDG_ChannelFlag);
void ADC_EnableAnalogWatchdogEventToTIM(ADC_Module* ADCx, ADC_AWDG Awdg, FunctionalState Cmd);

FlagStatus ADC_GetFlagStatus(ADC_Module* ADCx, uint32_t ADC_FLAG);
void ADC_ClearFlag(ADC_Module* ADCx, uint32_t ADC_FLAG);
void ADC_ConfigInt(ADC_Module* ADCx, uint32_t ADC_IT, FunctionalState Cmd);
INTStatus ADC_GetIntStatus(ADC_Module* ADCx, uint32_t ADC_IT);
void ADC_ClearIntPendingBit(ADC_Module* ADCx, uint32_t ADC_IT);

void ADC_SetChannelSingleDiff(ADC_Module* ADCx, uint32_t Channel, uint32_t SingleDiff);

void ADC_SetConvResultBitNum(ADC_Module* ADCx, uint32_t ResultBitNum);
void ADC_SelectClockMode(ADC_Module* ADCx, uint32_t ClockMode);
void ADC_SetBypassCalibration(ADC_Module* ADCx, FunctionalState Cmd);
void ADC_EnableBatteryVoltageMonitor(FunctionalState Cmd);

/*functions related to oversampling */
void ADC_ConfigOverSamplingRatioAndShift(ADC_Module *ADCx, uint32_t Ratio, uint32_t Shift);
void ADC_SetOverSamplingScope(ADC_Module *ADCx, uint32_t OversampleScope);
void ADC_EnableOverSamplingDiscont(ADC_Module *ADCx, FunctionalState Cmd);
void ADC_SetOffsetConfig(ADC_Module* ADCx, uint8_t ADC_Offset, ADC_OffsetType* ADC_OffsetStruct);
void ADC_GetOffsetConfig(ADC_Module* ADCx, uint8_t ADC_Offset, ADC_OffsetType* ADC_OffsetStruct);
void ADC_SetGainCompensation(ADC_Module *ADCx, uint32_t GainCompensationMode, uint32_t GainCompensationValue);

/*functions related to FIFO operations*/
void ADC_ClearFIFO(ADC_Module* ADCx);
void ADC_EnableFIFO(ADC_Module* ADCx, FunctionalState Cmd);
uint8_t ADC_GetFIFOInvalidedDataCount(ADC_Module* ADCx);
FlagStatus ADC_GetFIFOFlagStatus(ADC_Module* ADCx, uint16_t ADC_FIFOFLAG);
void ADC_ClearFIFOFlag(ADC_Module* ADCx, uint16_t ADC_FIFO_FLAG);
void ADC_ConfigFIFOWaterLevel(ADC_Module* ADCx, uint32_t FIFO_Level);
void ADC_ConfigFIFOInt(ADC_Module* ADCx, uint16_t ADC_FIFO_IT, FunctionalState Cmd);
void ADC_ClearFIFOIntPendingBit(ADC_Module* ADCx, uint16_t ADC_FIFO_IT);

//ErrorStatus ADC_ReadDataFromInternalReg(ADC_Module* ADCx, uint8_t Addr, uint16_t *ReadOutData);
//ErrorStatus ADC_WriteDataIntoInternalReg(ADC_Module* ADCx, uint8_t Addr, uint8_t Data);

void ADC_ConfigClk(ADC_Module* ADCx, ADC_CTRL3_CKMOD ADC_ClkMode, uint32_t Pll_CLK_source, uint32_t RCC_ADCPrescaler);

#ifdef __cplusplus
}
#endif

#endif /*__N32H76X_78X_ADC_H__ */

