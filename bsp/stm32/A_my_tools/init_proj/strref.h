/****************************************************************************
 *
 * File Name
 *  strref.h
 * Author
 *  wangk
 * Date
 *  2018/01/16
 * Descriptions:
 * 字符串reference接口定义
 *
 ****************************************************************************/

#ifndef __STRREF_H__
#define __STRREF_H__

#include <stdbool.h>
#include <stdint.h>

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
// Const字符串reference结构体
typedef struct
{
    uint32_t u32Len;
    const char* pcStr;
} StrConstRef_T;

/*----------------------------------------------------------------------------*
**                             Function Define                                *
**----------------------------------------------------------------------------*/
/*************************************************
* Function: STRREF_IsEmpty
* Description: 判断StrConstRef_T类型字符串是否为空
* Author: wangk
* Returns: 
* Parameter:
* History:
*************************************************/
bool STRREF_IsEmpty(const StrConstRef_T* pctStrRef);

/*************************************************
* Function: STRREF_StrCpy
* Description:  拷贝StrConstRef_T类型的字符串到指定长度缓冲区
*               超过长度会被截断,末尾自动添加'\0'
* Author: wangk
* Returns: 返回实际拷贝的长度(字节)
* Parameter:
* History:
*************************************************/
uint32_t STRREF_StrCpy(char* pszBuf, uint32_t u32BufLen, const StrConstRef_T* pctStrRef);

/*************************************************
* Function: STRREF_StrCmp
* Description:  比较StrConstRef_T类型的字符串和普通字符串的内容
*               行为类似于strcmp
* Author: wangk
* Returns: 1 0 -1
* Parameter:
* History:
*************************************************/
int32_t STRREF_StrCmp(const char* pcszStr, const StrConstRef_T* pctStrRef);

/*************************************************
* Function: STRREF_ToInt
* Description:  转换StrConstRef_T类型的字符串为有符号整数值(可处理正负号)
* Author: wangk
* Returns: 转换结果
* Parameter:
* History:
*************************************************/
int32_t STRREF_ToInt(const StrConstRef_T* pctStrRef);

/*************************************************
* Function: STRREF_ToU32
* Description:  转换StrConstRef_T类型的字符串为32位无符号整数值
* Author: wangk
* Returns: 转换结果
* Parameter:
* History:
*************************************************/
uint32_t STRREF_ToU32(const StrConstRef_T* pctStrRef);

/*************************************************
* Function: STRREF_HexStrToU32
* Description:  转换StrConstRef_T类型的HEX型字符串为32位无符号整数值
* Author: wangk
* Returns: 转换结果
* Parameter:
* History:
*************************************************/
uint32_t STRREF_HexStrToU32(const StrConstRef_T* pctStrRef);

/*************************************************
* Function: STRREF_IsInteger
* Description: 判断StrConstRef_T类型的字符串是否为整型数字串形式
* Author: wangk
* Returns: 判断结果
* Parameter:
* History:
*************************************************/
bool STRREF_IsInteger(const StrConstRef_T* pctStrRef);

/*************************************************
* Function: STRREF_Split
* Description: 将字符串按指定字符分解成子串
* Author: wangk
* Returns: 返回分解结果子串个数
* Parameter:
* History:
*************************************************/
uint32_t STRREF_Split(const StrConstRef_T* pctStrRef, char chSep, StrConstRef_T ptStrRefPartListBuf[], uint32_t u32ListBufLen);

/**--------------------------------------------------------------------------*
**                         Compiler Flag                                     *
**---------------------------------------------------------------------------*/
#ifdef   __cplusplus
}
#endif

#endif // __STRREF_H__
