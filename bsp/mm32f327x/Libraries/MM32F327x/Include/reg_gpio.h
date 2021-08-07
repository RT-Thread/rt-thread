////////////////////////////////////////////////////////////////////////////////
/// @file     reg_gpio.h
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

#ifndef __REG_GPIO_H
#define __REG_GPIO_H

// Files includes

#include <stdint.h>
#include <stdbool.h>
#include "types.h"




#if defined ( __CC_ARM )
#pragma anon_unions
#endif








////////////////////////////////////////////////////////////////////////////////
/// @brief GPIO Base Address Definition
////////////////////////////////////////////////////////////////////////////////

#define GPIOA_BASE                  (AHBPERIPH_BASE + 0x0020000)                ///< Base Address: 0x40040000
#define GPIOB_BASE                  (AHBPERIPH_BASE + 0x0020400)                ///< Base Address: 0x40040400
#define GPIOC_BASE                  (AHBPERIPH_BASE + 0x0020800)                ///< Base Address: 0x40040800
#define GPIOD_BASE                  (AHBPERIPH_BASE + 0x0020C00)                ///< Base Address: 0x40040C00
#define GPIOE_BASE                  (AHBPERIPH_BASE + 0x0021000)                ///< Base Address: 0x40041000
#define GPIOF_BASE                  (AHBPERIPH_BASE + 0x0021400)                ///< Base Address: 0x40041400
#define GPIOG_BASE                  (AHBPERIPH_BASE + 0x0021800)                ///< Base Address: 0x40041800
#define GPIOH_BASE                  (AHBPERIPH_BASE + 0x0021C00)                ///< Base Address: 0x40041C00


////////////////////////////////////////////////////////////////////////////////
/// @brief GPIO Registers Structure Definition
////////////////////////////////////////////////////////////////////////////////
typedef struct {
    __IO u32 CRL;                                                               ///< Control Register Low,                          offset: 0x00
    __IO u32 CRH;                                                               ///< Control Register High,                         offset: 0x04
    __IO u32 IDR;                                                               ///< Input Data Register,                           offset: 0x08
    __IO u32 ODR;                                                               ///< Output Data Register,                          offset: 0x0C
    __IO u32 BSRR;                                                              ///< Bit Set or Reset Register,                     offset: 0x10
    __IO u32 BRR;                                                               ///< Bit Reset Register,                            offset: 0x14
    __IO u32 LCKR;                                                              ///< Lock Register,                                 offset: 0x18
    __IO u32 DCR;                                                               ///< Pin Output Open Drain Config Register,         offset: 0x1C
    __IO u32 AFRL;                                                              ///< Port Multiplexing Function Low Register,       offset: 0x20
    __IO u32 AFRH;                                                              ///< Port Multiplexing Function High Register,      offset: 0x24
} GPIO_TypeDef;

////////////////////////////////////////////////////////////////////////////////
/// @brief GPIO type pointer Definition
////////////////////////////////////////////////////////////////////////////////
#define GPIOA                           ((GPIO_TypeDef*) GPIOA_BASE)
#define GPIOB                           ((GPIO_TypeDef*) GPIOB_BASE)
#define GPIOC                           ((GPIO_TypeDef*) GPIOC_BASE)
#define GPIOD                           ((GPIO_TypeDef*) GPIOD_BASE)
#define GPIOE                           ((GPIO_TypeDef*) GPIOE_BASE)
#define GPIOF                           ((GPIO_TypeDef*) GPIOF_BASE)
#define GPIOG                           ((GPIO_TypeDef*) GPIOG_BASE)
#define GPIOH                           ((GPIO_TypeDef*) GPIOH_BASE)


////////////////////////////////////////////////////////////////////////////////
/// @brief GPIO Common Register Bit Definition
////////////////////////////////////////////////////////////////////////////////




#define GPIO_CNF_MODE_AIN             0x00UL //0b0000,                                ///< Analog input
#define GPIO_CNF_MODE_FLOATING        0x04UL //0b0100,                                ///< Floating input
#define GPIO_CNF_MODE_INPUPD          0x08UL //0b1000,                                ///< Pull up and down input
#define GPIO_CNF_MODE_INRESEVED       0x0CUL //0b1100,                                ///< Reseved input mode
#define GPIO_CNF_MODE_OUT_PP          0x01UL //0b0001,                                ///< Universal push-pull  output default
#define GPIO_CNF_MODE_OUT_OD          0x05UL //0b0101,                                ///< Universal open drain output default
#define GPIO_CNF_MODE_AF_PP           0x09UL //0b1001,                                ///< Multiplex push-pull  output default
#define GPIO_CNF_MODE_AF_OD           0x0DUL //0b1101                                 ///< Multiplex open drain output default
#define GPIO_CNF_MODE_50MHZ_OUT_PP    0x01UL //0b0001,                                ///< Universal push-pull  output 50MHZ
#define GPIO_CNF_MODE_50MHZ_OUT_OD    0x05UL //0b0101,                                ///< Universal open drain output 50MHZ
#define GPIO_CNF_MODE_50MHZ_AF_PP     0x09UL //0b1001,                                ///< Multiplex push-pull  output 50MHZ
#define GPIO_CNF_MODE_50MHZ_AF_OD     0x0DUL //0b1101                                 ///< Multiplex open drain output 50MHZ
#define GPIO_CNF_MODE_20MHZ_OUT_PP    0x02UL //0b0010,                                ///< Universal push-pull  output 20MHZ
#define GPIO_CNF_MODE_20MHZ_OUT_OD    0x06UL //0b0110,                                ///< Universal open drain output 20MHZ
#define GPIO_CNF_MODE_20MHZ_AF_PP     0x0AUL //0b1010,                                ///< Multiplex push-pull  output 20MHZ
#define GPIO_CNF_MODE_20MHZ_AF_OD     0x0EUL //0b1110                                 ///< Multiplex open drain output 20MHZ
#define GPIO_CNF_MODE_10MHZ_OUT_PP    0x03UL //0b0011,                                ///< Universal push-pull  output 10MHZ
#define GPIO_CNF_MODE_10MHZ_OUT_OD    0x07UL //0b0111,                                ///< Universal open drain output 10MHZ
#define GPIO_CNF_MODE_10MHZ_AF_PP     0x0BUL //0b1011,                                ///< Multiplex push-pull  output 10MHZ
#define GPIO_CNF_MODE_10MHZ_AF_OD     0x0FUL //0b1111                                 ///< Multiplex open drain output 10MHZ
#define GPIO_CNF_MODE_MASK            0x0FUL //0b1111

#define GPIO_CRL_CNF_MODE_0_Pos       (0)  //                                       ///< Analog input
#define GPIO_CRL_CNF_MODE_1_Pos       (4)  //                                       ///< Floating input
#define GPIO_CRL_CNF_MODE_2_Pos       (8)  //                                       ///< Pull up and down input
#define GPIO_CRL_CNF_MODE_3_Pos       (12) //                                       ///< Reseved input mode
#define GPIO_CRL_CNF_MODE_4_Pos       (16) //                                       ///< Universal push-pull  output default
#define GPIO_CRL_CNF_MODE_5_Pos       (20) //                                       ///< Universal open drain output default
#define GPIO_CRL_CNF_MODE_6_Pos       (24) //                                       ///< Multiplex push-pull  output default
#define GPIO_CRL_CNF_MODE_7_Pos       (28) //                                       ///< Multiplex open drain output default
#define GPIO_CRH_CNF_MODE_8_Pos       (0)  //                                       ///< Universal push-pull  output 50MHZ
#define GPIO_CRH_CNF_MODE_9_Pos       (4)  //                                       ///< Universal open drain output 50MHZ
#define GPIO_CRH_CNF_MODE_10_Pos      (8)  //                                       ///< Multiplex push-pull  output 50MHZ
#define GPIO_CRH_CNF_MODE_11_Pos      (12) //                                       ///< Multiplex open drain output 50MHZ
#define GPIO_CRH_CNF_MODE_12_Pos      (16) //                                       ///< Universal push-pull  output 20MHZ
#define GPIO_CRH_CNF_MODE_13_Pos      (20) //                                       ///< Universal open drain output 20MHZ
#define GPIO_CRH_CNF_MODE_14_Pos      (24) //                                       ///< Multiplex push-pull  output 20MHZ
#define GPIO_CRH_CNF_MODE_15_Pos      (28) //                                       ///< Multiplex open drain output 20MHZ

