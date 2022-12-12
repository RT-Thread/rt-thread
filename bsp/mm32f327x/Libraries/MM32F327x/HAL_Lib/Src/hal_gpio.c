////////////////////////////////////////////////////////////////////////////////
/// @file     hal_gpio.c
/// @author   AE TEAM
/// @brief    THIS FILE PROVIDES ALL THE GPIO FIRMWARE FUNCTIONS.
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
#define _HAL_GPIO_C_

// Files includes
#include "reg_exti.h"
#include "hal_rcc.h"
#include "hal_gpio.h"




////////////////////////////////////////////////////////////////////////////////
/// @addtogroup MM32_Hardware_Abstract_Layer
/// @{

////////////////////////////////////////////////////////////////////////////////
/// @addtogroup GPIO_HAL
/// @{

////////////////////////////////////////////////////////////////////////////////
/// @addtogroup GPIO_Exported_Functions
/// @{

////////////////////////////////////////////////////////////////////////////////
/// @brief  Deinitializes the gpio peripheral registers to their default reset
///         values.
/// @param  gpio: select the GPIO peripheral.
/// @retval None.
////////////////////////////////////////////////////////////////////////////////
void GPIO_DeInit(GPIO_TypeDef* gpio)
{
    switch (*(vu32*)&gpio) {
        case (u32)GPIOA:
            RCC_AHBPeriphClockCmd(RCC_AHBENR_GPIOA, DISABLE);
            break;
        case (u32)GPIOB:
            RCC_AHBPeriphClockCmd(RCC_AHBENR_GPIOB, DISABLE);
            break;
        case (u32)GPIOC:
            RCC_AHBPeriphClockCmd(RCC_AHBENR_GPIOC, DISABLE);
            break;
        case (u32)GPIOD:
            RCC_AHBPeriphClockCmd(RCC_AHBENR_GPIOD, DISABLE);
            break;
        case (u32)GPIOE:
            RCC_AHBPeriphClockCmd(RCC_AHBENR_GPIOE, DISABLE);
            break;
        default:
            break;
    }
}

////////////////////////////////////////////////////////////////////////////////
/// @brief  Deinitializes the Alternate Functions (remap, event control
///         and EXTI configuration) registers to their default reset values.
/// @param  None.
/// @retval None.
////////////////////////////////////////////////////////////////////////////////
void GPIO_AFIODeInit()
{
    GPIOA->AFRL = 0xFFFFFFFF;
    GPIOA->AFRH = 0xF00FFFFF;       //  PA14:SWCLK, PA13:PSWDIO
    GPIOB->AFRL = 0xFFFFFFFF;
    GPIOB->AFRH = 0xFFFFFFFF;
    GPIOC->AFRL = 0xFFFFFFFF;
    GPIOC->AFRH = 0xFFFFFFFF;
    GPIOD->AFRL = 0xFFFFFFFF;
    GPIOD->AFRH = 0xFFFFFFFF;
    GPIOE->AFRL = 0xFFFFFFFF;
    GPIOE->AFRH = 0xFFFFFFFF;
}

////////////////////////////////////////////////////////////////////////////////
/// @brief  Initializes the gpio peripheral according to the specified
///         parameters in the init_struct.
/// @param  gpio: select the GPIO peripheral.
/// @param  init_struct: pointer to a GPIO_InitTypeDef structure that
///         contains the configuration information for the specified GPIO
///         peripheral.
/// @retval None.
////////////////////////////////////////////////////////////////////////////////
void GPIO_Init(GPIO_TypeDef* gpio, GPIO_InitTypeDef* init_struct)
{
    u8   idx;
    u8 i;
    u32 tmp;
    __IO u32* reg ;

    // 1x
    u32 dat = init_struct->GPIO_Mode & 0x0F;
    if (init_struct->GPIO_Mode & 0x10)
        dat |= init_struct->GPIO_Speed;

    // 0x
    reg  = &gpio->CRL;
    for (i = 0; i < 8; i++) {
        idx = i * 4;
        if ((init_struct->GPIO_Pin) & (1 << i)) {
            *reg  = (*reg  & ~(0xF << idx)) | (dat << idx);
        }
    }

    reg     = &gpio->CRH;
    tmp = init_struct->GPIO_Pin >> 8;
    for (i = 0; i < 8; i++) {
        idx = i * 4;
        if (tmp & (1 << i)) {
            *reg  = (*reg  & ~(0xF << idx)) | (dat << idx);
        }
    }

    // 2x,4x
    if (init_struct->GPIO_Mode == GPIO_Mode_IPD)
        gpio->BRR |= init_struct->GPIO_Pin;
    else if (init_struct->GPIO_Mode == GPIO_Mode_IPU)
        gpio->BSRR |= init_struct->GPIO_Pin;
}
////////////////////////////////////////////////////////////////////////////////
/// @brief  Fills each init_struct member with its default value.
/// @param init_struct : pointer to a GPIO_InitTypeDef structure
///   which will be initialized.
/// @retval : None
////////////////////////////////////////////////////////////////////////////////
void GPIO_StructInit(GPIO_InitTypeDef* init_struct)
{
    // Reset GPIO init structure parameters values
    init_struct->GPIO_Pin  = GPIO_Pin_All;
    init_struct->GPIO_Speed = GPIO_Speed_2MHz;
    init_struct->GPIO_Mode = GPIO_Mode_FLOATING;
}
////////////////////////////////////////////////////////////////////////////////
/// @brief  Reads the input data of specified GPIO port pin.
/// @param  gpio:  select the GPIO peripheral.
/// @param  pin:  specifies the port pin to be read.
///         This parameter can be GPIO_Pin_x where x can be (0..15).
/// @retval The input port pin value.
////////////////////////////////////////////////////////////////////////////////
bool GPIO_ReadInputDataBit(GPIO_TypeDef* gpio, u16 pin)
{
    return ((gpio->IDR & pin)) ? Bit_SET : Bit_RESET;
}

