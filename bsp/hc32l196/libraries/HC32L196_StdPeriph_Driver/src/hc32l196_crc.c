/******************************************************************************
*Copyright(C)2017, Huada Semiconductor Co.,Ltd All rights reserved.
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

/** \file crc.c
 **
 ** Common API of crc.
 ** @link crcGroup Some description @endlink
 **
 **   - 2017-05-16
 **
 ******************************************************************************/

/*******************************************************************************
 * Include files
 ******************************************************************************/
#include "hc32l196_crc.h"
/**
 *******************************************************************************
 ** \addtogroup CrcGroup
 ******************************************************************************/
//@{

/*******************************************************************************
 * Local pre-processor symbols/macros ('#define')
 ******************************************************************************/

/*******************************************************************************
 * Global variable definitions (declared in header file with 'extern')
 ******************************************************************************/

/*******************************************************************************
 * Local type definitions ('typedef')
 ******************************************************************************/

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
 ** \brief CRC16 编码(字节填充方式)
 **
 ** 该函数主要用于生成CRC16编码.
 **
 ** \param [in]  pu8Data          待编码数据指针（字节方式输入）
 ** \param [in]  u32Len           待编码数据长度（字节数）
 ** 
 ** \retval CRC16                 CRC16编码值.                                
 *****************************************************************************/
uint16_t CRC16_Get8(uint8_t* pu8Data, uint32_t u32Len)
{
    uint32_t u32Index = 0;
    
    M0P_CRC->CR_f.CR = 0;
    M0P_CRC->RESULT = 0xFFFF;
    for(u32Index = 0;u32Index<u32Len;u32Index++)
    {
            *((volatile uint8_t*)(&(M0P_CRC->DATA)))  = pu8Data[u32Index];
    }

    return (M0P_CRC->RESULT_f.RESULT);
}

/**
 *****************************************************************************
 ** \brief CRC16 编码(半字填充方式)
 **
 ** 该函数主要用于生成CRC16编码.
 **
 ** \param [in]  pu16Data          待编码数据指针（半字方式输入）
 ** \param [in]  u32Len           待编码数据长度（半字数）
 ** 
 ** \retval CRC16                 CRC16编码值.                                
 *****************************************************************************/
uint16_t CRC16_Get16(uint16_t* pu16Data, uint32_t u32Len)
{
    uint32_t u32Index = 0;
    
    M0P_CRC->CR_f.CR = 0;
    M0P_CRC->RESULT_f.RESULT = 0xFFFF;
    for (u32Index=0; u32Index<u32Len; u32Index++)
    {
        *((volatile uint16_t*)(&(M0P_CRC->DATA))) = pu16Data[u32Index];
    }
  
    return (M0P_CRC->RESULT_f.RESULT);
}

/**
 *****************************************************************************
 ** \brief CRC16 编码(字填充方式)
 **
 ** 该函数主要用于生成CRC16编码.
 **
 ** \param [in]  pu32Data          待编码数据指针（字方式输入）
 ** \param [in]  u32Len            待编码数据长度（字数）
 ** 
 ** \retval CRC16                  CRC16编码值.                                
 *****************************************************************************/
uint16_t CRC16_Get32(uint32_t* pu32Data, uint32_t u32Len)
{
    uint32_t u32Index = 0;
    
    M0P_CRC->CR_f.CR = 0;
    M0P_CRC->RESULT_f.RESULT = 0xFFFF;
    for (u32Index=0; u32Index<u32Len; u32Index++)
    {
        M0P_CRC->DATA_f.DATA = pu32Data[u32Index];
    }
  
    return (M0P_CRC->RESULT_f.RESULT);
}

/**
 *****************************************************************************
 ** \brief CRC16 校验(字节填充方式)
 **
 ** 该函数主要用于对数据及CRC16值进行校验.
 **
 ** \param [in]  pu8Data          待校验数据指针（字节方式输入）
 ** \param [in]  u32Len           待校验数据长度（字节数）
 ** \param [in]  u16CRC           待校验CRC16值
 ** 
 ** \retval Ok                    CRC校验正确
 ** \retval Error                 CRC校验错误                                
 *****************************************************************************/
en_result_t CRC16_Check8(uint8_t* pu8Data, uint32_t u32Len, uint16_t u16CRC)
{
    en_result_t enResult = Ok;
    uint32_t    u32Index = 0;
    
    M0P_CRC->CR_f.CR = 0;    
    M0P_CRC->RESULT_f.RESULT = 0xFFFF;
    for (u32Index=0; u32Index<u32Len; u32Index++)
    {
        *((volatile uint8_t*)(&(M0P_CRC->DATA))) = pu8Data[u32Index];
    }
    
     *((volatile uint8_t*)(&(M0P_CRC->DATA))) = (uint8_t)((((uint32_t)u16CRC)>>0)&0xFF);
     *((volatile uint8_t*)(&(M0P_CRC->DATA))) = (uint8_t)(((uint32_t)u16CRC>>8)&0xFF);
    
    enResult = M0P_CRC->CR_f.FLAG ? Ok : Error;
    
    return (enResult); 
}

