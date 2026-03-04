/**
 * @file main.c
 * @author N32cube
 */
  
 //!!!!!!!!!!!!!!!!NOTE!!!!!!!!!!!!!!!
 // Code cannot be added between /* NTFx CODE START xxxxx*/ and /* NTFx CODE END xxxxx*/

 /* NTFx CODE START Include*/
#include "main.h"
#include <stdio.h>
#include <stdint.h>
/* NTFx CODE END Include*/
/**
 * @brief  Main program.
 */
int main(void)
{   
    /* NTFx CODE START Config*/
    CopyVectTable(0x15000000,0x0,VECT_SIZE);
    RCC_Configuration();
    GPIO_Configuration();
    DMA_Configuration();
    NVIC_Configuration();
    USART_Configuration();
    /*  Configure the SysTick to have interrupt in 1ms time basis,then call SysTick_Delayms(ms)*/
    SysTick_Config(600000); 
    /* NTFx CODE END Config*/
    while(1)
    {

    }
}


