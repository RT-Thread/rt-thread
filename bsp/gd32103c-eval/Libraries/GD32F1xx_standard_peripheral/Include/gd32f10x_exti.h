/**
  ******************************************************************************
  * @brief   EXTI header file of the firmware library.
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __GD32F10X_EXTI_H
#define __GD32F10X_EXTI_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "gd32f10x.h"

/** @addtogroup GD32F10x_Firmware
  * @{
  */

/** @addtogroup EXTI
  * @{
  */

/** @defgroup EXTI_Exported_Types
  * @{
  */

/**
  * @brief  EXTI Mode enumeration
  */
typedef enum {
    EXTI_Mode_Interrupt = 0x00,
    EXTI_Mode_Event = 0x04
} EXTI_ModePara;

/**
  * @brief  EXTI Trigger enumeration
  */
typedef enum {
    EXTI_Trigger_Rising = 0x08,
    EXTI_Trigger_Falling = 0x0C,
    EXTI_Trigger_Rising_Falling = 0x10
} EXTI_TriggerPara;

/**
  * @brief  EXTI Initial Parameters
  */
typedef struct {
    uint32_t EXTI_LINE;                  /*!< The selection of EXTI lines. */
    EXTI_ModePara EXTI_Mode;             /*!< The mode for the EXTI lines, detailed in @ref EXTIMode_Para. */
    EXTI_TriggerPara EXTI_Trigger;       /*!< The trigger edge for the EXTI lines, detailed in EXTI_TriggerPara. */
    TypeState EXTI_LINEEnable;           /*!< The new value of the selected EXTI lines. */
} EXTI_InitPara;

/**
  * @}
  */

/** @defgroup EXTI_Exported_Constants
  * @{
  */

/** @defgroup EXTI_lines
  * @{
  */
#define EXTI_LINE0       ((uint32_t)0x00000001)        /*!< External interrupt line 0 */
#define EXTI_LINE1       ((uint32_t)0x00000002)        /*!< External interrupt line 1 */
#define EXTI_LINE2       ((uint32_t)0x00000004)        /*!< External interrupt line 2 */
#define EXTI_LINE3       ((uint32_t)0x00000008)        /*!< External interrupt line 3 */
#define EXTI_LINE4       ((uint32_t)0x00000010)        /*!< External interrupt line 4 */
#define EXTI_LINE5       ((uint32_t)0x00000020)        /*!< External interrupt line 5 */
#define EXTI_LINE6       ((uint32_t)0x00000040)        /*!< External interrupt line 6 */
#define EXTI_LINE7       ((uint32_t)0x00000080)        /*!< External interrupt line 7 */
#define EXTI_LINE8       ((uint32_t)0x00000100)        /*!< External interrupt line 8 */
#define EXTI_LINE9       ((uint32_t)0x00000200)        /*!< External interrupt line 9 */
#define EXTI_LINE10      ((uint32_t)0x00000400)        /*!< External interrupt line 10 */
#define EXTI_LINE11      ((uint32_t)0x00000800)        /*!< External interrupt line 11 */
#define EXTI_LINE12      ((uint32_t)0x00001000)        /*!< External interrupt line 12 */
#define EXTI_LINE13      ((uint32_t)0x00002000)        /*!< External interrupt line 13 */
#define EXTI_LINE14      ((uint32_t)0x00004000)        /*!< External interrupt line 14 */
#define EXTI_LINE15      ((uint32_t)0x00008000)        /*!< External interrupt line 15 */

#define EXTI_LINE16      ((uint32_t)0x00010000)        /*!< External interrupt line 16 
                                                            Connected to the LVD */
#define EXTI_LINE17      ((uint32_t)0x00020000)        /*!< External interrupt line 17 
                                                            Connected to the RTC Alarm */
#define EXTI_LINE18      ((uint32_t)0x00040000)        /*!< External interrupt line 18 
                                                            Connected to the USB Wakeup */
#define EXTI_LINE19      ((uint32_t)0x00080000)        /*!< External interrupt line 19
                                                            Connected to the Ethernet Wakeup */

/**
  * @}
  */

/**
  * @}
  */

/** @defgroup EXTI_Exported_Functions
  * @{
  */
void EXTI_DeInit(EXTI_InitPara *EXTI_InitParaStruct);
void EXTI_Init(EXTI_InitPara *EXTI_InitParaStruct);
void EXTI_SWINT_Enable(uint32_t EXTI_LINE);
TypeState EXTI_GetBitState(uint32_t EXTI_LINE);
void EXTI_ClearBitState(uint32_t EXTI_LINE);
TypeState EXTI_GetIntBitState(uint32_t EXTI_LINE);
void EXTI_ClearIntBitState(uint32_t EXTI_LINE);

#ifdef __cplusplus
}
#endif

#endif /* __GD32F10X_EXTI_H */

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

