/******************************************************************************
*Copyright(C)2018, Huada Semiconductor Co.,Ltd All rights reserved.
*
* This software is owned and published by:
* Huada Semiconductor Co.,Ltd("HDSC").
*
* BY DOWNLOADING, INSTALLING OR USING THIS SOFTWARE, YOU AGREE TO BE BOUND
* BY ALL THE TERMS AND CONDITIONS OF THIS AGREEMENT.
*
* This software contains source code for use with HDSC
* components. This software is licensed by HDSC to be adapted only
* for use in systems utilizing HDSC components. HDSC shall not be
* responsible for misuse or illegal use of this software for devices not
* supported herein. HDSC is providing this software "AS IS" and will
* not be responsible for issues arising from incorrect user implementation
* of the software.
*
* Disclaimer:
* HDSC MAKES NO WARRANTY, EXPRESS OR IMPLIED, ARISING BY LAW OR OTHERWISE,
* REGARDING THE SOFTWARE (INCLUDING ANY ACOOMPANYING WRITTEN MATERIALS),
* ITS PERFORMANCE OR SUITABILITY FOR YOUR INTENDED USE, INCLUDING,
* WITHOUT LIMITATION, THE IMPLIED WARRANTY OF MERCHANTABILITY, THE IMPLIED
* WARRANTY OF FITNESS FOR A PARTICULAR PURPOSE OR USE, AND THE IMPLIED
* WARRANTY OF NONINFRINGEMENT.
* HDSC SHALL HAVE NO LIABILITY (WHETHER IN CONTRACT, WARRANTY, TORT,
* NEGLIGENCE OR OTHERWISE) FOR ANY DAMAGES WHATSOEVER (INCLUDING, WITHOUT
* LIMITATION, DAMAGES FOR LOSS OF BUSINESS PROFITS, BUSINESS INTERRUPTION,
* LOSS OF BUSINESS INFORMATION, OR OTHER PECUNIARY LOSS) ARISING FROM USE OR
* INABILITY TO USE THE SOFTWARE, INCLUDING, WITHOUT LIMITATION, ANY DIRECT,
* INDIRECT, INCIDENTAL, SPECIAL OR CONSEQUENTIAL DAMAGES OR LOSS OF DATA,
* SAVINGS OR PROFITS,
* EVEN IF Disclaimer HAS BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.
* YOU ASSUME ALL RESPONSIBILITIES FOR SELECTION OF THE SOFTWARE TO ACHIEVE YOUR
* INTENDED RESULTS, AND FOR THE INSTALLATION OF, USE OF, AND RESULTS OBTAINED
* FROM, THE SOFTWARE.
*
* This software may be replicated in part or whole for the licensed use,
* with the restriction that this Disclaimer and Copyright notice must be
* included with each copy of this software, whether used in part or whole,
* at all times.
*/

/** \file flash.c
 **
 ** Common API of flash.
 ** @link flashGroup Some description @endlink
 **
 **   - 2018-05-08
 **
 ******************************************************************************/

/*******************************************************************************
 * Include files
 ******************************************************************************/
#include "hc32l196_flash.h"
/**
 *******************************************************************************
 ** \addtogroup FlashGroup
 ******************************************************************************/
//@{

/*******************************************************************************
 * Local pre-processor symbols/macros ('#define')
 ******************************************************************************/
#define FLASH_END_ADDR              (0x0003FFFFu)
#define FLASH_BYPASS()              M0P_FLASH->BYPASS = 0x5A5A;\
                                    M0P_FLASH->BYPASS = 0xA5A5; 
#define FLASH_IE_TRUE               (0x03)
#define FLASH_IE_FALSE              (0x00)

#define FLASH_TIMEOUT_INIT          (0xFFFFFFu)
#define FLASH_TIMEOUT_PGM           (0xFFFFFFu)
#define FLASH_TIMEOUT_ERASE         (0xFFFFFFu)

#define FLASH_LOCK_ALL              (0u)
#define FLASH_UNLOCK_ALL            (0xFFFFFFFFu)
/*******************************************************************************
 * Global variable definitions (declared in header file with 'extern')
 ******************************************************************************/

/*******************************************************************************
 * Local type definitions ('typedef')
 ******************************************************************************/
/**
 ******************************************************************************
 ** \brief FLASH OP
 ** 
 ** Flash 操作控制数据类型重定义 
 ******************************************************************************/
typedef enum en_flash_op
{
    Read        = 0u,           ///<读配置值
    Program     = 1u,           ///<编程配置值
    SectorErase = 2u,           ///<扇区擦除配置值
    ChipErase   = 3u,           ///<全片擦除配置值
} en_flash_op_t;

