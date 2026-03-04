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
 * @file n32h76x_78x_dac.h
 * @author Nations
 * @version v1.0.0
 *
 * @copyright Copyright (c) 2025, Nations Technologies Inc. All rights reserved.
 */#ifndef __N32H76X_78X_DAC_H__
#define __N32H76X_78X_DAC_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "n32h76x_78x.h"

/** DAC_Exported_Types **/

typedef enum
{
    DAC1 = 0,
    DAC2 = 1,
    DAC3 = 2,
    DAC4 = 3,
    DAC5 = 4,
    DAC6 = 5
} DACX;

typedef struct
{
  uint32_t DAC_Trigger;                

  uint32_t DAC_Trigger2;  

  uint32_t DAC_WaveGeneration; 

  uint32_t DAC_LFSRUnmask_TriangleAmplitude; 

  FunctionalState DAC_OutputBuffer;             /* Enable or disable the DAC output buffer  */

  FunctionalState DAC_TriggerEnable;            /* Enable or disable the DAC external trigger  ,when it is disable, it means Conversion is automatic once the DACx(y)_Dxxx register                                 \
                                                   has been loaded, and not by external trigger */

  FunctionalState DAC_ConnectOnChipPeripheral ; /* Secifies whether the DAC output is connected or not to on chip peripheral */

  FunctionalState DAC_ConnectExternalPin ;      /* Secifies whether the DAC output is connected or not to external pin */

  FunctionalState DAC_DMADoubleDataMode;        /* Enable or disable DMA double data mode  */

  FunctionalState DAC_SignedFormat;             /* Enable or disable signed format mode */

}DAC_InitType;


/** DAC_Exported_Constants **/

/** DAC_trigger **/
#define DAC_Trigger_Software               ((uint32_t)0x00000000U << 11)
#define DAC_Trigger_ATIM1_TRGO             ((uint32_t)0x00000001U << 11)
#define DAC_Trigger_ATIM2_TRGO             ((uint32_t)0x00000002U << 11)
#define DAC_Trigger_ATIM3_TRGO             ((uint32_t)0x00000003U << 11)
#define DAC_Trigger_ATIM4_TRGO             ((uint32_t)0x00000004U << 11)
#define DAC_Trigger_GTIMA1_TRGO            ((uint32_t)0x00000005U << 11)
#define DAC_Trigger_GTIMA2_TRGO            ((uint32_t)0x00000006U << 11)
#define DAC_Trigger_GTIMA3_TRGO            ((uint32_t)0x00000007U << 11)
#define DAC_Trigger_GTIMA4_TRGO            ((uint32_t)0x00000008U << 11)
#define DAC_Trigger_GTIMA5_TRGO            ((uint32_t)0x00000009U << 11)
#define DAC_Trigger_GTIMA6_TRGO            ((uint32_t)0x0000000AU << 11)
#define DAC_Trigger_GTIMA7_TRGO            ((uint32_t)0x0000000BU << 11)
#define DAC_Trigger_GTIMB1_TRGO            ((uint32_t)0x0000000CU << 11)
#define DAC_Trigger_GTIMB2_TRGO            ((uint32_t)0x0000000DU << 11)
#define DAC_Trigger_GTIMB3_TRGO            ((uint32_t)0x0000000EU << 11)
#define DAC_Trigger_EXTI5                  ((uint32_t)0x0000000FU << 11)
#define DAC_Trigger_EXTI7                  ((uint32_t)0x00000010U << 11)
#define DAC_Trigger_EXTI9                  ((uint32_t)0x00000011U << 11)
#define DAC_Trigger_SHRTIM1_RST_TRG1       ((uint32_t)0x00000012U << 11)
#define DAC_Trigger_SHRTIM1_RST_TRG2       ((uint32_t)0x00000013U << 11)
#define DAC_Trigger_SHRTIM1_RST_TRG3       ((uint32_t)0x00000014U << 11)
#define DAC_Trigger_SHRTIM1_RST_TRG4       ((uint32_t)0x00000015U << 11)
#define DAC_Trigger_SHRTIM1_RST_TRG5       ((uint32_t)0x00000016U << 11)
#define DAC_Trigger_SHRTIM1_RST_TRG6       ((uint32_t)0x00000017U << 11)
#define DAC_Trigger_SHRTIM1_RST_TRGO123    ((uint32_t)0x00000018U << 11)
#define DAC_Trigger_SHRTIM2_RST_TRG1       ((uint32_t)0x00000019U << 11)
#define DAC_Trigger_SHRTIM2_RST_TRG2       ((uint32_t)0x0000001AU << 11)
#define DAC_Trigger_SHRTIM2_RST_TRG3       ((uint32_t)0x0000001BU << 11)
#define DAC_Trigger_SHRTIM2_RST_TRG4       ((uint32_t)0x0000001CU << 11)
#define DAC_Trigger_SHRTIM2_RST_TRG5       ((uint32_t)0x0000001DU << 11)
#define DAC_Trigger_SHRTIM2_RST_TRG6       ((uint32_t)0x0000001EU << 11)
#define DAC_Trigger_SHRTIM2_RST_TRGO123    ((uint32_t)0x0000001FU << 11)

