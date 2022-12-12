/******************************************************************************
* Copyright (C) 2010 - 2020 Xilinx, Inc.  All rights reserved.
* SPDX-License-Identifier: MIT
******************************************************************************/

/*****************************************************************************/
/**
*
* @file xgpiops.h
* @addtogroup gpiops_v3_7
* @{
* @details
*
* The Xilinx PS GPIO driver. This driver supports the Xilinx PS GPIO
* Controller.
*
* The GPIO Controller supports the following features:
*    - 4 banks
*    - Masked writes (There are no masked reads)
*    - Bypass mode
*    - Configurable Interrupts (Level/Edge)
*
* This driver is intended to be RTOS and processor independent. Any needs for
* dynamic memory management, threads or thread mutual exclusion, virtual
* memory, or cache control must be satisfied by the layer above this driver.

* This driver supports all the features listed above, if applicable.
*
* <b>Driver Description</b>
*
* The device driver enables higher layer software (e.g., an application) to
* communicate to the GPIO.
*
* <b>Interrupts</b>
*
* The driver provides interrupt management functions and an interrupt handler.
* Users of this driver need to provide callback functions. An interrupt handler
* example is available with the driver.
*
* <b>Threads</b>
*
* This driver is not thread safe. Any needs for threads or thread mutual
* exclusion must be satisfied by the layer above this driver.
*
* <b>Asserts</b>
*
* Asserts are used within all Xilinx drivers to enforce constraints on argument
* values. Asserts can be turned off on a system-wide basis by defining, at
* compile time, the NDEBUG identifier. By default, asserts are turned on and it
* is recommended that users leave asserts on during development.
*
* <b>Building the driver</b>
*
* The XGpioPs driver is composed of several source files. This allows the user
* to build and link only those parts of the driver that are necessary.
* <br><br>
*
* <pre>
* MODIFICATION HISTORY:
*
* Ver   Who  Date     Changes
* ----- ---- -------- -----------------------------------------------
* 1.00a sv   01/15/10 First Release
* 1.01a sv   04/15/12 Removed the APIs XGpioPs_SetMode, XGpioPs_SetModePin
*                     XGpioPs_GetMode, XGpioPs_GetModePin as they are not
*              relevant to Zynq device.The interrupts are disabled
*              for output pins on all banks during initialization.
* 1.02a hk   08/22/13 Added low level reset API
* 2.1   hk   04/29/14 Use Input data register DATA_RO for read. CR# 771667.
* 2.2    sk     10/13/14 Used Pin number in Bank instead of pin number
*                       passed to APIs. CR# 822636
* 3.00  kvn  02/13/15 Modified code for MISRA-C:2012 compliance.
* 3.1    kvn  04/13/15 Add support for Zynq Ultrascale+ MP. CR# 856980.
*       ms   03/17/17 Added readme.txt file in examples folder for doxygen
*                     generation.
*       ms   04/05/17 Added tabspace for return statements in functions of
*                     gpiops examples for proper documentation while
*                     generating doxygen.
* 3.3   ms   04/17/17 Added notes about gpio input and output pin description
*                     for zcu102 and zc702 boards in polled and interrupt
*                     example, configured Interrupt pin to input pin for
*                     proper functioning of interrupt example.
* 3.4   aru  08/17/18 Resolved MISRA-C mandatory violations. CR# 1007751
* 3.5   sne  03/01/19 Fixes violations according to MISRAC-2012
*                     in safety mode and modified the code such as
*                     Use of mixed mode arithmetic,Declared the pointer param
*                     as Pointer to const,Casting operation to a pointer,
*                     Literal value requires a U suffix.
* 3.5   sne  03/14/19 Added Versal support.
* 3.6   mus  04/05/19 Replaced XPLAT_versal macro with XPLAT_VERSAL, to be in
*                     sync with standalone BSP
* 3.6    sne  06/12/19 Fixed IAR compiler warning.
* 3.6   sne  08/14/19 Added interrupt handler support on versal.
* 3.7    sne  12/04/19 Reverted versal examples support.
*
* </pre>
*
******************************************************************************/
#ifndef XGPIOPS_H        /* prevent circular inclusions */
#define XGPIOPS_H        /* by using protection macros */

