/**
  ******************************************************************************
  * @file    openamp_conf.h
  * @author  MCD Application Team
  * @brief   Configuration file for OpenAMP MW
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2019 STMicroelectronics. 
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the 
  * License. You may obtain a copy of the License at:
  *                       opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __OPENAMP_CONF__H__
#define __OPENAMP_CONF__H__

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#if defined (__LOG_TRACE_IO_) || defined(__LOG_UART_IO_)
#include "openamp_log.h"
#endif

 /* ########################## Mailbox Interface Selection ############################## */
 /**
   * @brief This is the list of Mailbox interface  to be used in the OpenAMP MW
   *        Please note that not all interfaces are supported by a STM32 device
   */
#define MAILBOX_IPCC_IF_ENABLED
//#define MAILBOX_HSEM_IF_ENABLED

 /* Includes ------------------------------------------------------------------*/
 /**
   * @brief Include Maibox interface  header file
   */

#ifdef MAILBOX_IPCC_IF_ENABLED
#include "mbox_ipcc.h"
#endif /* MAILBOX_IPCC_IF_ENABLED */

#ifdef MAILBOX_HSEM_IF_ENABLED
#include "mbox_hsem.h"
#endif /* MAILBOX_HSEM_IF_ENABLED */

 /* ########################## Virtual Diver Module Selection ############################## */
 /**
   * @brief This is the list of modules to be used in the OpenAMP Virtual driver module
   *        Please note that virtual driver are not supported on all stm32 families
   */
//#define VIRTUAL_UART_MODULE_ENABLED
//#define VIRTUAL_I2C_MODULE_ENABLED

 /* Includes ------------------------------------------------------------------*/
 /**
   * @brief Include Virtual Driver module's  header file
   */

#ifdef VIRTUAL_UART_MODULE_ENABLED
#include "virt_uart.h"
#endif /* VIRTUAL_UART_MODULE_ENABLED */

#ifdef VIRTUAL_I2C_MODULE_ENABLED
#include "virt_i2c.h"
#endif /* VIRTUAL_I2C_MODULE_ENABLED */

 /* ########################## Linux Master Selection ############################## */
 /**
  * @brief Due to Linux compatibility, it's important to distinguish if the MASTER is Linux or not.
  *        In that case, the LINUX_RPROC_MASTER define is required
  */
#define LINUX_RPROC_MASTER

/* USER CODE BEGIN INCLUDE */

/* USER CODE END INCLUDE */

/** @addtogroup OPENAMP_MW
  * @{
  */

/** @defgroup OPENAMP_CONF OPENAMP_CONF
  * @brief Configuration file for Openamp mw
  * @{
  */

/** @defgroup OPENAMP_CONF_Exported_Variables OPENAMP_CONF_Exported_Variables
  * @brief Public variables.
  * @{
  */

/**
  * @}
  */

/** @defgroup OPENAMP_CONF_Exported_Defines OPENAMP_CONF_Exported_Defines
  * @brief Defines for configuration of the Openamp mw
  * @{
  */

#if defined (__ICCARM__)
/*
 * For IAR, the .icf file should contain the following lines:
 * define symbol __OPENAMP_region_start__ = BASE_ADDRESS; (0x38000400 for example)
 * define symbol __OPENAMP_region_size__   = MEM_SIZE; (0xB000 as example)
 *
 * export symbol __OPENAMP_region_start__;
 * export symbol __OPENAMP_region_size__;
 */
extern const uint32_t  __OPENAMP_region_start__;
extern const uint8_t  __OPENAMP_region_size__;
#define SHM_START_ADDRESS       ((metal_phys_addr_t)&__OPENAMP_region_start__)
#define SHM_SIZE        ((size_t)&__OPENAMP_region_size__)

#elif defined(__CC_ARM)
/*
 * For MDK-ARM, the scatter file .sct should contain the following line:
 * LR_IROM1 ....  {
 *  ...
 *   __OpenAMP_SHMEM__ 0x38000400  EMPTY 0x0000B000 {} ; Shared Memory area used by OpenAMP
 *  }
 *
 */
