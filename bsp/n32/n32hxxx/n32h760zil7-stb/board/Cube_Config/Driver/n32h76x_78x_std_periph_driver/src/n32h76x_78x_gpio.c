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
 * @file n32h76x_78x_gpio.c
 * @author Nations
 * @version v1.0.0
 *
 * @copyright Copyright (c) 2025, Nations Technologies Inc. All rights reserved.
 */
/* Includes ------------------------------------------------------------------*/
#include "n32h76x_78x_gpio.h"
#include "n32h76x_78x_rcc.h"


#define GPIO_MODE             			((uint32_t)0x00000003)
//#define EXTI_MODE             			((uint32_t)0x10000000)
//#define GPIO_MODE_IT          			((uint32_t)0x00010000)
//#define GPIO_MODE_EVT         			((uint32_t)0x00020000)
//#define RISING_EDGE           			((uint32_t)0x00100000)
//#define FALLING_EDGE          			((uint32_t)0x00200000)
#define GPIO_OUTPUT_TYPE      			((uint32_t)0x00000010)
//#define GPIO_NUMBER           			((uint32_t)16)
#define GPIO_FILT_STEGE_MASK ((uint32_t)0x0000001F)


/**
*\*\name   GPIO_DeInit.
*\*\fun    Reset the GPIOx peripheral registers to their default reset values.
*\*\param  GPIOx :
*\*\          - GPIOA
*\*\          - GPIOB
*\*\          - GPIOC
*\*\          - GPIOD
*\*\          - GPIOE
*\*\          - GPIOF
*\*\          - GPIOG
*\*\          - GPIOH
*\*\          - GPIOI
*\*\          - GPIOJ
*\*\          - GPIOK
*\*\return none
*/
void GPIO_DeInit(GPIO_Module* GPIOx)
{
    /* Configure the port pins */
    /*------------------------- GPIO Mode Configuration --------------------*/
    if (GPIOx == GPIOA)
    {
        RCC_EnableAHB5PeriphReset1(RCC_AHB5_PERIPHRST_GPIOA);
    }
    else if (GPIOx == GPIOB)
    {
        RCC_EnableAHB5PeriphReset1(RCC_AHB5_PERIPHRST_GPIOB);
    }
    else if (GPIOx == GPIOC)
    {
        RCC_EnableAHB5PeriphReset1(RCC_AHB5_PERIPHRST_GPIOC);
    }
    else if (GPIOx == GPIOD)
    {
        RCC_EnableAHB5PeriphReset1(RCC_AHB5_PERIPHRST_GPIOD);
    }
    else if (GPIOx == GPIOE)
    {
        RCC_EnableAHB5PeriphReset1(RCC_AHB5_PERIPHRST_GPIOE);
    }
    else if (GPIOx == GPIOF)
    {
        RCC_EnableAHB5PeriphReset1(RCC_AHB5_PERIPHRST_GPIOF);
    }
    else if (GPIOx == GPIOG)
    {
        RCC_EnableAHB5PeriphReset1(RCC_AHB5_PERIPHRST_GPIOG);
    }
    else if (GPIOx == GPIOH)
    {
        RCC_EnableAHB5PeriphReset1(RCC_AHB5_PERIPHRST_GPIOH);
    }
    else if (GPIOx == GPIOI)
    {
        RCC_EnableAHB5PeriphReset2(RCC_AHB5_PERIPHRST_GPIOI);
    }
    else if (GPIOx == GPIOJ)
    {
        RCC_EnableAHB5PeriphReset2(RCC_AHB5_PERIPHRST_GPIOJ);
    }
    else if (GPIOx == GPIOK)
    {
        RCC_EnableAHB5PeriphReset2(RCC_AHB5_PERIPHRST_GPIOK);
    }
    else
    {
        return;
    }
}


/**
*\*\name   GPIO_InitPeripheral.
*\*\fun    Initialize the GPIOx peripheral with the value of the GPIO_InitStruct structure.
*\*\param   GPIOx :
*\*\          - GPIOA
*\*\          - GPIOB
*\*\          - GPIOC
*\*\          - GPIOD
*\*\          - GPIOE
*\*\          - GPIOF
*\*\          - GPIOG
*\*\          - GPIOH
*\*\          - GPIOI
*\*\          - GPIOJ
*\*\          - GPIOK
*\*\param  GPIO_InitStructure :
*\*\          - Pin
*\*\             - GPIO_PIN_0
*\*\             - GPIO_PIN_1
*\*\             - GPIO_PIN_2
*\*\             - GPIO_PIN_3
*\*\             - GPIO_PIN_4
*\*\             - GPIO_PIN_5
*\*\             - GPIO_PIN_6
*\*\             - GPIO_PIN_7
*\*\             - GPIO_PIN_8
*\*\             - GPIO_PIN_9
*\*\             - GPIO_PIN_10
*\*\             - GPIO_PIN_11
*\*\             - GPIO_PIN_12
*\*\             - GPIO_PIN_13
*\*\             - GPIO_PIN_14
*\*\             - GPIO_PIN_15
*\*\             - GPIO_PIN_ALL
*\*\          - GPIO_Mode
*\*\             - GPIO_MODE_INPUT
*\*\             - GPIO_MODE_OUTPUT_PP
*\*\             - GPIO_MODE_OUTPUT_OD
*\*\             - GPIO_MODE_AF_PP
*\*\             - GPIO_MODE_AF_OD
*\*\             - GPIO_MODE_ANALOG
*\*\          - GPIO_Pull
*\*\             - GPIO_NO_PULL
*\*\             - GPIO_PULL_UP
*\*\             - GPIO_PULL_DOWN
*\*\          - GPIO_Slew_Rate
*\*\             - GPIO_SLEW_RATE_FAST
*\*\             - GPIO_SLEW_RATE_SLOW
*\*\          - GPIO_Current
*\*\             - GPIO_DC_2mA
*\*\             - GPIO_DC_4mA
*\*\             - GPIO_DC_8mA
*\*\             - GPIO_DC_12mA
*\*\             - GPIO_5VTOL_DC_1mA
*\*\             - GPIO_5VTOL_DC_2mA
*\*\             - GPIO_5VTOL_DC_4mA
*\*\             - GPIO_5VTOL_DC_6mA
*\*\             - GPIO_SDRAM_DC_1mA
*\*\             - GPIO_SDRAM_DC_2mA
*\*\             - GPIO_SDRAM_DC_4mA
*\*\             - GPIO_SDRAM_DC_5mA
*\*\             - GPIO_SDRAM_DC_8mA
*\*\             - GPIO_SDRAM_DC_12mA
*\*\          - GPIO_Alternate
*\*\             - GPIO_AF0
*\*\             - GPIO_AF1
*\*\             - GPIO_AF2
*\*\             - GPIO_AF3
*\*\             - GPIO_AF4
*\*\             - GPIO_AF5
*\*\             - GPIO_AF6
*\*\             - GPIO_AF7
*\*\             - GPIO_AF8
*\*\             - GPIO_AF9
*\*\             - GPIO_AF10
*\*\             - GPIO_AF11
*\*\             - GPIO_AF12
*\*\             - GPIO_AF13
*\*\             - GPIO_AF14
*\*\             - GPIO_AF15
*\*\             - GPIO_NO_AF
*\*\return none
**/
void GPIO_InitPeripheral( GPIO_Module* GPIOx, GPIO_InitType* GPIO_InitStruct )
{
    uint32_t position = 0x00U;
    uint32_t iocurrent = 0x00U;
    uint32_t temp = 0x00U;

    /* Configure the port pins */

    while ((( GPIO_InitStruct->Pin ) >> position ) != 0 )
    {
        /* Get the IO position */
        iocurrent = ( GPIO_InitStruct->Pin ) & ( 1U << position );

        if ( iocurrent )
        {
            /*--------------------- GPIO Mode Configuration ------------------------*/
            /* In case of Alternate function mode selection */
            if (( GPIO_InitStruct->GPIO_Mode == GPIO_MODE_AF_PP) || (GPIO_InitStruct->GPIO_Mode == GPIO_MODE_AF_OD ) ||
                    (GPIO_InitStruct->GPIO_Mode == GPIO_MODE_INPUT)  || (GPIO_InitStruct->GPIO_Mode == GPIO_MODE_ANALOG))
            {
                /* Configure Alternate function mapped with the current IO */
                if(position & 0x08)
                {
                    temp = GPIOx->AFH;
                    temp &= ~(( uint32_t )0xFU << (( uint32_t )( position & ( uint32_t )0x07U ) * 4U ) ) ;
                    temp |= (( uint32_t )( GPIO_InitStruct->GPIO_Alternate ) << ((( uint32_t )position & ( uint32_t )0x07U ) * 4U ) ) ;
                    GPIOx->AFH = temp;
                }
                else
                {
                    temp = GPIOx->AFL;
                    temp &= ~(( uint32_t )0xFU << (( uint32_t )( position & ( uint32_t )0x07U ) * 4U ) ) ;
                    temp |= (( uint32_t )( GPIO_InitStruct->GPIO_Alternate ) << ((( uint32_t )position & ( uint32_t )0x07U ) * 4U ) ) ;
                    GPIOx->AFL = temp;
                }
            }

            /* In case of Output or Alternate function mode selection */
            if (( GPIO_InitStruct->GPIO_Mode == GPIO_MODE_OUTPUT_PP ) || ( GPIO_InitStruct->GPIO_Mode == GPIO_MODE_AF_PP ) ||
                    ( GPIO_InitStruct->GPIO_Mode == GPIO_MODE_OUTPUT_OD ) || ( GPIO_InitStruct->GPIO_Mode == GPIO_MODE_AF_OD ) )
            {
                /* Configure the IO Output Type */
                temp = GPIOx->POTYPE;
                temp &= ~( GPIO_POTYPE_POT0 << position ) ;
                temp |= ((( GPIO_InitStruct->GPIO_Mode & GPIO_OUTPUT_TYPE ) >> 4U ) << position );
                GPIOx->POTYPE = temp;
            }

            /* Configure IO Direction mode (Input, Output, Alternate or Analog) */
            temp = GPIOx->PMODE;

            temp &= ~( GPIO_PMODE_PMODE0 << ( position * 2U ) );

            temp |= (( GPIO_InitStruct->GPIO_Mode & GPIO_MODE ) << ( position * 2U ) );

            GPIOx->PMODE = temp;

            /* Activate the Pull-up or Pull down resistor for the current IO */
            temp = GPIOx->PUPD;

            temp &= ~( GPIO_PUPD_PUPD0 << ( position * 2U ) );

            temp |= (( GPIO_InitStruct->GPIO_Pull ) << ( position * 2U ) );

            GPIOx->PUPD = temp;

            /* Configure slew rate */
            temp = GPIOx->SR;

            temp &= ~(GPIO_SR_BIT_MASK << position);

            temp |= (GPIO_InitStruct->GPIO_Slew_Rate << position);

            GPIOx->SR = temp;

            /* Configure driver current */
            temp = GPIOx->DS;

            temp &= ~(GPIO_DS_BIT_MASK << ( position * 2U ));

            temp |= (GPIO_InitStruct->GPIO_Current << ( position * 2U ));

            GPIOx->DS = temp;
        }

        position++;
    }
}
/**
 *\*\name   GPIO_AFIOInitDefault.
 *\*\fun    Reset the AFIO peripheral registers to their default reset values.
 *\*\param  none
 *\*\return none
 */
