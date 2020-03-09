/**
 **************************************************************************
 * File Name    : at32f4xx_exti.h
 * Description  : at32f4xx EXTI header file
 * Date         : 2019-06-04
 * Version      : V1.0.5
 **************************************************************************
 */


/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __AT32F4xx_EXTI_H
#define __AT32F4xx_EXTI_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "at32f4xx.h"

/** @addtogroup at32f4xx_StdPeriph_Driver
  * @{
  */

/** @addtogroup EXTI
  * @{
  */

/** @defgroup EXTI_Exported_Types
  * @{
  */

/**
  * @brief  EXTI mode enumeration
  */

typedef enum
{
    EXTI_Mode_Interrupt = 0x00,
    EXTI_Mode_Event = 0x04
} EXTIMode_Type;

#define IS_EXTI_MODE(MODE)                  (((MODE) == EXTI_Mode_Interrupt) || ((MODE) == EXTI_Mode_Event))

/**
  * @brief  EXTI Trigger enumeration
  */

typedef enum
{
    EXTI_Trigger_Rising = 0x08,
    EXTI_Trigger_Falling = 0x0C,
    EXTI_Trigger_Rising_Falling = 0x10
} EXTITrigger_Type;

#define IS_EXTI_TRIGGER(TRIGGER)            (((TRIGGER) == EXTI_Trigger_Rising) || \
                                             ((TRIGGER) == EXTI_Trigger_Falling) || \
                                             ((TRIGGER) == EXTI_Trigger_Rising_Falling))
/**
  * @brief  EXTI Init Structure definition
  */

typedef struct
{
    uint32_t EXTI_Line;                     /*!< Specifies the EXTI lines to be enabled or disabled.
                                                  This parameter can be any combination of @ref EXTI_Lines */
                                            
    EXTIMode_Type EXTI_Mode;                /*!< Specifies the mode for the EXTI lines.
                                                  This parameter can be a value of @ref EXTIMode_Type */
                                            
    EXTITrigger_Type EXTI_Trigger;          /*!< Specifies the trigger signal active edge for the EXTI lines.
                                                  This parameter can be a value of @ref EXTIMode_Type */

    FunctionalState EXTI_LineEnable;        /*!< Specifies the new state of the selected EXTI lines.
                                                  This parameter can be set either to ENABLE or DISABLE */
} EXTI_InitType;

/**
  * @}
  */

/** @defgroup EXTI_Exported_Constants
  * @{
  */

/** @defgroup EXTI_Lines
  * @{
  */

#define EXTI_Line0                          ((uint32_t)0x000001)  /*!< External interrupt line 0 */
#define EXTI_Line1                          ((uint32_t)0x000002)  /*!< External interrupt line 1 */
#define EXTI_Line2                          ((uint32_t)0x000004)  /*!< External interrupt line 2 */
#define EXTI_Line3                          ((uint32_t)0x000008)  /*!< External interrupt line 3 */
#define EXTI_Line4                          ((uint32_t)0x000010)  /*!< External interrupt line 4 */
#define EXTI_Line5                          ((uint32_t)0x000020)  /*!< External interrupt line 5 */
#define EXTI_Line6                          ((uint32_t)0x000040)  /*!< External interrupt line 6 */
#define EXTI_Line7                          ((uint32_t)0x000080)  /*!< External interrupt line 7 */
#define EXTI_Line8                          ((uint32_t)0x000100)  /*!< External interrupt line 8 */
#define EXTI_Line9                          ((uint32_t)0x000200)  /*!< External interrupt line 9 */
#define EXTI_Line10                         ((uint32_t)0x000400)  /*!< External interrupt line 10 */
#define EXTI_Line11                         ((uint32_t)0x000800)  /*!< External interrupt line 11 */
#define EXTI_Line12                         ((uint32_t)0x001000)  /*!< External interrupt line 12 */
#define EXTI_Line13                         ((uint32_t)0x002000)  /*!< External interrupt line 13 */
#define EXTI_Line14                         ((uint32_t)0x004000)  /*!< External interrupt line 14 */
#define EXTI_Line15                         ((uint32_t)0x008000)  /*!< External interrupt line 15 */
#define EXTI_Line16                         ((uint32_t)0x010000)  /*!< External interrupt line 16 Connected to the PVD Output */
#define EXTI_Line17                         ((uint32_t)0x020000)  /*!< External interrupt line 17 Connected to the RTC Alarm event */
#define EXTI_Line18                         ((uint32_t)0x040000)  /*!< External interrupt line 18 Connected to the USB Device FS
                                                                      Wakeup from suspend event */
