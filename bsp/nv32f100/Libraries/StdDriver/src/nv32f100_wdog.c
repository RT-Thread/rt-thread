/****************************************************************************!     
 *     技术讨论：QQ群  123763203
 *     官网    ：www.navota.com
 *
 * @file       wdg.c
 * @brief      wdg定时器函数库
 * @author     Navota
 * @date       2017-1-1
 *******************************************************************************/
#include "nv32f100.h"

/******************************************************************************
*******************************************************************************/

/*****************************************************************************//*!
*
* @brief 禁用看门狗定时器
*        
* @param  none 
*
* @return none
*
*****************************************************************************/

void WDOG_Disable(void)
{
    uint8_t u8Cs1 =  WDOG->CS1;  
    uint8_t u8Cs2 =  WDOG->CS2;  
    uint16_t u16TOVAL =  WDOG->TOVAL;  
    uint16_t u16WIN =  WDOG->WIN;  

    u8Cs1       &= ~WDOG_CS1_EN_MASK;

    /* 首先要解锁unlock看门狗，才可以往寄存器写数据 */
    WDOG_Unlock(); 
    WDOG->CS2    =  u8Cs2;
    WDOG->TOVAL  =  u16TOVAL;
    WDOG->WIN    =  u16WIN;
    WDOG->CS1    =  u8Cs1;
}


/*****************************************************************************//*!
*
* @brief 禁用看门狗更新使能.
*        
* Disable watchdog but the watchdog can be enabled and updated later.
*
* @param  none 
*
* @return none
*
*****************************************************************************/

void WDOG_DisableWDOGEnableUpdate(void)
{
    uint8_t u8Cs1 =  WDOG->CS1;  
    uint8_t u8Cs2 =  WDOG->CS2;  
    uint16_t u16TOVAL =  WDOG->TOVAL;  
    uint16_t u16WIN =  WDOG->WIN;  

    u8Cs1       &= ~WDOG_CS1_EN_MASK;
    u8Cs1       |= WDOG_CS1_UPDATE_MASK;

	
    //WDOG_Unlock(); 
    WDOG->CS2    =  u8Cs2;
    WDOG->TOVAL  =  u16TOVAL;
    WDOG->WIN    =  u16WIN;
    WDOG->CS1    =  u8Cs1;
}

/*****************************************************************************//*!
*
* @brief 使能看门狗定时器.
*        
* @param  none
*
* @return none
*
*****************************************************************************/

void WDOG_Enable(void)
{
    uint8_t u8Cs1 =  WDOG->CS1;
    
    u8Cs1       |= WDOG_CS1_EN_MASK;

    /* 首先要解锁unlock看门狗，才可以往寄存器写数据 */
    WDOG_Unlock();
    WDOG->CS1    = u8Cs1;
}


/*****************************************************************************//*!
*
* @brief 初始化看门狗.
*        
* @param[in]   pConfig     配置看门狗的结构体.
*
* @return none
*
* @warning make sure that WDOG is not initialized after reset or WDOG update is enabled 
* after reset by calling WDOG_EnableUpdate / WDOG_DisableWDOGEnableUpdate.
*
* @see WDOG_EnableUpdate, WDOG_DisableWDOGEnableUpdate
*
*****************************************************************************/

