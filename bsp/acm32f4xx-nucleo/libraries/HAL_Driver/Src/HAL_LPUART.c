/*
  ******************************************************************************
  * @file    HAL_LPUART.c
  * @version V1.0.0
  * @date    2020
  * @brief   LPUART HAL module driver.
  *          This file provides firmware functions to manage the following
  *          functionalities of the Universal Asynchronous Receiver Transmitter Peripheral (LPUART).
  *           @ Initialization and de-initialization functions
  *           @ IO operation functions
  *           @ Peripheral Control functions
  ******************************************************************************
*/
#include "ACM32Fxx_HAL.h"

/*********************************************************************************
* Function    : HAL_LPUART_IRQHander
* Description : LPUART IRQHander 
* Input       : 
* Outpu       : 
* Author      : CWT                         Data : 2020Äê
**********************************************************************************/ 
void HAL_LPUART_IRQHander(LPUART_HandleTypeDef *hlpuart)  
{
    while ( (hlpuart->Instance->SR) & (1U << LPUART_SR_RX_INDEX))        
    {
        if(hlpuart->rx_read_index != (((hlpuart->rx_write_index) + 1)% (hlpuart->rx_buffer_size) ) )     
        {
            hlpuart->rx_buffer[hlpuart->rx_write_index] = hlpuart->Instance->RXDR;   
            hlpuart->rx_write_index = ((hlpuart->rx_write_index + 1)%(hlpuart->rx_buffer_size) );        
        }
        else
        {
            hlpuart->Instance->SR = (1U << LPUART_SR_RX_INDEX);  // buffer overflow  
            return;  
        }
    }
}
/************************************************************************
 * function   : HAL_UART_Buffer_Init
 * Description: uart buffer initiation.  
 * input : 
 *         UART_HandleTypeDef *huart: pointer to uart handle structure
 * return: 0: FAIL; 1: SUCCESS 
 ************************************************************************/
HAL_StatusTypeDef HAL_LPUART_Buffer_Init(LPUART_HandleTypeDef *hlpuart) 
{
    if(0x00 == IS_LPUART_INSTANCE(hlpuart->Instance))   
    {
        return HAL_ERROR;  
    }
    hlpuart->rx_read_index = 0;
    hlpuart->rx_write_index = 0;
    hlpuart->tx_busy = 0;  
    return HAL_OK;  
}

/**********************************************************************************
 * function   : HAL_LPUART_MSPInit  
 * Description: UART MCU specific initiation, such as IO share, module clock, ...  
 * input : 
 *         UART_HandleTypeDef *huart: pointer to uart handle structure
 * return: 0: FAIL; 1: SUCCESS 
 ***************************************************************************************/ 
 
__weak void HAL_LPUART_MSPInit(LPUART_HandleTypeDef *hlpuart) 
{ 
    GPIO_InitTypeDef gpio_init; 

    System_Module_Reset(RST_LPUART); 
    gpio_init.Pin = GPIO_PIN_2|GPIO_PIN_3;  // TX PA2 RX PA3 
    gpio_init.Mode = GPIO_MODE_AF_PP;   
    gpio_init.Pull = GPIO_PULLUP;   
    gpio_init.Alternate = GPIO_FUNCTION_6;  
    HAL_GPIO_Init(GPIOA,&gpio_init);   
    System_Module_Enable(EN_LPUART);  
}

/*********************************************************************************
* Function    : HAL_LPUART_MspDeInit
* Description :	LPUART MSP De-Initialization 
*               This function frees the hardware resources used in this example:
*              - Disable the Peripheral's clock
*              - Revert GPIO configuration to their default state
* Input       : hcan : pointer to a CAN_HandleTypeDef structure that contains
*                      the configuration information for CAN module
* Output      : 
* Author      : CWT                         Data : 2020Äê
**********************************************************************************/
void HAL_LPUART_MspDeInit(LPUART_HandleTypeDef *hlpuart)
{
    GPIO_InitTypeDef GPIO_InitStructure;   	
    /* Initialization GPIO */
    /* // TX PA2    RX PA3 */
    HAL_GPIO_DeInit(GPIOA, GPIO_PIN_2);
    HAL_GPIO_DeInit(GPIOA, GPIO_PIN_3);
}
/**********************************************************************************
 * function   : HAL_LPUART_Set_Baud_Rate
 * Description: set uart module's baud rate. It should be set when UART is disabled. 
 * input : 
 *         UART_HandleTypeDef *huart: pointer to uart handle structure
 * return: 0: FAIL; 1: SUCCESS 
 ***************************************************************************************/ 
