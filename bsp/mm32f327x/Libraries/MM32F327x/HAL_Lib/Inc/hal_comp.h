////////////////////////////////////////////////////////////////////////////////
/// @file     hal_comp.h
/// @author   AE TEAM
/// @brief    THIS FILE CONTAINS ALL THE FUNCTIONS PROTOTYPES FOR THE COMP
///           FIRMWARE LIBRARY.
////////////////////////////////////////////////////////////////////////////////
/// @attention
///
/// THE EXISTING FIRMWARE IS ONLY FOR REFERENCE, WHICH IS DESIGNED TO PROVIDE
/// CUSTOMERS WITH CODING INFORMATION ABOUT THEIR PRODUCTS SO THEY CAN SAVE
/// TIME. THEREFORE, MINDMOTION SHALL NOT BE LIABLE FOR ANY DIRECT, INDIRECT OR
/// CONSEQUENTIAL DAMAGES ABOUT ANY CLAIMS ARISING OUT OF THE CONTENT OF SUCH
/// HARDWARE AND/OR THE USE OF THE CODING INFORMATION CONTAINED HEREIN IN
/// CONNECTION WITH PRODUCTS MADE BY CUSTOMERS.
///
/// <H2><CENTER>&COPY; COPYRIGHT MINDMOTION </CENTER></H2>
////////////////////////////////////////////////////////////////////////////////

// Define to prevent recursive inclusion
#ifndef __HAL_COMP_H
#define __HAL_COMP_H


// Files includes
#include "reg_common.h"
#include "reg_comp.h"

////////////////////////////////////////////////////////////////////////////////
/// @addtogroup MM32_Hardware_Abstract_Layer
/// @{

////////////////////////////////////////////////////////////////////////////////
/// @defgroup COMP_HAL
/// @brief COMP HAL modules
/// @{
////////////////////////////////////////////////////////////////////////////////
/// @defgroup COMP_Exported_Types
/// @{

////////////////////////////////////////////////////////////////////////////////
/// @brief COMP_InvertingInput
////////////////////////////////////////////////////////////////////////////////
typedef enum {
    COMP_InvertingInput_IO0           = COMP_CSR_INM_0,                       ///< INM0 as COMP inverting input
    COMP_InvertingInput_IO1           = COMP_CSR_INM_1,                       ///< INM1 as COMP inverting input
    COMP_InvertingInput_IO2           = COMP_CSR_INM_2,                       ///< INM2 as COMP inverting input
    COMP_InvertingInput_CRV           = COMP_CSR_INM_3,                       ///< INM3 as COMP inverting input
    COMP_InvertingInput_IO3           = COMP_CSR_INM_3,                       ///< INM3 as COMP inverting input
} EM_COMP_InvertingInput;

////////////////////////////////////////////////////////////////////////////////
/// @brief COMP_NonInvertingInput
////////////////////////////////////////////////////////////////////////////////
typedef enum {
    COMP_NonInvertingInput_IO0        = COMP_CSR_INP_INP0,                    ///< INP0 as COMP non-inverting input
    COMP_NonInvertingInput_IO1        = COMP_CSR_INP_INP1,                    ///< INP1 as COMP non-inverting input
    COMP_NonInvertingInput_IO2        = COMP_CSR_INP_INP2,                    ///< INP2 as COMP non-inverting input
    COMP_NonInvertingInput_IO3        = COMP_CSR_INP_INP3,                    ///< INP3 as COMP non-inverting input
} EM_COMP_NonInvertingInput;