/** DAC_step_trigger **/
#define DAC_Trigger2_Software               ((uint32_t)0x00000000U << 1)
#define DAC_Trigger2_ATIM1_TRGO             ((uint32_t)0x00000001U << 1)
#define DAC_Trigger2_ATIM2_TRGO             ((uint32_t)0x00000002U << 1)
#define DAC_Trigger2_ATIM3_TRGO             ((uint32_t)0x00000003U << 1)
#define DAC_Trigger2_ATIM4_TRGO             ((uint32_t)0x00000004U << 1)
#define DAC_Trigger2_GTIMA1_TRGO            ((uint32_t)0x00000005U << 1)
#define DAC_Trigger2_GTIMA2_TRGO            ((uint32_t)0x00000006U << 1)
#define DAC_Trigger2_GTIMA3_TRGO            ((uint32_t)0x00000007U << 1)
#define DAC_Trigger2_GTIMA4_TRGO            ((uint32_t)0x00000008U << 1)
#define DAC_Trigger2_GTIMA5_TRGO            ((uint32_t)0x00000009U << 1)
#define DAC_Trigger2_GTIMA6_TRGO            ((uint32_t)0x0000000AU << 1)
#define DAC_Trigger2_GTIMA7_TRGO            ((uint32_t)0x0000000BU << 1)
#define DAC_Trigger2_GTIMB1_TRGO            ((uint32_t)0x0000000CU << 1)
#define DAC_Trigger2_GTIMB2_TRGO            ((uint32_t)0x0000000DU << 1)
#define DAC_Trigger2_GTIMB3_TRGO            ((uint32_t)0x0000000EU << 1)
#define DAC_Trigger2_EXTI6                  ((uint32_t)0x0000000FU << 1)
#define DAC_Trigger2_EXTI8                  ((uint32_t)0x00000010U << 1)
#define DAC_Trigger2_EXTI10                 ((uint32_t)0x00000011U << 1)
#define DAC_Trigger2_SHRTIM1_STEP_TRG1      ((uint32_t)0x00000012U << 1)
#define DAC_Trigger2_SHRTIM1_STEP_TRG2      ((uint32_t)0x00000013U << 1)
#define DAC_Trigger2_SHRTIM1_STEP_TRG3      ((uint32_t)0x00000014U << 1)
#define DAC_Trigger2_SHRTIM1_STEP_TRG4      ((uint32_t)0x00000015U << 1)
#define DAC_Trigger2_SHRTIM1_STEP_TRG5      ((uint32_t)0x00000016U << 1)
#define DAC_Trigger2_SHRTIM1_STEP_TRG6      ((uint32_t)0x00000017U << 1)
#define DAC_Trigger2_SHRTIM2_STEP_TRG1      ((uint32_t)0x00000019U << 1)
#define DAC_Trigger2_SHRTIM2_STEP_TRG2      ((uint32_t)0x0000001AU << 1)
#define DAC_Trigger2_SHRTIM2_STEP_TRG3      ((uint32_t)0x0000001BU << 1)
#define DAC_Trigger2_SHRTIM2_STEP_TRG4      ((uint32_t)0x0000001CU << 1)
#define DAC_Trigger2_SHRTIM2_STEP_TRG5      ((uint32_t)0x0000001DU << 1)
#define DAC_Trigger2_SHRTIM2_STEP_TRG6      ((uint32_t)0x0000001EU << 1)