////////////////////////////////////////////////////////////////////////////////
/// @brief GPIO_CRL Register Bit Definition
////////////////////////////////////////////////////////////////////////////////
#define GPIO_CRL_MODE                   ((u32)0x33333333)                       ///< Port x mode bits

#define GPIO_CRL_MODE0_Pos              (0)
#define GPIO_CRL_MODE0                  (0x03U << GPIO_CRL_MODE0_Pos)           ///< MODE0[1:0] bits (portx mode bits, pin 0)
#define GPIO_CRL_MODE0_0                (0x01U << GPIO_CRL_MODE0_Pos)           ///< Bit 0
#define GPIO_CRL_MODE0_1                (0x02U << GPIO_CRL_MODE0_Pos)           ///< Bit 1

#define GPIO_CRL_CNF0_Pos               (2)
#define GPIO_CRL_CNF0                   (0x03U << GPIO_CRL_CNF0_Pos)            ///< CNF0[1:0] bits (portx configuration bits, pin 0)
#define GPIO_CRL_CNF0_0                 (0x01U << GPIO_CRL_CNF0_Pos)            ///< Bit 0
#define GPIO_CRL_CNF0_1                 (0x02U << GPIO_CRL_CNF0_Pos)            ///< Bit 1

#define GPIO_CRL_MODE1_Pos              (4)
#define GPIO_CRL_MODE1                  (0x03U << GPIO_CRL_MODE1_Pos)           ///< MODE1[1:0] bits (portx mode bits, pin 1)
#define GPIO_CRL_MODE1_0                (0x01U << GPIO_CRL_MODE1_Pos)           ///< Bit 0
#define GPIO_CRL_MODE1_1                (0x02U << GPIO_CRL_MODE1_Pos)           ///< Bit 1

#define GPIO_CRL_CNF1_Pos               (6)
#define GPIO_CRL_CNF1                   (0x03U << GPIO_CRL_CNF1_Pos)            ///< CNF1[1:0] bits (portx configuration bits, pin 1)
#define GPIO_CRL_CNF1_0                 (0x01U << GPIO_CRL_CNF1_Pos)            ///< Bit 0
#define GPIO_CRL_CNF1_1                 (0x02U << GPIO_CRL_CNF1_Pos)            ///< Bit 1

#define GPIO_CRL_MODE2_Pos              (8)
#define GPIO_CRL_MODE2                  (0x03U << GPIO_CRL_MODE2_Pos)           ///< MODE2[1:0] bits (portx mode bits, pin 2)
#define GPIO_CRL_MODE2_0                (0x01U << GPIO_CRL_MODE2_Pos)           ///< Bit 0
#define GPIO_CRL_MODE2_1                (0x02U << GPIO_CRL_MODE2_Pos)           ///< Bit 1

#define GPIO_CRL_CNF2_Pos               (10)
#define GPIO_CRL_CNF2                   (0x03U << GPIO_CRL_CNF2_Pos)            ///< CNF2[1:0] bits (portx configuration bits, pin 2)
#define GPIO_CRL_CNF2_0                 (0x01U << GPIO_CRL_CNF2_Pos)            ///< Bit 0
#define GPIO_CRL_CNF2_1                 (0x02U << GPIO_CRL_CNF2_Pos)            ///< Bit 1

#define GPIO_CRL_MODE3_Pos              (12)
#define GPIO_CRL_MODE3                  (0x03U << GPIO_CRL_MODE3_Pos)           ///< MODE3[1:0] bits (portx mode bits, pin 3)
#define GPIO_CRL_MODE3_0                (0x01U << GPIO_CRL_MODE3_Pos)           ///< Bit 0
#define GPIO_CRL_MODE3_1                (0x02U << GPIO_CRL_MODE3_Pos)           ///< Bit 1

#define GPIO_CRL_CNF3_Pos               (14)
#define GPIO_CRL_CNF3                   (0x03U << GPIO_CRL_CNF3_Pos)            ///< CNF3[1:0] bits (portx configuration bits, pin 3)
#define GPIO_CRL_CNF3_0                 (0x01U << GPIO_CRL_CNF3_Pos)            ///< Bit 0
#define GPIO_CRL_CNF3_1                 (0x02U << GPIO_CRL_CNF3_Pos)            ///< Bit 1


#define GPIO_CRL_MODE4_Pos              (16)
#define GPIO_CRL_MODE4                  (0x03U << GPIO_CRL_MODE4_Pos)           ///< MODE4[1:0] bits (portx mode bits, pin 4)
#define GPIO_CRL_MODE4_0                (0x01U << GPIO_CRL_MODE4_Pos)           ///< Bit 0
#define GPIO_CRL_MODE4_1                (0x02U << GPIO_CRL_MODE4_Pos)           ///< Bit 1

#define GPIO_CRL_CNF4_Pos               (18)
#define GPIO_CRL_CNF4                   (0x03U << GPIO_CRL_CNF4_Pos)            ///< CNF4[1:0] bits (portx configuration bits, pin 4)
#define GPIO_CRL_CNF4_0                 (0x01U << GPIO_CRL_CNF4_Pos)            ///< Bit 0
#define GPIO_CRL_CNF4_1                 (0x02U << GPIO_CRL_CNF4_Pos)            ///< Bit 1

#define GPIO_CRL_MODE5_Pos              (20)
#define GPIO_CRL_MODE5                  (0x03U << GPIO_CRL_MODE5_Pos)           ///< MODE5[1:0] bits (portx mode bits, pin 5)
#define GPIO_CRL_MODE5_0                (0x01U << GPIO_CRL_MODE5_Pos)           ///< Bit 0
#define GPIO_CRL_MODE5_1                (0x02U << GPIO_CRL_MODE5_Pos)           ///< Bit 1

#define GPIO_CRL_CNF5_Pos               (22)
#define GPIO_CRL_CNF5                   (0x03U << GPIO_CRL_CNF5_Pos)            ///< CNF5[1:0] bits (portx configuration bits, pin 5)
#define GPIO_CRL_CNF5_0                 (0x01U << GPIO_CRL_CNF5_Pos)            ///< Bit 0
#define GPIO_CRL_CNF5_1                 (0x02U << GPIO_CRL_CNF5_Pos)            ///< Bit 1

#define GPIO_CRL_MODE6_Pos              (24)
#define GPIO_CRL_MODE6                  (0x03U << GPIO_CRL_MODE6_Pos)           ///< MODE6[1:0] bits (portx mode bits, pin 6)
#define GPIO_CRL_MODE6_0                (0x01U << GPIO_CRL_MODE6_Pos)           ///< Bit 0
#define GPIO_CRL_MODE6_1                (0x02U << GPIO_CRL_MODE6_Pos)           ///< Bit 1

#define GPIO_CRL_CNF6_Pos               (26)
#define GPIO_CRL_CNF6                   (0x03U << GPIO_CRL_CNF6_Pos)            ///< CNF6[1:0] bits (portx configuration bits, pin 6)
#define GPIO_CRL_CNF6_0                 (0x01U << GPIO_CRL_CNF6_Pos)            ///< Bit 0
#define GPIO_CRL_CNF6_1                 (0x02U << GPIO_CRL_CNF6_Pos)            ///< Bit 1

#define GPIO_CRL_MODE7_Pos              (28)
#define GPIO_CRL_MODE7                  (0x03U << GPIO_CRL_MODE7_Pos)           ///< MODE7[1:0] bits (portx mode bits, pin 7)
#define GPIO_CRL_MODE7_0                (0x01U << GPIO_CRL_MODE7_Pos)           ///< Bit 0
#define GPIO_CRL_MODE7_1                (0x02U << GPIO_CRL_MODE7_Pos)           ///< Bit 1

