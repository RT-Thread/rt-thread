////////////////////////////////////////////////////////////////////////////////
/// @file     reg_tim.h
/// @author   AE TEAM
/// @brief    THIS FILE CONTAINS ALL THE FUNCTIONS PROTOTYPES FOR THE SERIES OF
///           MM32 FIRMWARE LIBRARY.
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

#ifndef __REG_TIM_H
#define __REG_TIM_H

// Files includes

#include <stdint.h>
#include <stdbool.h>
#include "types.h"




#if defined ( __CC_ARM )
#pragma anon_unions
#endif










////////////////////////////////////////////////////////////////////////////////
/// @brief TIM Base Address Definition
////////////////////////////////////////////////////////////////////////////////
#define TIM1_BASE                       (APB2PERIPH_BASE + 0x2C00)              ///< Base Address: 0x40012C00
#define TIM2_BASE                       (APB1PERIPH_BASE + 0x0000)              ///< Base Address: 0x40000000
#define TIM3_BASE                       (APB1PERIPH_BASE + 0x0400)              ///< Base Address: 0x40000400
#define TIM4_BASE                       (APB1PERIPH_BASE + 0x0800)              ///< Base Address: 0x40000800

#define TIM5_BASE                       (APB1PERIPH_BASE + 0x0C00)              ///< Base Address: 0x40000C00
#define TIM6_BASE                       (APB1PERIPH_BASE + 0x1000)              ///< Base Address: 0x40001000
#define TIM7_BASE                       (APB1PERIPH_BASE + 0x1400)              ///< Base Address: 0x40001400
#define TIM8_BASE                       (APB2PERIPH_BASE + 0x3400)              ///< Base Address: 0x40013400







////////////////////////////////////////////////////////////////////////////////
/// @brief Timer Register Structure Definition
////////////////////////////////////////////////////////////////////////////////
typedef struct {
    __IO u32 CR1;                                                               ///< TIM control register 1,                        offset: 0x00
    __IO u32 CR2;                                                               ///< TIM control register 2,                        offset: 0x04
    __IO u32 SMCR;                                                              ///< TIM slave Mode Control register,               offset: 0x08
    __IO u32 DIER;                                                              ///< TIM DMA/interrupt enable register,             offset: 0x0C
    __IO u32 SR;                                                                ///< TIM status register,                           offset: 0x10
    __IO u32 EGR;                                                               ///< TIM event generation register,                 offset: 0x14
    __IO u32 CCMR1;                                                             ///< TIM capture/compare mode register 1,           offset: 0x18
    __IO u32 CCMR2;                                                             ///< TIM capture/compare mode register 2,           offset: 0x1C
    __IO u32 CCER;                                                              ///< TIM capture/compare enable register,           offset: 0x20
    __IO u32 CNT;                                                               ///< TIM counter register,                          offset: 0x24
    __IO u32 PSC;                                                               ///< TIM prescaler register,                        offset: 0x28
    __IO u32 ARR;                                                               ///< TIM auto-reload register,                      offset: 0x2C
    __IO u32 RCR;                                                               ///< TIM repetition counter register,               offset: 0x30
    __IO u32 CCR1;                                                              ///< TIM capture/compare register 1,                offset: 0x34
    __IO u32 CCR2;                                                              ///< TIM capture/compare register 2,                offset: 0x38
    __IO u32 CCR3;                                                              ///< TIM capture/compare register 3,                offset: 0x3C
    __IO u32 CCR4;                                                              ///< TIM capture/compare register 4,                offset: 0x40
    __IO u32 BDTR;                                                              ///< TIM break and dead-time register,              offset: 0x44
    __IO u32 DCR;                                                               ///< TIM DMA control register,                      offset: 0x48
    __IO u32 DMAR;                                                              ///< TIM DMA address for full transfer register,    offset: 0x4C
    __IO u32 OR;                                                                ///< Option register,                               offset: 0x50
    __IO u32 CCMR3;                                                             ///< TIM capture/compare mode register 3,           offset: 0x54
    __IO u32 CCR5;                                                              ///< TIM capture/compare register 5,                offset: 0x58
    __IO u32 PDER;                                                              ///< PWM Shift repeat enable register,                offset: 0x5C
    __IO u32 CCR1FALL;                                                          ///< PWM shift count CCR1 register,                 offset: 0x60
    __IO u32 CCR2FALL;                                                          ///< PWM shift count CCR2 register,                 offset: 0x64
    __IO u32 CCR3FALL;                                                          ///< PWM shift count CCR3 register,                 offset: 0x68
    __IO u32 CCR4FALL;                                                          ///< PWM shift count CCR4 register,                 offset: 0x6c
    __IO u32 CCR5FALL;                                                          ///< PWM shift count CCR5 register,                 offset: 0x70
} TIM_TypeDef;


////////////////////////////////////////////////////////////////////////////////
/// @brief TIM type pointer Definition
////////////////////////////////////////////////////////////////////////////////
#define TIM1                            ((TIM_TypeDef*) TIM1_BASE)
#define TIM2                            ((TIM_TypeDef*) TIM2_BASE)
#define TIM3                            ((TIM_TypeDef*) TIM3_BASE)
#define TIM4                            ((TIM_TypeDef*) TIM4_BASE)

#define TIM5                            ((TIM_TypeDef*) TIM5_BASE)
#define TIM6                            ((TIM_TypeDef*) TIM6_BASE)
#define TIM7                            ((TIM_TypeDef*) TIM7_BASE)

#define TIM8                            ((TIM_TypeDef*) TIM8_BASE)




////////////////////////////////////////////////////////////////////////////////
/// @brief TIM_CR1 Register Bit Definition
////////////////////////////////////////////////////////////////////////////////
#define TIM_CR1_CEN_Pos                 (0)
#define TIM_CR1_CEN                     (0x01U << TIM_CR1_CEN_Pos)              ///< Counter enable
#define TIM_CR1_UDIS_Pos                (1)
#define TIM_CR1_UDIS                    (0x01U << TIM_CR1_UDIS_Pos)             ///< Update disable
#define TIM_CR1_URS_Pos                 (2)
#define TIM_CR1_URS                     (0x01U << TIM_CR1_URS_Pos)              ///< Update request source
#define TIM_CR1_OPM_Pos                 (3)
#define TIM_CR1_OPM                     (0x01U << TIM_CR1_OPM_Pos)              ///< One pulse mode
#define TIM_CR1_DIR_Pos                 (4)
#define TIM_CR1_DIR                     (0x01U << TIM_CR1_DIR_Pos)              ///< Direction
#define TIM_CR1_CMS_Pos                 (5)
#define TIM_CR1_CMS                     (0x03U << TIM_CR1_CMS_Pos)              ///< CMS[1:0] bits (Center-aligned mode selection)
#define TIM_CR1_CMS_EDGEALIGNED         (0x00U << TIM_CR1_CMS_Pos)              ///< Edge-aligned mode
#define TIM_CR1_CMS_CENTERALIGNED1      (0x01U << TIM_CR1_CMS_Pos)              ///< Center-aligned mode 1
#define TIM_CR1_CMS_CENTERALIGNED2      (0x02U << TIM_CR1_CMS_Pos)              ///< Center-aligned mode 2
#define TIM_CR1_CMS_CENTERALIGNED3      (0x03U << TIM_CR1_CMS_Pos)              ///< Center-aligned mode 3
#define TIM_CR1_ARPEN_Pos               (7)
#define TIM_CR1_ARPEN                   (0x01U << TIM_CR1_ARPEN_Pos)            ///< Auto-reload preload enable
#define TIM_CR1_CKD_Pos                 (8)
#define TIM_CR1_CKD                     (0x03U << TIM_CR1_CKD_Pos)              ///< CKD[1:0] bits (clock division)
#define TIM_CR1_CKD_DIV1                (0x00U << TIM_CR1_CKD_Pos)              ///< Divided by 1
#define TIM_CR1_CKD_DIV2                (0x01U << TIM_CR1_CKD_Pos)              ///< Divided by 2
#define TIM_CR1_CKD_DIV4                (0x02U << TIM_CR1_CKD_Pos)              ///< Divided by 4

