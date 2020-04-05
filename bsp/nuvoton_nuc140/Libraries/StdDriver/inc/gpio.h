/**************************************************************************//**
 * @file     GPIO.h
 * @version  V3.00
 * $Revision: 3 $
 * $Date: 15/05/04 3:27p $
 * @brief    General Purpose I/O Driver Header File
 *
 * @note
 * Copyright (C) 2014 Nuvoton Technology Corp. All rights reserved.
 *
 ******************************************************************************/
#ifndef __GPIO_H__
#define __GPIO_H__

#ifdef __cplusplus
extern "C"
{
#endif


/** @addtogroup Standard_Driver Standard Driver
  @{
*/

/** @addtogroup GPIO_Driver GPIO Driver
  @{
*/

/** @addtogroup GPIO_EXPORTED_CONSTANTS GPIO Exported Constants
  @{
*/
#define GPIO_PIN_MAX            16 /*!< Specify Maximum Pins of Each GPIO Port */

/*---------------------------------------------------------------------------------------------------------*/
/*  PMD Constant Definitions                                                                               */
/*---------------------------------------------------------------------------------------------------------*/
#define GPIO_PMD_INPUT          0x0UL /*!< Input Mode */
#define GPIO_PMD_OUTPUT         0x1UL /*!< Output Mode */
#define GPIO_PMD_OPEN_DRAIN     0x2UL /*!< Open-Drain Mode */
#define GPIO_PMD_QUASI          0x3UL /*!< Quasi-bidirectional Mode */

/*---------------------------------------------------------------------------------------------------------*/
/*  GPIO Interrupt Type Constant Definitions                                                               */
/*---------------------------------------------------------------------------------------------------------*/
#define GPIO_INT_RISING         0x00010000UL /*!< Interrupt enable by Input Rising Edge */
#define GPIO_INT_FALLING        0x00000001UL /*!< Interrupt enable by Input Falling Edge */
#define GPIO_INT_BOTH_EDGE      0x00010001UL /*!< Interrupt enable by both Rising Edge and Falling Edge */
#define GPIO_INT_HIGH           0x01010000UL /*!< Interrupt enable by Level-High */
#define GPIO_INT_LOW            0x01000001UL /*!< Interrupt enable by Level-Level */

/*---------------------------------------------------------------------------------------------------------*/
/*  IMD Constant Definitions                                                                               */
/*---------------------------------------------------------------------------------------------------------*/
#define GPIO_IMD_EDGE           0UL /*!< IMD Setting for Edge Trigger Mode */
#define GPIO_IMD_LEVEL          1UL /*!< IMD Setting for Edge Level Mode */

/*---------------------------------------------------------------------------------------------------------*/
/*  DBNCECON Constant Definitions                                                                          */
/*---------------------------------------------------------------------------------------------------------*/
#define GPIO_INT_CLK_ON         0x00000020UL /*!< DBNCECON setting for all IO pins edge detection circuit is always active after reset */
#define GPIO_INT_CLK_OFF        0x00000000UL /*!< DBNCECON setting for edge detection circuit is active only if IO pin corresponding GPIOx_IEN bit is set to 1 */

#define GPIO_DBCLKSRC_LIRC      0x00000010UL /*!< DBNCECON setting for de-bounce counter clock source is the internal 10 kHz */
#define GPIO_DBCLKSRC_HCLK      0x00000000UL /*!< DBNCECON setting for de-bounce counter clock source is the HCLK */

#define GPIO_DBCLKSEL_1         0x00000000UL /*!< DBNCECON setting for sampling cycle = 1 clocks */
#define GPIO_DBCLKSEL_2         0x00000001UL /*!< DBNCECON setting for sampling cycle = 2 clocks */
#define GPIO_DBCLKSEL_4         0x00000002UL /*!< DBNCECON setting for sampling cycle = 4 clocks */
#define GPIO_DBCLKSEL_8         0x00000003UL /*!< DBNCECON setting for sampling cycle = 8 clocks */
#define GPIO_DBCLKSEL_16        0x00000004UL /*!< DBNCECON setting for sampling cycle = 16 clocks */
#define GPIO_DBCLKSEL_32        0x00000005UL /*!< DBNCECON setting for sampling cycle = 32 clocks */
#define GPIO_DBCLKSEL_64        0x00000006UL /*!< DBNCECON setting for sampling cycle = 64 clocks */
#define GPIO_DBCLKSEL_128       0x00000007UL /*!< DBNCECON setting for sampling cycle = 128 clocks */
#define GPIO_DBCLKSEL_256       0x00000008UL /*!< DBNCECON setting for sampling cycle = 256 clocks */
#define GPIO_DBCLKSEL_512       0x00000009UL /*!< DBNCECON setting for sampling cycle = 512 clocks */
#define GPIO_DBCLKSEL_1024      0x0000000AUL /*!< DBNCECON setting for sampling cycle = 1024 clocks */
#define GPIO_DBCLKSEL_2048      0x0000000BUL /*!< DBNCECON setting for sampling cycle = 2048 clocks */
#define GPIO_DBCLKSEL_4096      0x0000000CUL /*!< DBNCECON setting for sampling cycle = 4096 clocks */
#define GPIO_DBCLKSEL_8192      0x0000000DUL /*!< DBNCECON setting for sampling cycle = 8192 clocks */
#define GPIO_DBCLKSEL_16384     0x0000000EUL /*!< DBNCECON setting for sampling cycle = 16384 clocks */
#define GPIO_DBCLKSEL_32768     0x0000000FUL /*!< DBNCECON setting for sampling cycle = 32768 clocks */


/* Define GPIO Pin Data Input/Output. It could be used to control each I/O pin by pin address mapping.
   Example 1:

       PA0 = 1;

   It is used to set GPIO PA.0 to high;

   Example 2:

       if (PA0)
           PA0 = 0;

   If GPIO PA.0 pin status is high, then set GPIO PA.0 data output to low.
 */
#define GPIO_PIN_DATA(port, pin)    (*((volatile uint32_t *)((GPIO_PIN_DATA_BASE+(0x40*(port))) + ((pin)<<2))))
#define PA0             GPIO_PIN_DATA(0, 0 ) /*!< Specify PA.0 Pin Data Input/Output */
#define PA1             GPIO_PIN_DATA(0, 1 ) /*!< Specify PA.1 Pin Data Input/Output */
#define PA2             GPIO_PIN_DATA(0, 2 ) /*!< Specify PA.2 Pin Data Input/Output */
#define PA3             GPIO_PIN_DATA(0, 3 ) /*!< Specify PA.3 Pin Data Input/Output */
#define PA4             GPIO_PIN_DATA(0, 4 ) /*!< Specify PA.4 Pin Data Input/Output */
#define PA5             GPIO_PIN_DATA(0, 5 ) /*!< Specify PA.5 Pin Data Input/Output */
#define PA6             GPIO_PIN_DATA(0, 6 ) /*!< Specify PA.6 Pin Data Input/Output */
#define PA7             GPIO_PIN_DATA(0, 7 ) /*!< Specify PA.7 Pin Data Input/Output */
#define PA8             GPIO_PIN_DATA(0, 8 ) /*!< Specify PA.8 Pin Data Input/Output */
#define PA9             GPIO_PIN_DATA(0, 9 ) /*!< Specify PA.9 Pin Data Input/Output */
#define PA10            GPIO_PIN_DATA(0, 10) /*!< Specify PA.10 Pin Data Input/Output */
#define PA11            GPIO_PIN_DATA(0, 11) /*!< Specify PA.11 Pin Data Input/Output */
#define PA12            GPIO_PIN_DATA(0, 12) /*!< Specify PA.12 Pin Data Input/Output */
#define PA13            GPIO_PIN_DATA(0, 13) /*!< Specify PA.13 Pin Data Input/Output */
#define PA14            GPIO_PIN_DATA(0, 14) /*!< Specify PA.14 Pin Data Input/Output */
#define PA15            GPIO_PIN_DATA(0, 15) /*!< Specify PA.15 Pin Data Input/Output */
#define PB0             GPIO_PIN_DATA(1, 0 ) /*!< Specify PB.0 Pin Data Input/Output */
#define PB1             GPIO_PIN_DATA(1, 1 ) /*!< Specify PB.1 Pin Data Input/Output */
#define PB2             GPIO_PIN_DATA(1, 2 ) /*!< Specify PB.2 Pin Data Input/Output */
#define PB3             GPIO_PIN_DATA(1, 3 ) /*!< Specify PB.3 Pin Data Input/Output */
#define PB4             GPIO_PIN_DATA(1, 4 ) /*!< Specify PB.4 Pin Data Input/Output */
#define PB5             GPIO_PIN_DATA(1, 5 ) /*!< Specify PB.5 Pin Data Input/Output */
#define PB6             GPIO_PIN_DATA(1, 6 ) /*!< Specify PB.6 Pin Data Input/Output */
#define PB7             GPIO_PIN_DATA(1, 7 ) /*!< Specify PB.7 Pin Data Input/Output */
#define PB8             GPIO_PIN_DATA(1, 8 ) /*!< Specify PB.8 Pin Data Input/Output */
#define PB9             GPIO_PIN_DATA(1, 9 ) /*!< Specify PB.9 Pin Data Input/Output */
#define PB10            GPIO_PIN_DATA(1, 10) /*!< Specify PB.10 Pin Data Input/Output */
#define PB11            GPIO_PIN_DATA(1, 11) /*!< Specify PB.11 Pin Data Input/Output */
#define PB12            GPIO_PIN_DATA(1, 12) /*!< Specify PB.12 Pin Data Input/Output */
#define PB13            GPIO_PIN_DATA(1, 13) /*!< Specify PB.13 Pin Data Input/Output */
#define PB14            GPIO_PIN_DATA(1, 14) /*!< Specify PB.14 Pin Data Input/Output */
#define PB15            GPIO_PIN_DATA(1, 15) /*!< Specify PB.15 Pin Data Input/Output */
#define PC0             GPIO_PIN_DATA(2, 0 ) /*!< Specify PC.0 Pin Data Input/Output */
#define PC1             GPIO_PIN_DATA(2, 1 ) /*!< Specify PC.1 Pin Data Input/Output */
#define PC2             GPIO_PIN_DATA(2, 2 ) /*!< Specify PC.2 Pin Data Input/Output */
#define PC3             GPIO_PIN_DATA(2, 3 ) /*!< Specify PC.3 Pin Data Input/Output */
#define PC4             GPIO_PIN_DATA(2, 4 ) /*!< Specify PC.4 Pin Data Input/Output */
#define PC5             GPIO_PIN_DATA(2, 5 ) /*!< Specify PC.5 Pin Data Input/Output */
#define PC6             GPIO_PIN_DATA(2, 6 ) /*!< Specify PC.6 Pin Data Input/Output */
#define PC7             GPIO_PIN_DATA(2, 7 ) /*!< Specify PC.7 Pin Data Input/Output */
#define PC8             GPIO_PIN_DATA(2, 8 ) /*!< Specify PC.8 Pin Data Input/Output */
#define PC9             GPIO_PIN_DATA(2, 9 ) /*!< Specify PC.9 Pin Data Input/Output */
#define PC10            GPIO_PIN_DATA(2, 10) /*!< Specify PC.10 Pin Data Input/Output */
#define PC11            GPIO_PIN_DATA(2, 11) /*!< Specify PC.11 Pin Data Input/Output */
#define PC12            GPIO_PIN_DATA(2, 12) /*!< Specify PC.12 Pin Data Input/Output */
#define PC13            GPIO_PIN_DATA(2, 13) /*!< Specify PC.13 Pin Data Input/Output */
#define PC14            GPIO_PIN_DATA(2, 14) /*!< Specify PC.14 Pin Data Input/Output */
#define PC15            GPIO_PIN_DATA(2, 15) /*!< Specify PC.15 Pin Data Input/Output */
#define PD0             GPIO_PIN_DATA(3, 0 ) /*!< Specify PD.0 Pin Data Input/Output */
#define PD1             GPIO_PIN_DATA(3, 1 ) /*!< Specify PD.1 Pin Data Input/Output */
#define PD2             GPIO_PIN_DATA(3, 2 ) /*!< Specify PD.2 Pin Data Input/Output */
#define PD3             GPIO_PIN_DATA(3, 3 ) /*!< Specify PD.3 Pin Data Input/Output */
#define PD4             GPIO_PIN_DATA(3, 4 ) /*!< Specify PD.4 Pin Data Input/Output */
#define PD5             GPIO_PIN_DATA(3, 5 ) /*!< Specify PD.5 Pin Data Input/Output */
#define PD6             GPIO_PIN_DATA(3, 6 ) /*!< Specify PD.6 Pin Data Input/Output */
#define PD7             GPIO_PIN_DATA(3, 7 ) /*!< Specify PD.7 Pin Data Input/Output */
#define PD8             GPIO_PIN_DATA(3, 8 ) /*!< Specify PD.8 Pin Data Input/Output */
#define PD9             GPIO_PIN_DATA(3, 9 ) /*!< Specify PD.9 Pin Data Input/Output */
#define PD10            GPIO_PIN_DATA(3, 10) /*!< Specify PD.10 Pin Data Input/Output */
#define PD11            GPIO_PIN_DATA(3, 11) /*!< Specify PD.11 Pin Data Input/Output */
#define PD12            GPIO_PIN_DATA(3, 12) /*!< Specify PD.12 Pin Data Input/Output */
#define PD13            GPIO_PIN_DATA(3, 13) /*!< Specify PD.13 Pin Data Input/Output */
#define PD14            GPIO_PIN_DATA(3, 14) /*!< Specify PD.14 Pin Data Input/Output */
#define PD15            GPIO_PIN_DATA(3, 15) /*!< Specify PD.15 Pin Data Input/Output */
#define PE0             GPIO_PIN_DATA(4, 0 ) /*!< Specify PE.0 Pin Data Input/Output */
#define PE1             GPIO_PIN_DATA(4, 1 ) /*!< Specify PE.1 Pin Data Input/Output */
#define PE2             GPIO_PIN_DATA(4, 2 ) /*!< Specify PE.2 Pin Data Input/Output */
#define PE3             GPIO_PIN_DATA(4, 3 ) /*!< Specify PE.3 Pin Data Input/Output */
#define PE4             GPIO_PIN_DATA(4, 4 ) /*!< Specify PE.4 Pin Data Input/Output */
#define PE5             GPIO_PIN_DATA(4, 5 ) /*!< Specify PE.5 Pin Data Input/Output */
#define PE6             GPIO_PIN_DATA(4, 6 ) /*!< Specify PE.6 Pin Data Input/Output */
#define PE7             GPIO_PIN_DATA(4, 7 ) /*!< Specify PE.7 Pin Data Input/Output */
#define PE8             GPIO_PIN_DATA(4, 8 ) /*!< Specify PE.8 Pin Data Input/Output */
#define PE9             GPIO_PIN_DATA(4, 9 ) /*!< Specify PE.9 Pin Data Input/Output */
#define PE10            GPIO_PIN_DATA(4, 10) /*!< Specify PE.10 Pin Data Input/Output */
#define PE11            GPIO_PIN_DATA(4, 11) /*!< Specify PE.11 Pin Data Input/Output */
#define PE12            GPIO_PIN_DATA(4, 12) /*!< Specify PE.12 Pin Data Input/Output */
#define PE13            GPIO_PIN_DATA(4, 13) /*!< Specify PE.13 Pin Data Input/Output */
#define PE14            GPIO_PIN_DATA(4, 14) /*!< Specify PE.14 Pin Data Input/Output */
#define PE15            GPIO_PIN_DATA(4, 15) /*!< Specify PE.15 Pin Data Input/Output */
#define PF0             GPIO_PIN_DATA(5, 0 ) /*!< Specify PF.0 Pin Data Input/Output */
#define PF1             GPIO_PIN_DATA(5, 1 ) /*!< Specify PF.1 Pin Data Input/Output */
#define PF2             GPIO_PIN_DATA(5, 2 ) /*!< Specify PF.2 Pin Data Input/Output */
#define PF3             GPIO_PIN_DATA(5, 3 ) /*!< Specify PF.3 Pin Data Input/Output */


/*@}*/ /* end of group GPIO_EXPORTED_CONSTANTS */


/** @addtogroup GPIO_EXPORTED_FUNCTIONS GPIO Exported Functions
  @{
*/

/**
 * @brief       Clear GPIO Pin Interrupt Flag
 *
 * @param[in]   port        GPIO port. It could be PA, PB, PC, PD, PE or PF.
 * @param[in]   u32PinMask  The single or multiple pins of specified GPIO port.
 *                          It could be BIT0 ~ BIT15 for PA, PB, PC, PD and PE GPIO port.
 *                          It could be BIT0 ~ BIT3 for PF GPIO port.
 *
 * @return      None
 *
 * @details     Clear the interrupt status of specified GPIO pin.
 */
#define GPIO_CLR_INT_FLAG(port, u32PinMask)         ((port)->ISRC = (u32PinMask))

/**
 * @brief       Disable Pin De-bounce Function
 *
 * @param[in]   port        GPIO port. It could be PA, PB, PC, PD, PE or PF.
 * @param[in]   u32PinMask  The single or multiple pins of specified GPIO port.
 *                          It could be BIT0 ~ BIT15 for PA, PB, PC, PD and PE GPIO port.
 *                          It could be BIT0 ~ BIT3 for PF GPIO port.
 *
 * @return      None
 *
 * @details     Disable the interrupt de-bounce function of specified GPIO pin.
 */
#define GPIO_DISABLE_DEBOUNCE(port, u32PinMask)     ((port)->DBEN &= ~(u32PinMask))

/**
 * @brief       Enable Pin De-bounce Function
 *
 * @param[in]   port        GPIO port. It could be PA, PB, PC, PD, PE or PF.
 * @param[in]   u32PinMask  The single or multiple pins of specified GPIO port.
 *                          It could be BIT0 ~ BIT15 for PA, PB, PC, PD and PE GPIO port.
 *                          It could be BIT0 ~ BIT3 for PF GPIO port.
 *
 * @return      None
 *
 * @details     Enable the interrupt de-bounce function of specified GPIO pin.
 */
#define GPIO_ENABLE_DEBOUNCE(port, u32PinMask)      ((port)->DBEN |= (u32PinMask))

/**
 * @brief       Disable I/O Digital Input Path
 *
 * @param[in]   port        GPIO port. It could be PA, PB, PC, PD, PE or PF.
 * @param[in]   u32PinMask  The single or multiple pins of specified GPIO port.
 *                          It could be BIT0 ~ BIT15 for PA, PB, PC, PD and PE GPIO port.
 *                          It could be BIT0 ~ BIT3 for PF GPIO port.
 *
 * @return      None
 *
 * @details     Disable I/O digital input path of specified GPIO pin.
 */
#define GPIO_DISABLE_DIGITAL_PATH(port, u32PinMask) ((port)->OFFD |= ((u32PinMask)<<16))

/**
 * @brief       Enable I/O Digital Input Path
 *
 * @param[in]   port        GPIO port. It could be PA, PB, PC, PD, PE or PF.
 * @param[in]   u32PinMask  The single or multiple pins of specified GPIO port.
 *                          It could be BIT0 ~ BIT15 for PA, PB, PC, PD and PE GPIO port.
 *                          It could be BIT0 ~ BIT3 for PF GPIO port.
 *
 * @return      None
 *
 * @details     Enable I/O digital input path of specified GPIO pin.
 */
#define GPIO_ENABLE_DIGITAL_PATH(port, u32PinMask)  ((port)->OFFD &= ~((u32PinMask)<<16))

/**
 * @brief       Disable I/O DOUT mask
 *
 * @param[in]   port        GPIO port. It could be PA, PB, PC, PD, PE or PF.
 * @param[in]   u32PinMask  The single or multiple pins of specified GPIO port.
 *                          It could be BIT0 ~ BIT15 for PA, PB, PC, PD and PE GPIO port.
 *                          It could be BIT0 ~ BIT3 for PF GPIO port.
 *
 * @return      None
 *
 * @details     Disable I/O DOUT mask of specified GPIO pin.
 */
#define GPIO_DISABLE_DOUT_MASK(port, u32PinMask)    ((port)->DMASK &= ~(u32PinMask))

/**
 * @brief       Enable I/O DOUT mask
 *
 * @param[in]   port        GPIO port. It could be PA, PB, PC, PD, PE or PF.
 * @param[in]   u32PinMask  The single or multiple pins of specified GPIO port.
 *                          It could be BIT0 ~ BIT15 for PA, PB, PC, PD and PE GPIO port.
 *                          It could be BIT0 ~ BIT3 for PF GPIO port.
 *
 * @return      None
 *
 * @details     Enable I/O DOUT mask of specified GPIO pin.
 */
#define GPIO_ENABLE_DOUT_MASK(port, u32PinMask) ((port)->DMASK |= (u32PinMask))

/**
 * @brief       Get GPIO Pin Interrupt Flag
 *
 * @param[in]   port        GPIO port. It could be PA, PB, PC, PD, PE or PF.
 * @param[in]   u32PinMask  The single or multiple pins of specified GPIO port.
 *                          It could be BIT0 ~ BIT15 for PA, PB, PC, PD and PE GPIO port.
 *                          It could be BIT0 ~ BIT3 for PF GPIO port.
 *
 * @retval      0           No interrupt at specified GPIO pin
 * @retval      1           The specified GPIO pin generate an interrupt
 *
 * @details     Get the interrupt status of specified GPIO pin.
 */
#define GPIO_GET_INT_FLAG(port, u32PinMask)     ((port)->ISRC & (u32PinMask))

/**
 * @brief       Set De-bounce Sampling Cycle Time
 *
 * @param[in]   u32ClkSrc   The de-bounce counter clock source. It could be GPIO_DBCLKSRC_HCLK or GPIO_DBCLKSRC_LIRC.
 * @param[in]   u32ClkSel   The de-bounce sampling cycle selection. It could be \n
 *                              GPIO_DBCLKSEL_1, GPIO_DBCLKSEL_2, GPIO_DBCLKSEL_4, GPIO_DBCLKSEL_8, \n
 *                              GPIO_DBCLKSEL_16, GPIO_DBCLKSEL_32, GPIO_DBCLKSEL_64, GPIO_DBCLKSEL_128, \n
 *                              GPIO_DBCLKSEL_256, GPIO_DBCLKSEL_512, GPIO_DBCLKSEL_1024, GPIO_DBCLKSEL_2048, \n
 *                              GPIO_DBCLKSEL_4096, GPIO_DBCLKSEL_8192, GPIO_DBCLKSEL_16384, GPIO_DBCLKSEL_32768.
 *
 * @return      None
 *
 * @details     Set the interrupt de-bounce sampling cycle time based on the debounce counter clock source. \n
 *              Example: _GPIO_SET_DEBOUNCE_TIME(GPIO_DBCLKSRC_LIRC, GPIO_DBCLKSEL_4). \n
 *              It's meaning the De-debounce counter clock source is internal 10 KHz and sampling cycle selection is 4. \n
 *              Then the target de-bounce sampling cycle time is (4)*(1/(10*1000)) s = 4*0.0001 s = 400 us,
 *              and system will sampling interrupt input once per 400 us.
 */
#define GPIO_SET_DEBOUNCE_TIME(u32ClkSrc, u32ClkSel)    (GPIO->DBNCECON = (GPIO_DBNCECON_ICLK_ON_Msk | (u32ClkSrc) | (u32ClkSel)))

/**
 * @brief       Get GPIO Port IN Data
 *
 * @param[in]   port        GPIO port. It could be PA, PB, PC, PD, PE or PF.
 *
 * @return      The specified port data
 *
 * @details     Get the PIN register of specified GPIO port.
 */
#define GPIO_GET_IN_DATA(port)  ((port)->PIN)

/**
 * @brief       Set GPIO Port OUT Data
 *
 * @param[in]   port        GPIO port. It could be PA, PB, PC, PD, PE or PF.
 * @param[in]   u32Data     GPIO port data.
 *
 * @return      None
 *
 * @details     Set the Data into specified GPIO port.
 */
#define GPIO_SET_OUT_DATA(port, u32Data)    ((port)->DOUT = (u32Data))

/**
 * @brief       Toggle Specified GPIO pin
 *
 * @param[in]   u32Pin      Pxy
 *
 * @return      None
 *
 * @details     Toggle the specified GPIO pint.
 */
#define GPIO_TOGGLE(u32Pin) ((u32Pin) ^= 1)

/**
 * @brief       Enable External GPIO Interrupt 0
 *
 * @param[in]   port            GPIO port. It could be PA, PB, PC, PD, PE or PF.
 * @param[in]   u32Pin          The pin of specified GPIO port.
 *                              It could be 0 ~ 15 for PA, PB, PC, PD and PE GPIO port.
 *                              It could be 0 ~ 3 for PF GPIO port.
 * @param[in]   u32IntAttribs   The interrupt attribute of specified GPIO pin. It could be \n
 *                              GPIO_INT_RISING, GPIO_INT_FALLING, GPIO_INT_BOTH_EDGE, GPIO_INT_HIGH, GPIO_INT_LOW.
 *
 * @return      None
 *
 * @details     This function is used to enable specified GPIO pin interrupt.
 */
#define GPIO_EnableEINT0    GPIO_EnableInt


/**
 * @brief       Disable External GPIO Interrupt 0
 *
 * @param[in]   port        GPIO port. It could be PA, PB, PC, PD, PE or PF.
 * @param[in]   u32Pin      The pin of specified GPIO port.
 *                          It could be 0 ~ 15 for PA, PB, PC, PD and PE GPIO port.
 *                          It could be 0 ~ 3 for PF GPIO port.
 *
 * @return      None
 *
 * @details     This function is used to enable specified GPIO pin interrupt.
 */
#define GPIO_DisableEINT0   GPIO_DisableInt


/**
 * @brief       Enable External GPIO Interrupt 1
 *
 * @param[in]   port            GPIO port. It could be PA, PB, PC, PD, PE or PF.
 * @param[in]   u32Pin          The pin of specified GPIO port.
 *                              It could be 0 ~ 15 for PA, PB, PC, PD and PE GPIO port.
 *                              It could be 0 ~ 3 for PF GPIO port.
 * @param[in]   u32IntAttribs   The interrupt attribute of specified GPIO pin. It could be \n
 *                              GPIO_INT_RISING, GPIO_INT_FALLING, GPIO_INT_BOTH_EDGE, GPIO_INT_HIGH, GPIO_INT_LOW.
 *
 * @return      None
 *
 * @details     This function is used to enable specified GPIO pin interrupt.
 */
#define GPIO_EnableEINT1    GPIO_EnableInt


/**
 * @brief       Disable External GPIO Interrupt 1
 *
 * @param[in]   port        GPIO port. It could be PA, PB, PC, PD, PE or PF.
 * @param[in]   u32Pin      The pin of specified GPIO port.
 *                          It could be 0 ~ 15 for PA, PB, PC, PD and PE GPIO port.
 *                          It could be 0 ~ 3 for PF GPIO port.
 *
 * @return      None
 *
 * @details     This function is used to enable specified GPIO pin interrupt.
 */
#define GPIO_DisableEINT1   GPIO_DisableInt


void GPIO_SetMode(GPIO_T *port, uint32_t u32PinMask, uint32_t u32Mode);
void GPIO_EnableInt(GPIO_T *port, uint32_t u32Pin, uint32_t u32IntAttribs);
void GPIO_DisableInt(GPIO_T *port, uint32_t u32Pin);


/*@}*/ /* end of group GPIO_EXPORTED_FUNCTIONS */

/*@}*/ /* end of group GPIO_Driver */

/*@}*/ /* end of group Device_Driver */

#ifdef __cplusplus
}
#endif

#endif //__GPIO_H__

/*** (C) COPYRIGHT 2014 Nuvoton Technology Corp. ***/