extern unsigned int Image$$__OpenAMP_SHMEM__$$Base;
extern unsigned int Image$$__OpenAMP_SHMEM__$$ZI$$Length;
#define SHM_START_ADDRESS (unsigned int)&Image$$__OpenAMP_SHMEM__$$Base
#define SHM_SIZE          ((size_t)&Image$$__OpenAMP_SHMEM__$$ZI$$Length)

#else
/*
 * for GCC add the following content to the .ld file:
 * MEMORY
 * {
 * ...
 * OPEN_AMP_SHMEM (xrw) : ORIGIN = 0x38000400, LENGTH = 63K
 * }
 * __OPENAMP_region_start__  = ORIGIN(OPEN_AMP_SHMEM);
 * __OPENAMP_region_end__ = ORIGIN(OPEN_AMP_SHMEM) + LENGTH(OPEN_AMP_SHMEM);
 *
 * using the LENGTH(OPEN_AMP_SHMEM) to set the SHM_SIZE lead to a crash thus we
 * use the start and end address.
 */

extern int __OPENAMP_region_start__[];  /* defined by linker script */
extern int __OPENAMP_region_end__[];    /* defined by linker script */

#define SHM_START_ADDRESS       ((metal_phys_addr_t)__OPENAMP_region_start__)
#define SHM_SIZE                (size_t)((void *)__OPENAMP_region_end__ - (void *) __OPENAMP_region_start__)

#endif

#if defined LINUX_RPROC_MASTER
#define VRING_RX_ADDRESS        -1        /* allocated by Master processor: CA7 */
#define VRING_TX_ADDRESS        -1        /* allocated by Master processor: CA7 */
#define VRING_BUFF_ADDRESS      -1        /* allocated by Master processor: CA7 */
#define VRING_ALIGNMENT         16        /* fixed to match with linux constraint */
#define VRING_NUM_BUFFS         16		  /* number of rpmsg buffer */
#else

#define VRING_RX_ADDRESS     0x10040000             /* allocated by Master processor: CA7 */
#define VRING_TX_ADDRESS     0x10040400             /* allocated by Master processor: CA7 */
#define VRING_BUFF_ADDRESS   0x10040800             /* allocated by Master processor: CA7 */
#define VRING_ALIGNMENT      16         /* fixed to match with 4k page alignement requested by linux  */
#define VRING_NUM_BUFFS      16             /* number of rpmsg buffer */
#endif
/* Fixed parameter */
#define NUM_RESOURCE_ENTRIES 2
#define VRING_COUNT          2
#define VDEV_ID              0xFF
#define VRING0_ID            0              /* VRING0 ID (master to remote) fixed to 0 for linux compatibility*/
#define VRING1_ID            1              /* VRING1 ID (remote to master) fixed to 1 for linux compatibility  */

/**
  * @}
  */

/** @defgroup OPENAMP_CONF_Exported_Macros OPENAMP_CONF_Exported_Macros
  * @brief Aliases.
  * @{
  */

/* DEBUG macros */

#if defined (__LOG_TRACE_IO_) || defined(__LOG_UART_IO_)
  #define OPENAMP_log_dbg               log_dbg
  #define OPENAMP_log_info              log_info
  #define OPENAMP_log_warn              log_warn
  #define OPENAMP_log_err               log_err
#else
  #define OPENAMP_log_dbg(...)
  #define OPENAMP_log_info(...)
  #define OPENAMP_log_warn(...)
  #define OPENAMP_log_err(...)
#endif

/**
  * @}
  */

/** @defgroup OPENAMP_CONF_Exported_Types OPENAMP_CONF_Exported_Types
  * @brief Types.
  * @{
  */

/**
  * @}
  */

/** @defgroup OPENAMP_CONF_Exported_FunctionsPrototype OPENAMP_CONF_Exported_FunctionsPrototype
  * @brief Declaration of public functions for OpenAMP mw.
  * @{
  */

/* Exported functions -------------------------------------------------------*/

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

#ifdef __cplusplus
}
#endif

#endif /* __OPENAMP_CONF__H__ */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
