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
 * @file n32h76x_78x_dmamux.c
 * @author Nations
 * @version v1.0.0
 *
 * @copyright Copyright (c) 2025, Nations Technologies Inc. All rights reserved.
 */#include "n32h76x_78x_dmamux.h"
#include "n32h76x_78x_rcc.h"

/**
*\*\name    DMAMUX_DeInit.
*\*\fun     Reset the DMAMUX registers.
*\*\param   DMAMUXx :
*\*\          - DMAMUX1_ID
*\*\          - DMAMUX2_ID
*\*\return  none
**/
void DMAMUX_DeInit(DMAMUX_ID DMAMUXx)
{
    if (DMAMUXx == DMAMUX1_ID)
    {
        RCC_EnableAHB1PeriphReset1(RCC_AHB1_PERIPHRST_DMAMUX1);
    }
    else if (DMAMUXx == DMAMUX2_ID)
    {
        RCC_EnableAXIPeriphReset1(RCC_AXI_PERIPHRST_DMAMUX2);
    }
    else
    {
        /*no process*/
    }
}

/**
*\*\name    DMAMUX_SetRequestID.
*\*\fun     Set DMAMUX request ID for DMAMUX Channel x.
*\*\param   DMAMUXx (The input parameters must be the following values):
*\*\          - DMAMUX1_ID
*\*\          - DMAMUX2_ID
*\*\param   Channel (The input parameters must be the following values):
*\*\          - DMAMUX_CHANNEL_0
*\*\          - DMAMUX_CHANNEL_1
*\*\          - DMAMUX_CHANNEL_2
*\*\          - DMAMUX_CHANNEL_3
*\*\          - DMAMUX_CHANNEL_4
*\*\          - DMAMUX_CHANNEL_5
*\*\          - DMAMUX_CHANNEL_6
*\*\          - DMAMUX_CHANNEL_7
*\*\          - DMAMUX_CHANNEL_8
*\*\          - DMAMUX_CHANNEL_9
*\*\          - DMAMUX_CHANNEL_10
*\*\          - DMAMUX_CHANNEL_11
*\*\          - DMAMUX_CHANNEL_12
*\*\          - DMAMUX_CHANNEL_13
*\*\          - DMAMUX_CHANNEL_14
*\*\          - DMAMUX_CHANNEL_15
*\*\          - DMAMUX_CHANNEL_16
*\*\          - DMAMUX_CHANNEL_17
*\*\          - DMAMUX_CHANNEL_18
*\*\          - DMAMUX_CHANNEL_19
*\*\          - DMAMUX_CHANNEL_20
*\*\          - DMAMUX_CHANNEL_21
*\*\          - DMAMUX_CHANNEL_22
*\*\          - DMAMUX_CHANNEL_23
*\*\param   Request (The input parameters must be the following values):       
*\*\          - DMAMUX1_REQUEST_GENERATOR0       
*\*\          - DMAMUX1_REQUEST_GENERATOR1       
*\*\          - DMAMUX1_REQUEST_GENERATOR2       
*\*\          - DMAMUX1_REQUEST_GENERATOR3       
*\*\          - DMAMUX1_REQUEST_GENERATOR4       
*\*\          - DMAMUX1_REQUEST_GENERATOR5       
*\*\          - DMAMUX1_REQUEST_GENERATOR6       
*\*\          - DMAMUX1_REQUEST_GENERATOR7       
*\*\          - DMAMUX1_REQUEST_ADC1             
*\*\          - DMAMUX1_REQUEST_ADC2             
*\*\          - DMAMUX1_REQUEST_ADC3             
*\*\          - DMAMUX1_REQUEST_SHRTIM1_DMA0      
*\*\          - DMAMUX1_REQUEST_SHRTIM1_DMA1      
*\*\          - DMAMUX1_REQUEST_SHRTIM1_DMA2      
*\*\          - DMAMUX1_REQUEST_SHRTIM1_DMA3      
*\*\          - DMAMUX1_REQUEST_SHRTIM1_DMA4      
*\*\          - DMAMUX1_REQUEST_SHRTIM1_DMA5      
*\*\          - DMAMUX1_REQUEST_SHRTIM1_DMA6      
*\*\          - DMAMUX1_REQUEST_SHRTIM2_DMA0      
*\*\          - DMAMUX1_REQUEST_SHRTIM2_DMA1      
*\*\          - DMAMUX1_REQUEST_SHRTIM2_DMA2      
*\*\          - DMAMUX1_REQUEST_SHRTIM2_DMA3      
*\*\          - DMAMUX1_REQUEST_SHRTIM2_DMA4      
*\*\          - DMAMUX1_REQUEST_SHRTIM2_DMA5      
*\*\          - DMAMUX1_REQUEST_SHRTIM2_DMA6      
*\*\          - DMAMUX1_REQUEST_ATIM1_UP           
*\*\          - DMAMUX1_REQUEST_ATIM1_CH1          
*\*\          - DMAMUX1_REQUEST_ATIM1_CH2          
*\*\          - DMAMUX1_REQUEST_ATIM1_CH3          
*\*\          - DMAMUX1_REQUEST_ATIM1_CH4          
*\*\          - DMAMUX1_REQUEST_ATIM1_TRIG         
*\*\          - DMAMUX1_REQUEST_ATIM1_COM          
*\*\          - DMAMUX1_REQUEST_ATIM2_UP           
*\*\          - DMAMUX1_REQUEST_ATIM2_CH1          
*\*\          - DMAMUX1_REQUEST_ATIM2_CH2          
*\*\          - DMAMUX1_REQUEST_ATIM2_CH3          
*\*\          - DMAMUX1_REQUEST_ATIM2_CH4          
*\*\          - DMAMUX1_REQUEST_ATIM2_TRIG         
*\*\          - DMAMUX1_REQUEST_ATIM2_COM           
*\*\          - DMAMUX1_REQUEST_ATIM3_UP            
*\*\          - DMAMUX1_REQUEST_ATIM3_CH1           
*\*\          - DMAMUX1_REQUEST_ATIM3_CH2           
*\*\          - DMAMUX1_REQUEST_ATIM3_CH3           
*\*\          - DMAMUX1_REQUEST_ATIM3_CH4           
*\*\          - DMAMUX1_REQUEST_ATIM3_TRIG          
*\*\          - DMAMUX1_REQUEST_ATIM3_COM           
*\*\          - DMAMUX1_REQUEST_ATIM4_UP            
*\*\          - DMAMUX1_REQUEST_ATIM4_CH1           
*\*\          - DMAMUX1_REQUEST_ATIM4_CH2           
*\*\          - DMAMUX1_REQUEST_ATIM4_CH3           
*\*\          - DMAMUX1_REQUEST_ATIM4_CH4           
*\*\          - DMAMUX1_REQUEST_ATIM4_TRIG          
*\*\          - DMAMUX1_REQUEST_ATIM4_COM           
*\*\          - DMAMUX1_REQUEST_GTIMA1_CH1       
*\*\          - DMAMUX1_REQUEST_GTIMA1_CH2       
*\*\          - DMAMUX1_REQUEST_GTIMA1_CH3       
*\*\          - DMAMUX1_REQUEST_GTIMA1_CH4       
*\*\          - DMAMUX1_REQUEST_GTIMA1_TRIG      
*\*\          - DMAMUX1_REQUEST_GTIMA1_UP        
*\*\          - DMAMUX1_REQUEST_GTIMA2_CH1       
*\*\          - DMAMUX1_REQUEST_GTIMA2_CH2       
*\*\          - DMAMUX1_REQUEST_GTIMA2_CH3       
*\*\          - DMAMUX1_REQUEST_GTIMA2_CH4       
*\*\          - DMAMUX1_REQUEST_GTIMA2_TRIG      
*\*\          - DMAMUX1_REQUEST_GTIMA2_UP        
*\*\          - DMAMUX1_REQUEST_GTIMA3_CH1       
*\*\          - DMAMUX1_REQUEST_GTIMA3_CH2       
*\*\          - DMAMUX1_REQUEST_GTIMA3_CH3       
*\*\          - DMAMUX1_REQUEST_GTIMA3_CH4       
*\*\          - DMAMUX1_REQUEST_GTIMA3_TRIG      
*\*\          - DMAMUX1_REQUEST_GTIMA3_UP        
*\*\          - DMAMUX1_REQUEST_GTIMA4_CH1       
*\*\          - DMAMUX1_REQUEST_GTIMA4_CH2       
*\*\          - DMAMUX1_REQUEST_GTIMA4_CH3       
*\*\          - DMAMUX1_REQUEST_GTIMA4_CH4       
*\*\          - DMAMUX1_REQUEST_GTIMA4_TRIG      
*\*\          - DMAMUX1_REQUEST_GTIMA4_UP        
*\*\          - DMAMUX1_REQUEST_GTIMA5_CH1       
*\*\          - DMAMUX1_REQUEST_GTIMA5_CH2       
*\*\          - DMAMUX1_REQUEST_GTIMA5_CH3       
*\*\          - DMAMUX1_REQUEST_GTIMA5_CH4       
*\*\          - DMAMUX1_REQUEST_GTIMA5_TRIG      
*\*\          - DMAMUX1_REQUEST_GTIMA5_UP        
*\*\          - DMAMUX1_REQUEST_GTIMA6_CH1       
*\*\          - DMAMUX1_REQUEST_GTIMA6_CH2       
*\*\          - DMAMUX1_REQUEST_GTIMA6_CH3       
*\*\          - DMAMUX1_REQUEST_GTIMA6_CH4       
*\*\          - DMAMUX1_REQUEST_GTIMA6_TRIG      
*\*\          - DMAMUX1_REQUEST_GTIMA6_UP        
*\*\          - DMAMUX1_REQUEST_GTIMA7_CH1       
*\*\          - DMAMUX1_REQUEST_GTIMA7_CH2       
*\*\          - DMAMUX1_REQUEST_GTIMA7_CH3       
*\*\          - DMAMUX1_REQUEST_GTIMA7_CH4       
*\*\          - DMAMUX1_REQUEST_GTIMA7_TRIG      
*\*\          - DMAMUX1_REQUEST_GTIMA7_UP        
*\*\          - DMAMUX1_REQUEST_GTIMB1_CH1       
*\*\          - DMAMUX1_REQUEST_GTIMB1_CH2       
*\*\          - DMAMUX1_REQUEST_GTIMB1_CH3       
*\*\          - DMAMUX1_REQUEST_GTIMB1_CH4       
*\*\          - DMAMUX1_REQUEST_GTIMB1_TRIG      
*\*\          - DMAMUX1_REQUEST_GTIMB1_UP        
*\*\          - DMAMUX1_REQUEST_GTIMB2_CH1       
*\*\          - DMAMUX1_REQUEST_GTIMB2_CH2       
*\*\          - DMAMUX1_REQUEST_GTIMB2_CH3       
*\*\          - DMAMUX1_REQUEST_GTIMB2_CH4       
*\*\          - DMAMUX1_REQUEST_GTIMB2_TRIG      
*\*\          - DMAMUX1_REQUEST_GTIMB2_UP        
*\*\          - DMAMUX1_REQUEST_GTIMB3_CH1       
*\*\          - DMAMUX1_REQUEST_GTIMB3_CH2       
*\*\          - DMAMUX1_REQUEST_GTIMB3_CH3       
*\*\          - DMAMUX1_REQUEST_GTIMB3_CH4       
*\*\          - DMAMUX1_REQUEST_GTIMB3_TRIG      
*\*\          - DMAMUX1_REQUEST_GTIMB3_UP        
*\*\          - DMAMUX1_REQUEST_I2C1_RX         
*\*\          - DMAMUX1_REQUEST_I2C1_TX   
*\*\          - DMAMUX1_REQUEST_I2C2_RX   
*\*\          - DMAMUX1_REQUEST_I2C2_TX   
*\*\          - DMAMUX1_REQUEST_I2C3_RX   
*\*\          - DMAMUX1_REQUEST_I2C3_TX   
*\*\          - DMAMUX1_REQUEST_I2C4_RX   
*\*\          - DMAMUX1_REQUEST_I2C4_TX   
*\*\          - DMAMUX1_REQUEST_I2C5_RX   
*\*\          - DMAMUX1_REQUEST_I2C5_TX   
*\*\          - DMAMUX1_REQUEST_I2C6_RX   
*\*\          - DMAMUX1_REQUEST_I2C6_TX   
*\*\          - DMAMUX1_REQUEST_I2C7_RX   
*\*\          - DMAMUX1_REQUEST_I2C7_TX   
*\*\          - DMAMUX1_REQUEST_I2C8_RX   
*\*\          - DMAMUX1_REQUEST_I2C8_TX   
*\*\          - DMAMUX1_REQUEST_I2C9_RX   
*\*\          - DMAMUX1_REQUEST_I2C9_TX   
*\*\          - DMAMUX1_REQUEST_I2C10_RX   
*\*\          - DMAMUX1_REQUEST_I2C10_TX   
*\*\          - DMAMUX1_REQUEST_USART1_RX   
*\*\          - DMAMUX1_REQUEST_USART1_TX   
*\*\          - DMAMUX1_REQUEST_USART2_RX   
*\*\          - DMAMUX1_REQUEST_USART2_TX   
*\*\          - DMAMUX1_REQUEST_USART3_RX   
*\*\          - DMAMUX1_REQUEST_USART3_TX   
*\*\          - DMAMUX1_REQUEST_USART4_RX   
*\*\          - DMAMUX1_REQUEST_USART4_TX        
*\*\          - DMAMUX1_REQUEST_USART5_RX        
*\*\          - DMAMUX1_REQUEST_USART5_TX        
*\*\          - DMAMUX1_REQUEST_USART6_RX        
*\*\          - DMAMUX1_REQUEST_USART6_TX        
*\*\          - DMAMUX1_REQUEST_USART7_RX        
*\*\          - DMAMUX1_REQUEST_USART7_TX        
*\*\          - DMAMUX1_REQUEST_USART8_RX        
*\*\          - DMAMUX1_REQUEST_USART8_TX        
*\*\          - DMAMUX1_REQUEST_UART9_RX         
*\*\          - DMAMUX1_REQUEST_UART9_TX         
*\*\          - DMAMUX1_REQUEST_UART10_RX         
*\*\          - DMAMUX1_REQUEST_UART10_TX         
*\*\          - DMAMUX1_REQUEST_UART11_RX         
*\*\          - DMAMUX1_REQUEST_UART11_TX         
*\*\          - DMAMUX1_REQUEST_UART12_RX         
*\*\          - DMAMUX1_REQUEST_UART12_TX         
*\*\          - DMAMUX1_REQUEST_UART13_RX         
*\*\          - DMAMUX1_REQUEST_UART13_TX         
*\*\          - DMAMUX1_REQUEST_UART14_RX         
*\*\          - DMAMUX1_REQUEST_UART14_TX         
*\*\          - DMAMUX1_REQUEST_UART15_RX         
*\*\          - DMAMUX1_REQUEST_UART15_TX         
*\*\          - DMAMUX1_REQUEST_SPI1_RX      
*\*\          - DMAMUX1_REQUEST_SPI1_TX      
*\*\          - DMAMUX1_REQUEST_SPI2_RX      
*\*\          - DMAMUX1_REQUEST_SPI2_TX      
*\*\          - DMAMUX1_REQUEST_SPI3_RX      
*\*\          - DMAMUX1_REQUEST_SPI3_TX      
*\*\          - DMAMUX1_REQUEST_SPI4_RX      
*\*\          - DMAMUX1_REQUEST_SPI4_TX      
*\*\          - DMAMUX1_REQUEST_SPI5_RX      
*\*\          - DMAMUX1_REQUEST_SPI5_TX      
*\*\          - DMAMUX1_REQUEST_SPI6_RX      
*\*\          - DMAMUX1_REQUEST_SPI6_TX      
*\*\          - DMAMUX1_REQUEST_SPI7_RX      
*\*\          - DMAMUX1_REQUEST_SPI7_TX      
*\*\          - DMAMUX1_REQUEST_I2S1_RX      
*\*\          - DMAMUX1_REQUEST_I2S1_TX      
*\*\          - DMAMUX1_REQUEST_I2S2_RX      
*\*\          - DMAMUX1_REQUEST_I2S2_TX      
*\*\          - DMAMUX1_REQUEST_I2S3_RX      
*\*\          - DMAMUX1_REQUEST_I2S3_TX      
*\*\          - DMAMUX1_REQUEST_I2S4_RX      
*\*\          - DMAMUX1_REQUEST_I2S4_TX      
*\*\          - DMAMUX1_REQUEST_LPUART1_RX   
*\*\          - DMAMUX1_REQUEST_LPUART1_TX     
*\*\          - DMAMUX1_REQUEST_LPUART2_RX     
*\*\          - DMAMUX1_REQUEST_LPUART2_TX     
*\*\          - DMAMUX1_REQUEST_DAC1           
*\*\          - DMAMUX1_REQUEST_DAC2             
*\*\          - DMAMUX1_REQUEST_DSMU_CH1       
*\*\          - DMAMUX1_REQUEST_DSMU_CH2       
*\*\          - DMAMUX1_REQUEST_DSMU_CH3       
*\*\          - DMAMUX1_REQUEST_DSMU_CH4       
*\*\          - DMAMUX1_REQUEST_CANFD1       
*\*\          - DMAMUX1_REQUEST_CANFD2       
*\*\          - DMAMUX1_REQUEST_CANFD3       
*\*\          - DMAMUX1_REQUEST_CANFD4       
*\*\          - DMAMUX1_REQUEST_CANFD5       
*\*\          - DMAMUX1_REQUEST_CANFD6       
*\*\          - DMAMUX1_REQUEST_CANFD7       
*\*\          - DMAMUX1_REQUEST_CANFD8       
*\*\          - DMAMUX1_REQUEST_CORDIC_READ   
*\*\          - DMAMUX1_REQUEST_CORDIC_WRITE  
*\*\          - DMAMUX1_REQUEST_FMAC_READ     
*\*\          - DMAMUX1_REQUEST_FMAC_WRITE    
*\*\          - DMAMUX1_REQUEST_BTIM1         
*\*\          - DMAMUX1_REQUEST_BTIM2         
*\*\          - DMAMUX1_REQUEST_BTIM3         
*\*\          - DMAMUX1_REQUEST_BTIM4         
*\*\          - DMAMUX1_REQUEST_GTIMB1_COM  
*\*\          - DMAMUX1_REQUEST_GTIMB2_COM  
*\*\          - DMAMUX1_REQUEST_GTIMB3_COM  
*\*\          - DMAMUX1_REQUEST_DAC3           
*\*\          - DMAMUX1_REQUEST_DAC4           
*\*\          - DMAMUX1_REQUEST_DAC5           
*\*\          - DMAMUX1_REQUEST_DAC6                    
*\*\          - DMAMUX2_REQUEST_GENERATOR0      
*\*\          - DMAMUX2_REQUEST_GENERATOR1       
*\*\          - DMAMUX2_REQUEST_GENERATOR2       
*\*\          - DMAMUX2_REQUEST_GENERATOR3       
*\*\          - DMAMUX2_REQUEST_GENERATOR4       
*\*\          - DMAMUX2_REQUEST_GENERATOR5       
*\*\          - DMAMUX2_REQUEST_GENERATOR6       
*\*\          - DMAMUX2_REQUEST_GENERATOR7       
*\*\          - DMAMUX2_REQUEST_GENERATOR8       
*\*\          - DMAMUX2_REQUEST_GENERATOR9       
*\*\          - DMAMUX2_REQUEST_GENERATOR10      
*\*\          - DMAMUX2_REQUEST_GENERATOR11      
*\*\          - DMAMUX2_REQUEST_GENERATOR12      
*\*\          - DMAMUX2_REQUEST_GENERATOR13      
*\*\          - DMAMUX2_REQUEST_GENERATOR14      
*\*\          - DMAMUX2_REQUEST_GENERATOR15      
*\*\          - DMAMUX2_REQUEST_REQ_XSPI1_RX     
*\*\          - DMAMUX2_REQUEST_REQ_XSPI1_TX     
*\*\          - DMAMUX2_REQUEST_REQ_XSPI2_RX     
*\*\          - DMAMUX2_REQUEST_REQ_XSPI2_TX 
*\*\note    DMAMUX1 channel 0 to 7 are mapped to DMA1 channel 0 to 7.
*\*\        DMAMUX1 channel 8 to 15 are mapped to DMA2 channel 0 to 7.
*\*\        DMAMUX1 channel 16 to 23 are mapped to DMA3 channel 0 to 7.
*\*\        DMAMUX2 channel 0 to 15 are mapped to MDMA channel 0 to 15.
*\*\return  none
*\*\note    If DMAMUXx is DMAMUX2_ID, the maximum value of the Channel is DMAMUX_CHANNEL_15
**/
void DMAMUX_SetRequestID(DMAMUX_ID DMAMUXx, uint32_t Channel, uint32_t Request)
{
    uint32_t tempreg;

    if(DMAMUXx == DMAMUX1_ID)
    {
        tempreg = ((DMAMUX_Channel_TypeDef *)(DMAMUX1_BASE + (DMAMUX_CHCTRL_SIZE * (Channel))))->CHCTRL;
        tempreg &= (~DMAMUX_REQUEST_ID_MASK);
        tempreg |= (Request);
        ((DMAMUX_Channel_TypeDef *)(DMAMUX1_BASE + (DMAMUX_CHCTRL_SIZE * (Channel))))->CHCTRL = tempreg;
    }
    else
    {
        tempreg = ((DMAMUX_Channel_TypeDef *)(DMAMUX2_MDMA_BASE + (DMAMUX_CHCTRL_SIZE * (Channel))))->CHCTRL;
        tempreg &= (~DMAMUX_REQUEST_ID_MASK);
        tempreg |= (Request);
        ((DMAMUX_Channel_TypeDef *)(DMAMUX2_MDMA_BASE + (DMAMUX_CHCTRL_SIZE * (Channel))))->CHCTRL = tempreg;
    }
}