uint8_t HAL_LPUART_Set_Baud_Rate(LPUART_HandleTypeDef *hlpuart, uint32_t lpuart_clk, uint32_t baud_rate)
{
    uint32_t ibaud, fbaud, rxsamp;   

    if(0x00 == IS_LPUART_INSTANCE(hlpuart->Instance))   
    {
        return 0;  
    }
    ibaud = 2;
    fbaud = 0x952;   
    rxsamp = 1;    
    switch(lpuart_clk)  
    {
        case 32000:
        case 32768: 
        switch(baud_rate) 
        {
        case 9600:
        ibaud = 2;
        fbaud = 0x952; 
        break;

        case 4800: 
        ibaud = 5;
        fbaud = 0xefb;    
        break;

        case 2400: 
        ibaud = 12;
        fbaud = 0x6db;   
        break;

        case 1200: 
        ibaud = 26;
        fbaud = 0x492;   
        break;   
        default: 
        ibaud = 2;
        fbaud = 0x952; 
        break;  
        }
        rxsamp = ibaud >> 1;    
        break; 

        case 1875000:  // for ABP CLK=120M/2=60M  lpuart clk = 60M/32=1.875M
        switch(baud_rate) 
        {
            case 256000:
            ibaud = 6; 
            fbaud = 0x888; 
            break;

            case 115200:  
            ibaud = 15;  
            fbaud = 0x888; 
            break;
        }
        rxsamp = ibaud >> 1;    
        break; 
       
        default:  //  for ABP CLK=180M/2=90M  lpuart clk = 90M/32=2.8125M
        switch(baud_rate) 
        {
            case 256000:
            ibaud = 9;  //2.8125M/256000=10.984  ibaud=(10-1)
            fbaud = 0x7FE; // 0.984 *11=10
            break;

            case 115200:  
            ibaud = 23;  //2.8125M/115200=24.4140625  ibaud=(24-1)
            fbaud = 0x249; //0.4140625*11=4
            break;
        }
        rxsamp = ibaud >> 1;    
        break;  
    } 
    hlpuart->Instance->IBAUD = ibaud | (rxsamp << 8); 
    hlpuart->Instance->FBAUD = fbaud;  
    return 1;   
}

/************************************************************************
 * function   : HAL_LPUART_Config
 * Description: Configure UART module parameters, such as baudrate, parity, 
 *              stop bits, dataword. 
 * input : 
 *         UART_HandleTypeDef *huart: pointer to uart handle structure
 * return: 0: FAIL; 1: SUCCESS  
 ************************************************************************/
uint8_t HAL_LPUART_Config(LPUART_HandleTypeDef *hlpuart)  
{   
    volatile uint32_t temp_reg;
    if(0x00 == IS_LPUART_INSTANCE(hlpuart->Instance)) 
    {
        return 0;  
    }
    temp_reg = 1U << 7; // default value  
    temp_reg |= ((hlpuart->ConfigParam.WordLength << 4) | (hlpuart->ConfigParam.StopBits << 3));
    switch(hlpuart->ConfigParam.Parity)
    {
        case LPUART_PARITY_NONE:
        break;  // do nothing 

        case LPUART_PARITY_SELECT_ODD:
        case LPUART_PARITY_SELECT_EVEN:
        temp_reg |= (((hlpuart->ConfigParam.Parity - LPUART_PARITY_SELECT_ODD) << LPUART_EPS_INDEX) | (1 << LPUART_PEN_INDEX));    
        break;  

        case LPUART_PARITY_SELECT_ONE:
        case LPUART_PARITY_SELECT_ZERO: 
        temp_reg |= (((hlpuart->ConfigParam.Parity - LPUART_PARITY_SELECT_ONE) << LPUART_EPS_INDEX) | (1 << LPUART_SPS_INDEX) | (1 << LPUART_PEN_INDEX) );    
        break;
    }
    hlpuart->Instance->LCR = temp_reg;  
    return 1;  
}

