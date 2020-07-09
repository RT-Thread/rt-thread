/******************************************************************************
*
* @brief provide commond GPIO utilities. 
*
*******************************************************************************/
#ifndef _GPIO_H_
#define _GPIO_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "common.h"
#include "stdint.h"

/******************************************************************************
*define gpio pin name
*
*//*! @addtogroup gpio_pin_name_list
* @{
*******************************************************************************/
typedef enum
{
    /* in GPIOA register */
    GPIO_PTA0 = 0,              /*!< GPIO Pin PTA0 */
    GPIO_PTA1,                  /*!< GPIO Pin PTA1 */
    GPIO_PTA2,                  /*!< GPIO Pin PTA2 */
    GPIO_PTA3,                  /*!< GPIO Pin PTA3 */
    GPIO_PTA4,                  /*!< GPIO Pin PTA4 */
    GPIO_PTA5,                  /*!< GPIO Pin PTA5 */
    GPIO_PTA6,                  /*!< GPIO Pin PTA6 */
    GPIO_PTA7,                  /*!< GPIO Pin PTA7 */
    GPIO_PTB0,                  /*!< GPIO Pin PTB0 */
    GPIO_PTB1,                  /*!< GPIO Pin PTB1 */
    GPIO_PTB2,                  /*!< GPIO Pin PTB2 */
    GPIO_PTB3,                  /*!< GPIO Pin PTB3 */
    GPIO_PTB4,                  /*!< GPIO Pin PTB4 */
    GPIO_PTB5,                  /*!< GPIO Pin PTB5 */
    GPIO_PTB6,                  /*!< GPIO Pin PTB6 */
    GPIO_PTB7,                  /*!< GPIO Pin PTB7 */
    GPIO_PTC0,                  /*!< GPIO Pin PTC0 */
    GPIO_PTC1,                  /*!< GPIO Pin PTC1 */
    GPIO_PTC2,                  /*!< GPIO Pin PTC2 */
    GPIO_PTC3,                  /*!< GPIO Pin PTC3 */
    GPIO_PTC4,                  /*!< GPIO Pin PTC4 */
    GPIO_PTC5,                  /*!< GPIO Pin PTC5 */
    GPIO_PTC6,                  /*!< GPIO Pin PTC6 */
    GPIO_PTC7,                  /*!< GPIO Pin PTC7 */
    GPIO_PTD0,                  /*!< GPIO Pin PTD0 */
    GPIO_PTD1,                  /*!< GPIO Pin PTD1 */
    GPIO_PTD2,                  /*!< GPIO Pin PTD2 */
    GPIO_PTD3,                  /*!< GPIO Pin PTD3 */
    GPIO_PTD4,                  /*!< GPIO Pin PTD4 */
    GPIO_PTD5,                  /*!< GPIO Pin PTD5 */
    GPIO_PTD6,                  /*!< GPIO Pin PTD6 */
    GPIO_PTD7,                  /*!< GPIO Pin PTD7 */
    /* in GPIOB register */
    GPIO_PTE0,                  /*!< GPIO Pin PTE0 */
    GPIO_PTE1,                  /*!< GPIO Pin PTE1 */
    GPIO_PTE2,                  /*!< GPIO Pin PTE2 */
    GPIO_PTE3,                  /*!< GPIO Pin PTE3 */
    GPIO_PTE4,                  /*!< GPIO Pin PTE4 */
    GPIO_PTE5,                  /*!< GPIO Pin PTE5 */
    GPIO_PTE6,                  /*!< GPIO Pin PTE6 */
    GPIO_PTE7,                  /*!< GPIO Pin PTE7 */
    GPIO_PTF0,                  /*!< GPIO Pin PTF0 */
    GPIO_PTF1,                  /*!< GPIO Pin PTF1 */
    GPIO_PTF2,                  /*!< GPIO Pin PTF2 */
    GPIO_PTF3,                  /*!< GPIO Pin PTF3 */
    GPIO_PTF4,                  /*!< GPIO Pin PTF4 */
    GPIO_PTF5,                  /*!< GPIO Pin PTF5 */
    GPIO_PTF6,                  /*!< GPIO Pin PTF6 */
    GPIO_PTF7,                  /*!< GPIO Pin PTF7 */
    GPIO_PTG0,                  /*!< GPIO Pin PTG0 */
    GPIO_PTG1,                  /*!< GPIO Pin PTG1 */
    GPIO_PTG2,                  /*!< GPIO Pin PTG2 */
    GPIO_PTG3,                  /*!< GPIO Pin PTG3 */
    GPIO_PTG4,                  /*!< GPIO Pin PTG4 */
    GPIO_PTG5,                  /*!< GPIO Pin PTG5 */
    GPIO_PTG6,                  /*!< GPIO Pin PTG6 */
    GPIO_PTG7,                  /*!< GPIO Pin PTG7 */
    GPIO_PTH0,                  /*!< GPIO Pin PTH0 */
    GPIO_PTH1,                  /*!< GPIO Pin PTH1 */
    GPIO_PTH2,                  /*!< GPIO Pin PTH2 */
    GPIO_PTH3,                  /*!< GPIO Pin PTH3 */
    GPIO_PTH4,                  /*!< GPIO Pin PTH4 */
    GPIO_PTH5,                  /*!< GPIO Pin PTH5 */
    GPIO_PTH6,                  /*!< GPIO Pin PTH6 */
    GPIO_PTH7,                  /*!< GPIO Pin PTH7 */
    /* the following pins are not in NV322 */
    GPIO_PTI0,                  /*!< GPIO Pin PTI0 */
    GPIO_PTI1,                  /*!< GPIO Pin PTI1 */
    GPIO_PTI2,                  /*!< GPIO Pin PTI2 */
    GPIO_PTI3,                  /*!< GPIO Pin PTI3 */
    GPIO_PTI4,                  /*!< GPIO Pin PTI4 */
    GPIO_PTI5,                  /*!< GPIO Pin PTI5 */
    GPIO_PTI6,                  /*!< GPIO Pin PTI6 */
    GPIO_PTI7,                  /*!< GPIO Pin PTI7 */
    GPIO_PIN_MAX,
} GPIO_PinType;
/*! @} End of gpio_pin_name_list    */