void GPIO_AFIOInitDefault(void)
{
    RCC_EnableAHB5PeriphReset2(RCC_AHB5_PERIPHRST_AFIO);
}
/**
 *\*\name   GPIO_InitStruct.
 *\*\fun    Assign default values to each InitStruct member.
 *\*\param  InitStruct :
 *\*\           pointer to GPIO_InitType structure.
 *\*\return none
 */
void GPIO_InitStruct(GPIO_InitType* InitStruct)
{
    /* Reset GPIO structure member */
    InitStruct->Pin            = GPIO_PIN_NONE;
    InitStruct->GPIO_Mode      = GPIO_MODE_INPUT;
    InitStruct->GPIO_Pull      = GPIO_NO_PULL;
    InitStruct->GPIO_Slew_Rate = GPIO_SLEW_RATE_SLOW;
    InitStruct->GPIO_Current   = GPIO_DC_2mA;
    InitStruct->GPIO_Alternate = GPIO_NO_AF;
}

/**
 *\*\name   GPIO_ReadInputDataBit.
 *\*\fun    Get the pin status on the specified input pin.
 *\*\param  GPIOx :
 *\*\          - GPIOA
 *\*\          - GPIOB
 *\*\          - GPIOC
 *\*\          - GPIOD
 *\*\          - GPIOE
 *\*\          - GPIOF
 *\*\          - GPIOG
 *\*\          - GPIOH
 *\*\          - GPIOI
 *\*\          - GPIOJ
 *\*\          - GPIOK
 *\*\param  Pin :
 *\*\          - GPIO_PIN_0
 *\*\          - GPIO_PIN_1
 *\*\          - GPIO_PIN_2
 *\*\          - GPIO_PIN_3
 *\*\          - GPIO_PIN_4
 *\*\          - GPIO_PIN_5
 *\*\          - GPIO_PIN_6
 *\*\          - GPIO_PIN_7
 *\*\          - GPIO_PIN_8
 *\*\          - GPIO_PIN_9
 *\*\          - GPIO_PIN_10
 *\*\          - GPIO_PIN_11
 *\*\          - GPIO_PIN_12
 *\*\          - GPIO_PIN_13
 *\*\          - GPIO_PIN_14
 *\*\          - GPIO_PIN_15
 *\*\return the state on the input pin
  */
uint8_t GPIO_ReadInputDataBit( GPIO_Module* GPIOx, uint16_t GPIO_Pin )
{
    uint8_t bitstatus = 0x00;

    if (( GPIOx->PID & GPIO_Pin ) != ( uint32_t )Bit_RESET )
    {
        bitstatus = ( uint8_t )Bit_SET;
    }
    else
    {
        bitstatus = ( uint8_t )Bit_RESET;
    }

    return bitstatus;
}

/**
 *\*\name   GPIO_ReadInputData.
 *\*\fun    Get the input data on the designated GPIO port.
 *\*\param  GPIOx :
 *\*\          - GPIOA
 *\*\          - GPIOB
 *\*\          - GPIOC
 *\*\          - GPIOD
 *\*\          - GPIOE
 *\*\          - GPIOF
 *\*\          - GPIOG
 *\*\          - GPIOH
 *\*\          - GPIOI
 *\*\          - GPIOJ
 *\*\          - GPIOK
 *\*\return the data value on the GPIO input port.
 */
uint16_t GPIO_ReadInputData( GPIO_Module* GPIOx )
{
    return (( uint16_t )GPIOx->PID );
}

/**
 *\*\name   GPIO_ReadOutputDataBit.
 *\*\fun    Get the pin status on the specified input pin.
 *\*\param  GPIOx :
 *\*\          - GPIOA
 *\*\          - GPIOB
 *\*\          - GPIOC
 *\*\          - GPIOD
 *\*\          - GPIOE
 *\*\          - GPIOF
 *\*\          - GPIOG
 *\*\          - GPIOH
 *\*\          - GPIOI
 *\*\          - GPIOJ
 *\*\          - GPIOK
 *\*\param  Pin :
 *\*\          - GPIO_PIN_0
 *\*\          - GPIO_PIN_1
 *\*\          - GPIO_PIN_2
 *\*\          - GPIO_PIN_3
 *\*\          - GPIO_PIN_4
 *\*\          - GPIO_PIN_5
 *\*\          - GPIO_PIN_6
 *\*\          - GPIO_PIN_7
 *\*\          - GPIO_PIN_8
 *\*\          - GPIO_PIN_9
 *\*\          - GPIO_PIN_10
 *\*\          - GPIO_PIN_11
 *\*\          - GPIO_PIN_12
 *\*\          - GPIO_PIN_13
 *\*\          - GPIO_PIN_14
 *\*\          - GPIO_PIN_15
 *\*\return the state on the input pin
  */
uint8_t GPIO_ReadOutputDataBit( GPIO_Module* GPIOx, uint16_t GPIO_Pin )
{
    uint8_t bitstatus = 0x00;

    if (( GPIOx->POD & GPIO_Pin ) != ( uint32_t )Bit_RESET )
    {
        bitstatus = ( uint8_t )Bit_SET;
    }
    else
    {
        bitstatus = ( uint8_t )Bit_RESET;
    }

    return bitstatus;
}


/**
 *\*\name   GPIO_ReadOutputData.
 *\*\fun    Get the output data on the designated GPIO port.
 *\*\param  GPIOx :
 *\*\          - GPIOA
 *\*\          - GPIOB
 *\*\          - GPIOC
 *\*\          - GPIOD
 *\*\          - GPIOE
 *\*\          - GPIOF
 *\*\          - GPIOG
 *\*\          - GPIOH
 *\*\          - GPIOI
 *\*\          - GPIOJ
 *\*\          - GPIOK
 *\*\return the data value on the GPIO output port.
 */
uint16_t GPIO_ReadOutputData( GPIO_Module* GPIOx )
{
    return (( uint16_t )GPIOx->POD );
}

/**
 *\*\name   GPIO_SetBits.
 *\*\fun    Get the pin status on the specified input pin.
 *\*\param  GPIOx :
 *\*\          - GPIOA
 *\*\          - GPIOB
 *\*\          - GPIOC
 *\*\          - GPIOD
 *\*\          - GPIOE
 *\*\          - GPIOF
 *\*\          - GPIOG
 *\*\          - GPIOH
 *\*\          - GPIOI
 *\*\          - GPIOJ
 *\*\          - GPIOK
 *\*\param  Pin :
 *\*\          - GPIO_PIN_0
 *\*\          - GPIO_PIN_1
 *\*\          - GPIO_PIN_2
 *\*\          - GPIO_PIN_3
 *\*\          - GPIO_PIN_4
 *\*\          - GPIO_PIN_5
 *\*\          - GPIO_PIN_6
 *\*\          - GPIO_PIN_7
 *\*\          - GPIO_PIN_8
 *\*\          - GPIO_PIN_9
 *\*\          - GPIO_PIN_10
 *\*\          - GPIO_PIN_11
 *\*\          - GPIO_PIN_12
 *\*\          - GPIO_PIN_13
 *\*\          - GPIO_PIN_14
 *\*\          - GPIO_PIN_15
 *\*\return the state on the input pin
  */
void GPIO_SetBits( GPIO_Module* GPIOx, uint16_t GPIO_Pin )
{
    GPIOx->PBSC = GPIO_Pin;
}

/**
 *\*\name   GPIO_ResetBits.
 *\*\fun    Reset the selected data port bits.
 *\*\param  GPIOx :
 *\*\          - GPIOA
 *\*\          - GPIOB
 *\*\          - GPIOC
 *\*\          - GPIOD
 *\*\          - GPIOE
 *\*\          - GPIOF
 *\*\          - GPIOG
 *\*\          - GPIOH
 *\*\          - GPIOI
 *\*\          - GPIOJ
 *\*\          - GPIOK
 *\*\param  Pin :
 *\*\          - GPIO_PIN_0
 *\*\          - GPIO_PIN_1
 *\*\          - GPIO_PIN_2
 *\*\          - GPIO_PIN_3
 *\*\          - GPIO_PIN_4
 *\*\          - GPIO_PIN_5
 *\*\          - GPIO_PIN_6
 *\*\          - GPIO_PIN_7
 *\*\          - GPIO_PIN_8
 *\*\          - GPIO_PIN_9
 *\*\          - GPIO_PIN_10
 *\*\          - GPIO_PIN_11
 *\*\          - GPIO_PIN_12
 *\*\          - GPIO_PIN_13
 *\*\          - GPIO_PIN_14
 *\*\          - GPIO_PIN_15
 *\*\return none
 */
void GPIO_ResetBits( GPIO_Module* GPIOx, uint16_t GPIO_Pin )
{
    GPIOx->PBC = GPIO_Pin;
}


/**
 *\*\name   GPIO_WriteBit.
 *\*\fun    Reset the selected data port bits.
 *\*\param  GPIOx :
 *\*\          - GPIOA
 *\*\          - GPIOB
 *\*\          - GPIOC
 *\*\          - GPIOD
 *\*\          - GPIOE
 *\*\          - GPIOF
 *\*\          - GPIOG
 *\*\          - GPIOH
 *\*\          - GPIOI
 *\*\          - GPIOJ
 *\*\          - GPIOK
 *\*\param  Pin :
 *\*\          - GPIO_PIN_0
 *\*\          - GPIO_PIN_1
 *\*\          - GPIO_PIN_2
 *\*\          - GPIO_PIN_3
 *\*\          - GPIO_PIN_4
 *\*\          - GPIO_PIN_5
 *\*\          - GPIO_PIN_6
 *\*\          - GPIO_PIN_7
 *\*\          - GPIO_PIN_8
 *\*\          - GPIO_PIN_9
 *\*\          - GPIO_PIN_10
 *\*\          - GPIO_PIN_11
 *\*\          - GPIO_PIN_12
 *\*\          - GPIO_PIN_13
 *\*\          - GPIO_PIN_14
 *\*\          - GPIO_PIN_15
  *\*\param  BitVal :
 *\*\          - Bit_RESET
 *\*\          - Bit_SET
 *\*\return none
 */
