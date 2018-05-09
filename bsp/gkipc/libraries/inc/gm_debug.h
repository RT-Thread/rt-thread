/*!
*******************************************************************************
**
** \file      gm_debug.h
**
** \brief     Debug support module.
**
**            This file implements the public functions for a terminal utility
**            (basic functions only). You can use them for printf/scanf style
**            debug functions on a terminal or via OSD.
**
**            Note that if you want to use the almighty printf/scanf you have to
**            include the C-Lib (consumes about 25kB memory). If not
**            you can compile the module with DEBUG_NO_CLIB, then only
**            the simple functions are available.
**
**            Copyright:   2012 - 2013 (C) GoKe Microelectronics ShangHai Branch
**
** \attention THIS SAMPLE CODE IS PROVIDED AS IS. GOKE MICROELECTRONICS
**            ACCEPTS NO RESPONSIBILITY OR LIABILITY FOR ANY ERRORS OR
**            OMMISSIONS.
**
** \version
**
******************************************************************************/
#ifndef _GM_DEBUG_H_
#define _GM_DEBUG_H_

#include <gtypes.h>
#include <gmodids.h>

/*---------------------------------------------------------------------------*/
/* constants and macros                                                      */
/*---------------------------------------------------------------------------*/
#define UTIL_MAX_STR_LEN   40 //20 //Jennifer modified 20090422
#define GM_DEBUG_ERR_BASE  (GM_DEBUG_MODULE_ID<<16)
#define GM_DEBUG_DISABLE   0
#define GM_DEBUG_TTY       1
#define GM_DEBUG_OSD       2
#define GM_DEBUG_MEM       4

/*---------------------------------------------------------------------------*/
/* Display attributes and color codes                                        */
/*---------------------------------------------------------------------------*/
/* foreground colours */
#define GM_DGREY         "[1;30m"
#define GM_RED           "[1;31m"
#define GM_GREEN         "[1;32m"
#define GM_YELLOW        "[1;33m"
#define GM_BLUE          "[1;34m"
#define GM_MAGENTA       "[1;35m"
#define GM_CYAN          "[1;36m"
#define GM_WHITE         "[1;37m"
#define GM_BLACK         "[0;30m" /* low intensity */
#define GM_DRED          "[0;31m"
#define GM_DGREEN        "[0;32m"
#define GM_DYELLOW       "[0;33m"
#define GM_DBLUE         "[0;34m"
#define GM_DMAGENTA      "[0;35m"
#define GM_DCYAN         "[0;36m"
#define GM_GREY          "[0;37m"
/* background colours */
#define GM_BG_DGREY      "[1;40m"
#define GM_BG_RED        "[1;41m"
#define GM_BG_GREEN      "[1;42m"
#define GM_BG_YELLOW     "[1;43m"
#define GM_BG_BLUE       "[1;44m"
#define GM_BG_MAGENTA    "[1;45m"
#define GM_BG_CYAN       "[1;46m"
#define GM_BG_WHITE      "[1;47m"
#define GM_BG_BLACK      "[0;40m" /* low intensity */
#define GM_BG_DRED       "[0;41m"
#define GM_BG_DGREEN     "[0;42m"
#define GM_BG_DYELLOW    "[0;43m"
#define GM_BG_DBLUE      "[0;44m"
#define GM_BG_DMAGENTA   "[0;45m"
#define GM_BG_DCYAN      "[0;46m"
#define GM_BG_GREY       "[0;47m"
/* display attributes */
#define GM_DISP_RESET     "[0m"    /* default settings (color + attributes) */
#define GM_DISP_UNDERLINE "[4m"    /* cursor underline */
#define GM_DISP_REVERSE   "[7m"    /* reverse display */
#define GM_DISP_BLINK     "[5m"    /* cursor blink */
#define GM_DISP_INVISIBLE "[8m"    /* cursor invisible */


/*---------------------------------------------------------------------------*/
/* types, enums and structures                                               */
/*---------------------------------------------------------------------------*/
typedef struct
{
    U8     dispDevice;  /* or'ed combination of GM_DEBUG_TTY, GM_DEBUG_OSD,  */
                        /* GM_DEBUG_MEM or GM_DEBUG_DISABLE                  */
    S8     gpioRxPin;
    S8     gpioTxPin;
    U8     interruptEnable;
} GM_DEBUG_INIT_PARAMS_S;

typedef void (*out_put_device)(const char );


/*---------------------------------------------------------------------------*/
/* function prototypes                                                       */
/*---------------------------------------------------------------------------*/
#ifdef __cplusplus
extern "C" {
#endif
GERR  GM_DEBUG_Init(GM_DEBUG_INIT_PARAMS_S *paramsP);
int   GM_Printf(const char *__format, ...);
int   GM_Scanf(const char *__format, ...);
U8    GM_DEBUG_GetOutputDevice(void);
GERR GM_DEBUG_SetOutputDevice(out_put_device fun);
U8    GM_DEBUG_ReadChar(void);
GBOOL GM_DEBUG_CheckRxBuffer(void);
void  GM_PrintfSeperator1(void);
void  GM_PrintfSeperator2(void);

/* just a few simple terminal functions if you don't like to include the huge*/
/* printf/scanf from standard C-Lib. If you only like to use these functions */
/* make sure to compile this module with the precompiler flag DEBUG_NO_CLIB  */
/* to reduce memory amount. */
void GM_PrStrStr(const char *str1P, char *str2P);
void GM_PrStr(const char *strP);
void GM_PrHex(int data, int len);
void GM_PrInt(int data);
void GM_PrU32(U32 data);
void GM_PrCStrHex2(const char *strP, U32 data);
void GM_PrCStrHex4(const char *strP, S16 data);
void GM_PrCStrHex8(const char *strP, U32 data);
void GM_PrintChar(char cx);
char GM_ReceiveChar(void);
void GM_ScanStr(char *pDest);
void GM_LimScanStr(char *pDest, U32 length);
int  GM_ScanNum (const char *Format , U32 *pValue);

#ifdef __cplusplus
}
#endif

#endif /* _GM_DEBUG_H_ */
/* end of gm_debug.h */