/**
*\*\name    DMAMUX_GetRequestID.
*\*\fun     Get DMAMUX request ID for DMAMUX Channel x.
*\*\param   DMAMUXx (The input parameters must be the following values):
*\*\          - DMAMUX1_ID
*\*\          - DMAMUX2_ID
*\*\param   Channel (The input parameters must be the following values):
*\*\          - DMAMUX_CHANNEL_0
*\*\          - DMAMUX_CHANNEL_1
*\*\          - DMAMUX_CHANNEL_2
*\*\          - DMAMUX_CHANNEL_3
*\*\          - DMAMUX_CHANNEL_4
*\*\          - DMAMUX_CHANNEL_5
*\*\          - DMAMUX_CHANNEL_6
*\*\          - DMAMUX_CHANNEL_7
*\*\          - DMAMUX_CHANNEL_8
*\*\          - DMAMUX_CHANNEL_9
*\*\          - DMAMUX_CHANNEL_10
*\*\          - DMAMUX_CHANNEL_11
*\*\          - DMAMUX_CHANNEL_12
*\*\          - DMAMUX_CHANNEL_13
*\*\          - DMAMUX_CHANNEL_14
*\*\          - DMAMUX_CHANNEL_15
*\*\          - DMAMUX_CHANNEL_16
*\*\          - DMAMUX_CHANNEL_17
*\*\          - DMAMUX_CHANNEL_18
*\*\          - DMAMUX_CHANNEL_19
*\*\          - DMAMUX_CHANNEL_20
*\*\          - DMAMUX_CHANNEL_21
*\*\          - DMAMUX_CHANNEL_22
*\*\          - DMAMUX_CHANNEL_23
*\*\return  (Returned value can be one of the following values);       
*\*\          - DMAMUX1_REQUEST_GENERATOR0       
*\*\          - DMAMUX1_REQUEST_GENERATOR1       
*\*\          - DMAMUX1_REQUEST_GENERATOR2       
*\*\          - DMAMUX1_REQUEST_GENERATOR3       
*\*\          - DMAMUX1_REQUEST_GENERATOR4       
*\*\          - DMAMUX1_REQUEST_GENERATOR5       
*\*\          - DMAMUX1_REQUEST_GENERATOR6       
*\*\          - DMAMUX1_REQUEST_GENERATOR7       
*\*\          - DMAMUX1_REQUEST_ADC1             
*\*\          - DMAMUX1_REQUEST_ADC2             
*\*\          - DMAMUX1_REQUEST_ADC3             
*\*\          - DMAMUX1_REQUEST_SHRTIM1_DMA0      
*\*\          - DMAMUX1_REQUEST_SHRTIM1_DMA1      
*\*\          - DMAMUX1_REQUEST_SHRTIM1_DMA2      
*\*\          - DMAMUX1_REQUEST_SHRTIM1_DMA3      
*\*\          - DMAMUX1_REQUEST_SHRTIM1_DMA4      
*\*\          - DMAMUX1_REQUEST_SHRTIM1_DMA5      
*\*\          - DMAMUX1_REQUEST_SHRTIM1_DMA6      
*\*\          - DMAMUX1_REQUEST_SHRTIM2_DMA0      
*\*\          - DMAMUX1_REQUEST_SHRTIM2_DMA1      
*\*\          - DMAMUX1_REQUEST_SHRTIM2_DMA2      
*\*\          - DMAMUX1_REQUEST_SHRTIM2_DMA3      
*\*\          - DMAMUX1_REQUEST_SHRTIM2_DMA4      
*\*\          - DMAMUX1_REQUEST_SHRTIM2_DMA5      
*\*\          - DMAMUX1_REQUEST_SHRTIM2_DMA6      
*\*\          - DMAMUX1_REQUEST_ATIM1_UP           
*\*\          - DMAMUX1_REQUEST_ATIM1_CH1          
*\*\          - DMAMUX1_REQUEST_ATIM1_CH2          
*\*\          - DMAMUX1_REQUEST_ATIM1_CH3          
*\*\          - DMAMUX1_REQUEST_ATIM1_CH4          
*\*\          - DMAMUX1_REQUEST_ATIM1_TRIG         
*\*\          - DMAMUX1_REQUEST_ATIM1_COM          
*\*\          - DMAMUX1_REQUEST_ATIM2_UP           
*\*\          - DMAMUX1_REQUEST_ATIM2_CH1          
*\*\          - DMAMUX1_REQUEST_ATIM2_CH2          
*\*\          - DMAMUX1_REQUEST_ATIM2_CH3          
*\*\          - DMAMUX1_REQUEST_ATIM2_CH4          
*\*\          - DMAMUX1_REQUEST_ATIM2_TRIG         
*\*\          - DMAMUX1_REQUEST_ATIM2_COM           
*\*\          - DMAMUX1_REQUEST_ATIM3_UP            
*\*\          - DMAMUX1_REQUEST_ATIM3_CH1           
*\*\          - DMAMUX1_REQUEST_ATIM3_CH2           
*\*\          - DMAMUX1_REQUEST_ATIM3_CH3           
*\*\          - DMAMUX1_REQUEST_ATIM3_CH4           
*\*\          - DMAMUX1_REQUEST_ATIM3_TRIG          
*\*\          - DMAMUX1_REQUEST_ATIM3_COM           
*\*\          - DMAMUX1_REQUEST_ATIM4_UP            
*\*\          - DMAMUX1_REQUEST_ATIM4_CH1           
*\*\          - DMAMUX1_REQUEST_ATIM4_CH2           
*\*\          - DMAMUX1_REQUEST_ATIM4_CH3           
*\*\          - DMAMUX1_REQUEST_ATIM4_CH4           
*\*\          - DMAMUX1_REQUEST_ATIM4_TRIG          
*\*\          - DMAMUX1_REQUEST_ATIM4_COM           
*\*\          - DMAMUX1_REQUEST_GTIMA1_CH1       
*\*\          - DMAMUX1_REQUEST_GTIMA1_CH2       
*\*\          - DMAMUX1_REQUEST_GTIMA1_CH3       
*\*\          - DMAMUX1_REQUEST_GTIMA1_CH4       
*\*\          - DMAMUX1_REQUEST_GTIMA1_TRIG      
*\*\          - DMAMUX1_REQUEST_GTIMA1_UP        
*\*\          - DMAMUX1_REQUEST_GTIMA2_CH1       
*\*\          - DMAMUX1_REQUEST_GTIMA2_CH2       
*\*\          - DMAMUX1_REQUEST_GTIMA2_CH3       
*\*\          - DMAMUX1_REQUEST_GTIMA2_CH4       
*\*\          - DMAMUX1_REQUEST_GTIMA2_TRIG      
*\*\          - DMAMUX1_REQUEST_GTIMA2_UP        
*\*\          - DMAMUX1_REQUEST_GTIMA3_CH1       
*\*\          - DMAMUX1_REQUEST_GTIMA3_CH2       
*\*\          - DMAMUX1_REQUEST_GTIMA3_CH3       
*\*\          - DMAMUX1_REQUEST_GTIMA3_CH4       
*\*\          - DMAMUX1_REQUEST_GTIMA3_TRIG      
*\*\          - DMAMUX1_REQUEST_GTIMA3_UP        
*\*\          - DMAMUX1_REQUEST_GTIMA4_CH1       
*\*\          - DMAMUX1_REQUEST_GTIMA4_CH2       
*\*\          - DMAMUX1_REQUEST_GTIMA4_CH3       
*\*\          - DMAMUX1_REQUEST_GTIMA4_CH4       
*\*\          - DMAMUX1_REQUEST_GTIMA4_TRIG      
*\*\          - DMAMUX1_REQUEST_GTIMA4_UP        
*\*\          - DMAMUX1_REQUEST_GTIMA5_CH1       
*\*\          - DMAMUX1_REQUEST_GTIMA5_CH2       
*\*\          - DMAMUX1_REQUEST_GTIMA5_CH3       
*\*\          - DMAMUX1_REQUEST_GTIMA5_CH4       
*\*\          - DMAMUX1_REQUEST_GTIMA5_TRIG      
*\*\          - DMAMUX1_REQUEST_GTIMA5_UP        
*\*\          - DMAMUX1_REQUEST_GTIMA6_CH1       
*\*\          - DMAMUX1_REQUEST_GTIMA6_CH2       
*\*\          - DMAMUX1_REQUEST_GTIMA6_CH3       
*\*\          - DMAMUX1_REQUEST_GTIMA6_CH4       
*\*\          - DMAMUX1_REQUEST_GTIMA6_TRIG      
*\*\          - DMAMUX1_REQUEST_GTIMA6_UP        
*\*\          - DMAMUX1_REQUEST_GTIMA7_CH1       
*\*\          - DMAMUX1_REQUEST_GTIMA7_CH2       
*\*\          - DMAMUX1_REQUEST_GTIMA7_CH3       
*\*\          - DMAMUX1_REQUEST_GTIMA7_CH4       
*\*\          - DMAMUX1_REQUEST_GTIMA7_TRIG      
*\*\          - DMAMUX1_REQUEST_GTIMA7_UP        
*\*\          - DMAMUX1_REQUEST_GTIMB1_CH1       
*\*\          - DMAMUX1_REQUEST_GTIMB1_CH2       
*\*\          - DMAMUX1_REQUEST_GTIMB1_CH3       
*\*\          - DMAMUX1_REQUEST_GTIMB1_CH4       
*\*\          - DMAMUX1_REQUEST_GTIMB1_TRIG      
*\*\          - DMAMUX1_REQUEST_GTIMB1_UP        
*\*\          - DMAMUX1_REQUEST_GTIMB2_CH1       
*\*\          - DMAMUX1_REQUEST_GTIMB2_CH2       
*\*\          - DMAMUX1_REQUEST_GTIMB2_CH3       
*\*\          - DMAMUX1_REQUEST_GTIMB2_CH4       
*\*\          - DMAMUX1_REQUEST_GTIMB2_TRIG      
*\*\          - DMAMUX1_REQUEST_GTIMB2_UP        
*\*\          - DMAMUX1_REQUEST_GTIMB3_CH1       
*\*\          - DMAMUX1_REQUEST_GTIMB3_CH2       
*\*\          - DMAMUX1_REQUEST_GTIMB3_CH3       
*\*\          - DMAMUX1_REQUEST_GTIMB3_CH4       
*\*\          - DMAMUX1_REQUEST_GTIMB3_TRIG      
*\*\          - DMAMUX1_REQUEST_GTIMB3_UP        
*\*\          - DMAMUX1_REQUEST_I2C1_RX         
*\*\          - DMAMUX1_REQUEST_I2C1_TX   
*\*\          - DMAMUX1_REQUEST_I2C2_RX   
*\*\          - DMAMUX1_REQUEST_I2C2_TX   
*\*\          - DMAMUX1_REQUEST_I2C3_RX   
*\*\          - DMAMUX1_REQUEST_I2C3_TX   
*\*\          - DMAMUX1_REQUEST_I2C4_RX   
*\*\          - DMAMUX1_REQUEST_I2C4_TX   
*\*\          - DMAMUX1_REQUEST_I2C5_RX   
*\*\          - DMAMUX1_REQUEST_I2C5_TX   
*\*\          - DMAMUX1_REQUEST_I2C6_RX   
*\*\          - DMAMUX1_REQUEST_I2C6_TX   
*\*\          - DMAMUX1_REQUEST_I2C7_RX   
*\*\          - DMAMUX1_REQUEST_I2C7_TX   
*\*\          - DMAMUX1_REQUEST_I2C8_RX   
*\*\          - DMAMUX1_REQUEST_I2C8_TX   
*\*\          - DMAMUX1_REQUEST_I2C9_RX   
*\*\          - DMAMUX1_REQUEST_I2C9_TX   
*\*\          - DMAMUX1_REQUEST_I2C10_RX   
*\*\          - DMAMUX1_REQUEST_I2C10_TX   
*\*\          - DMAMUX1_REQUEST_USART1_RX   
*\*\          - DMAMUX1_REQUEST_USART1_TX   
*\*\          - DMAMUX1_REQUEST_USART2_RX   
*\*\          - DMAMUX1_REQUEST_USART2_TX   
*\*\          - DMAMUX1_REQUEST_USART3_RX   
*\*\          - DMAMUX1_REQUEST_USART3_TX   
*\*\          - DMAMUX1_REQUEST_USART4_RX   
*\*\          - DMAMUX1_REQUEST_USART4_TX        
*\*\          - DMAMUX1_REQUEST_USART5_RX        
*\*\          - DMAMUX1_REQUEST_USART5_TX        
*\*\          - DMAMUX1_REQUEST_USART6_RX        
*\*\          - DMAMUX1_REQUEST_USART6_TX        
*\*\          - DMAMUX1_REQUEST_USART7_RX        
*\*\          - DMAMUX1_REQUEST_USART7_TX        
*\*\          - DMAMUX1_REQUEST_USART8_RX        
*\*\          - DMAMUX1_REQUEST_USART8_TX        
*\*\          - DMAMUX1_REQUEST_UART9_RX         
*\*\          - DMAMUX1_REQUEST_UART9_TX         
*\*\          - DMAMUX1_REQUEST_UART10_RX         
*\*\          - DMAMUX1_REQUEST_UART10_TX         
*\*\          - DMAMUX1_REQUEST_UART11_RX         
*\*\          - DMAMUX1_REQUEST_UART11_TX         
*\*\          - DMAMUX1_REQUEST_UART12_RX         
*\*\          - DMAMUX1_REQUEST_UART12_TX         
*\*\          - DMAMUX1_REQUEST_UART13_RX         
*\*\          - DMAMUX1_REQUEST_UART13_TX         
*\*\          - DMAMUX1_REQUEST_UART14_RX         
*\*\          - DMAMUX1_REQUEST_UART14_TX         
*\*\          - DMAMUX1_REQUEST_UART15_RX         
*\*\          - DMAMUX1_REQUEST_UART15_TX         
*\*\          - DMAMUX1_REQUEST_SPI1_RX      
*\*\          - DMAMUX1_REQUEST_SPI1_TX      
*\*\          - DMAMUX1_REQUEST_SPI2_RX      
*\*\          - DMAMUX1_REQUEST_SPI2_TX      
*\*\          - DMAMUX1_REQUEST_SPI3_RX      
*\*\          - DMAMUX1_REQUEST_SPI3_TX      
*\*\          - DMAMUX1_REQUEST_SPI4_RX      
*\*\          - DMAMUX1_REQUEST_SPI4_TX      
*\*\          - DMAMUX1_REQUEST_SPI5_RX      
*\*\          - DMAMUX1_REQUEST_SPI5_TX      
*\*\          - DMAMUX1_REQUEST_SPI6_RX      
*\*\          - DMAMUX1_REQUEST_SPI6_TX      
*\*\          - DMAMUX1_REQUEST_SPI7_RX      
*\*\          - DMAMUX1_REQUEST_SPI7_TX      
*\*\          - DMAMUX1_REQUEST_I2S1_RX      
*\*\          - DMAMUX1_REQUEST_I2S1_TX      
*\*\          - DMAMUX1_REQUEST_I2S2_RX      
*\*\          - DMAMUX1_REQUEST_I2S2_TX      
*\*\          - DMAMUX1_REQUEST_I2S3_RX      
*\*\          - DMAMUX1_REQUEST_I2S3_TX      
*\*\          - DMAMUX1_REQUEST_I2S4_RX      
*\*\          - DMAMUX1_REQUEST_I2S4_TX      
*\*\          - DMAMUX1_REQUEST_LPUART1_RX   
*\*\          - DMAMUX1_REQUEST_LPUART1_TX     
*\*\          - DMAMUX1_REQUEST_LPUART2_RX     
*\*\          - DMAMUX1_REQUEST_LPUART2_TX     
*\*\          - DMAMUX1_REQUEST_DAC1           
*\*\          - DMAMUX1_REQUEST_DAC2             
*\*\          - DMAMUX1_REQUEST_DSMU_CH1       
*\*\          - DMAMUX1_REQUEST_DSMU_CH2       
*\*\          - DMAMUX1_REQUEST_DSMU_CH3       
*\*\          - DMAMUX1_REQUEST_DSMU_CH4       
*\*\          - DMAMUX1_REQUEST_CANFD1       
*\*\          - DMAMUX1_REQUEST_CANFD2       
*\*\          - DMAMUX1_REQUEST_CANFD3       
*\*\          - DMAMUX1_REQUEST_CANFD4       
*\*\          - DMAMUX1_REQUEST_CANFD5       
*\*\          - DMAMUX1_REQUEST_CANFD6       
*\*\          - DMAMUX1_REQUEST_CANFD7       
*\*\          - DMAMUX1_REQUEST_CANFD8       
*\*\          - DMAMUX1_REQUEST_CORDIC_READ   
*\*\          - DMAMUX1_REQUEST_CORDIC_WRITE  
*\*\          - DMAMUX1_REQUEST_FMAC_READ     
*\*\          - DMAMUX1_REQUEST_FMAC_WRITE    
*\*\          - DMAMUX1_REQUEST_BTIM1         
*\*\          - DMAMUX1_REQUEST_BTIM2         
*\*\          - DMAMUX1_REQUEST_BTIM3         
*\*\          - DMAMUX1_REQUEST_BTIM4         
*\*\          - DMAMUX1_REQUEST_GTIMB1_COM  
*\*\          - DMAMUX1_REQUEST_GTIMB2_COM  
*\*\          - DMAMUX1_REQUEST_GTIMB3_COM  
*\*\          - DMAMUX1_REQUEST_DAC3           
*\*\          - DMAMUX1_REQUEST_DAC4           
*\*\          - DMAMUX1_REQUEST_DAC5           
*\*\          - DMAMUX1_REQUEST_DAC6               
*\*\          - DMAMUX2_REQUEST_GENERATOR0      
*\*\          - DMAMUX2_REQUEST_GENERATOR1       
*\*\          - DMAMUX2_REQUEST_GENERATOR2       
*\*\          - DMAMUX2_REQUEST_GENERATOR3       
*\*\          - DMAMUX2_REQUEST_GENERATOR4       
*\*\          - DMAMUX2_REQUEST_GENERATOR5       
*\*\          - DMAMUX2_REQUEST_GENERATOR6       
*\*\          - DMAMUX2_REQUEST_GENERATOR7       
*\*\          - DMAMUX2_REQUEST_GENERATOR8       
*\*\          - DMAMUX2_REQUEST_GENERATOR9       
*\*\          - DMAMUX2_REQUEST_GENERATOR10      
*\*\          - DMAMUX2_REQUEST_GENERATOR11      
*\*\          - DMAMUX2_REQUEST_GENERATOR12      
*\*\          - DMAMUX2_REQUEST_GENERATOR13      
*\*\          - DMAMUX2_REQUEST_GENERATOR14      
*\*\          - DMAMUX2_REQUEST_GENERATOR15      
*\*\          - DMAMUX2_REQUEST_REQ_XSPI1_RX     
*\*\          - DMAMUX2_REQUEST_REQ_XSPI1_TX     
*\*\          - DMAMUX2_REQUEST_REQ_XSPI2_RX     
*\*\          - DMAMUX2_REQUEST_REQ_XSPI2_TX 
*\*\note    DMAMUX1 channel 0 to 7 are mapped to DMA1 channel 0 to 7.
*\*\        DMAMUX1 channel 8 to 15 are mapped to DMA2 channel 0 to 7.
*\*\        DMAMUX1 channel 16 to 23 are mapped to DMA3 channel 0 to 7.
*\*\        DMAMUX2 channel 0 to 15 are mapped to MDMA channel 0 to 15.
*\*\note    If DMAMUXx is DMAMUX2_ID, the maximum value of the Channel is DMAMUX_CHANNEL_15
**/
uint32_t DMAMUX_GetRequestID(DMAMUX_ID DMAMUXx, uint32_t Channel)
{
    uint32_t tempreg;

    if(DMAMUXx == DMAMUX1_ID)
    {
        tempreg = ((DMAMUX_Channel_TypeDef *)(DMAMUX1_BASE + (DMAMUX_CHCTRL_SIZE * (Channel))))->CHCTRL;
    }
    else
    {
        tempreg = ((DMAMUX_Channel_TypeDef *)(DMAMUX2_MDMA_BASE + (DMAMUX_CHCTRL_SIZE * (Channel))))->CHCTRL;
    }

    return (uint32_t)(tempreg & DMAMUX_REQUEST_ID_MASK);
}