/**
 *****************************************************************************
 ** \brief CRC16 校验(半字填充方式)
 **
 ** 该函数主要用于对数据及CRC16值进行校验.
 **
 ** \param [in]  pu16Data         待校验数据指针（半字方式输入）
 ** \param [in]  u32Len           待校验数据长度（半字数）
 ** \param [in]  u16CRC           待校验CRC16值
 ** 
 ** \retval Ok                    CRC校验正确
 ** \retval Error                 CRC校验错误                                
 *****************************************************************************/
en_result_t CRC16_Check16(uint16_t* pu16Data, uint32_t u32Len, uint16_t u16CRC)
{
    en_result_t enResult = Ok;
    uint32_t    u32Index = 0;

    M0P_CRC->CR_f.CR = 0;    
    M0P_CRC->RESULT_f.RESULT = 0xFFFF;
    for (u32Index=0; u32Index<u32Len; u32Index++)
    {
        *((volatile uint16_t*)(&(M0P_CRC->DATA))) = pu16Data[u32Index];
    }
    
     *((volatile uint16_t*)(&(M0P_CRC->DATA))) = u16CRC;
    
    enResult = M0P_CRC->CR_f.FLAG ? Ok : Error;
    
    return (enResult); 
}

/**
 *****************************************************************************
 ** \brief CRC16 校验(字填充方式)
 **
 ** 该函数主要用于对数据及CRC16值进行校验.
 **
 ** \param [in]  pu32Data         待校验数据指针（字方式输入）
 ** \param [in]  u32Len           待校验数据长度（字数）
 ** \param [in]  u16CRC           待校验CRC16值
 ** 
 ** \retval Ok                    CRC校验正确
 ** \retval Error                 CRC校验错误                                
 *****************************************************************************/
en_result_t CRC16_Check32(uint32_t* pu32Data, uint32_t u32Len, uint16_t u16CRC)
{
    en_result_t enResult = Ok;
    uint32_t    u32Index = 0;

    M0P_CRC->CR_f.CR = 0;    
    M0P_CRC->RESULT_f.RESULT = 0xFFFFFFFFu;
    for (u32Index=0; u32Index<u32Len; u32Index++)
    {
        *((volatile uint32_t*)(&(M0P_CRC->DATA))) = pu32Data[u32Index];
    }
    
     *((volatile uint16_t*)(&(M0P_CRC->DATA))) = ((uint16_t)u16CRC);
    
    enResult = M0P_CRC->CR_f.FLAG ? Ok : Error;
    
    return (enResult);
}

/**
 *****************************************************************************
 ** \brief CRC16 编码(字节填充方式)
 **
 ** 该函数主要用于生成CRC16编码.
 **
 ** \param [in]  pu8Data          待编码数据指针（字节方式输入）
 ** \param [in]  u32Len           待编码数据长度（字节数）
 ** 
 ** \retval CRC16                 CRC16编码值.                                
 *****************************************************************************/
uint32_t CRC32_Get8(uint8_t* pu8Data, uint32_t u32Len)
{
    uint32_t u32Index = 0;
    
    M0P_CRC->CR_f.CR = 1;
    M0P_CRC->RESULT = 0xFFFFFFFFu;
    for(u32Index = 0;u32Index<u32Len;u32Index++)
    {
            *((volatile uint8_t*)(&(M0P_CRC->DATA)))  = pu8Data[u32Index];
    }

    return (M0P_CRC->RESULT_f.RESULT);
}

/**
 *****************************************************************************
 ** \brief CRC16 编码(半字填充方式)
 **
 ** 该函数主要用于生成CRC16编码.
 **
 ** \param [in]  pu16Data          待编码数据指针（半字方式输入）
 ** \param [in]  u32Len           待编码数据长度（半字数）
 ** 
 ** \retval CRC16                 CRC16编码值.                                
 *****************************************************************************/
uint32_t CRC32_Get16(uint16_t* pu16Data, uint32_t u32Len)
{
    uint32_t u32Index = 0;
    
    M0P_CRC->CR_f.CR = 1;
    M0P_CRC->RESULT_f.RESULT = 0xFFFFFFFFu;
    for (u32Index=0; u32Index<u32Len; u32Index++)
    {
        *((volatile uint16_t*)(&(M0P_CRC->DATA))) = pu16Data[u32Index];
    }
  
    return (M0P_CRC->RESULT_f.RESULT);
}

/**
 *****************************************************************************
 ** \brief CRC16 编码(字填充方式)
 **
 ** 该函数主要用于生成CRC16编码.
 **
 ** \param [in]  pu32Data          待编码数据指针（字方式输入）
 ** \param [in]  u32Len            待编码数据长度（字数）
 ** 
 ** \retval CRC16                  CRC16编码值.                                
 *****************************************************************************/