////////////////////////////////////////////////////////////////////////////////
/// @brief TIM_CR2 Register Bit Definition
////////////////////////////////////////////////////////////////////////////////
#define TIM_CR2_CCPC_Pos                (0)
#define TIM_CR2_CCPC                    (0x01U << TIM_CR2_CCPC_Pos)             ///< Capture/Compare Preloaded Control
#define TIM_CR2_CCUS_Pos                (2)
#define TIM_CR2_CCUS                    (0x01U << TIM_CR2_CCUS_Pos)             ///< Capture/Compare Control Update Selection
#define TIM_CR2_CCDS_Pos                (3)
#define TIM_CR2_CCDS                    (0x01U << TIM_CR2_CCDS_Pos)             ///< Capture/Compare DMA Selection
#define TIM_CR2_MMS_Pos                 (4)
#define TIM_CR2_MMS                     (0x07U << TIM_CR2_MMS_Pos)              ///< MMS[2:0] bits (Master Mode Selection)
#define TIM_CR2_MMS_RESET               (0x00U << TIM_CR2_MMS_Pos)              ///< Master Mode Select: Reset
#define TIM_CR2_MMS_ENABLE              (0x01U << TIM_CR2_MMS_Pos)              ///< Master Mode Select: Enable
#define TIM_CR2_MMS_UPDATE              (0x02U << TIM_CR2_MMS_Pos)              ///< Master Mode Select: Update
#define TIM_CR2_MMS_OC1                 (0x03U << TIM_CR2_MMS_Pos)              ///< Master Mode Select: OC1
#define TIM_CR2_MMS_OC1REF              (0x04U << TIM_CR2_MMS_Pos)              ///< Master Mode Select: OC1Ref
#define TIM_CR2_MMS_OC2REF              (0x05U << TIM_CR2_MMS_Pos)              ///< Master Mode Select: OC2Ref
#define TIM_CR2_MMS_OC3REF              (0x06U << TIM_CR2_MMS_Pos)              ///< Master Mode Select: OC3Ref
#define TIM_CR2_MMS_OC4REF              (0x07U << TIM_CR2_MMS_Pos)              ///< Master Mode Select: OC4Ref
#define TIM_CR2_TI1S_Pos                (7)
#define TIM_CR2_TI1S                    (0x01U << TIM_CR2_TI1S_Pos)             ///< TI1 Selection
#define TIM_CR2_OIS1_Pos                (8)
#define TIM_CR2_OIS1                    (0x01U << TIM_CR2_OIS1_Pos)             ///< Output Idle state 1 (OC1 output)
#define TIM_CR2_OIS1N_Pos               (9)
#define TIM_CR2_OIS1N                   (0x01U << TIM_CR2_OIS1N_Pos)            ///< Output Idle state 1 (OC1N output)
#define TIM_CR2_OIS2_Pos                (10)
#define TIM_CR2_OIS2                    (0x01U << TIM_CR2_OIS2_Pos)             ///< Output Idle state 2 (OC2 output)
#define TIM_CR2_OIS2N_Pos               (11)
#define TIM_CR2_OIS2N                   (0x01U << TIM_CR2_OIS2N_Pos)            ///< Output Idle state 2 (OC2N output)
#define TIM_CR2_OIS3_Pos                (12)
#define TIM_CR2_OIS3                    (0x01U << TIM_CR2_OIS3_Pos)             ///< Output Idle state 3 (OC3 output)
#define TIM_CR2_OIS3N_Pos               (13)
#define TIM_CR2_OIS3N                   (0x01U << TIM_CR2_OIS3N_Pos)            ///< Output Idle state 3 (OC3N output)
#define TIM_CR2_OIS4_Pos                (14)
#define TIM_CR2_OIS4                    (0x01U << TIM_CR2_OIS4_Pos)             ///< Output Idle state 4 (OC4 output)


#define TIM_CR2_OIS5_Pos                (16)
#define TIM_CR2_OIS5                    (0x01U << TIM_CR2_OIS5_Pos)             ///< Output Idle state 5 (OC5 output)

////////////////////////////////////////////////////////////////////////////////
/// @brief TIM_SMCR Register Bit Definition
////////////////////////////////////////////////////////////////////////////////
#define TIM_SMCR_SMS_Pos                (0)
#define TIM_SMCR_SMS                    (0x07U << TIM_SMCR_SMS_Pos)             ///< SMS[2:0] bits (Slave mode selection)
#define TIM_SMCR_SMS_OFF                (0x00U << TIM_SMCR_SMS_Pos)             ///< Slave Mode select: OFF
#define TIM_SMCR_SMS_ENCODER1           (0x01U << TIM_SMCR_SMS_Pos)             ///< Slave Mode select: Encoder1
#define TIM_SMCR_SMS_ENCODER2           (0x02U << TIM_SMCR_SMS_Pos)             ///< Slave Mode select: Encoder2
#define TIM_SMCR_SMS_ENCODER3           (0x03U << TIM_SMCR_SMS_Pos)             ///< Slave Mode select: Encoder3
#define TIM_SMCR_SMS_RESET              (0x04U << TIM_SMCR_SMS_Pos)             ///< Slave Mode select: Reset
#define TIM_SMCR_SMS_GATED              (0x05U << TIM_SMCR_SMS_Pos)             ///< Slave Mode select: Gated
#define TIM_SMCR_SMS_TRIGGER            (0x06U << TIM_SMCR_SMS_Pos)             ///< Slave Mode select: Trigger
#define TIM_SMCR_SMS_EXTERNAL1          (0x07U << TIM_SMCR_SMS_Pos)             ///< Slave Mode select: External1

#define TIM_SMCR_OCCS_Pos               (3)
#define TIM_SMCR_OCCS                   (0x01U << TIM_SMCR_OCCS_Pos)            ///< Output compare clear selection