#define GPIO_CRL_CNF7_Pos               (30)
#define GPIO_CRL_CNF7                   (0x03U << GPIO_CRL_CNF7_Pos)            ///< CNF7[1:0] bits (portx configuration bits, pin 7)
#define GPIO_CRL_CNF7_0                 (0x01U << GPIO_CRL_CNF7_Pos)            ///< Bit 0
#define GPIO_CRL_CNF7_1                 (0x02U << GPIO_CRL_CNF7_Pos)            ///< Bit 1

////////////////////////////////////////////////////////////////////////////////
/// @brief GPIO_CRH Register Bit Definition
////////////////////////////////////////////////////////////////////////////////
#define GPIO_CRH_MODE                   ((u32)0x33333333)                       ///< Port x mode bits

#define GPIO_CRH_MODE8_Pos              (0)
#define GPIO_CRH_MODE8                  (0x03U << GPIO_CRH_MODE8_Pos)           ///< MODE8[1:0] bits (portx mode bits, pin 0)
#define GPIO_CRH_MODE8_0                (0x01U << GPIO_CRH_MODE8_Pos)           ///< Bit 0
#define GPIO_CRH_MODE8_1                (0x02U << GPIO_CRH_MODE8_Pos)           ///< Bit 1
#define GPIO_CRH_CNF8_Pos               (2)
#define GPIO_CRH_CNF8                   (0x03U << GPIO_CRH_CNF8_Pos)            ///< CNF8[1:0] bits (portx configuration bits, pin 0)
#define GPIO_CRH_CNF8_0                 (0x01U << GPIO_CRH_CNF8_Pos)            ///< Bit 0
#define GPIO_CRH_CNF8_1                 (0x02U << GPIO_CRH_CNF8_Pos)            ///< Bit 1
#define GPIO_CRH_MODE9_Pos              (4)
#define GPIO_CRH_MODE9                  (0x03U << GPIO_CRH_MODE9_Pos)           ///< MODE9[1:0] bits (portx mode bits, pin 1)
#define GPIO_CRH_MODE9_0                (0x01U << GPIO_CRH_MODE9_Pos)           ///< Bit 0
#define GPIO_CRH_MODE9_1                (0x02U << GPIO_CRH_MODE9_Pos)           ///< Bit 1
#define GPIO_CRH_CNF9_Pos               (6)
#define GPIO_CRH_CNF9                   (0x03U << GPIO_CRH_CNF9_Pos)            ///< CNF9[1:0] bits (portx configuration bits, pin 1)
#define GPIO_CRH_CNF9_0                 (0x01U << GPIO_CRH_CNF9_Pos)            ///< Bit 0
#define GPIO_CRH_CNF9_1                 (0x02U << GPIO_CRH_CNF9_Pos)            ///< Bit 1
#define GPIO_CRH_MODE10_Pos             (8)
#define GPIO_CRH_MODE10                 (0x03U << GPIO_CRH_MODE10_Pos)          ///< MODE10[1:0] bits (portx mode bits, pin 2)
#define GPIO_CRH_MODE10_0               (0x01U << GPIO_CRH_MODE10_Pos)          ///< Bit 0
#define GPIO_CRH_MODE10_1               (0x02U << GPIO_CRH_MODE10_Pos)          ///< Bit 1
#define GPIO_CRH_CNF10_Pos              (10)
#define GPIO_CRH_CNF10                  (0x03U << GPIO_CRH_CNF10_Pos)           ///< CNF10[1:0] bits (portx configuration bits, pin 2)
#define GPIO_CRH_CNF10_0                (0x01U << GPIO_CRH_CNF10_Pos)           ///< Bit 0
#define GPIO_CRH_CNF10_1                (0x02U << GPIO_CRH_CNF10_Pos)           ///< Bit 1
#define GPIO_CRH_MODE11_Pos             (12)
#define GPIO_CRH_MODE11                 (0x03U << GPIO_CRH_MODE11_Pos)          ///< MODE11[1:0] bits (portx mode bits, pin 3)
#define GPIO_CRH_MODE11_0               (0x01U << GPIO_CRH_MODE11_Pos)          ///< Bit 0
#define GPIO_CRH_MODE11_1               (0x02U << GPIO_CRH_MODE11_Pos)          ///< Bit 1
#define GPIO_CRH_CNF11_Pos              (14)
#define GPIO_CRH_CNF11                  (0x03U << GPIO_CRH_CNF11_Pos)           ///< CNF11[1:0] bits (portx configuration bits, pin 3)
#define GPIO_CRH_CNF11_0                (0x01U << GPIO_CRH_CNF11_Pos)           ///< Bit 0
#define GPIO_CRH_CNF11_1                (0x02U << GPIO_CRH_CNF11_Pos)           ///< Bit 1
#define GPIO_CRH_MODE12_Pos             (16)
#define GPIO_CRH_MODE12                 (0x03U << GPIO_CRH_MODE12_Pos)          ///< MODE12[1:0] bits (portx mode bits, pin 4)
#define GPIO_CRH_MODE12_0               (0x01U << GPIO_CRH_MODE12_Pos)          ///< Bit 0
#define GPIO_CRH_MODE12_1               (0x02U << GPIO_CRH_MODE12_Pos)          ///< Bit 1
#define GPIO_CRH_CNF12_Pos              (18)
#define GPIO_CRH_CNF12                  (0x03U << GPIO_CRH_CNF12_Pos)           ///< CNF12[1:0] bits (portx configuration bits, pin 4)
#define GPIO_CRH_CNF12_0                (0x01U << GPIO_CRH_CNF12_Pos)           ///< Bit 0
#define GPIO_CRH_CNF12_1                (0x02U << GPIO_CRH_CNF12_Pos)           ///< Bit 1
#define GPIO_CRH_MODE13_Pos             (20)
#define GPIO_CRH_MODE13                 (0x03U << GPIO_CRH_MODE13_Pos)          ///< MODE13[1:0] bits (portx mode bits, pin 5)
#define GPIO_CRH_MODE13_0               (0x01U << GPIO_CRH_MODE13_Pos)          ///< Bit 0
#define GPIO_CRH_MODE13_1               (0x02U << GPIO_CRH_MODE13_Pos)          ///< Bit 1
#define GPIO_CRH_CNF13_Pos              (22)
#define GPIO_CRH_CNF13                  (0x03U << GPIO_CRH_CNF13_Pos)           ///< CNF13[1:0] bits (portx configuration bits, pin 5)
#define GPIO_CRH_CNF13_0                (0x01U << GPIO_CRH_CNF13_Pos)           ///< Bit 0
#define GPIO_CRH_CNF13_1                (0x02U << GPIO_CRH_CNF13_Pos)           ///< Bit 1
#define GPIO_CRH_MODE14_Pos             (24)
#define GPIO_CRH_MODE14                 (0x03U << GPIO_CRH_MODE14_Pos)          ///< MODE14[1:0] bits (portx mode bits, pin 6)
#define GPIO_CRH_MODE14_0               (0x01U << GPIO_CRH_MODE14_Pos)          ///< Bit 0
#define GPIO_CRH_MODE14_1               (0x02U << GPIO_CRH_MODE14_Pos)          ///< Bit 1
#define GPIO_CRH_CNF14_Pos              (26)
#define GPIO_CRH_CNF14                  (0x03U << GPIO_CRH_CNF14_Pos)           ///< CNF14[1:0] bits (portx configuration bits, pin 6)
#define GPIO_CRH_CNF14_0                (0x01U << GPIO_CRH_CNF14_Pos)           ///< Bit 0
#define GPIO_CRH_CNF14_1                (0x02U << GPIO_CRH_CNF14_Pos)           ///< Bit 1
#define GPIO_CRH_MODE15_Pos             (28)
#define GPIO_CRH_MODE15                 (0x03U << GPIO_CRH_MODE15_Pos)          ///< MODE15[1:0] bits (portx mode bits, pin 7)
#define GPIO_CRH_MODE15_0               (0x01U << GPIO_CRH_MODE15_Pos)          ///< Bit 0
#define GPIO_CRH_MODE15_1               (0x02U << GPIO_CRH_MODE15_Pos)          ///< Bit 1
#define GPIO_CRH_CNF15_Pos              (30)
#define GPIO_CRH_CNF15                  (0x03U << GPIO_CRH_CNF15_Pos)           ///< CNF15[1:0] bits (portx configuration bits, pin 7)
#define GPIO_CRH_CNF15_0                (0x01U << GPIO_CRH_CNF15_Pos)           ///< Bit 0
#define GPIO_CRH_CNF15_1                (0x02U << GPIO_CRH_CNF15_Pos)           ///< Bit 1

