/**************************************************************************!     
 *     技术讨论：QQ群  123763203
 *     官网    ：www.navota.com
 *
 * @file       spi.c
 * @brief      串行外设接口模块(SPI)函数库
 * @author     Navota
 * @date       2017-1-1
 ****************************************************************************/
#include "nv32f100.h"

/****************************************************************************!
 * @ 存放SPI回调函数接口
 ****************************************************************************/

SPI_CallbackType SPI_Callback[MAX_SPI_NO] = {(SPI_CallbackType)NULL};

/*****************************************************************************//*!
   *
   * @brief 初始化SPI模块
   *        
   * @param[in]  pSPI     指向SPI模块.
   * @param[in]  pConfig  指向SPI配置参数.
   *
   * @return none.
   *
   *****************************************************************************/
void SPI_Init(SPI_Type *pSPI, SPI_ConfigType *pConfig)
{
#if defined(CPU_NV32M3)  
     /* sanity check */
    ASSERT((pSPI == SPI0));
    SIM->SCGC |= SIM_SCGC_SPI0_MASK;
#else
    /* sanity check */
    ASSERT((pSPI == SPI0) ||  (pSPI == SPI1));
    
    /*使能SPI模块总线时钟*/
    if( pSPI == SPI0)
    {
        SIM->SCGC |= SIM_SCGC_SPI0_MASK;
    }
    else
    {
        SIM->SCGC |= SIM_SCGC_SPI1_MASK;     
    }
#endif
    /*配置SPI控制寄存器 */
    if( pConfig->sSettings.bIntEn)  //使能SPI中断
    {
        SPI_IntEnable(pSPI);
#if defined(CPU_NV32M3)  
        NVIC_EnableIRQ(SPI0_IRQn);  
#else
        if( pSPI == SPI0 )
        {
			NVIC_EnableIRQ(SPI0_IRQn);
        }
        else
        {
			NVIC_EnableIRQ(SPI1_IRQn);
        }
#endif
    }

    if( pConfig->sSettings.bTxIntEn)  //使能SPI发送中断
    {
        SPI_TxIntEnable(pSPI);
#if defined(CPU_NV32M3)  
        NVIC_EnableIRQ(SPI0_IRQn);  
#else
        if( pSPI == SPI0 )
        {
			NVIC_EnableIRQ(SPI0_IRQn);
        }
        else
        {
			NVIC_EnableIRQ(SPI1_IRQn);
        }
#endif
    }
    if( pConfig->sSettings.bMasterMode)  //主/从机选择
    {
        SPI_SetMasterMode(pSPI); //SPI设置为主机模式
    }
    else
    {
		SPI_SetSlaveMode(pSPI); //SPI设置为从机模式
    }

    if( pConfig->sSettings.bClkPolarityLow) //时钟极性配置
    {
    	SPI_SetClockPol(pSPI,1);
    }
    if( pConfig->sSettings.bClkPhase1) //时钟相位配置
    {
        SPI_SetClockPhase(pSPI,1);
    }
    if( pConfig->sSettings.bShiftLSBFirst) //设置SPI串行数据传输开始位
    {
        SPI_SetLSBFirst(pSPI);  // SPI串行数据传输从最低位开始(LSB)
    }
    if( pConfig->sSettings.bMatchIntEn)
    {
        SPI_MatchIntEnable(pSPI); //使能SPI匹配中断
    }
    if( pConfig->sSettings.bModeFaultEn)
    {
        SPI_ModfEnable(pSPI);  //使能主机模式模式错误功能.
    }
    if( pConfig->sSettings.bMasterAutoDriveSS)
    {
			  /*设置SSOE和MODFEN位，从机模式中SS引脚为从机输出，自动驱动从机SS引脚使能*/
        SPI_SSOutputEnable(pSPI);
        SPI_ModfEnable(pSPI);
    }    
 
    if( pConfig->sSettings.bPinAsOuput)
    {
        SPI_BidirPinEnable(pSPI); //使能双向引脚配置.
    }

    if( pConfig->sSettings.bBidirectionModeEn)
    {
        SPI_BidirOutEnable(pSPI); //使能双向模式输出.
    }
    if( pConfig->sSettings.bStopInWaitMode)
    {
        SPI_ClockStopEnable(pSPI); //SPI时钟在等待模式下关闭
    }
    
    if(pConfig->sSettings.bMasterMode) //设置波特率
    {
        SPI_SetBaudRate(pSPI,pConfig->u32BusClkHz,pConfig->u32BitRate); 
    }

	/*使能SPI模块*/
    if( pConfig->sSettings.bModuleEn)
    {
        SPI_Enable(pSPI);
    }
}

