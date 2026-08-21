/**
  ******************************************************************************
  * @file    user_debug.c
  * @author  MCD Application Team
  * @brief   This file provides the Debug User Config Method.
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

/* Includes ------------------------------------------------------------------*/
#include <stdio.h>
#include <string.h>
#include "dbg/user_debug.h"


/** @defgroup TAE_Utilities TAE Utilities
  * @brief    TAE Utilities
  * @{
  */

/** @defgroup User_Debug User Debug
  * @brief    User Debug
  * @{
  */


/* Private Constants ---------------------------------------------------------*/
/** @defgroup User_Debug_Private_Constants User Debug Private Constants
  * @brief    User Debug Private Constants
  * @{
  */

/**
  * @brief C lib stdio.h putchar/getchar interface retarget
  * @note  With GCC/RAISONANCE, small DBG_NOR (option LD Linker->Libraries->Small DBG_NOR set to 'Yes') calls these functions
  */
#if   defined (__CC_ARM)                                        /*!< AC5 Compiler */

    #define PUTCHAR_PROTOTYPE           int fputc(int ch, FILE *f)
    #define GETCHAR_PROTOTYPE           int fgetc(FILE *f)

#elif defined (__ICCARM__)                                      /*!< IAR Compiler */

    #define PUTCHAR_PROTOTYPE           int putchar(int ch)
    #define GETCHAR_PROTOTYPE           int getchar(void)

#elif defined(__ARMCC_VERSION) && (__ARMCC_VERSION >= 6010050)  /*!< AC6 Compiler */

    #define PUTCHAR_PROTOTYPE           int fputc(int ch, FILE *f)
    #define GETCHAR_PROTOTYPE           int fgetc(FILE *f)

#elif defined (__GNUC__)                                        /*!< GCC Compiler */

    #define PUTCHAR_PROTOTYPE           int _write(int fd, char *pBuffer, int size)
    #define GETCHAR_PROTOTYPE           int _read(int fd, char *pBuffer, int size)

#else

    #error "Not supported compiler type"

#endif

/**
  * @}
  */


/* Private Types -------------------------------------------------------------*/
/** @defgroup User_Debug_Private_Types User Debug Private Types
  * @brief    User Debug Private Types
  * @{
  */

/**
  * @brief C lib stdio.h __FILE struct definition for KEIL Compiler
  */
#if defined(__CC_ARM)
#pragma import(__use_no_semihosting_swi)
struct __FILE {
    int handle;
    /* Add whatever you need here */
};
#endif

/**
  * @}
  */


/* Private Variables ---------------------------------------------------------*/
/** @defgroup User_Debug_Private_Variables User Debug Private Variables
  * @brief    User Debug Private Variables
  * @{
  */

#if defined(__CC_ARM) || defined(__ICCARM__) || (defined(__ARMCC_VERSION) && (__ARMCC_VERSION >= 6010050))
    /**
    * @brief C lib stdio.h __stdout FILE stream definition
    */
    FILE __stdout;

    /**
    * @brief C lib stdio.h __stdin FILE stream definition
    */
    FILE __stdin;

    /**
    * @brief C lib stdio.h __stderr FILE stream definition
    */
    //FILE __stderr;
#endif

/**
  * @brief user debug interface
  */
USER_DBG_IfcETypeDef user_dbg_ifc;

/**
  * @brief user debug ITM Rx buffer
  */
volatile int32_t ITM_RxBuffer;

#ifdef LL_UART_MODULE_ENABLED
    /**
    * @brief user debug uart instance
    */
    UART_TypeDef *user_dbg_uart_ins;
#endif

/**
  * @}
  */


/* Private Macros ------------------------------------------------------------*/
/* Private Function Prototypes -----------------------------------------------*/
/* Exported Variables --------------------------------------------------------*/
/* Exported Functions --------------------------------------------------------*/
/** @defgroup User_Debug_Exported_Functions User Debug Exported Functions
  * @brief    User Debug Exported Functions
  * @{
  */

