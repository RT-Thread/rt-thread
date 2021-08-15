////////////////////////////////////////////////////////////////////////////////
/// @file     hal_redefine.h
/// @author   AE TEAM
/// @brief    THIS FILE CONTAINS ALL THE FUNCTIONS PROTOTYPES FOR THE REDEFINE
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
#ifndef __HAL_REDEFINE_H
#define __HAL_REDEFINE_H

// Files includes


////////////////////////////////////////////////////////////////////////////////
/// @addtogroup MM32_Hardware_Abstract_Layer
/// @{

/////////////////////////////////////1///////////////////////////////////////////
/// @defgroup REDEFINE_HAL
/// @brief REDEFINE HAL modules
/// @{


////////////////////////////////////////////////////////////////////////////////
/// @defgroup REDEFINE_Exported_Types
/// @{
///

/// @}

////////////////////////////////////////////////////////////////////////////////
/// @defgroup REDEFINE_Exported_Constants
/// @{
//Lib redefine


////////////////////////////////////////////////////////////////////////////////
/// @brief HAL_lib Version compatibility definition
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
/// @brief TIM compatibility definition
////////////////////////////////////////////////////////////////////////////////

#define TIM_TRGOSource_Reset          TIM_TRIGSource_Reset
#define TIM_TRGOSource_Enable         TIM_TRIGSource_Enable
#define TIM_TRGOSource_Update         TIM_TRIGSource_Update
#define TIM_TRGOSource_OC1            TIM_TRIGSource_OC1
#define TIM_TRGOSource_OC1Ref         TIM_TRIGSource_OC1Ref
#define TIM_TRGOSource_OC2Ref         TIM_TRIGSource_OC2Ref
#define TIM_TRGOSource_OC3Ref         TIM_TRIGSource_OC3Ref
#define TIM_TRGOSource_OC4Ref         TIM_TRIGSource_OC4Ref
///< The UG bit in the TIM_EGR register is used as the trigger output (TRIG).
///< The Counter Enable CEN is used as the trigger output (TRIG).
///< The update event is used as the trigger output (TRIG).
///< The trigger output sends a positive pulse when the CC1IF flag     ///< is to be set, as soon as a capture or compare match occurs (TRIG).
///< OC1REF signal is used as the trigger output (TRIG).
///< OC2REF signal is used as the trigger output (TRIG).
///< OC3REF signal is used as the trigger output (TRIG).
///< OC4REF signal is used as the trigger output (TRIG).
/// @}

////////////////////////////////////////////////////////////////////////////////
/// @defgroup REDEFINE_Exported_Variables
/// @{
#ifdef _HAL_REDEFINE_C_

#define GLOBAL
#else
#define GLOBAL extern
#endif

#undef GLOBAL
/// @}

////////////////////////////////////////////////////////////////////////////////
/// @defgroup REDEFINE_Exported_Functions
/// @{



/// @}

/// @}

/// @}

////////////////////////////////////////////////////////////////////////////////
#endif // __HAL_REDEFINE_H 
////////////////////////////////////////////////////////////////////////////////