void GPIO_WriteBit( GPIO_Module* GPIOx, uint16_t GPIO_Pin, Bit_OperateType BitVal )
{
    if ( BitVal != Bit_RESET )
    {
        GPIOx->PBSC = GPIO_Pin;
    }
    else
    {
        GPIOx->PBC = GPIO_Pin;
    }
}

/**
 *\*\name   GPIO_Write.
 *\*\fun    Write data on the designated GPIO data port.
 *\*\param  GPIOx :
 *\*\          - GPIOA
 *\*\          - GPIOB
 *\*\          - GPIOC
 *\*\          - GPIOD
 *\*\          - GPIOE
 *\*\          - GPIOF
 *\*\          - GPIOG
 *\*\          - GPIOH
 *\*\          - GPIOI
 *\*\          - GPIOJ
 *\*\          - GPIOK
 *\*\param  data_value :
 *\*\          the value to be written to the port output data register.
 *\*\          - 0~0xFFFF
 *\*\return none
 */
void GPIO_Write( GPIO_Module* GPIOx, uint16_t data_value)
{
    GPIOx->POD = data_value;
}

/**
 *\*\name   GPIO_Pin_Toggle.
 *\*\fun    Toggle the specified port pin level.
 *\*\param  GPIOx :
 *\*\          - GPIOA
 *\*\          - GPIOB
 *\*\          - GPIOC
 *\*\          - GPIOD
 *\*\          - GPIOE
 *\*\          - GPIOF
 *\*\          - GPIOG
 *\*\          - GPIOH
 *\*\          - GPIOI
 *\*\          - GPIOJ
 *\*\          - GPIOK
 *\*\param  Pin :
 *\*\          - GPIO_PIN_0
 *\*\          - GPIO_PIN_1
 *\*\          - GPIO_PIN_2
 *\*\          - GPIO_PIN_3
 *\*\          - GPIO_PIN_4
 *\*\          - GPIO_PIN_5
 *\*\          - GPIO_PIN_6
 *\*\          - GPIO_PIN_7
 *\*\          - GPIO_PIN_8
 *\*\          - GPIO_PIN_9
 *\*\          - GPIO_PIN_10
 *\*\          - GPIO_PIN_11
 *\*\          - GPIO_PIN_12
 *\*\          - GPIO_PIN_13
 *\*\          - GPIO_PIN_14
 *\*\          - GPIO_PIN_15
 *\*\return none
 */
void GPIO_TogglePin(GPIO_Module *GPIOx, uint16_t Pin)
{
    GPIOx->POD ^= Pin;
}


/**
 *\*\name   GPIO_ConfigPinLock.
 *\*\fun    Toggle the specified port pin level.
 *\*\param  GPIOx :
 *\*\          - GPIOA
 *\*\          - GPIOB
 *\*\          - GPIOC
 *\*\          - GPIOD
 *\*\          - GPIOE
 *\*\          - GPIOF
 *\*\          - GPIOG
 *\*\          - GPIOH
 *\*\          - GPIOI
 *\*\          - GPIOJ
 *\*\          - GPIOK
 *\*\param  Pin :
 *\*\          - GPIO_PIN_0
 *\*\          - GPIO_PIN_1
 *\*\          - GPIO_PIN_2
 *\*\          - GPIO_PIN_3
 *\*\          - GPIO_PIN_4
 *\*\          - GPIO_PIN_5
 *\*\          - GPIO_PIN_6
 *\*\          - GPIO_PIN_7
 *\*\          - GPIO_PIN_8
 *\*\          - GPIO_PIN_9
 *\*\          - GPIO_PIN_10
 *\*\          - GPIO_PIN_11
 *\*\          - GPIO_PIN_12
 *\*\          - GPIO_PIN_13
 *\*\          - GPIO_PIN_14
 *\*\          - GPIO_PIN_15
 *\*\return none
 */
void GPIO_ConfigPinLock(GPIO_Module* GPIOx, uint16_t Pin)
{
    __IO uint32_t tmp = GPIO_PLOCK_PLOCKK;

    if(GPIOx == GPIOK)
    {
        tmp = GPIO_PLOCK_PLOCKK >> 8;
    }

    tmp |= Pin;
    /* Set PLOCKK bit */
    GPIOx->PLOCK = tmp;
    /* Reset PLOCKK bit */
    GPIOx->PLOCK = Pin;
    /* Set PLOCKK bit */
    GPIOx->PLOCK = tmp;
    /* Read PLOCKK bit*/
    tmp = GPIOx->PLOCK;
    /* Read PLOCKK bit*/
    tmp = GPIOx->PLOCK;
}


/**
*\*\name   GPIO_EXTILineConfig.
*\*\fun    Selects the GPIO pin used as EXTI Line.
*\*\param  EXTI_Line
             - EXTI_LINE0
             - EXTI_LINE1
             - ......
             - EXTI_LINE15
*\*\param  GPIO_PinSource
             - EXTI_GPIOA_Pin_0
             - ......
             - EXTI_GPIOA_Pin_15
             - EXTI_GPIOB_Pin_0
             - ......
             - EXTI_GPIOB_Pin_15
             - ......
             - EXTI_GPIOJ_Pin_0
             - ......
             - EXTI_GPIOJ_Pin_15
*\*\return none
*/
void GPIO_ConfigEXTILine(uint8_t EXTI_Line, uint8_t GPIO_PinSource)
{
    AFIO->EXTI_CFG[EXTI_Line / 4] |= GPIO_PinSource << (8 * (EXTI_Line % 4));
}

/**
 *\*\name   AFIO_ConfigSIPFLASHSEL.
 *\*\fun    Configure the SIP FLASH MODE SEL.
 *\*\param  AFIO_FLASH :
 *\*\          - AFIO_FLASH0
 *\*\          - AFIO_FLASH1
 *\*\          - AFIO_FLASH2
 *\*\          - AFIO_FLASH3
 *\*\          - AFIO_FLASH4
 *\*\          - AFIO_DISFLASH
 *\*\return none
 */
void AFIO_ConfigSIPFLASHSEL(uint32_t AFIO_FLASH)
{
    uint32_t tempReg;

    tempReg = AFIO->RMP_CFG;
    tempReg &= ~AFIO_RMP_CFG_SIP_FLASHSEL;
    tempReg |= AFIO_FLASH;

    AFIO->RMP_CFG = tempReg;
}

/**
 *\*\name   AFIO_ConfigSPINSSMode.
 *\*\fun    Configure the SPIx NSS mode during idle.
 *\*\param  AFIO_SPIx_NSS :
 *\*\          - AFIO_SPI1_NSS
 *\*\          - AFIO_SPI2_NSS
 *\*\          - AFIO_SPI3_NSS
 *\*\          - AFIO_SPI4_NSS
 *\*\          - AFIO_SPI5_NSS
 *\*\          - AFIO_SPI6_NSS
 *\*\          - AFIO_SPI7_NSS
 *\*\param  NSS_Mode :
 *\*\          - AFIO_SPI_NSS_HIGH_IMPEDANCE
 *\*\          - AFIO_SPI_NSS_HIGH_LEVEL
 *\*\return none
 */
void AFIO_ConfigSPINSSMode(uint32_t AFIO_SPIx_NSS, uint32_t NSS_Mode)
{
    uint32_t tempReg;

    tempReg = AFIO->RMP_CFG;

    if(NSS_Mode != AFIO_SPI_NSS_HIGH_IMPEDANCE)
    {
        tempReg |= AFIO_SPIx_NSS;
    }
    else
    {
        tempReg &= ~AFIO_SPIx_NSS;
    }

    AFIO->RMP_CFG = tempReg;
}

/**
 *\*\name   AFIO_Config_EXTI_Filter.
 *\*\fun    Enable or disable EXTI analog filter.
 *\*\param  EXTI_Filter :
 *\*\        - AFIO_EXTI_FILTER_ENABLE
 *\*\        - AFIO_EXTI_FILTER_DISABLE
 *\*\return none
 */
void AFIO_ConfigEXTIFilter(uint32_t EXTI_Filter)
{
    uint32_t tempReg;

    tempReg = AFIO->RMP_CFG ;

    if(EXTI_Filter != AFIO_EXTI_FILTER_ENABLE)
    {
        tempReg |= AFIO_EXTI_FILTER_DISABLE;
    }
    else
    {
        tempReg &= ~AFIO_EXTI_FILTER_DISABLE;
    }

    AFIO->RMP_CFG = tempReg;
}

/**
*\*\name   AFIO_ConfigSIPSDRAMPrior.
*\*\fun    Configure SIP SDRAM prority.
*\*\param  priority :
*\*\          - AFIO_SIP_SDRAM_PRIORITY_HIGH
*\*\          - AFIO_SIP_SDRAM_PRIORITY_LOW
*\*\return none
**/
void AFIO_ConfigSIPSDRAMPrior(uint32_t priority)
{
    uint32_t tempReg;

    tempReg = AFIO->RMP_CFG;

    if(priority != AFIO_SIP_SDRAM_PRIORITY_LOW)
    {
        tempReg |= AFIO_SIP_SDRAM_PRIORITY_HIGH;
    }
    else
    {
        tempReg &= ~AFIO_SIP_SDRAM_PRIORITY_HIGH;
    }

    AFIO->RMP_CFG = tempReg;
}

/**
 *\*\name   AFIO_ConfigSPII2SMode.
 *\*\fun    SEL only for pads sharing SPI/I2S.
 *\*\param  AFIO_SPIx_I2Sx :
 *\*\          - AFIO_SELECT_SPI1
 *\*\          - AFIO_SELECT_SPI2
 *\*\          - AFIO_SELECT_SPI3
 *\*\          - AFIO_SELECT_SPI4
 *\*\param  PADS_Mode :
 *\*\          - SPI_MODE
 *\*\          - I2S_MODE
 *\*\return none
 */
void AFIO_ConfigSPII2SMode(uint32_t AFIO_SPIx_I2Sx, uint32_t PADS_Mode)
{
    uint32_t tempReg;

    tempReg = AFIO->RMP_CFG;

    if(PADS_Mode != I2S_MODE)
    {
        tempReg |= AFIO_SPIx_I2Sx;
    }
    else
    {
        tempReg &= ~AFIO_SPIx_I2Sx;
    }

    AFIO->RMP_CFG = tempReg;
}

