/**
  ******************************************************************************
  * @file    tae32f53xx_ll.c
  * @author  MCD Application Team
  * @brief   LL module driver.
  *          This is the common part of the LL initialization
  *
  @verbatim
    ==============================================================================
                     ##### How to use this driver #####
    ==============================================================================
      [..]
      The common LL driver contains a set of generic and common APIs that can be
      used by the PPP peripheral drivers and the user to start using the LL.
      [..]
      The LL contains two APIs' categories:
           (+) Common LL APIs
           (+) Services LL APIs
  @endverbatim
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 Tai-Action.
  * All rights reserved.</center></h2>
  *
  * This software is licensed by Tai-Action under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "tae32f53xx_ll.h"


#define DBG_TAG             "TAE32F53xx LL"
#define DBG_LVL             DBG_ERROR
#include "dbg/tae32f53xx_dbg.h"


/** @defgroup TAE32F53xx_LL_Driver TAE32F53xx LL Driver
  * @brief    TAE32F53xx LL Driver
  * @{
  */

/** @defgroup TAE32F53xx_LL TAE32F53xx LL
  * @brief    TAE32F53xx LL
  * @{
  */

#ifdef LL_MODULE_ENABLED

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/** @defgroup TAE32F53xx_LL_Private_Macros TAE32F53xx LL Private Macros
  * @brief    TAE32F53xx LL Private Macros
  * @{
  */

/**
  * @brief  Judge is Tick freq or not
  * @param  FREQ Freq to be judged
  * @retval 0 isn't Tick freq
  * @retval 1 is Tick freq
  */
#define IS_TICKFREQ(FREQ)   (((FREQ) == LL_TICK_FREQ_10HZ)  || \
                             ((FREQ) == LL_TICK_FREQ_100HZ) || \
                             ((FREQ) == LL_TICK_FREQ_1KHZ))

/**
  * @}
  */

/* Private variables ---------------------------------------------------------*/
/** @defgroup TAE32F53xx_LL_Private_Variables TAE32F53xx LL Private Variables
  * @brief    TAE32F53xx LL Private Variables
  * @{
  */

/**
  * @brief SysTick counter
  */
__IO uint32_t uwTick;

/**
  * @brief SysTick interrupt priority
  */
uint32_t uwTickPrio = (1UL << __NVIC_PRIO_BITS) - 1;

/**
  * @brief SysTick interrupt frequency
  */
LL_TickFreqETypeDef uwTickFreq = LL_TICK_FREQ_DEFAULT;

/**
  * @}
  */

/* Private function prototypes -----------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
/** @defgroup TAE32F53xx_LL_Exported_Functions TAE32F53xx LL Exported Functions
  * @brief    TAE32F53xx LL Exported Functions
  * @{
  */

/** @defgroup TAE32F53xx_LL_Exported_Functions_Group1 TAE32F53xx Initialization and de-initialization Functions
 *  @brief    Initialization and de-initialization functions
 *
@verbatim
 ===============================================================================
              ##### Initialization and de-initialization functions #####
 ===============================================================================
   [..]  This section provides functions allowing to:
      (+) Initializes the Flash interface, the NVIC allocation and initial clock
          configuration. It initializes the systick also when timeout is needed
          and the backup domain when enabled.
      (+) de-Initializes common part of the LL.
      (+) Configure The time base source to have 1ms time base with a dedicated
          Tick interrupt priority.
        (++) SysTick timer is used by default as source of time base, but user
             can eventually implement his proper time base source (a general purpose
             timer for example or other time source), keeping in mind that Time base
             duration should be kept 1ms since PPP_TIMEOUT_VALUEs are defined and
             handled in milliseconds basis.
        (++) Time base configuration function (LL_InitTick ()) is called automatically
             at the beginning of the program after reset by LL_Init()
        (++) Source of time base is configured to generate interrupts at regular
             time intervals. Care must be taken if LL_Delay() is called from a
             peripheral ISR process, the Tick interrupt line must have higher priority
            (numerically lower) than the peripheral interrupt. Otherwise the caller
            ISR process will be blocked.
        (++) functions affecting time base configurations are declared as __WEAK
             to make override possible in case of other implementations in user file.
@endverbatim
  * @{
  */