/**
*\*\name    DMAMUX_SetSyncID.
*\*\fun     Set DMAMUX synchronization ID  on DMAMUX Channel x.
*\*\param   DMAMUXx (The input parameters must be the following values):
*\*\          - DMAMUX1_ID
*\*\          - DMAMUX2_ID
*\*\param   Channel (The input parameters must be the following values):
*\*\          - DMAMUX_CHANNEL_0
*\*\          - DMAMUX_CHANNEL_1
*\*\          - DMAMUX_CHANNEL_2
*\*\          - DMAMUX_CHANNEL_3
*\*\          - DMAMUX_CHANNEL_4
*\*\          - DMAMUX_CHANNEL_5
*\*\          - DMAMUX_CHANNEL_6
*\*\          - DMAMUX_CHANNEL_7
*\*\          - DMAMUX_CHANNEL_8
*\*\          - DMAMUX_CHANNEL_9
*\*\          - DMAMUX_CHANNEL_10
*\*\          - DMAMUX_CHANNEL_11
*\*\          - DMAMUX_CHANNEL_12
*\*\          - DMAMUX_CHANNEL_13
*\*\          - DMAMUX_CHANNEL_14
*\*\          - DMAMUX_CHANNEL_15
*\*\          - DMAMUX_CHANNEL_16
*\*\          - DMAMUX_CHANNEL_17
*\*\          - DMAMUX_CHANNEL_18
*\*\          - DMAMUX_CHANNEL_19
*\*\          - DMAMUX_CHANNEL_20
*\*\          - DMAMUX_CHANNEL_21
*\*\          - DMAMUX_CHANNEL_22
*\*\          - DMAMUX_CHANNEL_23
*\*\param   SyncID (The input parameters must be the following values):
*\*\          - DMAMUX1_SYNC_DMAMUX1_EVT0_7
*\*\          - DMAMUX1_SYNC_DMAMUX1_EVT8_15
*\*\          - DMAMUX1_SYNC_DMAMUX1_EVT16_23
*\*\          - DMAMUX1_SYNC_LPTIM5_OUT
*\*\          - DMAMUX1_SYNC_LPTIM4_OUT
*\*\          - DMAMUX1_SYNC_LPTIM3_OUT
*\*\          - DMAMUX1_SYNC_LPTIM2_OUT
*\*\          - DMAMUX1_SYNC_LPTIM1_OUT
*\*\          - DMAMUX1_SYNC_EXTI0
*\*\          - DMAMUX2_SYNC_INTERNAL_USED
*\*\return  none
*\*\note    If DMAMUXx is DMAMUX2_ID, the maximum value of the Channel is DMAMUX_CHANNEL_15
**/
void DMAMUX_SetSyncID(DMAMUX_ID DMAMUXx, uint32_t Channel, uint32_t SyncID)
{
    uint32_t tempreg;

    if(DMAMUXx == DMAMUX1_ID)
    {
        tempreg = ((DMAMUX_Channel_TypeDef *)(DMAMUX1_BASE + (DMAMUX_CHCTRL_SIZE * (Channel))))->CHCTRL;
        tempreg &= (~DMAMUX_SYNC_ID_MASK);
        tempreg |= (SyncID);
        ((DMAMUX_Channel_TypeDef *)(DMAMUX1_BASE + (DMAMUX_CHCTRL_SIZE * (Channel))))->CHCTRL = tempreg;
    }
    else
    {
        tempreg = ((DMAMUX_Channel_TypeDef *)(DMAMUX2_MDMA_BASE + (DMAMUX_CHCTRL_SIZE * (Channel))))->CHCTRL;
        tempreg &= (~DMAMUX_SYNC_ID_MASK);
        tempreg |= (SyncID);
        ((DMAMUX_Channel_TypeDef *)(DMAMUX2_MDMA_BASE + (DMAMUX_CHCTRL_SIZE * (Channel))))->CHCTRL = tempreg;
    }
}

