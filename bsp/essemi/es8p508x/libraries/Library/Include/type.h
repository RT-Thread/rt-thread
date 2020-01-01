/*********************************************************
 *Copyright (C), 2017, Shanghai Eastsoft Microelectronics Co., Ltd.
 *文件名:  type.h
 *作  者:  Liut 
 *版  本:  V1.01
 *日  期:  2017/11/01
 *描  述:  type define
 *备  注:  适用于HRSDK-GDB-8P508x
 本软件仅供学习和演示使用，对用户直接引用代码所带来的风险或后果不承担任何法律责任。
 **********************************************************/
#ifndef __TYPE_H__
#define __TYPE_H__

typedef enum {DISABLE = 0, ENABLE = !DISABLE} TYPE_FUNCEN,FuncState,TYPE_PINTIE,TYPE_PINTMASK,TYPE_BUZZEN;
typedef enum {RESET = 0, SET = !RESET} FlagStatus, ITStatus, PinStatus;
typedef enum {ERROR = 0, SUCCESS = !ERROR} ErrorStatus;


#endif