/**
 ******************************************************************************
 ** \brief FLASH 编程时间参数配置
 ** 
 ** FLASH编程时间参数配置数组定义 (4MHz)
 ******************************************************************************/
const uint32_t pu32PcgTimer4M[] = { 
                                    0x20u,          //Tnvs   
                                    0x17u,          //Tpgs   
                                    0x1Bu,          //Tprog  
                                    0x4650u,        //Tserase
                                    0x222E0u,       //Tmerase
                                    0x18u,          //Tprcv  
                                    0xF0u,          //Tsrcv  
                                    0x3E8u          //Tmrcv  
                                  };
/*******************************************************************************
 * Local variable definitions ('static')
 ******************************************************************************/

/*******************************************************************************
 * Local function prototypes ('static')
 ******************************************************************************/

/*******************************************************************************
 * Function implementation - global ('extern') and local ('static')
 ******************************************************************************/

/**
 *****************************************************************************
 ** \brief Flash中断标志获取
 **
 **
 ** \param [in]  enFlashIntType          Flash中断类型
 ** 
 ** \retval TRUE or FALSE                                      
 *****************************************************************************/
boolean_t Flash_GetIntFlag(en_flash_int_type_t enFlashIntType)
{
    boolean_t bRetVal = FALSE;
    
    if(M0P_FLASH->IFR & enFlashIntType)
    {
        bRetVal =  TRUE;
    }
    
    return bRetVal;
}

/**
 *****************************************************************************
 ** \brief Flash中断标志清除
 **
 **
 ** \param [in]  enFlashIntType          Flash中断类型
 ** 
 ** \retval Ok or Error                                      
 *****************************************************************************/
en_result_t Flash_ClearIntFlag(en_flash_int_type_t enFlashIntType)
{
    en_result_t enResult = Error;

    M0P_FLASH->ICLR &= ~(uint32_t)enFlashIntType;
    enResult = Ok;
    
    return enResult;
}

/**
 *****************************************************************************
 ** \brief Flash中断使能
 **
 **
 ** \param [in]  enFlashIntType          Flash中断类型
 ** 
 ** \retval Ok or Error                                      
 *****************************************************************************/
en_result_t Flash_EnableIrq (en_flash_int_type_t enFlashIntType)
{
    en_result_t enResult = Error;

    FLASH_BYPASS();
    M0P_FLASH->CR_f.IE |= enFlashIntType;
    
    enResult = Ok;

    return enResult;
}

/**
 *****************************************************************************
 ** \brief Flash中断禁止
 **
 **
 ** \param [in]  enFlashIntType          Flash中断类型
 ** 
 ** \retval Ok or Error                                      
 *****************************************************************************/
en_result_t Flash_DisableIrq(en_flash_int_type_t enFlashIntType)
{
    en_result_t enResult = Error;

    FLASH_BYPASS();
    M0P_FLASH->CR_f.IE &= ~(uint32_t)enFlashIntType;
    
    enResult = Ok;

    return enResult;
}

/**
 *****************************************************************************
 ** \brief FLASH 初始化函数——中断服务程序、编程时间配置及低功耗模式
 **
 ** 该函数用于配置中断服务函数、低功耗模式、根据系统时钟配置FLASH编程时间相关寄存器.
 **
 ** \param [in]  u8FreqCfg        FLASH编程时钟频率配置(根据HCLK的频率选择配置值)：
 **                               1      - 4MHz;
 **                               2      - 8MHz;
 **                               4      - 16MHz;
 **                               6      - 24MHz;
 **                               8      - 32MHz;
 **                               12     - 48MHz;
 **                               other   -  无效值
 ** \param [in] bDpstbEn          TRUE  - 当系统进入DeepSleep模式，FLASH进入低功耗模式;
 **                               FALSE - 当系统进入DeepSleep模式，FLASH不进入低功耗模式;
 ** 
 ** \retval Ok                    操作成功.
 ** \retval ErrorInvalidParameter 参数无效.
 ** \retval ErrorUninitialized    初始化失败。
 *****************************************************************************/