////////////////////////////////////////////////////////////////////////////////
/// @brief COMP_Output
////////////////////////////////////////////////////////////////////////////////
typedef enum {
    COMP_Output_None                  = 0x00000000,                             ///< No output
    COMP_Output_TIM1BKIN              = COMP_CSR_OUT_TIM1_BRAKE,                ///< Timer1 brake input
    COMP_Output_TIM1OCREFCLR          = COMP_CSR_OUT_TIM1_OCREFCLR,             ///< Timer1 ocrefclear input
    COMP_Output_TIM1IC1               = COMP_CSR_OUT_TIM1_CAPTURE1,             ///< Timer1 input capture 1
    COMP_Output_TIM2IC4               = COMP_CSR_OUT_TIM2_CAPTURE4,             ///< Timer2 input capture 4
    COMP_Output_TIM2OCREFCLR          = COMP_CSR_OUT_TIM2_OCREFCLR,             ///< Timer2 ocrefclear input
    COMP_Output_TIM3IC1               = COMP_CSR_OUT_TIM3_CAPTURE1,             ///< Timer3 input capture 1
    COMP_Output_TIM3OCREFCLR          = COMP_CSR_OUT_TIM3_OCREFCLR              ///< Timer3 ocrefclear input
} EM_COMP_Output;

////////////////////////////////////////////////////////////////////////////////
/// @brief COMP_OutputPoloarity
////////////////////////////////////////////////////////////////////////////////
typedef enum {
    COMP_NonInverted                  = 0x00000000,                             ///< COMP non-inverting output
    COMP_OutputPol_NonInverted        = 0x00000000,
    COMP_Inverted                     = 0x00008000,                             ///< COMP inverting output
    COMP_OutputPol_Inverted           = 0x00008000
} EM_COMP_OutputPol;

////////////////////////////////////////////////////////////////////////////////
/// @brief COMP_Hysteresis
////////////////////////////////////////////////////////////////////////////////
typedef enum {
    COMP_Hysteresis_No                = COMP_CSR_HYST_0,                      ///< Hysteresis Voltage: 0mV
    COMP_Hysteresis_Low               = COMP_CSR_HYST_15,                     ///< Hysteresis Voltage: 15mV
    COMP_Hysteresis_Medium            = COMP_CSR_HYST_30,                     ///< Hysteresis Voltage: 30mV
    COMP_Hysteresis_High              = COMP_CSR_HYST_90                      ///< Hysteresis Voltage: 90mV
} EM_COMP_Hysteresis;
typedef enum {
    COMP_Filter_0_Period                = COMP_CSR_OFLT_0,                      ///< filter is ((u32)0x00000000)
    COMP_Filter_2_Period                = COMP_CSR_OFLT_1,                      ///< filter is ((u32)0x00040000)
    COMP_Filter_4_Period                = COMP_CSR_OFLT_2,                      ///< filter is ((u32)0x00080000)
    COMP_Filter_8_Period                = COMP_CSR_OFLT_3,                      ///< filter is ((u32)0x000C0000)
    COMP_Filter_16_Period               = COMP_CSR_OFLT_4,                      ///< filter is ((u32)0x00100000)
    COMP_Filter_32_Period               = COMP_CSR_OFLT_5,                      ///< filter is ((u32)0x00140000)
    COMP_Filter_64_Period               = COMP_CSR_OFLT_6,                      ///< filter is ((u32)0x00180000)
    COMP_Filter_128_Period              = COMP_CSR_OFLT_7,                      ///< filter is ((u32)0x001C0000)
} EM_COMP_FILT;
////////////////////////////////////////////////////////////////////////////////
/// @brief COMP_Mode
////////////////////////////////////////////////////////////////////////////////
typedef enum {
    COMP_Mode_HighSpeed               = COMP_CSR_MODE_HIGHRATE,               ///< Comparator high rate mode
    COMP_Mode_MediumSpeed             = COMP_CSR_MODE_MEDIUMRATE,             ///< Comparator medium rate mode
    COMP_Mode_LowPower                = COMP_CSR_MODE_LOWPOWER,               ///< Comparator low power mode
    COMP_Mode_UltraLowPower           = COMP_CSR_MODE_LOWESTPOWER             ///< Comparator lowest power mode
} EM_COMP_Mode;

