/****************************************************************************
 *
 * File Name
 *  util.h
 * Author
 *  wangk
 * Date
 *  2018/01/17
 * Descriptions:
 * UTIL实用工具接口定义
 *
 ****************************************************************************/

#ifndef __UTIL_H__
#define __UTIL_H__

#include <stdint.h>
#include <stdbool.h>

/**---------------------------------------------------------------------------*
**                             Compiler Flag                                  *
**----------------------------------------------------------------------------*/
#ifdef __cplusplus
extern   "C"
{
#endif

/*----------------------------------------------------------------------------*
**                             Mcaro Definitions                              *
**----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*
**                             Data Structures                                *
**----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*
**                             Function Define                                *
**----------------------------------------------------------------------------*/
/*************************************************
* Function: UTIL_IsIPValid
* Description: 判断字符串是否为有效的IP地址
* Author: wangk
* Returns:
* Parameter:
* History:
*************************************************/
bool UTIL_IsIPValid(const char* pcszIP);

/*************************************************
* Function: UTIL_IsDomainNameValid
* Description: 判断字符串是否为有效的域名
* Author: wangk
* Returns:
* Parameter:
* History:
*************************************************/
bool UTIL_IsDomainNameValid(const char* pcszDomainName);

/*************************************************
* Function: UTIL_GetHexStr
* Description: 取得指定数据(HEX格式)
* Author: wangk
* Returns: 返回结果字符串长度
* Parameter:
* History:
*************************************************/
uint32_t UTIL_GetHexStr(const uint8_t* pcu8Data, uint32_t u32DataLen, char* pszBuf, uint32_t u32BufLen);

/*************************************************
* Function: UTIL_StrToU32
* Description: 字符串转32位无符号整数
* Author: wangk
* Returns:
* Parameter:
* History:
*************************************************/
uint32_t UTIL_StrToU32(const char* pcchStr, uint32_t u32StrLen);

/*************************************************
* Function: UTIL_HexCharToU8
* Description: HEX型字符转换成(半字节)HEX值
* Author: wangk
* Returns:
* Parameter:
* History:
*************************************************/
uint8_t UTIL_HexCharToU8(char chHexChar);

/*************************************************
* Function: UTIL_HexStrToU32
* Description: HEX型字符串转32位无符号整数
* Author: wangk
* Returns:
* Parameter:
* History:
*************************************************/
uint32_t UTIL_HexStrToU32(const char* pcchHexStr, uint32_t u32StrLen);

/*************************************************
* Function: UTIL_StrTo1000U32
* Description: "aaa.bbb"形式的小数字符串,转换成1000倍U32整数
* Author: wangk
* Returns:
* Parameter:
* History:
*************************************************/
uint32_t UTIL_StrTo1000U32(const char* pcchStr, uint32_t u32StrLen);

/*************************************************
* Function: UTIL_Pow10N
* Description: 返回10的N次方(N<=9)
* Author: wangk
* Returns:
* Parameter:
* History:
*************************************************/
uint32_t UTIL_Pow10N(uint32_t u32N);

/*************************************************
* Function: UTIL_ToFloatStr
* Description: (s32Val/10^N)结果转化为浮点型字符串
* Author: wangk
* Returns: 返回结果字符串长度
* Parameter:
* History:
*************************************************/
uint32_t UTIL_ToFloatStr(int32_t s32Val, uint32_t u32N,
                         char* szBuf, uint32_t u32BufLen);

/*************************************************
* Function: UTIL_TimeDiff
* Description: 计算时间差(处理计时溢出问题)
* Author: wangk
* Returns:
* Parameter:
* History:
*************************************************/
inline uint32_t UTIL_TimeDiff(uint32_t u32EndTime, uint32_t u32StartTime)
{
    #if 0
    uint32_t u32TimeDiff = u32EndTime - u32StartTime;

    if (u32EndTime < u32StartTime)
    {
        // 发生了计时溢出
        u32TimeDiff = u32EndTime + (UINT_MAX - u32StartTime);
    }

    #else
    /* 按照补码计算,如果溢出也能得到正确结果(a-b=a+(-b) 补码等于原码按位取反加1) */
    uint32_t u32TimeDiff = u32EndTime - u32StartTime;
    #endif
    return u32TimeDiff;
}

/*************************************************
* Function: UTIL_POW2Floor
* Description: 计算小于等于某数的最大2^N值
* Author: wangk
* Returns:
* Parameter:
* History:
*************************************************/
uint32_t UTIL_POW2Floor(uint32_t u32Val);

/*************************************************
* Function: UTIL_WeekDayNum
* Description: 已知年月日计算星期几
* Author: wangk
* Returns: (1~7)
* Parameter: u32Year > 2000
* History:
*************************************************/
uint8_t UTIL_WeekDayNum(uint32_t u32Year, uint8_t u8Month, uint8_t u8Day);

/**--------------------------------------------------------------------------*
**                         Compiler Flag                                     *
**---------------------------------------------------------------------------*/
#ifdef   __cplusplus
}
#endif

#endif // __UTIL_H__