#define TIM_SMCR_TS_Pos                 (4)
#define TIM_SMCR_TS                     (0x07U << TIM_SMCR_TS_Pos)              ///< TS[2:0] bits (Trigger selection)
#define TIM_SMCR_TS_ITR0                (0x00U << TIM_SMCR_TS_Pos)              ///< Internal Trigger 0 (ITR0)
#define TIM_SMCR_TS_ITR1                (0x01U << TIM_SMCR_TS_Pos)              ///< Internal Trigger 1 (ITR1)
#define TIM_SMCR_TS_ITR2                (0x02U << TIM_SMCR_TS_Pos)              ///< Internal Trigger 2 (ITR2)
#define TIM_SMCR_TS_ITR3                (0x03U << TIM_SMCR_TS_Pos)              ///< Internal Trigger 3 (ITR3)
#define TIM_SMCR_TS_TI1F_ED             (0x04U << TIM_SMCR_TS_Pos)              ///< TI1 Edge Detector (TI1F_ED)
#define TIM_SMCR_TS_TI1FP1              (0x05U << TIM_SMCR_TS_Pos)              ///< Filtered Timer Input 1 (TI1FP1)
#define TIM_SMCR_TS_TI2FP2              (0x06U << TIM_SMCR_TS_Pos)              ///< Filtered Timer Input 2 (TI2FP2)
#define TIM_SMCR_TS_ETRF                (0x07U << TIM_SMCR_TS_Pos)              ///< External Trigger input (ETRF)
#define TIM_SMCR_MSM_Pos                (7)
#define TIM_SMCR_MSM                    (0x01U << TIM_SMCR_MSM_Pos)             ///< Master/slave mode
#define TIM_SMCR_ETF_Pos                (8)
#define TIM_SMCR_ETF                    (0x0FU << TIM_SMCR_ETF_Pos)             ///< ETF[3:0] bits (External trigger filter)
#define TIM_SMCR_ETF_0                  (0x01U << TIM_SMCR_ETF_Pos)             ///< Bit 0
#define TIM_SMCR_ETF_1                  (0x02U << TIM_SMCR_ETF_Pos)             ///< Bit 1
#define TIM_SMCR_ETF_2                  (0x04U << TIM_SMCR_ETF_Pos)             ///< Bit 2
#define TIM_SMCR_ETF_3                  (0x08U << TIM_SMCR_ETF_Pos)             ///< Bit 3
#define TIM_SMCR_ETPS_Pos               (12)
#define TIM_SMCR_ETPS                   (0x03U << TIM_SMCR_ETPS_Pos)            ///< ETPS[1:0] bits (External trigger prescaler)
#define TIM_SMCR_ETPS_OFF               (0x00U << TIM_SMCR_ETPS_Pos)            ///< Prescaler OFF
#define TIM_SMCR_ETPS_DIV2              (0x01U << TIM_SMCR_ETPS_Pos)            ///< ETRP frequency divided by 2
#define TIM_SMCR_ETPS_DIV4              (0x02U << TIM_SMCR_ETPS_Pos)            ///< ETRP frequency divided by 4
#define TIM_SMCR_ETPS_DIV8              (0x03U << TIM_SMCR_ETPS_Pos)            ///< ETRP frequency divided by 8
#define TIM_SMCR_ECEN_Pos               (14)
#define TIM_SMCR_ECEN                   (0x01U << TIM_SMCR_ECEN_Pos)            ///< External clock enable
#define TIM_SMCR_ETP_Pos                (15)
#define TIM_SMCR_ETP                    (0x01U << TIM_SMCR_ETP_Pos)             ///< External trigger polarity
////////////////////////////////////////////////////////////////////////////////
/// @brief TIM_DIER Register Bit Definition
////////////////////////////////////////////////////////////////////////////////
#define TIM_DIER_UI_Pos                 (0)
#define TIM_DIER_UI                     (0x01U << TIM_DIER_UI_Pos)              ///< Update interrupt enable
#define TIM_DIER_CC1I_Pos               (1)
#define TIM_DIER_CC1I                   (0x01U << TIM_DIER_CC1I_Pos)            ///< Capture/Compare 1 interrupt enable
#define TIM_DIER_CC2I_Pos               (2)
#define TIM_DIER_CC2I                   (0x01U << TIM_DIER_CC2I_Pos)            ///< Capture/Compare 2 interrupt enable
#define TIM_DIER_CC3I_Pos               (3)
#define TIM_DIER_CC3I                   (0x01U << TIM_DIER_CC3I_Pos)            ///< Capture/Compare 3 interrupt enable
#define TIM_DIER_CC4I_Pos               (4)
#define TIM_DIER_CC4I                   (0x01U << TIM_DIER_CC4I_Pos)            ///< Capture/Compare 4 interrupt enable
#define TIM_DIER_COMI_Pos               (5)
#define TIM_DIER_COMI                   (0x01U << TIM_DIER_COMI_Pos)            ///< COM interrupt enable
#define TIM_DIER_TI_Pos                 (6)
#define TIM_DIER_TI                     (0x01U << TIM_DIER_TI_Pos)              ///< Trigger interrupt enable
#define TIM_DIER_BI_Pos                 (7)
#define TIM_DIER_BI                     (0x01U << TIM_DIER_BI_Pos)              ///< Break interrupt enable
#define TIM_DIER_UD_Pos                 (8)
#define TIM_DIER_UD                     (0x01U << TIM_DIER_UD_Pos)              ///< Update DMA request enable
#define TIM_DIER_CC1D_Pos               (9)
#define TIM_DIER_CC1D                   (0x01U << TIM_DIER_CC1D_Pos)            ///< Capture/Compare 1 DMA request enable
#define TIM_DIER_CC2D_Pos               (10)
#define TIM_DIER_CC2D                   (0x01U << TIM_DIER_CC2D_Pos)            ///< Capture/Compare 2 DMA request enable
#define TIM_DIER_CC3D_Pos               (11)
#define TIM_DIER_CC3D                   (0x01U << TIM_DIER_CC3D_Pos)            ///< Capture/Compare 3 DMA request enable
#define TIM_DIER_CC4D_Pos               (12)
#define TIM_DIER_CC4D                   (0x01U << TIM_DIER_CC4D_Pos)            ///< Capture/Compare 4 DMA request enable
#define TIM_DIER_COMD_Pos               (13)
#define TIM_DIER_COMD                   (0x01U << TIM_DIER_COMD_Pos)            ///< COM DMA request enable
#define TIM_DIER_TD_Pos                 (14)
#define TIM_DIER_TD                     (0x01U << TIM_DIER_TD_Pos)              ///< Trigger DMA request enable
#define TIM_DIER_CC5I_Pos               (16)
#define TIM_DIER_CC5I                   (0x01U << TIM_DIER_CC5I_Pos)            ///< Capture/Compare 5 interrupt enable

////////////////////////////////////////////////////////////////////////////////
/// @brief TIM_SR Register Bit Definition
////////////////////////////////////////////////////////////////////////////////
#define TIM_SR_UI_Pos                   (0)
#define TIM_SR_UI                       (0x01U << TIM_SR_UI_Pos)                ///< Update interrupt Flag
#define TIM_SR_CC1I_Pos                 (1)
#define TIM_SR_CC1I                     (0x01U << TIM_SR_CC1I_Pos)              ///< Capture/Compare 1 interrupt Flag
#define TIM_SR_CC2I_Pos                 (2)
#define TIM_SR_CC2I                     (0x01U << TIM_SR_CC2I_Pos)              ///< Capture/Compare 2 interrupt Flag
#define TIM_SR_CC3I_Pos                 (3)
#define TIM_SR_CC3I                     (0x01U << TIM_SR_CC3I_Pos)              ///< Capture/Compare 3 interrupt Flag
#define TIM_SR_CC4I_Pos                 (4)
#define TIM_SR_CC4I                     (0x01U << TIM_SR_CC4I_Pos)              ///< Capture/Compare 4 interrupt Flag
#define TIM_SR_COMI_Pos                 (5)
#define TIM_SR_COMI                     (0x01U << TIM_SR_COMI_Pos)              ///< COM interrupt Flag
#define TIM_SR_TI_Pos                   (6)
#define TIM_SR_TI                       (0x01U << TIM_SR_TI_Pos)                ///< Trigger interrupt Flag
#define TIM_SR_BI_Pos                   (7)
#define TIM_SR_BI                       (0x01U << TIM_SR_BI_Pos)                ///< Break interrupt Flag
#define TIM_SR_CC1O_Pos                 (9)
#define TIM_SR_CC1O                     (0x01U << TIM_SR_CC1O_Pos)              ///< Capture/Compare 1 Overcapture Flag
#define TIM_SR_CC2O_Pos                 (10)
#define TIM_SR_CC2O                     (0x01U << TIM_SR_CC2O_Pos)              ///< Capture/Compare 2 Overcapture Flag
#define TIM_SR_CC3O_Pos                 (11)
#define TIM_SR_CC3O                     (0x01U << TIM_SR_CC3O_Pos)              ///< Capture/Compare 3 Overcapture Flag
#define TIM_SR_CC4O_Pos                 (12)
#define TIM_SR_CC4O                     (0x01U << TIM_SR_CC4O_Pos)              ///< Capture/Compare 4 Overcapture Flag