/**
*\*\name    DMAMUX_GetSyncID.
*\*\fun     Get DMAMUX synchronization ID  on DMAMUX Channel x.
*\*\param   DMAMUXx (The input parameters must be the following values):
*\*\          - DMAMUX1_ID
*\*\          - DMAMUX2_ID
*\*\param   Channel (The input parameters must be the following values):
*\*\          - DMAMUX_CHANNEL_0
*\*\          - DMAMUX_CHANNEL_1
*\*\          - DMAMUX_CHANNEL_2
*\*\          - DMAMUX_CHANNEL_3
*\*\          - DMAMUX_CHANNEL_4
*\*\          - DMAMUX_CHANNEL_5
*\*\          - DMAMUX_CHANNEL_6
*\*\          - DMAMUX_CHANNEL_7
*\*\          - DMAMUX_CHANNEL_8
*\*\          - DMAMUX_CHANNEL_9
*\*\          - DMAMUX_CHANNEL_10
*\*\          - DMAMUX_CHANNEL_11
*\*\          - DMAMUX_CHANNEL_12
*\*\          - DMAMUX_CHANNEL_13
*\*\          - DMAMUX_CHANNEL_14
*\*\          - DMAMUX_CHANNEL_15
*\*\          - DMAMUX_CHANNEL_16
*\*\          - DMAMUX_CHANNEL_17
*\*\          - DMAMUX_CHANNEL_18
*\*\          - DMAMUX_CHANNEL_19
*\*\          - DMAMUX_CHANNEL_20
*\*\          - DMAMUX_CHANNEL_21
*\*\          - DMAMUX_CHANNEL_22
*\*\          - DMAMUX_CHANNEL_23
*\*\return  (Returned value can be one of the following values):
*\*\          - DMAMUX1_SYNC_DMAMUX1_EVT0_7
*\*\          - DMAMUX1_SYNC_DMAMUX1_EVT8_15
*\*\          - DMAMUX1_SYNC_DMAMUX1_EVT16_23
*\*\          - DMAMUX1_SYNC_LPTIM5_OUT
*\*\          - DMAMUX1_SYNC_LPTIM4_OUT
*\*\          - DMAMUX1_SYNC_LPTIM3_OUT
*\*\          - DMAMUX1_SYNC_LPTIM2_OUT
*\*\          - DMAMUX1_SYNC_LPTIM1_OUT
*\*\          - DMAMUX1_SYNC_EXTI0
*\*\          - DMAMUX2_SYNC_INTERNAL_USED
*\*\return  none
*\*\note    If DMAMUXx is DMAMUX2_ID, the maximum value of the Channel is DMAMUX_CHANNEL_15
**/
uint32_t DMAMUX_GetSyncID(DMAMUX_ID DMAMUXx, uint32_t Channel)
{
    uint32_t tempreg;

    if(DMAMUXx == DMAMUX1_ID)
    {
        tempreg = ((DMAMUX_Channel_TypeDef *)(DMAMUX1_BASE + (DMAMUX_CHCTRL_SIZE * (Channel))))->CHCTRL;
    }
    else
    {
        tempreg = ((DMAMUX_Channel_TypeDef *)(DMAMUX2_MDMA_BASE + (DMAMUX_CHCTRL_SIZE * (Channel))))->CHCTRL;
    }

    return (uint32_t)(tempreg & DMAMUX_SYNC_ID_MASK);
}

/**
*\*\name    DMAMUX_SetSyncRequestNumber.
*\*\fun     Set the number of DMA request that will be autorized after a synchronization event and/or the number of DMA request needed to generate an event.
*\*\param   DMAMUXx (The input parameters must be the following values):
*\*\          - DMAMUX1_ID
*\*\          - DMAMUX2_ID
*\*\param   Channel (The input parameters must be the following values):
*\*\          - DMAMUX_CHANNEL_0
*\*\          - DMAMUX_CHANNEL_1
*\*\          - DMAMUX_CHANNEL_2
*\*\          - DMAMUX_CHANNEL_3
*\*\          - DMAMUX_CHANNEL_4
*\*\          - DMAMUX_CHANNEL_5
*\*\          - DMAMUX_CHANNEL_6
*\*\          - DMAMUX_CHANNEL_7
*\*\          - DMAMUX_CHANNEL_8
*\*\          - DMAMUX_CHANNEL_9
*\*\          - DMAMUX_CHANNEL_10
*\*\          - DMAMUX_CHANNEL_11
*\*\          - DMAMUX_CHANNEL_12
*\*\          - DMAMUX_CHANNEL_13
*\*\          - DMAMUX_CHANNEL_14
*\*\          - DMAMUX_CHANNEL_15
*\*\          - DMAMUX_CHANNEL_16
*\*\          - DMAMUX_CHANNEL_17
*\*\          - DMAMUX_CHANNEL_18
*\*\          - DMAMUX_CHANNEL_19
*\*\          - DMAMUX_CHANNEL_20
*\*\          - DMAMUX_CHANNEL_21
*\*\          - DMAMUX_CHANNEL_22
*\*\          - DMAMUX_CHANNEL_23
*\*\param   RequestNumber This parameter must be a value between Min_Data = 1 and Max_Data = 32.
*\*\return  none
*\*\note    If DMAMUXx is DMAMUX2_ID, the maximum value of the Channel is DMAMUX_CHANNEL_15
**/
void DMAMUX_SetSyncRequestNumber(DMAMUX_ID DMAMUXx, uint32_t Channel, uint32_t RequestNumber)
{
    uint32_t tempreg;

    if(DMAMUXx == DMAMUX1_ID)
    {
        tempreg = ((DMAMUX_Channel_TypeDef *)(DMAMUX1_BASE + (DMAMUX_CHCTRL_SIZE * (Channel))))->CHCTRL;
        tempreg &= (~DMAMUX_REQ_NUMBER_MASK);
        tempreg |= ((RequestNumber - 1) << DMAMUX_REQ_NUMBER_Pos);
        ((DMAMUX_Channel_TypeDef *)(DMAMUX1_BASE + (DMAMUX_CHCTRL_SIZE * (Channel))))->CHCTRL = tempreg;
    }
    else
    {
        tempreg = ((DMAMUX_Channel_TypeDef *)(DMAMUX2_MDMA_BASE + (DMAMUX_CHCTRL_SIZE * (Channel))))->CHCTRL;
        tempreg &= (~DMAMUX_REQ_NUMBER_MASK);
        tempreg |= ((RequestNumber - 1) << DMAMUX_REQ_NUMBER_Pos);
        ((DMAMUX_Channel_TypeDef *)(DMAMUX2_MDMA_BASE + (DMAMUX_CHCTRL_SIZE * (Channel))))->CHCTRL = tempreg;
    }
}

/**
*\*\name    DMAMUX_GetSyncRequestNumber.
*\*\fun     Get the number of DMA request that will be autorized after a synchronization event and/or the number of DMA request needed to generate an event.
*\*\param   DMAMUXx (The input parameters must be the following values):
*\*\          - DMAMUX1_ID
*\*\          - DMAMUX2_ID
*\*\param   Channel (The input parameters must be the following values):
*\*\          - DMAMUX_CHANNEL_0
*\*\          - DMAMUX_CHANNEL_1
*\*\          - DMAMUX_CHANNEL_2
*\*\          - DMAMUX_CHANNEL_3
*\*\          - DMAMUX_CHANNEL_4
*\*\          - DMAMUX_CHANNEL_5
*\*\          - DMAMUX_CHANNEL_6
*\*\          - DMAMUX_CHANNEL_7
*\*\          - DMAMUX_CHANNEL_8
*\*\          - DMAMUX_CHANNEL_9
*\*\          - DMAMUX_CHANNEL_10
*\*\          - DMAMUX_CHANNEL_11
*\*\          - DMAMUX_CHANNEL_12
*\*\          - DMAMUX_CHANNEL_13
*\*\          - DMAMUX_CHANNEL_14
*\*\          - DMAMUX_CHANNEL_15
*\*\          - DMAMUX_CHANNEL_16
*\*\          - DMAMUX_CHANNEL_17
*\*\          - DMAMUX_CHANNEL_18
*\*\          - DMAMUX_CHANNEL_19
*\*\          - DMAMUX_CHANNEL_20
*\*\          - DMAMUX_CHANNEL_21
*\*\          - DMAMUX_CHANNEL_22
*\*\          - DMAMUX_CHANNEL_23
*\*\return  Between Min_Data = 1 and Max_Data = 32
*\*\note    If DMAMUXx is DMAMUX2_ID, the maximum value of the Channel is DMAMUX_CHANNEL_15
**/
uint32_t DMAMUX_GetSyncRequestNumber(DMAMUX_ID DMAMUXx, uint32_t Channel)
{
    uint32_t tempreg;

    if(DMAMUXx == DMAMUX1_ID)
    {
        tempreg = ((DMAMUX_Channel_TypeDef *)(DMAMUX1_BASE + (DMAMUX_CHCTRL_SIZE * (Channel))))->CHCTRL;
    }
    else
    {
        tempreg = ((DMAMUX_Channel_TypeDef *)(DMAMUX2_MDMA_BASE + (DMAMUX_CHCTRL_SIZE * (Channel))))->CHCTRL;
    }

    return (uint32_t)(((tempreg & DMAMUX_REQ_NUMBER_MASK) >> DMAMUX_REQ_NUMBER_Pos) + 1);
}

/**
*\*\name    DMAMUX_SetSyncPolarity.
*\*\fun     Set the polarity of the signal on which the DMA request is synchronized.
*\*\param   DMAMUXx (The input parameters must be the following values):
*\*\          - DMAMUX1_ID
*\*\          - DMAMUX2_ID
*\*\param   Channel (The input parameters must be the following values):
*\*\          - DMAMUX_CHANNEL_0
*\*\          - DMAMUX_CHANNEL_1
*\*\          - DMAMUX_CHANNEL_2
*\*\          - DMAMUX_CHANNEL_3
*\*\          - DMAMUX_CHANNEL_4
*\*\          - DMAMUX_CHANNEL_5
*\*\          - DMAMUX_CHANNEL_6
*\*\          - DMAMUX_CHANNEL_7
*\*\          - DMAMUX_CHANNEL_8
*\*\          - DMAMUX_CHANNEL_9
*\*\          - DMAMUX_CHANNEL_10
*\*\          - DMAMUX_CHANNEL_11
*\*\          - DMAMUX_CHANNEL_12
*\*\          - DMAMUX_CHANNEL_13
*\*\          - DMAMUX_CHANNEL_14
*\*\          - DMAMUX_CHANNEL_15
*\*\          - DMAMUX_CHANNEL_16
*\*\          - DMAMUX_CHANNEL_17
*\*\          - DMAMUX_CHANNEL_18
*\*\          - DMAMUX_CHANNEL_19
*\*\          - DMAMUX_CHANNEL_20
*\*\          - DMAMUX_CHANNEL_21
*\*\          - DMAMUX_CHANNEL_22
*\*\          - DMAMUX_CHANNEL_23
*\*\param   Polarity (The input parameters must be the following values).
*\*\          - DMAMUX_SYNC_NO_EVENT
*\*\          - DMAMUX_SYNC_POL_RISING
*\*\          - DMAMUX_SYNC_POL_FALLING
*\*\          - DMAMUX_SYNC_POL_RISING_FALLING
*\*\return  none
*\*\note    If DMAMUXx is DMAMUX2_ID, the maximum value of the Channel is DMAMUX_CHANNEL_15
**/
void DMAMUX_SetSyncPolarity(DMAMUX_ID DMAMUXx, uint32_t Channel, uint32_t Polarity)
{
    uint32_t tempreg;

    if(DMAMUXx == DMAMUX1_ID)
    {
        tempreg = ((DMAMUX_Channel_TypeDef *)(DMAMUX1_BASE + (DMAMUX_CHCTRL_SIZE * (Channel))))->CHCTRL;
        tempreg &= (~DMAMUX_SYNC_POL_MASK);
        tempreg |= (Polarity);
        ((DMAMUX_Channel_TypeDef *)(DMAMUX1_BASE + (DMAMUX_CHCTRL_SIZE * (Channel))))->CHCTRL = tempreg;
    }
    else
    {
        tempreg = ((DMAMUX_Channel_TypeDef *)(DMAMUX2_MDMA_BASE + (DMAMUX_CHCTRL_SIZE * (Channel))))->CHCTRL;
        tempreg &= (~DMAMUX_SYNC_POL_MASK);
        tempreg |= (Polarity);
        ((DMAMUX_Channel_TypeDef *)(DMAMUX2_MDMA_BASE + (DMAMUX_CHCTRL_SIZE * (Channel))))->CHCTRL = tempreg;
    }
}