/** DAC_wave_generation **/
#define DAC_WaveGeneration_None            ((uint32_t)0x00000000U)
#define DAC_WaveGeneration_Noise           ((uint32_t)DAC_CTRL_WxEN_0)
#define DAC_WaveGeneration_Triangle        ((uint32_t)DAC_CTRL_WxEN_1)
#define DAC_WaveGeneration_SAWTOOTH_INC    ((uint32_t)DAC_CTRL_WxEN_2)
#define DAC_WaveGeneration_SAWTOOTH_DEC    ((uint32_t)DAC_CTRL_WxEN_2 | DAC_CTRL_WxEN_1)

/** DAC_lfsrunmask_triangleamplitude **/
#define DAC_LFSRUnmask_Bit0                ((uint32_t)0x00000000U << 6) /*  Unmask DAC channel LFSR bit0 for noise wave generation */
#define DAC_LFSRUnmask_Bits1_0             ((uint32_t)0x00000001U << 6) /*  Unmask DAC channel LFSR bit[1:0] for noise wave generation */
#define DAC_LFSRUnmask_Bits2_0             ((uint32_t)0x00000002U << 6) /*  Unmask DAC channel LFSR bit[2:0] for noise wave generation */
#define DAC_LFSRUnmask_Bits3_0             ((uint32_t)0x00000003U << 6) /*  Unmask DAC channel LFSR bit[3:0] for noise wave generation */
#define DAC_LFSRUnmask_Bits4_0             ((uint32_t)0x00000004U << 6) /*  Unmask DAC channel LFSR bit[4:0] for noise wave generation */
#define DAC_LFSRUnmask_Bits5_0             ((uint32_t)0x00000005U << 6) /*  Unmask DAC channel LFSR bit[5:0] for noise wave generation */
#define DAC_LFSRUnmask_Bits6_0             ((uint32_t)0x00000006U << 6) /*  Unmask DAC channel LFSR bit[6:0] for noise wave generation */
#define DAC_LFSRUnmask_Bits7_0             ((uint32_t)0x00000007U << 6) /*  Unmask DAC channel LFSR bit[7:0] for noise wave generation */
#define DAC_LFSRUnmask_Bits8_0             ((uint32_t)0x00000008U << 6) /*  Unmask DAC channel LFSR bit[8:0] for noise wave generation */
#define DAC_LFSRUnmask_Bits9_0             ((uint32_t)0x00000009U << 6) /*  Unmask DAC channel LFSR bit[9:0] for noise wave generation */
#define DAC_LFSRUnmask_Bits10_0            ((uint32_t)0x0000000AU << 6) /*  Unmask DAC channel LFSR bit[10:0] for noise wave generation */
#define DAC_LFSRUnmask_Bits11_0            ((uint32_t)0x0000000BU << 6) /*  Unmask DAC channel LFSR bit[11:0] for noise wave generation */
#define DAC_TriangleAmplitude_1            ((uint32_t)0x00000000U << 6) /*  Select max triangle amplitude of 1 */
#define DAC_TriangleAmplitude_3            ((uint32_t)0x00000001U << 6) /*  Select max triangle amplitude of 3 */
#define DAC_TriangleAmplitude_7            ((uint32_t)0x00000002U << 6) /*  Select max triangle amplitude of 7 */
#define DAC_TriangleAmplitude_15           ((uint32_t)0x00000003U << 6) /*  Select max triangle amplitude of 15 */
#define DAC_TriangleAmplitude_31           ((uint32_t)0x00000004U << 6) /*  Select max triangle amplitude of 31 */
#define DAC_TriangleAmplitude_63           ((uint32_t)0x00000005U << 6) /*  Select max triangle amplitude of 63 */ 
#define DAC_TriangleAmplitude_127          ((uint32_t)0x00000006U << 6) /*  Select max triangle amplitude of 127 */  
#define DAC_TriangleAmplitude_255          ((uint32_t)0x00000007U << 6) /*  Select max triangle amplitude of 255 */		
#define DAC_TriangleAmplitude_511          ((uint32_t)0x00000008U << 6) /*  Select max triangle amplitude of 511 */  
#define DAC_TriangleAmplitude_1023         ((uint32_t)0x00000009U << 6) /*  Select max triangle amplitude of 1023 */
#define DAC_TriangleAmplitude_2047         ((uint32_t)0x0000000AU << 6) /*  Select max triangle amplitude of 2047 */
#define DAC_TriangleAmplitude_4095         ((uint32_t)0x0000000BU << 6) /*  Select max triangle amplitude of 4095 */ 


