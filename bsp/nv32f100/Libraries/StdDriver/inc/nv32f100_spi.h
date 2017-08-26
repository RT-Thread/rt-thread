/******************************************************************************
*
* @brief  SPI 驱动头文件.  
*
******************************************************************************/
#ifndef SPI_H_
#define SPI_H_
#ifdef __cplusplus
extern "C" {
#endif
	
#include "common.h"
/******************************************************************************
* 定义SPI模块个数
******************************************************************************/
#define     MAX_SPI_NO              2

/******************************************************************************
* 
* 定义SPI寄存复位值
*
*******************************************************************************/

#define SPI_C1_DEFAULT          0x04						/*!< SPI 控制寄存器1 */
#define SPI_C2_DEFAULT          0x00						/*!< SPI 控制寄存器2 */
#define SPI_BR_DEFAULT          0x00						/*!< SPI 波特率寄存器 */
#define SPI_S_DEFAULT           0x20						/*!< SPI 状态寄存器 */
#define SPI_M_DEFAULT           0x00						/*!< SPI 匹配寄存器 */


/******************************************************************************
* 
* 定义SPI传输状态
*
*******************************************************************************/

#define     SPI_ERR_SUCCESS            0                                /*!< 成功 */
#define     SPI_ERR_CODE_BASE         ((uint32)SPI0 - 0x40000000L)      /*!< SPI基地址错误 */
#define     SPI_ERR_TXBUF_NOT_EMPTY   (SPI_ERR_CODE_BASE+1)             /*!< 失败由于发送缓冲区空时，标志位没有置位*/
#define     SPI_ERR_RXBUF_NOT_FULL    (SPI_ERR_CODE_BASE+2)             /*!< 失败由于接收缓冲区满时，标志位没有置位  */
     
/******************************************************************************
* 数据类型别名定义
******************************************************************************/

typedef uint8_t   SPI_WidthType;  /* SPI 发送数据宽度类型 */
typedef uint32_t  ResultType;     /* SPI 收发返回状态数据类型 */

/******************************************************************************
* 
* SPI回调函数声明
*
*******************************************************************************/
typedef void (*SPI_CallbackType)(void);  

/******************************************************************************
*
* SPI 结构体类型
* 
*******************************************************************************/
typedef struct
{
    uint32_t bIntEn                               : 1; /*!< 1: 使能中断, 0: 禁用中断*/
    uint32_t bModuleEn                            : 1; /*!< 1: 使能SPI模块, 0: 禁用SPI模块 */
    uint32_t bTxIntEn                             : 1; /*!< 1: 使能发送中断, 0: 禁用发送中断 */
    uint32_t bMasterMode                          : 1; /*!< 1: 主机模式, 0: 从机模式 */
    uint32_t bClkPolarityLow                      : 1; /*!< 设置时钟极性 */
    uint32_t bClkPhase1                           : 1; /*!< 设置时钟相位 */
    uint32_t bMasterAutoDriveSS                   : 1; /*!< 从机选择输出使能 */
    uint32_t bShiftLSBFirst                       : 1; /*!< 1: LSB, 0: MSB */
    uint32_t bMatchIntEn                          : 1; /*!< 1: 使能匹配中断, 0: 禁用匹配中断 */
    uint32_t bModeFaultEn                         : 1; /*!< 使能主机模式错误功能 */
    uint32_t bBidirectionModeEn                   : 1; /*!< 双向模式输出控制 */
    uint32_t bPinAsOuput                          : 1; /*!< SPI引脚控制 */
    uint32_t bStopInWaitMode                      : 1; /*!< 配置SPI时钟在等待模式下的工作状态 */
    uint32_t bRsvd                                : 19;
} SPI_SettingType;


/******************************************************************************
*
* SPI配置结构体类型
* 
*******************************************************************************/

typedef struct 
{
    SPI_SettingType     sSettings;              /*!< SPI 结构体 */
    uint32_t              u32BitRate;           /*!< 设置波特率 */
    uint32_t              u32BusClkHz;          /*!< 输入总线时钟 */
} SPI_ConfigType;                              /*!< SPI配置结构体 */


/*****************************************************************************//*!
   *
   * @brief SPI串行数据传输从最低位开始(LSB)
   *        
   * @param[in]  pSPI  指向SPI模块  
   *
   * @return  none.
   *
   *****************************************************************************/

 __STATIC_INLINE void SPI_SetLSBFirst(SPI_Type *pSPI)
{
	pSPI->C1 |= SPI_C1_LSBFE_MASK;
}
/*****************************************************************************//*!
   *
   * @brief SPI串行数据传输从最高位开始(MSB)
   *        
   * @param[in]  pSPI  指向SPI模块  
   *
   * @return  none.
   *
   *****************************************************************************/

 __STATIC_INLINE void SPI_SetMSBFirst(SPI_Type *pSPI)
{
	pSPI->C1 &= ~SPI_C1_LSBFE_MASK;
}
/*****************************************************************************//*!
   *
   * @brief 设置SPI时钟极性.
   *        
   * @param[in]  pSPI  指向SPI模块  .  
   * @param[in]  u8PolLow   设置时钟极性.  1-SCK时钟有效状态为高（无效状态为低）
   *                                       0-SCK时钟有效状态为低（无效状态为高）
   * @return  none
   *
   *****************************************************************************/

 __STATIC_INLINE void SPI_SetClockPol(SPI_Type *pSPI,uint8_t u8PolLow)
{
	if( u8PolLow )
	{
		pSPI->C1 |= SPI_C1_CPOL_MASK;	
	}
	else
	{
		pSPI->C1 &= ~SPI_C1_CPOL_MASK;	
	}
}
/*****************************************************************************//*!
   *
   * @brief 设置SPI时钟相位.
   *        
   * @param[in]  pSPI   指向SPI模块  
   * @param[in]  u8Phase  设置时钟相位, 1 - 数据在SCK下降沿输出，在上升沿采样. 
   *                                    0 - 数据在SCK上升沿采样，在下降沿输出
   * @return  none
   *
   *****************************************************************************/

 __STATIC_INLINE void SPI_SetClockPhase(SPI_Type *pSPI,uint8_t u8Phase)
{
	if( u8Phase )
	{
		pSPI->C1 |= SPI_C1_CPHA_MASK;	
	}
	else
	{
		pSPI->C1 &= ~SPI_C1_CPHA_MASK;	
	}
}
/*****************************************************************************//*!
   *
   * @brief 使能SPI模块.
   *        
   * @param[in]  pSPI  指向SPI模块    
   *
   * @return  none
   *
   *****************************************************************************/

 __STATIC_INLINE void SPI_Enable(SPI_Type *pSPI)
{
	pSPI->C1 |= SPI_C1_SPE_MASK;
}
/*****************************************************************************//*!
   *
   * @brief 禁用SPI模块
   *        
   * @param[in]  pSPI   指向SPI模块  
   *  
   * @return  none
   *
   *****************************************************************************/

 __STATIC_INLINE void SPI_Disable(SPI_Type *pSPI)
{
	pSPI->C1 &= ~SPI_C1_SPE_MASK;
}
/*****************************************************************************//*!
   *
   * @brief 使能SPI中断.
   *        
   * @param[in]  pSPI  指向SPI模块  
   *
   * @return  none
   *
   *****************************************************************************/

 __STATIC_INLINE void SPI_IntEnable(SPI_Type *pSPI)
{
	pSPI->C1 |= SPI_C1_SPIE_MASK;
}
/*****************************************************************************//*!
   *
   * @brief  禁用SPI中断.
   *        
   * @param[in]  pSPI   指向SPI模块    
   *
   * @return  none
   *
   *****************************************************************************/
 __STATIC_INLINE void SPI_IntDisable(SPI_Type *pSPI)
{
	pSPI->C1 &= ~SPI_C1_SPIE_MASK;
}
/*****************************************************************************//*!
   *
   * @brief 设置SPI为主机模式.
   *        
   * @param[in]  pSPI   指向SPI模块    
   *
   * @return  none
   *
   *****************************************************************************/
 __STATIC_INLINE void SPI_SetMasterMode(SPI_Type *pSPI)
{
	pSPI->C1 |= SPI_C1_MSTR_MASK;
}
/*****************************************************************************//*!
   *
   * @brief 设置SPI为从机模式.
   *        
   * @param[in]  pSPI   指向SPI模块  .  
   *
   * @return  none
   *
   *****************************************************************************/
 __STATIC_INLINE void SPI_SetSlaveMode(SPI_Type *pSPI)
{
	pSPI->C1 &= ~SPI_C1_MSTR_MASK;
}
/*****************************************************************************//*!
   *
   * @brief 使能SPI发送中断.
   *        
   * @param[in]  pSPI   指向SPI模块  .  
   *
   * @return  none.
   *
   *****************************************************************************/
 __STATIC_INLINE void SPI_TxIntEnable(SPI_Type *pSPI)
{
	pSPI->C1 |= SPI_C1_SPTIE_MASK;
}
/*****************************************************************************//*!
   *
   * @brief 禁用SPI发送中断.
   *        
   * @param[in]  pSPI   指向SPI模块  .  
   *
   * @return  none
   *
   * @ Pass/ Fail criteria: none
   *****************************************************************************/
 __STATIC_INLINE void SPI_TxIntDisable(SPI_Type *pSPI)
{
	pSPI->C1 &= ~SPI_C1_SPTIE_MASK;
}
/*****************************************************************************//*!
   *
   * @brief 使能从机选择输出.
   *        
   * @param[in]  pSPI   指向SPI模块  .  
   *
   * @return  none
   *
   *****************************************************************************/
 __STATIC_INLINE void SPI_SSOutputEnable(SPI_Type *pSPI )
{
	pSPI->C1 |= SPI_C1_SSOE_MASK;
}
/*****************************************************************************//*!
   *
   * @brief 禁用从机选择输出.
   *        
   * @param[in]  pSPI   指向SPI模块  .  
   *
   * @return  none
   *
   *****************************************************************************/
 __STATIC_INLINE void SPI_SSOutputDisable(SPI_Type *pSPI )
{
	pSPI->C1 &= ~SPI_C1_SSOE_MASK;
}
/*****************************************************************************//*!
   *
   * @brief 使能SPI匹配中断.
   *        
   * @param[in]  pSPI  指向SPI模块  .  
   * 
   * @return  none
   *
   *****************************************************************************/
 __STATIC_INLINE void SPI_MatchIntEnable(SPI_Type *pSPI )
{
	pSPI->C2 |= SPI_C2_SPMIE_MASK;
}
/*****************************************************************************//*!
   *
   * @brief 禁用SPI匹配中断.
   *        
   * @param[in]  pSPI  指向SPI模块    
   *
   * @return  none.
   *
   *****************************************************************************/
 __STATIC_INLINE void SPI_MatchIntDisable(SPI_Type *pSPI )
{
	pSPI->C2 &= ~SPI_C2_SPMIE_MASK;
}
/*****************************************************************************//*!
   *
   * @brief 禁用主机模式错误功能
   *        
   * @param[in]  pSPI   指向SPI模块  .  
   *
   * @return  none.
   *
   *****************************************************************************/
 __STATIC_INLINE void SPI_ModfDisable(SPI_Type *pSPI )
{
	pSPI->C2 &= ~SPI_C2_MODFEN_MASK;
}
/*****************************************************************************//*!

   *
   * @brief 使能主机模式模式错误功能.
   *        
   * @param[in]  pSPI   指向SPI模块   
   *
   * @return  none.
   *
   *****************************************************************************/
 __STATIC_INLINE void SPI_ModfEnable(SPI_Type *pSPI )
{
	pSPI->C2 |= SPI_C2_MODFEN_MASK;
}
/*****************************************************************************//*!
   *
   * @brief 使能双向模式输出.
   *        
   * @param[in]  pSPI   指向SPI模块  .  
   *
   * @return  none.
   *
   *****************************************************************************/
 __STATIC_INLINE void SPI_BidirOutEnable(SPI_Type *pSPI )
{
	pSPI->C2 |= SPI_C2_BIDIROE_MASK;
}
/*****************************************************************************//*!
   *
   * @brief 禁用双向模式输出
   *        
   * @param[in]  pSPI  指向SPI模块    
   *
   * @return  none.
   *
   *****************************************************************************/
 __STATIC_INLINE void SPI_BidirOutDisable(SPI_Type *pSPI )
{
	pSPI->C2 &= ~SPI_C2_BIDIROE_MASK;
}
/*****************************************************************************//*!
   *
   * @brief SPI时钟在等待模式下一直运行
   *        
   * @param[in]  pSPI  指向SPI模块  .  
   * 
   * @return  none.
   *
   *****************************************************************************/
 __STATIC_INLINE void SPI_ClockStopDisable(SPI_Type *pSPI )
{
	pSPI->C2 &= ~SPI_C2_SPISWAI_MASK;
}
/*****************************************************************************//*!
   *
   * @brief SPI时钟在等待模式下关闭
   *        
   * @param[in]  pSPI   指向SPI模块    
   *  
   * @return  none
   *
   *****************************************************************************/
 __STATIC_INLINE void SPI_ClockStopEnable(SPI_Type *pSPI )
{
	pSPI->C2 |= SPI_C2_SPISWAI_MASK;
}
/*****************************************************************************//*!
   *
   * @brief 使能双向引脚配置.
   *        
   * @param[in]  pSPI   指向SPI模块    
   *   
   * @return  none
   *
   *****************************************************************************/
 __STATIC_INLINE void SPI_BidirPinEnable(SPI_Type *pSPI)
{
	pSPI->C2 |= SPI_C2_SPC0_MASK;
}
/*****************************************************************************//*!
   *
   * @brief SPI使用独立的引脚用作数据的输入输出.
   *        
   * @param[in]  pSPI  指向SPI模块    
   *   
   * @return  none
   *
   *****************************************************************************/
 __STATIC_INLINE void SPI_BidirPinDisable(SPI_Type *pSPI)
{
	pSPI->C2 &= ~SPI_C2_SPC0_MASK;
}
/*****************************************************************************//*!
   *
   * @brief 读取接收数据缓冲区满标准位.
   *        
   * @param[in]  pSPI   指向SPI模块  .  
   *    
   * @return  TRUE or FALSE.
   *
   *****************************************************************************/
 __STATIC_INLINE uint8_t SPI_IsSPRF(SPI_Type *pSPI )
{
	return(pSPI->S & SPI_S_SPRF_MASK);
}
/*****************************************************************************//*!
   *
   * @brief 读取SPI匹配标志位
   *        
   * @param[in]  pSPI   指向SPI模块  .  
   *    
   * @return  TRUE or FALSE.
   *
   *****************************************************************************/
 __STATIC_INLINE uint8_t SPI_IsSPMF(SPI_Type *pSPI )
{
	return(pSPI->S & SPI_S_SPMF_MASK);
}
/*****************************************************************************//*!
   *
   * @brief 读取SPI发送数据缓冲区空标志位.
   *        
   * @param[in]  pSPI   指向SPI模块  .  
   *    
   * @return  TRUE or FALSE.
   *
   *****************************************************************************/
 __STATIC_INLINE uint8_t SPI_IsSPTEF(SPI_Type *pSPI )
{
	return(pSPI->S & SPI_S_SPTEF_MASK);
}
/*****************************************************************************//*!
   *
   * @brief 读取主机模式错误标志位
   *        
   * @param[in]  pSPI 指向SPI模块    
   *    
   * @return  TRUE or FALSE.
   *
   *****************************************************************************/
 __STATIC_INLINE uint8_t SPI_IsMODF(SPI_Type *pSPI )
{
	return(pSPI->S & SPI_S_MODF_MASK);
}
/*****************************************************************************//*!
   *
   * @brief 读取SPI数据寄存器.
   *        
   * @param[in]  pSPI   指向SPI模块    
   *    
   * @return 数据寄存器的值
   *
   *****************************************************************************/
 __STATIC_INLINE uint8_t SPI_ReadDataReg(SPI_Type *pSPI )
{
	return pSPI->D;
}
/*****************************************************************************//*!
   *
   * @brief  写数据到SPI数据寄存器.
   *        
   * @param[in]  pSPI  指向SPI模块   
   * @param[in]  u8WrBuff   写到SPI数据寄存器的数据缓冲区 
   *
   * @return  none
   *
   *****************************************************************************/
 __STATIC_INLINE void SPI_WriteDataReg(SPI_Type *pSPI, uint8_t u8WrBuff )
{
	pSPI->D = u8WrBuff;
}
/*****************************************************************************//*!
   *
   * @brief 写数据到SPI匹配寄存器.
   *        
   * @param[in]  pSPI   指向SPI模块  
   * @param[in]  u8WrBuff   写到SPI匹配寄存器的数据缓冲区 
   *
   * @return  none
   *
   *****************************************************************************/
 __STATIC_INLINE void SPI_WriteMatchValue(SPI_Type *pSPI, uint8_t u8WrBuff )
{
	pSPI->M = u8WrBuff;
}
/******************************************************************************/

void SPI_Enable(SPI_Type *pSPI);
void SPI_Disable(SPI_Type *pSPI);
void SPI_SetLSBFirst(SPI_Type *pSPI);
void SPI_SetMSBFirst(SPI_Type *pSPI);
void SPI_IntEnable(SPI_Type *pSPI);
void SPI_IntDisable(SPI_Type *pSPI);
void SPI_SetMasterMode(SPI_Type *pSPI);
void SPI_SetSlaveMode(SPI_Type *pSPI);
void SPI_TxIntEnable(SPI_Type *pSPI);
void SPI_TxIntDisable(SPI_Type *pSPI);
void SPI_SSOutputEnable(SPI_Type *pSPI );
void SPI_SSOutputDisable(SPI_Type *pSPI );
void SPI_MatchIntEnable(SPI_Type *pSPI );
void SPI_MatchIntDisable(SPI_Type *pSPI );
void SPI_ModfDisable(SPI_Type *pSPI );
void SPI_ModfEnable(SPI_Type *pSPI );
void SPI_BidirOutEnable(SPI_Type *pSPI );
void SPI_BidirOutDisable(SPI_Type *pSPI );
void SPI_ClockStopDisable(SPI_Type *pSPI );
void SPI_ClockStopEnable(SPI_Type *pSPI );
void SPI_BidirPinEnable(SPI_Type *pSPI );
void SPI_BidirPinDisable(SPI_Type *pSPI );
void SPI_SetClockPol(SPI_Type *pSPI,uint8_t u8PolLow);
void SPI_SetClockPhase(SPI_Type *pSPI,uint8_t u8Phase);
void SPI_SetBaudRate(SPI_Type *pSPI,uint32_t u32BusClock,uint32_t u32Bps );
uint8_t SPI_IsSPRF(SPI_Type *pSPI );
uint8_t SPI_IsSPMF(SPI_Type *pSPI );
uint8_t SPI_IsSPTEF(SPI_Type *pSPI );
uint8_t SPI_IsMODF(SPI_Type *pSPI );
uint8_t SPI_ReadDataReg(SPI_Type *pSPI );
void SPI_WriteDataReg(SPI_Type *pSPI, uint8_t u8WrBuff );
void SPI_WriteMatchValue(SPI_Type *pSPI, uint8_t u8WrBuff );
void SPI_Init(SPI_Type *pSPI, SPI_ConfigType *pConfig);
void SPI_DeInit(SPI_Type *pSPI);
ResultType SPI_TransferWait(SPI_Type *pSPI, SPI_WidthType* pRdBuff, SPI_WidthType *pWrBuff,uint32 uiLength);
void SPI_SetCallback(SPI_Type *pSPI,SPI_CallbackType pfnCallback);


#ifdef __cplusplus
}
#endif
#endif 