////////////////////////////////////////////////////////////////////////////////
/// @brief GPIO_IDR Register Bit Definition
////////////////////////////////////////////////////////////////////////////////
#define GPIO_IDR_DATA_Pos               (0)
#define GPIO_IDR_DATA                   (0xFFFFU << GPIO_IDR_DATA_Pos)          ///< Port input data
////////////////////////////////////////////////////////////////////////////////
/// @brief GPIO_IDR Register Bit Definition
////////////////////////////////////////////////////////////////////////////////
#define GPIO_IDR_IDR0_Pos               (0)
#define GPIO_IDR_IDR0                   (0x01U << GPIO_IDR_IDR0_Pos)            ///< Portx Set bit 0
#define GPIO_IDR_IDR1_Pos               (1)
#define GPIO_IDR_IDR1                   (0x01U << GPIO_IDR_IDR1_Pos)            ///< Portx Set bit 1
#define GPIO_IDR_IDR2_Pos               (2)
#define GPIO_IDR_IDR2                   (0x01U << GPIO_IDR_IDR2_Pos)            ///< Portx Set bit 2
#define GPIO_IDR_IDR3_Pos               (3)
#define GPIO_IDR_IDR3                   (0x01U << GPIO_IDR_IDR3_Pos)            ///< Portx Set bit 3
#define GPIO_IDR_IDR4_Pos               (4)
#define GPIO_IDR_IDR4                   (0x01U << GPIO_IDR_IDR4_Pos)            ///< Portx Set bit 4
#define GPIO_IDR_IDR5_Pos               (5)
#define GPIO_IDR_IDR5                   (0x01U << GPIO_IDR_IDR5_Pos)            ///< Portx Set bit 5
#define GPIO_IDR_IDR6_Pos               (6)
#define GPIO_IDR_IDR6                   (0x01U << GPIO_IDR_IDR6_Pos)            ///< Portx Set bit 6
#define GPIO_IDR_IDR7_Pos               (7)
#define GPIO_IDR_IDR7                   (0x01U << GPIO_IDR_IDR7_Pos)            ///< Portx Set bit 7
#define GPIO_IDR_IDR8_Pos               (8)
#define GPIO_IDR_IDR8                   (0x01U << GPIO_IDR_IDR8_Pos)            ///< Portx Set bit 8
#define GPIO_IDR_IDR9_Pos               (9)
#define GPIO_IDR_IDR9                   (0x01U << GPIO_IDR_IDR9_Pos)            ///< Portx Set bit 9
#define GPIO_IDR_IDR10_Pos              (10)
#define GPIO_IDR_IDR10                  (0x01U << GPIO_IDR_IDR10_Pos)           ///< Portx Set bit 10
#define GPIO_IDR_IDR11_Pos              (11)
#define GPIO_IDR_IDR11                  (0x01U << GPIO_IDR_IDR11_Pos)           ///< Portx Set bit 11
#define GPIO_IDR_IDR12_Pos              (12)
#define GPIO_IDR_IDR12                  (0x01U << GPIO_IDR_IDR12_Pos)           ///< Portx Set bit 12
#define GPIO_IDR_IDR13_Pos              (13)
#define GPIO_IDR_IDR13                  (0x01U << GPIO_IDR_IDR13_Pos)           ///< Portx Set bit 13
#define GPIO_IDR_IDR14_Pos              (14)
#define GPIO_IDR_IDR14                  (0x01U << GPIO_IDR_IDR14_Pos)           ///< Portx Set bit 14
#define GPIO_IDR_IDR15_Pos              (15)
#define GPIO_IDR_IDR15                  (0x01U << GPIO_IDR_IDR15_Pos)           ///< Portx Set bit 15
////////////////////////////////////////////////////////////////////////////////
/// @brief GPIO_ODR Register Bit Definition
////////////////////////////////////////////////////////////////////////////////
#define GPIO_ODR_DATA_Pos               (0)
#define GPIO_ODR_DATA                   (0xFFFF << GPIO_ODR_DATA_Pos)           ///< Port output data
////////////////////////////////////////////////////////////////////////////////
/// @brief GPIO_ODR Register Bit Definition
////////////////////////////////////////////////////////////////////////////////
#define GPIO_ODR_ODR0_Pos               (0)
#define GPIO_ODR_ODR0                   (0x01U << GPIO_ODR_ODR0_Pos)            ///< Portx Set bit 0
#define GPIO_ODR_ODR1_Pos               (1)
#define GPIO_ODR_ODR1                   (0x01U << GPIO_ODR_ODR1_Pos)            ///< Portx Set bit 1
#define GPIO_ODR_ODR2_Pos               (2)
#define GPIO_ODR_ODR2                   (0x01U << GPIO_ODR_ODR2_Pos)            ///< Portx Set bit 2
#define GPIO_ODR_ODR3_Pos               (3)
#define GPIO_ODR_ODR3                   (0x01U << GPIO_ODR_ODR3_Pos)            ///< Portx Set bit 3
#define GPIO_ODR_ODR4_Pos               (4)
#define GPIO_ODR_ODR4                   (0x01U << GPIO_ODR_ODR4_Pos)            ///< Portx Set bit 4
#define GPIO_ODR_ODR5_Pos               (5)
#define GPIO_ODR_ODR5                   (0x01U << GPIO_ODR_ODR5_Pos)            ///< Portx Set bit 5
#define GPIO_ODR_ODR6_Pos               (6)
#define GPIO_ODR_ODR6                   (0x01U << GPIO_ODR_ODR6_Pos)            ///< Portx Set bit 6
#define GPIO_ODR_ODR7_Pos               (7)
#define GPIO_ODR_ODR7                   (0x01U << GPIO_ODR_ODR7_Pos)            ///< Portx Set bit 7
#define GPIO_ODR_ODR8_Pos               (8)
#define GPIO_ODR_ODR8                   (0x01U << GPIO_ODR_ODR8_Pos)            ///< Portx Set bit 8
#define GPIO_ODR_ODR9_Pos               (9)
#define GPIO_ODR_ODR9                   (0x01U << GPIO_ODR_ODR9_Pos)            ///< Portx Set bit 9
#define GPIO_ODR_ODR10_Pos              (10)
#define GPIO_ODR_ODR10                  (0x01U << GPIO_ODR_ODR10_Pos)           ///< Portx Set bit 10
#define GPIO_ODR_ODR11_Pos              (11)
#define GPIO_ODR_ODR11                  (0x01U << GPIO_ODR_ODR11_Pos)           ///< Portx Set bit 11
#define GPIO_ODR_ODR12_Pos              (12)
#define GPIO_ODR_ODR12                  (0x01U << GPIO_ODR_ODR12_Pos)           ///< Portx Set bit 12
#define GPIO_ODR_ODR13_Pos              (13)
#define GPIO_ODR_ODR13                  (0x01U << GPIO_ODR_ODR13_Pos)           ///< Portx Set bit 13
#define GPIO_ODR_ODR14_Pos              (14)
#define GPIO_ODR_ODR14                  (0x01U << GPIO_ODR_ODR14_Pos)           ///< Portx Set bit 14
#define GPIO_ODR_ODR15_Pos              (15)
#define GPIO_ODR_ODR15                  (0x01U << GPIO_ODR_ODR15_Pos)           ///< Portx Set bit 15