#define EXTI_Line19                         ((uint32_t)0x080000)  /*!< External interrupt line 19 Connected to the COMP1*/
#ifdef AT32F415xx
  #define EXTI_Line20                         ((uint32_t)0x100000)  /*!< External interrupt line 20 Connected to the COMP2*/
  #define EXTI_Line21                         ((uint32_t)0x200000)  /*!< External interrupt line 20 Connected to the RTC Temper_Pin and Temper_Stamp*/
  #define EXTI_Line22                         ((uint32_t)0x400000)  /*!< External interrupt line 20 Connected to the RTC Wakeup*/

  #define IS_EXTI_LINE(LINE)                  ((((LINE) & (uint32_t)0xFF800000) == 0x00) && ((LINE) != (uint16_t)0x00))
  #define IS_GET_EXTI_LINE(LINE)              (((LINE) == EXTI_Line0)  || ((LINE) == EXTI_Line1) || \
                                             ((LINE) == EXTI_Line2)  || ((LINE) == EXTI_Line3) || \
                                             ((LINE) == EXTI_Line4)  || ((LINE) == EXTI_Line5) || \
                                             ((LINE) == EXTI_Line6)  || ((LINE) == EXTI_Line7) || \
                                             ((LINE) == EXTI_Line8)  || ((LINE) == EXTI_Line9) || \
                                             ((LINE) == EXTI_Line10) || ((LINE) == EXTI_Line11) || \
                                             ((LINE) == EXTI_Line12) || ((LINE) == EXTI_Line13) || \
                                             ((LINE) == EXTI_Line14) || ((LINE) == EXTI_Line15) || \
                                             ((LINE) == EXTI_Line16) || ((LINE) == EXTI_Line17) || \
                                             ((LINE) == EXTI_Line18) || ((LINE) == EXTI_Line19) || \
                                             ((LINE) == EXTI_Line20) || ((LINE) == EXTI_Line21) || \
                                             ((LINE) == EXTI_Line22))
#else
  #define IS_EXTI_LINE(LINE)                  ((((LINE) & (uint32_t)0xFFF00000) == 0x00) && ((LINE) != (uint16_t)0x00))
  #define IS_GET_EXTI_LINE(LINE)              (((LINE) == EXTI_Line0)  || ((LINE) == EXTI_Line1) || \
                                             ((LINE) == EXTI_Line2)  || ((LINE) == EXTI_Line3) || \
                                             ((LINE) == EXTI_Line4)  || ((LINE) == EXTI_Line5) || \
                                             ((LINE) == EXTI_Line6)  || ((LINE) == EXTI_Line7) || \
                                             ((LINE) == EXTI_Line8)  || ((LINE) == EXTI_Line9) || \
                                             ((LINE) == EXTI_Line10) || ((LINE) == EXTI_Line11) || \
                                             ((LINE) == EXTI_Line12) || ((LINE) == EXTI_Line13) || \
                                             ((LINE) == EXTI_Line14) || ((LINE) == EXTI_Line15) || \
                                             ((LINE) == EXTI_Line16) || ((LINE) == EXTI_Line17) || \
                                             ((LINE) == EXTI_Line18) || ((LINE) == EXTI_Line19))
#endif


/**
  * @}
  */

/**
  * @}
  */

/** @defgroup EXTI_Exported_Macros
  * @{
  */

/**
  * @}
  */

/** @defgroup EXTI_Exported_Functions
  * @{
  */

void EXTI_Reset(void);
void EXTI_Init(EXTI_InitType* EXTI_InitStruct);
void EXTI_StructInit(EXTI_InitType* EXTI_InitStruct);
void EXTI_GenerateSWInt(uint32_t EXTI_Line);
FlagStatus EXTI_GetFlagStatus(uint32_t EXTI_Line);
void EXTI_ClearFlag(uint32_t EXTI_Line);
ITStatus EXTI_GetIntStatus(uint32_t EXTI_Line);
void EXTI_ClearIntPendingBit(uint32_t EXTI_Line);

#ifdef __cplusplus
}
#endif

#endif /* __AT32F4xx_EXTI_H */
/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */


