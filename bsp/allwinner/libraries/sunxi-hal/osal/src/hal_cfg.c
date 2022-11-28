/*
*********************************************************************************************************
*                                                    MELIS
*                                    the Easy Portable/Player Develop Kits
*                                                Config system
*
*                                    (c) Copyright 2011-2014, Sunny China
*                                             All Rights Reserved
*
* File    : sys_config.c
* By      : Sunny
* Version : v1.0
* Date    : 2011-4-28
* Descript: system config sevice functions.
* Update  : date                auther      ver     notes
*           2011-4-28 20:57:56  Sunny       1.0     Create this file.
*********************************************************************************************************
*/
#include "hal_cfg.h"

int32_t esCFG_GetKeyValue(char *SecName, char *KeyName, int32_t Value[], int32_t Count);
int32_t esCFG_GetGPIOSecKeyCount(char *GPIOSecName);
int32_t esCFG_GetGPIOSecData(char *GPIOSecName, void *pGPIOCfg, int32_t GPIONum);

#if 0
/*
*********************************************************************************************************
*                                       INITIALIZE CONFIG SYSTEM
*
* Description:
*
* Arguments  :
*
* Returns    :
*
* Note       :
*********************************************************************************************************
*/
int32_t Hal_Cfg_Init(uint8_t *CfgVAddr, uint32_t size)
{
    return esCFG_Init(CfgVAddr, size);
}

/*
*********************************************************************************************************
*                                       EXIT CONFIG SYSTEM
*
* Description:
*
* Arguments  :
*
* Returns    :
*
* Note       :
*********************************************************************************************************
*/
int32_t Hal_Cfg_Exit(void)
{
    return esCFG_Exit();
}
#endif

/*
*********************************************************************************************************
*                                       根据主键名称和子键名称获取脚本数据
*
* Description:
*
* Arguments  : main_name    主键名称
*
*              sub_name     子键名称
*
*              value        存放数据的buffer
*
*              count        buffer的最大个数
*
*
* Returns    : 获取数据是否成功
*
* Notes      :
*********************************************************************************************************
*/
int32_t Hal_Cfg_GetKeyValue(char *SecName, char *KeyName, int32_t Value[], int32_t Count)
{
    return  esCFG_GetKeyValue(SecName, KeyName, Value, Count);
}

#if 0
/*
*********************************************************************************************************
*                                       根据主键名称，获取主键下的子键总共个数
*
* Description:
*
* Arguments  : main_name    主键名称
*
*
*
* Returns    : 如果成功，返回子键个数
*              如果失败，返回负数
*
* Notes      :
*********************************************************************************************************
*/
int32_t Hal_Cfg_GetSecKeyCount(char *SecName)
{
    return  esCFG_GetSecKeyCount(SecName);
}

/*
*********************************************************************************************************
*                                       获取总共主键的个数
*
* Description:
*
* Arguments  :
*
*
*
* Returns    : 如果成功，返回主键个数
*              如果失败，返回负数
*
* Notes      :
*********************************************************************************************************
*/
int32_t Hal_Cfg_GetSecCount(void)
{
    return  esCFG_GetSecCount();
}
#endif
/*
*********************************************************************************************************
*                                       根据主键名称，获取主键下的GPIO类型总共个数
*
* Description:
*
* Arguments  : main_name    主键名称
*
*
*
* Returns    : 如果成功，返回主键个数
*              如果失败，返回负数
*
* Notes      :
*********************************************************************************************************
*/
int32_t Hal_Cfg_GetGPIOSecKeyCount(char *GPIOSecName)
{
    return  esCFG_GetGPIOSecKeyCount(GPIOSecName);
}

/*
*********************************************************************************************************
*                                       根据主键名称，获取主键下的GPIO类型的所有数据
*
* Description:
*
* Arguments  : main_name    主键名称
*
*              gpio_cfg     存放GPIO数据信息的buffer
*
*              gpio_count   GPIO的总共个数
*
*
* Returns    : 如果成功，返回成功标志
*              如果失败，返回负数
*
* Notes      :
*********************************************************************************************************
*/
int32_t Hal_Cfg_GetGPIOSecData(char *GPIOSecName, void *pGPIOCfg, int32_t GPIONum)
{
    return  esCFG_GetGPIOSecData(GPIOSecName, pGPIOCfg, GPIONum);
}