/**
*\*\name    DMAMUX_GetSyncPolarity.
*\*\fun     Get the polarity of the signal on which the DMA request is synchronized.
*\*\param   DMAMUXx (The input parameters must be the following values):
*\*\          - DMAMUX1_ID
*\*\          - DMAMUX2_ID
*\*\param   Channel (The input parameters must be the following values):
*\*\          - DMAMUX_CHANNEL_0
*\*\          - DMAMUX_CHANNEL_1
*\*\          - DMAMUX_CHANNEL_2
*\*\          - DMAMUX_CHANNEL_3
*\*\          - DMAMUX_CHANNEL_4
*\*\          - DMAMUX_CHANNEL_5
*\*\          - DMAMUX_CHANNEL_6
*\*\          - DMAMUX_CHANNEL_7
*\*\          - DMAMUX_CHANNEL_8
*\*\          - DMAMUX_CHANNEL_9
*\*\          - DMAMUX_CHANNEL_10
*\*\          - DMAMUX_CHANNEL_11
*\*\          - DMAMUX_CHANNEL_12
*\*\          - DMAMUX_CHANNEL_13
*\*\          - DMAMUX_CHANNEL_14
*\*\          - DMAMUX_CHANNEL_15
*\*\          - DMAMUX_CHANNEL_16
*\*\          - DMAMUX_CHANNEL_17
*\*\          - DMAMUX_CHANNEL_18
*\*\          - DMAMUX_CHANNEL_19
*\*\          - DMAMUX_CHANNEL_20
*\*\          - DMAMUX_CHANNEL_21
*\*\          - DMAMUX_CHANNEL_22
*\*\          - DMAMUX_CHANNEL_23
*\*\return  Returned value can be one of the following values:
*\*\          - DMAMUX_SYNC_NO_EVENT
*\*\          - DMAMUX_SYNC_POL_RISING
*\*\          - DMAMUX_SYNC_POL_FALLING
*\*\          - DMAMUX_SYNC_POL_RISING_FALLING
*\*\note    If DMAMUXx is DMAMUX2_ID, the maximum value of the Channel is DMAMUX_CHANNEL_15
**/
uint32_t DMAMUX_GetSyncPolarity(DMAMUX_ID DMAMUXx, uint32_t Channel)
{
    uint32_t tempreg;

    if(DMAMUXx == DMAMUX1_ID)
    {
        tempreg = ((DMAMUX_Channel_TypeDef *)(DMAMUX1_BASE + (DMAMUX_CHCTRL_SIZE * (Channel))))->CHCTRL;
    }
    else
    {
        tempreg = ((DMAMUX_Channel_TypeDef *)(DMAMUX2_MDMA_BASE + (DMAMUX_CHCTRL_SIZE * (Channel))))->CHCTRL;
    }

    return (uint32_t)(tempreg & DMAMUX_SYNC_POL_MASK);
}

/**
*\*\name    DMAMUX_EnableEventGeneration.
*\*\fun     Enable or disable the Event Generation on DMAMUX channel x.
*\*\param   DMAMUXx (The input parameters must be the following values):
*\*\          - DMAMUX1_ID
*\*\          - DMAMUX2_ID
*\*\param   Channel (The input parameters must be the following values):
*\*\          - DMAMUX_CHANNEL_0
*\*\          - DMAMUX_CHANNEL_1
*\*\          - DMAMUX_CHANNEL_2
*\*\          - DMAMUX_CHANNEL_3
*\*\          - DMAMUX_CHANNEL_4
*\*\          - DMAMUX_CHANNEL_5
*\*\          - DMAMUX_CHANNEL_6
*\*\          - DMAMUX_CHANNEL_7
*\*\          - DMAMUX_CHANNEL_8
*\*\          - DMAMUX_CHANNEL_9
*\*\          - DMAMUX_CHANNEL_10
*\*\          - DMAMUX_CHANNEL_11
*\*\          - DMAMUX_CHANNEL_12
*\*\          - DMAMUX_CHANNEL_13
*\*\          - DMAMUX_CHANNEL_14
*\*\          - DMAMUX_CHANNEL_15
*\*\          - DMAMUX_CHANNEL_16
*\*\          - DMAMUX_CHANNEL_17
*\*\          - DMAMUX_CHANNEL_18
*\*\          - DMAMUX_CHANNEL_19
*\*\          - DMAMUX_CHANNEL_20
*\*\          - DMAMUX_CHANNEL_21
*\*\          - DMAMUX_CHANNEL_22
*\*\          - DMAMUX_CHANNEL_23
*\*\param   Cmd :
*\*\          - ENABLE
*\*\          - DISABLE
*\*\return  none
*\*\note    If DMAMUXx is DMAMUX2_ID, the maximum value of the Channel is DMAMUX_CHANNEL_15
**/
void DMAMUX_EnableEventGeneration(DMAMUX_ID DMAMUXx, uint32_t Channel, FunctionalState Cmd)
{
    if(DMAMUXx == DMAMUX1_ID)
    {
        if(Cmd == ENABLE)
        {
            ((DMAMUX_Channel_TypeDef *)(DMAMUX1_BASE + (DMAMUX_CHCTRL_SIZE * (Channel))))->CHCTRL |= DMAMUX_EVENT_GEN_MASK;
        }
        else
        {
            ((DMAMUX_Channel_TypeDef *)(DMAMUX1_BASE + (DMAMUX_CHCTRL_SIZE * (Channel))))->CHCTRL &= (~DMAMUX_EVENT_GEN_MASK);
        }
    }
    else
    {
        if(Cmd == ENABLE)
        {
            ((DMAMUX_Channel_TypeDef *)(DMAMUX2_MDMA_BASE + (DMAMUX_CHCTRL_SIZE * (Channel))))->CHCTRL |= DMAMUX_EVENT_GEN_MASK;
        }
        else
        {
            ((DMAMUX_Channel_TypeDef *)(DMAMUX2_MDMA_BASE + (DMAMUX_CHCTRL_SIZE * (Channel))))->CHCTRL &= (~DMAMUX_EVENT_GEN_MASK);
        }
    }
}

/**
*\*\name    DMAMUX_EnableSync.
*\*\fun     Enable or disable the synchronization mode on DMAMUX channel x.
*\*\param   DMAMUXx (The input parameters must be the following values):
*\*\          - DMAMUX1_ID
*\*\          - DMAMUX2_ID
*\*\param   Channel (The input parameters must be the following values):
*\*\          - DMAMUX_CHANNEL_0
*\*\          - DMAMUX_CHANNEL_1
*\*\          - DMAMUX_CHANNEL_2
*\*\          - DMAMUX_CHANNEL_3
*\*\          - DMAMUX_CHANNEL_4
*\*\          - DMAMUX_CHANNEL_5
*\*\          - DMAMUX_CHANNEL_6
*\*\          - DMAMUX_CHANNEL_7
*\*\          - DMAMUX_CHANNEL_8
*\*\          - DMAMUX_CHANNEL_9
*\*\          - DMAMUX_CHANNEL_10
*\*\          - DMAMUX_CHANNEL_11
*\*\          - DMAMUX_CHANNEL_12
*\*\          - DMAMUX_CHANNEL_13
*\*\          - DMAMUX_CHANNEL_14
*\*\          - DMAMUX_CHANNEL_15
*\*\          - DMAMUX_CHANNEL_16
*\*\          - DMAMUX_CHANNEL_17
*\*\          - DMAMUX_CHANNEL_18
*\*\          - DMAMUX_CHANNEL_19
*\*\          - DMAMUX_CHANNEL_20
*\*\          - DMAMUX_CHANNEL_21
*\*\          - DMAMUX_CHANNEL_22
*\*\          - DMAMUX_CHANNEL_23
*\*\param   Cmd :
*\*\          - ENABLE
*\*\          - DISABLE
*\*\return  none
*\*\note    If DMAMUXx is DMAMUX2_ID, the maximum value of the Channel is DMAMUX_CHANNEL_15
**/
void DMAMUX_EnableSync(DMAMUX_ID DMAMUXx, uint32_t Channel, FunctionalState Cmd)
{
    if(DMAMUXx == DMAMUX1_ID)
    {
        if(Cmd == ENABLE)
        {
            ((DMAMUX_Channel_TypeDef *)(DMAMUX1_BASE + (DMAMUX_CHCTRL_SIZE * (Channel))))->CHCTRL |= DMAMUX_SYN_ENABLE_MASK;
        }
        else
        {
            ((DMAMUX_Channel_TypeDef *)(DMAMUX1_BASE + (DMAMUX_CHCTRL_SIZE * (Channel))))->CHCTRL &= (~DMAMUX_SYN_ENABLE_MASK);
        }
    }
    else
    {
        if(Cmd == ENABLE)
        {
            ((DMAMUX_Channel_TypeDef *)(DMAMUX2_MDMA_BASE + (DMAMUX_CHCTRL_SIZE * (Channel))))->CHCTRL |= DMAMUX_SYN_ENABLE_MASK;
        }
        else
        {
            ((DMAMUX_Channel_TypeDef *)(DMAMUX2_MDMA_BASE + (DMAMUX_CHCTRL_SIZE * (Channel))))->CHCTRL &= (~DMAMUX_SYN_ENABLE_MASK);
        }
    }
}

/**
*\*\name    DMAMUX_EnableRequestGen.
*\*\fun     Enable or disable the Request Generator.
*\*\param   DMAMUXx (The input parameters must be the following values):
*\*\          - DMAMUX1_ID
*\*\          - DMAMUX2_ID
*\*\param   RequestGenChannel (The input parameters must be the following values):
*\*\          - DMAMUX_REQ_GEN_0
*\*\          - DMAMUX_REQ_GEN_1
*\*\          - DMAMUX_REQ_GEN_2
*\*\          - DMAMUX_REQ_GEN_3
*\*\          - DMAMUX_REQ_GEN_4
*\*\          - DMAMUX_REQ_GEN_5
*\*\          - DMAMUX_REQ_GEN_6
*\*\          - DMAMUX_REQ_GEN_7
*\*\          - DMAMUX_REQ_GEN_8
*\*\          - DMAMUX_REQ_GEN_9
*\*\          - DMAMUX_REQ_GEN_10
*\*\          - DMAMUX_REQ_GEN_11
*\*\          - DMAMUX_REQ_GEN_12
*\*\          - DMAMUX_REQ_GEN_13
*\*\          - DMAMUX_REQ_GEN_14
*\*\          - DMAMUX_REQ_GEN_15
*\*\param   Cmd :
*\*\          - ENABLE
*\*\          - DISABLE
*\*\return  none
*\*\note    If DMAMUXx is DMAMUX1_ID, the maximum value of the RequestGenChannel is DMAMUX_REQ_GEN_7
**/
void DMAMUX_EnableRequestGen(DMAMUX_ID DMAMUXx, uint32_t RequestGenChannel, FunctionalState Cmd)
{
    if(DMAMUXx == DMAMUX1_ID)
    {
        if(Cmd == ENABLE)
        {
            ((DMAMUX_RequestGen_TypeDef *)(DMAMUX1_BASE + DMAMUX_REQ_GEN_OFFSET + (DMAMUX_CHCTRL_SIZE * (RequestGenChannel))))->CHCFG |= DMAMUX_GEN_ENABLE_MASK;
        }
        else
        {
            ((DMAMUX_RequestGen_TypeDef *)(DMAMUX1_BASE + DMAMUX_REQ_GEN_OFFSET + (DMAMUX_CHCTRL_SIZE * (RequestGenChannel))))->CHCFG &= (~DMAMUX_GEN_ENABLE_MASK);
        }
    }
    else
    {
        if(Cmd == ENABLE)
        {
            ((DMAMUX_RequestGen_TypeDef *)(DMAMUX2_MDMA_BASE + DMAMUX_REQ_GEN_OFFSET + (DMAMUX_CHCTRL_SIZE * (RequestGenChannel))))->CHCFG |= DMAMUX_GEN_ENABLE_MASK;
        }
        else
        {
            ((DMAMUX_RequestGen_TypeDef *)(DMAMUX2_MDMA_BASE + DMAMUX_REQ_GEN_OFFSET + (DMAMUX_CHCTRL_SIZE * (RequestGenChannel))))->CHCFG &= (~DMAMUX_GEN_ENABLE_MASK);
        }
    }
}