/**
  * @brief  This function is used to initialize the LL Library; it must be the first
  *         instruction to be executed in the main program (before to call any other
  *         LL function), it performs the following:
  *           Configure the Flash prefetch.
  *           Configures the SysTick to generate an interrupt each 1 millisecond,
  *           which is clocked by the LSI (at this stage, the clock is not yet
  *           configured and thus the system is running from the internal LSI at 32 KHz).
  *           Set NVIC Group Priority to 4.
  *           Calls the LL_MspInit() callback function defined in user file
  *           "tae32f53xx_ll_msp.c" to do the global low level hardware initialization
  *
  * @note   SysTick is used as time base for the LL_Delay() function, the application
  *         need to ensure that the SysTick time base is always set to 1 millisecond
  *         to have correct LL operation.
  * @param  None
  * @retval LL status
  */
LL_StatusETypeDef LL_Init(void)
{
#ifdef LL_FLASH_MODULE_ENABLED
    /* Configure Flash prefetch */
#if PREFETCH_ENABLE
    /* Prefetch enable */
    __LL_FLASH_I_BUS_PREFETCH_ENABLE();
    __LL_FLASH_D_BUS_PREFETCH_ENABLE();
#else
    /* Prefetch disable */
    __LL_FLASH_I_BUS_PREFETCH_DISABLE();
    __LL_FLASH_D_BUS_PREFETCH_DISABLE();
#endif /* PREFETCH_ENABLE */
#endif   /* LL_FLASH_MODULE_ENABLED */

    /* Set Interrupt Group Priority */
    LL_NVIC_SetPriorityGrouping(NVIC_PRIORITYGROUP_3);

    /* Use systick as time base source and configure 1ms tick (default clock after Reset is LSI) */
    LL_InitTick(TICK_INT_PRIORITY);

    /* Init the low level hardware */
    LL_MspInit();

    /* Return function status */
    return LL_OK;
}

/**
  * @brief This function de-Initializes common part of the LL and stops the systick of time base.
  * @note This function is optional.
  * @param  None
  * @retval LL status
  */
LL_StatusETypeDef LL_DeInit(void)
{
    /* Reset of all peripherals */
    LL_SYSCTRL_AllPeriphRstAssert();

    /* De-Init the low level hardware */
    LL_MspDeInit();

    /* Return function status */
    return LL_OK;
}

/**
  * @brief  Initialize the MSP.
  * @param  None
  * @retval None
  */
__WEAK void LL_MspInit(void)
{
    /* NOTE : This function should not be modified, when the callback is needed,
              the LL_MspInit could be implemented in the user file
     */
}

/**
  * @brief  DeInitializes the MSP.
  * @param  None
  * @retval None
  */
__WEAK void LL_MspDeInit(void)
{
    /* NOTE : This function should not be modified, when the callback is needed,
              the LL_MspDeInit could be implemented in the user file
     */
}


/**
  * @brief This function configures the source of the time base.
  *        The time source is configured to have 1ms time base with a dedicated
  *        Tick interrupt priority.
  * @note This function is called automatically at the beginning of program after
  *       reset by LL_Init().
  * @note In the default implementation, SysTick timer is the source of time base.
  *       It is used to generate interrupts at regular time intervals.
  *       Care must be taken if LL_Delay() is called from a peripheral ISR process,
  *       The SysTick interrupt must have higher priority (numerically lower)
  *       than the peripheral interrupt. Otherwise the caller ISR process will be blocked.
  *       The function is declared as __WEAK to be overwritten in case of other
  *       implementation  in user file.
  * @param TickPriority Tick interrupt priority.
  * @retval LL status
  */
