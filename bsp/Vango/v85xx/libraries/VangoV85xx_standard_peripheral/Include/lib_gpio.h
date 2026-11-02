/**
  ******************************************************************************
  * @file    lib_gpio.h 
  * @author  Application Team
  * @version V4.4.0
  * @date    2018-09-27
  * @brief   GPIO library.
  ******************************************************************************
  * @attention
  *
  ******************************************************************************
  */
#ifndef __LIB_GPIO_H
#define __LIB_GPIO_H

#ifdef __cplusplus
 extern "C" {
#endif

#include "target.h"
   
typedef struct
{
  uint32_t GPIO_Pin;
  uint32_t GPIO_Mode;
} GPIO_InitType;

/**
  * @brief Bit_State_enumeration
  */
typedef enum {
    Bit_RESET = 0,
    Bit_SET
} BitState;

//GPIO_Pin
#define GPIO_Pin_0                 ((uint16_t)0x0001)
#define GPIO_Pin_1                 ((uint16_t)0x0002)
#define GPIO_Pin_2                 ((uint16_t)0x0004)
#define GPIO_Pin_3                 ((uint16_t)0x0008)
#define GPIO_Pin_4                 ((uint16_t)0x0010)
#define GPIO_Pin_5                 ((uint16_t)0x0020)
#define GPIO_Pin_6                 ((uint16_t)0x0040)
#define GPIO_Pin_7                 ((uint16_t)0x0080)
#define GPIO_Pin_8                 ((uint16_t)0x0100)
#define GPIO_Pin_9                 ((uint16_t)0x0200)
#define GPIO_Pin_10                ((uint16_t)0x0400)
#define GPIO_Pin_11                ((uint16_t)0x0800)
#define GPIO_Pin_12                ((uint16_t)0x1000)
#define GPIO_Pin_13                ((uint16_t)0x2000)
#define GPIO_Pin_14                ((uint16_t)0x4000)
#define GPIO_Pin_15                ((uint16_t)0x8000)
#define GPIO_Pin_All               ((uint16_t)0xFFFF)
//GPIO_Mode
#define GPIO_Mode_INPUT           (0xCU)
#define GPIO_Mode_OUTPUT_CMOS     (0x2U)
#define GPIO_Mode_OUTPUT_OD       (0x3U)  
#define GPIO_Mode_INOUT_OD        (0xBU)
#define GPIO_Mode_INOUT_CMOS      (0xAU)
#define GPIO_Mode_FORBIDDEN       (0x4U)
  
//GPIO AF
#define GPIOB_AF_PLLHDIV     IOB_SEL_SEL1
#define GPIOB_AF_OSC         IOB_SEL_SEL6
#define GPIOB_AF_PLLLOUT     IOB_SEL_SEL2
#define GPIOE_AF_CMP1O       IOE_SEL_SEL7

//PMUIO AF
#define PMUIO7_AF_PLLDIV     PMU_IOASEL_SEL7
#define PMUIO_AF_CMP2O       PMU_IOASEL_SEL6
#define PMUIO3_AF_PLLDIV     PMU_IOASEL_SEL3
#define PMUIO_AF_Msk        (PMUIO7_AF_PLLDIV | PMUIO_AF_CMP2O | PMUIO3_AF_PLLDIV)

//GPIO pin remap
#define GPIO_REMAP_I2C       IO_MISC_I2CIOC

//PLLDIV
#define  GPIO_PLLDIV_1            IO_MISC_PLLHDIV_1        
#define  GPIO_PLLDIV_2            IO_MISC_PLLHDIV_2        
#define  GPIO_PLLDIV_4            IO_MISC_PLLHDIV_4        
#define  GPIO_PLLDIV_8            IO_MISC_PLLHDIV_8        
#define  GPIO_PLLDIV_16           IO_MISC_PLLHDIV_16 

/* Private macros ------------------------------------------------------------*/
#define IS_GPIO_PIN(__PIN__)  ((((__PIN__) & GPIO_Pin_All) != 0UL) &&\
                               (((__PIN__) & ~GPIO_Pin_All) == 0UL))

#define IS_GPIO_PINR(__PINR__)  (((__PINR__) == GPIO_Pin_0) ||\
                                 ((__PINR__) == GPIO_Pin_1) ||\
                                 ((__PINR__) == GPIO_Pin_2) ||\
                                 ((__PINR__) == GPIO_Pin_3) ||\
                                 ((__PINR__) == GPIO_Pin_4) ||\
                                 ((__PINR__) == GPIO_Pin_5) ||\
                                 ((__PINR__) == GPIO_Pin_6) ||\
                                 ((__PINR__) == GPIO_Pin_7) ||\
                                 ((__PINR__) == GPIO_Pin_8) ||\
                                 ((__PINR__) == GPIO_Pin_9) ||\
                                 ((__PINR__) == GPIO_Pin_10) ||\
                                 ((__PINR__) == GPIO_Pin_11) ||\
                                 ((__PINR__) == GPIO_Pin_12) ||\
                                 ((__PINR__) == GPIO_Pin_13) ||\
                                 ((__PINR__) == GPIO_Pin_14) ||\
                                 ((__PINR__) == GPIO_Pin_15))