////////////////////////////////////////////////////////////////////////////////
/// @brief GPIO_BRR Register Bit Definition
////////////////////////////////////////////////////////////////////////////////
#define GPIO_BSRR_BS_Pos                (0)
#define GPIO_BSRR_BS                    (0xFFFFU << GPIO_BSRR_BS_Pos)            ///< Portx Reset
////////////////////////////////////////////////////////////////////////////////
/// @brief GPIO_BSRR Register Bit Definition
////////////////////////////////////////////////////////////////////////////////
#define GPIO_BSRR_BS0_Pos               (0)
#define GPIO_BSRR_BS0                   (0x01U << GPIO_BSRR_BS0_Pos)            ///< Portx Set bit 0
#define GPIO_BSRR_BS1_Pos               (1)
#define GPIO_BSRR_BS1                   (0x01U << GPIO_BSRR_BS1_Pos)            ///< Portx Set bit 1
#define GPIO_BSRR_BS2_Pos               (2)
#define GPIO_BSRR_BS2                   (0x01U << GPIO_BSRR_BS2_Pos)            ///< Portx Set bit 2
#define GPIO_BSRR_BS3_Pos               (3)
#define GPIO_BSRR_BS3                   (0x01U << GPIO_BSRR_BS3_Pos)            ///< Portx Set bit 3
#define GPIO_BSRR_BS4_Pos               (4)
#define GPIO_BSRR_BS4                   (0x01U << GPIO_BSRR_BS4_Pos)            ///< Portx Set bit 4
#define GPIO_BSRR_BS5_Pos               (5)
#define GPIO_BSRR_BS5                   (0x01U << GPIO_BSRR_BS5_Pos)            ///< Portx Set bit 5
#define GPIO_BSRR_BS6_Pos               (6)
#define GPIO_BSRR_BS6                   (0x01U << GPIO_BSRR_BS6_Pos)            ///< Portx Set bit 6
#define GPIO_BSRR_BS7_Pos               (7)
#define GPIO_BSRR_BS7                   (0x01U << GPIO_BSRR_BS7_Pos)            ///< Portx Set bit 7
#define GPIO_BSRR_BS8_Pos               (8)
#define GPIO_BSRR_BS8                   (0x01U << GPIO_BSRR_BS8_Pos)            ///< Portx Set bit 8
#define GPIO_BSRR_BS9_Pos               (9)
#define GPIO_BSRR_BS9                   (0x01U << GPIO_BSRR_BS9_Pos)            ///< Portx Set bit 9
#define GPIO_BSRR_BS10_Pos              (10)
#define GPIO_BSRR_BS10                  (0x01U << GPIO_BSRR_BS10_Pos)           ///< Portx Set bit 10
#define GPIO_BSRR_BS11_Pos              (11)
#define GPIO_BSRR_BS11                  (0x01U << GPIO_BSRR_BS11_Pos)           ///< Portx Set bit 11
#define GPIO_BSRR_BS12_Pos              (12)
#define GPIO_BSRR_BS12                  (0x01U << GPIO_BSRR_BS12_Pos)           ///< Portx Set bit 12
#define GPIO_BSRR_BS13_Pos              (13)
#define GPIO_BSRR_BS13                  (0x01U << GPIO_BSRR_BS13_Pos)           ///< Portx Set bit 13
#define GPIO_BSRR_BS14_Pos              (14)
#define GPIO_BSRR_BS14                  (0x01U << GPIO_BSRR_BS14_Pos)           ///< Portx Set bit 14
#define GPIO_BSRR_BS15_Pos              (15)
#define GPIO_BSRR_BS15                  (0x01U << GPIO_BSRR_BS15_Pos)           ///< Portx Set bit 15

#define GPIO_BSRR_BR0_Pos               (16)
#define GPIO_BSRR_BR0                   (0x01U << GPIO_BSRR_BR0_Pos)            ///< Portx Reset bit 0
#define GPIO_BSRR_BR1_Pos               (17)
#define GPIO_BSRR_BR1                   (0x01U << GPIO_BSRR_BR1_Pos)            ///< Portx Reset bit 1
#define GPIO_BSRR_BR2_Pos               (18)
#define GPIO_BSRR_BR2                   (0x01U << GPIO_BSRR_BR2_Pos)            ///< Portx Reset bit 2
#define GPIO_BSRR_BR3_Pos               (19)
#define GPIO_BSRR_BR3                   (0x01U << GPIO_BSRR_BR3_Pos)            ///< Portx Reset bit 3
#define GPIO_BSRR_BR4_Pos               (20)
#define GPIO_BSRR_BR4                   (0x01U << GPIO_BSRR_BR4_Pos)            ///< Portx Reset bit 4
#define GPIO_BSRR_BR5_Pos               (21)
#define GPIO_BSRR_BR5                   (0x01U << GPIO_BSRR_BR5_Pos)            ///< Portx Reset bit 5
#define GPIO_BSRR_BR6_Pos               (22)
#define GPIO_BSRR_BR6                   (0x01U << GPIO_BSRR_BR6_Pos)            ///< Portx Reset bit 6
#define GPIO_BSRR_BR7_Pos               (23)
#define GPIO_BSRR_BR7                   (0x01U << GPIO_BSRR_BR7_Pos)            ///< Portx Reset bit 7
#define GPIO_BSRR_BR8_Pos               (24)
#define GPIO_BSRR_BR8                   (0x01U << GPIO_BSRR_BR8_Pos)            ///< Portx Reset bit 8
#define GPIO_BSRR_BR9_Pos               (25)
#define GPIO_BSRR_BR9                   (0x01U << GPIO_BSRR_BR9_Pos)            ///< Portx Reset bit 9
#define GPIO_BSRR_BR10_Pos              (26)
#define GPIO_BSRR_BR10                  (0x01U << GPIO_BSRR_BR10_Pos)           ///< Portx Reset bit 10
#define GPIO_BSRR_BR11_Pos              (27)
#define GPIO_BSRR_BR11                  (0x01U << GPIO_BSRR_BR11_Pos)           ///< Portx Reset bit 11
#define GPIO_BSRR_BR12_Pos              (28)
#define GPIO_BSRR_BR12                  (0x01U << GPIO_BSRR_BR12_Pos)           ///< Portx Reset bit 12
#define GPIO_BSRR_BR13_Pos              (29)
#define GPIO_BSRR_BR13                  (0x01U << GPIO_BSRR_BR13_Pos)           ///< Portx Reset bit 13
#define GPIO_BSRR_BR14_Pos              (30)
#define GPIO_BSRR_BR14                  (0x01U << GPIO_BSRR_BR14_Pos)           ///< Portx Reset bit 14
#define GPIO_BSRR_BR15_Pos              (31)
#define GPIO_BSRR_BR15                  (0x01U << GPIO_BSRR_BR15_Pos)           ///< Portx Reset bit 15

////////////////////////////////////////////////////////////////////////////////
/// @brief GPIO_BRR Register Bit Definition
////////////////////////////////////////////////////////////////////////////////
#define GPIO_BRR_BR_Pos                 (0)
#define GPIO_BRR_BR                     (0xFFFFU << GPIO_BRR_BR_Pos)            ///< Portx Reset