////////////////////////////////////////////////////////////////////////////////
/// @brief COMP_OutputLevel
////////////////////////////////////////////////////////////////////////////////
typedef enum {
    COMP_OutputLevel_High             = COMP_CSR_OUT,                         ///<  High output
    COMP_OutputLevel_Low              = 0x00000000                            ///<  Low output
} EM_COMP_OutputLevel;

////////////////////////////////////////////////////////////////////////////////
/// @brief  COMP Init structure definition
////////////////////////////////////////////////////////////////////////////////
typedef struct {
    union {
        u32 COMP_InvertingInput;
        u32 Invert;                                                             ///< Selects the inverting input of the comparator.
    };
    union {
        u32 COMP_NonInvertingInput;
        u32 NonInvert;                                                          ///< Selects the non inverting input of the comparator.
    };
    union {
        u32 COMP_Output;
        u32 Output;                                                             ///< Selects the output redirection of the comparator.
        u32 BlankingSrce;                                                       ///< Selects the output blanking source of the comparator.
    };
    union {
        u32 COMP_OutputPol;
        u32 OutputPol;                                                          ///< Selects the output polarity of the comparator.
    };
    union {
        u32 COMP_Hysteresis;
        u32 Hysteresis;                                                         ///< Selects the hysteresis voltage of the comparator.
    };
    union {
        u32 COMP_Mode;
        u32 Mode;                                                               ///< Selects the operating mode of the comparator and allows
    };
    union {
        u32 COMP_Filter;
        u32 OFLT;                                                               ///< to adjust the speed/consumption.
    };
} COMP_InitTypeDef;



typedef struct {

    FunctionalState COMP_Poll_En;                                                ///< Selects the inverting input of the comparator.

    u32 COMP_Poll_Ch;                                                            ///< Selects the non inverting input of the comparator.
    u32 COMP_Poll_Fixn;                                                          ///< Selects the output redirection of the comparator.
    u32 COMP_Poll_Period;                                                        ///< Selects the output polarity of the comparator.
    u32 COMP_Poll_Pout;                                                          ///< Selects the hysteresis voltage of the comparator.

} COMP_POLL_InitTypeDef;
/// @}

////////////////////////////////////////////////////////////////////////////////
/// @defgroup COMP_Exported_Constants
/// @{
////////////////////////////////////////////////////////////////////////////////
/// @brief  COMP Init structure definition
////////////////////////////////////////////////////////////////////////////////
typedef enum {
    COMP1                       =   (0x00000C),                               ///< Select comparator 1
    COMP2                       =   (0x000010),                               ///< Select comparator 2
} COMP_Selection_TypeDef;

#define COMP_BlankingSrce_None  ((u32)0x00000000)
#define COMP_CSR_CLEAR_MASK     ((u32)0x00000003)

#define COMP_CSR_COMPSW1        ((u32)0x00000002)

/// @}

////////////////////////////////////////////////////////////////////////////////
///@defgroup COMP_Exported_Variables
/// @{
#ifdef _HAL_COMP_C_

#define GLOBAL
#else
#define GLOBAL extern
#endif

#undef GLOBAL
/// @}

////////////////////////////////////////////////////////////////////////////////
/// @defgroup COMP_Exported_Functions
/// @{


void COMP_DeInit(COMP_Selection_TypeDef selection);
void COMP_Init(COMP_Selection_TypeDef selection, COMP_InitTypeDef* init_struct);
void COMP_StructInit(COMP_InitTypeDef* init_struct);
void COMP_Cmd(COMP_Selection_TypeDef selection, FunctionalState state);
void COMP_SwitchCmd(COMP_Selection_TypeDef selection, FunctionalState state);
void COMP_LockConfig(COMP_Selection_TypeDef selection);

u32 COMP_GetOutputLevel(COMP_Selection_TypeDef selection);

void COMP_SetCrv(u8 crv_select, u8 crv_level);
#define  SET_COMP_CRV COMP_SetCrv


/// @}

/// @}

/// @}

////////////////////////////////////////////////////////////////////////////////
#endif //__HAL_COMP_H
////////////////////////////////////////////////////////////////////////////////
