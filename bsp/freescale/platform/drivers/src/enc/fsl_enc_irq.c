/*******************************************************************************
*
* Copyright [2014-]2014 Freescale Semiconductor, Inc.

*
* This software is owned or controlled by Freescale Semiconductor.
* Use of this software is governed by the Freescale License
* distributed with this Material.
* See the LICENSE file distributed for more details.
* 
*
*******************************************************************************/

#include "fsl_device_registers.h"
#include "fsl_enc_driver.h"
#if FSL_FEATURE_SOC_ENC_COUNT

/*******************************************************************************
 * Variables
 ******************************************************************************/

/*******************************************************************************
 * Prototypes
 ******************************************************************************/
extern void ENC_ISR_Index(void);          /* Callback function of INDEX interrupt. */
extern void ENC_ISR_Home(void);           /* Callback function of HOME interrupt. */
extern void ENC_ISR_Rollover(void);       /* Callback function of roll-over interrupt. */
extern void ENC_ISR_Rollunder(void);      /* Callback function of roll-under interrupt. */
extern void ENC_ISR_Compare(void);        /* Callback function of compare interrupt. */
extern void ENC_ISR_Watchdog(void);       /* Callback function of WDT interrupt. */
extern void ENC_ISR_Simult(void);         /* Callback function of Simult-change interrupt. */

/*******************************************************************************
 * Code
 ******************************************************************************/

#if ((defined(KV40F15_SERIES)) || (defined(KV43F15_SERIES)) || (defined(KV44F15_SERIES)) || (defined(KV45F15_SERIES)) || (defined(KV46F15_SERIES)))


/*!
 * @brief Implementation of ENC Compare handler named in startup code.
 *
 * Passes instance to generic ENC IRQ handler.
 */
void ENC_COMPARE_IRQHandler(void)
{
    /* Get Compare Interrupt request. */
    if (ENC_DRV_GetStatusFlag(0U, kEncCmpFlag))
    {
        /* Call callback function. */
        ENC_ISR_Compare();

        /* Clear Compare Interrupt pending bit. */
        ENC_DRV_ClearStatusFlag(0U, kEncCmpFlag);
    }
}

/*!
 * @brief Implementation of HOME Signal handler named in startup code.
 *
 * Passes instance to generic ENC IRQ handler.
 */
void ENC_HOME_IRQHandler(void)
{
    /* Get Home signal Interrupt request. */
    if (ENC_DRV_GetStatusFlag(0U, kEncHomeSignalFlag))
    {
        /* Call callback function. */
        ENC_ISR_Home();
        
        /* Clear HOME Signal Interrupt Flag. */
        ENC_DRV_ClearStatusFlag(0U, kEncHomeSignalFlag);
    }
}

/*!
 * @brief Implementation of INDEX Pulse handler and Roll-over, Roll-under
 * named in startup code.
 *
 * Passes instance to generic ENC IRQ handler.
 */
void ENC_INDEX_IRQHandler(void)
{ 
    /* Get Index pulse Interrupt request. */
    if ( ENC_DRV_GetStatusFlag(0U, kEncIndexPulseFlag) & ENC_DRV_GetIntMode(0U, kEncIntIndexPulse) )
    {
        /* Call callback function. */
        ENC_ISR_Index();
        
        /* Clear interrupt pending bit. */
        ENC_DRV_ClearStatusFlag(0U, kEncIndexPulseFlag);
    }

    /* Get Roll-over Interrupt request. */
    if ( ENC_DRV_GetStatusFlag(0U, kEncRolloverFlag) & ENC_DRV_GetIntMode(0U, kEncIntRollover))
    {
        /* Call callback function. */
        ENC_ISR_Rollover();
        
        /* Clear interrupt pending bit. */
        ENC_DRV_ClearStatusFlag(0U, kEncRolloverFlag);
    }

    /* Get Roll-under Interrupt request. */
    if ( ENC_DRV_GetStatusFlag(0U, kEncRollunderFlag) & ENC_DRV_GetIntMode(0U, kEncIntRollunder))
    {
        /* Call callback function. */
        ENC_ISR_Rollunder();
        
        /* Clear interrupt pending bit. */
        ENC_DRV_ClearStatusFlag(0U, kEncRollunderFlag);
    }
}

/*!
 * @brief Implementation of Watchdog timeout handler named in startup code.
 *
 * Passes instance to generic ENC IRQ handler.
 */
void ENC_WDOG_SAB_IRQHandler(void)
{
    /* Get Watchdog Timeout Interrupt request. */
    if (ENC_DRV_GetStatusFlag(0U, kEncWatchdogTimeoutFlag))
    {
        /* Call callback function. */
        ENC_ISR_Watchdog();
        
        /* Clear Watchdog Timeout Interrupt Flag. */
        ENC_DRV_ClearStatusFlag(0U, kEncWatchdogTimeoutFlag);
    }

    /* Get Simultaneous change Interrupt request. */
    if (ENC_DRV_GetStatusFlag(0U, kEncSimultaneousFlag))
    {
        /* Call callback function. */
        ENC_ISR_Simult();
        
        /* Clear Simultaneous Interrupt Flag. */
        ENC_DRV_ClearStatusFlag(0U, kEncSimultaneousFlag);
    }
}

#else
    #error "No valid CPU defined!"
#endif
#endif
/*******************************************************************************
 * EOF
 ******************************************************************************/