__WEAK LL_StatusETypeDef LL_InitTick(uint32_t TickPriority)
{
    /* Configure the SysTick to have interrupt in 1ms time basis*/
    if (LL_SYSTICK_Config(LL_SYSCTRL_SysclkGet() / (1000U / uwTickFreq)) > 0U) {
        return LL_ERROR;
    }

    /* Configure the SysTick IRQ priority */
    if (TickPriority < (1UL << __NVIC_PRIO_BITS)) {
        LL_NVIC_SetPriority(SysTick_IRQn, TickPriority, 0U);
        uwTickPrio = TickPriority;
    } else {
        return LL_ERROR;
    }

    /* Return function status */
    return LL_OK;
}


/**
  * @}
  */

/** @defgroup TAE32F53xx_LL_Exported_Functions_Group2 TAE32F53xx LL Control functions
  * @brief    TAE32F53xx LL Control functions
  *
@verbatim
 ===============================================================================
                      ##### LL Control functions #####
 ===============================================================================
    [..]  This section provides functions allowing to:
      (+) Provide a tick value in millisecond
      (+) Provide a blocking delay in millisecond
      (+) Suspend the time base source interrupt
      (+) Resume the time base source interrupt
      (+) Get the LL API driver version
      (+) Get the unique device identifier
@endverbatim
  * @{
  */

/**
  * @brief This function is called to increment a global variable "uwTick"
  *        used as application time base.
  * @note In the default implementation, this variable is incremented each 1ms
  *       in SysTick ISR.
  * @note This function is declared as __WEAK to be overwritten in case of other
  *      implementations in user file.
  * @param  None
  * @retval None
  */
__WEAK void LL_IncTick(void)
{
    uwTick += uwTickFreq;
}

/**
  * @brief Provides a tick value in millisecond
  * @note  This function is declared as __WEAK to be overwritten in case of other
  *       implementations in user file.
  * @param  None
  * @retval tick value
  */
__WEAK uint32_t LL_GetTick(void)
{
    return uwTick;
}

/**
  * @brief This function returns a tick priority
  * @param  None
  * @retval tick priority
  */
uint32_t LL_GetTickPrio(void)
{
    return uwTickPrio;
}

/**
  * @brief  Set new tick Freq
  * @param  Freq New tick freq
  * @retval LL status
  */
LL_StatusETypeDef LL_SetTickFreq(LL_TickFreqETypeDef Freq)
{
    LL_StatusETypeDef status = LL_OK;
    assert_param(IS_TICKFREQ(Freq));

    if (uwTickFreq != Freq) {
        /* Apply the new tick Freq  */
        status = LL_InitTick(uwTickPrio);

        if (status == LL_OK) {
            uwTickFreq = Freq;
        }
    }

    return status;
}

/**
  * @brief  Get tick frequency
  * @param  None
  * @retval tick period in Hz
  */
LL_TickFreqETypeDef LL_GetTickFreq(void)
{
    return uwTickFreq;
}

/**
  * @brief This function provides minimum delay (in milliseconds) based
  *        on variable incremented.
  * @note In the default implementation , SysTick timer is the source of time base.
  *       It is used to generate interrupts at regular time intervals where uwTick
  *       is incremented.
  * @note This function is declared as __WEAK to be overwritten in case of other
  *       implementations in user file.
  * @param Delay specifies the delay time length, in milliseconds.
  * @retval None
  */
__WEAK void LL_Delay(uint32_t Delay)
{
    uint32_t tickstart = LL_GetTick();
    uint32_t wait = Delay;

    /* Add a freq to guarantee minimum wait */
    if (wait < LL_MAX_DELAY) {
        wait += (uint32_t)(uwTickFreq);
    }

    while ((LL_GetTick() - tickstart) < wait) {
    }
}

/**
  * @brief Suspend Tick increment.
  * @note In the default implementation , SysTick timer is the source of time base. It is
  *       used to generate interrupts at regular time intervals. Once LL_SuspendTick()
  *       is called, the SysTick interrupt will be disabled and so Tick increment
  *       is suspended.
  * @note This function is declared as __WEAK to be overwritten in case of other
  *       implementations in user file.
  * @param  None
  * @retval None
  */