#define TIM_SR_CC5I_Pos                 (16)
#define TIM_SR_CC5I                     (0x01U << TIM_SR_CC5I_Pos)              ///< Capture/Compare 5 interrupt Flag

////////////////////////////////////////////////////////////////////////////////
/// @brief TIM_EGR Register Bit Definition
////////////////////////////////////////////////////////////////////////////////
#define TIM_EGR_UG_Pos                  (0)
#define TIM_EGR_UG                      (0x01U << TIM_EGR_UG_Pos)               ///< Update Generation
#define TIM_EGR_CC1G_Pos                (1)
#define TIM_EGR_CC1G                    (0x01U << TIM_EGR_CC1G_Pos)             ///< Capture/Compare 1 Generation
#define TIM_EGR_CC2G_Pos                (2)
#define TIM_EGR_CC2G                    (0x01U << TIM_EGR_CC2G_Pos)             ///< Capture/Compare 2 Generation
#define TIM_EGR_CC3G_Pos                (3)
#define TIM_EGR_CC3G                    (0x01U << TIM_EGR_CC3G_Pos)             ///< Capture/Compare 3 Generation
#define TIM_EGR_CC4G_Pos                (4)
#define TIM_EGR_CC4G                    (0x01U << TIM_EGR_CC4G_Pos)             ///< Capture/Compare 4 Generation
#define TIM_EGR_COMG_Pos                (5)
#define TIM_EGR_COMG                    (0x01U << TIM_EGR_COMG_Pos)             ///< Capture/Compare Control Update Generation
#define TIM_EGR_TG_Pos                  (6)
#define TIM_EGR_TG                      (0x01U << TIM_EGR_TG_Pos)               ///< Trigger Generation
#define TIM_EGR_BG_Pos                  (7)
#define TIM_EGR_BG                      (0x01U << TIM_EGR_BG_Pos)               ///< Break Generation

#define TIM_EGR_CC5G_Pos                (16)
#define TIM_EGR_CC5G                    (0x01U << TIM_EGR_CC5G_Pos)             ///< Capture/Compare 5 Generation

////////////////////////////////////////////////////////////////////////////////
/// @brief TIM_CCMR1 Register Bit Definition
////////////////////////////////////////////////////////////////////////////////
#define TIM_CCMR1_CC1S_Pos              (0)
#define TIM_CCMR1_CC1S                  (0x03U << TIM_CCMR1_CC1S_Pos)           ///< CC1S[1:0] bits (Capture/Compare 1 Selection)
#define TIM_CCMR1_CC1S_OC               (0x00U << TIM_CCMR1_CC1S_Pos)           ///< Channel is configured as output
#define TIM_CCMR1_CC1S_DIRECTTI         (0x01U << TIM_CCMR1_CC1S_Pos)           ///< Channel is configured as input, IC1 is mapped on TI1
#define TIM_CCMR1_CC1S_INDIRECTTI       (0x02U << TIM_CCMR1_CC1S_Pos)           ///< Channel is configured as input, IC1 is mapped on TI2
#define TIM_CCMR1_CC1S_TRC              (0x03U << TIM_CCMR1_CC1S_Pos)           ///< Channel is configured as input, IC1 is mapped on TRC
#define TIM_CCMR1_OC1FEN_Pos            (2)
#define TIM_CCMR1_OC1FEN                (0x01U << TIM_CCMR1_OC1FEN_Pos)         ///< Output Compare 1 Fast enable

#define TIM_CCMR1_OC1PEN_Pos            (3)
#define TIM_CCMR1_OC1PEN                (0x01U << TIM_CCMR1_OC1PEN_Pos)         ///< Output Compare 1 Preload enable
#define TIM_CCMR1_OC1M_Pos              (4)
#define TIM_CCMR1_OC1M                  (0x07U << TIM_CCMR1_OC1M_Pos)           ///< OC1M[2:0] bits (Output Compare 1 Mode)
#define TIM_CCMR1_OC1M_TIMING           (0x00U << TIM_CCMR1_OC1M_Pos)           ///< Timing
#define TIM_CCMR1_OC1M_ACTIVE           (0x01U << TIM_CCMR1_OC1M_Pos)           ///< Active
#define TIM_CCMR1_OC1M_INACTIVE         (0x02U << TIM_CCMR1_OC1M_Pos)           ///< Inactive
#define TIM_CCMR1_OC1M_TOGGLE           (0x03U << TIM_CCMR1_OC1M_Pos)           ///< Toggle
#define TIM_CCMR1_OC1M_FORCEINACTIVE    (0x04U << TIM_CCMR1_OC1M_Pos)           ///< Forceinactive
#define TIM_CCMR1_OC1M_FORCEACTIVE      (0x05U << TIM_CCMR1_OC1M_Pos)           ///< Forceactive
#define TIM_CCMR1_OC1M_PWM1             (0x06U << TIM_CCMR1_OC1M_Pos)           ///< PWM1
#define TIM_CCMR1_OC1M_PWM2             (0x07U << TIM_CCMR1_OC1M_Pos)           ///< PWM2

#define TIM_CCMR1_OC1CEN_Pos            (7)
#define TIM_CCMR1_OC1CEN                (0x01U << TIM_CCMR1_OC1CEN_Pos)         ///< Output Compare 1Clear Enable
#define TIM_CCMR1_CC2S_Pos              (8)
#define TIM_CCMR1_CC2S                  (0x03U << TIM_CCMR1_CC2S_Pos)           ///< CC2S[1:0] bits (Capture/Compare 2 Selection)
#define TIM_CCMR1_CC2S_OC               (0x00U << TIM_CCMR1_CC2S_Pos)           ///< Channel is configured as output
#define TIM_CCMR1_CC2S_DIRECTTI         (0x01U << TIM_CCMR1_CC2S_Pos)           ///< Channel is configured as input, IC2 is mapped on TI2
#define TIM_CCMR1_CC2S_INDIRECTTI       (0x02U << TIM_CCMR1_CC2S_Pos)           ///< Channel is configured as input, IC2 is mapped on TI1
#define TIM_CCMR1_CC2S_TRC              (0x03U << TIM_CCMR1_CC2S_Pos)           ///< Channel is configured as input, IC2 is mapped on TRC
#define TIM_CCMR1_OC2FEN_Pos            (10)
#define TIM_CCMR1_OC2FEN                (0x01U << TIM_CCMR1_OC2FEN_Pos)         ///< Output Compare 2 Fast enable
#define TIM_CCMR1_OC2PEN_Pos            (11)
#define TIM_CCMR1_OC2PEN                (0x01U << TIM_CCMR1_OC2PEN_Pos)         ///< Output Compare 2 Preload enable
#define TIM_CCMR1_OC2M_Pos              (12)
#define TIM_CCMR1_OC2M                  (0x07U << TIM_CCMR1_OC2M_Pos)           ///< OC2M[2:0] bits (Output Compare 2 Mode)
#define TIM_CCMR1_OC2M_TIMING           (0x00U << TIM_CCMR1_OC2M_Pos)           ///< Timing
#define TIM_CCMR1_OC2M_ACTIVE           (0x01U << TIM_CCMR1_OC2M_Pos)           ///< Active
#define TIM_CCMR1_OC2M_INACTIVE         (0x02U << TIM_CCMR1_OC2M_Pos)           ///< Inactive
#define TIM_CCMR1_OC2M_TOGGLE           (0x03U << TIM_CCMR1_OC2M_Pos)           ///< Toggle
#define TIM_CCMR1_OC2M_FORCEINACTIVE    (0x04U << TIM_CCMR1_OC2M_Pos)           ///< Forceinactive
#define TIM_CCMR1_OC2M_FORCEACTIVE      (0x05U << TIM_CCMR1_OC2M_Pos)           ///< Forceactive
#define TIM_CCMR1_OC2M_PWM1             (0x06U << TIM_CCMR1_OC2M_Pos)           ///< PWM1
#define TIM_CCMR1_OC2M_PWM2             (0x07U << TIM_CCMR1_OC2M_Pos)           ///< PWM2
#define TIM_CCMR1_OC2CEN_Pos            (15)
#define TIM_CCMR1_OC2CEN                (0x01U << TIM_CCMR1_OC2CEN_Pos)         ///< Output Compare 2 Clear Enable