/******************************************************************************
*define gpio pin mask
*
*//*! @addtogroup gpio_pin_mask_list
* @{
*******************************************************************************/
typedef enum
{
    /* in GPIOA register */
    GPIO_PTA0_MASK = (1<<0),    /*!< GPIO Pin PTA0 bit mask */        
    GPIO_PTA1_MASK = (1<<1),    /*!< GPIO Pin PTA1 bit mask */
    GPIO_PTA2_MASK = (1<<2),    /*!< GPIO Pin PTA2 bit mask */
    GPIO_PTA3_MASK = (1<<3),    /*!< GPIO Pin PTA3 bit mask */
    GPIO_PTA4_MASK = (1<<4),    /*!< GPIO Pin PTA4 bit mask */
    GPIO_PTA5_MASK = (1<<5),    /*!< GPIO Pin PTA5 bit mask */
    GPIO_PTA6_MASK = (1<<6),    /*!< GPIO Pin PTA6 bit mask */
    GPIO_PTA7_MASK = (1<<7),    /*!< GPIO Pin PTA7 bit mask */
    GPIO_PTB0_MASK = (1<<8),    /*!< GPIO Pin PTB0 bit mask */
    GPIO_PTB1_MASK = (1<<9),    /*!< GPIO Pin PTB1 bit mask */
    GPIO_PTB2_MASK = (1<<10),   /*!< GPIO Pin PTB2 bit mask */
    GPIO_PTB3_MASK = (1<<11),   /*!< GPIO Pin PTB3 bit mask */
    GPIO_PTB4_MASK = (1<<12),   /*!< GPIO Pin PTB4 bit mask */
    GPIO_PTB5_MASK = (1<<13),   /*!< GPIO Pin PTB5 bit mask */
    GPIO_PTB6_MASK = (1<<14),   /*!< GPIO Pin PTB6 bit mask */
    GPIO_PTB7_MASK = (1<<15),   /*!< GPIO Pin PTB7 bit mask */
    GPIO_PTC0_MASK = (1<<16),   /*!< GPIO Pin PTC0 bit mask */
    GPIO_PTC1_MASK = (1<<17),   /*!< GPIO Pin PTC1 bit mask */
    GPIO_PTC2_MASK = (1<<18),   /*!< GPIO Pin PTC2 bit mask */
    GPIO_PTC3_MASK = (1<<19),   /*!< GPIO Pin PTC3 bit mask */
    GPIO_PTC4_MASK = (1<<20),   /*!< GPIO Pin PTC4 bit mask */
    GPIO_PTC5_MASK = (1<<21),   /*!< GPIO Pin PTC5 bit mask */
    GPIO_PTC6_MASK = (1<<22),   /*!< GPIO Pin PTC6 bit mask */
    GPIO_PTC7_MASK = (1<<23),   /*!< GPIO Pin PTC7 bit mask */
    GPIO_PTD0_MASK = (1<<24),   /*!< GPIO Pin PTD0 bit mask */
    GPIO_PTD1_MASK = (1<<25),   /*!< GPIO Pin PTD1 bit mask */
    GPIO_PTD2_MASK = (1<<26),   /*!< GPIO Pin PTD2 bit mask */
    GPIO_PTD3_MASK = (1<<27),   /*!< GPIO Pin PTD3 bit mask */
    GPIO_PTD4_MASK = (1<<28),   /*!< GPIO Pin PTD4 bit mask */
    GPIO_PTD5_MASK = (1<<29),   /*!< GPIO Pin PTD5 bit mask */
    GPIO_PTD6_MASK = (1<<30),   /*!< GPIO Pin PTD6 bit mask */
    GPIO_PTD7_MASK = (1<<31),   /*!< GPIO Pin PTD7 bit mask */
    /* in GPIOB register */
    GPIO_PTE0_MASK = (1<<0),    /*!< GPIO Pin PTE0 bit mask */
    GPIO_PTE1_MASK = (1<<1),    /*!< GPIO Pin PTE1 bit mask */
    GPIO_PTE2_MASK = (1<<2),    /*!< GPIO Pin PTE2 bit mask */
    GPIO_PTE3_MASK = (1<<3),    /*!< GPIO Pin PTE3 bit mask */
    GPIO_PTE4_MASK = (1<<4),    /*!< GPIO Pin PTE4 bit mask */
    GPIO_PTE5_MASK = (1<<5),    /*!< GPIO Pin PTE5 bit mask */
    GPIO_PTE6_MASK = (1<<6),    /*!< GPIO Pin PTE6 bit mask */
    GPIO_PTE7_MASK = (1<<7),    /*!< GPIO Pin PTE7 bit mask */
    GPIO_PTF0_MASK = (1<<8),    /*!< GPIO Pin PTF0 bit mask */
    GPIO_PTF1_MASK = (1<<9),    /*!< GPIO Pin PTF1 bit mask */
    GPIO_PTF2_MASK = (1<<10),   /*!< GPIO Pin PTF2 bit mask */
    GPIO_PTF3_MASK = (1<<11),   /*!< GPIO Pin PTF3 bit mask */
    GPIO_PTF4_MASK = (1<<12),   /*!< GPIO Pin PTF4 bit mask */
    GPIO_PTF5_MASK = (1<<13),   /*!< GPIO Pin PTF5 bit mask */
    GPIO_PTF6_MASK = (1<<14),   /*!< GPIO Pin PTF6 bit mask */
    GPIO_PTF7_MASK = (1<<15),   /*!< GPIO Pin PTF7 bit mask */
    GPIO_PTG0_MASK = (1<<16),   /*!< GPIO Pin PTG0 bit mask */
    GPIO_PTG1_MASK = (1<<17),   /*!< GPIO Pin PTG1 bit mask */
    GPIO_PTG2_MASK = (1<<18),   /*!< GPIO Pin PTG2 bit mask */
    GPIO_PTG3_MASK = (1<<19),   /*!< GPIO Pin PTG3 bit mask */
    GPIO_PTG4_MASK = (1<<20),   /*!< GPIO Pin PTG4 bit mask */
    GPIO_PTG5_MASK = (1<<21),   /*!< GPIO Pin PTG5 bit mask */
    GPIO_PTG6_MASK = (1<<22),   /*!< GPIO Pin PTG6 bit mask */
    GPIO_PTG7_MASK = (1<<23),   /*!< GPIO Pin PTG7 bit mask */
    GPIO_PTH0_MASK = (1<<24),   /*!< GPIO Pin PTH0 bit mask */
    GPIO_PTH1_MASK = (1<<25),   /*!< GPIO Pin PTH1 bit mask */
    GPIO_PTH2_MASK = (1<<26),   /*!< GPIO Pin PTH2 bit mask */
    GPIO_PTH3_MASK = (1<<27),   /*!< GPIO Pin PTH3 bit mask */
    GPIO_PTH4_MASK = (1<<28),   /*!< GPIO Pin PTH4 bit mask */
    GPIO_PTH5_MASK = (1<<29),   /*!< GPIO Pin PTH5 bit mask */
    GPIO_PTH6_MASK = (1<<30),   /*!< GPIO Pin PTH6 bit mask */
    GPIO_PTH7_MASK = (1<<31),   /*!< GPIO Pin PTH7 bit mask */
    /* in GPIOC register */
    GPIO_PTI0_MASK = (1<<0),    /*!< GPIO Pin PTI0 bit mask */
    GPIO_PTI1_MASK = (1<<1),    /*!< GPIO Pin PTI1 bit mask */
    GPIO_PTI2_MASK = (1<<2),    /*!< GPIO Pin PTI2 bit mask */
    GPIO_PTI3_MASK = (1<<3),    /*!< GPIO Pin PTI3 bit mask */
    GPIO_PTI4_MASK = (1<<4),    /*!< GPIO Pin PTI4 bit mask */
    GPIO_PTI5_MASK = (1<<5),    /*!< GPIO Pin PTI5 bit mask */
    GPIO_PTI6_MASK = (1<<6),    /*!< GPIO Pin PTI6 bit mask */
    GPIO_PTI7_MASK = (1<<7),    /*!< GPIO Pin PTI7 bit mask */
} GPIO_PinMaskType;
/*! @} End of gpio_pin_mask_list    */