/**
 *\*\name   AFIO_SDMMCClkSel.
 *\*\fun    SDMMC clk external or feedback clk input.
 *\*\param  AFIO_clk_sel :
 *\*\          - SDMMC1_CLKFB
 *\*\          - SDMMC2_CLKFB
 *\*\param  cmd :
 *\*\          - ENABLE
 *\*\          - DISABLE
 *\*\return none
 */
void AFIO_SDMMCClkSel(uint32_t AFIO_clk_sel, FunctionalState cmd)
{
    uint32_t tempReg;

    tempReg = AFIO->RMP_CFG;

    if(cmd != DISABLE)
    {
        tempReg |= AFIO_clk_sel;
    }
    else
    {
        tempReg &= ~AFIO_clk_sel;
    }

    AFIO->RMP_CFG = tempReg;
}


/**
 *\*\name   AFIO_I2SFullpuplexSel.
 *\*\fun    To enable full duplex mode for I2S1-4
 *\*\param  AFIO_I2S_sel :
 *\*\          - I2S1_FULLDUPLEX
 *\*\          - I2S2_FULLDUPLEX
 *\*\          - I2S3_FULLDUPLEX
 *\*\          - I2S4_FULLDUPLEX
 *\*\return none
 */
void AFIO_I2SFullpuplexSel(uint32_t AFIO_clk_sel)
{
    uint32_t tempReg;

    tempReg = AFIO->RMP_CFG;

    tempReg &= ~AFIO_RMP_CFG_I2S_FDUP;
    tempReg |= AFIO_clk_sel;

    AFIO->RMP_CFG = tempReg;
}

/**
 *\*\name   AFIO_ConfigXSPIBigEndian.
 *\*\fun    Enable or disable the big endian for XSPI XIP mode.
 *\*\param  AFIO_BigEndian_sel :
 *\*\          - XSPI1_ENDIAN
 *\*\          - XSPI2_ENDIAN
 *\*\param  Endian :
 *\*\          - XSPI_LITTLE_ENDIAN
 *\*\          - XSPI_BIG_ENDIAN
 *\*\return none
 */
void AFIO_ConfigXSPIBigEndian(uint32_t xspi_endian, uint32_t Endian)
{
    uint32_t tempReg;

    tempReg = AFIO->RMP_CFG ;

    if(Endian != XSPI_LITTLE_ENDIAN)
    {
        tempReg |= xspi_endian;
    }
    else
    {
        tempReg &= ~xspi_endian;
    }

    AFIO->RMP_CFG = tempReg;
}

/**
 *\*\name   AFIO_ConfigFEMCNANDSRAM.
 *\*\fun    To select between Nand and Sram.
 *\*\param  Nand_Sram_sel :
 *\*\        - FEMC_NAND_SEL
 *\*\        - FEMC_SRAM_SEL
 *\*\return none
 */
void AFIO_ConfigFEMCNANDSRAM(uint32_t Nand_Sram_sel)
{
    uint32_t tempReg;

    tempReg = AFIO->RMP_CFG ;

    if(Nand_Sram_sel == FEMC_NAND_SEL)
    {
        tempReg |= FEMC_NAND_SEL;
    }
    else
    {
        tempReg &= ~FEMC_NAND_SEL;
    }

    AFIO->RMP_CFG = tempReg;
}


/**
 *\*\name   AFIO_FEMCNOByteStrobe.
 *\*\fun    ANDed of NBLs for Flashes do or not support byte strobes.
 *\*\param  Byte_Strobes_sel :
 *\*\        - NO_BYTE_STROBE
 *\*\        - BYTE_STROBE
 *\*\return none
 */
void AFIO_FEMCNOByteStrobe(uint32_t Byte_Strobes_sel)
{
    uint32_t tempReg;

    tempReg = AFIO->RMP_CFG ;

    if(Byte_Strobes_sel == NO_BYTE_STROBE)
    {
        tempReg |= NO_BYTE_STROBE;
    }
    else
    {
        tempReg &= ~NO_BYTE_STROBE;
    }

    AFIO->RMP_CFG = tempReg;
}

/**
 *\*\name   AFIO_ConfigETH1Mode.
 *\*\fun    For the ETH1 PHY selection.
 *\*\param  ETH1_PHY_sel :
 *\*\          ETH1_GMII_SEL
 *\*\          ETH1_RGMII_SEL
 *\*\          ETH1_RMII_SEL
 *\*\          ETH1_MII_SEL
 *\*\return none
 */
void AFIO_ConfigETH1Mode(uint32_t ETH1_PHY_sel)
{
    uint32_t tempReg;

    tempReg = AFIO->RMP_CFG;

    tempReg &= ~AFIO_RMP_CFG_ETH1_PHY;

    tempReg |= ETH1_PHY_sel;

    AFIO->RMP_CFG = tempReg;
}

/**
 *\*\name   AFIO_ConfigETH2Mode.
 *\*\fun    For the ETH2 PHY selection.
 *\*\param  ETH2_PHY_sel :
 *\*\        - ETH2_RMII_SEL
 *\*\        - ETH2_MII_SEL
 *\*\return none
 */
void AFIO_ConfigETH2Mode(uint32_t ETH2_PHY_sel)
{
    uint32_t tempReg;

    tempReg = AFIO->RMP_CFG ;

    if(ETH2_PHY_sel == ETH2_RMII_SEL)
    {
        tempReg |= ETH2_RMII_SEL;
    }
    else
    {
        tempReg &= ~ETH2_RMII_SEL;
    }

    AFIO->RMP_CFG = tempReg;
}

/**
*\*\name   AFIO_ConfigSHRT1FALTPin.
*\*\fun    SHRTIM1 GPIO FAULT PIN Config
*\*\param  channel_pin :
*\*\          - SHRT1_FAULT_CHANNEL_PA15
*\*\          - SHRT1_FAULT_CHANNEL_PB3
*\*\          - SHRT1_FAULT_CHANNEL_PC11
*\*\          - SHRT1_FAULT_CHANNEL_PD4
*\*\          - SHRT1_FAULT_CHANNEL_PE4
*\*\          - SHRT1_FAULT_CHANNEL_PG9
*\*\          - SHRT1_FAULT_CHANNEL_PG10
*\*\          - SHRT1_FAULT_CHANNEL_PI6
*\*\          - SHRT1_FAULT_CHANNEL_PI15
*\*\          - SHRT1_FAULT_CHANNEL_PK2
*\*\param  channel_num :
*\*\          - SHRT_FAULT_CHANNEL_1
*\*\          - SHRT_FAULT_CHANNEL_2
*\*\          - SHRT_FAULT_CHANNEL_3
*\*\          - SHRT_FAULT_CHANNEL_4
*\*\          - SHRT_FAULT_CHANNEL_5
*\*\          - SHRT_FAULT_CHANNEL_6
*\*\return none
**/
void AFIO_ConfigSHRT1FALTPin(SHRT1_FAULT_CHANNEL channel_pin, SHRT_FAULT_CHANNEL_NUM channel_num)
{
    uint32_t tempReg;

    tempReg = AFIO->SHRT1_FALT_CFG;
    tempReg &= ~(AFIO_SHRT1_FALT_CFG_SHRT_FALT1 << ((channel_num) * 4));
    tempReg |= channel_pin << (channel_num * 4);
    AFIO->SHRT1_FALT_CFG = tempReg;
}

/**
*\*\name   AFIO_ConfigSHRT2FALTPin.
*\*\fun    SHRTIM2 GPIO FAULT PIN Config
*\*\param  channel_pin :
*\*\          - SHRT2_FAULT_CHANNEL_PC5
*\*\          - SHRT2_FAULT_CHANNEL_PD1
*\*\          - SHRT2_FAULT_CHANNEL_PD15
*\*\          - SHRT2_FAULT_CHANNEL_PF9
*\*\          - SHRT2_FAULT_CHANNEL_PF13
*\*\          - SHRT2_FAULT_CHANNEL_PG1
*\*\          - SHRT2_FAULT_CHANNEL_PI0
*\*\          - SHRT2_FAULT_CHANNEL_PI9
*\*\          - SHRT2_FAULT_CHANNEL_PI13
*\*\          - SHRT2_FAULT_CHANNEL_PJ0
*\*\          - SHRT2_FAULT_CHANNEL_PK1
*\*\          - SHRT2_FAULT_CHANNEL_PK6
*\*\param  channel_num :
*\*\          - SHRT_FAULT_CHANNEL_1
*\*\          - SHRT_FAULT_CHANNEL_2
*\*\          - SHRT_FAULT_CHANNEL_3
*\*\          - SHRT_FAULT_CHANNEL_4
*\*\          - SHRT_FAULT_CHANNEL_5
*\*\          - SHRT_FAULT_CHANNEL_6
*\*\return none
**/
void AFIO_ConfigSHRT2FALTPin(SHRT2_FAULT_CHANNEL channel_pin, SHRT_FAULT_CHANNEL_NUM channel_num)
{
    uint32_t tempReg;

    tempReg = AFIO->SHRT2_FALT_CFG;
    tempReg &= ~(AFIO_SHRT2_FALT_CFG_SHRT_FALT1 << ((channel_num) * 4));
    tempReg |= channel_pin << (channel_num * 4);
    AFIO->SHRT2_FALT_CFG = tempReg;
}