////////////////////////////////////////////////////////////////////////////////
/// @brief  Reads all GPIO port pins input data.
/// @param  gpio: select the GPIO peripheral.
/// @retval GPIO port input data value.
////////////////////////////////////////////////////////////////////////////////
u16 GPIO_ReadInputData(GPIO_TypeDef* gpio)
{
    return gpio->IDR;
}

////////////////////////////////////////////////////////////////////////////////
/// @brief  Reads the output data of specified GPIO port pin.
/// @param  gpio: select the GPIO peripheral.
/// @param  pin:  specifies the port bit to be read.
///         This parameter can be GPIO_Pin_x where x can be (0..15).
/// @retval The output port pin value.
////////////////////////////////////////////////////////////////////////////////
bool GPIO_ReadOutputDataBit(GPIO_TypeDef* gpio, u16 pin)
{
    return (gpio->ODR & pin) ? Bit_SET : Bit_RESET;
}

////////////////////////////////////////////////////////////////////////////////
/// @brief  Reads all GPIO port pins output data.
/// @param  gpio: select the GPIO peripheral.
/// @retval GPIO port output data value.
////////////////////////////////////////////////////////////////////////////////
u16 GPIO_ReadOutputData(GPIO_TypeDef* gpio)
{
    return gpio->ODR;
}

////////////////////////////////////////////////////////////////////////////////
/// @brief  Sets the selected GPIO port pin.
/// @param  gpio: where x can be (A..D) to select the GPIO peripheral.
/// @param  pin: specifies the port pins to be written.
///         This parameter can be any combination of GPIO_Pin_x where x can be
///         (0..15).
/// @retval None.
////////////////////////////////////////////////////////////////////////////////
void GPIO_SetBits(GPIO_TypeDef* gpio, u16 pin)
{
    gpio->BSRR = pin;
}

////////////////////////////////////////////////////////////////////////////////
/// @brief  Clears the selected GPIO port bit.
/// @param  gpio: where x can be (A..D) to select the GPIO peripheral.
/// @param  pin: specifies the port pins to be written.
///         This parameter can be any combination of GPIO_Pin_x where x can be
///         (0..15).
/// @retval None.
////////////////////////////////////////////////////////////////////////////////
void GPIO_ResetBits(GPIO_TypeDef* gpio, u16 pin)
{
    gpio->BRR = pin;
}

////////////////////////////////////////////////////////////////////////////////
/// @brief  Sets or clears the selected GPIO port pin.
/// @param  gpio: select the GPIO peripheral.
/// @param  pin: specifies the port bit to be written.
///         This parameter can be one of GPIO_Pin_x where x can be (0..15).
/// @param  value: specifies the value to be written to the selected bit.
///         This parameter can be one of the BitAction enum values:
/// @arg    Bit_RESET: to clear the port pin
/// @arg    Bit_SET: to set the port pin
/// @retval None.
////////////////////////////////////////////////////////////////////////////////
void GPIO_WriteBit(GPIO_TypeDef* gpio, u16 pin, BitAction value)
{
    (value) ? (gpio->BSRR = pin) : (gpio->BRR = pin);
}

