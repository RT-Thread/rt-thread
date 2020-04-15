/*******************************************************************
* *file       : ES32F0271_sub.h
* *description: ES32F0271 Device Head File
* *author     : Eastsoft AE Team
* *version    : V1.00.01
* *data       : 4/10/2018
*
* *Copyright (C) 2018 Shanghai Eastsoft Microelectronics Co., Ltd.
*******************************************************************/

/** @addtogroup CMSIS
  * @{
  */
 
/** @addtogroup ES32F0271_SUB1
  * @{
  */

#ifndef __ES32F0271_SUB_H__
#define __ES32F0271_SUB_H__

#ifdef __cplusplus
extern "C"{
#endif

/** 
  * @brief defines 'read only' 、'write only'、 'read / write' permissions.
  */
#define __I   volatile const  /* defines 'read only' permissions */
#define __O   volatile        /* defines 'write only' permissions */
#define __IO  volatile        /* defines 'read / write' permissions */
  
/** @addtogroup Configuration_section_for_CMSIS
  * @{
  */
/** 
  * @brief configuration of the cortex-M3 processor and core peripherals.
  */  

#define __MPU_PRESENT           0       /*!< cm0ikmcu does not provide a MPU present or not       */
#define __NVIC_PRIO_BITS        2       /*!< cm0ikmcu Supports 2 Bits for the Priority Levels     */
#define __Vendor_SysTickConfig  0       /*!< Set to 1 if different SysTick Config is used         */
/**
  * @}
  */ 

/** @addtogroup peripherals_interrupt_number_definition
  * @{
  */

typedef enum IRQn
{

  /****** ES32 Processor Exceptions Numbers ******************************************************/

  /***************        Cortex-M0 Processor Exceptions Numbers        **************************/
  NonMaskableInt_IRQn   = -14,      /*!< 2 Non Maskable Interrupt                               */
  HardFault_IRQn        = -13,      /*!< 3 Cortex-M0 Hard Fault Interrupt                       */
  SVCall_IRQn           = -5,       /*!< 11 Cortex-M0 SV Call Interrupt                         */
  PendSV_IRQn           = -2,       /*!< 14 Cortex-M0 Pend SV Interrupt                         */
  SysTick_IRQn          = -1,       /*!< 15 Cortex-M0 System Tick Interrupt                     */

  /****************        ES32F0271_SUB specific Exceptions Numbers        **************************/
  WWDT_IRQn             = 0,        /*  0       | WWDT          Interrupt                       */
  PVD_IRQn              = 1,        /*  1       | PVD           Interrupt   EXTI[20]            */
  RTC_IRQn              = 2,        /*  2       | RTC           Interrupt                       */
  WAKEUP_IRQn           = 3,        /*  3       | WAKEUP        Interrupt   EXTI[21]            */
  CM0IKMCU_IRQ04_IRQn   = 4,        /*  4       |               Interrupt                       */
  EXTI_0to1_IRQn        = 5,        /*  5       | EXTI[1:0]     Interrupt   GPIOx[1:0]          */
  EXTI_2to3_IRQn        = 6,        /*  6       | EXTI[3:2]     Interrupt   GPIOx[3:2]          */
  EXTI_4to15_IRQn       = 7,        /*  7       | EXTI[15:4]    Interrupt   GPIOx[15:4]         */
  CM0IKMCU_IRQ08_IRQn   = 8,        /*  8       |               Interrupt                       */
  DMA1_CH0_IRQn         = 9,        /*  9       | DMA1_CH0      Interrupt                       */
  DMA1_CH12_IRQn        = 10,       /*  10      | DMA1_CH12     Interrupt                       */
  DMA1_CH345_IRQn       = 11,       /*  11      | DMA1_CH345    Interrupt                       */
  ADC_CMP_IRQn          = 12,       /*  12      | ADC/COMP0-3   Interrupt   EXTI[19:16])        */
  AD16C4T1_IRQn         = 13,       /*  13      | AD16C4T1      Interrupt                       */
  BS16T1_IRQn           = 14,       /*  14      | BS16T1        Interrupt                       */
  GP32C4T1_IRQn         = 15,       /*  15      | GP32C4T1      Interrupt                       */
  GP16C4T1_IRQn         = 16,       /*  16      | GP16C4T1      Interrupt                       */
  GP16C4T2_IRQn         = 17,       /*  17      | GP16C4T2      Interrupt                       */
  GP16C4T3_IRQn         = 18,       /*  18      | GP16C4T3      Interrupt                       */
  GP16C2T1_IRQn         = 19,       /*  19      | GP16C2T1      Interrupt                       */
  GP16C2T2_IRQn         = 20,       /*  20      | GP16C2T2      Interrupt                       */
  GP16C2T3_IRQn         = 21,       /*  21      | GP16C2T3      Interrupt                       */
  GP16C2T4_IRQn         = 22,       /*  22      | GP16C2T4      Interrupt                       */
  I2C1_IRQn             = 23,       /*  23      | I2C1          Interrupt                       */
  I2C2_IRQn             = 24,       /*  24      | I2C2          Interrupt                       */
  SPI1_IRQn             = 25,       /*  25      | SPI1          Interrupt                       */
  SPI2_IRQn             = 26,       /*  26      | SPI2          Interrupt                       */
  UART1_IRQn            = 27,       /*  27      | UART1         Interrupt                       */
  UART2_IRQn            = 28,       /*  28      | UART2         Interrupt                       */
  UART3_IRQn            = 29,       /*  29      | UART3         Interrupt                       */
  SUART12_IRQn          = 30,       /*  30      | SUART1/2      Interrupt                       */
  USB_IRQn              = 31        /*  31      | USB           Interrupt                       */
} IRQn_Type;

/**
  * @}
  */ 

/* Includes-------------------------------------------------------------------------------*/

#include "core_cm0.h"
#include <stdint.h>
#include <stdbool.h>
#include "system_es32f027x.h"
/** 
  * @brief these files declare Peripheral register bit_definition.
  */
#include "reg_rcu.h"
#include "reg_syscfg.h"
#include "reg_fc.h"
#include "reg_dma.h"
#include "reg_gpio.h"
#include "reg_i2c.h"
#include "reg_uart.h"
#include "reg_adc.h"
#include "reg_cmp.h"
#include "reg_dac.h"
#include "reg_spi.h"
#include "reg_crc.h"
#include "reg_ad16c4t.h"
#include "reg_hdiv.h"
#include "reg_aes.h"
#include "reg_wwdt.h"
#include "reg_rtc.h"
#include "reg_mswd.h"
#include "reg_mcm.h"
#include "reg_exti.h"
#include "reg_usb.h"

/******************************************************************************/
/*                              Peripheral register                           */
/******************************************************************************/

/*   allow anonymous structures and anonymous enumeration    */
/* #pragma anon_unions */

/******************************************************************************/
/*                            Peripheral memory map                           */
/******************************************************************************/
 
/*********************      Base addresses        *************************/
#define FLASH_BASE        (0x08000000UL)
#define FLASH_INFO_BASE   (0x1FFFE000UL)  /* EFLASH Info  ( 6K Bytes) - Boot Loader Memory */
#define SRAM_BASE         (0x20000000UL)
#define APB1_BASE         (0x40000000UL)
#define APB2_BASE         (0x40010000UL)
#define AHB1_BASE         (0x40020000UL)
#define AHB2_BASE         (0x48000000UL)
#define CM0IN_BASE        (0xE0000000UL)

/* Cortex簧-M0 internal Peripherals - CM0IN_BASE: 0xE0000000*/
#define TICK_BASE         (CM0IN_BASE     + 0xE010)

#define SRAM1_BASE        (SRAM_BASE      + 0x0000)   // SRAM1 Memory ( 4K Bytes)
#define SRAM2_BASE        (SRAM_BASE      + 0x1000)   // SRAM2 Memory ( 4K Bytes) for Rev.B
#define STACK_SIZE        0x00000400>>2               // Stack size (in Words)
#define SRAMTOP           0x1000//0x2000              // Jackey 2018.9.5

/*****************     peripherals base addresses      ********************/
/* APB1 */
#define GP32C4T1_BASE     (APB1_BASE      + 0x0000)
#define GP16C4T1_BASE     (APB1_BASE      + 0x0400)
#define GP16C4T2_BASE     (APB1_BASE      + 0x0800)
#define GP16C4T3_BASE     (APB1_BASE      + 0x0C00)
#define BS16T1_BASE       (APB1_BASE      + 0x1000)
#define WWDT_BASE         (APB1_BASE      + 0x2C00)
#define IWDT_BASE         (APB1_BASE      + 0x3000)
#define SPI2_BASE         (APB1_BASE      + 0x3800)
#define UART2_BASE        (APB1_BASE      + 0x4400)
#define UART3_BASE        (APB1_BASE      + 0x4800)
#define SUART1_BASE       (APB1_BASE      + 0x4C00)
#define SUART2_BASE       (APB1_BASE      + 0x5000)
#define I2C1_BASE         (APB1_BASE      + 0x5400)
#define I2C2_BASE         (APB1_BASE      + 0x5800)
#define DAC_BASE          (APB1_BASE      + 0x5C00)
#define PWR_BASE          (APB1_BASE      + 0x7000)
/* APB2 */
#define EXTI_BASE         (APB2_BASE      + 0x0400)
#define ADC_BASE          (APB2_BASE      + 0x2400)
#define AD16C4T1_BASE     (APB2_BASE      + 0x2C00)
#define SPI1_BASE         (APB2_BASE      + 0x3000)
#define UART1_BASE        (APB2_BASE      + 0x3800)
#define GP16C2T1_BASE     (APB2_BASE      + 0x4000)
#define GP16C2T2_BASE     (APB2_BASE      + 0x4400)
#define GP16C2T3_BASE     (APB2_BASE      + 0x4800)
#define GP16C2T4_BASE     (APB2_BASE      + 0x4C00)
#define MCM_BASE          (APB2_BASE      + 0x5400)
#define DBGMCU_BASE       (APB2_BASE      + 0x5800)
#define COMP_BASE         (APB2_BASE      + 0x5C00)
/* AHB1 */
#define DMA1_BASE         (AHB1_BASE      + 0x0000)
#define RCU_BASE          (AHB1_BASE      + 0x1000)
#define SYSCFG_BASE       (AHB1_BASE      + 0x1400)
#define RTC_BASE          (AHB1_BASE      + 0x1800)
#define EFLASH_BASE       (AHB1_BASE      + 0x2000)
#define MSWD_BASE         (AHB1_BASE      + 0x2C00)
#define CRC_BASE          (AHB1_BASE      + 0x3000)
#define AES_BASE          (AHB1_BASE      + 0x3400)
#define USB_BASE          (AHB1_BASE      + 0x3800)
#define HDIV_BASE         (AHB1_BASE      + 0x3C00)
/* AHB2 */
#define GPIOA_BASE        (AHB2_BASE      + 0x0000)
#define GPIOB_BASE        (AHB2_BASE      + 0x0400)
#define GPIOC_BASE        (AHB2_BASE      + 0x0800)
#define GPIOD_BASE        (AHB2_BASE      + 0x0C00)
#define GPIOE_BASE        (AHB2_BASE      + 0x1000)
#define GPIOF_BASE        (AHB2_BASE      + 0x1400)

/*********************      Peripheral declaration        *************************/
#define TICK              (( TICK_TypeDef     *)     TICK_BASE)
#define GPIOA             (( GPIO_TypeDef     *)    GPIOA_BASE)
#define GPIOB             (( GPIO_TypeDef     *)    GPIOB_BASE)
#define GPIOC             (( GPIO_TypeDef     *)    GPIOC_BASE)
#define GPIOD             (( GPIO_TypeDef     *)    GPIOD_BASE)
#define DMA1              (( DMA_TypeDef      *)     DMA1_BASE)
#define RCU               (( RCU_TypeDef      *)      RCU_BASE)
#define SYSCFG            (( SYSCFG_TypeDef   *)   SYSCFG_BASE)
#define FC                (( FC_TypeDef       *)   EFLASH_BASE)
#define CRC               (( CRC_TypeDef      *)      CRC_BASE)
#define AES               (( AES_TypeDef      *)      AES_BASE)
#define HDIV              (( HDIV_TypeDef     *)     HDIV_BASE)
#define MSWD              (( MSWD_TypeDef     *)     MSWD_BASE)
#define USB               (( USBCTRL_TypeDef  *)      USB_BASE)
#define USBH              (( USBCTRL_TypeDef  *)      USB_BASE)
#define USBD              (( USBCTRL_TypeDef  *)      USB_BASE)
#define IWDT              (( IWDT_TypeDef     *)     IWDT_BASE)
#define WWDT              (( WWDT_TypeDef     *)     WWDT_BASE)
#define ADC               (( ADC_TypeDef      *)      ADC_BASE)
#define AD16C4T1          (( AD16C4T_TypeDef  *) AD16C4T1_BASE)
#define GP32C4T1          (( AD16C4T_TypeDef  *) GP32C4T1_BASE)
#define GP16C4T1          (( AD16C4T_TypeDef  *) GP16C4T1_BASE)
#define GP16C4T2          (( AD16C4T_TypeDef  *) GP16C4T2_BASE)
#define GP16C4T3          (( AD16C4T_TypeDef  *) GP16C4T3_BASE)
#define GP16C2T1          (( AD16C4T_TypeDef  *) GP16C2T1_BASE)
#define GP16C2T2          (( AD16C4T_TypeDef  *) GP16C2T2_BASE)
#define GP16C2T3          (( AD16C4T_TypeDef  *) GP16C2T3_BASE)
#define GP16C2T4          (( AD16C4T_TypeDef  *) GP16C2T4_BASE)
#define BS16T1            (( AD16C4T_TypeDef  *)   BS16T1_BASE)
#define SPI1              (( SPI_TypeDef      *)     SPI1_BASE)
#define SPI2              (( SPI_TypeDef      *)     SPI2_BASE)
#define I2C1              (( I2C_TypeDef      *)     I2C1_BASE)
#define I2C2              (( I2C_TypeDef      *)     I2C2_BASE)
#define DAC               (( DAC_TypeDef      *)      DAC_BASE)
#define CMP               (( CMP_TypeDef      *)     COMP_BASE)
#define UART1             (( UART_TypeDef     *)    UART1_BASE)
#define UART2             (( UART_TypeDef     *)    UART2_BASE)
#define UART3             (( UART_TypeDef     *)    UART3_BASE)
#define SUART1            (( UART_TypeDef     *)   SUART1_BASE)
#define SUART2            (( UART_TypeDef     *)   SUART2_BASE)
#define EXTI              (( EXTI_TypeDef     *)     EXTI_BASE)
#define RTC               (( RTC_TypeDef      *)      RTC_BASE)
#define MCM               (( MCM_TypeDef      *)      MCM_BASE)
/*   Special stuff */
#define MSG_INCR          ( __IO uint8_t  *) (DBGMCU_BASE + 0x50)
#define MSG_WR            ( __IO uint32_t *) (DBGMCU_BASE + 0x54)
#define MSG_END           ( __IO uint32_t *) (DBGMCU_BASE + 0x58)
#define MSG_INCR_S        ( __IO uint32_t *) (DBGMCU_BASE + 0x5C)
#define MSG_INCR_X        ( __IO uint32_t *) (DBGMCU_BASE + 0x60)
#define MSG_INCR_B        ( __IO uint32_t *) (DBGMCU_BASE + 0x64)
#define MSG_PTR           ( __IO uint8_t **) (DBGMCU_BASE + 0x68)
#define MSG_INCR_D        ( __IO uint32_t *) (DBGMCU_BASE + 0x78)
#define INCR_ERR_CNT      ( __IO uint32_t *) (DBGMCU_BASE + 0x6C)

#define END_SIM     *MSG_END
#define SIM_FAIL    0xFFFFAAAA
#define SIM_PASS    0xFFFF5555
/******************************************************************************/
/*                                          macros                            */
/******************************************************************************/  

/** @addtogroup Public_macros
  * @{
  */
#if defined (__CC_ARM)
#define __INLINE__  __inline
#else
#define __INLINE__  inline
#endif

#define __isr__

#define UNUSED(x) ((void)(x))

#ifdef USE_ASSERT
#define assert_param(x)   \
do                        \
{                         \
  if (!(x))               \
  {                       \
    __disable_irq();      \
    while (1)             \
    ;                     \
  }                       \
} while (0)
#else
#define assert_param(x)
#endif

#define BIT(x)                   ((uint32_t)((uint32_t)0x01U<<(x)))

#define BITS(start, end)         ((0xFFFFFFFFUL << (start)) &\
                                  (0xFFFFFFFFUL >> (31U - (uint32_t)(end)))) 