/*********************************************************************************
* Function    : LPUART_Clock_Select
* Description : Select the LPUART clock. 
* Input       : lpuart_clk_src:Could be LPUART_CLOCK_SOURCE_RC32K        LPUART_CLOCK_SOURCE_XTAL       LPUART_CLOCK_SOURCE_PLL_DIV
* Outpu       : 
* Author      : CWT                         Data : 2020Äê
**********************************************************************************/ 
void LPUART_Clock_Select(uint8_t lpuart_clk_src)
{
    if (0 == lpuart_clk_src)
    {
        SCU->CCR2 &= (~(BIT13 | BIT14) );     // RC32K 
    }
    else if (1 == lpuart_clk_src) 
    {
        SCU->CCR2 = (SCU->CCR2 & (~(BIT13 | BIT14) )) | (BIT13);     // XTAL 
    }
    else
    {
        SCU->CCR2 = (SCU->CCR2 & (~(BIT11 | BIT12| BIT13 | BIT14) )) | (BIT11 | BIT12 | BIT14);  // pclk/32          
    }
}
/************************************************************************
 * function   : HAL_LPUART_Init
 * Description: uart initial with parameters. 
 * input : 
 *         UART_HandleTypeDef *huart: pointer to uart handle structure
 * return: 0: FAIL; 1: SUCCESS   
 ************************************************************************/
HAL_StatusTypeDef HAL_LPUART_Init(LPUART_HandleTypeDef *hlpuart) 
{  
    uint32_t lpuart_clock;
    if(0x00 == IS_LPUART_INSTANCE(hlpuart->Instance)) 
    {
        return HAL_ERROR;;  
    }

    HAL_LPUART_Buffer_Init(hlpuart);    
    /*reset module, configure tx and rx, enable module clock*/
    HAL_LPUART_MSPInit(hlpuart); 

    if (LPUART_CLOCK_SOURCE_RC32K == hlpuart->ConfigParam.ClockSrc)
    {
        lpuart_clock = 32000;  
        System_Module_Enable(EN_RTC); 
        System_Enable_Disable_RTC_Domain_Access(FUNC_ENABLE);
        System_Enable_RC32K(); 
        LPUART_Clock_Select(0);
    }
    else if (LPUART_CLOCK_SOURCE_XTAL == hlpuart->ConfigParam.ClockSrc)
    {
        lpuart_clock = 32768;  
        System_Module_Enable(EN_RTC); 
       System_Enable_Disable_RTC_Domain_Access(FUNC_ENABLE);
        System_Enable_XTAL();   
        LPUART_Clock_Select(1);
    }
    else
    {
        lpuart_clock = System_Get_APBClock()/32;      
        LPUART_Clock_Select(2);  
    }
    HAL_LPUART_Set_Baud_Rate(hlpuart, lpuart_clock, hlpuart->ConfigParam.BaudRate);    

    HAL_LPUART_Config(hlpuart);     

    hlpuart->Instance->SR = LPUART_SR_BITS_ALL;  
    hlpuart->Instance->IE = (1U << LPUART_IE_RX_INDEX);   
    hlpuart->Instance->CR = (1U << LPUART_CR_RXE_INDEX) | (1 << LPUART_CR_TXE_INDEX);  
    hlpuart->Instance->LCR=((hlpuart->StopWakeup.Wakeup_Source<<5)|(hlpuart->StopWakeup.Wakeup_Check<<7)); 
    hlpuart->Instance->ADDR=(hlpuart->StopWakeup.Wakeup_Addr);
    NVIC_ClearPendingIRQ(LPUART_IRQn);
    NVIC_EnableIRQ(LPUART_IRQn);  
    return HAL_OK;;  
}
HAL_StatusTypeDef HAL_LPUART_DeInit(LPUART_HandleTypeDef *hlpuart)
{
    /* Check  handle */
    if(!IS_LPUART_INSTANCE(hlpuart->Instance)) return HAL_ERROR;
    HAL_LPUART_MspDeInit(hlpuart);
    /* Disable LPUART clock */
    System_Module_Disable(EN_LPUART);
    /* Return function status */
    return HAL_OK;
}
/************************************************************************
 * function   : HAL_LPUART_Wait_TX_Done
 * Description: wait uart not busy 
 * input : 
 *         UART_HandleTypeDef *huart: pointer to uart handle structure
 * return: 0: FAIL; 1: SUCCESS   
 ************************************************************************/
HAL_StatusTypeDef HAL_LPUART_Wait_TX_Done(LPUART_HandleTypeDef *hlpuart) 
{   
    while (0 == (hlpuart->Instance->SR & (1 << LPUART_SR_TX_FINISH_INDEX) ) ) {};  
    hlpuart->Instance->SR = (1 << LPUART_SR_TX_FINISH_INDEX);     
    return HAL_OK;  
}  

void HAL_LPUART_Output(LPUART_HandleTypeDef *hlpuart, unsigned char c)     
{
    if ((hlpuart->Instance->SR) & (1U << LPUART_SR_TX_EMPTY_INDEX) )  
    {
        hlpuart->Instance->TXDR = c;  
    }

    HAL_LPUART_Wait_TX_Done(hlpuart);   
}