////////////////////////////////////////////////////////////////////////////////
/// @brief GPIO_BRR Register Bit Definition
////////////////////////////////////////////////////////////////////////////////
#define GPIO_BRR_BR0_Pos               (0)
#define GPIO_BRR_BR0                   (0x01U << GPIO_BRR_BR0_Pos)            ///< Portx Set bit 0
#define GPIO_BRR_BR1_Pos               (1)
#define GPIO_BRR_BR1                   (0x01U << GPIO_BRR_BR1_Pos)            ///< Portx Set bit 1
#define GPIO_BRR_BR2_Pos               (2)
#define GPIO_BRR_BR2                   (0x01U << GPIO_BRR_BR2_Pos)            ///< Portx Set bit 2
#define GPIO_BRR_BR3_Pos               (3)
#define GPIO_BRR_BR3                   (0x01U << GPIO_BRR_BR3_Pos)            ///< Portx Set bit 3
#define GPIO_BRR_BR4_Pos               (4)
#define GPIO_BRR_BR4                   (0x01U << GPIO_BRR_BR4_Pos)            ///< Portx Set bit 4
#define GPIO_BRR_BR5_Pos               (5)
#define GPIO_BRR_BR5                   (0x01U << GPIO_BRR_BR5_Pos)            ///< Portx Set bit 5
#define GPIO_BRR_BR6_Pos               (6)
#define GPIO_BRR_BR6                   (0x01U << GPIO_BRR_BR6_Pos)            ///< Portx Set bit 6
#define GPIO_BRR_BR7_Pos               (7)
#define GPIO_BRR_BR7                   (0x01U << GPIO_BRR_BR7_Pos)            ///< Portx Set bit 7
#define GPIO_BRR_BR8_Pos               (8)
#define GPIO_BRR_BR8                   (0x01U << GPIO_BRR_BR8_Pos)            ///< Portx Set bit 8
#define GPIO_BRR_BR9_Pos               (9)
#define GPIO_BRR_BR9                   (0x01U << GPIO_BRR_BR9_Pos)            ///< Portx Set bit 9
#define GPIO_BRR_BR10_Pos              (10)
#define GPIO_BRR_BR10                  (0x01U << GPIO_BRR_BR10_Pos)           ///< Portx Set bit 10
#define GPIO_BRR_BR11_Pos              (11)
#define GPIO_BRR_BR11                  (0x01U << GPIO_BRR_BR11_Pos)           ///< Portx Set bit 11
#define GPIO_BRR_BR12_Pos              (12)
#define GPIO_BRR_BR12                  (0x01U << GPIO_BRR_BR12_Pos)           ///< Portx Set bit 12
#define GPIO_BRR_BR13_Pos              (13)
#define GPIO_BRR_BR13                  (0x01U << GPIO_BRR_BR13_Pos)           ///< Portx Set bit 13
#define GPIO_BRR_BR14_Pos              (14)
#define GPIO_BRR_BR14                  (0x01U << GPIO_BRR_BR14_Pos)           ///< Portx Set bit 14
#define GPIO_BRR_BR15_Pos              (15)
#define GPIO_BRR_BR15                  (0x01U << GPIO_BRR_BR15_Pos)           ///< Portx Set bit 15

////////////////////////////////////////////////////////////////////////////////
/// @brief GPIO_LCKR Register Bit Definition
////////////////////////////////////////////////////////////////////////////////
#define GPIO_LCKR_LCK_Pos               (0)
#define GPIO_LCKR_LCK                   (0xFFFFU << GPIO_LCKR_LCK_Pos)          ///< Portx Lock
#define GPIO_LCKR_LCKK_Pos              (16)
#define GPIO_LCKR_LCKK                  (0x01U << GPIO_LCKR_LCKK_Pos)           ///< Lock key

////////////////////////////////////////////////////////////////////////////////
/// @brief GPIO_LCKR Register Bit Definition
////////////////////////////////////////////////////////////////////////////////
#define GPIO_LCKR_LCK0_Pos               (0)
#define GPIO_LCKR_LCK0                   (0x01U << GPIO_LCKR_LCK0_Pos)          ///< Portx Set bit 0
#define GPIO_LCKR_LCK1_Pos               (1)
#define GPIO_LCKR_LCK1                   (0x01U << GPIO_LCKR_LCK1_Pos)          ///< Portx Set bit 1
#define GPIO_LCKR_LCK2_Pos               (2)
#define GPIO_LCKR_LCK2                   (0x01U << GPIO_LCKR_LCK2_Pos)          ///< Portx Set bit 2
#define GPIO_LCKR_LCK3_Pos               (3)
#define GPIO_LCKR_LCK3                   (0x01U << GPIO_LCKR_LCK3_Pos)          ///< Portx Set bit 3
#define GPIO_LCKR_LCK4_Pos               (4)
#define GPIO_LCKR_LCK4                   (0x01U << GPIO_LCKR_LCK4_Pos)          ///< Portx Set bit 4
#define GPIO_LCKR_LCK5_Pos               (5)
#define GPIO_LCKR_LCK5                   (0x01U << GPIO_LCKR_LCK5_Pos)          ///< Portx Set bit 5
#define GPIO_LCKR_LCK6_Pos               (6)
#define GPIO_LCKR_LCK6                   (0x01U << GPIO_LCKR_LCK6_Pos)          ///< Portx Set bit 6
#define GPIO_LCKR_LCK7_Pos               (7)
#define GPIO_LCKR_LCK7                   (0x01U << GPIO_LCKR_LCK7_Pos)          ///< Portx Set bit 7
#define GPIO_LCKR_LCK8_Pos               (8)
#define GPIO_LCKR_LCK8                   (0x01U << GPIO_LCKR_LCK8_Pos)          ///< Portx Set bit 8
#define GPIO_LCKR_LCK9_Pos               (9)
#define GPIO_LCKR_LCK9                   (0x01U << GPIO_LCKR_LCK9_Pos)          ///< Portx Set bit 9
#define GPIO_LCKR_LCK10_Pos              (10)
#define GPIO_LCKR_LCK10                  (0x01U << GPIO_LCKR_LCK10_Pos)         ///< Portx Set bit 10
#define GPIO_LCKR_LCK11_Pos              (11)
#define GPIO_LCKR_LCK11                  (0x01U << GPIO_LCKR_LCK11_Pos)         ///< Portx Set bit 11
#define GPIO_LCKR_LCK12_Pos              (12)
#define GPIO_LCKR_LCK12                  (0x01U << GPIO_LCKR_LCK12_Pos)         ///< Portx Set bit 12
#define GPIO_LCKR_LCK13_Pos              (13)
#define GPIO_LCKR_LCK13                  (0x01U << GPIO_LCKR_LCK13_Pos)         ///< Portx Set bit 13
#define GPIO_LCKR_LCK14_Pos              (14)
#define GPIO_LCKR_LCK14                  (0x01U << GPIO_LCKR_LCK14_Pos)         ///< Portx Set bit 14
#define GPIO_LCKR_LCK15_Pos              (15)
#define GPIO_LCKR_LCK15                  (0x01U << GPIO_LCKR_LCK15_Pos)         ///< Portx Set bit 15

////////////////////////////////////////////////////////////////////////////////
/// @brief GPIO_DCR Register Bit Definition
////////////////////////////////////////////////////////////////////////////////
#define GPIO_DCR_PX0_Pos                (0)
#define GPIO_DCR_PX0                    (0x03U << GPIO_DCR_PX0_Pos)                  ///< PX0[1:0] bits (pinx configuration bits, pin 0)
#define GPIO_DCR_PX0_MODE0              (0x00U << GPIO_DCR_PX0_Pos)                  ///< Mode = 0
#define GPIO_DCR_PX0_MODE1              (0x01U << GPIO_DCR_PX0_Pos)                  ///< Mode = 1
#define GPIO_DCR_PX0_MODE2              (0x02U << GPIO_DCR_PX0_Pos)                  ///< Mode = 2
#define GPIO_DCR_PX0_MODE3              (0x03U << GPIO_DCR_PX0_Pos)                  ///< Mode = 3
#define GPIO_DCR_PX1_Pos                (2)
#define GPIO_DCR_PX1                    (0x03U << GPIO_DCR_PX1_Pos)                  ///< PX1[1:0] bits (pinx configuration bits, pin 1)
#define GPIO_DCR_PX1_MODE0              (0x00U << GPIO_DCR_PX1_Pos)                  ///< Mode = 0
#define GPIO_DCR_PX1_MODE1              (0x01U << GPIO_DCR_PX1_Pos)                  ///< Mode = 1
#define GPIO_DCR_PX1_MODE2              (0x02U << GPIO_DCR_PX1_Pos)                  ///< Mode = 2
#define GPIO_DCR_PX1_MODE3              (0x03U << GPIO_DCR_PX1_Pos)                  ///< Mode = 3
#define GPIO_DCR_PX2_Pos                (4)
#define GPIO_DCR_PX2                    (0x03U << GPIO_DCR_PX2_Pos)                  ///< PX2[1:0] bits (pinx configuration bits, pin 2)
#define GPIO_DCR_PX2_MODE0              (0x00U << GPIO_DCR_PX2_Pos)                  ///< Mode = 0
#define GPIO_DCR_PX2_MODE1              (0x01U << GPIO_DCR_PX2_Pos)                  ///< Mode = 1
#define GPIO_DCR_PX2_MODE2              (0x02U << GPIO_DCR_PX2_Pos)                  ///< Mode = 2
#define GPIO_DCR_PX2_MODE3              (0x03U << GPIO_DCR_PX2_Pos)                  ///< Mode = 3
#define GPIO_DCR_PX3_Pos                (6)
#define GPIO_DCR_PX3                    (0x03U << GPIO_DCR_PX3_Pos)                  ///< PX3[1:0] bits (pinx configuration bits, pin 3)
#define GPIO_DCR_PX3_MODE0              (0x00U << GPIO_DCR_PX3_Pos)                  ///< Mode = 0
#define GPIO_DCR_PX3_MODE1              (0x01U << GPIO_DCR_PX3_Pos)                  ///< Mode = 1
#define GPIO_DCR_PX3_MODE2              (0x02U << GPIO_DCR_PX3_Pos)                  ///< Mode = 2
#define GPIO_DCR_PX3_MODE3              (0x03U << GPIO_DCR_PX3_Pos)                  ///< Mode = 3

