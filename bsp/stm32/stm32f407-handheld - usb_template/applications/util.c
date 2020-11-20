/****************************************************************************
 *
 * File Name
 *  util.c
 * Author
 *  wangk
 * Date
 *  2018/01/17
 * Descriptions:
 * UTIL实用工具接口实现
 *
 ******************************************************************************/
/*----------------------------------------------------------------------------*
**                             Dependencies                                   *
**----------------------------------------------------------------------------*/
#include <stdint.h>
#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <limits.h> // UINT_MAX
#include <rtthread.h>

#include "util.h"
#include "strref.h"
#include "common.h"

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
* Function: UTIL_IsIPValid
* Description: 判断字符串是否为有效的IP地址
* Author: wangk
* Returns:
* Parameter:
* History:
*************************************************/
bool UTIL_IsIPValid(const char* pcszIP)
{
	bool bRet = false;
#if 0
	int n[4] = {0};
	char c[4] = {0};

	// 参数检查
	if (NULL == pcszIP || '\0' == pcszIP[0])
	{
		bRet = false;
		goto _END;
	}

	if (sscanf(pcszIP, "%d%c%d%c%d%c%d%c",
				 &n[0], &c[0], &n[1], &c[1],
				 &n[2], &c[2], &n[3], &c[3]) == 7)
	{
		int i = 0;
		for(i = 0; i < 3; ++i)
		{
			if (c[i] != '.')
			{
				bRet = false;
				goto _END;
			}
		}
		for(i = 0; i < 4; ++i)
		{
			if ((n[i] > 255) || (n[i] < 0))
			{
				bRet = false;
				goto _END;
			}
		}
		bRet = true;
	}
#else
	/* 分解为4个子串 */
	StrConstRef_T tSdyStrList[4] = {{0, NULL},};
	uint32_t i = 0;
	uint32_t u32ListLen = 0;
	
	// 参数检查
	if (NULL == pcszIP || '\0' == pcszIP[0])
	{
		bRet = false;
		goto _END;
	}
	
	// 第一个子串起始地址和长度初始化
	tSdyStrList[u32ListLen].pcStr = pcszIP;
	tSdyStrList[u32ListLen].u32Len = 0;
	while ('\0' != pcszIP[i])
	{
		if ('.' == pcszIP[i])
		{
			++u32ListLen;
			if (u32ListLen >= ARRAY_SIZE(tSdyStrList))
			{ // 子串超过4个
				bRet = false;
				goto _END;
			}
			// 下一个子串起始地址和长度初始化
			tSdyStrList[u32ListLen].pcStr = pcszIP + i + 1;
			tSdyStrList[u32ListLen].u32Len = 0;
		}
		else
		{
			++(tSdyStrList[u32ListLen].u32Len);
		}
		i++;
	}
	if (u32ListLen < ARRAY_SIZE(tSdyStrList))
	{ // 最后一个子串
		++u32ListLen;
	}

	// 子串不足4个
	if (ARRAY_SIZE(tSdyStrList) != u32ListLen)
	{
		bRet = false;
		goto _END;
	}

	// 检查每个子串有效性
	for (i = 0; i < u32ListLen; ++i)
	{
		const StrConstRef_T* ptSdyStr = &(tSdyStrList[i]);
		if ((ptSdyStr->u32Len <= 0) || (ptSdyStr->u32Len > 3))
		{ // 子串长度无效
			bRet = false;
			goto _END;
		}
		uint32_t j = 0;
		for (j = 0; j < ptSdyStr->u32Len; ++j)
		{
			if (!isdigit(ptSdyStr->pcStr[j]))
			{ // 包含非数字字符
				bRet = false;
				goto _END;
			}
		}
		int32_t s32Tmp = atoi(ptSdyStr->pcStr);
		if ((s32Tmp > 255) || (s32Tmp < 0))
		{ // 超范围
			bRet = false;
			goto _END;
		}
	}
	bRet = true;
#endif

_END:
	return bRet;
}