/**
*\*\name   AFIO_ConfigSHRT1EXEVPin.
*\*\fun    SHRTIM1 external event pin Config
*\*\param  channel_pin :
*\*\          - SHRT1_EXEV_CHANNEL_PB4
*\*\          - SHRT1_EXEV_CHANNEL_PB5
*\*\          - SHRT1_EXEV_CHANNEL_PB6
*\*\          - SHRT1_EXEV_CHANNEL_PB7
*\*\          - SHRT1_EXEV_CHANNEL_PC10
*\*\          - SHRT1_EXEV_CHANNEL_PC12
*\*\          - SHRT1_EXEV_CHANNEL_PD5
*\*\          - SHRT1_EXEV_CHANNEL_PD8
*\*\          - SHRT1_EXEV_CHANNEL_PD9
*\*\          - SHRT1_EXEV_CHANNEL_PE6
*\*\          - SHRT1_EXEV_CHANNEL_PG0
*\*\          - SHRT1_EXEV_CHANNEL_PG11
*\*\          - SHRT1_EXEV_CHANNEL_PG12
*\*\          - SHRT1_EXEV_CHANNEL_PG13
*\*\          - SHRT1_EXEV_CHANNEL_PI14
*\*\          - SHRT1_EXEV_CHANNEL_PJ5
*\*\          - SHRT1_EXEV_CHANNEL_PK3
*\*\          - SHRT1_EXEV_CHANNEL_PK4
*\*\param  channel_num :
*\*\          - SHRT_EXEV_CHANNEL_1
*\*\          - SHRT_EXEV_CHANNEL_2
*\*\          - SHRT_EXEV_CHANNEL_3
*\*\          - SHRT_EXEV_CHANNEL_4
*\*\          - SHRT_EXEV_CHANNEL_5
*\*\          - SHRT_EXEV_CHANNEL_6
*\*\          - SHRT_EXEV_CHANNEL_7
*\*\          - SHRT_EXEV_CHANNEL_8
*\*\          - SHRT_EXEV_CHANNEL_9
*\*\          - SHRT_EXEV_CHANNEL_10
*\*\return none
**/
void AFIO_ConfigSHRT1EXEVPin(SHRT1_EXEV_CHANNEL channel_pin, SHRT_EXEV_CHANNEL_NUM channel_num)
{
    uint32_t tempReg;
    uint32_t temp_index;

    temp_index = channel_num / 5;

    tempReg = AFIO->SHRT1_EXEV_CFG[temp_index];

    tempReg &= ~(AFIO_SHRT1_EXEV_CFG1_SHRT_EXEV1 << ((channel_num % 5) * 5));

    tempReg |= channel_pin << ((channel_num % 5) * 5);

    AFIO->SHRT1_EXEV_CFG[temp_index] = tempReg;
}

/**
*\*\name   AFIO_ConfigSHRT2EXEVPin.
*\*\fun    SHRTIM2 external event pin Config
*\*\param  channel_pin :
*\*\          - SHRT2_EXEV_CHANNEL_PA2
*\*\          - SHRT2_EXEV_CHANNEL_PC4
*\*\          - SHRT2_EXEV_CHANNEL_PD0
*\*\          - SHRT2_EXEV_CHANNEL_PD11
*\*\          - SHRT2_EXEV_CHANNEL_PE3
*\*\          - SHRT2_EXEV_CHANNEL_PE14
*\*\          - SHRT2_EXEV_CHANNEL_PF10
*\*\          - SHRT2_EXEV_CHANNEL_PG8
*\*\          - SHRT2_EXEV_CHANNEL_PG15
*\*\          - SHRT2_EXEV_CHANNEL_PH7
*\*\          - SHRT2_EXEV_CHANNEL_PH8
*\*\          - SHRT2_EXEV_CHANNEL_PH10
*\*\          - SHRT2_EXEV_CHANNEL_PH11
*\*\          - SHRT2_EXEV_CHANNEL_PH12
*\*\          - SHRT2_EXEV_CHANNEL_PI11
*\*\          - SHRT2_EXEV_CHANNEL_PJ2
*\*\          - SHRT2_EXEV_CHANNEL_J14
*\*\          - SHRT2_EXEV_CHANNEL_PK0
*\*\param  channel_num :
*\*\          - SHRT_EXEV_CHANNEL_1
*\*\          - SHRT_EXEV_CHANNEL_2
*\*\          - SHRT_EXEV_CHANNEL_3
*\*\          - SHRT_EXEV_CHANNEL_4
*\*\          - SHRT_EXEV_CHANNEL_5
*\*\          - SHRT_EXEV_CHANNEL_6
*\*\          - SHRT_EXEV_CHANNEL_7
*\*\          - SHRT_EXEV_CHANNEL_8
*\*\          - SHRT_EXEV_CHANNEL_9
*\*\          - SHRT_EXEV_CHANNEL_10
*\*\return none
**/
void AFIO_ConfigSHRT2EXEVPin(SHRT2_EXEV_CHANNEL channel_pin, SHRT_EXEV_CHANNEL_NUM channel_num)
{
    uint32_t tempReg;
    uint32_t temp_index;

    temp_index = channel_num / 5;

    tempReg = AFIO->SHRT2_EXEV_CFG[temp_index];

    tempReg &= ~(AFIO_SHRT2_EXEV_CFG1_SHRT_EXEV1 << ((channel_num % 5) * 5));

    tempReg |= channel_pin << ((channel_num % 5) * 5);

    AFIO->SHRT2_EXEV_CFG[temp_index] = tempReg;
}

/**
*\*\name   AFIO_ConfigPinTol5VGPIOA.
*\*\fun    Enable or disable the PA_5V tolerance.
*\*\param  Pin :
*\*\           - AFIO_TOL5V_PA0
*\*\           - AFIO_TOL5V_PA0_C
*\*\           - AFIO_TOL5V_PA1
*\*\           - AFIO_TOL5V_PA1_C
*\*\           - AFIO_TOL5V_PA2
*\*\           - AFIO_TOL5V_PA3
*\*\           - AFIO_TOL5V_PA4
*\*\           - AFIO_TOL5V_PA5
*\*\           - AFIO_TOL5V_PA6
*\*\           - AFIO_TOL5V_PA7
*\*\param  cmd :
*\*\           - DISABLE
*\*\           - ENABLE
*\*\return none
**/
void AFIO_ConfigPinTol5VGPIOA(uint32_t Pin, FunctionalState cmd)
{
    uint32_t tempReg;

    tempReg = AFIO->TOL5V_CFG1;

    if(cmd != DISABLE)
    {
        tempReg |= Pin;
    }
    else
    {
        tempReg &= ~(Pin);
    }

    AFIO->TOL5V_CFG1 = tempReg;
}

/**
*\*\name   AFIO_ConfigPinTol5VGPIOB.
*\*\fun    Enable or disable the PB_5V tolerance.
*\*\param  Pin :
*\*\           - AFIO_TOL5V_PB0
*\*\           - AFIO_TOL5V_PB1
*\*\param  cmd :
*\*\           - DISABLE
*\*\           - ENABLE
*\*\return none
**/
void AFIO_ConfigPinTol5VGPIOB(uint32_t Pin, FunctionalState cmd)
{
    uint32_t tempReg;

    tempReg = AFIO->TOL5V_CFG2;

    if(cmd != DISABLE)
    {
        tempReg |= Pin;
    }
    else
    {
        tempReg &= ~(Pin);
    }

    AFIO->TOL5V_CFG2 = tempReg;
}
/**
*\*\name   AFIO_ConfigPinTol5VGPIOC.
*\*\fun    Enable or disable the PC_5V tolerance.
*\*\param  Pin :
*\*\           - AFIO_TOL5V_PC0
*\*\           - AFIO_TOL5V_PC1
*\*\           - AFIO_TOL5V_PC2
*\*\           - AFIO_TOL5V_PC2_C
*\*\           - AFIO_TOL5V_PC3
*\*\           - AFIO_TOL5V_PC3_C
*\*\           - AFIO_TOL5V_PC4
*\*\           - AFIO_TOL5V_PC5
*\*\           - AFIO_TOL5V_PC6
*\*\           - AFIO_TOL5V_PC8
*\*\           - AFIO_TOL5V_PC13
*\*\param  cmd :
*\*\           - DISABLE
*\*\           - ENABLE
*\*\return none
**/
void AFIO_ConfigPinTol5VGPIOC(uint32_t Pin, FunctionalState cmd)
{
    uint32_t tempReg;

    tempReg = AFIO->TOL5V_CFG3;

    if(cmd != DISABLE)
    {
        tempReg |= Pin;
    }
    else
    {
        tempReg &= ~(Pin);
    }

    AFIO->TOL5V_CFG3 = tempReg;
}

/**
*\*\name   AFIO_ConfigPinTol5VGPIOF.
*\*\fun    Enable or disable the PF_5V tolerance.
*\*\param  Pin :
*\*\           - AFIO_TOL5V_PF3
*\*\           - AFIO_TOL5V_PF4
*\*\           - AFIO_TOL5V_PF5
*\*\           - AFIO_TOL5V_PF6
*\*\           - AFIO_TOL5V_PF7
*\*\           - AFIO_TOL5V_PF8
*\*\           - AFIO_TOL5V_PF9
*\*\           - AFIO_TOL5V_PF10
*\*\           - AFIO_TOL5V_PF11
*\*\           - AFIO_TOL5V_PF12
*\*\           - AFIO_TOL5V_PF13
*\*\           - AFIO_TOL5V_PF14
*\*\param  cmd :
*\*\           - DISABLE
*\*\           - ENABLE
*\*\return none
**/
void AFIO_ConfigPinTol5VGPIOF( uint32_t Pin, FunctionalState cmd)
{
    uint32_t tempReg;

    tempReg = AFIO->TOL5V_CFG4;

    if(cmd != DISABLE)
    {
        tempReg |= Pin;
    }
    else
    {
        tempReg &= ~(Pin);
    }

    AFIO->TOL5V_CFG4 = tempReg;
}

/**
*\*\name   AFIO_ConfigPinTol5VGPIOH.
*\*\fun    Enable or disable the PH_5V tolerance.
*\*\param  Pin :
*\*\           - AFIO_TOL5V_PH2
*\*\           - AFIO_TOL5V_PH3
*\*\           - AFIO_TOL5V_PH4
*\*\           - AFIO_TOL5V_PH5
*\*\param  cmd :
*\*\           - DISABLE
*\*\           - ENABLE
*\*\return none
**/
void AFIO_ConfigPinTol5VGPIOH( uint32_t Pin, FunctionalState cmd)
{
    uint32_t tempReg;

    tempReg = AFIO->TOL5V_CFG5;

    if(cmd != DISABLE)
    {
        tempReg |= Pin;
    }
    else
    {
        tempReg &= ~(Pin);
    }

    AFIO->TOL5V_CFG5 = tempReg;
}

/**
*\*\name   AFIO_ConfigPinTol5VGPIOI.
*\*\fun    Enable or disable the PI_5V tolerance.
*\*\param  Pin :
*\*\           - AFIO_TOL5V_PI8
*\*\           - AFIO_TOL5V_PI15
*\*\param  cmd :
*\*\           - DISABLE
*\*\           - ENABLE
*\*\return none
**/
void AFIO_ConfigPinTol5VGPIOI( uint32_t Pin, FunctionalState cmd)
{
    uint32_t tempReg;

    tempReg = AFIO->TOL5V_CFG6;

    if(cmd != DISABLE)
    {
        tempReg |= Pin;
    }
    else
    {
        tempReg &= ~(Pin);
    }

    AFIO->TOL5V_CFG6 = tempReg;
}

