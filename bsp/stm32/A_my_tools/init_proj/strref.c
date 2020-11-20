/****************************************************************************
 *
 * File Name
 *  strref.c
 * Author
 *  wangk
 * Date
 *  2018/01/16
 * Descriptions:
 * 字符串reference接口实现
 *
 ******************************************************************************/
/*----------------------------------------------------------------------------*
**                             Dependencies                                   *
**----------------------------------------------------------------------------*/
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "common.h"
#include "util.h"
#include "strref.h"

/**---------------------------------------------------------------------------*
 **                            Debugging Flag                                 *
 **---------------------------------------------------------------------------*/

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
**                             Local Vars                                     *
**----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*
**                             Local Function                                 *
**----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*
**                             Public Function                                *
**----------------------------------------------------------------------------*/
/*************************************************
* Function: STRREF_IsEmpty
* Description: 判断StrConstRef_T类型字符串是否为空
* Author: wangk
* Returns: 
* Parameter:
* History:
*************************************************/
bool STRREF_IsEmpty(const StrConstRef_T* pctStrRef)
{
	if (NULL == pctStrRef)
	{
		return true;
	}
	
	if ((NULL == pctStrRef->pcStr) || (pctStrRef->u32Len <= 0))
	{
		return true;
	}
	
	return false;
}

/*************************************************
* Function: STRREF_StrCpy
* Description:  拷贝StrConstRef_T类型的字符串到指定长度缓冲区
*               超过长度会被截断,末尾自动添加'\0'
* Author: wangk
* Returns: 返回实际拷贝的长度(字节)
* Parameter:
* History:
*************************************************/
uint32_t STRREF_StrCpy(char* pszBuf, uint32_t u32BufLen, const StrConstRef_T* pctStrRef)
{
	if ((NULL == pszBuf) || (u32BufLen <= 0))
	{
		return 0;
	}
	if ((NULL == pctStrRef) || (pctStrRef->u32Len <= 0))
	{
		pszBuf[0] = '\0';
		return 0;
	}
	uint32_t u32CopyLen = MIN(u32BufLen - 1, pctStrRef->u32Len);
	memcpy(pszBuf, pctStrRef->pcStr, u32CopyLen);
	pszBuf[u32CopyLen] = '\0';
	return u32CopyLen;
}

/*************************************************
* Function: STRREF_StrCmp
* Description:  比较StrConstRef_T类型的字符串和普通字符串的内容
*               行为类似于strcmp
* Author: wangk
* Returns: 1 0 -1
* Parameter:
* History:
*************************************************/
int32_t STRREF_StrCmp(const char* pcszStr, const StrConstRef_T* pctStrRef)
{
	if ((NULL == pcszStr) && (NULL == pctStrRef))
	{
		return 0;
	}
	if ((NULL == pcszStr) && (NULL != pctStrRef))
	{
		return -1;
	}
	if ((NULL != pcszStr) && (NULL == pctStrRef))
	{
		return 1;
	}
	if (('\0' == pcszStr[0]) && (0 == pctStrRef->u32Len))
	{
		return 0;
	}
	if (('\0' == pcszStr[0]) && (0 != pctStrRef->u32Len))
	{
		return -1;
	}
	if (('\0' != pcszStr[0]) && (0 == pctStrRef->u32Len))
	{
		return 1;
	}
	return strncmp(pcszStr, pctStrRef->pcStr, pctStrRef->u32Len);
}

/*************************************************
* Function: STRREF_ToInt
* Description:  转换StrConstRef_T类型的字符串为有符号整数值(可处理正负号)
* Author: wangk
* Returns: 转换结果
* Parameter:
* History:
*************************************************/
int32_t STRREF_ToInt(const StrConstRef_T* pctStrRef)
{
	if ((NULL == pctStrRef) || (pctStrRef->u32Len <= 0))
	{
		return 0;
	}
	char szBuf[32] = "";
	STRREF_StrCpy(szBuf, sizeof(szBuf), pctStrRef);

	int32_t s32Ret = 0;
	const char* pszStr = szBuf;

	if (('+' == szBuf[0]) || ('-' == szBuf[0]))
	{ // 处理正负号
		++pszStr;
	}

	s32Ret = (int32_t)atoi(pszStr);

	if ('-' == szBuf[0])
	{ // 负数
		s32Ret = -s32Ret;
	}

	return s32Ret;
}