__WEAK void LL_SuspendTick(void)
{
    /* Disable SysTick Interrupt */
    CLEAR_BIT(SysTick->CTRL, SysTick_CTRL_TICKINT_Msk);
}

/**
  * @brief Resume Tick increment.
  * @note In the default implementation , SysTick timer is the source of time base. It is
  *       used to generate interrupts at regular time intervals. Once LL_ResumeTick()
  *       is called, the SysTick interrupt will be enabled and so Tick increment
  *       is resumed.
  * @note This function is declared as __WEAK to be overwritten in case of other
  *       implementations in user file.
  * @param  None
  * @retval None
  */
__WEAK void LL_ResumeTick(void)
{
    /* Enable SysTick Interrupt */
    SET_BIT(SysTick->CTRL, SysTick_CTRL_TICKINT_Msk);
}

/**
  * @brief  Get the LL revision
  * @param  None
  * @retval version 0xXYZR (8bits for each decimal, R for RC)
  */
uint32_t LL_GetHalVersion(void)
{
    return __TAE32F53xx_LL_VERSION;
}

/**
  * @brief  Returns words of the device unique identifier (UID based on 128 bits)
  * @param  UID[] device unique identifier store buffer
  * @return None
  */
void LL_GetUID(uint32_t *UID[4])
{
    //:TODO: return the device UID
}

/**
  * @}
  */


/** @defgroup TAE32F53xx_LL_Exported_Functions_Group3 TAE32F53xx LL Misc Functions
  * @brief    TAE32F53xx LL Misc Functions
  * @{
  */

/**
  * @brief  LL Show Platform Information
  * @param  None
  * @return None
  */
void LL_ShowInfo(void)
{
    DBG_LogRaw("\n======================== Platform Information =======================\n");

    DBG_LogRaw("Tai-Action TAE32F53xx SDK "SDK_STAGE_STR" V%d.%d.%d "__DATE__" "__TIME__"\n\n", \
               __TAE32F53xx_LL_VERSION_MAIN, __TAE32F53xx_LL_VERSION_SUB1, __TAE32F53xx_LL_VERSION_SUB2);

    DBG_LogRaw("CPU  clock %9u Hz\n", LL_SYSCTRL_SysclkGet());
    DBG_LogRaw("AHB  clock %9u Hz\n", LL_SYSCTRL_AHBClkGet());
    DBG_LogRaw("APB0 clock %9u Hz\n", LL_SYSCTRL_APB0ClkGet());
    DBG_LogRaw("APB1 clock %9u Hz\n", LL_SYSCTRL_APB1ClkGet());

    DBG_LogRaw("HSE  clock %9u Hz\n", HSE_VALUE);
    DBG_LogRaw("HSI  clock %9u Hz\n", HSI_VALUE);
    DBG_LogRaw("LSI  clock %9u Hz\n", LSI_VALUE);

    DBG_LogRaw("=====================================================================\n\n");
}

/**
  * @brief  Delay 1ms
  * @param  ms The time to delay in 1ms Unit
  * @return None
  */
void delay_ms(uint32_t ms)
{
    LL_Delay(ms);
}

/**
  * @brief  printf array
  * @param  ptr printf array pointer
  * @param  len array len
  * @retval None
  */
void printf_array(void *ptr, uint32_t len)
{
    uint32_t cnt = 0;
    uint8_t *p_ptr = (uint8_t *)ptr;

    while (len--) {
        DBG_LogRaw("%02x ", *p_ptr);
        cnt++;
        p_ptr++;

        if (!(cnt & 0x0f)) {
            DBG_LogRaw("\r\n");
        }
    }

    if ((cnt & 0x0f) != 0x0f) {
        DBG_LogRaw("\r\n");
    }
}

/**
  * @}
  */

/**
  * @}
  */

/* Private functions ---------------------------------------------------------*/


#endif /* LL_MODULE_ENABLED */


/**
  * @}
  */

/**
  * @}
  */

/************************* (C) COPYRIGHT Tai-Action *****END OF FILE***********/