#define TIM_CCMR1_IC1PSC_Pos            (2)
#define TIM_CCMR1_IC1PSC                (0x03U << TIM_CCMR1_IC1PSC_Pos)         ///< IC1PSC[1:0] bits (Input Capture 1 Prescaler)
#define TIM_CCMR1_IC1PSC_DIV1           (0x00U << TIM_CCMR1_IC1PSC_Pos)         ///< No Prescaler
#define TIM_CCMR1_IC1PSC_DIV2           (0x01U << TIM_CCMR1_IC1PSC_Pos)         ///< Capture is done once every 2 events
#define TIM_CCMR1_IC1PSC_DIV4           (0x02U << TIM_CCMR1_IC1PSC_Pos)         ///< Capture is done once every 4 events
#define TIM_CCMR1_IC1PSC_DIV8           (0x03U << TIM_CCMR1_IC1PSC_Pos)         ///< Capture is done once every 8 events
#define TIM_CCMR1_IC1F_Pos              (4)
#define TIM_CCMR1_IC1F                  (0x0FU << TIM_CCMR1_IC1F_Pos)           ///< IC1F[3:0] bits (Input Capture 1 Filter)
#define TIM_CCMR1_IC1F_0                (0x01U << TIM_CCMR1_IC1F_Pos)           ///< Bit 0
#define TIM_CCMR1_IC1F_1                (0x02U << TIM_CCMR1_IC1F_Pos)           ///< Bit 1
#define TIM_CCMR1_IC1F_2                (0x04U << TIM_CCMR1_IC1F_Pos)           ///< Bit 2
#define TIM_CCMR1_IC1F_3                (0x08U << TIM_CCMR1_IC1F_Pos)           ///< Bit 3

#define TIM_CCMR1_IC2PSC_Pos            (10)
#define TIM_CCMR1_IC2PSC                (0x03U << TIM_CCMR1_IC2PSC_Pos)         ///< IC2PSC[1:0] bits (Input Capture 2 Prescaler)
#define TIM_CCMR1_IC2PSC_DIV1           (0x00U << TIM_CCMR1_IC2PSC_Pos)         ///< No Prescaler
#define TIM_CCMR1_IC2PSC_DIV2           (0x01U << TIM_CCMR1_IC2PSC_Pos)         ///< Capture is done once every 2 events
#define TIM_CCMR1_IC2PSC_DIV4           (0x02U << TIM_CCMR1_IC2PSC_Pos)         ///< Capture is done once every 4 events
#define TIM_CCMR1_IC2PSC_DIV8           (0x03U << TIM_CCMR1_IC2PSC_Pos)         ///< Capture is done once every 8 events
#define TIM_CCMR1_IC2F_Pos              (12)
#define TIM_CCMR1_IC2F                  (0x0FU << TIM_CCMR1_IC2F_Pos)           ///< IC2F[3:0] bits (Input Capture 2 Filter)
#define TIM_CCMR1_IC2F_0                (0x01U << TIM_CCMR1_IC2F_Pos)           ///< Bit 0
#define TIM_CCMR1_IC2F_1                (0x02U << TIM_CCMR1_IC2F_Pos)           ///< Bit 1
#define TIM_CCMR1_IC2F_2                (0x04U << TIM_CCMR1_IC2F_Pos)           ///< Bit 2
#define TIM_CCMR1_IC2F_3                (0x08U << TIM_CCMR1_IC2F_Pos)           ///< Bit 3