#ifdef __cplusplus
extern "C" {
#endif

/***************************** Include Files *********************************/

#include "xstatus.h"
#include "xgpiops_hw.h"
#include "xplatform_info.h"

/************************** Constant Definitions *****************************/

/** @name Interrupt types
 *  @{
 * The following constants define the interrupt types that can be set for each
 * GPIO pin.
 */
#define XGPIOPS_IRQ_TYPE_EDGE_RISING    0x00U  /**< Interrupt on Rising edge */
#define XGPIOPS_IRQ_TYPE_EDGE_FALLING    0x01U  /**< Interrupt Falling edge */
#define XGPIOPS_IRQ_TYPE_EDGE_BOTH    0x02U  /**< Interrupt on both edges */
#define XGPIOPS_IRQ_TYPE_LEVEL_HIGH    0x03U  /**< Interrupt on high level */
#define XGPIOPS_IRQ_TYPE_LEVEL_LOW    0x04U  /**< Interrupt on low level */
/*@}*/

#define XGPIOPS_BANK_MAX_PINS        (u32)32 /**< Max pins in a GPIO bank */
#define XGPIOPS_BANK0            0x00U  /**< GPIO Bank 0 */
#define XGPIOPS_BANK1            0x01U  /**< GPIO Bank 1 */
#define XGPIOPS_BANK2            0x02U  /**< GPIO Bank 2 */
#define XGPIOPS_BANK3            0x03U  /**< GPIO Bank 3 */

#ifdef XPAR_PSU_GPIO_0_BASEADDR
#define XGPIOPS_BANK4            0x04U  /**< GPIO Bank 4 */
#define XGPIOPS_BANK5            0x05U  /**< GPIO Bank 5 */
#endif

#define XGPIOPS_MAX_BANKS_ZYNQMP        0x06U  /**< Max banks in a
                                        *    Zynq Ultrascale+ MP GPIO device
                                        */
#define XGPIOPS_MAX_BANKS        0x04U  /**< Max banks in a Zynq GPIO device */

#define XGPIOPS_DEVICE_MAX_PIN_NUM_ZYNQMP    (u32)174 /**< Max pins in the
                          *    Zynq Ultrascale+ MP GPIO device
                          * 0 - 25,  Bank 0
                          * 26 - 51, Bank 1
                          *    52 - 77, Bank 2
                          *    78 - 109, Bank 3
                          *    110 - 141, Bank 4
                          *    142 - 173, Bank 5
                          */
#define XGPIOPS_DEVICE_MAX_PIN_NUM    (u32)118 /**< Max pins in the Zynq GPIO device
                          * 0 - 31,  Bank 0
                          * 32 - 53, Bank 1
                          *    54 - 85, Bank 2
                          *    86 - 117, Bank 3
                          */

/**************************** Type Definitions *******************************/

/****************************************************************************/
/**
 * This handler data type allows the user to define a callback function to
 * handle the interrupts for the GPIO device. The application using this
 * driver is expected to define a handler of this type, to support interrupt
 * driven mode. The handler executes in an interrupt context such that minimal
 * processing should be performed.
 *
 * @param    CallBackRef is a callback reference passed in by the upper layer
 *        when setting the callback functions for a GPIO bank. It is
 *        passed back to the upper layer when the callback is invoked. Its
 *        type is not important to the driver component, so it is a void
 *        pointer.
 * @param    Bank is the bank for which the interrupt status has changed.
 * @param    Status is the Interrupt status of the GPIO bank.
 *
 *****************************************************************************/
typedef void (*XGpioPs_Handler) (void *CallBackRef, u32 Bank, u32 Status);

/**
 * This typedef contains configuration information for a device.
 */
typedef struct {
    u16 DeviceId;        /**< Unique ID of device */
    u32 BaseAddr;        /**< Register base address */
} XGpioPs_Config;

/**
 * The XGpioPs driver instance data. The user is required to allocate a
 * variable of this type for the GPIO device in the system. A pointer
 * to a variable of this type is then passed to the driver API functions.
 */
typedef struct {
    XGpioPs_Config GpioConfig;    /**< Device configuration */
    u32 IsReady;            /**< Device is initialized and ready */
    XGpioPs_Handler Handler;    /**< Status handlers for all banks */
    void *CallBackRef;         /**< Callback ref for bank handlers */
    u32 Platform;            /**< Platform data */
    u32 MaxPinNum;            /**< Max pins in the GPIO device */
    u8 MaxBanks;            /**< Max banks in a GPIO device */
        u32 PmcGpio;                    /**< Flag for accessing PS GPIO for versal*/
} XGpioPs;

/***************** Macros (Inline Functions) Definitions *********************/

/************************** Function Prototypes ******************************/

/* Functions in xgpiops.c */
s32 XGpioPs_CfgInitialize(XGpioPs *InstancePtr, const XGpioPs_Config *ConfigPtr,
               u32 EffectiveAddr);

/* Bank APIs in xgpiops.c */
u32 XGpioPs_Read(const XGpioPs *InstancePtr, u8 Bank);
void XGpioPs_Write(const XGpioPs *InstancePtr, u8 Bank, u32 Data);
void XGpioPs_SetDirection(const XGpioPs *InstancePtr, u8 Bank, u32 Direction);
u32 XGpioPs_GetDirection(const XGpioPs *InstancePtr, u8 Bank);
void XGpioPs_SetOutputEnable(const XGpioPs *InstancePtr, u8 Bank, u32 OpEnable);
u32 XGpioPs_GetOutputEnable(const XGpioPs *InstancePtr, u8 Bank);
#ifdef versal
void XGpioPs_GetBankPin(const XGpioPs *InstancePtr,u8 PinNumber,u8 *BankNumber, u8 *PinNumberInBank);
#else
void XGpioPs_GetBankPin(u8 PinNumber,u8 *BankNumber, u8 *PinNumberInBank);
#endif

/* Pin APIs in xgpiops.c */
u32 XGpioPs_ReadPin(const XGpioPs *InstancePtr, u32 Pin);
void XGpioPs_WritePin(const XGpioPs *InstancePtr, u32 Pin, u32 Data);
void XGpioPs_SetDirectionPin(const XGpioPs *InstancePtr, u32 Pin, u32 Direction);
u32 XGpioPs_GetDirectionPin(const XGpioPs *InstancePtr, u32 Pin);
void XGpioPs_SetOutputEnablePin(const XGpioPs *InstancePtr, u32 Pin, u32 OpEnable);
u32 XGpioPs_GetOutputEnablePin(const XGpioPs *InstancePtr, u32 Pin);

/* Diagnostic functions in xgpiops_selftest.c */
s32 XGpioPs_SelfTest(const XGpioPs *InstancePtr);

/* Functions in xgpiops_intr.c */
/* Bank APIs in xgpiops_intr.c */
void XGpioPs_IntrEnable(const XGpioPs *InstancePtr, u8 Bank, u32 Mask);
void XGpioPs_IntrDisable(const XGpioPs *InstancePtr, u8 Bank, u32 Mask);
u32 XGpioPs_IntrGetEnabled(const XGpioPs *InstancePtr, u8 Bank);
u32 XGpioPs_IntrGetStatus(const XGpioPs *InstancePtr, u8 Bank);
void XGpioPs_IntrClear(const XGpioPs *InstancePtr, u8 Bank, u32 Mask);
void XGpioPs_SetIntrType(const XGpioPs *InstancePtr, u8 Bank, u32 IntrType,
              u32 IntrPolarity, u32 IntrOnAny);
void XGpioPs_GetIntrType(const XGpioPs *InstancePtr, u8 Bank, u32 *IntrType,
              u32 *IntrPolarity, u32 *IntrOnAny);
void XGpioPs_SetCallbackHandler(XGpioPs *InstancePtr, void *CallBackRef,
                 XGpioPs_Handler FuncPointer);
void XGpioPs_IntrHandler(const XGpioPs *InstancePtr);

/* Pin APIs in xgpiops_intr.c */
void XGpioPs_SetIntrTypePin(const XGpioPs *InstancePtr, u32 Pin, u8 IrqType);
u8 XGpioPs_GetIntrTypePin(const XGpioPs *InstancePtr, u32 Pin);

void XGpioPs_IntrEnablePin(const XGpioPs *InstancePtr, u32 Pin);
void XGpioPs_IntrDisablePin(const XGpioPs *InstancePtr, u32 Pin);
u32 XGpioPs_IntrGetEnabledPin(const XGpioPs *InstancePtr, u32 Pin);
u32 XGpioPs_IntrGetStatusPin(const XGpioPs *InstancePtr, u32 Pin);
void XGpioPs_IntrClearPin(const XGpioPs *InstancePtr, u32 Pin);

/* Functions in xgpiops_sinit.c */
XGpioPs_Config *XGpioPs_LookupConfig(u16 DeviceId);
#ifdef __cplusplus
}
#endif

#endif /* end of protection macro */
/** @} */