/*************************************************
* Function: STRREF_ToU32
* Description:  转换StrConstRef_T类型的字符串为32位无符号整数值
* Author: wangk
* Returns: 转换结果
* Parameter:
* History:
*************************************************/
uint32_t STRREF_ToU32(const StrConstRef_T* pctStrRef)
{
	if (STRREF_IsEmpty(pctStrRef))
	{
		return 0;
	}

	return UTIL_StrToU32(pctStrRef->pcStr, pctStrRef->u32Len);
}

/*************************************************
* Function: STRREF_HexStrToU32
* Description:  转换StrConstRef_T类型的HEX型字符串为32位无符号整数值
* Author: wangk
* Returns: 转换结果
* Parameter:
* History:
*************************************************/
uint32_t STRREF_HexStrToU32(const StrConstRef_T* pctStrRef)
{
	if (STRREF_IsEmpty(pctStrRef))
	{
		return 0;
	}

	return UTIL_HexStrToU32(pctStrRef->pcStr, pctStrRef->u32Len);
}

/*************************************************
* Function: STRREF_IsInteger
* Description: 判断StrConstRef_T类型的字符串是否为整型数字串形式
* Author: wangk
* Returns: 判断结果
* Parameter:
* History:
*************************************************/
bool STRREF_IsInteger(const StrConstRef_T* pctStrRef)
{
	if ((NULL == pctStrRef) || (pctStrRef->u32Len <= 0))
	{
		return false;
	}
	bool bRet = true;
	uint32_t i = 0;
	if (('+' == pctStrRef->pcStr[0]) || ('-' == pctStrRef->pcStr[0]))
	{
		++i;
	}
	if (i >= pctStrRef->u32Len)
	{
		return false;
	}
	for (; i < pctStrRef->u32Len; ++i)
	{
		if (!isdigit(pctStrRef->pcStr[i]))
		{
			bRet = false;
			break;
		}
	}
	return bRet;
}

/*************************************************
* Function: STRREF_Split
* Description: 将字符串按指定字符分解成子串
* Author: wangk
* Returns: 返回分解结果子串个数
* Parameter:
* History:
*************************************************/
uint32_t STRREF_Split(const StrConstRef_T* pctStrRef, char chSep, StrConstRef_T ptStrRefPartListBuf[], uint32_t u32ListBufLen)
{
	// 参数检查
	if (STRREF_IsEmpty(pctStrRef) 
		|| (NULL == ptStrRefPartListBuf)
		|| (u32ListBufLen <= 0))
	{
		return 0;
	}
	
	uint32_t u32ListLen = 0;
	uint32_t i = 0;

	// 第一个子串起始地址和长度初始化
	ptStrRefPartListBuf[u32ListLen].pcStr = pctStrRef->pcStr;
	ptStrRefPartListBuf[u32ListLen].u32Len = 0;
	for (i = 0; i < pctStrRef->u32Len; ++i)
	{
			if (chSep == pctStrRef->pcStr[i])
			{
					if ((u32ListLen + 1) >= u32ListBufLen)
					{ // 超过最大Split数
							break;
					}
					// 下一个子串起始地址和长度初始化
					++u32ListLen;
					ptStrRefPartListBuf[u32ListLen].pcStr = pctStrRef->pcStr + i + 1;
					ptStrRefPartListBuf[u32ListLen].u32Len = 0;
			}
			else
			{
					++(ptStrRefPartListBuf[u32ListLen].u32Len);
			}
	}
	
	// 计入最后一个子串
	++u32ListLen;

	return u32ListLen;
}

/**---------------------------------------------------------------------------*
 **                         Compiler Flag                                     *
 **---------------------------------------------------------------------------*/
#ifdef   __cplusplus
}
#endif
// End of strref.c