////////////////////////////////////////////////////////////////////////////////
/// @brief TIM_CCMR2 Register Bit Definition
////////////////////////////////////////////////////////////////////////////////
#define TIM_CCMR2_CC3S_Pos              (0)
#define TIM_CCMR2_CC3S                  (0x03U << TIM_CCMR2_CC3S_Pos)           ///< CC3S[1:0] bits (Capture/Compare 3 Selection)
#define TIM_CCMR2_CC3S_OC               (0x00U << TIM_CCMR2_CC3S_Pos)           ///< Channel is configured as output
#define TIM_CCMR2_CC3S_DIRECTTI         (0x01U << TIM_CCMR2_CC3S_Pos)           ///< Channel is configured as input, IC3 is mapped on TI3
#define TIM_CCMR2_CC3S_INDIRECTTI       (0x02U << TIM_CCMR2_CC3S_Pos)           ///< Channel is configured as input, IC3 is mapped on TI4
#define TIM_CCMR2_CC3S_TRC              (0x03U << TIM_CCMR2_CC3S_Pos)           ///< Channel is configured as input, IC3 is mapped on TRC
#define TIM_CCMR2_OC3FEN_Pos            (2)
#define TIM_CCMR2_OC3FEN                (0x01U << TIM_CCMR2_OC3FEN_Pos)         ///< Output Compare 3 Fast enable
#define TIM_CCMR2_IC3PSC_Pos            (2)
#define TIM_CCMR2_IC3PSC                (0x03U << TIM_CCMR2_IC3PSC_Pos)         ///< IC3PSC[1:0] bits (Input Capture 3 Prescaler)
#define TIM_CCMR2_IC3PSC_DIV1           (0x00U << TIM_CCMR2_IC3PSC_Pos)         ///< No Prescaler
#define TIM_CCMR2_IC3PSC_DIV2           (0x01U << TIM_CCMR2_IC3PSC_Pos)         ///< Capture is done once every 2 events
#define TIM_CCMR2_IC3PSC_DIV4           (0x02U << TIM_CCMR2_IC3PSC_Pos)         ///< Capture is done once every 4 events
#define TIM_CCMR2_IC3PSC_DIV8           (0x03U << TIM_CCMR2_IC3PSC_Pos)         ///< Capture is done once every 8 events
#define TIM_CCMR2_OC3PEN_Pos            (3)
#define TIM_CCMR2_OC3PEN                (0x01U << TIM_CCMR2_OC3PEN_Pos)         ///< Output Compare 3 Preload enable
#define TIM_CCMR2_OC3M_Pos              (4)
#define TIM_CCMR2_OC3M                  (0x07U << TIM_CCMR2_OC3M_Pos)           ///< OC3M[2:0] bits (Output Compare 3 Mode)
#define TIM_CCMR2_OC3M_TIMING           (0x00U << TIM_CCMR2_OC3M_Pos)           ///< Timing
#define TIM_CCMR2_OC3M_ACTIVE           (0x01U << TIM_CCMR2_OC3M_Pos)           ///< Active
#define TIM_CCMR2_OC3M_INACTIVE         (0x02U << TIM_CCMR2_OC3M_Pos)           ///< Inactive
#define TIM_CCMR2_OC3M_TOGGLE           (0x03U << TIM_CCMR2_OC3M_Pos)           ///< Toggle
#define TIM_CCMR2_OC3M_FORCEINACTIVE    (0x04U << TIM_CCMR2_OC3M_Pos)           ///< Forceinactive
#define TIM_CCMR2_OC3M_FORCEACTIVE      (0x05U << TIM_CCMR2_OC3M_Pos)           ///< Forceactive
#define TIM_CCMR2_OC3M_PWM1             (0x06U << TIM_CCMR2_OC3M_Pos)           ///< PWM1
#define TIM_CCMR2_OC3M_PWM2             (0x07U << TIM_CCMR2_OC3M_Pos)           ///< PWM2
#define TIM_CCMR2_IC3F_Pos              (4)
#define TIM_CCMR2_IC3F                  (0x0FU << TIM_CCMR2_IC3F_Pos)           ///< IC3F[3:0] bits (Input Capture 3 Filter)
#define TIM_CCMR2_IC3F_0                (0x01U << TIM_CCMR2_IC3F_Pos)           ///< Bit 0
#define TIM_CCMR2_IC3F_1                (0x02U << TIM_CCMR2_IC3F_Pos)           ///< Bit 1
#define TIM_CCMR2_IC3F_2                (0x04U << TIM_CCMR2_IC3F_Pos)           ///< Bit 2
#define TIM_CCMR2_IC3F_3                (0x08U << TIM_CCMR2_IC3F_Pos)           ///< Bit 3
#define TIM_CCMR2_OC3CEN_Pos            (7)
#define TIM_CCMR2_OC3CEN                (0x01U << TIM_CCMR2_OC3CEN_Pos)         ///< Output Compare 3 Clear Enable
#define TIM_CCMR2_CC4S_Pos              (8)
#define TIM_CCMR2_CC4S                  (0x03U << TIM_CCMR2_CC4S_Pos)           ///< CC4S[1:0] bits (Capture/Compare 4 Selection)
#define TIM_CCMR2_CC4S_OC               (0x00U << TIM_CCMR2_CC4S_Pos)           ///< Channel is configured as output
#define TIM_CCMR2_CC4S_DIRECTTI         (0x01U << TIM_CCMR2_CC4S_Pos)           ///< Channel is configured as input, IC4 is mapped on TI4
#define TIM_CCMR2_CC4S_INDIRECTTI       (0x02U << TIM_CCMR2_CC4S_Pos)           ///< Channel is configured as input, IC4 is mapped on TI3
#define TIM_CCMR2_CC4S_TRC              (0x03U << TIM_CCMR2_CC4S_Pos)           ///< Channel is configured as input, IC4 is mapped on TRC
#define TIM_CCMR2_OC4FEN_Pos            (10)
#define TIM_CCMR2_OC4FEN                (0x01U << TIM_CCMR2_OC4FEN_Pos)         ///< Output Compare 4 Fast enable
#define TIM_CCMR2_OC4PEN_Pos            (11)
#define TIM_CCMR2_OC4PEN                (0x01U << TIM_CCMR2_OC4PEN_Pos)         ///< Output Compare 4 Preload enable
#define TIM_CCMR2_OC4M_Pos              (12)
#define TIM_CCMR2_OC4M                  (0x07U << TIM_CCMR2_OC4M_Pos)           ///< OC4M[2:0] bits (Output Compare 4 Mode)
#define TIM_CCMR2_OC4M_TIMING           (0x00U << TIM_CCMR2_OC4M_Pos)           ///< Timing
#define TIM_CCMR2_OC4M_ACTIVE           (0x01U << TIM_CCMR2_OC4M_Pos)           ///< Active
#define TIM_CCMR2_OC4M_INACTIVE         (0x02U << TIM_CCMR2_OC4M_Pos)           ///< Inactive
#define TIM_CCMR2_OC4M_TOGGLE           (0x03U << TIM_CCMR2_OC4M_Pos)           ///< Toggle
#define TIM_CCMR2_OC4M_FORCEINACTIVE    (0x04U << TIM_CCMR2_OC4M_Pos)           ///< Forceinactive
#define TIM_CCMR2_OC4M_FORCEACTIVE      (0x05U << TIM_CCMR2_OC4M_Pos)           ///< Forceactive
#define TIM_CCMR2_OC4M_PWM1             (0x06U << TIM_CCMR2_OC4M_Pos)           ///< PWM1
#define TIM_CCMR2_OC4M_PWM2             (0x07U << TIM_CCMR2_OC4M_Pos)           ///< PWM2
#define TIM_CCMR2_OC4CEN_Pos            (15)
#define TIM_CCMR2_OC4CEN                (0x01U << TIM_CCMR2_OC4CEN_Pos)         ///< Output Compare 4 Clear Enable
#define TIM_CCMR2_IC4PSC_Pos            (10)
#define TIM_CCMR2_IC4PSC                (0x03U << TIM_CCMR2_IC4PSC_Pos)         ///< IC4PSC[1:0] bits (Input Capture 4 Prescaler)
#define TIM_CCMR2_IC4PSC_DIV1           (0x00U << TIM_CCMR2_IC4PSC_Pos)         ///< No Prescaler
#define TIM_CCMR2_IC4PSC_DIV2           (0x01U << TIM_CCMR2_IC4PSC_Pos)         ///< Capture is done once every 2 events
#define TIM_CCMR2_IC4PSC_DIV4           (0x02U << TIM_CCMR2_IC4PSC_Pos)         ///< Capture is done once every 4 events
#define TIM_CCMR2_IC4PSC_DIV8           (0x03U << TIM_CCMR2_IC4PSC_Pos)         ///< Capture is done once every 8 events
#define TIM_CCMR2_IC4F_Pos              (12)
#define TIM_CCMR2_IC4F                  (0x0FU << TIM_CCMR2_IC4F_Pos)           ///< IC4F[3:0] bits (Input Capture 4 Filter)
#define TIM_CCMR2_IC4F_0                (0x01U << TIM_CCMR2_IC4F_Pos)           ///< Bit 0
#define TIM_CCMR2_IC4F_1                (0x02U << TIM_CCMR2_IC4F_Pos)           ///< Bit 1
#define TIM_CCMR2_IC4F_2                (0x04U << TIM_CCMR2_IC4F_Pos)           ///< Bit 2
#define TIM_CCMR2_IC4F_3                (0x08U << TIM_CCMR2_IC4F_Pos)           ///< Bit 3