/**
*\*\name   AFIO_ConfigPinTol5VGPIOJ.
*\*\fun    Enable or disable the PJ_5V tolerance.
*\*\param  Pin :
*\*\           - AFIO_TOL5V_PJ0
*\*\           - AFIO_TOL5V_PJ3
*\*\           - AFIO_TOL5V_PJ4
*\*\           - AFIO_TOL5V_PJ5
*\*\           - AFIO_TOL5V_PJ6
*\*\           - AFIO_TOL5V_PJ7
*\*\param  cmd :
*\*\           - DISABLE
*\*\           - ENABLE
*\*\return none
**/
void AFIO_ConfigPinTol5VGPIOJ( uint32_t Pin, FunctionalState cmd)
{
    uint32_t tempReg;

    tempReg = AFIO->TOL5V_CFG7;

    if(cmd != DISABLE)
    {
        tempReg |= Pin;
    }
    else
    {
        tempReg &= ~(Pin);
    }

    AFIO->TOL5V_CFG7 = tempReg;
}

/**
 *\*\name   AFIO_SIPInitPeripheral.
 *\*\fun    Configure the Sip Pin  Pull up or down
 *\*\param  sip_index :
 *\*\           - AFIO_SIP_DAT7
 *\*\           - AFIO_SIP_DAT6
 *\*\           - AFIO_SIP_DAT5
 *\*\           - AFIO_SIP_DAT4
 *\*\           - AFIO_SIP_DAT3
 *\*\           - AFIO_SIP_DAT2
 *\*\           - AFIO_SIP_DAT1
 *\*\           - AFIO_SIP_DAT0
 *\*\param  pupd :
 *\*\           - AFIO_SIP_Mode_NO_PULL
 *\*\           - AFIO_SIP_Mode_PULL_UP
 *\*\           - AFIO_SIP_Mode_PULL_DOWN
 *\*\param  slew_rate :
 *\*\           - SIP_Mode_FAST
 *\*\           - SIP_Mode_SLOW
 *\*\param  driver_stength :
 *\*\           - SIP_DC_2mA
 *\*\           - SIP_DC_4mA
 *\*\           - SIP_DC_8mA
 *\*\           - SIP_DC_12mA
 *\*\return none
 */
void AFIO_SIPInitPeripheral(uint8_t sip_index, uint32_t pupd, uint32_t slew_rate, uint32_t driver_stength)
{
    uint32_t temp = 0x00U;

    temp = AFIO->SIP_PUPD;

    temp &= ~(AFIO_SIP_MASK << (2 * sip_index));

    temp |= (pupd << (2 * sip_index));

    AFIO->SIP_PUPD = temp;


    temp = AFIO->SIPSR;

    temp &= ~(GPIO_SR_BIT_MASK << (sip_index));

    temp |= (slew_rate << ( sip_index));

    AFIO->SIPSR = temp;

    temp = AFIO->SIPDS;

    temp &= ~(GPIO_DS_BIT_MASK << (2 * sip_index));

    temp |= (driver_stength << (2 * sip_index));

    AFIO->SIPDS = temp;
}

/**
 * @brief  Configur ADC external trigger.
 * @param ADCETRType choose whether to configure rule conversion or injection conversion .
 *   This parameter can be AFIO_ADC_ETRI and AFIO_ADC_ETRR.
 * @param ADCTrigRemap specifies the external trigger line be configured.
 *   This parameter can be AFIO_ADC_TRIG_EXTI_x where x can be (0..15) or AFIO_ADC_TRIG_TIM8_CHy where y can be(3..4).
 */

/**
*\*\name   AFIO_ConfigADCExtLineTrigSource.
*\*\fun    Configurate ADC external line trigger.
*\*\param  ADC_num :
*\*\          - AFIO_ADC_1
*\*\          - AFIO_ADC_2
*\*\          - AFIO_ADC_3
*\*\param  ADCETRType :
*\*\          - AFIO_ADC_ETRI
*\*\          - AFIO_ADC_ETRR
*\*\param  ADC_trigger :
*\*\          - AFIO_ADC_TRIG_EXTI_0
*\*\          - AFIO_ADC_TRIG_EXTI_1
*\*\          - AFIO_ADC_TRIG_EXTI_2
*\*\          - AFIO_ADC_TRIG_EXTI_3
*\*\          - AFIO_ADC_TRIG_EXTI_4
*\*\          - AFIO_ADC_TRIG_EXTI_5
*\*\          - AFIO_ADC_TRIG_EXTI_6
*\*\          - AFIO_ADC_TRIG_EXTI_7
*\*\          - AFIO_ADC_TRIG_EXTI_8
*\*\          - AFIO_ADC_TRIG_EXTI_9
*\*\          - AFIO_ADC_TRIG_EXTI_10
*\*\          - AFIO_ADC_TRIG_EXTI_11
*\*\          - AFIO_ADC_TRIG_EXTI_12
*\*\          - AFIO_ADC_TRIG_EXTI_13
*\*\          - AFIO_ADC_TRIG_EXTI_14
*\*\          - AFIO_ADC_TRIG_EXTI_15
*\*\return none
**/
void AFIO_ConfigADCExtLineTrigSource(AFIO_ADC_NUM ADC_num, AFIO_ADC_ETRType ADCETRType, AFIO_ADC_Trig_RemapType ADCTrigRemap)
{
    uint32_t tmpregister = 0x00;

    /* Check the parameters */
    tmpregister = AFIO->ADCRMP_CFG;

    /* clear AFIO_ADCRMP_CFG register bit*/
    tmpregister &= (~(AFIO_ADCRMP_CFG_ADC3_EXTIRRSEL << (ADC_num * 8 + ADCETRType * 4)));

    /* select which external line is connected*/
    tmpregister |= ADCTrigRemap << (ADC_num * 8 + ADCETRType * 4);

    AFIO->ADCRMP_CFG = tmpregister;
}

/**
*\*\name   AFIO_ConfigADCSWPA0_C.
*\*\fun    Config ADC PA0_C channel.
*\*\param  ADCsw
*\*\           - ADC_SW_PA0_C_ADC2_INP0
*\*\           - ADC_SW_PA0_C_ADC2_INP1
*\*\           - ADC_SW_PA0_C_ADC1_INP0
*\*\           - ADC_SW_PA0_C_ADC1_INP1
*\*\           - ADC_SW_PA0_C_CLOSE
*\*\return none
**/
void AFIO_ConfigADCSWPA0_C(uint32_t ADCsw)
{
    uint32_t tempReg;

    tempReg  = AFIO->ADCSW_CFG;
    tempReg &= ~ADC_SW_PA0_C_MSK;
    tempReg |= ADCsw;

    AFIO->ADCSW_CFG  = tempReg;
}

/**
*\*\name   AFIO_ConfigADCSWPC2_C.
*\*\fun    Config ADC PC2_C channel
*\*\param  ADCsw
*\*\           - ADC_SW_PC2_C_ADC2_INP0
*\*\           - ADC_SW_PC2_C_ADC2_INP1
*\*\           - ADC_SW_PC2_C_ADC3_INP0
*\*\           - ADC_SW_PC2_C_ADC3_INP1
*\*\           - ADC_SW_PC2_C_CLOSE
*\*\return none
**/
void AFIO_ConfigADCSWPC2_C(uint32_t ADCsw)
{
    uint32_t tempReg;

    tempReg  = AFIO->ADCSW_CFG;
    tempReg &= ~ADC_SW_PC2_C_MSK;
    tempReg |= ADCsw;

    AFIO->ADCSW_CFG  = tempReg;
}

/**
*\*\name   AFIO_ConfigADCSWPC3_C.
*\*\fun    Config ADC PC3_C channel
*\*\param  ADCsw
*\*\           - ADC_SW_PC3_C_ADC2_INP1
*\*\           - ADC_SW_PC3_C_ADC3_INP2
*\*\           - ADC_SW_PC3_C_CLOSE
*\*\return none
**/
void AFIO_ConfigADCSWPC3_C(uint32_t ADCsw)
{
    uint32_t tempReg;

    tempReg  = AFIO->ADCSW_CFG;
    tempReg &= ~ADC_SW_PC3_C_MSK;
    tempReg |= ADCsw;

    AFIO->ADCSW_CFG  = tempReg;
}

/**
*\*\name   AFIO_ConfigADCSWPA1_C.
*\*\fun    Config ADC PA1_C channel
*\*\param  ADCsw
*\*\           - ADC_SW_PA1_C_ADC2_INP1
*\*\           - ADC_SW_PA1_C_ADC1_INP1
*\*\           - ADC_SW_PA1_C_CLOSE
*\*\return none
**/
void AFIO_ConfigADCSWPA1_C(uint32_t ADCsw)
{
    uint32_t tempReg;

    tempReg  = AFIO->ADCSW_CFG;
    tempReg &= ~ADC_SW_PA1_C_MSK;
    tempReg |= ADCsw;

    AFIO->ADCSW_CFG  = tempReg;
}

/**
*\*\name   AFIO_ConfigADCSWPI15.
*\*\fun    Config ADC PI15 channel
*\*\param  ADCsw
*\*\           - ADC_SW_PI15_ADC2_INP17
*\*\           - ADC_SW_PI15_ADC3_INP17
*\*\           - ADC_SW_PI15_CLOSE
*\*\return none
**/
void AFIO_ConfigADCSWPI15(uint32_t ADCsw)
{
    uint32_t tempReg;

    tempReg  = AFIO->ADCSW_CFG;
    tempReg &= ~ADC_SW_PI15_MSK;
    tempReg |= ADCsw;

    AFIO->ADCSW_CFG  = tempReg;
}

/**
*\*\name   AFIO_ADCSWVBATEnable.
*\*\fun    Enable or disable ADC VBAT channel
*\*\param   Cmd :
*\*\          - ENABLE
*\*\          - DISABLE
*\*\return none
**/
void AFIO_ADCSWVBATEnable(FunctionalState Cmd)
{
    uint32_t tempReg;

    tempReg  = AFIO->ADCSW_CFG;

    if (Cmd != DISABLE)
    {
        tempReg |= ADC_SW_VBAT_ADC3_INP17;
    }
    else
    {
        tempReg &= ~ADC_SW_VBAT_ADC3_INP17;
    }

    AFIO->ADCSW_CFG  = tempReg;
}

/**
*\*\name   AFIO_ADCSWPJ0Enable.
*\*\fun    Enable or disable ADC PJ0 channel
*\*\param   Cmd :
*\*\          - ENABLE
*\*\          - DISABLE
*\*\return none
**/
void AFIO_ADCSWPJ0Enable(FunctionalState Cmd)
{
    uint32_t tempReg;

    tempReg  = AFIO->ADCSW_CFG;

    if (Cmd != DISABLE)
    {
        tempReg |= ADC_SW_PJ0_ADC2_INP16;
    }
    else
    {
        tempReg &= ~ADC_SW_PJ0_ADC2_INP16;
    }

    AFIO->ADCSW_CFG  = tempReg;
}