/** DAC_CTRL **/
#define DACy_CTRL_TRIG_OVERLOCKIEN_EN_MASK  ((uint32_t)DAC_CTRL_TROVCyIEN)
#define DACy_CTRL_OUTPUT_TO_EXTPIN_EN_MASK  ((uint32_t)DAC_CTRL_EXOUTy)
#define DACy_CTRL_OUTPUT_TO_ONCHAIP_EN_MASK ((uint32_t)DAC_CTRL_INOUTy)
#define DACy_CTRL_CALIBATE_EN_MASK          ((uint32_t)DAC_CTRL_CALyEN)
#define DACy_CTRL_WAVE_TYPE_MASK            ((uint32_t)DAC_CTRL_WyEN)
#define DACy_CTRL_SINGFORMAT_EN_MASK        ((uint32_t)DAC_CTRL_SINFORMATyEN)
#define DACy_CTRL_DMADOUBLEMODE_EN_MASK     ((uint32_t)DAC_CTRL_DMADOUBLEyEN)
#define DACy_CTRL_HIGH_DRIVER_EN_MASK       ((uint32_t)DAC_CTRL_HDByEN)
#define DACy_CTRL_DMA_UDRIEN_EN_MASK        ((uint32_t)DAC_CTRL_DMAUDRyIEn)
#define DACy_CTRL_TRIGGER_EN_MASK           ((uint32_t)DAC_CTRL_TyEN)
#define DACy_CTRL_BUFF_EN_MASK              ((uint32_t)DAC_CTRL_ByEN)
#define DACy_CTRL_DMA_EN_MASK               ((uint32_t)DAC_CTRL_DMAyEN)
#define DACy_CTRL_EN_MASK                   ((uint32_t)DAC_CTRL_DACyEN)

#define DACx_CTRL_TRIG_OVERLOCKIEN_EN_MASK  ((uint32_t)DAC_CTRL_TROVCxIEN)
#define DACx_CTRL_OUTPUT_TO_EXTPIN_EN_MASK  ((uint32_t)DAC_CTRL_EXOUTx)
#define DACx_CTRL_OUTPUT_TO_ONCHAIP_EN_MASK ((uint32_t)DAC_CTRL_INOUTx)
#define DACx_CTRL_CALIBATE_EN_MASK          ((uint32_t)DAC_CTRL_CALxEN)
#define DACx_CTRL_WAVE_TYPE_MASK            ((uint32_t)DAC_CTRL_WxEN)
#define DACx_CTRL_SINGFORMAT_EN_MASK        ((uint32_t)DAC_CTRL_SINFORMATxEN)
#define DACx_CTRL_DMADOUBLEMODE_EN_MASK     ((uint32_t)DAC_CTRL_DMADOUBLExEN)
#define DACx_CTRL_HIGH_DRIVER_EN_MASK       ((uint32_t)DAC_CTRL_HDBxEN)
#define DACx_CTRL_DMA_UDRIEN_EN_MASK        ((uint32_t)DAC_CTRL_DMAUDRxIEn)
#define DACx_CTRL_TRIGGER_EN_MASK           ((uint32_t)DAC_CTRL_TxEN)
#define DACx_CTRL_BUFF_EN_MASK              ((uint32_t)DAC_CTRL_BxEN)
#define DACx_CTRL_DMA_EN_MASK               ((uint32_t)DAC_CTRL_DMAxEN)
#define DACx_CTRL_EN_MASK                   ((uint32_t)DAC_CTRL_DACxEN)