////////////////////////////////////////////////////////////////////////////////
/// @brief TIM_CCER Register Bit Definition
////////////////////////////////////////////////////////////////////////////////
#define TIM_CCER_CC1EN_Pos              (0)
#define TIM_CCER_CC1EN                  (0x01U << TIM_CCER_CC1EN_Pos)           ///< Capture/Compare 1 output enable
#define TIM_CCER_CC1P_Pos               (1)
#define TIM_CCER_CC1P                   (0x01U << TIM_CCER_CC1P_Pos)            ///< Capture/Compare 1 output Polarity
#define TIM_CCER_CC1NEN_Pos             (2)
#define TIM_CCER_CC1NEN                 (0x01U << TIM_CCER_CC1NEN_Pos)          ///< Capture/Compare 1 Complementary output enable
#define TIM_CCER_CC1NP_Pos              (3)
#define TIM_CCER_CC1NP                  (0x01U << TIM_CCER_CC1NP_Pos)           ///< Capture/Compare 1 Complementary output Polarity
#define TIM_CCER_CC2EN_Pos              (4)
#define TIM_CCER_CC2EN                  (0x01U << TIM_CCER_CC2EN_Pos)           ///< Capture/Compare 2 output enable
#define TIM_CCER_CC2P_Pos               (5)
#define TIM_CCER_CC2P                   (0x01U << TIM_CCER_CC2P_Pos)            ///< Capture/Compare 2 output Polarity
#define TIM_CCER_CC2NEN_Pos             (6)
#define TIM_CCER_CC2NEN                 (0x01U << TIM_CCER_CC2NEN_Pos)          ///< Capture/Compare 2 Complementary output enable
#define TIM_CCER_CC2NP_Pos              (7)
#define TIM_CCER_CC2NP                  (0x01U << TIM_CCER_CC2NP_Pos)           ///< Capture/Compare 2 Complementary output Polarity
#define TIM_CCER_CC3EN_Pos              (8)
#define TIM_CCER_CC3EN                  (0x01U << TIM_CCER_CC3EN_Pos)           ///< Capture/Compare 3 output enable
#define TIM_CCER_CC3P_Pos               (9)
#define TIM_CCER_CC3P                   (0x01U << TIM_CCER_CC3P_Pos)            ///< Capture/Compare 3 output Polarity
#define TIM_CCER_CC3NEN_Pos             (10)
#define TIM_CCER_CC3NEN                 (0x01U << TIM_CCER_CC3NEN_Pos)          ///< Capture/Compare 3 Complementary output enable
#define TIM_CCER_CC3NP_Pos              (11)
#define TIM_CCER_CC3NP                  (0x01U << TIM_CCER_CC3NP_Pos)           ///< Capture/Compare 3 Complementary output Polarity
#define TIM_CCER_CC4EN_Pos              (12)
#define TIM_CCER_CC4EN                  (0x01U << TIM_CCER_CC4EN_Pos)           ///< Capture/Compare 4 output enable
#define TIM_CCER_CC4P_Pos               (13)
#define TIM_CCER_CC4P                   (0x01U << TIM_CCER_CC4P_Pos)            ///< Capture/Compare 4 output Polarity
#define TIM_CCER_CC4NP_Pos              (15)
#define TIM_CCER_CC4NP                  (0x01U << TIM_CCER_CC4NP_Pos)           ///< Capture/Compare 4 complementary output polarity

#define TIM_CCER_CC5EN_Pos              (16)
#define TIM_CCER_CC5EN                  (0x01U << TIM_CCER_CC5EN_Pos)           ///< Capture/Compare 5 output enable
#define TIM_CCER_CC5P_Pos               (17)
#define TIM_CCER_CC5P                   (0x01U << TIM_CCER_CC5P_Pos)            ///< Capture/Compare 5 output Polarity

////////////////////////////////////////////////////////////////////////////////
/// @brief TIM_CNT Register Bit Definition
////////////////////////////////////////////////////////////////////////////////
#define TIM_CNT_CNT                     (0xFFFFU)                               ///< Counter Value


////////////////////////////////////////////////////////////////////////////////
/// @brief TIM_PSC Register Bit Definition
////////////////////////////////////////////////////////////////////////////////
#define TIM_PSC_PSC                     (0xFFFFU)                               ///< Prescaler Value

////////////////////////////////////////////////////////////////////////////////
/// @brief TIM_ARR Register Bit Definition
////////////////////////////////////////////////////////////////////////////////
#define TIM_ARR_ARR                     (0xFFFFU)                               ///< actual auto-reload Value


////////////////////////////////////////////////////////////////////////////////
/// @brief TIM_RCR Register Bit Definition
////////////////////////////////////////////////////////////////////////////////
#define TIM_RCR_REP                     (0xFFU)                                 ///< Repetition Counter Value

#define TIM_RCR_REP_CNT_Pos             (8)
#define TIM_RCR_REP_CNT                 (0xFFU << TIM_RCR_REP_CNT_Pos)          ///< Repetition counter value of real-time writing

////////////////////////////////////////////////////////////////////////////////
/// @brief TIM_CCR1 Register Bit Definition
////////////////////////////////////////////////////////////////////////////////
#define TIM_CCR1_CCR1                  (0xFFFFU)                               ///< Capture/Compare 1 Value


////////////////////////////////////////////////////////////////////////////////
/// @brief TIM_CCR2 Register Bit Definition
////////////////////////////////////////////////////////////////////////////////
#define TIM_CCR2_CCR2                  (0xFFFFU)                               ///< Capture/Compare 2 Value


////////////////////////////////////////////////////////////////////////////////
/// @brief TIM_CCR3 Register Bit Definition
////////////////////////////////////////////////////////////////////////////////
#define TIM_CCR3_CCR3                  (0xFFFFU)                               ///< Capture/Compare 3 Value


////////////////////////////////////////////////////////////////////////////////
/// @brief TIM_CCR4 Register Bit Definition
////////////////////////////////////////////////////////////////////////////////
#define TIM_CCR4_CCR4                  (0xFFFFU)                               ///< Capture/Compare 4 Value


////////////////////////////////////////////////////////////////////////////////
/// @brief TIM_BDTR Register Bit Definition
////////////////////////////////////////////////////////////////////////////////
#define TIM_BDTR_DTG_Pos                (0)
#define TIM_BDTR_DTG                    (0xFFU << TIM_BDTR_DTG_Pos)             ///< DTG[0:7] bits (Dead-Time Generator set-up)
#define TIM_BDTR_DTG_0                  (0x01U << TIM_BDTR_DTG_Pos)             ///< Bit 0
#define TIM_BDTR_DTG_1                  (0x02U << TIM_BDTR_DTG_Pos)             ///< Bit 1
#define TIM_BDTR_DTG_2                  (0x04U << TIM_BDTR_DTG_Pos)             ///< Bit 2
#define TIM_BDTR_DTG_3                  (0x08U << TIM_BDTR_DTG_Pos)             ///< Bit 3
#define TIM_BDTR_DTG_4                  (0x10U << TIM_BDTR_DTG_Pos)             ///< Bit 4
#define TIM_BDTR_DTG_5                  (0x20U << TIM_BDTR_DTG_Pos)             ///< Bit 5
#define TIM_BDTR_DTG_6                  (0x40U << TIM_BDTR_DTG_Pos)             ///< Bit 6
#define TIM_BDTR_DTG_7                  (0x80U << TIM_BDTR_DTG_Pos)             ///< Bit 7
#define TIM_BDTR_LOCK_Pos               (8)
#define TIM_BDTR_LOCK                   (0x03U << TIM_BDTR_LOCK_Pos)            ///< LOCK[1:0] bits (Lock Configuration)
#define TIM_BDTR_LOCK_OFF               (0x00U << TIM_BDTR_LOCK_Pos)            ///< Lock Off
#define TIM_BDTR_LOCK_1                 (0x01U << TIM_BDTR_LOCK_Pos)            ///< Lock Level 1
#define TIM_BDTR_LOCK_2                 (0x02U << TIM_BDTR_LOCK_Pos)            ///< Lock Level 2
#define TIM_BDTR_LOCK_3                 (0x03U << TIM_BDTR_LOCK_Pos)            ///< Lock Level 3
#define TIM_BDTR_OSSI_Pos               (10)
#define TIM_BDTR_OSSI                   (0x01U << TIM_BDTR_OSSI_Pos)            ///< Off-State Selection for Idle mode
#define TIM_BDTR_OSSR_Pos               (11)
#define TIM_BDTR_OSSR                   (0x01U << TIM_BDTR_OSSR_Pos)            ///< Off-State Selection for Run mode
#define TIM_BDTR_BKEN_Pos               (12)
#define TIM_BDTR_BKEN                   (0x01U << TIM_BDTR_BKEN_Pos)            ///< Break enable
#define TIM_BDTR_BKP_Pos                (13)
#define TIM_BDTR_BKP                    (0x01U << TIM_BDTR_BKP_Pos)             ///< Break Polarity
#define TIM_BDTR_AOEN_Pos               (14)
#define TIM_BDTR_AOEN                   (0x01U << TIM_BDTR_AOEN_Pos)            ///< Automatic Output enable
#define TIM_BDTR_MOEN_Pos               (15)
#define TIM_BDTR_MOEN                   (0x01U << TIM_BDTR_MOEN_Pos)            ///< Main Output enable

