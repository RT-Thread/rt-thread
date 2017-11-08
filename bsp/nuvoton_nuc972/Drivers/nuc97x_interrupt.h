/*
 * File      : nuc97x_interrupt.h
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2006, RT-Thread Development Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rt-thread.org/license/LICENSE
 *
 * Change Logs:
 * Date           Author		Notes
 * 2017/11/08     Urey			first version
 */
#ifndef _NUC970_INTERRUPT_H_
#define _NUC970_INTERRUPT_H_

/**
 * @details  Interrupt Number Definition.
 */
typedef enum IRQn {

    /******  NUC970 Specific Interrupt Numbers *****************************************/
    WDT_IRQn                = 1,       /*!< Watch Dog Timer Interrupt                  */
    WWDT_IRQn               = 2,       /*!< Windowed-WDT Interrupt                     */
    LVD_IRQn                = 3,       /*!< Low Voltage Detect Interrupt               */
    EINT0_IRQn              = 4,       /*!< External Interrupt 0                       */
    EINT1_IRQn              = 5,       /*!< External Interrupt 1                       */
    EINT2_IRQn              = 6,       /*!< External Interrupt 2                       */
    EINT3_IRQn              = 7,       /*!< External Interrupt 3                       */
    EINT4_IRQn              = 8,       /*!< External Interrupt 4                       */
    EINT5_IRQn              = 9,       /*!< External Interrupt 5                       */
    EINT6_IRQn              = 10,      /*!< External Interrupt 6                       */
    EINT7_IRQn              = 11,      /*!< External Interrupt 7                       */
    ACTL_IRQn               = 12,      /*!< Audio Controller Interrupt                 */
    LCD_IRQn                = 13,      /*!< LCD Controller Interrupt                   */
    CAP_IRQn                = 14,      /*!< Sensor Interface Controller Interrupt      */
    RTC_IRQn                = 15,      /*!< Real Time Clock Interrupt                  */
    TMR0_IRQn               = 16,      /*!< Timer 0 Interrupt                          */
    TMR1_IRQn               = 17,      /*!< Timer 1 Interrupt                          */
    ADC_IRQn                = 18,      /*!< ADC Interrupt                              */
    EMC0_RX_IRQn            = 19,      /*!< EMC 0 RX Interrupt                         */
    EMC1_RX_IRQn            = 20,      /*!< EMC 1 RX Interrupt                         */
    EMC0_TX_IRQn            = 21,      /*!< EMC 0 TX Interrupt                         */
    EMC1_TX_IRQn            = 22,      /*!< EMC 1 TX Interrupt                         */
    EHCI_IRQn               = 23,      /*!< USB 2.0 Host Controller Interrupt          */
    OHCI_IRQn               = 24,      /*!< USB 1.1 Host Controller Interrupt          */
    GDMA0_IRQn              = 25,      /*!< GDMA Channel 0 Interrupt                   */
    GDMA1_IRQn              = 26,      /*!< GDMA Channel 1 Interrupt                   */
    SDH_IRQn                = 27,      /*!< SD/SDIO Host Interrupt                     */
    FMI_IRQn                = 28,      /*!< FMI Interrupt                              */
    USBD_IRQn               = 29,      /*!< USB Device Interrupt                       */
    TMR2_IRQn               = 30,      /*!< Timer 2 Interrupt                          */
    TMR3_IRQn               = 31,      /*!< Timer 3 Interrupt                          */
    TMR4_IRQn               = 32,      /*!< Timer 4 Interrupt                          */
    JPEG_IRQn               = 33,      /*!< JPEG Engine Interrupt                      */
    GE2D_IRQn               = 34,      /*!< 2D Graphic Engine Interrupt                */
    CRPT_IRQn               = 35,      /*!< Cryptographic Accelerator Interrupt        */
    UART0_IRQn              = 36,      /*!< UART 0 Interrupt                           */
    UART1_IRQn              = 37,      /*!< UART 1 Interrupt                           */
    UART2_IRQn              = 38,      /*!< UART 2 Interrupt                           */
    UART4_IRQn              = 39,      /*!< UART 4 Interrupt                           */
    UART6_IRQn              = 40,      /*!< UART 6 Interrupt                           */
    UART8_IRQn              = 41,      /*!< UART 8 Interrupt                           */
    UART10_IRQn             = 42,      /*!< UART 10 Interrupt                          */
    UART3_IRQn              = 43,      /*!< UART 3 Interrupt                           */
    UART5_IRQn              = 44,      /*!< UART 5 Interrupt                           */
    UART7_IRQn              = 45,      /*!< UART 7 Interrupt                           */
    UART9_IRQn              = 46,      /*!< UART 9 Interrupt                           */
    ETMR0_IRQn              = 47,      /*!< Enhanced Timer 0 Interrupt                 */
    ETMR1_IRQn              = 48,      /*!< Enhanced Timer 1 Interrupt                 */
    ETMR2_IRQn              = 49,      /*!< Enhanced Timer 2 Interrupt                 */
    ETMR3_IRQn              = 50,      /*!< Enhanced Timer 3 Interrupt                 */
    SPI0_IRQn               = 51,      /*!< SPI 0 Interrupt                            */
    SPI1_IRQn               = 52,      /*!< SPI 1 Interrupt                            */
    I2C0_IRQn               = 53,      /*!< I2C 0 Interrupt                            */
    I2C1_IRQn               = 54,      /*!< I2C 1 Interrupt                            */
    SC0_IRQn                = 55,      /*!< Smart Card 0 Interrupt                     */
    SC1_IRQn                = 56,      /*!< Smart Card 1 Interrupt                     */
    GPIO_IRQn               = 57,      /*!< GPIO Interrupt                             */
    CAN0_IRQn               = 58,      /*!< CAN 0 Interrupt                            */
    CAN1_IRQn               = 59,      /*!< CAN 1 Interrupt                            */
    PWM_IRQn                = 60,      /*!< PWM Interrupt                              */
    KPI_IRQn                = 61,      /*!< KPI Interrupt                              */
} IRQn_Type;


/* The parameters for sysSetInterruptPriorityLevel() and sysInstallISR() use */
#define FIQ_LEVEL_0     0       /*!< FIQ Level 0 */
#define IRQ_LEVEL_1     1       /*!< IRQ Level 1 */
#define IRQ_LEVEL_2     2       /*!< IRQ Level 2 */
#define IRQ_LEVEL_3     3       /*!< IRQ Level 3 */
#define IRQ_LEVEL_4     4       /*!< IRQ Level 4 */
#define IRQ_LEVEL_5     5       /*!< IRQ Level 5 */
#define IRQ_LEVEL_6     6       /*!< IRQ Level 6 */
#define IRQ_LEVEL_7     7       /*!< IRQ Level 7 */

/* The parameters for rt_hw_interrupt_set_type() use */
#define LOW_LEVEL_SENSITIVE        0x00
#define HIGH_LEVEL_SENSITIVE       0x40
#define NEGATIVE_EDGE_TRIGGER      0x80
#define POSITIVE_EDGE_TRIGGER      0xC0


void rt_hw_interrupt_set_priority(int vector,int priority);
void rt_hw_interrupt_set_type(int vector,int type);

#endif /* _NUC970_INTERRUPT_H_ */