en_result_t Flash_Init(uint8_t u8FreqCfg, boolean_t bDpstbEn)
{
    uint32_t                u32Index  = 0;
    volatile uint32_t       u32TimeOut = FLASH_TIMEOUT_INIT;
    en_result_t             enResult  = Ok;
    uint32_t                u32PrgTimer[8] = {0}; 
    volatile uint32_t       *pu32PrgTimerReg = (volatile uint32_t*)M0P_FLASH;
    
    if ((1  != u8FreqCfg) && (2  != u8FreqCfg) &&
        (4  != u8FreqCfg) && (6  != u8FreqCfg) &&
        (8  != u8FreqCfg) && (12 != u8FreqCfg))
    {
        enResult = ErrorInvalidParameter;
        return (enResult);
    }
    
    M0P_FLASH->CR_f.DPSTB_EN = bDpstbEn;
    
    //flash时间参数配置值计算
    for(u32Index=0; u32Index<8; u32Index++)
    {
        u32PrgTimer[u32Index] = u8FreqCfg * pu32PcgTimer4M[u32Index];
    } 
    
    //flash时间参数寄存器配置
    for(u32Index=0; u32Index<8; u32Index++)
    {
        u32TimeOut = FLASH_TIMEOUT_INIT;
        while(pu32PrgTimerReg[u32Index]  != u32PrgTimer[u32Index])
        {
            if(u32TimeOut--)
            {
                FLASH_BYPASS();
                pu32PrgTimerReg[u32Index] = u32PrgTimer[u32Index];
            }
            else
            {
                return ErrorUninitialized;
            }
        }
    }
    
    return (enResult);
}

/**
 *****************************************************************************
 ** \brief FLASH 字节写
 **
 ** 用于向FLASH写入1字节数据.
 **
 ** \param [in]  u32Addr          Flash地址
 ** \param [in]  u8Data           1字节数据
 ** 
 ** \retval Ok                    写入成功.
 ** \retval ErrorInvalidParameter FLASH地址无效
 ** \retval ErrorTimeout          操作超时
 *****************************************************************************/
en_result_t Flash_WriteByte(uint32_t u32Addr, uint8_t u8Data)
{
    en_result_t             enResult = Ok;    
    volatile uint32_t       u32TimeOut = FLASH_TIMEOUT_PGM;
    
    if (FLASH_END_ADDR < u32Addr)
    {
        enResult = ErrorInvalidParameter;
        return (enResult);
    }
    
    //busy?
    u32TimeOut = FLASH_TIMEOUT_PGM;
    while (TRUE == M0P_FLASH->CR_f.BUSY)
    {
        if(0 == u32TimeOut--)
        {
            return ErrorTimeout;
        }
    }
    
    //set OP
    u32TimeOut = FLASH_TIMEOUT_PGM;
    while(Program != M0P_FLASH->CR_f.OP)
    {
        if(u32TimeOut--)
        {
            FLASH_BYPASS();
            M0P_FLASH->CR_f.OP = Program;
        }
        else
        {
            return ErrorTimeout;
        }
    }
    
    //Flash 解锁
    Flash_UnlockAll();
    
    //write data
    *((volatile uint8_t*)u32Addr) = u8Data;
    
    //busy?
    u32TimeOut = FLASH_TIMEOUT_PGM;
    while (TRUE == M0P_FLASH->CR_f.BUSY)
    {
        if(0 == u32TimeOut--)
        {
            return ErrorTimeout;
        }
    }
    
    //Flash 加锁
    Flash_LockAll();
    
    return (enResult);
}

/**
 *****************************************************************************
 ** \brief FLASH 半字写
 **
 ** 用于向FLASH写入半字（2字节）数据.
 **
 ** \param [in]  u32Addr         Flash地址
 ** \param [in]  u16Data        半字（2字节）数据
 ** 
 ** \retval Ok                    写入成功.
 ** \retval ErrorInvalidParameter FLASH地址无效
 ** \retval ErrorTimeout          操作超时
 *****************************************************************************/
en_result_t Flash_WriteHalfWord(uint32_t u32Addr, uint16_t u16Data)
{
    en_result_t             enResult = Ok;    
    volatile uint32_t       u32TimeOut = FLASH_TIMEOUT_PGM;
    
    if (FLASH_END_ADDR < u32Addr)
    {
        enResult = ErrorInvalidParameter;
        return (enResult);
    }
    
    //busy?
    u32TimeOut = FLASH_TIMEOUT_PGM;
    while (TRUE == M0P_FLASH->CR_f.BUSY)
    {
        if(0 == u32TimeOut--)
        {
            return ErrorTimeout;
        }
    }
    
    //set OP
    u32TimeOut = FLASH_TIMEOUT_PGM;
    while(Program != M0P_FLASH->CR_f.OP)
    {
        if(u32TimeOut--)
        {
            FLASH_BYPASS();
            M0P_FLASH->CR_f.OP = Program;
        }
        else
        {
            return ErrorTimeout;
        }
    }
    
    //Flash 解锁
    Flash_UnlockAll();
    
    //write data
    *((volatile uint16_t*)u32Addr) = u16Data;
    
    //busy?
    u32TimeOut = FLASH_TIMEOUT_PGM;
    while (TRUE == M0P_FLASH->CR_f.BUSY)
    {
        if(0 == u32TimeOut--)
        {
            return ErrorTimeout;
        }
    }
    
    //Flash 加锁
    Flash_LockAll();
    
    return (enResult);
}