#define IS_GPIO_MODE(__MODE__)  (((__MODE__) ==  GPIO_Mode_INPUT)       ||\
                                 ((__MODE__) ==  GPIO_Mode_OUTPUT_CMOS) ||\
                                 ((__MODE__) ==  GPIO_Mode_OUTPUT_OD)   ||\
                                 ((__MODE__) ==  GPIO_Mode_INOUT_OD)    ||\
                                 ((__MODE__) ==  GPIO_Mode_INOUT_CMOS)  ||\
                                 ((__MODE__) ==  GPIO_Mode_FORBIDDEN))

#define IS_GPIO_BITVAL(__BITVAL__)  (((__BITVAL__) == 1U) || ((__BITVAL__) == 0U))

#define IS_GPIO_GPIOAF(__GPIOAF__)  (((__GPIOAF__) == GPIOB_AF_PLLHDIV) ||\
                                     ((__GPIOAF__) == GPIOB_AF_OSC)     ||\
                                     ((__GPIOAF__) == GPIOE_AF_CMP1O)   ||\
                                     ((__GPIOAF__) == GPIOB_AF_PLLLOUT))

#define IS_GPIO_PMUIOAF(__PMUIOAF__)  ((((__PMUIOAF__) & PMUIO_AF_Msk) != 0U) &&\
                                       (((__PMUIOAF__) & ~PMUIO_AF_Msk) == 0U))

#define IS_GPIO_REMAP(__REMAP__)  ((__REMAP__) == GPIO_REMAP_I2C)

#define IS_GPIO_PLLDIV(__PLLDIV__)  (((__PLLDIV__) == GPIO_PLLDIV_1) ||\
                                     ((__PLLDIV__) == GPIO_PLLDIV_2) ||\
                                     ((__PLLDIV__) == GPIO_PLLDIV_4) ||\
                                     ((__PLLDIV__) == GPIO_PLLDIV_8) ||\
                                     ((__PLLDIV__) == GPIO_PLLDIV_16))

/* Exported Functions ------------------------------------------------------- */
/* GPIO Exported Functions Group1: 
                                   Initialization and functions --------------*/
void GPIOBToF_Init(GPIO_TypeDef *GPIOx, GPIO_InitType *InitStruct);
void GPIOA_Init(GPIOA_TypeDef *GPIOx, GPIO_InitType *InitStruct);
/* GPIO Exported Functions Group2: 
                                   Read input data ---------------------------*/
uint8_t GPIOBToF_ReadInputDataBit(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin);
uint8_t GPIOA_ReadInputDataBit(GPIOA_TypeDef *GPIOx, uint16_t GPIO_Pin);
uint16_t GPIOBToF_ReadInputData(GPIO_TypeDef* GPIOx);
uint16_t GPIOA_ReadInputData(GPIOA_TypeDef* GPIOx);
/* GPIO Exported Functions Group3: 
                                   Read output data --------------------------*/
uint8_t GPIOBToF_ReadOutputDataBit(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin);
uint8_t GPIOA_ReadOutputDataBit(GPIOA_TypeDef* GPIOx, uint16_t GPIO_Pin);
uint16_t GPIOBToF_ReadOutputData(GPIO_TypeDef* GPIOx);
uint16_t GPIOA_ReadOutputData(GPIOA_TypeDef* GPIOx);
/* GPIO Exported Functions Group4: 
                                   Write output data -------------------------*/
void GPIOBToF_SetBits(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin);
void GPIOA_SetBits(GPIOA_TypeDef* GPIOx, uint16_t GPIO_Pin);
void GPIOBToF_ResetBits(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin);
void GPIOA_ResetBits(GPIOA_TypeDef* GPIOx, uint16_t GPIO_Pin);
void GPIOBToF_WriteBit(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin, uint8_t val);
void GPIOA_WriteBit(GPIOA_TypeDef* GPIOx, uint16_t GPIO_Pin, uint8_t val);
void GPIOBToF_Write(GPIO_TypeDef* GPIOx, uint16_t val);
void GPIOA_Write(GPIOA_TypeDef* GPIOx, uint16_t val);
/* GPIO Exported Functions Group5: 
                                   IO AF configure ---------------------------*/
void GPIOBToF_AFConfig(GPIO_TypeDef* GPIOx, uint32_t GPIO_AFx, uint8_t NewState);
void GPIOA_AFConfig(uint32_t PMUIO_AFx, uint8_t NewState);
/* GPIO Exported Functions Group6: 
                                   IO Remap configure ------------------------*/
void GPIO_PinRemapConfig(uint32_t GPIO_Remap, uint8_t NewState);
/* GPIO Exported Functions Group7: 
                                   Others ------------------------------------*/
void GPIO_PLLDIV_Config(uint32_t Divider);
void GPIOA_NoDeg_Cmd( uint16_t GPIO_Pin, uint8_t NewState);

#ifdef __cplusplus
}
#endif
     
#endif  /* __LIB_GPIO_H */

/*********************************** END OF FILE ******************************/