/** DAC_SOTT **/
#define DACx_CTRL_TRIGxEN_MASK              (DAC_SOTTR_TRxEN)      
#define DACy_CTRL_TRIGyEN_MASK              (DAC_SOTTR_TRyEN) 
#define DACx_CTRL_TRIGxSTEPEN_MASK          (DAC_SOTTR_TRBxEN) 
#define DACy_CTRL_TRIGySTEPEN_MASK          (DAC_SOTTR_TRByEN) 

#define DACx_CTRL_TRIGALLEN_MASK            (DAC_SOTTR_TRxEN  | DAC_SOTTR_TRyEN)
#define DACy_CTRL_TRIGALLSTEPEN_MASK        (DAC_SOTTR_TRBxEN | DAC_SOTTR_TRByEN)

/** DAC_SELCTRL **/
#define DACx_SELCTRL_SINCSEL_MASK           (DAC_SETCTRL_SINCSELx)
#define DACx_SELCTRL_MAxSEL_MASK            (DAC_SETCTRL_MAxSEL)
#define DACx_SELCTRL_TxSEL_MASK             (DAC_SETCTRL_TxSEL)

#define DACy_SELCTRL_SINCSEL_MASK           (DAC_SETCTRL_SINCSELy)
#define DACy_SELCTRL_MAySEL_MASK            (DAC_SETCTRL_MAySEL)
#define DACy_SELCTRL_TySEL_MASK             (DAC_SETCTRL_TySEL)

/** DAC_GCTRL **/
#define DAC_GCTRL_SYNSEL_MASK               (DAC_GCTRL_SYNSEL)

#define DAC12_GCTRL_PCS_MASK                (DAC12_GCTRL_PCS)
#define DAC3456_GCTRL_PCS_MASK              (DAC3456_GCTRL_PCS)

#define DAC_GCTRL_FREQ_MODE_MASK            (DAC12_GCTRL_HFSEL)
#define DAC_HIGH_FREQ_MODE_DISABLE          ((~DAC12_GCTRL_HFSEL))
#define DAC_HIGH_FREQ_MODE_BELOW_80M        (DAC12_GCTRL_HFSEL_0)
#define DAC_HIGH_FREQ_MODE_BELOW_160M       (DAC12_GCTRL_HFSEL_1)
#define DAC_HIGH_FREQ_MODE_ABOVE_160M       (DAC12_GCTRL_HFSEL_0|DAC12_GCTRL_HFSEL_1)

/** DAC_CALC **/
#define DAC_CALC_OTRIMxVALUE_MASK           (DAC_CALC_OTRIMx)
#define DAC_CALC_OTRIMyVALUE_MASK           (DAC_CALC_OTRIMy)

/** DAC_STINC **/
#define DAC_STINC_STINCDATAx_MASK           (DAC_STINC_STINCDATAx)
#define DAC_STINC_STINCDATAy_MASK           (DAC_STINC_STINCDATAy)
/** DAC_STRST **/
#define DAC_STRST_STRSTDATAx_MASK           (DAC_STRST_STRSTDATAx)
#define DAC_STRST_STRSTDATAy_MASK           (DAC_STRST_STRSTDATAy)

#define IS_DAC12(x)                         ((uint8_t)(x) < 2)
#define IS_DAC34(x)                         (((uint8_t)(x) == 2) || ((uint8_t)(x) == 3))
#define IS_DAC56(x)                         (((uint8_t)(x) == 4) || ((uint8_t)(x) == 5))

#define IS_DAC13(x)                         ((((uint8_t)(x) == 0) || ((uint8_t)(x) == 2)))

#define IS_DAC135(x)                       (((uint8_t)(x) % 2) == 0) 
#define IS_DAC246(x)                       (((uint8_t)(x) % 2) != 0)