void WDOG_Init(WDOG_ConfigPtr pConfig)
{
    uint8_t     u8Cs1;
    uint8_t     u8Cs2;
    uint16_t    u16Toval;
    uint16_t    u16Win;
    
    u8Cs1       = 0x80;                                   /* CS1寄存器的默认值 */
    u8Cs2       = 0;
    u16Toval    = pConfig->u16ETMeOut;
    u16Win      = pConfig->u16WinETMe;
        
    if(pConfig->sBits.bDisable)
    {
        u8Cs1 &= ~WDOG_CS1_EN_MASK;
    }
    if(pConfig->sBits.bIntEnable)
    {
        u8Cs1 |= WDOG_CS1_INT_MASK;
    }
    if(pConfig->sBits.bStopEnable)
    {
        u8Cs1 |= WDOG_CS1_STOP_MASK;
    }
    if(pConfig->sBits.bDbgEnable)
    {
        u8Cs1 |= WDOG_CS1_DBG_MASK;
    }
    if(pConfig->sBits.bWaitEnable)
    {
        u8Cs1 |= WDOG_CS1_WAIT_MASK;
    }
    if(pConfig->sBits.bUpdateEnable)
    {
        u8Cs1 |= WDOG_CS1_UPDATE_MASK;
    }
    if(pConfig->sBits.bWinEnable)
    {
        u8Cs2 |= WDOG_CS2_WIN_MASK;
    }
    if(pConfig->sBits.bPrescaler)
    {
        u8Cs2 |= WDOG_CS2_PRES_MASK;
    }
    u8Cs2   |= (pConfig->sBits.bClkSrc & 0x03);
    
    /* 首先要解锁unlock看门狗，才可以往寄存器写数据 */
    WDOG_Unlock();             
    WDOG->CS2   = u8Cs2;

    WDOG->TOVAL8B.TOVALL  = u16Toval;
    WDOG->TOVAL8B.TOVALH  = u16Toval >> 8;
    
    WDOG->WIN8B.WINL  = u16Win;
    WDOG->WIN8B.WINH  = u16Win >> 8;
    
    WDOG->CS1   = u8Cs1;                            
}


/*****************************************************************************//*!
*
* @brief 复位看门狗.
*        
* @param   none 
*
* @return none
*
*****************************************************************************/

void WDOG_DeInit(void)
{
    WDOG_Unlock();
    
    WDOG->CS2    =  WDOG_CS2_DEFAULT_VALUE;
    WDOG->TOVAL  =  WDOG_TOVAL_DEFAULT_VALUE;
    WDOG->WIN    =  WDOG_WIN_DEFAULT_VALUE;    
    WDOG->CS1    =  WDOG_CS1_DEFAULT_VALUE;
}

/*****************************************************************************//*!
*
* @brief 喂狗-刷新看门狗.
*        
* @param   none
*
* @return none
*
*****************************************************************************/

void WDOG_Feed(void)
{
    DisableInterrupts;
    WDOG->CNT = 0x02A6;
    WDOG->CNT = 0x80B4;
    EnableInterrupts;
}



/*****************************************************************************//*!
*
* @brief 使能更新看门狗. 
*        
* @param  none
*
* @return none
*
*****************************************************************************/

void WDOG_EnableUpdate(void)
{
    uint8_t u8Cs1 =  WDOG->CS1;  
    uint8_t u8Cs2 =  WDOG->CS2;  
    uint16_t u16TOVAL =  WDOG->TOVAL;  
    uint16_t u16WIN =  WDOG->WIN;  

    u8Cs1 |= WDOG_CS1_UPDATE_MASK;

    /* 首先要解锁unlock看门狗，才可以往寄存器写数据 */
    WDOG_Unlock(); 
    WDOG->CS2    =  u8Cs2;
    WDOG->TOVAL  =  u16TOVAL;
    WDOG->WIN    =  u16WIN;
    WDOG->CS1    =  u8Cs1;  
}


/*****************************************************************************//*!
*
* @brief 禁用更新看门狗. 
*        
* @param  none 
*
* @return none
*
*****************************************************************************/

void WDOG_DisableUpdate(void)
{
    uint8_t u8Cs1 =  WDOG->CS1;  
    uint8_t u8Cs2 =  WDOG->CS2;  
    uint16_t u16TOVAL =  WDOG->TOVAL;  
    uint16_t u16WIN =  WDOG->WIN;  

    u8Cs1 &= ~WDOG_CS1_UPDATE_MASK;

    /* 首先要解锁unlock看门狗，才可以往寄存器写数据 */
    WDOG_Unlock(); 
    WDOG->CS2    =  u8Cs2;
    WDOG->TOVAL  =  u16TOVAL;
    WDOG->WIN    =  u16WIN;
    WDOG->CS1    =  u8Cs1;  
    
}


/********************************************************************/

/*! @}                                                  			*/




