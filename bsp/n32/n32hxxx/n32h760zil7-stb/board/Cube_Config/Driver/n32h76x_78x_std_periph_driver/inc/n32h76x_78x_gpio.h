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
 * @file n32h76x_78x_gpio.h
 * @author Nations
 * @version v1.0.0
 *
 * @copyright Copyright (c) 2025, Nations Technologies Inc. All rights reserved.
 */

#ifndef __N32H76X_78X_GPIO_H__
#define __N32H76X_78X_GPIO_H__

#ifdef __cplusplus
extern "C"
{
#endif

#include "n32h76x_78x.h"


   /*** GPIO Structure Definition Start ***/


   /***GPIO Init structure definition***/
typedef struct
{
    uint32_t         Pin;            /* Specifies the GPIO pins to be configured. */
    uint32_t         GPIO_Mode;      /* Specifies the operating mode for the selected pins. */
    uint32_t         GPIO_Pull;      /* Specifies the Pull-up or Pull-Down activation for the selected pins. */
    uint32_t         GPIO_Slew_Rate; /* Specify the reverse speed for the selected pins. */
    uint32_t         GPIO_Current;   /* Driving capability of the select pins. */
    uint32_t         GPIO_Alternate; /* Peripheral to be connected to the selected pins. */
}GPIO_InitType;

/** Bit_SET and Bit_RESET enumeration **/  
typedef enum
{
    Bit_RESET = 0,
    Bit_SET
}Bit_OperateType;

/*** GPIO Structure Definition End ***/

/*** GPIO Macro Definition Start ***/
#define GPIO_GET_INDEX(GPIOX_BASE)      (((GPIOX_BASE) - GPIOA_BASE)/0x400UL)

#define GPIO_GET_PERIPH(INDEX)          ((GPIO_Module*)(GPIOA_BASE + (INDEX) * 0x400UL))

/** Bit mask define **/
#define GPIO_PMODE_BIT_MASK                 (GPIO_PMODE_PMODE0)
#define GPIO_PUPD_BIT_MASK                  (GPIO_PUPD_PUPD0)
#define GPIO_AFSEL_BIT_MASK                 (GPIO_AFSEL0_AFSEL0)
#define GPIO_DS_BIT_MASK                    (GPIO_DS_DS0)
#define GPIO_SR_BIT_MASK                    (GPIO_SR_SR0)
#define AFIO_EXTI_BIT_MASK                  (AFIO_EXTI_CFG1_EXTI0)

/** SIP SDRAM priority select in AFIO  **/
#define AFIO_SIP_SDRAM_PRIORITY_HIGH        (AFIO_RMP_CFG_SIP_SDRAM_SEL)
#define AFIO_SIP_SDRAM_PRIORITY_LOW         ((uint32_t)0x00000000U)

/** SPI mode definition in AFIO **/
#define AFIO_SPI1_NSS                       (AFIO_RMP_CFG_SPI1_NSS)
#define AFIO_SPI2_NSS                       (AFIO_RMP_CFG_SPI2_NSS)
#define AFIO_SPI3_NSS                       (AFIO_RMP_CFG_SPI3_NSS)
#define AFIO_SPI4_NSS                       (AFIO_RMP_CFG_SPI4_NSS)
#define AFIO_SPI5_NSS                       (AFIO_RMP_CFG_SPI5_NSS)
#define AFIO_SPI6_NSS                       (AFIO_RMP_CFG_SPI6_NSS)
#define AFIO_SPI7_NSS                       (AFIO_RMP_CFG_SPI7_NSS)
#define AFIO_SPI_NSS_HIGH_IMPEDANCE         ((uint32_t)0x00000000U)
#define AFIO_SPI_NSS_HIGH_LEVEL             (AFIO_RMP_CFG_SPI1_NSS)

/** SIP FLASH MODE SEL in AFIO **/
#define AFIO_FLASH0                         ((uint32_t)0x00000000U)                                    // IS25WJ032F
#define AFIO_FLASH1                         AFIO_RMP_CFG_SIP_FLASHSEL_0                                // IS25LP016D
#define AFIO_FLASH2                         AFIO_RMP_CFG_SIP_FLASHSEL_1                                // XM25LU32CK 
#define AFIO_FLASH3                         AFIO_RMP_CFG_SIP_FLASHSEL_1 | AFIO_RMP_CFG_SIP_FLASHSEL_0  // GT25Q16A
#define AFIO_FLASH4                         AFIO_RMP_CFG_SIP_FLASHSEL_2                                // GT25Q32A
#define AFIO_DISFLASH                       AFIO_RMP_CFG_SIP_FLASHSEL_2 | AFIO_RMP_CFG_SIP_FLASHSEL_1 | AFIO_RMP_CFG_SIP_FLASHSEL_0 // Disable SIP segment (switch to Main IOM)  Default

/** EXTI Analog Filter definition in AFIO  **/
#define AFIO_EXTI_FILTER_ENABLE             ((uint32_t)0x00000000U)
#define AFIO_EXTI_FILTER_DISABLE            (AFIO_RMP_CFG_EXTI_AFLTBYPS)

/** DBG enable definition in AFIO  **/      
#define AFIO_SELECT_SPI1                    (AFIO_RMP_CFG_SPI1_SEL)
#define AFIO_SELECT_SPI2                    (AFIO_RMP_CFG_SPI2_SEL)
#define AFIO_SELECT_SPI3                    (AFIO_RMP_CFG_SPI3_SEL)
#define AFIO_SELECT_SPI4                    (AFIO_RMP_CFG_SPI4_SEL)
#define I2S_MODE                            ((uint32_t)0x00000000U)
#define SPI_MODE                            (AFIO_RMP_CFG_SPI1_SEL)

/** SDMMC clk select in AFIO  **/           
#define SDMMC1_CLKFB                        (AFIO_RMP_CFG_SDMMC1_CLKFB)
#define SDMMC2_CLKFB                        (AFIO_RMP_CFG_SDMMC2_CLKFB)
                                            
#define I2S1_FULLDUPLEX                     ((uint32_t)0x00000000)
#define I2S2_FULLDUPLEX                     (AFIO_RMP_CFG_I2S_FDUP_0)
#define I2S3_FULLDUPLEX                     (AFIO_RMP_CFG_I2S_FDUP_1)
#define I2S4_FULLDUPLEX                     (AFIO_RMP_CFG_I2S_FDUP_0 | AFIO_RMP_CFG_I2S_FDUP_1)

#define SIP_Mode_FAST                       (GPIO_SR_FAST_SLEW)
#define SIP_Mode_SLOW                       (GPIO_SR_SLOW_SLEW)

/** XSPI BigEndian  select in AFIO  **/
#define XSPI1_ENDIAN                        (AFIO_RMP_CFG_XSPI1_EDN)
#define XSPI2_ENDIAN                        (AFIO_RMP_CFG_XSPI2_EDN)
#define XSPI_LITTLE_ENDIAN                  ((uint32_t)0x00000000U)
#define XSPI_BIG_ENDIAN                     (AFIO_RMP_CFG_XSPI1_EDN)

/** FEMC NAND SRAM select in AFIO  **/      
#define FEMC_NAND_SEL                       (AFIO_RMP_CFG_FEMCSEL)
#define FEMC_SRAM_SEL                       ((uint32_t)0x00000000U)
                                            
/** FEMC NO_BYTE STROBE select in AFIO  **/ 
#define NO_BYTE_STROBE                      (AFIO_RMP_CFG_FEMC_NOBYTE)
#define BYTE_STROBE                         ((uint32_t)0x00000000U)

/** ETH2 PHY select in AFIO  **/
#define ETH2_RMII_SEL                       (AFIO_RMP_CFG_ETH2_PHY)
#define ETH2_MII_SEL                        ((uint32_t)0x00000000U)

/** ETH1 PHY select in AFIO  **/
#define ETH1_GMII_SEL                       ((uint32_t)0x00000000U)
#define ETH1_RGMII_SEL                      (AFIO_RMP_CFG_ETH1_PHY_0)
#define ETH1_RMII_SEL                       (AFIO_RMP_CFG_ETH1_PHY_1)
#define ETH1_MII_SEL                        (AFIO_RMP_CFG_ETH1_PHY_0 | AFIO_RMP_CFG_ETH1_PHY_1)

/** Bit mask define **/
#define GPIO_PUPD_BIT_MASK                  (GPIO_PUPD_PUPD0)
#define GPIO_DS_BIT_MASK                    (GPIO_DS_DS0)
#define GPIO_SR_BIT_MASK                    (GPIO_SR_SR0)

/** GPIO_mode_define **/
#define GPIO_MODE_OD_MARK                   (GPIO_POTYPE_OPEN_DRAIN << 4)

#define GPIO_MODE_INPUT                     (GPIO_PMODE_INPUT)                          /* Input Floating Mode */
#define GPIO_MODE_OUTPUT_PP                 (GPIO_PMODE_OUTPUT)                         /* Output Push Pull Mode */
#define GPIO_MODE_OUTPUT_OD                 (GPIO_PMODE_OUTPUT | GPIO_MODE_OD_MARK)     /* Output Open Drain Mode */
#define GPIO_MODE_AF_PP                     (GPIO_PMODE_AF_OUTPUT)                      /* Alternate Function Push Pull Mode  */
#define GPIO_MODE_AF_OD                     (GPIO_PMODE_AF_OUTPUT | GPIO_MODE_OD_MARK)  /* Alternate Function Open Drain Mode */
#define GPIO_MODE_ANALOG                    (GPIO_PMODE_ANALOG)                         /* Analog Mode */

/** GPIO pins define **/
#define GPIO_PIN_0                          ((uint16_t)0x0001U)  /* Pin 0 selected    */
#define GPIO_PIN_1                          ((uint16_t)0x0002U)  /* Pin 1 selected    */
#define GPIO_PIN_2                          ((uint16_t)0x0004U)  /* Pin 2 selected    */
#define GPIO_PIN_3                          ((uint16_t)0x0008U)  /* Pin 3 selected    */
#define GPIO_PIN_4                          ((uint16_t)0x0010U)  /* Pin 4 selected    */
#define GPIO_PIN_5                          ((uint16_t)0x0020U)  /* Pin 5 selected    */
#define GPIO_PIN_6                          ((uint16_t)0x0040U)  /* Pin 6 selected    */
#define GPIO_PIN_7                          ((uint16_t)0x0080U)  /* Pin 7 selected    */
#define GPIO_PIN_8                          ((uint16_t)0x0100U)  /* Pin 8 selected    */
#define GPIO_PIN_9                          ((uint16_t)0x0200U)  /* Pin 9 selected    */
#define GPIO_PIN_10                         ((uint16_t)0x0400U)  /* Pin 10 selected   */
#define GPIO_PIN_11                         ((uint16_t)0x0800U)  /* Pin 11 selected   */
#define GPIO_PIN_12                         ((uint16_t)0x1000U)  /* Pin 12 selected   */
#define GPIO_PIN_13                         ((uint16_t)0x2000U)  /* Pin 13 selected   */
#define GPIO_PIN_14                         ((uint16_t)0x4000U)  /* Pin 14 selected   */
#define GPIO_PIN_15                         ((uint16_t)0x8000U)  /* Pin 15 selected   */
#define GPIO_PIN_ALL                        ((uint16_t)0xFFFFU)  /* All pins selected */
#define GPIO_PIN_NONE                       ((uint16_t)0x0000U)  /* None pin selected */

/** GPIO Pull-Up or Pull-Down Activation **/
#define GPIO_NO_PULL                        (GPIO_PUPD_NO_PULL)     /* No Pull-up or Pull-down activation */
#define GPIO_PULL_UP                        (GPIO_PUPD_PULL_UP)     /* Pull-up activation */
#define GPIO_PULL_DOWN                      (GPIO_PUPD_PULL_DOWN)   /* Pull-down activation */

/** GPIO Drive strength config **/
#define GPIO_DC_2mA                         (GPIO_DS_2mA)
#define GPIO_DC_4mA                         (GPIO_DS_4mA)
#define GPIO_DC_8mA                         (GPIO_DS_8mA)
#define GPIO_DC_12mA                        (GPIO_DS_12mA)

#define GPIO_5VTOL_DC_1mA                   (GPIO_DS_2mA)
#define GPIO_5VTOL_DC_2mA                   (GPIO_DS_4mA)
#define GPIO_5VTOL_DC_4mA                   (GPIO_DS_8mA)
#define GPIO_5VTOL_DC_6mA                   (GPIO_DS_12mA)

#define GPIO_SDRAM_DC_1mA                   (GPIO_DS_2mA)
#define GPIO_SDRAM_DC_2mA                   (GPIO_DS_2mA)
#define GPIO_SDRAM_DC_4mA                   (GPIO_DS_4mA)
#define GPIO_SDRAM_DC_5mA                   (GPIO_DS_4mA)
#define GPIO_SDRAM_DC_8mA                   (GPIO_DS_8mA)
#define GPIO_SDRAM_DC_12mA                  (GPIO_DS_12mA)

/** slew rate config **/
#define GPIO_SLEW_RATE_FAST                 (GPIO_SR_FAST_SLEW)
#define GPIO_SLEW_RATE_SLOW                 (GPIO_SR_SLOW_SLEW)

/** GPIO port sources **/
#define GPIOA_PORT_SOURCE                   ((uint8_t)0x00U)
#define GPIOB_PORT_SOURCE                   ((uint8_t)0x01U)
#define GPIOC_PORT_SOURCE                   ((uint8_t)0x02U)
#define GPIOD_PORT_SOURCE                   ((uint8_t)0x03U)
#define GPIOE_PORT_SOURCE                   ((uint8_t)0x04U)
#define GPIOF_PORT_SOURCE                   ((uint8_t)0x05U)
#define GPIOG_PORT_SOURCE                   ((uint8_t)0x06U)
#define GPIOH_PORT_SOURCE                   ((uint8_t)0x07U)
#define GPIOI_PORT_SOURCE                   ((uint8_t)0x08U)
#define GPIOJ_PORT_SOURCE                   ((uint8_t)0x09U)
#define GPIOK_PORT_SOURCE                   ((uint8_t)0x0AU)

/** GPIO pin sources **/
#define GPIO_PIN_SOURCE0                    ((uint8_t)0x00U) /* Pin 0 selected    */
#define GPIO_PIN_SOURCE1                    ((uint8_t)0x01U) /* Pin 1 selected    */
#define GPIO_PIN_SOURCE2                    ((uint8_t)0x02U) /* Pin 2 selected    */
#define GPIO_PIN_SOURCE3                    ((uint8_t)0x03U) /* Pin 3 selected    */
#define GPIO_PIN_SOURCE4                    ((uint8_t)0x04U) /* Pin 4 selected    */
#define GPIO_PIN_SOURCE5                    ((uint8_t)0x05U) /* Pin 5 selected    */
#define GPIO_PIN_SOURCE6                    ((uint8_t)0x06U) /* Pin 6 selected    */
#define GPIO_PIN_SOURCE7                    ((uint8_t)0x07U) /* Pin 7 selected    */
#define GPIO_PIN_SOURCE8                    ((uint8_t)0x08U) /* Pin 8 selected    */
#define GPIO_PIN_SOURCE9                    ((uint8_t)0x09U) /* Pin 9 selected    */
#define GPIO_PIN_SOURCE10                   ((uint8_t)0x0AU) /* Pin 10 selected   */
#define GPIO_PIN_SOURCE11                   ((uint8_t)0x0BU) /* Pin 11 selected   */
#define GPIO_PIN_SOURCE12                   ((uint8_t)0x0CU) /* Pin 12 selected   */
#define GPIO_PIN_SOURCE13                   ((uint8_t)0x0DU) /* Pin 13 selected   */
#define GPIO_PIN_SOURCE14                   ((uint8_t)0x0EU) /* Pin 14 selected   */
#define GPIO_PIN_SOURCE15                   ((uint8_t)0x0FU) /* Pin 15 selected   */

/** GPIOx_Alternate_function_selection Alternate function selection **/
#define GPIO_AF0                            (GPIO_AFSEL_AF0 )
#define GPIO_AF1                            (GPIO_AFSEL_AF1 )
#define GPIO_AF2                            (GPIO_AFSEL_AF2 )
#define GPIO_AF3                            (GPIO_AFSEL_AF3 )
#define GPIO_AF4                            (GPIO_AFSEL_AF4 )
#define GPIO_AF5                            (GPIO_AFSEL_AF5 )
#define GPIO_AF6                            (GPIO_AFSEL_AF6 )
#define GPIO_AF7                            (GPIO_AFSEL_AF7 )
#define GPIO_AF8                            (GPIO_AFSEL_AF8 )
#define GPIO_AF9                            (GPIO_AFSEL_AF9 )
#define GPIO_AF10                           (GPIO_AFSEL_AF10)
#define GPIO_AF11                           (GPIO_AFSEL_AF11)
#define GPIO_AF12                           (GPIO_AFSEL_AF12)
#define GPIO_AF13                           (GPIO_AFSEL_AF13)
#define GPIO_AF14                           (GPIO_AFSEL_AF14)
#define GPIO_AF15                           (GPIO_AFSEL_AF15)
#define GPIO_NO_AF                          (GPIO_AFSEL_AF15)
#define GPIO_NO_AF1                         (GPIO_AFSEL_AF13)   //user can change no alternate function according different GPIOs

#define EXTI_GPIOA_Pin_0             ((uint8_t)0x00)
#define EXTI_GPIOB_Pin_0             ((uint8_t)0x01)
#define EXTI_GPIOC_Pin_0             ((uint8_t)0x02)
#define EXTI_GPIOD_Pin_0             ((uint8_t)0x03)
#define EXTI_GPIOE_Pin_0             ((uint8_t)0x04)
#define EXTI_GPIOF_Pin_0             ((uint8_t)0x05)
#define EXTI_GPIOG_Pin_0             ((uint8_t)0x06)
#define EXTI_GPIOH_Pin_0             ((uint8_t)0x07)
#define EXTI_GPIOI_Pin_0             ((uint8_t)0x08)
#define EXTI_GPIOJ_Pin_0             ((uint8_t)0x09)
#define EXTI_GPIOK_Pin_0             ((uint8_t)0x0A)
    
#define EXTI_GPIOA_Pin_1             ((uint8_t)0x0B)
#define EXTI_GPIOB_Pin_1             ((uint8_t)0x0C)
#define EXTI_GPIOC_Pin_1             ((uint8_t)0x0D)
#define EXTI_GPIOD_Pin_1             ((uint8_t)0x0E)
#define EXTI_GPIOE_Pin_1             ((uint8_t)0x0F)
#define EXTI_GPIOF_Pin_1             ((uint8_t)0x10)
#define EXTI_GPIOG_Pin_1             ((uint8_t)0x11)
#define EXTI_GPIOH_Pin_1             ((uint8_t)0x12)
#define EXTI_GPIOI_Pin_1             ((uint8_t)0x13)
#define EXTI_GPIOJ_Pin_1             ((uint8_t)0x14)
#define EXTI_GPIOK_Pin_1             ((uint8_t)0x15)
    
#define EXTI_GPIOA_Pin_2             ((uint8_t)0x16)
#define EXTI_GPIOB_Pin_2             ((uint8_t)0x17)
#define EXTI_GPIOC_Pin_2             ((uint8_t)0x18)
#define EXTI_GPIOD_Pin_2             ((uint8_t)0x19)
#define EXTI_GPIOE_Pin_2             ((uint8_t)0x1A)
#define EXTI_GPIOF_Pin_2             ((uint8_t)0x1B)
#define EXTI_GPIOG_Pin_2             ((uint8_t)0x1C)
#define EXTI_GPIOH_Pin_2             ((uint8_t)0x1D)
#define EXTI_GPIOI_Pin_2             ((uint8_t)0x1E)
#define EXTI_GPIOJ_Pin_2             ((uint8_t)0x1F)
#define EXTI_GPIOK_Pin_2             ((uint8_t)0x20)
    
#define EXTI_GPIOA_Pin_3             ((uint8_t)0x21)
#define EXTI_GPIOB_Pin_3             ((uint8_t)0x22)
#define EXTI_GPIOC_Pin_3             ((uint8_t)0x23)
#define EXTI_GPIOD_Pin_3             ((uint8_t)0x24)
#define EXTI_GPIOE_Pin_3             ((uint8_t)0x25)
#define EXTI_GPIOF_Pin_3             ((uint8_t)0x26)
#define EXTI_GPIOG_Pin_3             ((uint8_t)0x27)
#define EXTI_GPIOH_Pin_3             ((uint8_t)0x28)
#define EXTI_GPIOI_Pin_3             ((uint8_t)0x29)
#define EXTI_GPIOJ_Pin_3             ((uint8_t)0x2A)
#define EXTI_GPIOK_Pin_3             ((uint8_t)0x2B)
    
#define EXTI_GPIOA_Pin_4             ((uint8_t)0x2C)
#define EXTI_GPIOB_Pin_4             ((uint8_t)0x2D)
#define EXTI_GPIOC_Pin_4             ((uint8_t)0x2E)
#define EXTI_GPIOD_Pin_4             ((uint8_t)0x2F)
#define EXTI_GPIOE_Pin_4             ((uint8_t)0x30)
#define EXTI_GPIOF_Pin_4             ((uint8_t)0x31)
#define EXTI_GPIOG_Pin_4             ((uint8_t)0x32)
#define EXTI_GPIOH_Pin_4             ((uint8_t)0x33)
#define EXTI_GPIOI_Pin_4             ((uint8_t)0x34)
#define EXTI_GPIOJ_Pin_4             ((uint8_t)0x35)
#define EXTI_GPIOK_Pin_4             ((uint8_t)0x36)
    
#define EXTI_GPIOA_Pin_5             ((uint8_t)0x37)
#define EXTI_GPIOB_Pin_5             ((uint8_t)0x38)
#define EXTI_GPIOC_Pin_5             ((uint8_t)0x39)
#define EXTI_GPIOD_Pin_5             ((uint8_t)0x3A)
#define EXTI_GPIOE_Pin_5             ((uint8_t)0x3B)
#define EXTI_GPIOF_Pin_5             ((uint8_t)0x3C)
#define EXTI_GPIOG_Pin_5             ((uint8_t)0x3D)
#define EXTI_GPIOH_Pin_5             ((uint8_t)0x3E)
#define EXTI_GPIOI_Pin_5             ((uint8_t)0x3F)
#define EXTI_GPIOJ_Pin_5             ((uint8_t)0x40)
#define EXTI_GPIOK_Pin_5             ((uint8_t)0x41)
    
#define EXTI_GPIOA_Pin_6             ((uint8_t)0x42)
#define EXTI_GPIOB_Pin_6             ((uint8_t)0x43)
#define EXTI_GPIOC_Pin_6             ((uint8_t)0x44)
#define EXTI_GPIOD_Pin_6             ((uint8_t)0x45)
#define EXTI_GPIOE_Pin_6             ((uint8_t)0x46)
#define EXTI_GPIOF_Pin_6             ((uint8_t)0x47)
#define EXTI_GPIOG_Pin_6             ((uint8_t)0x48)
#define EXTI_GPIOH_Pin_6             ((uint8_t)0x49)
#define EXTI_GPIOI_Pin_6             ((uint8_t)0x4A)
#define EXTI_GPIOJ_Pin_6             ((uint8_t)0x4B)
#define EXTI_GPIOK_Pin_6             ((uint8_t)0x4C)
    
#define EXTI_GPIOA_Pin_7             ((uint8_t)0x4D)
#define EXTI_GPIOB_Pin_7             ((uint8_t)0x4E)
#define EXTI_GPIOC_Pin_7             ((uint8_t)0x4F)
#define EXTI_GPIOD_Pin_7             ((uint8_t)0x50)
#define EXTI_GPIOE_Pin_7             ((uint8_t)0x51)
#define EXTI_GPIOF_Pin_7             ((uint8_t)0x52)
#define EXTI_GPIOG_Pin_7             ((uint8_t)0x53)
#define EXTI_GPIOH_Pin_7             ((uint8_t)0x54)
#define EXTI_GPIOI_Pin_7             ((uint8_t)0x55)
#define EXTI_GPIOJ_Pin_7             ((uint8_t)0x56)
#define EXTI_GPIOK_Pin_7             ((uint8_t)0x57)
    
#define EXTI_GPIOA_Pin_8             ((uint8_t)0x58)
#define EXTI_GPIOB_Pin_8             ((uint8_t)0x59)
#define EXTI_GPIOC_Pin_8             ((uint8_t)0x5A)
#define EXTI_GPIOD_Pin_8             ((uint8_t)0x5B)
#define EXTI_GPIOE_Pin_8             ((uint8_t)0x5C)
#define EXTI_GPIOF_Pin_8             ((uint8_t)0x5D)
#define EXTI_GPIOG_Pin_8             ((uint8_t)0x5E)
#define EXTI_GPIOH_Pin_8             ((uint8_t)0x5F)
#define EXTI_GPIOI_Pin_8             ((uint8_t)0x60)
#define EXTI_GPIOJ_Pin_8             ((uint8_t)0x61)

#define EXTI_GPIOA_Pin_9            ((uint8_t)0x63)
#define EXTI_GPIOB_Pin_9            ((uint8_t)0x64)
#define EXTI_GPIOC_Pin_9            ((uint8_t)0x65)
#define EXTI_GPIOD_Pin_9            ((uint8_t)0x66)
#define EXTI_GPIOE_Pin_9            ((uint8_t)0x67)
#define EXTI_GPIOF_Pin_9            ((uint8_t)0x68)
#define EXTI_GPIOG_Pin_9            ((uint8_t)0x69)
#define EXTI_GPIOH_Pin_9            ((uint8_t)0x6A)
#define EXTI_GPIOI_Pin_9            ((uint8_t)0x6B)
#define EXTI_GPIOJ_Pin_9            ((uint8_t)0x6C)

#define EXTI_GPIOA_Pin_10            ((uint8_t)0x6E)
#define EXTI_GPIOB_Pin_10            ((uint8_t)0x6F)
#define EXTI_GPIOC_Pin_10            ((uint8_t)0x70)
#define EXTI_GPIOD_Pin_10            ((uint8_t)0x71)
#define EXTI_GPIOE_Pin_10            ((uint8_t)0x72)
#define EXTI_GPIOF_Pin_10            ((uint8_t)0x73)
#define EXTI_GPIOG_Pin_10            ((uint8_t)0x74)
#define EXTI_GPIOH_Pin_10            ((uint8_t)0x75)
#define EXTI_GPIOI_Pin_10            ((uint8_t)0x76)
#define EXTI_GPIOJ_Pin_10            ((uint8_t)0x77)

#define EXTI_GPIOA_Pin_11            ((uint8_t)0x79)
#define EXTI_GPIOB_Pin_11            ((uint8_t)0x7A)
#define EXTI_GPIOC_Pin_11            ((uint8_t)0x7B)
#define EXTI_GPIOD_Pin_11            ((uint8_t)0x7C)
#define EXTI_GPIOE_Pin_11            ((uint8_t)0x7D)
#define EXTI_GPIOF_Pin_11            ((uint8_t)0x7E)
#define EXTI_GPIOG_Pin_11            ((uint8_t)0x7F)
#define EXTI_GPIOH_Pin_11            ((uint8_t)0x80)
#define EXTI_GPIOI_Pin_11            ((uint8_t)0x81)
#define EXTI_GPIOJ_Pin_11            ((uint8_t)0x82)

#define EXTI_GPIOA_Pin_12            ((uint8_t)0x84)
#define EXTI_GPIOB_Pin_12            ((uint8_t)0x85)
#define EXTI_GPIOC_Pin_12            ((uint8_t)0x86)
#define EXTI_GPIOD_Pin_12            ((uint8_t)0x87)
#define EXTI_GPIOE_Pin_12            ((uint8_t)0x88)
#define EXTI_GPIOF_Pin_12            ((uint8_t)0x89)
#define EXTI_GPIOG_Pin_12            ((uint8_t)0x8A)
#define EXTI_GPIOH_Pin_12            ((uint8_t)0x8B)
#define EXTI_GPIOI_Pin_12            ((uint8_t)0x8C)
#define EXTI_GPIOJ_Pin_12            ((uint8_t)0x8D)

#define EXTI_GPIOA_Pin_13            ((uint8_t)0x8F)
#define EXTI_GPIOB_Pin_13            ((uint8_t)0x90)
#define EXTI_GPIOC_Pin_13            ((uint8_t)0x91)
#define EXTI_GPIOD_Pin_13            ((uint8_t)0x92)
#define EXTI_GPIOE_Pin_13            ((uint8_t)0x93)
#define EXTI_GPIOF_Pin_13            ((uint8_t)0x94)
#define EXTI_GPIOG_Pin_13            ((uint8_t)0x95)
#define EXTI_GPIOH_Pin_13            ((uint8_t)0x96)
#define EXTI_GPIOI_Pin_13            ((uint8_t)0x97)
#define EXTI_GPIOJ_Pin_13            ((uint8_t)0x98)

#define EXTI_GPIOA_Pin_14            ((uint8_t)0x9A)
#define EXTI_GPIOB_Pin_14            ((uint8_t)0x9B)
#define EXTI_GPIOC_Pin_14            ((uint8_t)0x9C)
#define EXTI_GPIOD_Pin_14            ((uint8_t)0x9D)
#define EXTI_GPIOE_Pin_14            ((uint8_t)0x9E)
#define EXTI_GPIOF_Pin_14            ((uint8_t)0x9F)
#define EXTI_GPIOG_Pin_14            ((uint8_t)0xA0)
#define EXTI_GPIOH_Pin_14            ((uint8_t)0xA1)
#define EXTI_GPIOI_Pin_14            ((uint8_t)0xA2)
#define EXTI_GPIOJ_Pin_14            ((uint8_t)0xA3)

#define EXTI_GPIOA_Pin_15            ((uint8_t)0xA5)
#define EXTI_GPIOB_Pin_15            ((uint8_t)0xA6)
#define EXTI_GPIOC_Pin_15            ((uint8_t)0xA7)
#define EXTI_GPIOD_Pin_15            ((uint8_t)0xA8)
#define EXTI_GPIOE_Pin_15            ((uint8_t)0xA9)
#define EXTI_GPIOF_Pin_15            ((uint8_t)0xAA)
#define EXTI_GPIOG_Pin_15            ((uint8_t)0xAB)
#define EXTI_GPIOH_Pin_15            ((uint8_t)0xAC)
#define EXTI_GPIOI_Pin_15            ((uint8_t)0xAD)
#define EXTI_GPIOJ_Pin_15            ((uint8_t)0xAE)

#define AFIO_TOL5V_PA0               (AFIO_TOL5V_CFG1_PA0TOLENN)
#define AFIO_TOL5V_PA0_C             (AFIO_TOL5V_CFG1_PA0_C_TOLENN)
#define AFIO_TOL5V_PA1               (AFIO_TOL5V_CFG1_PA1TOLENN)
#define AFIO_TOL5V_PA1_C             (AFIO_TOL5V_CFG1_PA1_C_TOLENN)
#define AFIO_TOL5V_PA2               (AFIO_TOL5V_CFG1_PA2TOLENN)
#define AFIO_TOL5V_PA3               (AFIO_TOL5V_CFG1_PA3TOLENN)
#define AFIO_TOL5V_PA4               (AFIO_TOL5V_CFG1_PA4TOLENN)
#define AFIO_TOL5V_PA5               (AFIO_TOL5V_CFG1_PA5TOLENN)
#define AFIO_TOL5V_PA6               (AFIO_TOL5V_CFG1_PA6TOLENN)
#define AFIO_TOL5V_PA7               (AFIO_TOL5V_CFG1_PA7TOLENN)

#define AFIO_TOL5V_PB0               (AFIO_TOL5V_CFG2_PB0TOLENN)
#define AFIO_TOL5V_PB1               (AFIO_TOL5V_CFG2_PB1TOLENN)

#define AFIO_TOL5V_PC0               (AFIO_TOL5V_CFG3_PC0TOLENN)
#define AFIO_TOL5V_PC1               (AFIO_TOL5V_CFG3_PC1TOLENN)
#define AFIO_TOL5V_PC2               (AFIO_TOL5V_CFG3_PC2TOLENN)
#define AFIO_TOL5V_PC2_C             (AFIO_TOL5V_CFG3_PC2_C_TOLENN)
#define AFIO_TOL5V_PC3               (AFIO_TOL5V_CFG3_PC3TOLENN)
#define AFIO_TOL5V_PC3_C             (AFIO_TOL5V_CFG3_PC3_C_TOLENN)
#define AFIO_TOL5V_PC4               (AFIO_TOL5V_CFG3_PC4TOLENN)
#define AFIO_TOL5V_PC5               (AFIO_TOL5V_CFG3_PC5TOLENN)
#define AFIO_TOL5V_PC6               (AFIO_TOL5V_CFG3_PC6TOLENN)
#define AFIO_TOL5V_PC8               (AFIO_TOL5V_CFG3_PC8TOLENN)
#define AFIO_TOL5V_PC13              (AFIO_TOL5V_CFG3_PC13TOLENN)

#define AFIO_TOL5V_PF3               (AFIO_TOL5V_CFG4_PF3TOLENN)
#define AFIO_TOL5V_PF4               (AFIO_TOL5V_CFG4_PF4TOLENN)
#define AFIO_TOL5V_PF5               (AFIO_TOL5V_CFG4_PF5TOLENN)
#define AFIO_TOL5V_PF6               (AFIO_TOL5V_CFG4_PF6TOLENN)
#define AFIO_TOL5V_PF7               (AFIO_TOL5V_CFG4_PF7TOLENN)
#define AFIO_TOL5V_PF8               (AFIO_TOL5V_CFG4_PF8TOLENN)
#define AFIO_TOL5V_PF9               (AFIO_TOL5V_CFG4_PF9TOLENN)
#define AFIO_TOL5V_PF10              (AFIO_TOL5V_CFG4_PF10TOLENN)
#define AFIO_TOL5V_PF11              (AFIO_TOL5V_CFG4_PF11TOLENN)
#define AFIO_TOL5V_PF12              (AFIO_TOL5V_CFG4_PF12TOLENN)
#define AFIO_TOL5V_PF13              (AFIO_TOL5V_CFG4_PF13TOLENN)
#define AFIO_TOL5V_PF14              (AFIO_TOL5V_CFG4_PF14TOLENN)

#define AFIO_TOL5V_PH2               (AFIO_TOL5V_CFG5_PH2TOLENN)
#define AFIO_TOL5V_PH3               (AFIO_TOL5V_CFG5_PH3TOLENN)
#define AFIO_TOL5V_PH4               (AFIO_TOL5V_CFG5_PH4TOLENN)
#define AFIO_TOL5V_PH5               (AFIO_TOL5V_CFG5_PH5TOLENN)

#define AFIO_TOL5V_PI8               (AFIO_TOL5V_CFG6_PI8TOLENN)
#define AFIO_TOL5V_PI15              (AFIO_TOL5V_CFG6_PI15TOLENN)

#define AFIO_TOL5V_PJ0               (AFIO_TOL5V_CFG7_PJ0TOLENN)
#define AFIO_TOL5V_PJ3               (AFIO_TOL5V_CFG7_PJ3TOLENN)
#define AFIO_TOL5V_PJ4               (AFIO_TOL5V_CFG7_PJ4TOLENN)
#define AFIO_TOL5V_PJ5               (AFIO_TOL5V_CFG7_PJ5TOLENN)
#define AFIO_TOL5V_PJ6               (AFIO_TOL5V_CFG7_PJ6TOLENN)
#define AFIO_TOL5V_PJ7               (AFIO_TOL5V_CFG7_PJ7TOLENN)


typedef enum
{
    SHRT_FAULT_CHANNEL_1 = 0,
    SHRT_FAULT_CHANNEL_2,
    SHRT_FAULT_CHANNEL_3,
    SHRT_FAULT_CHANNEL_4,
    SHRT_FAULT_CHANNEL_5,
    SHRT_FAULT_CHANNEL_6,
}SHRT_FAULT_CHANNEL_NUM;

/*FAULT*/
typedef enum
{
    SHRT1_FAULT_CHANNEL_PA15 = 1,
    SHRT1_FAULT_CHANNEL_PB3,
    SHRT1_FAULT_CHANNEL_PC11,
    SHRT1_FAULT_CHANNEL_PD4,
    SHRT1_FAULT_CHANNEL_PE4,
    SHRT1_FAULT_CHANNEL_PG9,
    SHRT1_FAULT_CHANNEL_PG10,
    SHRT1_FAULT_CHANNEL_PI6,
    SHRT1_FAULT_CHANNEL_PI15,
    SHRT1_FAULT_CHANNEL_PK2,
}SHRT1_FAULT_CHANNEL;

typedef enum
{
    SHRT2_FAULT_CHANNEL_PC5 = 1,
    SHRT2_FAULT_CHANNEL_PD1,
    SHRT2_FAULT_CHANNEL_PD15,
    SHRT2_FAULT_CHANNEL_PF9,
    SHRT2_FAULT_CHANNEL_PF13,
    SHRT2_FAULT_CHANNEL_PG1,
    SHRT2_FAULT_CHANNEL_PI0,
    SHRT2_FAULT_CHANNEL_PI9,
    SHRT2_FAULT_CHANNEL_PI13,
    SHRT2_FAULT_CHANNEL_PJ0,
    SHRT2_FAULT_CHANNEL_PK1,
    SHRT2_FAULT_CHANNEL_PK6,
}SHRT2_FAULT_CHANNEL;

typedef enum
{
    SHRT_EXEV_CHANNEL_1 = 0,
    SHRT_EXEV_CHANNEL_2,
    SHRT_EXEV_CHANNEL_3,
    SHRT_EXEV_CHANNEL_4,
    SHRT_EXEV_CHANNEL_5,
    SHRT_EXEV_CHANNEL_6,
    SHRT_EXEV_CHANNEL_7,
    SHRT_EXEV_CHANNEL_8,
    SHRT_EXEV_CHANNEL_9,
    SHRT_EXEV_CHANNEL_10,
}SHRT_EXEV_CHANNEL_NUM;

/*External Event*/
typedef enum
{
    SHRT1_EXEV_CHANNEL_PB4 = 1,
    SHRT1_EXEV_CHANNEL_PB5,
    SHRT1_EXEV_CHANNEL_PB6,
    SHRT1_EXEV_CHANNEL_PB7,
    SHRT1_EXEV_CHANNEL_PC10,
    SHRT1_EXEV_CHANNEL_PC12,
    SHRT1_EXEV_CHANNEL_PD5,
    SHRT1_EXEV_CHANNEL_PD8,
    SHRT1_EXEV_CHANNEL_PD9,
    SHRT1_EXEV_CHANNEL_PE6,
    SHRT1_EXEV_CHANNEL_PG0,
    SHRT1_EXEV_CHANNEL_PG11,
    SHRT1_EXEV_CHANNEL_PG12,
    SHRT1_EXEV_CHANNEL_PG13,
    SHRT1_EXEV_CHANNEL_PI14,
    SHRT1_EXEV_CHANNEL_PJ5,
    SHRT1_EXEV_CHANNEL_PK3,
    SHRT1_EXEV_CHANNEL_PK4,
}SHRT1_EXEV_CHANNEL;

typedef enum
{
    SHRT2_EXEV_CHANNEL_PA2 = 1,
    SHRT2_EXEV_CHANNEL_PC4,
    SHRT2_EXEV_CHANNEL_PD0,
    SHRT2_EXEV_CHANNEL_PD11,
    SHRT2_EXEV_CHANNEL_PE3,
    SHRT2_EXEV_CHANNEL_PE14,
    SHRT2_EXEV_CHANNEL_PF10,
    SHRT2_EXEV_CHANNEL_PG8,
    SHRT2_EXEV_CHANNEL_PG15,
    SHRT2_EXEV_CHANNEL_PH7,
    SHRT2_EXEV_CHANNEL_PH8,
    SHRT2_EXEV_CHANNEL_PH10,
    SHRT2_EXEV_CHANNEL_PH11,
    SHRT2_EXEV_CHANNEL_PH12,
    SHRT2_EXEV_CHANNEL_PI11,
    SHRT2_EXEV_CHANNEL_PJ2,
    SHRT2_EXEV_CHANNEL_PJ14,
    SHRT2_EXEV_CHANNEL_PK0,
}SHRT2_EXEV_CHANNEL;

#define AFIO_SIP_DAT0                       (0x00)
#define AFIO_SIP_DAT1                       (0x01)
#define AFIO_SIP_DAT2                       (0x02)
#define AFIO_SIP_DAT3                       (0x03)
#define AFIO_SIP_DAT4                       (0x04)
#define AFIO_SIP_DAT5                       (0x05)
#define AFIO_SIP_DAT6                       (0x06)
#define AFIO_SIP_DAT7                       (0x07)
#define AFIO_SIP_MASK                       ((uint32_t)0x00000003U)
#define AFIO_SIP_Mode_NO_PULL               (GPIO_PUPD_NO_PULL)     /* No Pull-up or Pull-down activation */
#define AFIO_SIP_Mode_PULL_UP               (GPIO_PUPD_PULL_UP)     /* Pull-up activation */
#define AFIO_SIP_Mode_PULL_DOWN             (GPIO_PUPD_PULL_DOWN)   /* Pull-down activation */

/** AFIO SIP Drive strength config **/
#define SIP_DC_2mA                          (GPIO_DS_2mA)
#define SIP_DC_4mA                          (GPIO_DS_4mA)
#define SIP_DC_8mA                          (GPIO_DS_8mA)
#define SIP_DC_12mA                         (GPIO_DS_12mA)

/** AFIO SIP Slew_Rate **/
#define SIP_Mode_FAST                       (GPIO_SR_FAST_SLEW)
#define SIP_Mode_SLOW                       (GPIO_SR_SLOW_SLEW)

/** ADC switch config **/
#define ADC_SW_PA0_C_MSK                    (AFIO_ADCSW_CFG_SWPA0_C)
#define ADC_SW_PA0_C_ADC2_INP0              (AFIO_ADCSW_CFG_SWPA0_C_0)
#define ADC_SW_PA0_C_ADC2_INP1              (AFIO_ADCSW_CFG_SWPA0_C_1)
#define ADC_SW_PA0_C_ADC1_INP0              (AFIO_ADCSW_CFG_SWPA0_C_2)
#define ADC_SW_PA0_C_ADC1_INP1              (AFIO_ADCSW_CFG_SWPA0_C_3)
#define ADC_SW_PA0_C_CLOSE                  ((uint32_t)0x00000000U)

#define ADC_SW_PC2_C_MSK                    (AFIO_ADCSW_CFG_SWPC2_C)
#define ADC_SW_PC2_C_ADC2_INP0              (AFIO_ADCSW_CFG_SWPC2_C_0)
#define ADC_SW_PC2_C_ADC2_INP1              (AFIO_ADCSW_CFG_SWPC2_C_1)
#define ADC_SW_PC2_C_ADC3_INP0              (AFIO_ADCSW_CFG_SWPC2_C_2)
#define ADC_SW_PC2_C_ADC3_INP1              (AFIO_ADCSW_CFG_SWPC2_C_3)
#define ADC_SW_PC2_C_CLOSE                  ((uint32_t)0x00000000U)

#define ADC_SW_PC3_C_MSK                    (AFIO_ADCSW_CFG_SWPC3_C)
#define ADC_SW_PC3_C_ADC2_INP1              (AFIO_ADCSW_CFG_SWPC3_C_0)
#define ADC_SW_PC3_C_ADC3_INP2              (AFIO_ADCSW_CFG_SWPC3_C_1)
#define ADC_SW_PC3_C_CLOSE                  ((uint32_t)0x00000000U)

#define ADC_SW_PA1_C_MSK                    (AFIO_ADCSW_CFG_SWPA1_C)
#define ADC_SW_PA1_C_ADC2_INP1              (AFIO_ADCSW_CFG_SWPA1_C_0)
#define ADC_SW_PA1_C_ADC1_INP1              (AFIO_ADCSW_CFG_SWPA1_C_1)
#define ADC_SW_PA1_C_CLOSE                  ((uint32_t)0x00000000U)

#define ADC_SW_PI15_MSK                     (AFIO_ADCSW_CFG_SWPI15)
#define ADC_SW_PI15_ADC2_INP17              (AFIO_ADCSW_CFG_SWPI15_0)
#define ADC_SW_PI15_ADC3_INP17              (AFIO_ADCSW_CFG_SWPI15_1)
#define ADC_SW_PI15_CLOSE                   ((uint32_t)0x00000000U)

#define ADC_SW_VBAT_MSK                     (0x00000000)
#define ADC_SW_VBAT_ADC3_INP17              (AFIO_ADCSW_CFG_VBAT)

#define ADC_SW_PJ0_MSK                      (0x00000000)
#define ADC_SW_PJ0_ADC2_INP16               (AFIO_ADCSW_CFG_SW_PJ0)

#define ADC_SW_PJ3_MSK                      (0x00000000)
#define ADC_SW_PJ3_ADC3_INP18               (AFIO_ADCSW_CFG_SW_PJ3)

#define ADC_SW_TEMP_MSK                      (0x00000000)
#define ADC_SW_TEMP_ADC3_INP18               (AFIO_ADCSW_CFG_SW_TEMP)

#define ADC_SW_PJ4_MSK                      (0x00000000)
#define ADC_SW_PJ4_ADC3_INP19               (AFIO_ADCSW_CFG_SW_PJ4)

#define ADC_SW_PJ5_MSK                      (0x00000000)
#define ADC_SW_PJ5_ADC2_INP16               (AFIO_ADCSW_CFG_SW_PJ5)

#define ADC_SW_PJ6_MSK                      (0x00000000)
#define ADC_SW_PJ6_ADC3_INP18               (AFIO_ADCSW_CFG_SW_PJ6)

#define ADC_SW_PJ7_MSK                      (0x00000000)
#define ADC_SW_PJ7_ADC3_INP19               (AFIO_ADCSW_CFG_SW_PJ7)

#define ADC_SW_VREF_MSK                      (0x00000000)
#define ADC_SW_VREF_ADC3_INP19               (AFIO_ADCSW_CFG_VREF)

#define ADC_SW_DAC246_OUT_MSK               (AFIO_ADCSW_CFG_SW_DAC246_OUT)
#define ADC_SW_DAC2_OUT_ADC2_INP17          (AFIO_ADCSW_CFG_SW_DAC2_OUT)
#define ADC_SW_DAC4_OUT_ADC2_INP17          (AFIO_ADCSW_CFG_SW_DAC4_OUT)
#define ADC_SW_DAC6_OUT_ADC2_INP17          (AFIO_ADCSW_CFG_SW_DAC6_OUT)
#define ADC_SW_DAC246_OUT_ADC2_DISABLE      ((uint32_t)0x00000000U)

#define ADC_SW_DAC135_OUT_MSK               (AFIO_ADCSW_CFG_SW_DAC135_OUT)
#define ADC_SW_DAC1_OUT_ADC2_INP16          (AFIO_ADCSW_CFG_SW_DAC1_OUT)
#define ADC_SW_DAC3_OUT_ADC2_INP16          (AFIO_ADCSW_CFG_SW_DAC3_OUT)
#define ADC_SW_DAC5_OUT_ADC2_INP16          (AFIO_ADCSW_CFG_SW_DAC5_OUT)
#define ADC_SW_DAC135_OUT_ADC2_DISABLE      ((uint32_t)0x00000000U)

typedef enum
{
    AFIO_ADC_1 = 2U,
    AFIO_ADC_2 = 1U,
    AFIO_ADC_3 = 0U
}AFIO_ADC_NUM;

typedef enum
{
    AFIO_ADC_ETRR = 0U,
    AFIO_ADC_ETRI = 1U
}AFIO_ADC_ETRType;

typedef enum
{
    AFIO_ADC_TRIG_EXTI_0 = 0x00U,
    AFIO_ADC_TRIG_EXTI_1 = 0x01U,
    AFIO_ADC_TRIG_EXTI_2,
    AFIO_ADC_TRIG_EXTI_3,
    AFIO_ADC_TRIG_EXTI_4,
    AFIO_ADC_TRIG_EXTI_5,
    AFIO_ADC_TRIG_EXTI_6,
    AFIO_ADC_TRIG_EXTI_7,
    AFIO_ADC_TRIG_EXTI_8,
    AFIO_ADC_TRIG_EXTI_9,
    AFIO_ADC_TRIG_EXTI_10,
    AFIO_ADC_TRIG_EXTI_11,
    AFIO_ADC_TRIG_EXTI_12,
    AFIO_ADC_TRIG_EXTI_13,
    AFIO_ADC_TRIG_EXTI_14,
    AFIO_ADC_TRIG_EXTI_15,
}AFIO_ADC_Trig_RemapType;

typedef enum 
{
    AFIO_SDRAM_PIN_PA4 = 0,
    AFIO_SDRAM_PIN_PA5 = 1, 
    AFIO_SDRAM_PIN_PA7, 
    AFIO_SDRAM_PIN_PB5, 
    AFIO_SDRAM_PIN_PB6, 
    AFIO_SDRAM_PIN_PB14,
    AFIO_SDRAM_PIN_PB15,
    AFIO_SDRAM_PIN_PC0,
    AFIO_SDRAM_PIN_PC2,
    AFIO_SDRAM_PIN_PC3,
    AFIO_SDRAM_PIN_PC4,
    AFIO_SDRAM_PIN_PC5,
    AFIO_SDRAM_PIN_PC12,
    AFIO_SDRAM_PIN_PD0,
    AFIO_SDRAM_PIN_PD1,
    AFIO_SDRAM_PIN_PD2,
    AFIO_SDRAM_PIN_PD8,
    AFIO_SDRAM_PIN_PD9,
    AFIO_SDRAM_PIN_PD10,
    AFIO_SDRAM_PIN_PD14,
    AFIO_SDRAM_PIN_PD15,
    AFIO_SDRAM_PIN_PE0,
    AFIO_SDRAM_PIN_PE1,
    AFIO_SDRAM_PIN_PE7,
    AFIO_SDRAM_PIN_PE8,
    AFIO_SDRAM_PIN_PE9,
    AFIO_SDRAM_PIN_PE10,
    AFIO_SDRAM_PIN_PE11,
    AFIO_SDRAM_PIN_PE12,
    AFIO_SDRAM_PIN_PE13,
    AFIO_SDRAM_PIN_PE14,
    AFIO_SDRAM_PIN_PE15,

    AFIO_SDRAM_PIN_PF0,
    AFIO_SDRAM_PIN_PF1,
    AFIO_SDRAM_PIN_PF2,
    AFIO_SDRAM_PIN_PF3,
    AFIO_SDRAM_PIN_PF4,
    AFIO_SDRAM_PIN_PF5,
    AFIO_SDRAM_PIN_PF11,
    AFIO_SDRAM_PIN_PF12,
    AFIO_SDRAM_PIN_PF13,
    AFIO_SDRAM_PIN_PF14,
    AFIO_SDRAM_PIN_PF15,
    AFIO_SDRAM_PIN_PG0,
    AFIO_SDRAM_PIN_PG1,
    AFIO_SDRAM_PIN_PG2,
    AFIO_SDRAM_PIN_PG4,
    AFIO_SDRAM_PIN_PG5,
    AFIO_SDRAM_PIN_PG8,
    AFIO_SDRAM_PIN_PG15,
    AFIO_SDRAM_PIN_PH2,
    AFIO_SDRAM_PIN_PH3,
    AFIO_SDRAM_PIN_PH5,
    AFIO_SDRAM_PIN_PH6,
    AFIO_SDRAM_PIN_PH7,
    AFIO_SDRAM_PIN_PH8,
    AFIO_SDRAM_PIN_PH9,
    AFIO_SDRAM_PIN_PH10,
    AFIO_SDRAM_PIN_PH11,
    AFIO_SDRAM_PIN_PH12,
    AFIO_SDRAM_PIN_PH13,
    AFIO_SDRAM_PIN_PH14,
    AFIO_SDRAM_PIN_PH15,
    AFIO_SDRAM_PIN_PI0,

    AFIO_SDRAM_PIN_PI1,
    AFIO_SDRAM_PIN_PI2,
    AFIO_SDRAM_PIN_PI3,
    AFIO_SDRAM_PIN_PI4,
    AFIO_SDRAM_PIN_PI5,
    AFIO_SDRAM_PIN_PI6,
    AFIO_SDRAM_PIN_PI7,
    AFIO_SDRAM_PIN_PI9,
    AFIO_SDRAM_PIN_PI10
} AFIO_SDRAM_PIN;


/** GPIO_Exported_Functions **/
void GPIO_DeInit( GPIO_Module *GPIOx);
void GPIO_AFIODeInit( void );
void GPIO_InitStruct(GPIO_InitType* InitStruct);
void GPIO_InitPeripheral( GPIO_Module* GPIOx, GPIO_InitType* GPIO_InitStruct);
uint8_t GPIO_ReadInputDataBit( GPIO_Module* GPIOx, uint16_t GPIO_Pin);
uint16_t GPIO_ReadInputData( GPIO_Module* GPIOx );
uint8_t GPIO_ReadOutputDataBit( GPIO_Module* GPIOx, uint16_t GPIO_Pin);
uint16_t GPIO_ReadOutputData( GPIO_Module* GPIOx );
void GPIO_SetBits( GPIO_Module* GPIOx, uint16_t GPIO_Pin);
void GPIO_ResetBits( GPIO_Module* GPIOx, uint16_t GPIO_Pin );
void GPIO_WriteBit( GPIO_Module* GPIOx, uint16_t GPIO_Pin, Bit_OperateType BitVal);
void GPIO_Write( GPIO_Module* GPIOx, uint16_t data_value );
void GPIO_TogglePin(GPIO_Module *GPIOx, uint16_t Pin);
void GPIO_ConfigPinLock( GPIO_Module* GPIOx, uint16_t GPIO_Pin);

void GPIO_ConfigEXTILine(uint8_t EXTI_Line, uint8_t GPIO_PinSource);
void AFIO_ConfigEXTIFilter(uint32_t EXTI_Filter);

void AFIO_ConfigADCExtLineTrigSource(AFIO_ADC_NUM ADC_num, AFIO_ADC_ETRType ADCETRType, AFIO_ADC_Trig_RemapType ADCTrigRemap);

void GPIO_AFIOInitDefault(void);
void AFIO_ConfigSHRT1EXEVPin(SHRT1_EXEV_CHANNEL channel_pin, SHRT_EXEV_CHANNEL_NUM channel_num);
void AFIO_ConfigSHRT1FALTPin(SHRT1_FAULT_CHANNEL channel_pin, SHRT_FAULT_CHANNEL_NUM channel_num);
void AFIO_ConfigSHRT2EXEVPin(SHRT2_EXEV_CHANNEL channel_pin, SHRT_EXEV_CHANNEL_NUM channel_num);
void AFIO_ConfigSHRT2FALTPin(SHRT2_FAULT_CHANNEL channel_pin, SHRT_FAULT_CHANNEL_NUM channel_num);
void AFIO_ConfigSIPFLASHSEL(uint32_t AFIO_FLASH);
void AFIO_ConfigSIPSDRAMPrior(uint32_t priority);
void AFIO_ConfigSPII2SMode(uint32_t AFIO_SPIx_I2Sx, uint32_t PADS_Mode);
void AFIO_ConfigSPINSSMode(uint32_t AFIO_SPIx_NSS, uint32_t NSS_Mode);
void AFIO_ConfigXSPIBigEndian(uint32_t xspi_endian, uint32_t Endian);
void AFIO_ConfigIOFilter(uint8_t Filter_Cycle);
void AFIO_ConfigPinAnFilter(GPIO_Module* GPIOx, uint32_t Pin,FunctionalState cmd);
void AFIO_ConfigPinFilter(GPIO_Module* GPIOx, uint32_t Pin,FunctionalState cmd);
void AFIO_ConfigHSMODE(GPIO_Module* GPIOx, uint32_t Pin, FunctionalState cmd);
void AFIO_ConfigPinTol5VGPIOA(uint32_t Pin,FunctionalState cmd);
void AFIO_ConfigPinTol5VGPIOB(uint32_t Pin,FunctionalState cmd);
void AFIO_ConfigPinTol5VGPIOC(uint32_t Pin,FunctionalState cmd);
void AFIO_ConfigPinTol5VGPIOF(uint32_t Pin,FunctionalState cmd);
void AFIO_ConfigPinTol5VGPIOH(uint32_t Pin,FunctionalState cmd);
void AFIO_ConfigPinTol5VGPIOI(uint32_t Pin,FunctionalState cmd);
void AFIO_ConfigPinTol5VGPIOJ(uint32_t Pin,FunctionalState cmd);
void AFIO_ConfigSDRAMDSNRemap(AFIO_SDRAM_PIN pin, FunctionalState cmd);
void AFIO_ConfigSDRAMDSPRemap(AFIO_SDRAM_PIN pin, FunctionalState cmd);
void AFIO_ConfigSDRAMVREFRemap(AFIO_SDRAM_PIN pin, FunctionalState cmd);
void AFIO_ConfigSDRAMVREFData(uint8_t reg_index, uint32_t data);
void AFIO_ConfigSDRAMDSNData(uint8_t reg_index, uint32_t data);
void AFIO_ConfigSDRAMDSPData(uint8_t reg_index, uint32_t data);
void AFIO_ConfigETH1Mode(uint32_t ETH1_PHY_sel);
void AFIO_ConfigETH2Mode(uint32_t ETH2_PHY_sel);
void AFIO_ConfigFEMCNANDSRAM(uint32_t Nand_Sram_sel);
void AFIO_FEMCNOByteStrobe(uint32_t Byte_Strobes_sel);
void AFIO_I2SFullpuplexSel(uint32_t AFIO_clk_sel);
void AFIO_SDMMCClkSel(uint32_t AFIO_clk_sel, FunctionalState cmd);
void AFIO_ConfigXSPIDecNonce(uint8_t nonce_num, u32 data);
void AFIO_SIPInitPeripheral(uint8_t sip_index, uint32_t pupd, uint32_t slew_rate, uint32_t driver_stength);

void AFIO_ADCSWPJ0Enable(FunctionalState Cmd);
void AFIO_ADCSWPJ3Enable(FunctionalState Cmd);
void AFIO_ADCSWPJ4Enable(FunctionalState Cmd);
void AFIO_ADCSWPJ5Enable(FunctionalState Cmd);
void AFIO_ADCSWPJ6Enable(FunctionalState Cmd);
void AFIO_ADCSWPJ7Enable(FunctionalState Cmd);
void AFIO_ADCSWTEMPEnable(FunctionalState Cmd);
void AFIO_ADCSWVBATEnable(FunctionalState Cmd);
void AFIO_ADCSWVREFEnable(FunctionalState Cmd);

void AFIO_ConfigADCSWDAC246OUT(uint32_t ADCsw);
void AFIO_ConfigADCSWDAC135OUT(uint32_t ADCsw);
void AFIO_ConfigADCSWPA0_C(uint32_t ADCsw);
void AFIO_ConfigADCSWPA1_C(uint32_t ADCsw);
void AFIO_ConfigADCSWPC2_C(uint32_t ADCsw);
void AFIO_ConfigADCSWPC3_C(uint32_t ADCsw);
void AFIO_ConfigADCSWPI15(uint32_t ADCsw);


#ifdef __cplusplus
}

#endif

#endif /* __N32H76X_78X_GPIO_H__ */