#define GPIO_DCR_PX4_Pos                (8)
#define GPIO_DCR_PX4                    (0x03U << GPIO_DCR_PX4_Pos)                  ///< PX4[1:0] bits (pinx configuration bits, pin 4)
#define GPIO_DCR_PX4_MODE0              (0x00U << GPIO_DCR_PX4_Pos)                  ///< Mode = 0
#define GPIO_DCR_PX4_MODE1              (0x01U << GPIO_DCR_PX4_Pos)                  ///< Mode = 1
#define GPIO_DCR_PX4_MODE2              (0x02U << GPIO_DCR_PX4_Pos)                  ///< Mode = 2
#define GPIO_DCR_PX4_MODE3              (0x03U << GPIO_DCR_PX4_Pos)                  ///< Mode = 3

#define GPIO_DCR_PX5_Pos                (10)
#define GPIO_DCR_PX5                    (0x03U << GPIO_DCR_PX5_Pos)                  ///< PX5[1:0] bits (pinx configuration bits, pin 5)
#define GPIO_DCR_PX5_MODE0              (0x00U << GPIO_DCR_PX5_Pos)                  ///< Mode = 0
#define GPIO_DCR_PX5_MODE1              (0x01U << GPIO_DCR_PX5_Pos)                  ///< Mode = 1
#define GPIO_DCR_PX5_MODE2              (0x02U << GPIO_DCR_PX5_Pos)                  ///< Mode = 2
#define GPIO_DCR_PX5_MODE3              (0x03U << GPIO_DCR_PX5_Pos)                  ///< Mode = 3

#define GPIO_DCR_PX6_Pos                (12)
#define GPIO_DCR_PX6                    (0x03U << GPIO_DCR_PX6_Pos)                  ///< PX6[1:0] bits (pinx configuration bits, pin 6)
#define GPIO_DCR_PX6_MODE0              (0x00U << GPIO_DCR_PX6_Pos)                  ///< Mode = 0
#define GPIO_DCR_PX6_MODE1              (0x01U << GPIO_DCR_PX6_Pos)                  ///< Mode = 1
#define GPIO_DCR_PX6_MODE2              (0x02U << GPIO_DCR_PX6_Pos)                  ///< Mode = 2
#define GPIO_DCR_PX6_MODE3              (0x03U << GPIO_DCR_PX6_Pos)                  ///< Mode = 3

#define GPIO_DCR_PX7_Pos                (14)
#define GPIO_DCR_PX7                    (0x03U << GPIO_DCR_PX7_Pos)                  ///< PX7[1:0] bits (pinx configuration bits, pin 7)
#define GPIO_DCR_PX7_MODE0              (0x00U << GPIO_DCR_PX7_Pos)                  ///< Mode = 0
#define GPIO_DCR_PX7_MODE1              (0x01U << GPIO_DCR_PX7_Pos)                  ///< Mode = 1
#define GPIO_DCR_PX7_MODE2              (0x02U << GPIO_DCR_PX7_Pos)                  ///< Mode = 2
#define GPIO_DCR_PX7_MODE3              (0x03U << GPIO_DCR_PX7_Pos)                  ///< Mode = 3

#define GPIO_DCR_PX8_Pos                (16)
#define GPIO_DCR_PX8                    (0x03U << GPIO_DCR_PX8_Pos)                  ///< PX8[1:0] bits (pinx configuration bits, pin 8)
#define GPIO_DCR_PX8_MODE0              (0x00U << GPIO_DCR_PX8_Pos)                  ///< Mode = 0
#define GPIO_DCR_PX8_MODE1              (0x01U << GPIO_DCR_PX8_Pos)                  ///< Mode = 1
#define GPIO_DCR_PX8_MODE2              (0x02U << GPIO_DCR_PX8_Pos)                  ///< Mode = 2
#define GPIO_DCR_PX8_MODE3              (0x03U << GPIO_DCR_PX8_Pos)                  ///< Mode = 3

#define GPIO_DCR_PX9_Pos                (18)
#define GPIO_DCR_PX9                    (0x03U << GPIO_DCR_PX9_Pos)                  ///< PX9[1:0] bits (pinx configuration bits, pin 9)
#define GPIO_DCR_PX9_MODE0              (0x00U << GPIO_DCR_PX9_Pos)                  ///< Mode = 0
#define GPIO_DCR_PX9_MODE1              (0x01U << GPIO_DCR_PX9_Pos)                  ///< Mode = 1
#define GPIO_DCR_PX9_MODE2              (0x02U << GPIO_DCR_PX9_Pos)                  ///< Mode = 2
#define GPIO_DCR_PX9_MODE3              (0x03U << GPIO_DCR_PX9_Pos)                  ///< Mode = 3

#define GPIO_DCR_PX10_Pos               (20)
#define GPIO_DCR_PX10                   (0x03U << GPIO_DCR_PX10_Pos)                 ///< PX10[1:0] bits (pinx configuration bits, pin 10)
#define GPIO_DCR_PX10_MODE0             (0x00U << GPIO_DCR_PX10_Pos)                 ///< Mode = 0
#define GPIO_DCR_PX10_MODE1             (0x01U << GPIO_DCR_PX10_Pos)                 ///< Mode = 1
#define GPIO_DCR_PX10_MODE2             (0x02U << GPIO_DCR_PX10_Pos)                 ///< Mode = 2
#define GPIO_DCR_PX10_MODE3             (0x03U << GPIO_DCR_PX10_Pos)                 ///< Mode = 3

#define GPIO_DCR_PX11_Pos               (22)
#define GPIO_DCR_PX11                   (0x03U << GPIO_DCR_PX11_Pos)                 ///< PX11[1:0] bits (pinx configuration bits, pin 11)
#define GPIO_DCR_PX11_MODE0             (0x00U << GPIO_DCR_PX11_Pos)                 ///< Mode = 0
#define GPIO_DCR_PX11_MODE1             (0x01U << GPIO_DCR_PX11_Pos)                 ///< Mode = 1
#define GPIO_DCR_PX11_MODE2             (0x02U << GPIO_DCR_PX11_Pos)                 ///< Mode = 2
#define GPIO_DCR_PX11_MODE3             (0x03U << GPIO_DCR_PX11_Pos)                 ///< Mode = 3
#define GPIO_DCR_PX12_Pos               (24)
#define GPIO_DCR_PX12                   (0x03U << GPIO_DCR_PX12_Pos)                 ///< PX12[1:0] bits (pinx configuration bits, pin 12)
#define GPIO_DCR_PX12_MODE0             (0x00U << GPIO_DCR_PX12_Pos)                 ///< Mode = 0
#define GPIO_DCR_PX12_MODE1             (0x01U << GPIO_DCR_PX12_Pos)                 ///< Mode = 1
#define GPIO_DCR_PX12_MODE2             (0x02U << GPIO_DCR_PX12_Pos)                 ///< Mode = 2
#define GPIO_DCR_PX12_MODE3             (0x03U << GPIO_DCR_PX12_Pos)                 ///< Mode = 3
#define GPIO_DCR_PX13_Pos               (26)
#define GPIO_DCR_PX13                   (0x03U << GPIO_DCR_PX13_Pos)                 ///< PX13[1:0] bits (pinx configuration bits, pin 13)
#define GPIO_DCR_PX13_MODE0             (0x00U << GPIO_DCR_PX13_Pos)                 ///< Mode = 0
#define GPIO_DCR_PX13_MODE1             (0x01U << GPIO_DCR_PX13_Pos)                 ///< Mode = 1
#define GPIO_DCR_PX13_MODE2             (0x02U << GPIO_DCR_PX13_Pos)                 ///< Mode = 2
#define GPIO_DCR_PX13_MODE3             (0x03U << GPIO_DCR_PX13_Pos)                 ///< Mode = 3