#define SET_BIT(REG, SETMASK)     ((REG) |= (SETMASK))

#define CLEAR_BIT(REG, SETMASK)   ((REG) &= ~(SETMASK))

#define READ_BIT(REG, SETMASK)    ((REG) & (SETMASK))

#define CLEAR_REG(REG)            ((REG) = (0x0))

#define WRITE_REG(REG, VAL)       ((REG) = (VAL))

#define READ_REG(REG)             ((REG))

#define MODIFY_REG(REG, CLEARMASK, SETMASK)  WRITE_REG((REG), (((READ_REG(REG)) & (~(CLEARMASK))) | (SETMASK)))

#define POSITION_VAL(VAL)         (__CLZ(__RBIT(VAL)))

/** 
  * @}
  */

/******************************************************************************/
/*                                types                                       */
/******************************************************************************/  
/** @addtogroup Public_types
  * @{
  */
typedef enum 
{  
  DISABLE = 0,
  ENABLE = !DISABLE
} TypeFunc,FuncState;
#define IS_FUNC_STATE(x) (((x) == DISABLE) || ((x) == ENABLE))

typedef enum 
{
  RESET = 0, 
  SET = !RESET
} FlagStatus, ITStatus, PinStatus;

typedef enum 
{
  ERROR = 0, 
  SUCCESS = !ERROR
} ErrorStatus;

typedef enum 
{
  BIT_RESET = 0x0,
  BIT_SET   = 0x1,
} BitStatus;

typedef enum 
{
  FALSE = 0x0,
  TRUE  = 0x1,
} TypeBool;

typedef enum 
{
  UNLOCK = 0x0,
  LOCK   = 0x1,
} LockState;
#define IS_LOCK_STATE(x) (((x) == UNLOCK) || ((x) == LOCK))

/** 
  * @} Public_types
  */

#ifdef __cplusplus
}
#endif  

#endif

/** 
  * @} ES32F0271_SUB
  */
  
/** 
  * @} CMSIS
  */

/************* (C) COPYRIGHT Eastsoft Microelectronics *****END OF FILE****/
