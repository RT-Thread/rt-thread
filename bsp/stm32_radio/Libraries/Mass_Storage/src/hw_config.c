/******************** (C) COPYRIGHT 2009 STMicroelectronics ********************
* File Name          : hw_config.c
* Author             : MCD Application Team
* Version            : V3.0.1
* Date               : 04/27/2009
* Description        : Hardware Configuration & Setup
********************************************************************************
* THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
* WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE TIME.
* AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY DIRECT,
* INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING FROM THE
* CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE CODING
* INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
*******************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include "hw_config.h"
#include "platform_config.h"
#include "mass_mal.h"
#include "usb_desc.h"
#include "usb_pwr.h"

void Set_System(void)
{
    /* Enable and GPIOD clock */
    USB_Disconnect_Config();

    /* MAL configuration */
    MAL_Config();
}

/*******************************************************************************
* Function Name  : Set_USBClock
* Description    : Configures USB Clock input (48MHz)
* Input          : None.
* Return         : None.
*******************************************************************************/
void Set_USBClock(void)
{
    /* USBCLK = PLLCLK */
    RCC_USBCLKConfig(RCC_USBCLKSource_PLLCLK_1Div5);

    /* Enable USB clock */
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_USB, ENABLE);
}

/*******************************************************************************
* Function Name  : Enter_LowPowerMode
* Description    : Power-off system clocks and power while entering suspend mode
* Input          : None.
* Return         : None.
*******************************************************************************/
void Enter_LowPowerMode(void)
{
    /* Set the device state to suspend */
    bDeviceState = SUSPENDED;
}

/*******************************************************************************
* Function Name  : Leave_LowPowerMode
* Description    : Restores system clocks and power while exiting suspend mode
* Input          : None.
* Return         : None.
*******************************************************************************/
void Leave_LowPowerMode(void)
{
    DEVICE_INFO *pInfo = &Device_Info;

    /* Set the device state to the correct state */
    if (pInfo->Current_Configuration != 0)
    {
        /* Device configured */
        bDeviceState = CONFIGURED;
    }
    else
    {
        bDeviceState = ATTACHED;
    }

}

/*******************************************************************************
* Function Name  : USB_Interrupts_Config
* Description    : Configures the USB interrupts
* Input          : None.
* Return         : None.
*******************************************************************************/
void USB_Interrupts_Config(void)
{
    NVIC_InitTypeDef NVIC_InitStructure;

    //NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);

    NVIC_InitStructure.NVIC_IRQChannel = USB_LP_CAN1_RX0_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);

    NVIC_InitStructure.NVIC_IRQChannel = USB_HP_CAN1_TX_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);

#if 0
    NVIC_InitStructure.NVIC_IRQChannel = SDIO_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
#endif /* USE_STM3210E_EVAL */

}

/*******************************************************************************
* Function Name  : Led_Config
* Description    : configure the Read/Write LEDs.
* Input          : None.
* Output         : None.
* Return         : None.
*******************************************************************************/
void Led_Config(void)
{
}

/*******************************************************************************
* Function Name  : Led_RW_ON
* Description    : Turn ON the Read/Write LEDs.
* Input          : None.
* Output         : None.
* Return         : None.
*******************************************************************************/
void Led_RW_ON(void)
{
#if (USB_USE_LED == 1)
    GPIO_SetBits(USB_LED_PORT, USB_LED_PIN);
#endif
}

/*******************************************************************************
* Function Name  : Led_RW_OFF
* Description    : Turn off the Read/Write LEDs.
* Input          : None.
* Output         : None.
* Return         : None.
*******************************************************************************/
void Led_RW_OFF(void)
{
#if (USB_USE_LED == 1)
    GPIO_ResetBits(USB_LED_PORT, USB_LED_PIN);
#endif
}
/*******************************************************************************
* Function Name  : USB_Configured_LED
* Description    : Turn ON the Read/Write LEDs.
* Input          : None.
* Output         : None.
* Return         : None.
*******************************************************************************/
void USB_Configured_LED(void)
{
    //GPIO_SetBits(USB_LED_PORT, GPIO_Pin_6);
}