/*************************************************
* Function: UTIL_IsDomainNameValid
* Description: 判断字符串是否为有效的域名
* Author: wangk
* Returns:
* Parameter:
* History:
*************************************************/
bool UTIL_IsDomainNameValid(const char* pcszDomainName)
{
	bool bRet = true;

	/*
			域名中只能包含以下字符：
	　　26个字母(a~z)不区分大小写。
	　　0、1、2、3、4、5、6、7、8、9。
	　　"-" 中横线。
	*/
	uint32_t i = 0;
	while ('\0' != pcszDomainName[i])
	{
		if (((pcszDomainName[i] >= 'A') && (pcszDomainName[i] <= 'Z'))
			|| ((pcszDomainName[i] >= 'a') && (pcszDomainName[i] <= 'z'))
			|| ((pcszDomainName[i] >= '0') && (pcszDomainName[i] <= '9'))
			|| ('-' == pcszDomainName[i]) || ('.' == pcszDomainName[i]))
		{ // 合法字符
			i++;
		}
		else
		{ // 非法字符
			bRet = false;
			break;
		}
	}

	return bRet;
}

/*************************************************
* Function: UTIL_GetHexStr
* Description: 取得指定数据(HEX格式)
* Author: wangk
* Returns: 返回结果字符串长度
* Parameter:
* History:
*************************************************/
uint32_t UTIL_GetHexStr(const uint8_t* pcu8Data, uint32_t u32DataLen, char* pszBuf, uint32_t u32BufLen)
{
	if ((NULL == pszBuf)
		|| (u32BufLen <=0 ))
	{ // 缓冲区无效
		return 0;
	}
	
	/* 清空缓冲区为"" */
	pszBuf[0] = '\0';
	
	if ((NULL == pcu8Data)
		|| (u32DataLen <=0 ))
	{ // 数据为空
		return 0;
	}

	/* 最大可转换长度为: ((u32BufLen - 1) / 2) */
	uint32_t u32TransLen = MIN(u32DataLen, ((u32BufLen - 1) / 2));
	uint32_t i = 0;
	uint32_t j = 0;
	for (i = 0; i < u32TransLen; ++i)
	{
		uint8_t u8Byte = pcu8Data[i];
		uint8_t u8HHalf = (u8Byte >> 4) & 0x0F;
		uint8_t u8LHalf = u8Byte & 0x0F;
		pszBuf[j++] = TO_HEX_CHAR(u8HHalf);
		pszBuf[j++] = TO_HEX_CHAR(u8LHalf);
	}
	pszBuf[j] = '\0';

	/* 返回结果串长度 */
	return j;
}

/*************************************************
* Function: UTIL_StrToU32
* Description: 字符串转32位无符号整数
* Author: wangk
* Returns:
* Parameter:
* History:
*************************************************/
uint32_t UTIL_StrToU32(const char* pcchStr, uint32_t u32StrLen)
{
	if ((NULL == pcchStr) 
		|| (u32StrLen <= 0))
	{
		return 0;
	}
	
	/* 去掉高位0 */
	uint32_t i = 0;
	for (i = 0; i < u32StrLen; ++i)
	{
		if ('0' != pcchStr[i])
		{
			break;
		}
	}
	pcchStr += i;
	u32StrLen -= i;
	
	if (u32StrLen <= 0)
	{ // 全0
		return 0;
	}
	
	if (u32StrLen > 10)
	{ // 超过U32表示范围
		return 0;
	}
	
	uint32_t u32Val = 0;
	for (i = 0; i < u32StrLen; ++i)
	{
		char cVal = pcchStr[i];
		if (!isdigit(cVal))
		{
			break;
		}
		u32Val = u32Val * 10 + (cVal - '0');
	}

	return u32Val;
}

/*************************************************
* Function: UTIL_HexCharToU8
* Description: HEX型字符转换成(半字节)HEX值
* Author: wangk
* Returns:
* Parameter:
* History:
*************************************************/
uint8_t UTIL_HexCharToU8(char chHexChar)
{
	uint8_t u8Val = 0;
	
	if ((chHexChar >= '0') && (chHexChar <= '9'))
	{
		u8Val = chHexChar - '0';
	}
	else if ((chHexChar >= 'a') && (chHexChar <= 'f'))
	{
		u8Val = 0x0A + (chHexChar - 'a');
	}
	else if ((chHexChar >= 'A') && (chHexChar <= 'F'))
	{
		u8Val = 0x0A + (chHexChar - 'A');
	} // else 非法字符
	
	return u8Val;
}

