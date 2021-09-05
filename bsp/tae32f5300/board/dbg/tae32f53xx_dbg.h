/**
  ******************************************************************************
  * @file    tae32f53xx_dbg.h
  * @author  MCD Application Team
  * @brief   The macro definitions for dbg
  *
  ==============================================================================
        ##### How to use #####
  ==============================================================================
  *
  * If you want to use debug macro, you can use as following steps:
  *
  * Step 1: Macros in "tae32f53xx_dbg_conf.h"
  *     a. Define the TAE_USING_DBG to enable the feature
  *         #define TAE_USING_DBG
  *
  *     b. Define the print interface for dbg
  *         #define TAE_DBG_PRINT(...)  printf(__VA_ARGS__)
  *
  *     c. Other optional macros define, such as TAE_USING_DBG_COLOR
  *
  * Step 2: Macros in your C/C++ file
  *     a. Define the debug tag and level for dbg. If you did not define this,
           default definition will be used.
  *         #define DBG_TAG         "TAG"    // must be string
  *         #define DBG_LVL         DBG_INFO // others DBG_ERROR, DBG_WARNING, DBG_LOG.
  *                                             DBG_LOG > DBG_INFO > DBG_WARNING > DBG_ERROR
  *
  *     b. Include this header file
  *         #include "tae32f53xx_dbg.h"    // this must after of DBG_LVL, DBG_TAG or other options
  *
  * Step 3: LOG_X macro to print out logs in your C/C++ file
  *     PLEASE NOTE: LOG_X is related to the DBG_LVL that defined in Step 2. Using LOG_X
  *     witch higher then DBG_LVL will be ignored.
  *         LOG_D("this is a debug log!");
  *         LOG_I("this is a info log!")
  *         LOG_W("this is a warning log!")
  *         LOG_E("this is a error log!");
  *
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 Tai-Action.
  * All rights reserved.</center></h2>
  *
  * This software is licensed by Tai-Action under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef _TAE32F53XX_DBG_H_
#define _TAE32F53XX_DBG_H_

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* Includes ------------------------------------------------------------------*/
#include "tae32f53xx_dbg_conf.h"


/** @addtogroup TAE_Utilities
  * @{
  */

/** @defgroup TAE_Debug TAE Debug
  * @brief    TAE Debug
  * @{
  */


/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/** @defgroup TAE_Debug_Exported_Constants TAE Debug Exported Constants
  * @brief    TAE Debug Exported Constants
  * @{
  */

#ifdef TAE_USING_DBG

/* DEBUG level */
#define DBG_NONE            0
#define DBG_ERROR           1
#define DBG_WARNING         2
#define DBG_INFO            3
#define DBG_LOG             4

/* The color for terminal (foreground) */
#define BLACK               30
#define RED                 31
#define GREEN               32
#define YELLOW              33
#define BLUE                34
#define PURPLE              35
#define CYAN                36
#define WHITE               37
#define CLEAR_ALL           0

#ifndef DBG_TAG
#define DBG_TAG             "DBG"
#endif

#ifndef DBG_LVL
#define DBG_LVL             DBG_WARNING
#endif

#ifndef TAE_DBG_PRINT
#define TAE_DBG_PRINT(fmt, ...)
#endif

#endif /* TAE_USING_DBG */

/**
  * @}
  */


/* Exported macro ------------------------------------------------------------*/
/** @defgroup TAE_Debug_Exported_Macros TAE Debug Exported Macros
  * @brief    TAE Debug Exported Macros
  * @{
  */

#ifdef TAE_USING_DBG

#ifdef TAE_USING_DBG_COLOR
#define _DBG_COLOR(color)                   TAE_DBG_PRINT("\033["#color"m")
#define _DBG_LOG_HEAD(lvl_name, color)      TAE_DBG_PRINT("\033["#color"m[" lvl_name "@" DBG_TAG "] ")
#define _DBG_LOG_END()                      TAE_DBG_PRINT("\033[0m")
#else
#define _DBG_COLOR(color)
#define _DBG_LOG_HEAD(lvl_name, color)      TAE_DBG_PRINT("[" lvl_name "@" DBG_TAG "] ")
#define _DBG_LOG_END()                      TAE_DBG_PRINT("")
#endif  /* TAE_USING_DBG_COLOR */