/**
*\*\name    DMAMUX_SetRequestGenPolarity.
*\*\fun     Set the polarity of the signal on which the DMA request is generated.
*\*\param   DMAMUXx (The input parameters must be the following values):
*\*\          - DMAMUX1_ID
*\*\          - DMAMUX2_ID
*\*\param   RequestGenChannel (The input parameters must be the following values):
*\*\          - DMAMUX_REQ_GEN_0
*\*\          - DMAMUX_REQ_GEN_1
*\*\          - DMAMUX_REQ_GEN_2
*\*\          - DMAMUX_REQ_GEN_3
*\*\          - DMAMUX_REQ_GEN_4
*\*\          - DMAMUX_REQ_GEN_5
*\*\          - DMAMUX_REQ_GEN_6
*\*\          - DMAMUX_REQ_GEN_7
*\*\          - DMAMUX_REQ_GEN_8
*\*\          - DMAMUX_REQ_GEN_9
*\*\          - DMAMUX_REQ_GEN_10
*\*\          - DMAMUX_REQ_GEN_11
*\*\          - DMAMUX_REQ_GEN_12
*\*\          - DMAMUX_REQ_GEN_13
*\*\          - DMAMUX_REQ_GEN_14
*\*\          - DMAMUX_REQ_GEN_15
*\*\param   Polarity :
*\*\          - DMAMUX_REQ_GEN_NO_EVENT
*\*\          - DMAMUX_REQ_GEN_POL_RISING
*\*\          - DMAMUX_REQ_GEN_POL_FALLING
*\*\          - DMAMUX_REQ_GEN_POL_RISING_FALLING
*\*\return  none
*\*\note    If DMAMUXx is DMAMUX1_ID, the maximum value of the RequestGenChannel is DMAMUX_REQ_GEN_7
**/
void DMAMUX_SetRequestGenPolarity(DMAMUX_ID DMAMUXx, uint32_t RequestGenChannel, uint32_t Polarity)
{
    uint32_t tempreg;

    if(DMAMUXx == DMAMUX1_ID)
    {
        tempreg = ((DMAMUX_RequestGen_TypeDef *)(DMAMUX1_BASE + DMAMUX_REQ_GEN_OFFSET + (DMAMUX_CHCTRL_SIZE * (RequestGenChannel))))->CHCFG;
        tempreg &= (~DMAMUX_REQ_GEN_POL_MASK);
        tempreg |= (Polarity);
        ((DMAMUX_RequestGen_TypeDef *)(DMAMUX1_BASE + DMAMUX_REQ_GEN_OFFSET + (DMAMUX_CHCTRL_SIZE * (RequestGenChannel))))->CHCFG = tempreg;
    }
    else
    {
        tempreg = ((DMAMUX_RequestGen_TypeDef *)(DMAMUX2_MDMA_BASE + DMAMUX_REQ_GEN_OFFSET + (DMAMUX_CHCTRL_SIZE * (RequestGenChannel))))->CHCFG;
        tempreg &= (~DMAMUX_REQ_GEN_POL_MASK);
        tempreg |= (Polarity);
        ((DMAMUX_RequestGen_TypeDef *)(DMAMUX2_MDMA_BASE + DMAMUX_REQ_GEN_OFFSET + (DMAMUX_CHCTRL_SIZE * (RequestGenChannel))))->CHCFG = tempreg;
    }
}

/**
*\*\name    DMAMUX_GetRequestGenPolarity.
*\*\fun     Get the polarity of the signal on which the DMA request is generated..
*\*\param   DMAMUXx (The input parameters must be the following values):
*\*\          - DMAMUX1_ID
*\*\          - DMAMUX2_ID
*\*\param   RequestGenChannel (The input parameters must be the following values):
*\*\          - DMAMUX_REQ_GEN_0
*\*\          - DMAMUX_REQ_GEN_1
*\*\          - DMAMUX_REQ_GEN_2
*\*\          - DMAMUX_REQ_GEN_3
*\*\          - DMAMUX_REQ_GEN_4
*\*\          - DMAMUX_REQ_GEN_5
*\*\          - DMAMUX_REQ_GEN_6
*\*\          - DMAMUX_REQ_GEN_7
*\*\          - DMAMUX_REQ_GEN_8
*\*\          - DMAMUX_REQ_GEN_9
*\*\          - DMAMUX_REQ_GEN_10
*\*\          - DMAMUX_REQ_GEN_11
*\*\          - DMAMUX_REQ_GEN_12
*\*\          - DMAMUX_REQ_GEN_13
*\*\          - DMAMUX_REQ_GEN_14
*\*\          - DMAMUX_REQ_GEN_15
*\*\return  Returned value can be one of the following values:
*\*\          - DMAMUX_REQ_GEN_NO_EVENT
*\*\          - DMAMUX_REQ_GEN_POL_RISING
*\*\          - DMAMUX_REQ_GEN_POL_FALLING
*\*\          - DMAMUX_REQ_GEN_POL_RISING_FALLING
*\*\note    If DMAMUXx is DMAMUX1_ID, the maximum value of the RequestGenChannel is DMAMUX_REQ_GEN_7
**/
uint32_t DMAMUX_GetRequestGenPolarity(DMAMUX_ID DMAMUXx, uint32_t RequestGenChannel)
{
    uint32_t tempreg;

    if(DMAMUXx == DMAMUX1_ID)
    {
        tempreg = ((DMAMUX_RequestGen_TypeDef *)(DMAMUX1_BASE + DMAMUX_REQ_GEN_OFFSET + (DMAMUX_CHCTRL_SIZE * (RequestGenChannel))))->CHCFG;
    }
    else
    {
        tempreg = ((DMAMUX_RequestGen_TypeDef *)(DMAMUX2_MDMA_BASE + DMAMUX_REQ_GEN_OFFSET + (DMAMUX_CHCTRL_SIZE * (RequestGenChannel))))->CHCFG;
    }

    return (uint32_t)(tempreg & DMAMUX_REQ_GEN_POL_MASK);
}

/**
*\*\name    DMAMUX_SetGenRequestNumber.
*\*\fun     Set the number of DMA request that will be autorized after a generation event.
*\*\param   DMAMUXx (The input parameters must be the following values):
*\*\          - DMAMUX1_ID
*\*\          - DMAMUX2_ID
*\*\param   RequestGenChannel (The input parameters must be the following values):
*\*\          - DMAMUX_REQ_GEN_0
*\*\          - DMAMUX_REQ_GEN_1
*\*\          - DMAMUX_REQ_GEN_2
*\*\          - DMAMUX_REQ_GEN_3
*\*\          - DMAMUX_REQ_GEN_4
*\*\          - DMAMUX_REQ_GEN_5
*\*\          - DMAMUX_REQ_GEN_6
*\*\          - DMAMUX_REQ_GEN_7
*\*\          - DMAMUX_REQ_GEN_8
*\*\          - DMAMUX_REQ_GEN_9
*\*\          - DMAMUX_REQ_GEN_10
*\*\          - DMAMUX_REQ_GEN_11
*\*\          - DMAMUX_REQ_GEN_12
*\*\          - DMAMUX_REQ_GEN_13
*\*\          - DMAMUX_REQ_GEN_14
*\*\          - DMAMUX_REQ_GEN_15
*\*\param   RequestNumber This parameter must be a value between Min_Data = 1 and Max_Data = 32:
*\*\return  none
*\*\note    If DMAMUXx is DMAMUX1_ID, the maximum value of the RequestGenChannel is DMAMUX_REQ_GEN_7
**/
void DMAMUX_SetGenRequestNumber(DMAMUX_ID DMAMUXx, uint32_t RequestGenChannel, uint32_t RequestNumber)
{
    uint32_t tempreg;

    if(DMAMUXx == DMAMUX1_ID)
    {
        tempreg = ((DMAMUX_RequestGen_TypeDef *)(DMAMUX1_BASE + DMAMUX_REQ_GEN_OFFSET + (DMAMUX_CHCTRL_SIZE * RequestGenChannel)))->CHCFG;
        tempreg &= (~DMAMUX_REQ_GEN_NUMBER_MASK);
        tempreg |= ((RequestNumber - 1) << DMAMUX_REQ_GEN_NUMBER_Pos);
        ((DMAMUX_RequestGen_TypeDef *)(DMAMUX1_BASE + DMAMUX_REQ_GEN_OFFSET + (DMAMUX_CHCTRL_SIZE * RequestGenChannel)))->CHCFG = tempreg;
    }
    else
    {
        tempreg = ((DMAMUX_RequestGen_TypeDef *)(DMAMUX2_MDMA_BASE + DMAMUX_REQ_GEN_OFFSET + (DMAMUX_CHCTRL_SIZE * RequestGenChannel)))->CHCFG;
        tempreg &= (~DMAMUX_REQ_GEN_NUMBER_MASK);
        tempreg |= ((RequestNumber - 1) << DMAMUX_REQ_GEN_NUMBER_Pos);
        ((DMAMUX_RequestGen_TypeDef *)(DMAMUX2_MDMA_BASE + DMAMUX_REQ_GEN_OFFSET + (DMAMUX_CHCTRL_SIZE * RequestGenChannel)))->CHCFG = tempreg;
    }
}

/**
*\*\name    DMAMUX_GetGenRequestNumber.
*\*\fun     Get the number of DMA request that will be autorized after a generation event.
*\*\param   DMAMUXx (The input parameters must be the following values):
*\*\          - DMAMUX1_ID
*\*\          - DMAMUX2_ID
*\*\param   RequestGenChannel (The input parameters must be the following values):
*\*\          - DMAMUX_REQ_GEN_0
*\*\          - DMAMUX_REQ_GEN_1
*\*\          - DMAMUX_REQ_GEN_2
*\*\          - DMAMUX_REQ_GEN_3
*\*\          - DMAMUX_REQ_GEN_4
*\*\          - DMAMUX_REQ_GEN_5
*\*\          - DMAMUX_REQ_GEN_6
*\*\          - DMAMUX_REQ_GEN_7
*\*\          - DMAMUX_REQ_GEN_8
*\*\          - DMAMUX_REQ_GEN_9
*\*\          - DMAMUX_REQ_GEN_10
*\*\          - DMAMUX_REQ_GEN_11
*\*\          - DMAMUX_REQ_GEN_12
*\*\          - DMAMUX_REQ_GEN_13
*\*\          - DMAMUX_REQ_GEN_14
*\*\          - DMAMUX_REQ_GEN_15
*\*\return  Between Min_Data = 1 and Max_Data = 32
*\*\note    If DMAMUXx is DMAMUX1_ID, the maximum value of the RequestGenChannel is DMAMUX_REQ_GEN_7
**/
uint32_t DMAMUX_GetGenRequestNumber(DMAMUX_ID DMAMUXx, uint32_t RequestGenChannel)
{
    uint32_t tempreg;

    if(DMAMUXx == DMAMUX1_ID)
    {
        tempreg = ((DMAMUX_RequestGen_TypeDef *)(DMAMUX1_BASE + DMAMUX_REQ_GEN_OFFSET + (DMAMUX_CHCTRL_SIZE * RequestGenChannel)))->CHCFG;
    }
    else
    {
        tempreg = ((DMAMUX_RequestGen_TypeDef *)(DMAMUX2_MDMA_BASE + DMAMUX_REQ_GEN_OFFSET + (DMAMUX_CHCTRL_SIZE * RequestGenChannel)))->CHCFG;
    }

    return (uint32_t)(((tempreg & DMAMUX_REQ_GEN_NUMBER_MASK) >> DMAMUX_REQ_GEN_NUMBER_Pos) + 1);
}

