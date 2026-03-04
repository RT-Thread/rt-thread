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
 * @file n32h76x_78x_exti.h
 * @author Nations
 * @version v1.0.0
 *
 * @copyright Copyright (c) 2025, Nations Technologies Inc. All rights reserved.
 */
#ifndef __N32H76X_78X_EXTI_H__
#define __N32H76X_78X_EXTI_H__

#ifdef __cplusplus
extern "C"
{
#endif

#include "n32h76x_78x.h"

/*** EXTI Structure Definition Start ***/



/** EXTI mode enumeration **/ 
typedef enum
{
    EXTI_Mode_Interrupt = 0x60,
    EXTI_Mode_Event     = 0xA0,
}EXTIMode_TypeDef;

/** EXTI Trigger enumeration **/
typedef enum
{
    EXTI_Trigger_Rising  = 0x00,
    EXTI_Trigger_Falling = 0x20,
    EXTI_Trigger_Rising_Falling = 0x10
}EXTITrigger_TypeDef;

/** EXTI Init Structure definition **/
typedef struct
{
    uint32_t EXTI_Line;               /*!< Specifies the EXTI lines to be enabled or disabled.  */                                       

    EXTIMode_TypeDef EXTI_Mode;       /*!< Specifies the mode for the EXTI lines.*/                                        

    EXTITrigger_TypeDef EXTI_Trigger; /*!< Specifies the trigger signal active edge for the EXTI lines. */
                                 
    FunctionalState EXTI_LineCmd;     /*!< Specifies the new state of the selected EXTI lines. */
} EXTI_InitType;                                      

/*** EXTI Structure Definition End ***/


/*** EXTI Macro Definition Start ***/
/**  EXTI_Lines **/
#define EXTI_LINE0       ((uint32_t)0)   /* External interrupt line 0 */
#define EXTI_LINE1       ((uint32_t)1)   /* External interrupt line 1 */
#define EXTI_LINE2       ((uint32_t)2)   /* External interrupt line 2 */
#define EXTI_LINE3       ((uint32_t)3)   /* External interrupt line 3 */
#define EXTI_LINE4       ((uint32_t)4)   /* External interrupt line 4 */
#define EXTI_LINE5       ((uint32_t)5)   /* External interrupt line 5 */
#define EXTI_LINE6       ((uint32_t)6)   /* External interrupt line 6 */
#define EXTI_LINE7       ((uint32_t)7)   /* External interrupt line 7 */
#define EXTI_LINE8       ((uint32_t)8)   /* External interrupt line 8 */
#define EXTI_LINE9       ((uint32_t)9)   /* External interrupt line 9 */
#define EXTI_LINE10      ((uint32_t)10)  /* External interrupt line 10 */
#define EXTI_LINE11      ((uint32_t)11)  /* External interrupt line 11 */
#define EXTI_LINE12      ((uint32_t)12)  /* External interrupt line 12 */
#define EXTI_LINE13      ((uint32_t)13)  /* External interrupt line 13 */
#define EXTI_LINE14      ((uint32_t)14)  /* External interrupt line 14 */
#define EXTI_LINE15      ((uint32_t)15)  /* External interrupt line 15 */
#define EXTI_LINE16      ((uint32_t)16)  /* External interrupt line 16 Connected to the PVD Output */
#define EXTI_LINE17      ((uint32_t)17)  /* External interrupt line 17 Connected to the RTC_ALARM */
#define EXTI_LINE18      ((uint32_t)18)  /* External interrupt line 18 Connected to the RTC tamper or timestamp*/
#define EXTI_LINE19      ((uint32_t)19)  /* External interrupt line 19 Connected to the RTC wakeup timer */
#define EXTI_LINE20      ((uint32_t)20)  /* External interrupt line 20 Connected to the COMP1 output */
#define EXTI_LINE21      ((uint32_t)21)  /* External interrupt line 21 Connected to the COMP2 output */
#define EXTI_LINE22      ((uint32_t)22)  /* External interrupt line 22 Connected to the COMP3 output */
#define EXTI_LINE23      ((uint32_t)23)  /* External interrupt line 23 Connected to the COMP4 output */
#define EXTI_LINE24      ((uint32_t)100) /* External interrupt line 24 Connected to the SDMMC1_wkup */
#define EXTI_LINE25      ((uint32_t)101) /* External interrupt line 25 Connected to the SDMMC2_wkup*/
#define EXTI_LINE49      ((uint32_t)42)  /* External interrupt line 49 Connected to the LPUART1 wakeup */
#define EXTI_LINE51      ((uint32_t)127) /* External interrupt line 51 Connected to the DCMUA Interrupt */
#define EXTI_LINE52      ((uint32_t)43)  /* External interrupt line 52 Connected to the LPUART2 wakeup */
#define EXTI_LINE54      ((uint32_t)130) /* External interrupt line 54 Connected to the DCMUB Interruptt */
#define EXTI_LINE55      ((uint32_t)139) /* External interrupt line 55 Connected to the CM7 AHBS_ABORT */
#define EXTI_LINE56      ((uint32_t)138) /* External interrupt line 56 Connected to the CM7_AHBSRDY_ERROR */
#define EXTI_LINE62      ((uint32_t)48)  /* External interrupt line 62 Connected to the USB1 wakeup */
#define EXTI_LINE63      ((uint32_t)49)  /* External interrupt line 63 Connected to the USB2 wakeup */
#define EXTI_LINE64      ((uint32_t)44)  /* External interrupt line 64 Connected to the CM7 Correctable Error on Cache Read */
#define EXTI_LINE65      ((uint32_t)45)  /* External interrupt line 65 Connected to the CM7 Fatal Error on Cache Read */
#define EXTI_LINE66      ((uint32_t)37)  /* External interrupt line 66 Connected to the LPTIM1 wakeup */
#define EXTI_LINE67      ((uint32_t)38)  /* External interrupt line 67 Connected to the LPTIM2 wakeup */
#define EXTI_LINE68      ((uint32_t)39)  /* External interrupt line 68 Connected to the LPTIM3 wakeup */
#define EXTI_LINE69      ((uint32_t)40)  /* External interrupt line 69 Connected to the LPTIM4 wakeup */
#define EXTI_LINE70      ((uint32_t)31)  /* External interrupt line 70 Connected to the wakeup1 */
#define EXTI_LINE71      ((uint32_t)32)  /* External interrupt line 71 Connected to the wakeup2 */
#define EXTI_LINE72      ((uint32_t)33)  /* External interrupt line 72 Connected to the wakeup3 */
#define EXTI_LINE73      ((uint32_t)34)  /* External interrupt line 73 Connected to the wakeup4 */
#define EXTI_LINE74      ((uint32_t)35)  /* External interrupt line 74 Connected to the wakeup5 */
#define EXTI_LINE75      ((uint32_t)36)  /* External interrupt line 75 Connected to the wakeup6 */
#define EXTI_LINE76      ((uint32_t)152) /* External interrupt line 76 Connected to the RCC interrupt */
#define EXTI_LINE77      ((uint32_t)153) /* External interrupt line 77 Connected to the SEMA1 interrupt */
#define EXTI_LINE78      ((uint32_t)154) /* External interrupt line 78 Connected to the SEMA2 interrupt */
#define EXTI_LINE79      ((uint32_t)155) /* External interrupt line 79 Connected to the CortexM4 SEV interrupt */
#define EXTI_LINE80      ((uint32_t)156) /* External interrupt line 80 Connected to the CortexM7 SEV interrupt */
#define EXTI_LINE81      ((uint32_t)24)  /* External interrupt line 81 Connected to the  WWDG1 reset */
#define EXTI_LINE82      ((uint32_t)25)  /* External interrupt line 82 Connected to the  WWDG2 reset */
#define EXTI_LINE83      ((uint32_t)102) /* External interrupt line 83 Connected to the  ETH1 Wkup */
#define EXTI_LINE84      ((uint32_t)103) /* External interrupt line 84 Connected to the  ETH2 Wkup */
#define EXTI_LINE85      ((uint32_t)157) /* External interrupt line 85 Connected to the  HSECSS interrupt */
#define EXTI_LINE86      ((uint32_t)41)  /* External interrupt line 86 Connected to the  LPTIM5 wakeup */
#define EXTI_LINE87      ((uint32_t)28)  /* External interrupt line 87 Connected to the  DSI Error Event */
#define EXTI_LINE88      ((uint32_t)51)  /* External interrupt line 88 Connected to the  BKP EMC */
#define EXTI_LINE89      ((uint32_t)50)  /* External interrupt line 89 Connected to the  VDDD EMC */

/** EXTI_TSSEL_Line **/
#define EXTI_TSSEL_LINE_MASK    (EXTI_TS_SEL_TSSEL)  /** External interrupt line all **/
#define EXTI_TSSEL_LINE0        (EXTI_TS_SEL_EXTI0)  /** External interrupt line 0 **/
#define EXTI_TSSEL_LINE1        (EXTI_TS_SEL_EXTI1)  /** External interrupt line 1 **/
#define EXTI_TSSEL_LINE2        (EXTI_TS_SEL_EXTI2)  /** External interrupt line 2 **/
#define EXTI_TSSEL_LINE3        (EXTI_TS_SEL_EXTI3)  /** External interrupt line 3 **/
#define EXTI_TSSEL_LINE4        (EXTI_TS_SEL_EXTI4)  /** External interrupt line 4 **/
#define EXTI_TSSEL_LINE5        (EXTI_TS_SEL_EXTI5)  /** External interrupt line 5 **/
#define EXTI_TSSEL_LINE6        (EXTI_TS_SEL_EXTI6)  /** External interrupt line 6 **/
#define EXTI_TSSEL_LINE7        (EXTI_TS_SEL_EXTI7)  /** External interrupt line 7 **/
#define EXTI_TSSEL_LINE8        (EXTI_TS_SEL_EXTI8)  /** External interrupt line 8 **/
#define EXTI_TSSEL_LINE9        (EXTI_TS_SEL_EXTI9)  /** External interrupt line 9 **/
#define EXTI_TSSEL_LINE10       (EXTI_TS_SEL_EXTI10) /** External interrupt line 10 **/
#define EXTI_TSSEL_LINE11       (EXTI_TS_SEL_EXTI11) /** External interrupt line 11 **/
#define EXTI_TSSEL_LINE12       (EXTI_TS_SEL_EXTI12) /** External interrupt line 12 **/
#define EXTI_TSSEL_LINE13       (EXTI_TS_SEL_EXTI13) /** External interrupt line 13 **/
#define EXTI_TSSEL_LINE14       (EXTI_TS_SEL_EXTI14) /** External interrupt line 14 **/
#define EXTI_TSSEL_LINE15       (EXTI_TS_SEL_EXTI15) /** External interrupt line 15 **/

/*** EXTI Macro Definition End ***/

/** EXTI Driving Functions Declaration **/
void EXTI_DeInit(void);

void EXTI_InitPeripheral(EXTI_InitType* EXTI_InitStruct );
void EXTI_InitStruct(EXTI_InitType* EXTI_InitStruct );
void EXTI_TriggerSWInt(uint32_t EXTI_Line );
FlagStatus EXTI_GetStatusFlag( uint32_t EXTI_Line);
void EXTI_ClrStatusFlag(uint32_t EXTI_Line);
ITStatus  EXTI_GetITStatus(uint32_t EXTI_Line);
void EXTI_ClrITPendBit(uint32_t EXTI_Line);
void EXTI_RTCTimeStampSel(uint32_t EXTI_TSSEL_Line);

#ifdef __cplusplus
}

#endif

#endif /* __N32H76X_78X_EXTI_H__ */