/******************************************************************************
*define gpio pin config type
*
*//*! @addtogroup gpio_pin_config_type_list
* @{
*******************************************************************************/
/*
*   . Internal pullup is disabled if the pin is configured as an output
*   . High-current drive function is disabled, if the pin is configured as an input
*       Only PTH1/0, PTE1/0, PTD1/0, PTB5/4 support Hight-current Drive.
*/
typedef enum
{
    GPIO_PinOutput = 0,                 /*!< set pin as outout */
    GPIO_PinInput,                      /*!< set pin as input */
    GPIO_PinInput_InternalPullup,       /*!< set internal pullup for input pin */
    GPIO_PinOutput_HighCurrent,         /*!< set high drive for output pin */
} GPIO_PinConfigType;
/*! @} End of gpio_pin_config_type_list */

/******************************************************************************
* define GPIO APIs
*
*//*! @addtogroup gpio_api_list
* @{
*******************************************************************************/

/*****************************************************************************//*!
* @brief    Toggle the pins which are specified by u32PinMask in single cycle.
*        
* @param[in] pGPIO       Pointer to GPIO module, can be FGPIOA/FGPIOB.
* @param[in] u32PinMask  Specify GPIO pin need to be toggled
*
* @return none
*
* @ Pass/ Fail criteria: none
*****************************************************************************/
__STATIC_INLINE void FGPIO_Toggle(FGPIO_Type *pFGPIO, uint32_t u32PinMask)
{
    pFGPIO->PTOR = u32PinMask;   /* Toggle the pins specified by u32PinMask */
}