uint32_t CRC32_Get32(uint32_t* pu32Data, uint32_t u32Len)
{
    uint32_t u32Index = 0;
    
    M0P_CRC->CR_f.CR = 1;    
    M0P_CRC->RESULT_f.RESULT = 0xFFFFFFFFu;
    for (u32Index=0; u32Index<u32Len; u32Index++)
    {
        M0P_CRC->DATA_f.DATA = pu32Data[u32Index];
    }
  
    return (M0P_CRC->RESULT_f.RESULT);
}

/**
 *****************************************************************************
 ** \brief CRC16 校验(字节填充方式)
 **
 ** 该函数主要用于对数据及CRC16值进行校验.
 **
 ** \param [in]  pu8Data          待校验数据指针（字节方式输入）
 ** \param [in]  u32Len           待校验数据长度（字节数）
 ** \param [in]  u16CRC           待校验CRC16值
 ** 
 ** \retval Ok                    CRC校验正确
 ** \retval Error                 CRC校验错误                                
 *****************************************************************************/
en_result_t CRC32_Check8(uint8_t* pu8Data, uint32_t u32Len, uint32_t u32CRC)
{
    en_result_t enResult = Ok;
    uint32_t    u32Index = 0;
    
    M0P_CRC->CR_f.CR = 1;     
    M0P_CRC->RESULT_f.RESULT = 0xFFFFFFFFu;
    for (u32Index=0; u32Index<u32Len; u32Index++)
    {
        *((volatile uint8_t*)(&(M0P_CRC->DATA))) = pu8Data[u32Index];
    }
    
     *((volatile uint8_t*)(&(M0P_CRC->DATA))) = (uint8_t)((u32CRC>>0)&0xFF);
     *((volatile uint8_t*)(&(M0P_CRC->DATA))) = (uint8_t)((u32CRC>>8)&0xFF);
     *((volatile uint8_t*)(&(M0P_CRC->DATA))) = (uint8_t)((u32CRC>>16)&0xFF);
     *((volatile uint8_t*)(&(M0P_CRC->DATA))) = (uint8_t)((u32CRC>>24)&0xFF);
        
    enResult = M0P_CRC->CR_f.FLAG ? Ok : Error;
    
    return (enResult); 
}

/**
 *****************************************************************************
 ** \brief CRC16 校验(半字填充方式)
 **
 ** 该函数主要用于对数据及CRC16值进行校验.
 **
 ** \param [in]  pu16Data         待校验数据指针（半字方式输入）
 ** \param [in]  u32Len           待校验数据长度（半字数）
 ** \param [in]  u16CRC           待校验CRC16值
 ** 
 ** \retval Ok                    CRC校验正确
 ** \retval Error                 CRC校验错误                                
 *****************************************************************************/
en_result_t CRC32_Check16(uint16_t* pu16Data, uint32_t u32Len, uint32_t u32CRC)
{
    en_result_t enResult = Ok;
    uint32_t    u32Index = 0;
    
    M0P_CRC->CR_f.CR = 1;     
    M0P_CRC->RESULT_f.RESULT = 0xFFFFFFFFu;
    for (u32Index=0; u32Index<u32Len; u32Index++)
    {
        *((volatile uint16_t*)(&(M0P_CRC->DATA))) = pu16Data[u32Index];
    }
    
     *((volatile uint16_t*)(&(M0P_CRC->DATA))) = (uint16_t)((u32CRC>>0)&0xFFFF);
     *((volatile uint16_t*)(&(M0P_CRC->DATA))) = (uint16_t)((u32CRC>>16)&0xFFFF);

    
    enResult = M0P_CRC->CR_f.FLAG ? Ok : Error;
    
    return (enResult); 
}

/**
 *****************************************************************************
 ** \brief CRC16 校验(字填充方式)
 **
 ** 该函数主要用于对数据及CRC16值进行校验.
 **
 ** \param [in]  pu32Data         待校验数据指针（字方式输入）
 ** \param [in]  u32Len           待校验数据长度（字数）
 ** \param [in]  u16CRC           待校验CRC16值
 ** 
 ** \retval Ok                    CRC校验正确
 ** \retval Error                 CRC校验错误                                
 *****************************************************************************/
en_result_t CRC32_Check32(uint32_t* pu32Data, uint32_t u32Len, uint32_t u32CRC)
{
    en_result_t enResult = Ok;
    uint32_t    u32Index = 0;
    
    M0P_CRC->CR_f.CR = 1;     
    M0P_CRC->RESULT_f.RESULT = 0xFFFFFFFFu;
    for (u32Index=0; u32Index<u32Len; u32Index++)
    {
        *((volatile uint32_t*)(&(M0P_CRC->DATA))) = pu32Data[u32Index];
    }
    
     *((volatile uint32_t*)(&(M0P_CRC->DATA))) = u32CRC;
    
    enResult = M0P_CRC->CR_f.FLAG ? Ok : Error;
    
    return (enResult);
}
//@} // CrcGroup

/*******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/