/************************************************************************
 * function   : uart_send_bytes
 * Description: uart send bytes
 * input :
 *         UINT32 uart_index: Serial port number 
 *         UINT8* buff: out buffer
 *         UINT32 length: buffer length
 * return: none
 ************************************************************************/
void HAL_LPUART_Send_Bytes(LPUART_HandleTypeDef *hlpuart, uint8_t *buff, uint32_t length)    
{
    uint32_t i;
    for (i = 0; i < length; i++)
    {
        HAL_LPUART_Output(hlpuart, *buff++);     
    }
}

/************************************************************************
 * function   : HAL_LPUART_Receive_Bytes_Timeout  
 * Description: uart receive bytes 
 * input : 
 *         UART_HandleTypeDef *huart: pointer to uart handle structure
 *         UINT8* buff: out buffer
 *         UINT32 length: buffer length 
 *         UINT32 ms: number of ms to delay one byte 
 * return: received bytes 
 ************************************************************************/
uint32_t HAL_LPUART_Receive_Bytes_Timeout(LPUART_HandleTypeDef *hlpuart, uint8_t * rxbuff, uint32_t length, uint32_t ms) 
{
    volatile uint32_t i, timeout, count;;    
    if(0x00 == IS_LPUART_INSTANCE(hlpuart->Instance)) 
    {
        return 0;  
    } 
    timeout = (System_Get_APBClock() >> 13) * ms;  
    count = timeout;  
    i = 0;
    while(i < length) 
    {
        if((hlpuart->rx_read_index) != (hlpuart->rx_write_index)) 
        {
            rxbuff[i] = hlpuart->rx_buffer[hlpuart->rx_read_index];  
            hlpuart->rx_read_index = (((hlpuart->rx_read_index) + 1)%(hlpuart->rx_buffer_size) );   
            count = timeout;   
            i++;
        }
        else
        {       
            if (0 == count)//timeout 
            {
                break;  
            }
            else
            {
                count--;  
            }
        }
    }
    return i; 
}     
/************************************************************************
 * function   : HAL_LPUART_Receive_Bytes
 * Description: LPUART receive bytes.
 * input : 
 *         UART_HandleTypeDef *huart: pointer to uart handle structure
 *         buff:receive data buff
 *         length:length of buff
 * return:length  
 ************************************************************************/
uint32_t HAL_LPUART_Receive_Bytes(LPUART_HandleTypeDef *hlpuart, uint8_t * rxbuff, uint32_t length) 
{
    volatile uint32_t i, ie_backup;       
    if(0x00 == IS_LPUART_INSTANCE(hlpuart->Instance)) 
    {
        return 0;  
    }
    ie_backup = hlpuart->Instance->IE;   
    hlpuart->Instance->IE = 0;  
    i = 0;
    while(i < length) 
    {
        if( (hlpuart->Instance->SR) & (1U << LPUART_SR_RX_INDEX) ) 
        {
            rxbuff[i] = hlpuart->Instance->RXDR; 
            i++; 
        }
    }
    hlpuart->Instance->IE = ie_backup;    
    return length; 
}   
/************************************************************************
 * function   : HAL_LPUART_DMA_Send_Bytes
 * Description: LPUART send bytes by DMA.
 * input : 
 *         UART_HandleTypeDef *huart: pointer to uart handle structure
 *         buff:send data buff
 *         length:length of buff
 * return:none  
 ************************************************************************/
void HAL_LPUART_DMA_Send_Bytes(LPUART_HandleTypeDef *hlpuart, uint8_t *buff, uint32_t length)    
{
    hlpuart->Instance->CR |= (1U << LPUART_CR_DMA_EN_INDEX);   
    hlpuart->tx_busy = 1;   
    HAL_DMA_Start_IT(hlpuart->dma_tx_handler, (uint32_t)buff, (uint32_t)&hlpuart->Instance->TXDR, length);   
 }   

/************************************************************************
 * function   : HAL_LPUART_Clear_Wakeup_Flags
 * Description: Clear the LPUART STOP wake up flag.
 * input : 
 *         UART_HandleTypeDef *huart: pointer to uart handle structure
 *         Wakeup_Bits:LPUART wakeup flag,could be: LPUART_WAKEUP_RX_BIT    LPUART_WAKEUP_MATCH_BIT    LPUART_WAKEUP_START_BIT
 * return:none  
 ************************************************************************/

void HAL_LPUART_Clear_Wakeup_Flags(LPUART_HandleTypeDef *hlpuart, uint32_t Wakeup_Bits)  
{
    hlpuart->Instance->SR = Wakeup_Bits;   
} 