/*****************************************************************************//*!
* @brief Read input data from GPIO which is specified by pGPIO in single cycle.
*        
* @param[in] pGPIO       Pointer to GPIO module, can be FGPIOA/FGPIOB.
*
* @return   GPIO input value unsigned int 32-bit
*
* @ Pass/ Fail criteria: none
*****************************************************************************/
 __STATIC_INLINE uint32_t FGPIO_Read(FGPIO_Type *pFGPIO)
{
    return (pFGPIO->PDIR);      /* Read Port Data Input Register */
  
}

/*****************************************************************************//*!
* @brief    Write output data to GPIO which is specified by pGPIO in single cycle.
*        
* @param[in] pGPIO       Pointer to GPIO module, can be FGPIOA/FGPIOB.
* @param[in] u32Value    value to output
*
* @return   none
*
* @ Pass/ Fail criteria: none
*****************************************************************************/
__STATIC_INLINE void FGPIO_Write(FGPIO_Type *pFGPIO, uint32_t u32Value)
{    
    pFGPIO->PDOR = u32Value;    /* Write Port Ouput Data Register */
}

void GPIO_DeInit(GPIO_Type *pGPIO);
void GPIO_Init(GPIO_Type *pGPIO, uint32_t u32PinMask, GPIO_PinConfigType sGpioType);
void GPIO_Toggle(GPIO_Type *pGPIO, uint32_t u32PinMask);
uint32_t GPIO_Read(GPIO_Type *pGPIO);
void GPIO_Write(GPIO_Type *pGPIO, uint32_t u32Value);
void GPIO_PinInit(GPIO_PinType GPIO_Pin, GPIO_PinConfigType GPIO_PinConfig);
void GPIO_PinToggle(GPIO_PinType GPIO_Pin);
void GPIO_PinSet(GPIO_PinType GPIO_Pin);
void GPIO_PinClear(GPIO_PinType GPIO_Pin);
uint8_t GPIO_BitRead(GPIO_PinType GPIO_Pin);
    
/*! @} End of gpio_api_list */

#ifdef __cplusplus
}
#endif
#endif /* #ifndef _GPIO_H_ */
