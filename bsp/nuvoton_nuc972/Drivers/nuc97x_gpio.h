/*
 * File      : nuc97x_gpio.h
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
#ifndef _NUC970_GPIO_H_
#define _NUC970_GPIO_H_

#include "nuc97x.h"

/// @cond HIDDEN_SYMBOLS
#ifndef GPIO_ERR_PORT_BUSY
#define GPIO_ERR_PORT_BUSY      -1
#define GPIO_ERR_UNSUPPORTED    -2
#define GPIO_ERR_BIT_BUSY       -3
#define SUCCESSFUL              0
#endif

#define MAX_PORT 10  /*!< GPIO Port Number */

#define GPIOA_MASK  0x0000FFFF  /*!< GPIO Port A Mask */
#define GPIOB_MASK  0x0000FFFF  /*!< GPIO Port B Mask */
#define GPIOC_MASK  0x00007FFF  /*!< GPIO Port C Mask */
#define GPIOD_MASK  0x0000FFFF  /*!< GPIO Port D Mask */
#define GPIOE_MASK  0x0000FFFF  /*!< GPIO Port E Mask */
#define GPIOF_MASK  0x0000FFFF  /*!< GPIO Port F Mask */
#define GPIOG_MASK  0x0000FFFF  /*!< GPIO Port G Mask */
#define GPIOH_MASK  0x0000FFFF  /*!< GPIO Port H Mask */
#define GPIOI_MASK  0x0000FFFF  /*!< GPIO Port I Mask */
#define GPIOJ_MASK  0x0000003F  /*!< GPIO Port J Mask */


typedef INT32 (*GPIO_CALLBACK)(UINT32 status, UINT32 userData);
typedef INT32 (*EINT_CALLBACK)(UINT32 status, UINT32 userData);

/** \brief  Structure type of GPIO_PORT
 */
typedef enum {
    GPIOA=0x000,   /*!< Port A offset of GPIO base address      */
    GPIOB=0x040,   /*!< Port B offset of GPIO base address      */
    GPIOC=0x080,   /*!< Port C offset of GPIO base address      */
    GPIOD=0x0C0,   /*!< Port D offset of GPIO base address      */
    GPIOE=0x100,   /*!< Port E offset of GPIO base address      */
    GPIOF=0x140,   /*!< Port F offset of GPIO base address      */
    GPIOG=0x180,   /*!< Port G offset of GPIO base address      */
    GPIOH=0x1C0,   /*!< Port H offset of GPIO base address      */
    GPIOI=0x200,   /*!< Port I offset of GPIO base address      */
    GPIOJ=0x240,   /*!< Port J offset of GPIO base address      */
} GPIO_PORT;


#define    GPIO_Pin_0      ((UINT32)0x00000001)  /* Pin 0  selected */
#define    GPIO_Pin_1      ((UINT32)0x00000002)  /* Pin 1  selected */
#define    GPIO_Pin_2      ((UINT32)0x00000004)  /* Pin 2  selected */
#define    GPIO_Pin_3      ((UINT32)0x00000008)  /* Pin 3  selected */
#define    GPIO_Pin_4      ((UINT32)0x00000010)  /* Pin 4  selected */
#define    GPIO_Pin_5      ((UINT32)0x00000020)  /* Pin 5  selected */
#define    GPIO_Pin_6      ((UINT32)0x00000040)  /* Pin 6  selected */
#define    GPIO_Pin_7      ((UINT32)0x00000080)  /* Pin 7  selected */
#define    GPIO_Pin_8      ((UINT32)0x00000100)  /* Pin 8  selected */
#define    GPIO_Pin_9      ((UINT32)0x00000200)  /* Pin 9  selected */
#define    GPIO_Pin_10     ((UINT32)0x00000400)  /* Pin 10 selected */
#define    GPIO_Pin_11     ((UINT32)0x00000800)  /* Pin 11 selected */
#define    GPIO_Pin_12     ((UINT32)0x00001000)  /* Pin 12 selected */
#define    GPIO_Pin_13     ((UINT32)0x00002000)  /* Pin 13 selected */
#define    GPIO_Pin_14     ((UINT32)0x00004000)  /* Pin 14 selected */
#define    GPIO_Pin_15     ((UINT32)0x00008000)  /* Pin 15 selected */
#define    GPIO_Pin_16     ((UINT32)0x00010000)  /* Pin 16 selected */
#define    GPIO_Pin_17     ((UINT32)0x00020000)  /* Pin 17 selected */
#define    GPIO_Pin_18     ((UINT32)0x00040000)  /* Pin 18 selected */
#define    GPIO_Pin_19     ((UINT32)0x00080000)  /* Pin 19 selected */
#define    GPIO_Pin_20     ((UINT32)0x00100000)  /* Pin 20 selected */
#define    GPIO_Pin_21     ((UINT32)0x00200000)  /* Pin 21 selected */
#define    GPIO_Pin_22     ((UINT32)0x00400000)  /* Pin 22 selected */
#define    GPIO_Pin_23     ((UINT32)0x00800000)  /* Pin 23 selected */
#define    GPIO_Pin_24     ((UINT32)0x01000000)  /* Pin 24 selected */
#define    GPIO_Pin_25     ((UINT32)0x02000000)  /* Pin 25 selected */
#define    GPIO_Pin_26     ((UINT32)0x04000000)  /* Pin 26 selected */
#define    GPIO_Pin_27     ((UINT32)0x08000000)  /* Pin 27 selected */
#define    GPIO_Pin_28     ((UINT32)0x10000000)  /* Pin 28 selected */
#define    GPIO_Pin_29     ((UINT32)0x20000000)  /* Pin 29 selected */
#define    GPIO_Pin_30     ((UINT32)0x40000000)  /* Pin 30 selected */
#define    GPIO_Pin_31     ((UINT32)0x80000000)  /* Pin 31 selected */