#define TIM_BDTR_DOEN_Pos               (16)
#define TIM_BDTR_DOEN                   (0x01U << TIM_BDTR_DOEN_Pos)            ///< Direct Output enable
////////////////////////////////////////////////////////////////////////////////
/// @brief TIM_DCR Register Bit Definition
////////////////////////////////////////////////////////////////////////////////
#define TIM_DCR_DBA_Pos                 (0)
#define TIM_DCR_DBA                     (0x1FU << TIM_DCR_DBA_Pos)              ///< DBA[4:0] bits (DMA Base Address)
#define TIM_DCR_DBA_0                   (0x01U << TIM_DCR_DBA_Pos)              ///< Bit 0
#define TIM_DCR_DBA_1                   (0x02U << TIM_DCR_DBA_Pos)              ///< Bit 1
#define TIM_DCR_DBA_2                   (0x04U << TIM_DCR_DBA_Pos)              ///< Bit 2
#define TIM_DCR_DBA_3                   (0x08U << TIM_DCR_DBA_Pos)              ///< Bit 3
#define TIM_DCR_DBA_4                   (0x10U << TIM_DCR_DBA_Pos)              ///< Bit 4
#define TIM_DCR_DBL_Pos                 (8)
#define TIM_DCR_DBL                     (0x1FU << TIM_DCR_DBL_Pos)              ///< DBL[4:0] bits (DMA Burst Length)
#define TIM_DCR_DBL_0                   (0x01U << TIM_DCR_DBL_Pos)              ///< Bit 0
#define TIM_DCR_DBL_1                   (0x02U << TIM_DCR_DBL_Pos)              ///< Bit 1
#define TIM_DCR_DBL_2                   (0x04U << TIM_DCR_DBL_Pos)              ///< Bit 2
#define TIM_DCR_DBL_3                   (0x08U << TIM_DCR_DBL_Pos)              ///< Bit 3
#define TIM_DCR_DBL_4                   (0x10U << TIM_DCR_DBL_Pos)              ///< Bit 4

////////////////////////////////////////////////////////////////////////////////
/// @brief TIM_DMAR Register Bit Definition
////////////////////////////////////////////////////////////////////////////////
#define TIM_DMAR_DMAB                   (0xFFFFU)                               ///< DMA register for burst accesses

////////////////////////////////////////////////////////////////////////////////
/// @brief TIM_CCMR3 Register Bit Definition
////////////////////////////////////////////////////////////////////////////////
#define TIM_CCMR3_OC5FEN_Pos        (2)
#define TIM_CCMR3_OC5FEN            (0x01U << TIM_CCMR3_OC5FEN_Pos)         ///< Output Compare 5 Fast enable
#define TIM_CCMR3_OC5PEN_Pos        (3)
#define TIM_CCMR3_OC5PEN            (0x01U << TIM_CCMR3_OC5PEN_Pos)         ///< Output Compare 5 Preload enable
#define TIM_CCMR3_OC5M_Pos          (4)
#define TIM_CCMR3_OC5M              (0x07U << TIM_CCMR3_OC5M_Pos)           ///< OC5M[2:0] bits (Output Compare 5 Mode)

#define TIM_CCMR3_OC5CEN_Pos        (7)
#define TIM_CCMR3_OC5CEN            (0x01U << TIM_CCMR3_OC5CEN_Pos)         ///< Output Compare 5 Clear Enable
////////////////////////////////////////////////////////////////////////////////
/// @brief TIM_CCR5 Register Bit Definition
////////////////////////////////////////////////////////////////////////////////
#define TIM_CCR5_CCR5               (0xFFFF)                                ///< Capture/Compare 5 Value

////////////////////////////////////////////////////////////////////////////////
/// @brief TIM_PDER Register Bit Definition
////////////////////////////////////////////////////////////////////////////////
#define TIM_PDER_CCDREPE_Pos        (0)
#define TIM_PDER_CCDREPE            (0x01U << TIM_PDER_CCDREPE_Pos)         ///< DMA request flow enable
#define TIM_PDER_CCR1SHIFTEN_Pos    (1)
#define TIM_PDER_CCR1SHIFTEN        (0x01U << TIM_PDER_CCR1SHIFTEN_Pos)     ///< CCR1 pwm shift enable
#define TIM_PDER_CCR2SHIFTEN_Pos    (2)
#define TIM_PDER_CCR2SHIFTEN        (0x01U << TIM_PDER_CCR2SHIFTEN_Pos)     ///< CCR2 pwm shift enable
#define TIM_PDER_CCR3SHIFTEN_Pos    (3)
#define TIM_PDER_CCR3SHIFTEN        (0x01U << TIM_PDER_CCR3SHIFTEN_Pos)     ///< CCR3 pwm shift enable
#define TIM_PDER_CCR4SHIFTEN_Pos    (4)
#define TIM_PDER_CCR4SHIFTEN        (0x01U << TIM_PDER_CCR4SHIFTEN_Pos)     ///< CCR4 pwm shift enable
#define TIM_PDER_CCR5SHIFTEN_Pos    (5)
#define TIM_PDER_CCR5SHIFTEN        (0x01U << TIM_PDER_CCR5SHIFTEN_Pos)     ///< CCR5 pwm shift enable

////////////////////////////////////////////////////////////////////////////////
/// @brief TIM_CCR1FALL Register Bit Definition
////////////////////////////////////////////////////////////////////////////////
#define TIM_CCR1FALL_CCR1FALL       (0xFFFFU)                               ///< Capture/compare value for ch1 when counting down in PWM center-aligned mode

////////////////////////////////////////////////////////////////////////////////
/// @brief TIM_CCR2FALL Register Bit Definition
////////////////////////////////////////////////////////////////////////////////
#define TIM_CCR2FALL_CCR2FALL       (0xFFFFU)                               ///< Capture/compare value for ch2 when counting down in PWM center-aligned mode

////////////////////////////////////////////////////////////////////////////////
/// @brief TIM_CCR3FALL Register Bit Definition
////////////////////////////////////////////////////////////////////////////////
#define TIM_CCR3FALL_CCR3FALL       (0xFFFFU)                               ///< Capture/compare value for ch3 when counting down in PWM center-aligned mode

////////////////////////////////////////////////////////////////////////////////
/// @brief TIM_CCR4FALL Register Bit Definition
////////////////////////////////////////////////////////////////////////////////
#define TIM_CCR4FALL_CCR4FALL       (0xFFFFU)                               ///< Capture/compare value for ch4 when counting down in PWM center-aligned mode

////////////////////////////////////////////////////////////////////////////////
/// @brief TIM_CCR5FALL Register Bit Definition
////////////////////////////////////////////////////////////////////////////////
#define TIM_CCR5FALL_CCR5FALL       (0xFFFFU)                               ///< Capture/compare value for ch5 when counting down in PWM center-aligned mode



/// @}

/// @}

/// @}

////////////////////////////////////////////////////////////////////////////////
#endif
////////////////////////////////////////////////////////////////////////////////