/**
  * @brief  User Debug Init
  * @note   Remember to implement the LL_UART_MspInit interface in the user file if use UART as debug interface
  * @param  ifc User debug interface
  * @return LL Status
  */
LL_StatusETypeDef User_Debug_Init(USER_DBG_IfcETypeDef ifc)
{
    LL_StatusETypeDef ret = LL_FAILED;

    //Check ifc to be Valid
    if (ifc == USER_DBG_IFC_NO) {
        user_dbg_ifc = USER_DBG_IFC_NO;
        user_dbg_uart_ins = NULL;
        return LL_OK;
    }

    //User Debug Interface Init
    if (ifc == USER_DBG_IFC_ITM) {
#ifdef LL_GPIO_MODULE_ENABLED
        //SWO GPIO Init: PB3
        GPIO_InitTypeDef swo_init;
        swo_init.Pin = GPIO_PIN_3;
        swo_init.IntMode = GPIO_INT_MODE_CLOSE;
        swo_init.OType = GPIO_OTYPE_PP;
        swo_init.Pull = GPIO_NOPULL;
        swo_init.Speed = GPIO_SPEED_FREQ_LOW;
        swo_init.Alternate = GPIO_AF2_SWO;
        ret = LL_GPIO_Init(GPIOB, &swo_init);

        if (ret == LL_OK) {
            user_dbg_ifc = ifc;
        }

#endif

    } else {

#ifdef LL_UART_MODULE_ENABLED

        UART_TypeDef *uart_ins_temp;

        if (ifc == USER_DBG_IFC_UART0) {
            uart_ins_temp = UART0;
        } else if (ifc == USER_DBG_IFC_UART1) {
            uart_ins_temp = UART1;
        } else if (ifc == USER_DBG_IFC_UART2) {
            uart_ins_temp = UART2;
        } else if (ifc == USER_DBG_IFC_UART3) {
            uart_ins_temp = UART3;
        } else if (ifc == USER_DBG_IFC_UART4) {
            uart_ins_temp = UART4;
        } else {
            return LL_INVALID;
        }

        //UART Init
        UART_InitTypeDef uart_init;
        memset((void *)&uart_init, 0x00, sizeof(uart_init));
        uart_init.baudrate = 115200;
        uart_init.dat_len = UART_DAT_LEN_8b;
        uart_init.stop_len = UART_STOP_LEN_1b;
        uart_init.parity = UART_PARITY_NO;
        ret = LL_UART_Init(uart_ins_temp, &uart_init);

        if (ret == LL_OK) {
            user_dbg_ifc = ifc;
            user_dbg_uart_ins = uart_ins_temp;
        }

#endif
    }

    return ret;
}

/**
  * @brief  User Debug DeInit
  * @note   Remember to implement the LL_UART_MspDeInit interface in the user file if use UART as debug interface
  * @return LL Status
  */
LL_StatusETypeDef User_Debug_DeInit(void)
{
    LL_StatusETypeDef ret = LL_FAILED;

    //Check current user debug interface to be Valid
    if (user_dbg_ifc == USER_DBG_IFC_NO) {
        user_dbg_uart_ins = NULL;
        return LL_OK;
    }

    if (user_dbg_ifc == USER_DBG_IFC_ITM) {
#ifdef LL_GPIO_MODULE_ENABLED
        //SWO GPIO DeInit: PB3
        ret = LL_GPIO_DeInit(GPIOB, GPIO_PIN_3);

        if (ret == LL_OK) {
            user_dbg_ifc = USER_DBG_IFC_NO;
        }

#endif

    } else {

#ifdef LL_UART_MODULE_ENABLED

        if (user_dbg_uart_ins == NULL) {
            return LL_INVALID;
        }

        //UART DeInit
        ret = LL_UART_DeInit(user_dbg_uart_ins);

        if (ret == LL_OK) {
            user_dbg_ifc = USER_DBG_IFC_NO;
            user_dbg_uart_ins = NULL;
        }

#endif
    }

    return ret;
}