/*************************************************
* Function: UTIL_HexStrToU32
* Description: HEX型字符串转32位无符号整数
* Author: wangk
* Returns:
* Parameter:
* History:
*************************************************/
uint32_t UTIL_HexStrToU32(const char* pcchHexStr, uint32_t u32StrLen)
{
	if ((NULL == pcchHexStr)
		|| (u32StrLen <= 0))
	{
		return 0;
	}
	
	/* 去掉高位0 */
	uint32_t i = 0;
	for (i = 0; i < u32StrLen; ++i)
	{
		if ('0' != pcchHexStr[i])
		{
			break;
		}
	}
	pcchHexStr += i;
	u32StrLen -= i;
	
	if (u32StrLen <= 0)
	{ // 全0
		return 0;
	}
	
	if (u32StrLen > 8)
	{ // 超过U32表示范围
		return 0;
	}
	
	uint32_t u32Val = 0;
	for (i = 0; i < u32StrLen; ++i)
	{
		char chHexChar = pcchHexStr[i];
		if (!IS_HEX_CHAR(chHexChar))
		{ // 包含非法字符
			break;
		}
		u32Val = u32Val * 16 + UTIL_HexCharToU8(chHexChar);
	}

	return u32Val;
}

/*************************************************
* Function: UTIL_StrTo1000U32
* Description: "aaa.bbb"形式的小数字符串,转换成1000倍U32整数
* Author: wangk
* Returns:
* Parameter:
* History:
*************************************************/
uint32_t UTIL_StrTo1000U32(const char* pcchStr, uint32_t u32StrLen)
{
	if ((NULL == pcchStr) 
		|| (u32StrLen <= 0))
	{
		return 0;
	}
	
	// 跳过前面的0
	while (('0' == *pcchStr) 
		&& (u32StrLen > 0))
	{
		++pcchStr;
		--u32StrLen;
	}
	if (u32StrLen <= 0)
	{
		return 0;
	}

	// 找到小数点的位置
	uint32_t i = 0;
	while ((i < u32StrLen) && ('.' != pcchStr[i]))
	{
		++i;
	}

	// 整数位数超范围
	if (i > 10)
	{ // u32最多表示10位十进制数
		return 0;
	}
	
	uint32_t u32Interger = UTIL_StrToU32(pcchStr, i); // 整数部分值
	uint32_t u321000U32 = 0; // 1000倍
	if (i < u32StrLen)
	{ // 有小数部分
		uint32_t u32DecimalLen = u32StrLen - i - 1; // 小数部分长度
		// u32最多表示10位十进制数, 整数部分已占用i位, 小数部分最多保留(10-i)位
		if (u32DecimalLen > (10 - i))
		{ // 超过u32表示范围, 忽略后后续小数位数
			u32DecimalLen = (10 - i);
		}
		uint32_t u32KmDecimal = UTIL_StrToU32(pcchStr + i + 1, u32DecimalLen); // 小数部分值
		uint32_t u32Unit = UTIL_Pow10N(u32DecimalLen); // 单位因数
		u321000U32 = (u32Interger * 1000 + (u32KmDecimal * 1000) / u32Unit); // 放大1000倍
	}
	else
	{ // 没有小数部分
		u321000U32 = (u32Interger * 1000); // 放大1000倍
	}

	return u321000U32;
}

/*************************************************
* Function: UTIL_Pow10N
* Description: 返回10的N次方(N<=9)
* Author: wangk
* Returns:
* Parameter:
* History:
*************************************************/
uint32_t UTIL_Pow10N(uint32_t u32N)
{
	uint32_t u32Val = 1;
	uint32_t i = 0;
	for (i = 0; i < u32N; ++i)
	{
		u32Val *= 10;
	}

	return u32Val;
}