/*****************************************************************************//*!
   *
   * @brief 设置SPI波特率.
   *        
   * @param[in]  pSPI   指向SPI模块
   * @param[in]  u32BusClock   总线时钟.
   * @param[in]  u32Bps   SPI波特率.
   *
   * @return  none.
   *
   *****************************************************************************/
void SPI_SetBaudRate(SPI_Type *pSPI,uint32_t u32BusClock,uint32_t u32Bps)
{
	uint32_t u32BitRateDivisor;
	uint8_t u8Sppr;
	uint8_t u8Spr;
    uint8_t u8ReadFlag;
	u32BitRateDivisor = u32BusClock/u32Bps; /* 计算波特率因子 */
       
    u8ReadFlag = 0;
    /* 计算最适合的 SPPR 和 SPR */
    for (u8Spr = 0; u8Spr <= 8; u8Spr++)
    {
        for(u8Sppr = 0; u8Sppr <= 7; u8Sppr++)
        {
            if((u32BitRateDivisor>>(u8Spr+1))<=(u8Sppr+1))
            {
                u8ReadFlag = 1;
                break;
            }
        }
        if(u8ReadFlag)
        {
            break;
        }
    }
    if(u8Sppr >=8)
    {
        u8Sppr = 7;
    }
    if(u8Spr >8)
    {
        u8Spr = 8;
    }
    /* 设置波特率 */
    pSPI->BR = SPI_BR_SPPR(u8Sppr) | SPI_BR_SPR(u8Spr);
}

/*****************************************************************************//*!
   *
   * @brief 读/写数据寄存器.
   *        
   * @param[in]   pSPI   指向SPI模块.
   * @param[in]   pWrBuff -- 发送（写）数组指针
   * @param[in]   uiLength -- 读/写数据长度.
   * @param[out]   pRdBuff --  接收（读）数组指针. 
   * 
   * @return  if <0, means error, 0: success.
   *
   *****************************************************************************/
ResultType SPI_TransferWait(SPI_Type *pSPI, SPI_WidthType* pRdBuff, SPI_WidthType *pWrBuff,uint32 uiLength)
{
    ResultType err = SPI_ERR_SUCCESS;
    uint32_t  i;
    
    if(!uiLength)
    {
        return (err);
    }
    for(i = 0; i < uiLength; i++)
    {
        while(!SPI_IsSPTEF(pSPI));
        SPI_WriteDataReg(pSPI,pWrBuff[i]);
        while(!SPI_IsSPRF(pSPI));
        pRdBuff[i] = SPI_ReadDataReg(pSPI);
    }
    return (err);        
}



/*****************************************************************************//*!
   *
   * @brief 复位SPI模块
   *        
   * @param[in]   pSPI 指向SPI模块
   *         
   * @return none.
   *
   *****************************************************************************/
void SPI_DeInit(SPI_Type *pSPI)
{  
    int16 i;
    pSPI->C1 = SPI_C1_DEFAULT;
    pSPI->C2 = SPI_C2_DEFAULT;
    pSPI->BR = SPI_BR_DEFAULT;
    pSPI->M  = SPI_M_DEFAULT;
    for(i = 0; i<100; i++);                 /*延时一段时间，等待SPI退出中断 */
}

/*****************************************************************************//*!
   *
   * @brief 设置SPI回调函数，在中断服务函数中调用
   *        
   * @param[in]   pSPI  指向SPI模块
   * @param[in]  pfnCallback  回调函数. 
   *  
   * @return none.
   *
*****************************************************************************/
void SPI_SetCallback(SPI_Type *pSPI,SPI_CallbackType pfnCallback)
{
    uint32_t    u32Port = ((uint32_t)pSPI-(uint32_t)SPI0)>>12;
    ASSERT(u32Port <2);
    SPI_Callback[u32Port] = pfnCallback;
}

/*****************************************************************************//*!
   *
   * @brief SPI0 中断服务函数.
   *        
   * @param   none.
   * @return  none.
   *
   *****************************************************************************/

void SPI0_Isr(void)
{
    if( SPI_Callback[0] )
    {
		SPI_Callback[0]();
    }
}
#ifndef CPU_NV32M3
/*****************************************************************************//*!
   *
   * @brief SPI1 中断服务函数
   *        
   * @param   none.
   * @return  none.
   *
   *****************************************************************************/

void SPI1_Isr(void)
{
    if( SPI_Callback[1] )
    {
		SPI_Callback[1]();
    }
}
#endif