/**
  * @brief  User Debug Get Char
  * @param  None
  * @return get char value
  */
int User_Debug_GetChar(void)
{
    int val = 0;

    //Check user debug interface to be Valid
    if (user_dbg_ifc == USER_DBG_IFC_NO) {
        return 0;
    }

    if (user_dbg_ifc == USER_DBG_IFC_ITM) {
        while (!ITM_CheckChar()) {
            __NOP();
        }

        val = ITM_ReceiveChar();
    } else {
#ifdef LL_UART_MODULE_ENABLED

        if (user_dbg_uart_ins == NULL) {
            return 0;
        }

        //Wait RX data to be ready
        while (__LL_UART_IsRxFIFOEmpty(user_dbg_uart_ins));

        //Read data from UART
        val = __LL_UART_RxDat9bits_Read(user_dbg_uart_ins);
#endif
    }

    return val;
}

/**
  * @brief  User Debug Put Char
  * @param  Data put data
  * @return None
  */
void User_Debug_PutChar(uint16_t Data)
{
    //Check user debug interface to be Valid
    if (user_dbg_ifc == USER_DBG_IFC_NO) {
        return;
    }

    if (user_dbg_ifc == USER_DBG_IFC_ITM) {
        ITM_SendChar(Data);
    } else {
#ifdef LL_UART_MODULE_ENABLED

        if (user_dbg_uart_ins == NULL) {
            return;
        }

        //Wait TXFIFO to be no full
        while (__LL_UART_IsTxFIFOFull(user_dbg_uart_ins));

        //Send data to UART
        __LL_UART_TxDat9bits_Write(user_dbg_uart_ins, Data);
#endif
    }
}

/**
  * @}
  */


/* Private Functions ---------------------------------------------------------*/
/** @defgroup User_Debug_Private_Functions User Debug Private Functions
  * @brief    User Debug Private Functions
  * @{
  */


#if defined(__CC_ARM) || defined(__ICCARM__) || (defined(__ARMCC_VERSION) && (__ARMCC_VERSION >= 6010050))
/**
  * @brief  Get char, Retargets the C library DBG_NOR function to the UART or ITM.
  * @param  f file pointer
  * @retval get char value
  */
GETCHAR_PROTOTYPE {
    int val = 0;

    val = User_Debug_GetChar();

    return val;
}

/**
  * @brief  Put char, Retargets the C library DBG_NOR function to the UART or ITM.
  * @param  ch put data
  * @param  f file pointer
  * @retval ch
  */
PUTCHAR_PROTOTYPE {
    User_Debug_PutChar(ch);

    return ch;
}

/**
  * @brief  ferror
  * @param  f: Printed entry pointer
  * @retval Return result
  */
int ferror(FILE *f)
{
    /* Your implementation of ferror */
    return EOF;
}

/**
  * @brief  _ttywrch
  * @param  ch: The value of the string to print
  * @retval None
  */
void _ttywrch(int ch)
{
    int file = 0;
    fputc(ch, (FILE *)file);
}

/**
  * @brief  _sys_exit
  * @param  return_code: Return wrong information
  * @retval None
  */
void _sys_exit(int return_code)
{
    while (1);    /* endless loop */
}

/**
  * @brief  backspace
  * @param  None
  * @return 0
  */
int __backspace()
{
    return 0;
}

#else

PUTCHAR_PROTOTYPE {
    for (int i = 0; i < size; i++)
    {
        User_Debug_PutChar(pBuffer[i]);
    }

    return size;
}

GETCHAR_PROTOTYPE {
    for (int i = 0; i < size; i++)
    {
        pBuffer[i] = User_Debug_GetChar();
    }

    return size;
}

#endif

/**
  * @}
  */


/**
  * @}
  */

/**
  * @}
  */


/************************* (C) COPYRIGHT Tai-Action *****END OF FILE***********/

