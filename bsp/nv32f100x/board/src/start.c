/******************************************************************************
* @brief provide high-level startup routines for NV32Fxx.
*
*******************************************************************************/

#include "start.h"
#include "common.h"
#include "wdog.h"
#include "sysinit.h"

/********************************************************************/
/********************************************************************/
/*!
 * \brief   flash SystemInit
 * \return  None
 *
 * this is a system initialization function which dediu16Cated in Keil
 * others complier don't use it.
 * it is similar to start function
 */
void SystemInit( void )
{
#if !defined(ENABLE_WDOG)
    /* Disable the watchdog ETMer */
    WDOG_Disable();
#else
    /* Disable the watchdog ETMer but enable update */
    WDOG_DisableWDOGEnableUpdate();
#endif

    sysinit();

}