/**
 *****************************************************************************
 ** \brief FLASH 字写
 **
 ** 用于向FLASH写入1个字的数据.
 **
 ** \param [in]  u32Addr         Flash地址
 ** \param [in]  u32Data         1个字数据
 ** 
 ** \retval Ok                    写入成功.
 ** \retval ErrorInvalidParameter FLASH地址无效
 ** \retval ErrorTimeout          操作超时
 *****************************************************************************/
en_result_t Flash_WriteWord(uint32_t u32Addr, uint32_t u32Data)
{
    en_result_t             enResult = Ok;    
    volatile uint32_t       u32TimeOut = FLASH_TIMEOUT_PGM;
    
    if (FLASH_END_ADDR < u32Addr)
    {
        enResult = ErrorInvalidParameter;
        return (enResult);
    }
    
    //busy?
    u32TimeOut = FLASH_TIMEOUT_PGM;
    while (TRUE == M0P_FLASH->CR_f.BUSY)
    {
        if(0 == u32TimeOut--)
        {
            return ErrorTimeout;
        }
    }
    
    //Flash 解锁
    Flash_UnlockAll();
    
    //set OP
    u32TimeOut = FLASH_TIMEOUT_PGM;
    while(Program != M0P_FLASH->CR_f.OP)
    {
        if(u32TimeOut--)
        {
            FLASH_BYPASS();
            M0P_FLASH->CR_f.OP = Program;
        }
        else
        {
            return ErrorTimeout;
        }
    }
    
    //write data
    *((volatile uint32_t*)u32Addr) = u32Data;
    
    //busy?
    u32TimeOut = FLASH_TIMEOUT_PGM;
    while (TRUE == M0P_FLASH->CR_f.BUSY)
    {
        if(0 == u32TimeOut--)
        {
            return ErrorTimeout;
        }
    }
    
    //Flash 加锁
    Flash_LockAll();
    
    return (enResult);
}

/**
 *****************************************************************************
 ** \brief FLASH 扇区擦除
 **
 ** FLASH 扇区擦除.
 **
 ** \param [in]  u32SectorAddr    所擦除扇区内的地址
 ** 
 ** \retval Ok                    擦除成功.
 ** \retval ErrorInvalidParameter FLASH地址无效 
 ** \retval ErrorTimeout          操作超时
 *****************************************************************************/
en_result_t Flash_SectorErase(uint32_t u32SectorAddr)
{
    en_result_t             enResult = Ok;    
    volatile uint32_t       u32TimeOut = FLASH_TIMEOUT_ERASE;
    
    if (FLASH_END_ADDR < u32SectorAddr)
    {
        enResult = ErrorInvalidParameter;
        return (enResult);
    }
    
    //busy?
    u32TimeOut = FLASH_TIMEOUT_ERASE;
    while (TRUE == M0P_FLASH->CR_f.BUSY)
    {
        if(0 == u32TimeOut--)
        {
            return ErrorTimeout;
        }
    }
    
    //Flash 解锁
    Flash_UnlockAll();
    
    //set OP
    u32TimeOut = FLASH_TIMEOUT_ERASE;
    while(SectorErase != M0P_FLASH->CR_f.OP)
    {
        if(u32TimeOut--)
        {
            FLASH_BYPASS();
            M0P_FLASH->CR_f.OP = SectorErase;
        }
        else
        {
            return ErrorTimeout;
        }
    }
    
    //write data
    *((volatile uint8_t*)u32SectorAddr) = 0;
    
    //busy?
    u32TimeOut = FLASH_TIMEOUT_ERASE;
    while (TRUE == M0P_FLASH->CR_f.BUSY)
    {
        if(0 == u32TimeOut--)
        {
            return ErrorTimeout;
        }
    }
    
    //Flash 加锁
    Flash_LockAll();
    
    return (enResult);
}

