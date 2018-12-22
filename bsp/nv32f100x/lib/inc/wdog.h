
/******************************************************************************
* @brief provide commond watch dog utilities. 
*
*******************************************************************************
*
* provide APIs for accessing watch dog
******************************************************************************/

#ifndef __WDOG_H__
#define __WDOG_H__

#ifdef __cplusplus
extern "C" {
#endif


/******************************************************************************
* Includes
******************************************************************************/
#include "sim.h"

/******************************************************************************
* Constants
******************************************************************************/

/******************************************************************************
* Macros
******************************************************************************/
/* wdog_unlock sequence must be performed within 16 bus clock cycles without
 * any interrupt 
 */

   
/* WDOG clock sources option */
/******************************************************************************
* define watchdog clock source selection
*
*//*! @addtogroup wdog_clock_sources
* @{
*******************************************************************************/

#define WDOG_CLK_BUS                    0   /*!< clock source is bus clock */
#define WDOG_CLK_INTERNAL_32KHZ         2   /*!< clock source is internal oscillator 32 kHz (ICSIRCLK) */
#define WDOG_CLK_INTERNAL_1KHZ	        1   /*!< clock source is internal LPO 1 KHz */
#define WDOG_CLK_EXTERNAL               3   /*!< clock source is external clock */
/*! @} End of wdog_clock_sources                                                    					*/

/* WDOG clock source selection */
#define WDOG_CLK  (WDOG_CLK_INTERNAL_1KHZ)
    
/* WDOG default values */
#define WDOG_CS1_DEFAULT_VALUE      0x80
#define WDOG_CS2_DEFAULT_VALUE      0x01
#define WDOG_TOVAL_DEFAULT_VALUE    0x0400
#define WDOG_WIN_DEFAULT_VALUE      0x0000
     
/* WDOG utilities */  

/******************************************************************************
* define watchdog API list
*
*//*! @addtogroup wdog_api_list
* @{
*******************************************************************************/
/*! 
 * @brief watchdog unlock routine.
 */
#define WDOG_Unlock()        WDOG->CNT = 0x20C5; WDOG->CNT = 0x28D9        
//#define WDOG_Unlock()       DisableInterrupts; WDOG->CNT = 0x20C5; WDOG->CNT = 0x28D9; EnableInterrupts        
/*! @} End of wdog_api_list                                                    					*/

/******************************************************************************
* Types
******************************************************************************/

/******************************************************************************
* define watchdog configuration structure
*
*//*! @addtogroup wdog_config_type
* @{
*******************************************************************************/

/*!
 * @brief watchdog configuration structure.
 *
 */
typedef struct {	
    struct {
	uint16_t    bIntEnable      : 1;    /*!< watchdog interrupt enable */
	uint16_t    bDisable        : 1;    /*!< disable watchdog */
	uint16_t    bWaitEnable     : 1;    /*!< enable watchdog in wait mode */
	uint16_t    bStopEnable     : 1;    /*!< enable watchdog in stop mode */
	uint16_t    bDbgEnable      : 1;    /*!< enable watchdog in debug mode */
	uint16_t    bWinEnable      : 1;    /*!< enable watchdog window mode */
	uint16_t    bUpdateEnable   : 1;    /*!< enable update of watchdog control */
	uint16_t    bClkSrc         : 2;    /*!< watchdog clock source selection */  
	uint16_t    bPrescaler      : 1;    /*!< prescaler */  
    }sBits;                             /*!< bitfield structure  */
    uint16_t    u16ETMeOut;             /*!< watchdog ETMeout value */
    uint16_t    u16WinETMe;             /*!< watchdog window value */
} WDOG_ConfigType, *WDOG_ConfigPtr;  /*!< watchdog configuration structure type */
/*! @} End of wdog_config_type                                                    					*/

/******************************************************************************
* Global variables
******************************************************************************/

/******************************************************************************
* Global functions
******************************************************************************/

/******************************************************************************
* define watchdog API list
*
*//*! @addtogroup wdog_api_list
* @{
*******************************************************************************/


/*****************************************************************************//*!
*
* @brief set ETMe out value for WDOG.
*        
* @param[in]   u16ETMeOut  ETMeout value to TOVAL register.
*
* @return none
*
* @ Pass/ Fail criteria: none
*
*****************************************************************************/

__STATIC_INLINE void WDOG_SetETMeOut(uint16_t u16ETMeOut)
{
    WDOG->CNT = 0x20C5; 
    WDOG->CNT = 0x28D9;
    WDOG->TOVAL8B.TOVALL  = u16ETMeOut;
    WDOG->TOVAL8B.TOVALH  = u16ETMeOut >> 8;
}


/*****************************************************************************//*!
*
* @brief set window value for WDOG.
*        
* @param[in]   u16WinETMe  window value to WIN register.
*
* @return none
*
* @ Pass/ Fail criteria: none
*
*****************************************************************************/

__STATIC_INLINE void WDOG_SetWindow(uint16_t u16WinETMe)
{
    WDOG->CNT = 0x20C5; 
    WDOG->CNT = 0x28D9;
    WDOG->WIN8B.WINL  = u16WinETMe;
    WDOG->WIN8B.WINH  = u16WinETMe >> 8;
}

/*****************************************************************************//*!
*
* @brief check if watchdog reset occurs.
*        
* @param    none.
*
* @return   TRUE if watchdog reset occurs, FALSE otherwise.
*
* @ Pass/ Fail criteria: none
*****************************************************************************/

__STATIC_INLINE uint8_t WDOG_IsReset(void)
{
    if(SIM_GetStatus(SIM_SRSID_WDOG_MASK))
    {
        return (TRUE);
    }
    return (FALSE);
}

/*! @} End of wdog_api_list                                                    					*/


void WDOG_Init(WDOG_ConfigPtr pConfig);
void WDOG_DeInit(void);
void WDOG_Disable(void);
void WDOG_DisableWDOGEnableUpdate(void);
void WDOG_Enable(void);
void WDOG_Feed(void);
void WDOG_SetETMeOut(uint16_t u16ETMeOut);
void WDOG_SetWindow(uint16_t u16WinETMe);
void WDOG_EnableUpdate(void);
void WDOG_DisableUpdate(void);
uint8_t WDOG_IsReset(void);

#ifdef __cplusplus
}
#endif

/********************************************************************/
#endif /* __WDOG_H__ */