////////////////////////////////////////////////////////////////////////////////
/// @brief  Writes data to all GPIO port pins.
/// @param  gpio: where x can be (A..D) to select the GPIO peripheral.
/// @param  value: specifies the value to be written to the port output data
///         register.
/// @retval None.
////////////////////////////////////////////////////////////////////////////////
void GPIO_Write(GPIO_TypeDef* gpio, u16 value)
{
    gpio->ODR = value;
}

////////////////////////////////////////////////////////////////////////////////
/// @brief  Locks GPIO Pins configuration.
/// @param  gpio: to select the GPIO peripheral.
/// @param  pin: specifies the port bit to be written.
///         This parameter can be any combination of GPIO_Pin_x where x can be
///         (0..15).
/// @param  state: new lock state of the port pin.
///         This parameter can be: ENABLE or DISABLE.
/// @retval None.
////////////////////////////////////////////////////////////////////////////////
void GPIO_PinLock(GPIO_TypeDef* gpio, u16 pin, FunctionalState state)
{
    (state) ? (gpio->LCKR |= pin) : (gpio->LCKR &= ~pin);
}

////////////////////////////////////////////////////////////////////////////////
/// @brief  Locks GPIO Pins configuration registers until next system reset.
/// @param  gpio: to select the GPIO peripheral.
/// @param  pin: specifies the port bit to be written.
///         This parameter can be any combination of GPIO_Pin_x where x can be
///         (0..15).
/// @retval None.
////////////////////////////////////////////////////////////////////////////////
void GPIO_PinLockConfig(GPIO_TypeDef* gpio, u16 pin)
{
    gpio->LCKR = GPIO_LCKR_LCKK | pin;
    gpio->LCKR = pin;
    gpio->LCKR = GPIO_LCKR_LCKK | pin;
    gpio->LCKR;
    gpio->LCKR;
}

////////////////////////////////////////////////////////////////////////////////
/// @brief  Enables or disables the port pin remapping.
/// @param  remap: selects the pin to remap.
/// @param  mask: the corresponding remapping mask of the remapping pin.
/// @param  state: new state of the port pin remapping.
///         This parameter can be: ENABLE or DISABLE.
/// @retval None.
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
/// @brief  Writes data to the specified GPIO data port.
/// @param  gpio: select the GPIO peripheral.
/// @param  pin: specifies the pin for the Alternate function.
///         This parameter can be GPIO_PinSourcex where x can be (0..15) for
///         GPIOA, GPIOB, GPIOD and (0..12) for GPIOC .
/// @param  alternate_function: selects the pin to used as Alternate function.
///         This parameter can be the GPIO_AF_x where x can be (0..7).
/// @note   The pin should be used for Digital IP.
/// @retval None.
////////////////////////////////////////////////////////////////////////////////
void GPIO_PinAFConfig(GPIO_TypeDef* gpio, u8 pin, u8 alternate_function)
{
    u8 shift = (pin & 0x07) * 4;
    u32* ptr = (pin < 8) ? (u32*)&gpio->AFRL : (u32*)&gpio->AFRH;
    *ptr = (*ptr & ~(0x0F << shift)) | (alternate_function << shift);
}

////////////////////////////////////////////////////////////////////////////////
/// @brief  Set the remap function and AF function of the GPIO pin.
/// @param  gpio:select the GPIO peripheral.
/// @param  pin: specifies the pin for the Alternate function.
///         This parameter can be GPIO_Pin_x where x can be (0..15) for
///         GPIOA, GPIOB, GPIOD and (0..12) for GPIOC .
/// @param  remap: selects the pin to remap.
/// @param  alternate_function: selects the pin to used as Alternate function.
///         This parameter can be the GPIO_AF_x where x can be (0..7).
/// @note   The pin should be used for Digital IP.
/// @retval None.
////////////////////////////////////////////////////////////////////////////////
void exGPIO_PinAFConfig(GPIO_TypeDef* gpio, u16 pin, s32 remap, s8 alternate_function)
{
    u8 i;
    u8 shift;
    u32* ptr;

    if (alternate_function >= 0) {
        for (i = 0; i < 32; i++) {
            if (pin & 0x01) {
                pin = i;
                break;
            }
            pin >>= 1;
        }

        shift = (pin & 0x07) * 4;
        ptr = (pin < 8) ? (u32*)&gpio->AFRL : (u32*)&gpio->AFRH;
        *ptr = (*ptr & ~(0x0F << shift)) | (alternate_function << shift);
    }
}


/// @}

/// @}

/// @}

