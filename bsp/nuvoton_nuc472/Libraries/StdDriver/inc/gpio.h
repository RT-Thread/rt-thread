/**************************************************************************//**
 * @file     gpio.h
 * @version  V1.00
 * $Revision: 13 $
 * $Date: 14/12/01 10:32a $
 * @brief    NUC472/NUC442 GPIO driver header file
 *
 * @note
 * Copyright (C) 2014 Nuvoton Technology Corp. All rights reserved.
 *****************************************************************************/
#ifndef __GPIO_H__
#define __GPIO_H__

#ifdef __cplusplus
extern "C"
{
#endif


/** @addtogroup NUC472_442_Device_Driver NUC472/NUC442 Device Driver
  @{
*/

/** @addtogroup NUC472_442_GPIO_Driver GPIO Driver
  @{
*/

/** @addtogroup NUC472_442_GPIO_EXPORTED_CONSTANTS GPIO Exported Constants
  @{
*/
#define GPIO_PIN_MAX    16   /*!< Specify Maximum Pins of Each GPIO Port */

/*---------------------------------------------------------------------------------------------------------*/
/*  MODE Constant Definitions                                                                               */
/*---------------------------------------------------------------------------------------------------------*/
#define GPIO_MODE_INPUT              0x0UL           /*!< Input Mode */
#define GPIO_MODE_OUTPUT             0x1UL           /*!< Output Mode */
#define GPIO_MODE_OPEN_DRAIN         0x2UL           /*!< Open-Drain Mode */
#define GPIO_MODE_QUASI              0x3UL           /*!< Quasi-bidirectional Mode */

/*---------------------------------------------------------------------------------------------------------*/
/*  GPIO Interrupt Type Constant Definitions                                                               */
/*---------------------------------------------------------------------------------------------------------*/
#define GPIO_INT_RISING             0x00010000UL    /*!< Interrupt enable by Input Rising Edge */
#define GPIO_INT_FALLING            0x00000001UL    /*!< Interrupt enable by Input Falling Edge */
#define GPIO_INT_BOTH_EDGE          0x00010001UL    /*!< Interrupt enable by both Rising Edge and Falling Edge */
#define GPIO_INT_HIGH               0x01010000UL    /*!< Interrupt enable by Level-High */
#define GPIO_INT_LOW                0x01000001UL    /*!< Interrupt enable by Level-Level */

/*---------------------------------------------------------------------------------------------------------*/
/*  IMD Constant Definitions                                                                               */
/*---------------------------------------------------------------------------------------------------------*/
#define GPIO_IMD_EDGE               0UL             /*!< IMD Setting for Edge Trigger Mode */
#define GPIO_IMD_LEVEL              1UL             /*!< IMD Setting for Edge Level Mode */

/*---------------------------------------------------------------------------------------------------------*/
/*  DBCTL Constant Definitions                                                                          */
/*---------------------------------------------------------------------------------------------------------*/
#define GPIO_DBCTL_ICLK_ON           0x00000020UL /*!< DBCTL setting for all IO pins edge detection circuit is always active after reset */
#define GPIO_DBCTL_ICLK_OFF          0x00000000UL /*!< DBCTL setting for edge detection circuit is active only if IO pin corresponding GPIOx_IEN bit is set to 1 */

#define GPIO_DBCTL_DBCLKSRC_IRC10K   0x00000010UL /*!< DBCTL setting for de-bounce counter clock source is the internal 10 kHz */
#define GPIO_DBCTL_DBCLKSRC_HCLK     0x00000000UL /*!< DBCTL setting for de-bounce counter clock source is the internal HCLK */

#define GPIO_DBCTL_DBCLKSEL_1        0x00000000UL /*!< DBCTL setting for sampling cycle = 1 clocks */
#define GPIO_DBCTL_DBCLKSEL_2        0x00000001UL /*!< DBCTL setting for sampling cycle = 2 clocks */
#define GPIO_DBCTL_DBCLKSEL_4        0x00000002UL /*!< v setting for sampling cycle = 4 clocks */
#define GPIO_DBCTL_DBCLKSEL_8        0x00000003UL /*!< DBCTL setting for sampling cycle = 8 clocks */
#define GPIO_DBCTL_DBCLKSEL_16       0x00000004UL /*!< DBCTL setting for sampling cycle = 16 clocks */
#define GPIO_DBCTL_DBCLKSEL_32       0x00000005UL /*!< DBCTL setting for sampling cycle = 32 clocks */
#define GPIO_DBCTL_DBCLKSEL_64       0x00000006UL /*!< DBCTL setting for sampling cycle = 64 clocks */
#define GPIO_DBCTL_DBCLKSEL_128      0x00000007UL /*!< DBCTL setting for sampling cycle = 128 clocks */
#define GPIO_DBCTL_DBCLKSEL_256      0x00000008UL /*!< DBCTL setting for sampling cycle = 256 clocks */
#define GPIO_DBCTL_DBCLKSEL_512      0x00000009UL /*!< DBCTL setting for sampling cycle = 512 clocks */
#define GPIO_DBCTL_DBCLKSEL_1024     0x0000000AUL /*!< DBCTL setting for sampling cycle = 1024 clocks */
#define GPIO_DBCTL_DBCLKSEL_2048     0x0000000BUL /*!< DBCTL setting for sampling cycle = 2048 clocks */
#define GPIO_DBCTL_DBCLKSEL_4096     0x0000000CUL /*!< DBCTL setting for sampling cycle = 4096 clocks */
#define GPIO_DBCTL_DBCLKSEL_8192     0x0000000DUL /*!< DBCTL setting for sampling cycle = 8192 clocks */
#define GPIO_DBCTL_DBCLKSEL_16384    0x0000000EUL /*!< DBCTL setting for sampling cycle = 16384 clocks */
#define GPIO_DBCTL_DBCLKSEL_32768    0x0000000FUL /*!< DBCTL setting for sampling cycle = 32768 clocks */

/** Define GPIO Pin Data Input/Output. It could be used to control each I/O pin by pin address mapping.
 *  Example 1:
 *
 *      PA0 = 1;
 *
 *  It is used to set PA0 to high;
 *
 *  Example 2:
 *
 *      if (PA0)
 *          PA0 = 0;
 *
 *  If PA0 pin status is high, then set PA0 data output to low.
 */
#define GPIO_PIN_ADDR(port, pin)    (*((volatile uint32_t *)((GPIO_PIN_DATA_BASE+(0x40*(port))) + ((pin)<<2))))
#define PA0             GPIO_PIN_ADDR(0, 0)  /*!< Specify PA0 Pin Data Input/Output */
#define PA1             GPIO_PIN_ADDR(0, 1)  /*!< Specify PA1 Pin Data Input/Output */
#define PA2             GPIO_PIN_ADDR(0, 2)  /*!< Specify PA2 Pin Data Input/Output */
#define PA3             GPIO_PIN_ADDR(0, 3)  /*!< Specify PA3 Pin Data Input/Output */
#define PA4             GPIO_PIN_ADDR(0, 4)  /*!< Specify PA4 Pin Data Input/Output */
#define PA5             GPIO_PIN_ADDR(0, 5)  /*!< Specify PA5 Pin Data Input/Output */
#define PA6             GPIO_PIN_ADDR(0, 6)  /*!< Specify PA6 Pin Data Input/Output */
#define PA7             GPIO_PIN_ADDR(0, 7)  /*!< Specify PA7 Pin Data Input/Output */
#define PA8             GPIO_PIN_ADDR(0, 8)  /*!< Specify PA8 Pin Data Input/Output */
#define PA9             GPIO_PIN_ADDR(0, 9)  /*!< Specify PA9 Pin Data Input/Output */
#define PA10            GPIO_PIN_ADDR(0, 10) /*!< Specify PA10 Pin Data Input/Output */
#define PA11            GPIO_PIN_ADDR(0, 11) /*!< Specify PA11 Pin Data Input/Output */
#define PA12            GPIO_PIN_ADDR(0, 12) /*!< Specify PA12 Pin Data Input/Output */
#define PA13            GPIO_PIN_ADDR(0, 13) /*!< Specify PA13 Pin Data Input/Output */
#define PA14            GPIO_PIN_ADDR(0, 14) /*!< Specify PA14 Pin Data Input/Output */
#define PA15            GPIO_PIN_ADDR(0, 15) /*!< Specify PA15 Pin Data Input/Output */

#define PB0             GPIO_PIN_ADDR(1, 0)  /*!< Specify PB0 Pin Data Input/Output */
#define PB1             GPIO_PIN_ADDR(1, 1)  /*!< Specify PB1 Pin Data Input/Output */
#define PB2             GPIO_PIN_ADDR(1, 2)  /*!< Specify PB2 Pin Data Input/Output */
#define PB3             GPIO_PIN_ADDR(1, 3)  /*!< Specify PB3 Pin Data Input/Output */
#define PB4             GPIO_PIN_ADDR(1, 4)  /*!< Specify PB4 Pin Data Input/Output */
#define PB5             GPIO_PIN_ADDR(1, 5)  /*!< Specify PB5 Pin Data Input/Output */
#define PB6             GPIO_PIN_ADDR(1, 6)  /*!< Specify PB6 Pin Data Input/Output */
#define PB7             GPIO_PIN_ADDR(1, 7)  /*!< Specify PB7 Pin Data Input/Output */
#define PB8             GPIO_PIN_ADDR(1, 8)  /*!< Specify PB8 Pin Data Input/Output */
#define PB9             GPIO_PIN_ADDR(1, 9)  /*!< Specify PB9 Pin Data Input/Output */
#define PB10            GPIO_PIN_ADDR(1, 10) /*!< Specify PB10 Pin Data Input/Output */
#define PB11            GPIO_PIN_ADDR(1, 11) /*!< Specify PB11 Pin Data Input/Output */
#define PB12            GPIO_PIN_ADDR(1, 12) /*!< Specify PB12 Pin Data Input/Output */
#define PB13            GPIO_PIN_ADDR(1, 13) /*!< Specify PB13 Pin Data Input/Output */
#define PB14            GPIO_PIN_ADDR(1, 14) /*!< Specify PB14 Pin Data Input/Output */
#define PB15            GPIO_PIN_ADDR(1, 15) /*!< Specify PB15 Pin Data Input/Output */

#define PC0             GPIO_PIN_ADDR(2, 0)  /*!< Specify PC0 Pin Data Input/Output */
#define PC1             GPIO_PIN_ADDR(2, 1)  /*!< Specify PC1 Pin Data Input/Output */
#define PC2             GPIO_PIN_ADDR(2, 2)  /*!< Specify PC2 Pin Data Input/Output */
#define PC3             GPIO_PIN_ADDR(2, 3)  /*!< Specify PC3 Pin Data Input/Output */
#define PC4             GPIO_PIN_ADDR(2, 4)  /*!< Specify PC4 Pin Data Input/Output */
#define PC5             GPIO_PIN_ADDR(2, 5)  /*!< Specify PC5 Pin Data Input/Output */
#define PC6             GPIO_PIN_ADDR(2, 6)  /*!< Specify PC6 Pin Data Input/Output */
#define PC7             GPIO_PIN_ADDR(2, 7)  /*!< Specify PC7 Pin Data Input/Output */
#define PC8             GPIO_PIN_ADDR(2, 8)  /*!< Specify PC8 Pin Data Input/Output */
#define PC9             GPIO_PIN_ADDR(2, 9)  /*!< Specify PC9 Pin Data Input/Output */
#define PC10            GPIO_PIN_ADDR(2, 10) /*!< Specify PC10 Pin Data Input/Output */
#define PC11            GPIO_PIN_ADDR(2, 11) /*!< Specify PC11 Pin Data Input/Output */
#define PC12            GPIO_PIN_ADDR(2, 12) /*!< Specify PC12 Pin Data Input/Output */
#define PC13            GPIO_PIN_ADDR(2, 13) /*!< Specify PC13 Pin Data Input/Output */
#define PC14            GPIO_PIN_ADDR(2, 14) /*!< Specify PC14 Pin Data Input/Output */
#define PC15            GPIO_PIN_ADDR(2, 15) /*!< Specify PC15 Pin Data Input/Output */

#define PD0             GPIO_PIN_ADDR(3, 0)  /*!< Specify PD0 Pin Data Input/Output */
#define PD1             GPIO_PIN_ADDR(3, 1)  /*!< Specify PD1 Pin Data Input/Output */
#define PD2             GPIO_PIN_ADDR(3, 2)  /*!< Specify PD2 Pin Data Input/Output */
#define PD3             GPIO_PIN_ADDR(3, 3)  /*!< Specify PD3 Pin Data Input/Output */
#define PD4             GPIO_PIN_ADDR(3, 4)  /*!< Specify PD4 Pin Data Input/Output */
#define PD5             GPIO_PIN_ADDR(3, 5)  /*!< Specify PD5 Pin Data Input/Output */
#define PD6             GPIO_PIN_ADDR(3, 6)  /*!< Specify PD6 Pin Data Input/Output */
#define PD7             GPIO_PIN_ADDR(3, 7)  /*!< Specify PD7 Pin Data Input/Output */
#define PD8             GPIO_PIN_ADDR(3, 8)  /*!< Specify PD8 Pin Data Input/Output */
#define PD9             GPIO_PIN_ADDR(3, 9)  /*!< Specify PD9 Pin Data Input/Output */
#define PD10            GPIO_PIN_ADDR(3, 10) /*!< Specify PD10 Pin Data Input/Output */
#define PD11            GPIO_PIN_ADDR(3, 11) /*!< Specify PD11 Pin Data Input/Output */
#define PD12            GPIO_PIN_ADDR(3, 12) /*!< Specify PD12 Pin Data Input/Output */
#define PD13            GPIO_PIN_ADDR(3, 13) /*!< Specify PD13 Pin Data Input/Output */
#define PD14            GPIO_PIN_ADDR(3, 14) /*!< Specify PD14 Pin Data Input/Output */
#define PD15            GPIO_PIN_ADDR(3, 15) /*!< Specify PD15 Pin Data Input/Output */

#define PE0             GPIO_PIN_ADDR(4, 0)  /*!< Specify PE0 Pin Data Input/Output */
#define PE1             GPIO_PIN_ADDR(4, 1)  /*!< Specify PE1 Pin Data Input/Output */
#define PE2             GPIO_PIN_ADDR(4, 2)  /*!< Specify PE2 Pin Data Input/Output */
#define PE3             GPIO_PIN_ADDR(4, 3)  /*!< Specify PE3 Pin Data Input/Output */
#define PE4             GPIO_PIN_ADDR(4, 4)  /*!< Specify PE4 Pin Data Input/Output */
#define PE5             GPIO_PIN_ADDR(4, 5)  /*!< Specify PE5 Pin Data Input/Output */
#define PE6             GPIO_PIN_ADDR(4, 6)  /*!< Specify PE6 Pin Data Input/Output */
#define PE7             GPIO_PIN_ADDR(4, 7)  /*!< Specify PE7 Pin Data Input/Output */
#define PE8             GPIO_PIN_ADDR(4, 8)  /*!< Specify PE8 Pin Data Input/Output */
#define PE9             GPIO_PIN_ADDR(4, 9)  /*!< Specify PE9 Pin Data Input/Output */
#define PE10            GPIO_PIN_ADDR(4, 10) /*!< Specify PE10 Pin Data Input/Output */
#define PE11            GPIO_PIN_ADDR(4, 11) /*!< Specify PE11 Pin Data Input/Output */
#define PE12            GPIO_PIN_ADDR(4, 12) /*!< Specify PE12 Pin Data Input/Output */
#define PE13            GPIO_PIN_ADDR(4, 13) /*!< Specify PE13 Pin Data Input/Output */
#define PE14            GPIO_PIN_ADDR(4, 14) /*!< Specify PE14 Pin Data Input/Output */
#define PE15            GPIO_PIN_ADDR(4, 15) /*!< Specify PE15 Pin Data Input/Output */

#define PF0             GPIO_PIN_ADDR(5, 0)  /*!< Specify PF0 Pin Data Input/Output */
#define PF1             GPIO_PIN_ADDR(5, 1)  /*!< Specify PF1 Pin Data Input/Output */
#define PF2             GPIO_PIN_ADDR(5, 2)  /*!< Specify PF2 Pin Data Input/Output */
#define PF3             GPIO_PIN_ADDR(5, 3)  /*!< Specify PF3 Pin Data Input/Output */
#define PF4             GPIO_PIN_ADDR(5, 4)  /*!< Specify PF4 Pin Data Input/Output */
#define PF5             GPIO_PIN_ADDR(5, 5)  /*!< Specify PF5 Pin Data Input/Output */
#define PF6             GPIO_PIN_ADDR(5, 6)  /*!< Specify PF6 Pin Data Input/Output */
#define PF7             GPIO_PIN_ADDR(5, 7)  /*!< Specify PF7 Pin Data Input/Output */
#define PF8             GPIO_PIN_ADDR(5, 8)  /*!< Specify PF8 Pin Data Input/Output */
#define PF9             GPIO_PIN_ADDR(5, 9)  /*!< Specify PF9 Pin Data Input/Output */
#define PF10            GPIO_PIN_ADDR(5, 10) /*!< Specify PF10 Pin Data Input/Output */
#define PF11            GPIO_PIN_ADDR(5, 11) /*!< Specify PF11 Pin Data Input/Output */
#define PF12            GPIO_PIN_ADDR(5, 12) /*!< Specify PF12 Pin Data Input/Output */
#define PF13            GPIO_PIN_ADDR(5, 13) /*!< Specify PF13 Pin Data Input/Output */
#define PF14            GPIO_PIN_ADDR(5, 14) /*!< Specify PF14 Pin Data Input/Output */
#define PF15            GPIO_PIN_ADDR(5, 15) /*!< Specify PF15 Pin Data Input/Output */

#define PG0             GPIO_PIN_ADDR(6, 0)  /*!< Specify PG0 Pin Data Input/Output */
#define PG1             GPIO_PIN_ADDR(6, 1)  /*!< Specify PG1 Pin Data Input/Output */
#define PG2             GPIO_PIN_ADDR(6, 2)  /*!< Specify PG2 Pin Data Input/Output */
#define PG3             GPIO_PIN_ADDR(6, 3)  /*!< Specify PG3 Pin Data Input/Output */
#define PG4             GPIO_PIN_ADDR(6, 4)  /*!< Specify PG4 Pin Data Input/Output */
#define PG5             GPIO_PIN_ADDR(6, 5)  /*!< Specify PG5 Pin Data Input/Output */
#define PG6             GPIO_PIN_ADDR(6, 6)  /*!< Specify PG6 Pin Data Input/Output */
#define PG7             GPIO_PIN_ADDR(6, 7)  /*!< Specify PG7 Pin Data Input/Output */
#define PG8             GPIO_PIN_ADDR(6, 8)  /*!< Specify PG8 Pin Data Input/Output */
#define PG9             GPIO_PIN_ADDR(6, 9)  /*!< Specify PG9 Pin Data Input/Output */
#define PG10            GPIO_PIN_ADDR(6, 10) /*!< Specify PG10 Pin Data Input/Output */
#define PG11            GPIO_PIN_ADDR(6, 11) /*!< Specify PG11 Pin Data Input/Output */
#define PG12            GPIO_PIN_ADDR(6, 12) /*!< Specify PG12 Pin Data Input/Output */
#define PG13            GPIO_PIN_ADDR(6, 13) /*!< Specify PG13 Pin Data Input/Output */
#define PG14            GPIO_PIN_ADDR(6, 14) /*!< Specify PG14 Pin Data Input/Output */
#define PG15            GPIO_PIN_ADDR(6, 15) /*!< Specify PG15 Pin Data Input/Output */

#define PH0             GPIO_PIN_ADDR(7, 0)  /*!< Specify PH0 Pin Data Input/Output */
#define PH1             GPIO_PIN_ADDR(7, 1)  /*!< Specify PH1 Pin Data Input/Output */
#define PH2             GPIO_PIN_ADDR(7, 2)  /*!< Specify PH2 Pin Data Input/Output */
#define PH3             GPIO_PIN_ADDR(7, 3)  /*!< Specify PH3 Pin Data Input/Output */
#define PH4             GPIO_PIN_ADDR(7, 4)  /*!< Specify PH4 Pin Data Input/Output */
#define PH5             GPIO_PIN_ADDR(7, 5)  /*!< Specify PH5 Pin Data Input/Output */
#define PH6             GPIO_PIN_ADDR(7, 6)  /*!< Specify PH6 Pin Data Input/Output */
#define PH7             GPIO_PIN_ADDR(7, 7)  /*!< Specify PH7 Pin Data Input/Output */
#define PH8             GPIO_PIN_ADDR(7, 8)  /*!< Specify PH8 Pin Data Input/Output */
#define PH9             GPIO_PIN_ADDR(7, 9)  /*!< Specify PH9 Pin Data Input/Output */
#define PH10            GPIO_PIN_ADDR(7, 10) /*!< Specify PH10 Pin Data Input/Output */
#define PH11            GPIO_PIN_ADDR(7, 11) /*!< Specify PH11 Pin Data Input/Output */
#define PH12            GPIO_PIN_ADDR(7, 12) /*!< Specify PH12 Pin Data Input/Output */
#define PH13            GPIO_PIN_ADDR(7, 13) /*!< Specify PH13 Pin Data Input/Output */
#define PH14            GPIO_PIN_ADDR(7, 14) /*!< Specify PH14 Pin Data Input/Output */
#define PH15            GPIO_PIN_ADDR(7, 15) /*!< Specify PH15 Pin Data Input/Output */

#define PI0             GPIO_PIN_ADDR(8, 0)  /*!< Specify PI0 Pin Data Input/Output */
#define PI1             GPIO_PIN_ADDR(8, 1)  /*!< Specify PI1 Pin Data Input/Output */
#define PI2             GPIO_PIN_ADDR(8, 2)  /*!< Specify PI2 Pin Data Input/Output */
#define PI3             GPIO_PIN_ADDR(8, 3)  /*!< Specify PI3 Pin Data Input/Output */
#define PI4             GPIO_PIN_ADDR(8, 4)  /*!< Specify PI4 Pin Data Input/Output */
#define PI5             GPIO_PIN_ADDR(8, 5)  /*!< Specify PI5 Pin Data Input/Output */
#define PI6             GPIO_PIN_ADDR(8, 6)  /*!< Specify PI6 Pin Data Input/Output */
#define PI7             GPIO_PIN_ADDR(8, 7)  /*!< Specify PI7 Pin Data Input/Output */
#define PI8             GPIO_PIN_ADDR(8, 8)  /*!< Specify PI8 Pin Data Input/Output */
#define PI9             GPIO_PIN_ADDR(8, 9)  /*!< Specify PI9 Pin Data Input/Output */
#define PI10            GPIO_PIN_ADDR(8, 10) /*!< Specify PI10 Pin Data Input/Output */
#define PI11            GPIO_PIN_ADDR(8, 11) /*!< Specify PI11 Pin Data Input/Output */
#define PI12            GPIO_PIN_ADDR(8, 12) /*!< Specify PI12 Pin Data Input/Output */
#define PI13            GPIO_PIN_ADDR(8, 13) /*!< Specify PI13 Pin Data Input/Output */
#define PI14            GPIO_PIN_ADDR(8, 14) /*!< Specify PI14 Pin Data Input/Output */
#define PI15            GPIO_PIN_ADDR(8, 15) /*!< Specify PI15 Pin Data Input/Output */

/*@}*/ /* end of group NUC472_442_GPIO_EXPORTED_CONSTANTS */

/** @addtogroup NUC472_442_GPIO_EXPORTED_FUNCTIONS GPIO Exported Functions
  @{
*/

/**
 * @brief       Clear GPIO Pin Interrupt Flag
 *
 * @param[in]   gpio        GPIO port. It could be \ref PA, \ref PB, ... or \ref GPI
 * @param[in]   u32PinMask  The single or multiple pins of specified GPIO port.
 *
 * @return      None
 *
 * @details     Clear the interrupt status of specified GPIO pin.
 */
#define GPIO_CLR_INT_FLAG(gpio, u32PinMask)   ((gpio)->INTSRC = u32PinMask)

/**
 * @brief       Disable Pin De-bounce Function
 *
 * @param[in]   gpio        GPIO port. It could be \ref PA, \ref PB, ... or \ref GPI
 * @param[in]   u32PinMask  The single or multiple pins of specified GPIO port.
 *
 * @return      None
 *
 * @details     Disable the interrupt de-bounce function of specified GPIO pin.
 */
#define GPIO_DISABLE_DEBOUNCE(gpio, u32PinMask)   ((gpio)->DBEN &= ~u32PinMask)

/**
 * @brief       Enable Pin De-bounce Function
 *
 * @param[in]   gpio        GPIO port. It could be \ref PA, \ref PB, ... or \ref GPI
 * @param[in]   u32PinMask  The single or multiple pins of specified GPIO port.
 *
 * @return      None
 *
 * @details     Enable the interrupt de-bounce function of specified GPIO pin.
 */
#define GPIO_ENABLE_DEBOUNCE(gpio, u32PinMask)    ((gpio)->DBEN |= u32PinMask)

/**
 * @brief       Disable I/O Digital Input Path
 *
 * @param[in]   gpio        GPIO port. It could be \ref PA, \ref PB, ... or \ref GPI
 * @param[in]   u32PinMask  The single or multiple pins of specified GPIO port.
 *
 * @return      None
 *
 * @details     Disable I/O digital input path of specified GPIO pin.
 */
#define GPIO_DISABLE_DIGITAL_PATH(gpio, u32PinMask)   ((gpio)->DINOFF |= (u32PinMask << 16))

/**
 * @brief       Enable I/O Digital Input Path
 *
 * @param[in]   gpio        GPIO port. It could be \ref PA, \ref PB, ... or \ref GPI
 * @param[in]   u32PinMask  The single or multiple pins of specified GPIO port.
 *
 * @return      None
 *
 * @details     Enable I/O digital input path of specified GPIO pin.
 */
#define GPIO_ENABLE_DIGITAL_PATH(gpio, u32PinMask)    ((gpio)->DINOFF &= ~(u32PinMask << 16))

/**
 * @brief       Disable I/O DOUT mask
 *
 * @param[in]   gpio        GPIO port. It could be \ref PA, \ref PB, ... or \ref GPI
 * @param[in]   u32PinMask  The single or multiple pins of specified GPIO port.
 *
 * @return      None
 *
 * @details     Disable I/O DOUT mask of specified GPIO pin.
 */
#define GPIO_DISABLE_DOUT_MASK(gpio, u32PinMask)   ((gpio)->DATMSK &= ~u32PinMask)

/**
 * @brief       Enable I/O DOUT mask
 *
 * @param[in]   gpio        GPIO port. It could be \ref PA, \ref PB, ... or \ref GPI
 * @param[in]   u32PinMask  The single or multiple pins of specified GPIO port.
 *
 * @return      None
 *
 * @details     Enable I/O DOUT mask of specified GPIO pin.
 */
#define GPIO_ENABLE_DOUT_MASK(gpio, u32PinMask)    ((gpio)->DATMSK |= u32PinMask)

/**
 * @brief       Get GPIO Pin Interrupt Flag
 *
 * @param[in]   gpio        GPIO port. It could be \ref PA, \ref PB, ... or \ref GPI
 * @param[in]   u32PinMask  The single or multiple pins of specified GPIO port.
 *
 * @retval      0           No interrupt at specified GPIO pin
 * @retval      1           The specified GPIO pin generate an interrupt
 *
 * @details     Get the interrupt status of specified GPIO pin.
 */
#define GPIO_GET_INT_FLAG(gpio, u32PinMask)   ((gpio)->INTSRC & u32PinMask)

/**
 * @brief       Set De-bounce Sampling Cycle Time
 *
 * @param[in]   u32ClkSrc   The de-bounce counter clock source. It could be \ref GPIO_DBCTL_DBCLKSRC_HCLK or \ref GPIO_DBCTL_DBCLKSRC_IRC10K.
 * @param[in]   u32ClkSel   The de-bounce sampling cycle selection. It could be \n
 *                          \ref GPIO_DBCTL_DBCLKSEL_1, \ref GPIO_DBCTL_DBCLKSEL_2, \ref GPIO_DBCTL_DBCLKSEL_4, \ref GPIO_DBCTL_DBCLKSEL_8, \n
 *                          \ref GPIO_DBCTL_DBCLKSEL_16, \ref GPIO_DBCTL_DBCLKSEL_32, \ref GPIO_DBCTL_DBCLKSEL_64, \ref GPIO_DBCTL_DBCLKSEL_128, \n
 *                          \ref GPIO_DBCTL_DBCLKSEL_256, \ref GPIO_DBCTL_DBCLKSEL_512, \ref GPIO_DBCTL_DBCLKSEL_1024, \ref GPIO_DBCTL_DBCLKSEL_2048, \n
 *                          \ref GPIO_DBCTL_DBCLKSEL_4096, \ref GPIO_DBCTL_DBCLKSEL_8192, \ref GPIO_DBCTL_DBCLKSEL_16384, \ref GPIO_DBCTL_DBCLKSEL_32768.
 *
 * @return      None
 *
 * @details     Set the interrupt de-bounce sampling cycle time based on the debounce counter clock source. \n
 *              Example: _GPIO_SET_DEBOUNCE_TIME(GPIO_DBCTL_DBCLKSRC_IRC10K, GPIO_DBCTL_DBCLKSEL_4). \n
 *              It's meaning the De-debounce counter clock source is internal 10 KHz and sampling cycle selection is 4. \n
 *              Then the target de-bounce sampling cycle time is (2^4)*(1/(10*1000)) s = 16*0.0001 s = 1600 us,
 *              and system will sampling interrupt input once per 1600 us.
 */
#define GPIO_SET_DEBOUNCE_TIME(u32ClkSrc, u32ClkSel)  (GPIO->DBCTL = (GPIO_DBCTL_ICLKON_Msk | u32ClkSrc | u32ClkSel))

/**
 * @brief       Get GPIO Port IN Data
 *
 * @param[in]   gpio        GPIO port. It could be \ref PA, \ref PB, ... or \ref GPI
 *
 * @retval      The specified port data
 *
 * @details     Get the PIN register of specified GPIO port.
 */
#define GPIO_GET_IN_DATA(gpio)   ((gpio)->PIN)

/**
 * @brief       Set GPIO Port OUT Data
 *
 * @param[in]   gpio        GPIO port. It could be \ref PA, \ref PB, ... or \ref GPI
 * @param[in]   u32Data     GPIO port data.
 *
 * @retval      None
 *
 * @details     Set the Data into specified GPIO port.
 */
#define GPIO_SET_OUT_DATA(gpio, u32Data)   ((gpio)->DOUT = (u32Data))


/**
 * @brief       Toggle Specified GPIO pin
 *
 * @param[in]   u32Pin       Pxy
 *
 * @retval      None
 *
 * @details     Toggle the specified GPIO pint.
 */
#define GPIO_TOGGLE(u32Pin)   ((u32Pin) ^= 1)

/**
 * @brief       Enable External GPIO interrupt 0
 *
 * @param[in]   gpio            GPIO port. It could be \ref PA, \ref PB, ... or \ref GPI
 * @param[in]   u32Pin          The pin of specified GPIO port.
 * @param[in]   u32IntAttribs   The interrupt attribute of specified GPIO pin. It could be \n
 *                              \ref GPIO_INT_RISING, \ref GPIO_INT_FALLING, \ref GPIO_INT_BOTH_EDGE, \ref GPIO_INT_HIGH, \ref GPIO_INT_LOW.
 *
 * @return      None
 *
 * @details     This function is used to enable specified GPIO pin interrupt.
 */
#define GPIO_EnableEINT0    GPIO_EnableInt


/**
 * @brief       Disable External GPIO interrupt 0
 *
 * @param[in]   gpio        GPIO port. It could be \ref PA, \ref PB, ... or \ref GPI
 * @param[in]   u32Pin      The pin of specified GPIO port. It could be 0 ~ 15.
 *
 * @return      None
 *
 * @details     This function is used to enable specified GPIO pin interrupt.
 */
#define GPIO_DisableEINT0   GPIO_DisableInt


/**
 * @brief       Enable External GPIO interrupt 1
 *
 * @param[in]   gpio            GPIO port. It could be \ref PA, \ref PB, ... or \ref GPI
 * @param[in]   u32Pin          The pin of specified GPIO port.
 * @param[in]   u32IntAttribs   The interrupt attribute of specified GPIO pin. It could be \n
 *                              \ref GPIO_INT_RISING, \ref GPIO_INT_FALLING, \ref GPIO_INT_BOTH_EDGE, \ref GPIO_INT_HIGH, \ref GPIO_INT_LOW.
 *
 * @return      None
 *
 * @details     This function is used to enable specified GPIO pin interrupt.
 */
#define GPIO_EnableEINT1    GPIO_EnableInt


/**
 * @brief       Disable External GPIO interrupt 1
 *
 * @param[in]   gpio        GPIO port. It could be \ref PA, \ref PB, ... or \ref GPI
 * @param[in]   u32Pin      The pin of specified GPIO port. It could be 0 ~ 15.
 *
 * @return      None
 *
 * @details     This function is used to enable specified GPIO pin interrupt.
 */
#define GPIO_DisableEINT1   GPIO_DisableInt

/**
 * @brief       Enable External GPIO interrupt n
 *
 * @param[in]   gpio            GPIO port. It could be \ref PA, \ref PB, ... or \ref GPI
 * @param[in]   u32Pin          The pin of specified GPIO port.
 * @param[in]   u32IntAttribs   The interrupt attribute of specified GPIO pin. It could be \n
 *                              \ref GPIO_INT_RISING, \ref GPIO_INT_FALLING, \ref GPIO_INT_BOTH_EDGE, \ref GPIO_INT_HIGH, \ref GPIO_INT_LOW.
 *
 * @return      None
 *
 * @details     This function is used to enable specified GPIO pin interrupt.
 */
#define GPIO_EnableEINT     GPIO_EnableInt


/**
 * @brief       Disable External GPIO interrupt n
 *
 * @param[in]   gpio        GPIO port. It could be \ref PA, \ref PB, ... or \ref GPI
 * @param[in]   u32Pin      The pin of specified GPIO port. It could be 0 ~ 15.
 *
 * @return      None
 *
 * @details     This function is used to enable specified GPIO pin interrupt.
 */
#define GPIO_DisableEINT    GPIO_DisableInt


void GPIO_SetMode(GPIO_T *gpio, uint32_t u32PinMask, uint32_t u32Mode);
void GPIO_EnableInt(GPIO_T *gpio, uint32_t u32Pin, uint32_t u32IntAttribs);
void GPIO_DisableInt(GPIO_T *gpio, uint32_t u32Pin);



/*@}*/ /* end of group NUC472_442_GPIO_EXPORTED_FUNCTIONS */

/*@}*/ /* end of group NUC472_442_GPIO_Driver */

/*@}*/ /* end of group NUC472_442_Device_Driver */

#ifdef __cplusplus
}
#endif

#endif //__GPIO_H__

/*** (C) COPYRIGHT 2013 Nuvoton Technology Corp. ***/