/*******************************************************************************
* Function Name  : USB_NotConfigured_LED
* Description    : Turn off the Read/Write LEDs.
* Input          : None.
* Output         : None.
* Return         : None.
*******************************************************************************/
void USB_NotConfigured_LED(void)
{
    //GPIO_ResetBits(USB_LED_PORT, GPIO_Pin_6);
}

/*******************************************************************************
* Function Name  : USB_Cable_Config
* Description    : Software Connection/Disconnection of USB Cable.
* Input          : None.
* Return         : Status
*******************************************************************************/
void USB_Cable_Config (FunctionalState NewState)
{
    if (NewState != DISABLE)
    {
        GPIO_SetBits(USB_DISCONNECT, USB_DISCONNECT_PIN);
    }
    else
    {
        GPIO_ResetBits(USB_DISCONNECT, USB_DISCONNECT_PIN);
    }
}

/*******************************************************************************
* Function Name  : Get_SerialNum.
* Description    : Create the serial number string descriptor.
* Input          : None.
* Output         : None.
* Return         : None.
*******************************************************************************/
void Get_SerialNum(void)
{
    uint32_t Device_Serial0, Device_Serial1, Device_Serial2;

    Device_Serial0 = *(__IO uint32_t*)(0x1FFFF7E8);
    Device_Serial1 = *(__IO uint32_t*)(0x1FFFF7EC);
    Device_Serial2 = *(__IO uint32_t*)(0x1FFFF7F0);

    if (Device_Serial0 != 0)
    {
        MASS_StringSerial[2] = (uint8_t)(Device_Serial0 & 0x000000FF);
        MASS_StringSerial[4] = (uint8_t)((Device_Serial0 & 0x0000FF00) >> 8);
        MASS_StringSerial[6] = (uint8_t)((Device_Serial0 & 0x00FF0000) >> 16);
        MASS_StringSerial[8] = (uint8_t)((Device_Serial0 & 0xFF000000) >> 24);

        MASS_StringSerial[10] = (uint8_t)(Device_Serial1 & 0x000000FF);
        MASS_StringSerial[12] = (uint8_t)((Device_Serial1 & 0x0000FF00) >> 8);
        MASS_StringSerial[14] = (uint8_t)((Device_Serial1 & 0x00FF0000) >> 16);
        MASS_StringSerial[16] = (uint8_t)((Device_Serial1 & 0xFF000000) >> 24);

        MASS_StringSerial[18] = (uint8_t)(Device_Serial2 & 0x000000FF);
        MASS_StringSerial[20] = (uint8_t)((Device_Serial2 & 0x0000FF00) >> 8);
        MASS_StringSerial[22] = (uint8_t)((Device_Serial2 & 0x00FF0000) >> 16);
        MASS_StringSerial[24] = (uint8_t)((Device_Serial2 & 0xFF000000) >> 24);
    }
}

/*******************************************************************************
* Function Name  : MAL_Config
* Description    : MAL_layer configuration
* Input          : None.
* Return         : None.
*******************************************************************************/
void MAL_Config(void)
{
    MAL_Init(0);
}

/*******************************************************************************
* Function Name  : USB_Disconnect_Config
* Description    : Disconnect pin configuration
* Input          : None.
* Return         : None.
*******************************************************************************/
void USB_Disconnect_Config(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIO_DISCONNECT, ENABLE);

    /* config USB cable pin */
    GPIO_InitStructure.GPIO_Pin   = USB_DISCONNECT_PIN;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_Out_PP;
    GPIO_Init(USB_DISCONNECT, &GPIO_InitStructure);
}

/******************* (C) COPYRIGHT 2009 STMicroelectronics *****END OF FILE****/