/*************************************************
* Function: UTIL_ToFloatStr
* Description: (s32Val/10^N)结果转化为浮点型字符串
* Author: wangk
* Returns: 返回结果字符串长度
* Parameter:
* History:
*************************************************/
uint32_t UTIL_ToFloatStr(int32_t s32Val, uint32_t u32N, 
	char* pszBuf, uint32_t u32BufLen)
{
	int iStrLen = rt_snprintf(pszBuf, u32BufLen, "%d", s32Val);
	if ((iStrLen <= 0) 
		|| (iStrLen >= u32BufLen))
	{ // Buffer空间不足
		pszBuf[0] = '\0';
		return 0;
	}
	
	char* pszU32Val = pszBuf;
	uint32_t u32U32ValLen = (uint32_t)iStrLen;
	if ('-' == pszBuf[0])
	{ // 负数
		pszU32Val += 1;
		u32U32ValLen -= 1;
	}

	uint32_t u32ResLen = (uint32_t)iStrLen;
	if (u32U32ValLen <= u32N)
	{
		// 填0长度
		uint32_t u32Fill0Len = (u32N - u32U32ValLen);
		u32ResLen += STR_LEN("0.") + u32Fill0Len;
		if (u32ResLen >= u32BufLen)
		{ // Buffer空间不足
			pszBuf[0] = '\0';
			return 0;
		}
		// 小数部分后移
		memmove(pszU32Val + u32Fill0Len + STR_LEN("0."), pszU32Val, u32U32ValLen);
		pszU32Val[0] = '0';
		pszU32Val[1] = '.';
		if (u32Fill0Len > 0)
		{
			// 填充0 
			memset(pszU32Val + STR_LEN("0."), (int)'0', u32Fill0Len);
		}
	}
	else
	{
		// 整数部分
		uint32_t u32IntPartLen = u32U32ValLen - u32N; // 整数部分长度
		if (u32N > 0)
		{
			u32ResLen += STR_LEN(".");
			if (u32ResLen >= u32BufLen)
			{ // Buffer空间不足
				pszBuf[0] = '\0';
				return 0;
			}
			// 小数部分后移一个位置
			memmove(pszU32Val + u32IntPartLen + 1, pszU32Val + u32IntPartLen, u32N);
			// 小数点
			pszU32Val[u32IntPartLen] = '.';
		}
	}
	pszBuf[u32ResLen] = '\0';
	return u32ResLen;
}

/*************************************************
* Function: UTIL_POW2Floor
* Description: 计算小于等于某数的最大2^N值
* Author: wangk
* Returns: 
* Parameter:
* History:
*************************************************/
uint32_t UTIL_POW2Floor(uint32_t u32Val)
{
	uint32_t u32POW2Floor = 0x00000001;
	while (u32Val >>= 1)
	{
		u32POW2Floor <<= 1;
	}
	return u32POW2Floor;
}

/*************************************************
* Function: UTIL_WeekDayNum
* Description: 已知年月日计算星期几
* Author: wangk
* Returns: (1~7)
* Parameter: u32Year > 2000
* History:
*************************************************/
uint8_t UTIL_WeekDayNum(uint32_t u32Year, uint8_t u8Month, uint8_t u8Day)
{
  uint32_t u32WeekDay = 0;
  
  if(u8Month < 3U)
  {
    /*D = { [(23 x month) / 9] + day + 4 + year + [(year - 1) / 4] - [(year - 1) / 100] + [(year - 1) / 400] } mod 7*/
    u32WeekDay = (((23U * u8Month) / 9U) + u8Day + 4U + u32Year + ((u32Year - 1U) / 4U) - ((u32Year - 1U) / 100U) + ((u32Year - 1U) / 400U)) % 7U;
  }
  else
  {
    /*D = { [(23 x month) / 9] + day + 4 + year + [year / 4] - [year / 100] + [year / 400] - 2 } mod 7*/
    u32WeekDay = (((23U * u8Month) / 9U) + u8Day + 4U + u32Year + (u32Year / 4U) - (u32Year / 100U) + (u32Year / 400U) - 2U ) % 7U;
  }

	if (0U == u32WeekDay)
	{
		u32WeekDay = 7U;
	}
	
  return (uint8_t)u32WeekDay;
}

/**---------------------------------------------------------------------------*
 **                         Compiler Flag                                     *
 **---------------------------------------------------------------------------*/
#ifdef   __cplusplus
}
#endif
// End of util.c