/**
*\*\name   AFIO_ADCSWPJ3Enable.
*\*\fun    Enable or disable ADC PJ3 channel
*\*\param   Cmd :
*\*\          - ENABLE
*\*\          - DISABLE
*\*\return none
**/
void AFIO_ADCSWPJ3Enable(FunctionalState Cmd)
{
    uint32_t tempReg;

    tempReg  = AFIO->ADCSW_CFG;

    if (Cmd != DISABLE)
    {
        tempReg |= ADC_SW_PJ3_ADC3_INP18;
    }
    else
    {
        tempReg &= ~ADC_SW_PJ3_ADC3_INP18;
    }

    AFIO->ADCSW_CFG  = tempReg;
}

/**
*\*\name   AFIO_ADCSWTEMPEnable.
*\*\fun    Enable or disable ADC TEMP channel
*\*\param   Cmd :
*\*\          - ENABLE
*\*\          - DISABLE
*\*\return none
**/
void AFIO_ADCSWTEMPEnable(FunctionalState Cmd)
{
    uint32_t tempReg;

    tempReg  = AFIO->ADCSW_CFG;

    if (Cmd != DISABLE)
    {
        tempReg |= ADC_SW_TEMP_ADC3_INP18;
    }
    else
    {
        tempReg &= ~ADC_SW_TEMP_ADC3_INP18;
    }

    AFIO->ADCSW_CFG  = tempReg;
}

/**
*\*\name   AFIO_ADCSWPJ4Enable.
*\*\fun    Enable or disable ADC PJ4 channel
*\*\param   Cmd :
*\*\          - ENABLE
*\*\          - DISABLE
*\*\return none
**/
void AFIO_ADCSWPJ4Enable(FunctionalState Cmd)
{
    uint32_t tempReg;

    tempReg  = AFIO->ADCSW_CFG;

    if (Cmd != DISABLE)
    {
        tempReg |= ADC_SW_PJ4_ADC3_INP19;
    }
    else
    {
        tempReg &= ~ADC_SW_PJ4_ADC3_INP19;
    }

    AFIO->ADCSW_CFG  = tempReg;
}

/**
*\*\name   AFIO_ADCSWPJ5Enable.
*\*\fun    Enable or disable ADC PJ5 channel
*\*\param   Cmd :
*\*\          - ENABLE
*\*\          - DISABLE
*\*\return none
**/
void AFIO_ADCSWPJ5Enable(FunctionalState Cmd)
{
    uint32_t tempReg;

    tempReg  = AFIO->ADCSW_CFG;

    if (Cmd != DISABLE)
    {
        tempReg |= ADC_SW_PJ5_ADC2_INP16;
    }
    else
    {
        tempReg &= ~ADC_SW_PJ5_ADC2_INP16;
    }

    AFIO->ADCSW_CFG  = tempReg;
}

/**
*\*\name   AFIO_ADCSWPJ6Enable.
*\*\fun    Enable or disable ADC PJ6 channel
*\*\param   Cmd :
*\*\          - ENABLE
*\*\          - DISABLE
*\*\return none
**/
void AFIO_ADCSWPJ6Enable(FunctionalState Cmd)
{
    uint32_t tempReg;

    tempReg  = AFIO->ADCSW_CFG;

    if (Cmd != DISABLE)
    {
        tempReg |= ADC_SW_PJ6_ADC3_INP18;
    }
    else
    {
        tempReg &= ~ADC_SW_PJ6_ADC3_INP18;
    }

    AFIO->ADCSW_CFG  = tempReg;
}

/**
*\*\name   AFIO_ADCSWPJ7Enable.
*\*\fun    Enable or disable ADC PJ7 channel
*\*\param   Cmd :
*\*\          - ENABLE
*\*\          - DISABLE
*\*\return none
**/
void AFIO_ADCSWPJ7Enable(FunctionalState Cmd)
{
    uint32_t tempReg;

    tempReg  = AFIO->ADCSW_CFG;

    if (Cmd != DISABLE)
    {
        tempReg |= ADC_SW_PJ7_ADC3_INP19;
    }
    else
    {
        tempReg &= ~ADC_SW_PJ7_ADC3_INP19;
    }

    AFIO->ADCSW_CFG  = tempReg;
}

/**
*\*\name   AFIO_ADCSWVREFEnable.
*\*\fun    Enable or disable ADC VREF channel
*\*\param   Cmd :
*\*\          - ENABLE
*\*\          - DISABLE
*\*\return none
**/
void AFIO_ADCSWVREFEnable(FunctionalState Cmd)
{
    uint32_t tempReg;

    tempReg  = AFIO->ADCSW_CFG;

    if (Cmd != DISABLE)
    {
        tempReg |= ADC_SW_VREF_ADC3_INP19;
    }
    else
    {
        tempReg &= ~ADC_SW_VREF_ADC3_INP19;
    }

    AFIO->ADCSW_CFG  = tempReg;
}

/**
*\*\name   AFIO_ConfigADCSWDAC246OUT.
*\*\fun    Config ADC DAC2/4/6_OUT channel
*\*\param  ADCsw
*\*\           - ADC_SW_DAC2_OUT_ADC2_INP17
*\*\           - ADC_SW_DAC4_OUT_ADC2_INP17
*\*\           - ADC_SW_DAC6_OUT_ADC2_INP17
*\*\           - ADC_SW_DAC246_OUT_ADC2_DISABLE
*\*\return none
**/
void AFIO_ConfigADCSWDAC246OUT(uint32_t ADCsw)
{
    uint32_t tempReg;

    tempReg  = AFIO->ADCSW_CFG;
    tempReg &= ~ADC_SW_DAC246_OUT_MSK;
    tempReg |= ADCsw;

    AFIO->ADCSW_CFG  = tempReg;
}

/**
*\*\name   AFIO_ConfigADCSWDAC135OUT.
*\*\fun    Config ADC DAC1/3/5_OUT channel
*\*\param  ADCsw
*\*\           - ADC_SW_DAC1_OUT_ADC2_INP16
*\*\           - ADC_SW_DAC3_OUT_ADC2_INP16
*\*\           - ADC_SW_DAC5_OUT_ADC2_INP16
*\*\           - ADC_SW_DAC135_OUT_ADC2_DISABLE
*\*\return none
**/
void AFIO_ConfigADCSWDAC135OUT(uint32_t ADCsw)
{
    uint32_t tempReg;

    tempReg  = AFIO->ADCSW_CFG;
    tempReg &= ~ADC_SW_DAC135_OUT_MSK;
    tempReg |= ADCsw;

    AFIO->ADCSW_CFG  = tempReg;
}

/**
 *\*\name   AFIO_ConfigIOFilter.
 *\*\fun    Configure IO filter cycle which is counted in AHB clock.
 *\*\param  Filter_Cycle :
 *\*\        - 0~127
 *\*\return none
 */
void AFIO_ConfigIOFilter(uint8_t Filter_Cycle)
{
    uint32_t tempReg;

    tempReg  = AFIO->FILTER_CFG;
    tempReg &= ~AFIO_FILTER_CFG_IOFLTCFG;
    tempReg |= Filter_Cycle;
    AFIO->FILTER_CFG  = tempReg;
}

/**
 *\*\name   AFIO_ConfigPinFilter.
 *\*\fun    Enable or disable the analog filter function for GPIOx pin.
 *\*\param   GPIOx :
 *\*\          - GPIOA
 *\*\          - GPIOB
 *\*\          - GPIOC
 *\*\          - GPIOD
 *\*\          - GPIOE
 *\*\          - GPIOF
 *\*\          - GPIOG
 *\*\          - GPIOH
 *\*\          - GPIOI
 *\*\          - GPIOJ
 *\*\          - GPIOK
 *\*\param   Pin :
 *\*\          - GPIO_Pin_0
 *\*\          - GPIO_Pin_1
 *\*\          - GPIO_Pin_2
 *\*\          - GPIO_Pin_3
 *\*\          - GPIO_Pin_4
 *\*\          - GPIO_Pin_5
 *\*\          - GPIO_Pin_6
 *\*\          - GPIO_Pin_7
 *\*\          - GPIO_Pin_8
 *\*\          - GPIO_Pin_9
 *\*\          - GPIO_Pin_10
 *\*\          - GPIO_Pin_11
 *\*\          - GPIO_Pin_12
 *\*\          - GPIO_Pin_13
 *\*\          - GPIO_Pin_14
 *\*\          - GPIO_Pin_15
 *\*\          - GPIO_Pin_ALL
 *\*\param   cmd :
 *\*\          - DISABLE
 *\*\          - ENABLE
 *\*\return none
 */