#define GPIO_DCR_PX14_Pos               (28)
#define GPIO_DCR_PX14                   (0x03U << GPIO_DCR_PX14_Pos)                 ///< PX14[1:0] bits (pinx configuration bits, pin 14)
#define GPIO_DCR_PX14_MODE0             (0x00U << GPIO_DCR_PX14_Pos)                 ///< Mode = 0
#define GPIO_DCR_PX14_MODE1             (0x01U << GPIO_DCR_PX14_Pos)                 ///< Mode = 1
#define GPIO_DCR_PX14_MODE2             (0x02U << GPIO_DCR_PX14_Pos)                 ///< Mode = 2
#define GPIO_DCR_PX14_MODE3             (0x03U << GPIO_DCR_PX14_Pos)                 ///< Mode = 3
#define GPIO_DCR_PX15_Pos               (30)
#define GPIO_DCR_PX15                   (0x03U << GPIO_DCR_PX15_Pos)                 ///< PX15[1:0] bits (pinx configuration bits, pin 15)
#define GPIO_DCR_PX15_MODE0             (0x00U << GPIO_DCR_PX15_Pos)                 ///< Mode = 0
#define GPIO_DCR_PX15_MODE1             (0x01U << GPIO_DCR_PX15_Pos)                 ///< Mode = 1
#define GPIO_DCR_PX15_MODE2             (0x02U << GPIO_DCR_PX15_Pos)                 ///< Mode = 2
#define GPIO_DCR_PX15_MODE3             (0x03U << GPIO_DCR_PX15_Pos)                 ///< Mode = 3
////////////////////////////////////////////////////////////////////////////////
/// @brief GPIO_AFRL Register Bit Definition
////////////////////////////////////////////////////////////////////////////////
#define GPIO_AFRL_AFR0_Pos              (0)
#define GPIO_AFRL_AFR0                  (0x0FU << GPIO_AFRL_AFR0_Pos)           ///< Multiplexing function selection for bit 0 of portx
#define GPIO_AFRL_AFR1_Pos              (4)
#define GPIO_AFRL_AFR1                  (0x0FU << GPIO_AFRL_AFR1_Pos)           ///< Multiplexing function selection for bit 1 of portx
#define GPIO_AFRL_AFR2_Pos              (8)
#define GPIO_AFRL_AFR2                  (0x0FU << GPIO_AFRL_AFR2_Pos)           ///< Multiplexing function selection for bit 2 of portx
#define GPIO_AFRL_AFR3_Pos              (12)
#define GPIO_AFRL_AFR3                  (0x0FU << GPIO_AFRL_AFR3_Pos)           ///< Multiplexing function selection for bit 3 of portx
#define GPIO_AFRL_AFR4_Pos              (16)
#define GPIO_AFRL_AFR4                  (0x0FU << GPIO_AFRL_AFR4_Pos)           ///< Multiplexing function selection for bit 4 of portx
#define GPIO_AFRL_AFR5_Pos              (20)
#define GPIO_AFRL_AFR5                  (0x0FU << GPIO_AFRL_AFR5_Pos)           ///< Multiplexing function selection for bit 5 of portx
#define GPIO_AFRL_AFR6_Pos              (24)
#define GPIO_AFRL_AFR6                  (0x0FU << GPIO_AFRL_AFR6_Pos)           ///< Multiplexing function selection for bit 6 of portx
#define GPIO_AFRL_AFR7_Pos              (28)
#define GPIO_AFRL_AFR7                  (0x0FU << GPIO_AFRL_AFR7_Pos)           ///< Multiplexing function selection for bit 7 of portx

////////////////////////////////////////////////////////////////////////////////
/// @brief GPIO_AFRH Register Bit Definition
////////////////////////////////////////////////////////////////////////////////
#define GPIO_AFRH_AFR8_Pos              (0)
#define GPIO_AFRH_AFR8                  (0x0FU << GPIO_AFRH_AFR8_Pos)           ///< Multiplexing function selection for bit 8 of portx
#define GPIO_AFRH_AFR9_Pos              (4)
#define GPIO_AFRH_AFR9                  (0x0FU << GPIO_AFRH_AFR9_Pos)           ///< Multiplexing function selection for bit 9 of portx
#define GPIO_AFRH_AFR10_Pos             (8)
#define GPIO_AFRH_AFR10                 (0x0FU << GPIO_AFRH_AFR10_Pos)          ///< Multiplexing function selection for bit 10 of portx
#define GPIO_AFRH_AFR11_Pos             (12)
#define GPIO_AFRH_AFR11                 (0x0FU << GPIO_AFRH_AFR11_Pos)          ///< Multiplexing function selection for bit 11 of portx
#define GPIO_AFRH_AFR12_Pos             (16)
#define GPIO_AFRH_AFR12                 (0x0FU << GPIO_AFRH_AFR12_Pos)          ///< Multiplexing function selection for bit 12 of portx
#define GPIO_AFRH_AFR13_Pos             (20)
#define GPIO_AFRH_AFR13                 (0x0FU << GPIO_AFRH_AFR13_Pos)          ///< Multiplexing function selection for bit 13 of portx
#define GPIO_AFRH_AFR14_Pos             (24)
#define GPIO_AFRH_AFR14                 (0x0FU << GPIO_AFRH_AFR14_Pos)          ///< Multiplexing function selection for bit 14 of portx
#define GPIO_AFRH_AFR15_Pos             (28)
#define GPIO_AFRH_AFR15                 (0x0FU << GPIO_AFRH_AFR15_Pos)          ///< Multiplexing function selection for bit 15 of portx
#define GPIO_AF_MODEMASK                (0x0FU)                                 ///< Mode = 0
#define GPIO_AF_MODE0                   (0x00U)                                 ///< Mode = 0
#define GPIO_AF_MODE1                   (0x01U)                                 ///< Mode = 1
#define GPIO_AF_MODE2                   (0x02U)                                 ///< Mode = 2
#define GPIO_AF_MODE3                   (0x03U)                                 ///< Mode = 3
#define GPIO_AF_MODE4                   (0x04U)                                 ///< Mode = 4
#define GPIO_AF_MODE5                   (0x05U)                                 ///< Mode = 5
#define GPIO_AF_MODE6                   (0x06U)                                 ///< Mode = 6
#define GPIO_AF_MODE7                   (0x07U)                                 ///< Mode = 7
#define GPIO_AF_MODE8                   (0x08U)                                 ///< Mode = 8 
#define GPIO_AF_MODE9                   (0x09U)                                 ///< Mode = 9 
#define GPIO_AF_MODE10                  (0x0AU)                                 ///< Mode = 10
#define GPIO_AF_MODE11                  (0x0BU)                                 ///< Mode = 11
#define GPIO_AF_MODE12                  (0x0CU)                                 ///< Mode = 12
#define GPIO_AF_MODE13                  (0x0DU)                                 ///< Mode = 13
#define GPIO_AF_MODE14                  (0x0EU)                                 ///< Mode = 14
#define GPIO_AF_MODE15                  (0x0FU)                                 ///< Mode = 15




/// @}

/// @}

/// @}

////////////////////////////////////////////////////////////////////////////////
#endif
////////////////////////////////////////////////////////////////////////////////