/**
 *****************************************************************************
 ** \brief FLASH 全片擦除(该函数仅限RAM中运行！！！)
 **
 ** FLASH 全片擦除.
 **
 ** 
 ** \retval Ok              擦除成功.
 ** \retval ErrorTimeout    操作超时
 **
 *****************************************************************************/
en_result_t Flash_ChipErase(void)
{
    en_result_t             enResult = Ok;    
    volatile uint32_t       u32TimeOut = FLASH_TIMEOUT_ERASE; 
    
    //busy?
    u32TimeOut = FLASH_TIMEOUT_ERASE;
    while (TRUE == M0P_FLASH->CR_f.BUSY)
    {
        if(0 == u32TimeOut--)
        {
            return ErrorTimeout;
        }
    }
    
    //set OP
    u32TimeOut = FLASH_TIMEOUT_ERASE;
    while(ChipErase != M0P_FLASH->CR_f.OP)
    {
        if(u32TimeOut--)
        {
            FLASH_BYPASS();
            M0P_FLASH->CR_f.OP = ChipErase;
        }
        else
        {
            return ErrorTimeout;
        }
    }
    
    //Flash 解锁
    Flash_UnlockAll();
    
    //write data
    *((volatile uint8_t*)0) = 0;
    
    //busy?
    u32TimeOut = FLASH_TIMEOUT_ERASE;
    while (TRUE == M0P_FLASH->CR_f.BUSY)
    {
        if(0 == u32TimeOut--)
        {
            return ErrorTimeout;
        }
    }
    
    //Flash 加锁
    Flash_LockAll();
    
    return (enResult);
}

/**
 *****************************************************************************
 ** \brief FLASH 编程保护加锁
 **
 ** 
 ** \retval Null                               
 *****************************************************************************/
void Flash_LockAll(void)
{ 
    FLASH_BYPASS();
    M0P_FLASH->SLOCK0 = FLASH_LOCK_ALL;
    FLASH_BYPASS();
    M0P_FLASH->SLOCK1 = FLASH_LOCK_ALL;    
    FLASH_BYPASS();
    M0P_FLASH->SLOCK2 = FLASH_LOCK_ALL;
    FLASH_BYPASS();
    M0P_FLASH->SLOCK3 = FLASH_LOCK_ALL;

}

/**
 *****************************************************************************
 ** \brief FLASH 编程保护解锁
 **
 ** 
 ** \retval Null                             
 *****************************************************************************/
void Flash_UnlockAll(void)
{
   
    FLASH_BYPASS();
    M0P_FLASH->SLOCK0 = FLASH_UNLOCK_ALL;
    FLASH_BYPASS();
    M0P_FLASH->SLOCK1 = FLASH_UNLOCK_ALL;
    FLASH_BYPASS();
    M0P_FLASH->SLOCK2 = FLASH_UNLOCK_ALL;
    FLASH_BYPASS();
    M0P_FLASH->SLOCK3 = FLASH_UNLOCK_ALL;

}

/**
 *****************************************************************************
 ** \brief FLASH 读等待周期设置
 **
 ** \param [in]  enWaitCycle  插入FLASH读等待周期数枚举类型
 ** 
 ** \retval Ok                    解锁成功
 ** \retval ErrorInvalidParameter 参数错误                                
 *****************************************************************************/
en_result_t Flash_WaitCycle(en_flash_waitcycle_t enWaitCycle)
{
    en_result_t enResult = Ok;
    
    FLASH_BYPASS();
    M0P_FLASH->CR_f.WAIT = enWaitCycle;
    
    return enResult;
}

/**
 *****************************************************************************
 ** \brief FLASH LOCK 设置
 **
 ** \param [in]  enLock  @ref en_flash_lock_t
 ** \param [in]  u32LockValue 32bits，对应bit=0：加锁，对应Sector不允许擦写；对应bit=1：解锁。
 ** \note  加解锁范围Sector：[enLock*128 + i*4, enLock*128 + i*4+3]
 **        (i表示u32LockValue的bit位置，0~31)
 **        例如：enLock = FlashLock1, u32LockValue = 0x00000002,
 **              则加解锁范围为：[Sector128,Sector131]
 ** \retval Ok                    解锁成功
 ** \retval ErrorInvalidParameter 参数错误                                
 *****************************************************************************/
en_result_t Flash_LockSet(en_flash_lock_t enLock, uint32_t u32LockValue)
{
    FLASH_BYPASS();
    *((&M0P_FLASH->SLOCK0) + enLock) = u32LockValue;
    
    return Ok;
}
//@} // FlashGroup

/*******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/