void AFIO_ConfigPinAnFilter(GPIO_Module* GPIOx, uint32_t Pin, FunctionalState cmd)
{
    uint32_t tempReg;
    uint32_t RegNum;
    uint32_t BitMask;
    uint32_t GPIO_Index;

    GPIO_Index = (uint32_t)GPIOx;
    GPIO_Index = GPIO_GET_INDEX(GPIO_Index);

    RegNum = GPIO_Index / 2UL;

    if(GPIO_Index == 8 || GPIO_Index == 9) //GPIOI, GPIOJ
    {
        BitMask = Pin << (16UL * ((GPIO_Index + 1) & 0x1UL));
    }
    else
    {
        BitMask = Pin << (16UL * (GPIO_Index & 0x1UL));
    }

    tempReg = AFIO->EFT_CFG[RegNum];

    if(cmd != DISABLE)
    {
        tempReg |= BitMask;
    }
    else
    {
        tempReg &= ~(BitMask);
    }

    AFIO->EFT_CFG[RegNum] = tempReg;
}
/**
*\*\name   AFIO_ConfigDigitalPinFilter.
*\*\fun    Enable or disable the digital filter function for GPIOx pin.
*\*\param   GPIOx :
*\*\          - GPIOA
*\*\          - GPIOB
*\*\          - GPIOC
*\*\          - GPIOD
*\*\          - GPIOE
*\*\          - GPIOF
*\*\          - GPIOG
*\*\          - GPIOH
*\*\          - GPIOI
*\*\          - GPIOJ
*\*\          - GPIOK
*\*\param  Pin :
*\*\          - GPIO_Pin_0
*\*\          - GPIO_Pin_1
*\*\          - GPIO_Pin_2
*\*\          - GPIO_Pin_3
*\*\          - GPIO_Pin_4
*\*\          - GPIO_Pin_5
*\*\          - GPIO_Pin_6
*\*\          - GPIO_Pin_7
*\*\          - GPIO_Pin_8
*\*\          - GPIO_Pin_9
*\*\          - GPIO_Pin_10
*\*\          - GPIO_Pin_11
*\*\          - GPIO_Pin_12
*\*\          - GPIO_Pin_13
*\*\          - GPIO_Pin_14
*\*\          - GPIO_Pin_15
*\*\          - GPIO_Pin_ALL
*\*\param  cmd :
*\*\          - DISABLE
*\*\          - ENABLE
*\*\return none
**/
void AFIO_ConfigPinFilter(GPIO_Module* GPIOx, uint32_t Pin, FunctionalState cmd)
{
    uint32_t tempReg;
    uint32_t RegNum;
    uint32_t BitMask;
    uint32_t GPIO_Index;

    GPIO_Index = (uint32_t)GPIOx;
    GPIO_Index = GPIO_GET_INDEX(GPIO_Index);

    RegNum = GPIO_Index / 2UL;

    if(GPIO_Index == 8 || GPIO_Index == 9) //GPIOI, GPIOJ
    {
        BitMask = Pin << (16UL * ((GPIO_Index + 1) & 0x1UL));
    }
    else
    {
        BitMask = Pin << (16UL * (GPIO_Index & 0x1UL));
    }

    tempReg = AFIO->DIGEFT_CFG[RegNum];

    if(cmd != DISABLE)
    {
        tempReg |= BitMask;
    }
    else
    {
        tempReg &= ~(BitMask);
    }

    AFIO->DIGEFT_CFG[RegNum] = tempReg;
}

/**
 *\*\name   AFIO_ConfigHSMODE.
 *\*\fun    Enable or disable HS_EN pad interface connection for SDRAM PAD model.
 *\*\param   GPIOx :
 *\*\          - GPIOA
 *\*\          - GPIOB
 *\*\          - GPIOC
 *\*\          - GPIOD
 *\*\          - GPIOE
 *\*\          - GPIOF
 *\*\          - GPIOG
 *\*\          - GPIOH
 *\*\          - GPIOI
 *\*\param   Pin :
 *\*\          - GPIO_Pin_0
 *\*\          - GPIO_Pin_1
 *\*\          - GPIO_Pin_2
 *\*\          - GPIO_Pin_3
 *\*\          - GPIO_Pin_4
 *\*\          - GPIO_Pin_5
 *\*\          - GPIO_Pin_6
 *\*\          - GPIO_Pin_7
 *\*\          - GPIO_Pin_8
 *\*\          - GPIO_Pin_9
 *\*\          - GPIO_Pin_10
 *\*\          - GPIO_Pin_11
 *\*\          - GPIO_Pin_12
 *\*\          - GPIO_Pin_13
 *\*\          - GPIO_Pin_14
 *\*\          - GPIO_Pin_15
 *\*\          - GPIO_Pin_ALL
 *\*\param   cmd :
 *\*\          - DISABLE
 *\*\          - ENABLE
 *\*\note   Most of pins support ,but some pins don't support.
 *\*\return none
 */
void AFIO_ConfigHSMODE(GPIO_Module* GPIOx, uint32_t Pin, FunctionalState cmd)
{
    uint32_t tempReg;
    uint32_t RegNum;
    uint32_t BitMask;
    uint32_t GPIO_Index;

    GPIO_Index = (uint32_t)GPIOx;
    GPIO_Index = GPIO_GET_INDEX(GPIO_Index);

    RegNum = GPIO_Index / 2UL;
    BitMask = Pin << (16UL * ((GPIO_Index + 1) & 0x1UL));
    tempReg = AFIO->HSMODE_CFG[RegNum];

    if(cmd != DISABLE)
    {
        tempReg |= BitMask;
    }
    else
    {
        tempReg &= ~(BitMask);
    }

    AFIO->HSMODE_CFG[RegNum] = tempReg;
}

/**
*\*\name   AFIO_ConfigXSPIDecNonce.
*\*\fun    Set the XSPI DEC NONCE counter value.
*\*\param  nonce_num
*\*\           - 0
*\*\           - 1
*\*\           - 2
*\*\param  data: 0x00000000~ 0xFFFFFFFF
*\*\return none
**/
void AFIO_ConfigXSPIDecNonce(uint8_t nonce_num, u32 data)
{
    if(nonce_num == 0x00)
    {
        AFIO->XSPI1_NONCE0 = data;
    }
    else if(nonce_num == 0x01)
    {
        AFIO->XSPI1_NONCE1 = data;
    }
    else if(nonce_num == 0x02)
    {
        AFIO->XSPI1_NONCE2 = data;
    }
}

/**
*\*\name   AFIO_ConfigSDRAMVREFRemap.
*\*\fun    Config SDRAM VREF counter value.
*\*\param  pin
*\*\          - AFIO_SDRAM_PIN_PA4
*\*\          - AFIO_SDRAM_PIN_PA5
*\*\          - AFIO_SDRAM_PIN_PA7
*\*\          - AFIO_SDRAM_PIN_PB5
*\*\          - AFIO_SDRAM_PIN_PB6
*\*\          - ...
*\*\          - AFIO_SDRAM_PIN_PI7
*\*\          - AFIO_SDRAM_PIN_PI9
*\*\          - AFIO_SDRAM_PIN_PI10
*\*\param  cmd :
*\*\          - DISABLE
*\*\          - ENABLE
*\*\return none
**/
void AFIO_ConfigSDRAMVREFRemap(AFIO_SDRAM_PIN pin, FunctionalState cmd)
{
    uint8_t temp;
    uint32_t temp_reg;

    temp = pin / 32;
    temp_reg = AFIO->SDRAM_VREF_EN[temp];

    if(cmd != DISABLE)
    {
        temp_reg |= (uint32_t)(0x00000001) << (pin % 32);
    }
    else
    {
        temp_reg &= ~(uint32_t)(0x00000001) << (pin % 32);
    }

    AFIO->SDRAM_VREF_EN[temp] = temp_reg;
}

/**
*\*\name   AFIO_ConfigSDRAMVREFData.
*\*\fun    Config SDRAM VREF counter value.
*\*\param  reg_index:
*\*\          - 0
*\*\          - 1
*\*\          - 2
*\*\param  data: when reg_index = 0 or 1, data range 0~0xFFFFFFFF, when reg_index = 2, data range 0~0x1FF
*\*\return none
**/
void AFIO_ConfigSDRAMVREFData(uint8_t reg_index, uint32_t data)
{
    AFIO->SDRAM_VREF_EN[reg_index] = data;
}


/**
*\*\name   AFIO_ConfigSDRAMDSNRemap.
*\*\fun    Config SDRAM DSN counter value.
*\*\param  pin
*\*\          - AFIO_SDRAM_PIN_PA4
*\*\          - AFIO_SDRAM_PIN_PA5
*\*\          - AFIO_SDRAM_PIN_PA7
*\*\          - AFIO_SDRAM_PIN_PB5
*\*\          - AFIO_SDRAM_PIN_PB6
*\*\          - ...
*\*\          - AFIO_SDRAM_PIN_PI7
*\*\          - AFIO_SDRAM_PIN_PI9
*\*\          - AFIO_SDRAM_PIN_PI10
*\*\param  cmd :
*\*\          - DISABLE
*\*\          - ENABLE
*\*\return none
**/
void AFIO_ConfigSDRAMDSNRemap(AFIO_SDRAM_PIN pin, FunctionalState cmd)
{
    uint8_t temp;
    uint32_t temp_reg;

    temp = pin / 32;
    temp_reg = AFIO->SDRAMDSN_CFG[temp];

    if(cmd != DISABLE)
    {
        temp_reg |= (uint32_t)(0x00000001) << (pin % 32);
    }
    else
    {
        temp_reg &= ~(uint32_t)(0x00000001) << (pin % 32);
    }

    AFIO->SDRAMDSN_CFG[temp] = temp_reg;
}

/**
*\*\name   AFIO_ConfigSDRAMDSNData.
*\*\fun    Config SDRAM DSN counter value.
*\*\param  reg_index:
*\*\          - 0
*\*\          - 1
*\*\          - 2
*\*\param  data: when reg_index = 0 or 1, data range 0~0xFFFFFFFF, when reg_index = 2, data range 0~0x1FF
*\*\return none
**/
void AFIO_ConfigSDRAMDSNData(uint8_t reg_index, uint32_t data)
{
    AFIO->SDRAMDSN_CFG[reg_index] = data;
}

/**
*\*\name   AFIO_ConfigSDRAMDSPRemap.
*\*\fun    Config SDRAM DSP counter value.
*\*\param  pin
*\*\          - AFIO_SDRAM_PIN_PA4
*\*\          - AFIO_SDRAM_PIN_PA5
*\*\          - AFIO_SDRAM_PIN_PA7
*\*\          - AFIO_SDRAM_PIN_PB5
*\*\          - AFIO_SDRAM_PIN_PB6
*\*\          - ...
*\*\          - AFIO_SDRAM_PIN_PI7
*\*\          - AFIO_SDRAM_PIN_PI9
*\*\          - AFIO_SDRAM_PIN_PI10
*\*\param  cmd :
*\*\          - DISABLE
*\*\          - ENABLE
*\*\return none
**/
void AFIO_ConfigSDRAMDSPRemap(AFIO_SDRAM_PIN pin, FunctionalState cmd)
{
    uint8_t temp;
    uint32_t temp_reg;

    temp = pin / 32;
    temp_reg = AFIO->SDRAMDSP_CFG[temp];

    if(cmd != DISABLE)
    {
        temp_reg |= (uint32_t)(0x00000001) << (pin % 32);
    }
    else
    {
        temp_reg &= ~(uint32_t)(0x00000001) << (pin % 32);
    }

    AFIO->SDRAMDSP_CFG[temp] = temp_reg;
}

/**
*\*\name   AFIO_ConfigSDRAMDSPData.
*\*\fun    Config SDRAM DSP counter value.
*\*\param  reg_index:
*\*\          - 0
*\*\          - 1
*\*\          - 2
*\*\param  data: when reg_index = 0 or 1, data range 0~0xFFFFFFFF, when reg_index = 2, data range 0~0x1FF
*\*\return none
**/
void AFIO_ConfigSDRAMDSPData(uint8_t reg_index, uint32_t data)
{
    AFIO->SDRAMDSP_CFG[reg_index] = data;
}