/**
*\*\name    DMAMUX_SetRequestSignalID.
*\*\fun     Set DMAMUX external Request Signal ID on DMAMUX Request Generation Trigger Event Channel x.
*\*\param   DMAMUXx (The input parameters must be the following values):
*\*\          - DMAMUX1_ID
*\*\          - DMAMUX2_ID
*\*\param   RequestGenChannel (The input parameters must be the following values):
*\*\          - DMAMUX_REQ_GEN_0
*\*\          - DMAMUX_REQ_GEN_1
*\*\          - DMAMUX_REQ_GEN_2
*\*\          - DMAMUX_REQ_GEN_3
*\*\          - DMAMUX_REQ_GEN_4
*\*\          - DMAMUX_REQ_GEN_5
*\*\          - DMAMUX_REQ_GEN_6
*\*\          - DMAMUX_REQ_GEN_7
*\*\          - DMAMUX_REQ_GEN_8
*\*\          - DMAMUX_REQ_GEN_9
*\*\          - DMAMUX_REQ_GEN_10
*\*\          - DMAMUX_REQ_GEN_11
*\*\          - DMAMUX_REQ_GEN_12
*\*\          - DMAMUX_REQ_GEN_13
*\*\          - DMAMUX_REQ_GEN_14
*\*\          - DMAMUX_REQ_GEN_15
*\*\param   RequestSignalID (The input parameters must be the following values):
*\*\          - DMAMUX1_REQ_GEN_DMAMUX1_EVT0_EVT7
*\*\          - DMAMUX1_REQ_GEN_DMAMUX1_EVT8_EVT5
*\*\          - DMAMUX1_REQ_GEN_DMAMUX1_EVT16_EVT23
*\*\          - DMAMUX1_REQ_GEN_LPTIM4_OUT
*\*\          - DMAMUX1_REQ_GEN_LPTIM3_OUT
*\*\          - DMAMUX1_REQ_GEN_LPTIM2_OUT
*\*\          - DMAMUX1_REQ_GEN_LPTIM1_OUT
*\*\          - DMAMUX1_REQ_GEN_EXTI0
*\*\          - DMAMUX1_REQ_GEN_CANFD1_INT0
*\*\          - DMAMUX1_REQ_GEN_CANFD2_INT0
*\*\          - DMAMUX1_REQ_GEN_CANFD3_INT0
*\*\          - DMAMUX1_REQ_GEN_CANFD4_INT0
*\*\          - DMAMUX1_REQ_GEN_CANFD5_INT0
*\*\          - DMAMUX1_REQ_GEN_CANFD6_INT0
*\*\          - DMAMUX1_REQ_GEN_CANFD7_INT0
*\*\          - DMAMUX1_REQ_GEN_CANFD8_INT0
*\*\          - DMAMUX1_REQ_GEN_LPTIM5_OUT
*\*\          - DMAMUX1_REQ_GEN_ESC_INT
*\*\          - DMAMUX1_REQ_GEN_CANFD1_INT1
*\*\          - DMAMUX1_REQ_GEN_CANFD2_INT1
*\*\          - DMAMUX1_REQ_GEN_CANFD3_INT1
*\*\          - DMAMUX1_REQ_GEN_CANFD4_INT1
*\*\          - DMAMUX1_REQ_GEN_CANFD5_INT1
*\*\          - DMAMUX1_REQ_GEN_CANFD6_INT1
*\*\          - DMAMUX1_REQ_GEN_CANFD7_INT1
*\*\          - DMAMUX1_REQ_GEN_CANFD8_INT1
*\*\          - DMAMUX2_DMA1_CH0_TC_INT
*\*\          - DMAMUX2_DMA1_CH1_TC_INT
*\*\          - DMAMUX2_DMA1_CH2_TC_INT
*\*\          - DMAMUX2_DMA1_CH3_TC_INT
*\*\          - DMAMUX2_DMA1_CH4_TC_INT
*\*\          - DMAMUX2_DMA1_CH5_TC_INT
*\*\          - DMAMUX2_DMA1_CH6_TC_INT
*\*\          - DMAMUX2_DMA1_CH7_TC_INT
*\*\          - DMAMUX2_DMA2_CH0_TC_INT
*\*\          - DMAMUX2_DMA2_CH1_TC_INT
*\*\          - DMAMUX2_DMA2_CH2_TC_INT
*\*\          - DMAMUX2_DMA2_CH3_TC_INT
*\*\          - DMAMUX2_DMA2_CH4_TC_INT
*\*\          - DMAMUX2_DMA2_CH5_TC_INT
*\*\          - DMAMUX2_DMA2_CH6_TC_INT
*\*\          - DMAMUX2_DMA2_CH7_TC_INT
*\*\          - DMAMUX2_DMA3_CH0_TC_INT
*\*\          - DMAMUX2_DMA3_CH1_TC_INT
*\*\          - DMAMUX2_DMA3_CH2_TC_INT
*\*\          - DMAMUX2_DMA3_CH3_TC_INT
*\*\          - DMAMUX2_DMA3_CH4_TC_INT
*\*\          - DMAMUX2_DMA3_CH5_TC_INT
*\*\          - DMAMUX2_DMA3_CH6_TC_INT
*\*\          - DMAMUX2_DMA3_CH7_TC_INT
*\*\          - DMAMUX2_REQ_GEN_DMAMUX2_LCDC_INT
*\*\          - DMAMUX2_REQ_GEN_DMAMUX2_GPU_INT
*\*\          - DMAMUX2_REQ_GEN_DMAMUX2_JEPG_SGDMA_H2P_INT
*\*\          - DMAMUX2_REQ_GEN_DMAMUX2_JEPG_SGDMA_P2H_INT
*\*\          - DMAMUX2_REQ_GEN_DMAMUX2_MIPI_INT
*\*\          - DMAMUX2_REQ_GEN_DMAMUX2_USB1_INT
*\*\          - DMAMUX2_REQ_GEN_DMAMUX2_USB2_INT
*\*\          - DMAMUX2_REQ_GEN_SDMMC1_INT
*\*\          - DMAMUX2_REQ_GEN_SDMMC2_INT
*\*\          - DMAMUX2_REQ_GEN_DVP1_INT
*\*\          - DMAMUX2_REQ_GEN_DVP2_INT
*\*\          - DMAMUX2_REQ_GEN_EHT1_INT
*\*\          - DMAMUX2_REQ_GEN_EHT2_INT
*\*\          - DMAMUX2_REQ_GEN_SDPU_INT
*\*\return  none
*\*\note    If DMAMUXx is DMAMUX1_ID, the maximum value of the RequestGenChannel is DMAMUX_REQ_GEN_7
**/
void DMAMUX_SetRequestSignalID(DMAMUX_ID DMAMUXx, uint32_t RequestGenChannel, uint32_t RequestSignalID)
{
    uint32_t tempreg;

    if(DMAMUXx == DMAMUX1_ID)
    {
        tempreg = ((DMAMUX_RequestGen_TypeDef *)(DMAMUX1_BASE + DMAMUX_REQ_GEN_OFFSET + (DMAMUX_CHCTRL_SIZE * (RequestGenChannel))))->CHCFG;
        tempreg &= (~DMAMUX_REQ_GEN_SIG_ID_MASK);
        tempreg |= (RequestSignalID);
        ((DMAMUX_RequestGen_TypeDef *)(DMAMUX1_BASE + DMAMUX_REQ_GEN_OFFSET + (DMAMUX_CHCTRL_SIZE * (RequestGenChannel))))->CHCFG = tempreg;
    }
    else
    {
        tempreg = ((DMAMUX_RequestGen_TypeDef *)(DMAMUX2_MDMA_BASE + DMAMUX_REQ_GEN_OFFSET + (DMAMUX_CHCTRL_SIZE * (RequestGenChannel))))->CHCFG;
        tempreg &= (~DMAMUX_REQ_GEN_SIG_ID_MASK);
        tempreg |= (RequestSignalID);
        ((DMAMUX_RequestGen_TypeDef *)(DMAMUX2_MDMA_BASE + DMAMUX_REQ_GEN_OFFSET + (DMAMUX_CHCTRL_SIZE * (RequestGenChannel))))->CHCFG = tempreg;
    }
}

/**
*\*\name    DMAMUX_GetRequestSignalID.
*\*\fun     Get DMAMUX external Request Signal ID set on DMAMUX Channel x.
*\*\param   DMAMUXx (The input parameters must be the following values):
*\*\          - DMAMUX1_ID
*\*\          - DMAMUX2_ID
*\*\param   RequestGenChannel (The input parameters must be the following values):
*\*\          - DMAMUX_REQ_GEN_0
*\*\          - DMAMUX_REQ_GEN_1
*\*\          - DMAMUX_REQ_GEN_2
*\*\          - DMAMUX_REQ_GEN_3
*\*\          - DMAMUX_REQ_GEN_4
*\*\          - DMAMUX_REQ_GEN_5
*\*\          - DMAMUX_REQ_GEN_6
*\*\          - DMAMUX_REQ_GEN_7
*\*\          - DMAMUX_REQ_GEN_8
*\*\          - DMAMUX_REQ_GEN_9
*\*\          - DMAMUX_REQ_GEN_10
*\*\          - DMAMUX_REQ_GEN_11
*\*\          - DMAMUX_REQ_GEN_12
*\*\          - DMAMUX_REQ_GEN_13
*\*\          - DMAMUX_REQ_GEN_14
*\*\          - DMAMUX_REQ_GEN_15
*\*\return Returned value can be one of the following values:
*\*\          - DMAMUX1_REQ_GEN_DMAMUX1_EVT0_EVT7
*\*\          - DMAMUX1_REQ_GEN_DMAMUX1_EVT8_EVT5
*\*\          - DMAMUX1_REQ_GEN_DMAMUX1_EVT16_EVT23
*\*\          - DMAMUX1_REQ_GEN_LPTIM4_OUT
*\*\          - DMAMUX1_REQ_GEN_LPTIM3_OUT
*\*\          - DMAMUX1_REQ_GEN_LPTIM2_OUT
*\*\          - DMAMUX1_REQ_GEN_LPTIM1_OUT
*\*\          - DMAMUX1_REQ_GEN_EXTI0
*\*\          - DMAMUX1_REQ_GEN_CANFD1_INT0
*\*\          - DMAMUX1_REQ_GEN_CANFD2_INT0
*\*\          - DMAMUX1_REQ_GEN_CANFD3_INT0
*\*\          - DMAMUX1_REQ_GEN_CANFD4_INT0
*\*\          - DMAMUX1_REQ_GEN_CANFD5_INT0
*\*\          - DMAMUX1_REQ_GEN_CANFD6_INT0
*\*\          - DMAMUX1_REQ_GEN_CANFD7_INT0
*\*\          - DMAMUX1_REQ_GEN_CANFD8_INT0
*\*\          - DMAMUX1_REQ_GEN_LPTIM5_OUT
*\*\          - DMAMUX1_REQ_GEN_ESC_INT
*\*\          - DMAMUX1_REQ_GEN_CANFD1_INT1
*\*\          - DMAMUX1_REQ_GEN_CANFD2_INT1
*\*\          - DMAMUX1_REQ_GEN_CANFD3_INT1
*\*\          - DMAMUX1_REQ_GEN_CANFD4_INT1
*\*\          - DMAMUX1_REQ_GEN_CANFD5_INT1
*\*\          - DMAMUX1_REQ_GEN_CANFD6_INT1
*\*\          - DMAMUX1_REQ_GEN_CANFD7_INT1
*\*\          - DMAMUX1_REQ_GEN_CANFD8_INT1
*\*\          - DMAMUX2_DMA1_CH0_TC_INT
*\*\          - DMAMUX2_DMA1_CH1_TC_INT
*\*\          - DMAMUX2_DMA1_CH2_TC_INT
*\*\          - DMAMUX2_DMA1_CH3_TC_INT
*\*\          - DMAMUX2_DMA1_CH4_TC_INT
*\*\          - DMAMUX2_DMA1_CH5_TC_INT
*\*\          - DMAMUX2_DMA1_CH6_TC_INT
*\*\          - DMAMUX2_DMA1_CH7_TC_INT
*\*\          - DMAMUX2_DMA2_CH0_TC_INT
*\*\          - DMAMUX2_DMA2_CH1_TC_INT
*\*\          - DMAMUX2_DMA2_CH2_TC_INT
*\*\          - DMAMUX2_DMA2_CH3_TC_INT
*\*\          - DMAMUX2_DMA2_CH4_TC_INT
*\*\          - DMAMUX2_DMA2_CH5_TC_INT
*\*\          - DMAMUX2_DMA2_CH6_TC_INT
*\*\          - DMAMUX2_DMA2_CH7_TC_INT
*\*\          - DMAMUX2_DMA3_CH0_TC_INT
*\*\          - DMAMUX2_DMA3_CH1_TC_INT
*\*\          - DMAMUX2_DMA3_CH2_TC_INT
*\*\          - DMAMUX2_DMA3_CH3_TC_INT
*\*\          - DMAMUX2_DMA3_CH4_TC_INT
*\*\          - DMAMUX2_DMA3_CH5_TC_INT
*\*\          - DMAMUX2_DMA3_CH6_TC_INT
*\*\          - DMAMUX2_DMA3_CH7_TC_INT
*\*\          - DMAMUX2_REQ_GEN_DMAMUX2_LCDC_INT
*\*\          - DMAMUX2_REQ_GEN_DMAMUX2_GPU_INT
*\*\          - DMAMUX2_REQ_GEN_DMAMUX2_JEPG_SGDMA_H2P_INT
*\*\          - DMAMUX2_REQ_GEN_DMAMUX2_JEPG_SGDMA_P2H_INT
*\*\          - DMAMUX2_REQ_GEN_DMAMUX2_MIPI_INT
*\*\          - DMAMUX2_REQ_GEN_DMAMUX2_USB1_INT
*\*\          - DMAMUX2_REQ_GEN_DMAMUX2_USB2_INT
*\*\          - DMAMUX2_REQ_GEN_SDMMC1_INT
*\*\          - DMAMUX2_REQ_GEN_SDMMC2_INT
*\*\          - DMAMUX2_REQ_GEN_DVP1_INT
*\*\          - DMAMUX2_REQ_GEN_DVP2_INT
*\*\          - DMAMUX2_REQ_GEN_EHT1_INT
*\*\          - DMAMUX2_REQ_GEN_EHT2_INT
*\*\          - DMAMUX2_REQ_GEN_SDPU_INT
*\*\note    If DMAMUXx is DMAMUX1_ID, the maximum value of the RequestGenChannel is DMAMUX_REQ_GEN_7
**/
uint32_t DMAMUX_GetRequestSignalID(DMAMUX_ID DMAMUXx, uint32_t RequestGenChannel)
{
    uint32_t tempreg;

    if(DMAMUXx == DMAMUX1_ID)
    {
        tempreg = ((DMAMUX_RequestGen_TypeDef *)(DMAMUX1_BASE + DMAMUX_REQ_GEN_OFFSET + (DMAMUX_CHCTRL_SIZE * (RequestGenChannel))))->CHCFG;
    }
    else
    {
        tempreg = ((DMAMUX_RequestGen_TypeDef *)(DMAMUX2_MDMA_BASE + DMAMUX_REQ_GEN_OFFSET + (DMAMUX_CHCTRL_SIZE * (RequestGenChannel))))->CHCFG;
    }

    return (uint32_t)(tempreg & DMAMUX_REQ_GEN_SIG_ID_MASK);
}

/**
*\*\name    DMAMUX_GetSynOverrunStatus.
*\*\fun     Get Synchronization Event Overrun Flag of Channel x.
*\*\param   DMAMUXx (The input parameters must be the following values):
*\*\          - DMAMUX1_ID
*\*\          - DMAMUX2_ID
*\*\param   Channel (The input parameters must be the following values):
*\*\          - DMAMUX_CHANNEL_0
*\*\          - DMAMUX_CHANNEL_1
*\*\          - DMAMUX_CHANNEL_2
*\*\          - DMAMUX_CHANNEL_3
*\*\          - DMAMUX_CHANNEL_4
*\*\          - DMAMUX_CHANNEL_5
*\*\          - DMAMUX_CHANNEL_6
*\*\          - DMAMUX_CHANNEL_7
*\*\          - DMAMUX_CHANNEL_8
*\*\          - DMAMUX_CHANNEL_9
*\*\          - DMAMUX_CHANNEL_10
*\*\          - DMAMUX_CHANNEL_11
*\*\          - DMAMUX_CHANNEL_12
*\*\          - DMAMUX_CHANNEL_13
*\*\          - DMAMUX_CHANNEL_14
*\*\          - DMAMUX_CHANNEL_15
*\*\          - DMAMUX_CHANNEL_16
*\*\          - DMAMUX_CHANNEL_17
*\*\          - DMAMUX_CHANNEL_18
*\*\          - DMAMUX_CHANNEL_19
*\*\          - DMAMUX_CHANNEL_20
*\*\          - DMAMUX_CHANNEL_21
*\*\          - DMAMUX_CHANNEL_22
*\*\          - DMAMUX_CHANNEL_23
*\*\return  FlagStatus:
*\*\          - SET
*\*\          - RESET
*\*\note    If DMAMUXx is DMAMUX2_ID, the maximum value of the Channel is DMAMUX_CHANNEL_15
**/
FlagStatus DMAMUX_GetSynOverrunStatus(DMAMUX_ID DMAMUXx, uint32_t Channel)
{
    uint32_t tempreg;

    if(DMAMUXx == DMAMUX1_ID)
    {
        tempreg = ((DMAMUX_ChannelStatus_TypeDef *)(DMAMUX1_BASE + DMAMUX_CH_STATUS_OFFSET + (DMAMUX_CHCTRL_SIZE * (Channel))))->STS;
    }
    else
    {
        tempreg = ((DMAMUX_ChannelStatus_TypeDef *)(DMAMUX2_MDMA_BASE + DMAMUX_CH_STATUS_OFFSET + (DMAMUX_CHCTRL_SIZE * (Channel))))->STS;
    }

    return ((tempreg & (1 << Channel)) != 0U) ? SET : RESET;
}