#define DBG_LogRaw(...)                         TAE_DBG_PRINT(__VA_ARGS__)

#define DBG_Log(lvl_name, color, fmt, ...)                      \
    do {                                                        \
        _DBG_LOG_HEAD(lvl_name, color);                         \
        TAE_DBG_PRINT(fmt, ##__VA_ARGS__);                      \
        _DBG_COLOR(0);                                          \
    } while (0)

#define DBG_LogLine(lvl_name, color, fmt, ...)                  \
    do {                                                        \
        _DBG_LOG_HEAD(lvl_name, color);                         \
        TAE_DBG_PRINT(fmt, ##__VA_ARGS__);                      \
        _DBG_COLOR(0);                                          \
        _DBG_LOG_END();                                         \
    } while (0)

#define DBG_Here()                                              \
    if ((DBG_LVL) >= DBG_INFO) {                                \
        _DBG_LOG_HEAD("I", 32);                                 \
        TAE_DBG_PRINT("Here is %s:%d", __FUNCTION__,            \
            __LINE__);                                          \
        _DBG_COLOR(0);                                          \
        _DBG_LOG_END();                                         \
    }

#define DBG_Enter()                                             \
    if ((DBG_LVL) >= DBG_INFO) {                                \
        _DBG_LOG_HEAD("I", 32);                                 \
        TAE_DBG_PRINT("Enter function %s", __FUNCTION__);       \
        _DBG_COLOR(0);                                          \
        _DBG_LOG_END();                                         \
    }

#define DBG_Exit()                                              \
    if ((DBG_LVL) >= DBG_INFO) {                                \
        _DBG_LOG_HEAD("I", 32);                                 \
        TAE_DBG_PRINT("Exit function %s", __FUNCTION__);        \
        _DBG_COLOR(0);                                          \
        _DBG_LOG_END();                                         \
    }

#else

#define DBG_Log(level, fmt, ...)
#define DBG_LogLine(lvl_name, color, fmt, ...)
#define DBG_LogRaw(...)
#define DBG_Here()
#define DBG_Enter()
#define DBG_Exit()

#endif /* TAE_USING_DBG */


#if (DBG_LVL >= DBG_LOG)
#define LOG_D(fmt, ...)         DBG_LogLine("D", CLEAR_ALL, fmt, ##__VA_ARGS__)
#else
#define LOG_D(fmt, ...)
#endif

#if (DBG_LVL >= DBG_INFO)
#define LOG_I(fmt, ...)         DBG_LogLine("I", GREEN, fmt, ##__VA_ARGS__)
#else
#define LOG_I(fmt, ...)
#endif

#if (DBG_LVL >= DBG_WARNING)
#define LOG_W(fmt, ...)         DBG_LogLine("W", YELLOW, fmt, ##__VA_ARGS__)
#else
#define LOG_W(fmt, ...)
#endif

#if (DBG_LVL >= DBG_ERROR)
#define LOG_E(fmt, ...)         DBG_LogLine("E", RED, fmt, ##__VA_ARGS__)
#else
#define LOG_E(fmt, ...)
#endif

#define LOG_R(...)              DBG_LogRaw(__VA_ARGS__)

#define LOG_Enter()             DBG_Enter()

#define LOG_Exit()              DBG_Exit()

#define LOG_Here()              DBG_Here()

/**
  * @}
  */


/* Exported functions --------------------------------------------------------*/
/* Private types -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private constants ---------------------------------------------------------*/
/* Private macros ------------------------------------------------------------*/
/* Private functions ---------------------------------------------------------*/


/**
  * @}
  */

/**
  * @}
  */


#ifdef __cplusplus
}
#endif /* __cplusplus */


#endif /* _TAE32F53XX_DBG_H_ */


/************************* (C) COPYRIGHT Tai-Action *****END OF FILE***********/