/** DAC_data_alignment **/
#define DAC_ALIGN_R_8BIT                   ((uint32_t)0x00000000U)
#define DAC_ALIGN_L_12BIT                  ((uint32_t)0x00000004U)
#define DAC_ALIGN_R_12BIT                  ((uint32_t)0x00000008U)

/**DAC interrupts_definition **/
#define DAC_INT_DMAUDRIEN                  (DAC_CTRL_DMAUDRxIEn)
#define DAC_INT_TROVIEN                    (DAC_CTRL_TROVCxIEN)

/** DAC_STS Flag **/
#define DAC_FLAG_DMAUDR                    (DAC_STS_DMAUDRx)  
#define DAC_FLAG_CALCOMPLETE               (DAC_STS_CALFLAGx) 
#define DAC_FLAG_DORSTAT                   (DAC_STS_DORSTATx) 
#define DAC_FLAG_TROVC                     (DAC_STS_TROVCFLAGx) 
#define DAC_FLAG_VFLAGCOMP                 (DAC_STS_VFLAGxCOMP) 

/** DAC_STS INT Flag **/
#define DAC_INTFLAG_DMAUDR                 (DAC_STS_DMAUDRx)  
#define DAC_INTFLAG_TROVC                  (DAC_STS_TROVCFLAGx)


/** DAC_Exported_Functions **/
void DAC_DeInit(DACX DACx);
void DAC_StructInit(DAC_InitType* DAC_InitStruct);
void DAC_Init(DACX DACx, DAC_InitType* DAC_InitStruct);

void DAC_Enable(DACX DACx, FunctionalState Cmd);
void DAC_DmaEnable(DACX DACx, FunctionalState Cmd);
void DAC_CaliEnable(DACX DACx, FunctionalState Cmd);
void DAC_ConnetToExternalPinEnable(DACX DACx, FunctionalState Cmd);
void DAC_ConnetToOnChipEnable(DACX DACx, FunctionalState Cmd);
void DAC_HighDriveAbilityEnable(DACX DACx, FunctionalState Cmd);
void DAC_SignFormatModeEnable(DACX DACx, FunctionalState Cmd);
void DAC_DMADoubleDataModeEnable(DACX DACx, FunctionalState Cmd);

void DAC_SoftTrgEnable(DACX DACx, FunctionalState Cmd);
void DAC_SoftTrgSawStepEnable(DACX DACx, FunctionalState Cmd);
void DAC_DualSoftwareTrgEnable(DAC_Module *Dual_DACx, FunctionalState Cmd);
void DAC_DualSoftwareTrgSawStepEnable(DAC_Module *Dual_DACx, FunctionalState Cmd);

void DAC_WaveGenerationConfig(DACX DACx, uint32_t DAC_Wave);
void DAC_SetSawtoothResetValue(DACX DACx, uint16_t ResetValue);
void DAC_SetSawtoothStepValue(DACX DACx, uint16_t StepData);
void DAC_SetData(DACX DACx, uint32_t DAC_Align, uint16_t Data);
void DAC_SetDualChData(DAC_Module *Dual_DACx, uint32_t DAC_Align, uint16_t Data2, uint16_t Data1);
uint16_t DAC_GetOutputDataVal(DACX DACx);

FlagStatus DAC_GetFlagSts(DACX DACx, uint32_t DAC_FLAG);
void DAC_ClearFlag(DACX DACx, uint32_t DAC_FLAG);

void DAC_ConfigInt(DACX DACx, uint32_t DAC_IT, FunctionalState Cmd);
FlagStatus DAC_GetIntSts(DACX DACx, uint32_t DAC_IT);
void DAC_ClearITPendingBit(DACX DACx, uint32_t DAC_IT);

void DAC_ConfigClkPrescaler(DAC_Module* DACx, uint8_t Prescaler);
void DAC_SetHighFrequencyMode(DAC_Module* DACx, uint32_t mode);
void DAC_SetUserTrimming(DACX DACx, uint8_t TrimmingValue);
#ifdef __cplusplus
}
#endif

#endif /*__N32H76X_78X_DAC_H__ */