/**
*\*\name    DMAMUX_GetTrigOverrunStatus.
*\*\fun     Get Request Generator x Trigger Event Overrun Flag.
*\*\param   DMAMUXx (The input parameters must be the following values):
*\*\          - DMAMUX1_ID
*\*\          - DMAMUX2_ID
*\*\param   RequestGenChannel (The input parameters must be the following values):
*\*\          - DMAMUX_REQ_GEN_0
*\*\          - DMAMUX_REQ_GEN_1
*\*\          - DMAMUX_REQ_GEN_2
*\*\          - DMAMUX_REQ_GEN_3
*\*\          - DMAMUX_REQ_GEN_4
*\*\          - DMAMUX_REQ_GEN_5
*\*\          - DMAMUX_REQ_GEN_6
*\*\          - DMAMUX_REQ_GEN_7
*\*\          - DMAMUX_REQ_GEN_8
*\*\          - DMAMUX_REQ_GEN_9
*\*\          - DMAMUX_REQ_GEN_10
*\*\          - DMAMUX_REQ_GEN_11
*\*\          - DMAMUX_REQ_GEN_12
*\*\          - DMAMUX_REQ_GEN_13
*\*\          - DMAMUX_REQ_GEN_14
*\*\          - DMAMUX_REQ_GEN_15
*\*\return  FlagStatus:
*\*\          - SET
*\*\          - RESET
*\*\note    If DMAMUXx is DMAMUX1_ID, the maximum value of the RequestGenChannel is DMAMUX_REQ_GEN_7
**/
FlagStatus DMAMUX_GetTrigOverrunStatus(DMAMUX_ID DMAMUXx, uint32_t RequestGenChannel)
{
    uint32_t tempreg;

    if(DMAMUXx == DMAMUX1_ID)
    {
        tempreg = ((DMAMUX_RequestGenStatus_TypeDef *)(DMAMUX1_BASE + DMAMUX_REQ_GEN_STATUS_OFFSET + (DMAMUX_CHCTRL_SIZE * (RequestGenChannel))))->RGSTS;
    }
    else
    {
        tempreg = ((DMAMUX_RequestGenStatus_TypeDef *)(DMAMUX2_MDMA_BASE + DMAMUX_REQ_GEN_STATUS_OFFSET + (DMAMUX_CHCTRL_SIZE * (RequestGenChannel))))->RGSTS;
    }

    return ((tempreg & (1 << RequestGenChannel)) != 0U) ? SET : RESET;
}


/**
*\*\name    DMAMUX_ClearSynOverrunStatus.
*\*\fun     Clear Synchronization Event Overrun Flag of Channel x.
*\*\param   DMAMUXx (The input parameters must be the following values):
*\*\          - DMAMUX1_ID
*\*\          - DMAMUX2_ID
*\*\param   Channel (The input parameters must be the following values):
*\*\          - DMAMUX_CHANNEL_0
*\*\          - DMAMUX_CHANNEL_1
*\*\          - DMAMUX_CHANNEL_2
*\*\          - DMAMUX_CHANNEL_3
*\*\          - DMAMUX_CHANNEL_4
*\*\          - DMAMUX_CHANNEL_5
*\*\          - DMAMUX_CHANNEL_6
*\*\          - DMAMUX_CHANNEL_7
*\*\          - DMAMUX_CHANNEL_8
*\*\          - DMAMUX_CHANNEL_9
*\*\          - DMAMUX_CHANNEL_10
*\*\          - DMAMUX_CHANNEL_11
*\*\          - DMAMUX_CHANNEL_12
*\*\          - DMAMUX_CHANNEL_13
*\*\          - DMAMUX_CHANNEL_14
*\*\          - DMAMUX_CHANNEL_15
*\*\          - DMAMUX_CHANNEL_16
*\*\          - DMAMUX_CHANNEL_17
*\*\          - DMAMUX_CHANNEL_18
*\*\          - DMAMUX_CHANNEL_19
*\*\          - DMAMUX_CHANNEL_20
*\*\          - DMAMUX_CHANNEL_21
*\*\          - DMAMUX_CHANNEL_22
*\*\          - DMAMUX_CHANNEL_23
*\*\return  none
*\*\note    If DMAMUXx is DMAMUX2_ID, the maximum value of the Channel is DMAMUX_CHANNEL_15
**/
void DMAMUX_ClearSynOverrunStatus(DMAMUX_ID DMAMUXx, uint32_t Channel)
{
    if(DMAMUXx == DMAMUX1_ID)
    {
        ((DMAMUX_ChannelStatus_TypeDef *)(DMAMUX1_BASE + DMAMUX_CH_STATUS_OFFSET + (DMAMUX_CHCTRL_SIZE * (Channel))))->STS |= (uint32_t)(1 << Channel);
    }
    else
    {
        ((DMAMUX_ChannelStatus_TypeDef *)(DMAMUX2_MDMA_BASE + DMAMUX_CH_STATUS_OFFSET + (DMAMUX_CHCTRL_SIZE * (Channel))))->STS |= (uint32_t)(1 << Channel);;
    }
}


/**
*\*\name    DMAMUX_ClearTrigOverrunStatus.
*\*\fun     Clear Request Generator x Trigger Event Overrun Flag.
*\*\param   DMAMUXx (The input parameters must be the following values):
*\*\          - DMAMUX1_ID
*\*\          - DMAMUX2_ID
*\*\param   RequestGenChannel (The input parameters must be the following values):
*\*\          - DMAMUX_REQ_GEN_0
*\*\          - DMAMUX_REQ_GEN_1
*\*\          - DMAMUX_REQ_GEN_2
*\*\          - DMAMUX_REQ_GEN_3
*\*\          - DMAMUX_REQ_GEN_4
*\*\          - DMAMUX_REQ_GEN_5
*\*\          - DMAMUX_REQ_GEN_6
*\*\          - DMAMUX_REQ_GEN_7
*\*\          - DMAMUX_REQ_GEN_8
*\*\          - DMAMUX_REQ_GEN_9
*\*\          - DMAMUX_REQ_GEN_10
*\*\          - DMAMUX_REQ_GEN_11
*\*\          - DMAMUX_REQ_GEN_12
*\*\          - DMAMUX_REQ_GEN_13
*\*\          - DMAMUX_REQ_GEN_14
*\*\          - DMAMUX_REQ_GEN_15
*\*\return  none:
*\*\note    If DMAMUXx is DMAMUX1_ID, the maximum value of the RequestGenChannel is DMAMUX_REQ_GEN_7
**/
void DMAMUX_ClearTrigOverrunStatus(DMAMUX_ID DMAMUXx, uint32_t RequestGenChannel)
{
    if(DMAMUXx == DMAMUX1_ID)
    {
        ((DMAMUX_RequestGenStatus_TypeDef *)(DMAMUX1_BASE + DMAMUX_REQ_GEN_STATUS_OFFSET + (DMAMUX_CHCTRL_SIZE * (RequestGenChannel))))->RGCLR |= (uint32_t)(1 << RequestGenChannel);
    }
    else
    {
        ((DMAMUX_RequestGenStatus_TypeDef *)(DMAMUX2_MDMA_BASE + DMAMUX_REQ_GEN_STATUS_OFFSET + (DMAMUX_CHCTRL_SIZE * (RequestGenChannel))))->RGCLR |= (uint32_t)(1 << RequestGenChannel);;
    }
}


/**
*\*\name    DMAMUX_EnableSynEventOverrunInt.
*\*\fun     Enable or disable the Synchronization Event Overrun Interrupt on DMAMUX channel x.
*\*\param   DMAMUXx (The input parameters must be the following values):
*\*\          - DMAMUX1_ID
*\*\          - DMAMUX2_ID
*\*\param   Channel (The input parameters must be the following values):
*\*\          - DMAMUX_CHANNEL_0
*\*\          - DMAMUX_CHANNEL_1
*\*\          - DMAMUX_CHANNEL_2
*\*\          - DMAMUX_CHANNEL_3
*\*\          - DMAMUX_CHANNEL_4
*\*\          - DMAMUX_CHANNEL_5
*\*\          - DMAMUX_CHANNEL_6
*\*\          - DMAMUX_CHANNEL_7
*\*\          - DMAMUX_CHANNEL_8
*\*\          - DMAMUX_CHANNEL_9
*\*\          - DMAMUX_CHANNEL_10
*\*\          - DMAMUX_CHANNEL_11
*\*\          - DMAMUX_CHANNEL_12
*\*\          - DMAMUX_CHANNEL_13
*\*\          - DMAMUX_CHANNEL_14
*\*\          - DMAMUX_CHANNEL_15
*\*\          - DMAMUX_CHANNEL_16
*\*\          - DMAMUX_CHANNEL_17
*\*\          - DMAMUX_CHANNEL_18
*\*\          - DMAMUX_CHANNEL_19
*\*\          - DMAMUX_CHANNEL_20
*\*\          - DMAMUX_CHANNEL_21
*\*\          - DMAMUX_CHANNEL_22
*\*\          - DMAMUX_CHANNEL_23
*\*\param   Cmd :
*\*\          - ENABLE
*\*\          - DISABLE
*\*\return  none
*\*\note    If DMAMUXx is DMAMUX2_ID, the maximum value of the Channel is DMAMUX_CHANNEL_15
**/
void DMAMUX_EnableSynEventOverrunInt(DMAMUX_ID DMAMUXx, uint32_t Channel, FunctionalState Cmd)
{
    if(DMAMUXx == DMAMUX1_ID)
    {
        if(Cmd == ENABLE)
        {
            ((DMAMUX_Channel_TypeDef *)(DMAMUX1_BASE + (DMAMUX_CHCTRL_SIZE * (Channel))))->CHCTRL |= DMAMUX_SYNOVERRUN_INTEN_MASK;
        }
        else
        {
            ((DMAMUX_Channel_TypeDef *)(DMAMUX1_BASE + (DMAMUX_CHCTRL_SIZE * (Channel))))->CHCTRL &= (~DMAMUX_SYNOVERRUN_INTEN_MASK);
        }
    }
    else
    {
        if(Cmd == ENABLE)
        {
            ((DMAMUX_Channel_TypeDef *)(DMAMUX2_MDMA_BASE + (DMAMUX_CHCTRL_SIZE * (Channel))))->CHCTRL |= DMAMUX_SYNOVERRUN_INTEN_MASK;
        }
        else
        {
            ((DMAMUX_Channel_TypeDef *)(DMAMUX2_MDMA_BASE + (DMAMUX_CHCTRL_SIZE * (Channel))))->CHCTRL &= (~DMAMUX_SYNOVERRUN_INTEN_MASK);
        }
    }
}

/**
*\*\name    DMAMUX_EnableTrigOverrunInt.
*\*\fun     Enable or disable the Request Generation Trigger Event Overrun Interrupt on DMAMUX channel x.
*\*\param   DMAMUXx (The input parameters must be the following values):
*\*\          - DMAMUX1_ID
*\*\          - DMAMUX2_ID
*\*\param   RequestGenChannel (The input parameters must be the following values):
*\*\          - DMAMUX_REQ_GEN_0
*\*\          - DMAMUX_REQ_GEN_1
*\*\          - DMAMUX_REQ_GEN_2
*\*\          - DMAMUX_REQ_GEN_3
*\*\          - DMAMUX_REQ_GEN_4
*\*\          - DMAMUX_REQ_GEN_5
*\*\          - DMAMUX_REQ_GEN_6
*\*\          - DMAMUX_REQ_GEN_7
*\*\          - DMAMUX_REQ_GEN_8
*\*\          - DMAMUX_REQ_GEN_9
*\*\          - DMAMUX_REQ_GEN_10
*\*\          - DMAMUX_REQ_GEN_11
*\*\          - DMAMUX_REQ_GEN_12
*\*\          - DMAMUX_REQ_GEN_13
*\*\          - DMAMUX_REQ_GEN_14
*\*\          - DMAMUX_REQ_GEN_15
*\*\param   Cmd :
*\*\          - ENABLE
*\*\          - DISABLE
*\*\return  none
*\*\note    If DMAMUXx is DMAMUX1_ID, the maximum value of the RequestGenChannel is DMAMUX_REQ_GEN_7
**/
void DMAMUX_EnableTrigOverrunInt(DMAMUX_ID DMAMUXx, uint32_t RequestGenChannel, FunctionalState Cmd)
{
    if(DMAMUXx == DMAMUX1_ID)
    {
        if(Cmd == ENABLE)
        {
            ((DMAMUX_RequestGen_TypeDef *)(DMAMUX1_BASE + DMAMUX_REQ_GEN_OFFSET + (DMAMUX_CHCTRL_SIZE * (RequestGenChannel))))->CHCFG |= DMAMUX_TRIGOVERRUN_INTEN_MASK;
        }
        else
        {
            ((DMAMUX_RequestGen_TypeDef *)(DMAMUX1_BASE + DMAMUX_REQ_GEN_OFFSET + (DMAMUX_CHCTRL_SIZE * (RequestGenChannel))))->CHCFG &= (~DMAMUX_TRIGOVERRUN_INTEN_MASK);
        }
    }
    else
    {
        if(Cmd == ENABLE)
        {
            ((DMAMUX_RequestGen_TypeDef *)(DMAMUX2_MDMA_BASE + DMAMUX_REQ_GEN_OFFSET + (DMAMUX_CHCTRL_SIZE * (RequestGenChannel))))->CHCFG |= DMAMUX_TRIGOVERRUN_INTEN_MASK;
        }
        else
        {
            ((DMAMUX_RequestGen_TypeDef *)(DMAMUX2_MDMA_BASE + DMAMUX_REQ_GEN_OFFSET + (DMAMUX_CHCTRL_SIZE * (RequestGenChannel))))->CHCFG &= (~DMAMUX_TRIGOVERRUN_INTEN_MASK);
        }
    }
}