#define    GPIO_Pin_All   ((uint32_t)0xFFFFFFFF)  /* All pins selected */


/** \brief  Structure type of GPIO_DIR
 */
typedef enum {
    DIR_INPUT,   /*!< GPIO Output mode      */
    DIR_OUTPUT   /*!< GPIO Input mode      */
} GPIO_DIR;

/** \brief  Structure type of GPIO_PULL
 */
typedef enum {
    NO_PULL_UP, /*!< GPIO Pull-Up Disable */
    PULL_UP     /*!< GPIO Pull-Up Enable */
} GPIO_PULL;

/** \brief  Structure type of GPIO_DRV
 */
typedef enum {
    DRV_LOW,   /*!< GPIO Set to Low */
    DRV_HIGH   /*!< GPIO Set to High */
} GPIO_DRV;

/** \brief  Structure type of GPIO_NIRQ
 */
typedef enum {
    NIRQ0=0,   /*!< External interrupt 0 */
    NIRQ1,     /*!< External interrupt 1 */
    NIRQ2,     /*!< External interrupt 2 */
    NIRQ3,     /*!< External interrupt 3 */
    NIRQ4,     /*!< External interrupt 4 */
    NIRQ5,     /*!< External interrupt 5 */
    NIRQ6,     /*!< External interrupt 6 */
    NIRQ7,     /*!< External interrupt 7 */
} GPIO_NIRQ;

/** \brief  Structure type of GPIO_TRIGGER_TYPE
 */
typedef enum {
    LOW,                   /*!< Trigger type set low */
    HIGH,                  /*!< Trigger type set high */
    FALLING,               /*!< Trigger type set falling edge */
    RISING,                /*!< Trigger type set rising edge */
    BOTH_EDGE              /*!< Trigger type set falling edge and rising edge */
} GPIO_TRIGGER_TYPE;

/// @cond HIDDEN_SYMBOLS
typedef struct {
    UINT16          bitBusyFlag[MAX_PORT];
    GPIO_CALLBACK   IRQCallback[MAX_PORT];
    UINT32          IRQUserData[MAX_PORT];
    EINT_CALLBACK   EINTIRQCallback[8];
    UINT32          EINTIRQUserData[8];
} GPIO_CFG;
/// @endcond HIDDEN_SYMBOLS


/** @addtogroup NUC970_GPIO_EXPORTED_FUNCTIONS GPIO Exported Functions
  @{
*/

INT32 GPIO_Open(GPIO_PORT port, GPIO_DIR direction, GPIO_PULL pull);
INT32 GPIO_Close(GPIO_PORT port);
INT32 GPIO_Set(GPIO_PORT port, UINT32 bitMap);
INT32 GPIO_Clr(GPIO_PORT port, UINT32 bitMap);
UINT32 GPIO_ReadPort(GPIO_PORT port);
INT32 GPIO_SetPortDir(GPIO_PORT port, GPIO_DIR direction);

/* General GPIO bit function */
INT32 GPIO_OpenBit(GPIO_PORT port, UINT32 bit, GPIO_DIR direction, GPIO_PULL pull);
INT32 GPIO_CloseBit(GPIO_PORT port, UINT32 bit);
INT32 GPIO_SetBit(GPIO_PORT port, UINT32 bit);
INT32 GPIO_ClrBit(GPIO_PORT port, UINT32 bit);
INT32 GPIO_ReadBit(GPIO_PORT port, UINT32 bit);
INT32 GPIO_SetBitDir(GPIO_PORT port, UINT32 bit, GPIO_DIR direction);
INT32 GPIO_EnableTriggerType(GPIO_PORT port, UINT32 bit, GPIO_TRIGGER_TYPE triggerType);
INT32 GPIO_DisableTriggerType(GPIO_PORT port, UINT32 bit);
INT32 GPIO_EnableInt(GPIO_PORT port, GPIO_CALLBACK callback, UINT32 userData);
INT32 GPIO_DisableInt(GPIO_PORT port);
INT32 GPIO_ClrISR(GPIO_PORT port, UINT32 bit);
INT32 GPIO_ClrISRBit(GPIO_PORT port, UINT32 bit);

/* GPIO status function */
BOOL GPIO_BitIsUsed(GPIO_PORT port, UINT32 bit);

/* External GPIO interrupt function */
INT32 GPIO_EnableEINT(GPIO_NIRQ nIrq, GPIO_CALLBACK callback, UINT32 userData);
INT32 GPIO_DisableEINT(GPIO_NIRQ nIrq);
INT32 GPIO_EnableDebounce(INT32 debounceClkSel);
INT32 GPIO_DisableDebounce(void);

#endif /* _NUC970_GPIO_H_ */
