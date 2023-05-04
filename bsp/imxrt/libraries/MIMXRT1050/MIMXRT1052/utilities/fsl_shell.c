/*
 * Copyright (c) 2015, Freescale Semiconductor, Inc.
 * Copyright 2016-2018 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * POSIX getopt for Windows
 * Code given out at the 1985 UNIFORUM conference in Dallas.
 *
 * From std-unix@ut-sally.UUCP (Moderator, John Quarterman) Sun Nov  3 14:34:15 1985
 * Relay-Version: version B 2.10.3 4.3bsd-beta 6/6/85; site gatech.CSNET
 * Posting-Version: version B 2.10.2 9/18/84; site ut-sally.UUCP
 * Path: gatech!akgua!mhuxv!mhuxt!mhuxr!ulysses!allegra!mit-eddie!genrad!panda!talcott!harvard!seismo!ut-sally!std-unix
 * From: std-unix@ut-sally.UUCP (Moderator, John Quarterman)
 * Newsgroups: mod.std.unix
 * Subject: public domain AT&T getopt source
 * Message-ID: <3352@ut-sally.UUCP>
 * Date: 3 Nov 85 19:34:15 GMT
 * Date-Received: 4 Nov 85 12:25:09 GMT
 * Organization: IEEE/P1003 Portable Operating System Environment Committee
 * Lines: 91
 * Approved: jsq@ut-sally.UUC
 * Here's something you've all been waiting for:  the AT&T public domain
 * source for getopt(3).  It is the code which was given out at the 1985
 * UNIFORUM conference in Dallas.  I obtained it by electronic mail
 * directly from AT&T.  The people there assure me that it is indeed
 * in the public domain
 * There is no manual page.  That is because the one they gave out at
 * UNIFORUM was slightly different from the current System V Release 2
 * manual page.  The difference apparently involved a note about the
 * famous rules 5 and 6, recommending using white space between an option
 * and its first argument, and not grouping options that have arguments.
 * Getopt itself is currently lenient about both of these things White
 * space is allowed, but not mandatory, and the last option in a group can
 * have an argument.  That particular version of the man page evidently
 * has no official existence, and my source at AT&T did not send a copy.
 * The current SVR2 man page reflects the actual behavor of this getopt.
 * However, I am not about to post a copy of anything licensed by AT&T.
 */

#include <assert.h>
#include <stdarg.h>
#include <stdlib.h>
#include "fsl_str.h"

#include "generic_list.h"
#include "serial_manager.h"

#include "fsl_shell.h"

/*
 * The OSA_USED macro can only be defined when the OSA component is used.
 * If the source code of the OSA component does not exist, the OSA_USED cannot be defined.
 * OR, If OSA component is not added into project event the OSA source code exists, the OSA_USED
 * also cannot be defined.
 * The source code path of the OSA component is <MCUXpresso_SDK>/components/osa.
 *
 */
#if defined(OSA_USED)

#if (defined(SHELL_USE_COMMON_TASK) && (SHELL_USE_COMMON_TASK > 0U))
#include "common_task.h"
#else
#include "fsl_os_abstraction.h"
#endif

#endif

/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define KEY_ESC (0x1BU)
#define KET_DEL (0x7FU)

#define SHELL_EVENT_DATA_ARRIVED (1U << 0)
#define SHELL_EVENT_DATA_SENT (1U << 1)

#define SHELL_SPRINTF_BUFFER_SIZE (64U)

/*! @brief A type for the handle special key. */
typedef enum _fun_key_status
{
    kSHELL_Normal = 0U,   /*!< Normal key */
    kSHELL_Special = 1U,  /*!< Special key */
    kSHELL_Function = 2U, /*!< Function key */
} fun_key_status_t;

/*! @brief Data structure for Shell environment. */
typedef struct _shell_context_handle
{
    list_t commandContextListHead; /*!< Command shellContextHandle list queue head */
    serial_handle_t serialHandle;  /*!< Serial manager handle */
    uint8_t
        serialWriteHandleBuffer[SERIAL_MANAGER_WRITE_HANDLE_SIZE];   /*!< The buffer for serial manager write handle */
    serial_write_handle_t serialWriteHandle;                         /*!< The serial manager write handle */
    uint8_t serialReadHandleBuffer[SERIAL_MANAGER_READ_HANDLE_SIZE]; /*!< The buffer for serial manager read handle */
    serial_read_handle_t serialReadHandle;                           /*!< The serial manager read handle */
    char *prompt;                                                    /*!< Prompt string */
#if (defined(SHELL_NON_BLOCKING_MODE) && (SHELL_NON_BLOCKING_MODE > 0U))

#if defined(OSA_USED)

#if (defined(SHELL_USE_COMMON_TASK) && (SHELL_USE_COMMON_TASK > 0U))
    common_task_message_t commontaskMsg; /*!< Message for common task */
#else
    uint8_t event[OSA_EVENT_HANDLE_SIZE]; /*!< Event instance */
    uint8_t taskId[OSA_TASK_HANDLE_SIZE]; /*!< Task handle */
#endif

#endif

#endif
    char line[SHELL_BUFFER_SIZE];                          /*!< Consult buffer */
    char hist_buf[SHELL_HISTORY_COUNT][SHELL_BUFFER_SIZE]; /*!< History buffer*/
    char printBuffer[SHELL_SPRINTF_BUFFER_SIZE];           /*!< Buffer for print */
    uint32_t printLength;                                  /*!< All length has been printed */
    uint16_t hist_current;                                 /*!< Current history command in hist buff*/
    uint16_t hist_count;                                   /*!< Total history command in hist buff*/
    enum _fun_key_status stat;                             /*!< Special key status */
    uint8_t cmd_num;                                       /*!< Number of user commands */
    uint8_t l_pos;                                         /*!< Total line position */
    uint8_t c_pos;                                         /*!< Current line position */
    volatile uint8_t notificationPost;                     /*!< The serial manager notification is post */
    uint8_t exit;                                          /*!< Exit Flag*/
    uint8_t printBusy;                                     /*!< Print is busy */
} shell_context_handle_t;

#define SHELL_STRUCT_OFFSET(type, field) ((size_t) & (((type *)0)->field))
#define SHEEL_COMMAND_POINTER(node) ((shell_command_t *)(((uint32_t)node) - SHELL_STRUCT_OFFSET(shell_command_t, link)))
/*******************************************************************************
 * Prototypes
 ******************************************************************************/
static shell_status_t SHELL_HelpCommand(shell_handle_t shellContextHandle,
                                        int32_t argc,
                                        char **argv); /*!< help command */

static shell_status_t SHELL_ExitCommand(shell_handle_t shellContextHandle,
                                        int32_t argc,
                                        char **argv); /*!< exit command */

static int32_t SHELL_ParseLine(const char *cmd, uint32_t len, char *argv[]); /*!< parse line command */

static int32_t SHELL_StringCompare(const char *str1, const char *str2, int32_t count); /*!< compare string command */

static void SHELL_ProcessCommand(shell_context_handle_t *shellContextHandle, const char *cmd); /*!< process a command */

static void SHELL_GetHistoryCommand(shell_context_handle_t *shellContextHandle,
                                    uint8_t hist_pos); /*!< get commands history */

static void SHELL_AutoComplete(shell_context_handle_t *shellContextHandle); /*!< auto complete command */

static shell_status_t SHELL_GetChar(shell_context_handle_t *shellContextHandle,
                                    uint8_t *ch); /*!< get a char from communication interface */

#if (defined(SHELL_NON_BLOCKING_MODE) && (SHELL_NON_BLOCKING_MODE > 0U))
static void SHELL_Task(void *param); /*!<  Shell task*/
#endif

/*******************************************************************************
 * Variables
 ******************************************************************************/

SHELL_COMMAND_DEFINE(help, "\r\n\"help\": List all the registered commands\r\n", SHELL_HelpCommand, 0);
SHELL_COMMAND_DEFINE(exit, "\r\n\"exit\": Exit program\r\n", SHELL_ExitCommand, 0);

static char s_paramBuffer[SHELL_BUFFER_SIZE];

#if (defined(SHELL_NON_BLOCKING_MODE) && (SHELL_NON_BLOCKING_MODE > 0U))

#if defined(OSA_USED)

#if (defined(SHELL_USE_COMMON_TASK) && (SHELL_USE_COMMON_TASK > 0U))

#else
                                          /*
                                           * \brief Defines the serial manager task's stack
                                           */
OSA_TASK_DEFINE(SHELL_Task, SHELL_TASK_PRIORITY, 1, SHELL_TASK_STACK_SIZE, false);
#endif

#endif

#endif
/*******************************************************************************
 * Code
 ******************************************************************************/

#if (defined(SHELL_NON_BLOCKING_MODE) && (SHELL_NON_BLOCKING_MODE > 0U))
static void SHELL_SerialManagerTxCallback(void *callbackParam,
                                          serial_manager_callback_message_t *message,
                                          serial_manager_status_t status)
{
    if ((NULL == callbackParam) || (NULL == message))
    {
        return;
    }

    if (kStatus_SerialManager_Success == status)
    {
    }
    else if (kStatus_SerialManager_Canceled == status)
    {
    }
    else
    {
    }
}

static void SHELL_SerialManagerRxCallback(void *callbackParam,
                                          serial_manager_callback_message_t *message,
                                          serial_manager_status_t status)
{
    shell_context_handle_t *shellHandle;
    if ((NULL == callbackParam) || (NULL == message))
    {
        return;
    }

    shellHandle = (shell_context_handle_t *)callbackParam;
    if (kStatus_SerialManager_Notify == status)
    {
        if (!shellHandle->notificationPost)
        {
            shellHandle->notificationPost = 1U;
#if defined(OSA_USED)

#if (defined(SHELL_USE_COMMON_TASK) && (SHELL_USE_COMMON_TASK > 0U))
            shellHandle->commontaskMsg.callback = SHELL_Task;
            shellHandle->commontaskMsg.callbackParam = shellHandle;
            COMMON_TASK_post_message(&shellHandle->commontaskMsg);
#else
            (void)OSA_EventSet((osa_event_handle_t)shellHandle->event, SHELL_EVENT_DATA_ARRIVED);
#endif

#else
            SHELL_Task(shellHandle);
#endif
        }
    }
    else if (kStatus_SerialManager_Success == status)
    {
    }
    else
    {
    }
}
#endif

static void SHELL_WriteBuffer(char *buffer, int32_t *indicator, char val, int len)
{
    shell_context_handle_t *shellContextHandle;
    int i = 0;
    shellContextHandle = (shell_context_handle_t *)buffer;

    for (i = 0; i < len; i++)
    {
        if ((*indicator + 1) >= SHELL_SPRINTF_BUFFER_SIZE)
        {
            SerialManager_WriteBlocking(shellContextHandle->serialWriteHandle,
                                        (uint8_t *)shellContextHandle->printBuffer, *indicator);
            shellContextHandle->printLength += *indicator;
            *indicator = 0U;
        }

        shellContextHandle->printBuffer[*indicator] = val;
        (*indicator)++;
    }
}

static int SHELL_Sprintf(void *buffer, const char *formatString, va_list ap)
{
    shell_context_handle_t *shellContextHandle;
    uint32_t length;
    shellContextHandle = (shell_context_handle_t *)buffer;

    length = StrFormatPrintf(formatString, ap, (char *)buffer, SHELL_WriteBuffer);
    shellContextHandle->printLength += length;
    return length;
}

#if (defined(SHELL_NON_BLOCKING_MODE) && (SHELL_NON_BLOCKING_MODE > 0U))
static void SHELL_Task(void *param)
#else
void SHELL_Task(shell_handle_t shellHandle)
#endif
{
#if (defined(SHELL_NON_BLOCKING_MODE) && (SHELL_NON_BLOCKING_MODE > 0U))
    shell_context_handle_t *shellContextHandle = (shell_context_handle_t *)param;
#else
    shell_context_handle_t *shellContextHandle = (shell_context_handle_t *)shellHandle;
#endif
    uint8_t ch;

    if (NULL != shellContextHandle)
    {
#if (defined(SHELL_NON_BLOCKING_MODE) && (SHELL_NON_BLOCKING_MODE > 0U))

#if defined(OSA_USED)

#if (defined(SHELL_USE_COMMON_TASK) && (SHELL_USE_COMMON_TASK > 0U))
#else
        osa_event_flags_t ev = 0;

        do
        {
            if (KOSA_StatusSuccess == OSA_EventWait((osa_event_handle_t)shellContextHandle->event, osaEventFlagsAll_c,
                                                    false, osaWaitForever_c, &ev))
            {
                if (ev & SHELL_EVENT_DATA_ARRIVED)
#endif

#endif

#endif
        {
            shellContextHandle->notificationPost = 0;
            do
            {
                if (shellContextHandle->exit)
                {
                    if (shellContextHandle->serialReadHandle)
                    {
                        SerialManager_CloseReadHandle(shellContextHandle->serialReadHandle);
                        shellContextHandle->serialReadHandle = NULL;
                    }
                    if (shellContextHandle->serialWriteHandle)
                    {
                        SerialManager_CloseWriteHandle(shellContextHandle->serialWriteHandle);
                        shellContextHandle->serialWriteHandle = NULL;
                    }
                    break;
                }
                if (kStatus_SHELL_Success != SHELL_GetChar(shellContextHandle, &ch))
                {
                    /* If error occurred when getting a char, exit the task and waiting the new data arriving. */
                    break;
                }

                /* Special key */
                if (ch == KEY_ESC)
                {
                    shellContextHandle->stat = kSHELL_Special;
                    continue;
                }
                else if (shellContextHandle->stat == kSHELL_Special)
                {
                    /* Function key */
                    if (ch == '[')
                    {
                        shellContextHandle->stat = kSHELL_Function;
                        continue;
                    }
                    shellContextHandle->stat = kSHELL_Normal;
                }
                else if (shellContextHandle->stat == kSHELL_Function)
                {
                    shellContextHandle->stat = kSHELL_Normal;

                    switch ((uint8_t)ch)
                    {
                        /* History operation here */
                        case 'A': /* Up key */
                            SHELL_GetHistoryCommand(shellContextHandle, shellContextHandle->hist_current);
                            if (shellContextHandle->hist_current < (shellContextHandle->hist_count - 1))
                            {
                                shellContextHandle->hist_current++;
                            }
                            break;
                        case 'B': /* Down key */
                            SHELL_GetHistoryCommand(shellContextHandle, shellContextHandle->hist_current);
                            if (shellContextHandle->hist_current > 0)
                            {
                                shellContextHandle->hist_current--;
                            }
                            break;
                        case 'D': /* Left key */
                            if (shellContextHandle->c_pos)
                            {
                                SHELL_Write(shellContextHandle, "\b", 1);
                                shellContextHandle->c_pos--;
                            }
                            break;
                        case 'C': /* Right key */
                            if (shellContextHandle->c_pos < shellContextHandle->l_pos)
                            {
                                SHELL_Write(shellContextHandle, &shellContextHandle->line[shellContextHandle->c_pos],
                                            1);
                                shellContextHandle->c_pos++;
                            }
                            break;
                        default:
                            break;
                    }
                    continue;
                }
                /* Handle tab key */
                else if (ch == '\t')
                {
#if SHELL_AUTO_COMPLETE
                    /* Move the cursor to the beginning of line */
                    for (int i = 0; i < shellContextHandle->c_pos; i++)
                    {
                        SHELL_Write(shellContextHandle, "\b", 1);
                    }
                    /* Do auto complete */
                    SHELL_AutoComplete(shellContextHandle);
                    /* Move position to end */
                    shellContextHandle->c_pos = shellContextHandle->l_pos = strlen(shellContextHandle->line);
#endif
                    continue;
                }
                /* Handle backspace key */
                else if ((ch == KET_DEL) || (ch == '\b'))
                {
                    /* There must be at last one char */
                    if (shellContextHandle->c_pos == 0)
                    {
                        continue;
                    }

                    shellContextHandle->l_pos--;
                    shellContextHandle->c_pos--;

                    if (shellContextHandle->l_pos > shellContextHandle->c_pos)
                    {
                        memmove(&shellContextHandle->line[shellContextHandle->c_pos],
                                &shellContextHandle->line[shellContextHandle->c_pos + 1],
                                shellContextHandle->l_pos - shellContextHandle->c_pos);
                        shellContextHandle->line[shellContextHandle->l_pos] = 0;
                        SHELL_Write(shellContextHandle, "\b", 1);
                        SHELL_Write(shellContextHandle, &shellContextHandle->line[shellContextHandle->c_pos],
                                    strlen(&shellContextHandle->line[shellContextHandle->c_pos]));
                        SHELL_Write(shellContextHandle, "  \b", 3);

                        /* Reset position */
                        for (int i = shellContextHandle->c_pos; i <= shellContextHandle->l_pos; i++)
                        {
                            SHELL_Write(shellContextHandle, "\b", 1);
                        }
                    }
                    else /* Normal backspace operation */
                    {
                        SHELL_Write(shellContextHandle, "\b \b", 3);
                        shellContextHandle->line[shellContextHandle->l_pos] = 0;
                    }
                    continue;
                }
                else
                {
                }

                /* Input too long */
                if (shellContextHandle->l_pos >= (SHELL_BUFFER_SIZE - 1))
                {
                    shellContextHandle->l_pos = 0;
                }

                /* Handle end of line, break */
                if ((ch == '\r') || (ch == '\n'))
                {
                    static char endoflinechar = 0U;

                    if ((endoflinechar != 0U) && (endoflinechar != ch))
                    {
                        continue;
                    }
                    else
                    {
                        endoflinechar = ch;
                        SHELL_Write(shellContextHandle, "\r\n", 2);
                        /* If command line is NULL, will start a new transfer */
                        if (0U == strlen(shellContextHandle->line))
                        {
                            SHELL_Write(shellContextHandle, shellContextHandle->prompt,
                                        strlen(shellContextHandle->prompt));
                            continue;
                        }
                        SHELL_ProcessCommand(shellContextHandle, shellContextHandle->line);
                        /* Reset all params */
                        shellContextHandle->c_pos = shellContextHandle->l_pos = 0;
                        shellContextHandle->hist_current = 0;
                        SHELL_Write(shellContextHandle, shellContextHandle->prompt, strlen(shellContextHandle->prompt));
                        memset(shellContextHandle->line, 0, sizeof(shellContextHandle->line));
                        continue;
                    }
                }

                /* Normal character */
                if (shellContextHandle->c_pos < shellContextHandle->l_pos)
                {
                    memmove(&shellContextHandle->line[shellContextHandle->c_pos + 1],
                            &shellContextHandle->line[shellContextHandle->c_pos],
                            shellContextHandle->l_pos - shellContextHandle->c_pos);
                    shellContextHandle->line[shellContextHandle->c_pos] = ch;
                    SHELL_Write(shellContextHandle, &shellContextHandle->line[shellContextHandle->c_pos],
                                strlen(&shellContextHandle->line[shellContextHandle->c_pos]));
                    /* Move the cursor to new position */
                    for (int i = shellContextHandle->c_pos; i < shellContextHandle->l_pos; i++)
                    {
                        SHELL_Write(shellContextHandle, "\b", 1);
                    }
                }
                else
                {
                    shellContextHandle->line[shellContextHandle->l_pos] = ch;
                    SHELL_Write(shellContextHandle, &shellContextHandle->line[shellContextHandle->l_pos], 1);
                }

                ch = 0;
                shellContextHandle->l_pos++;
                shellContextHandle->c_pos++;
            } while (!shellContextHandle->exit);
        }
#if (defined(SHELL_NON_BLOCKING_MODE) && (SHELL_NON_BLOCKING_MODE > 0U))

#if defined(OSA_USED)

#if (defined(SHELL_USE_COMMON_TASK) && (SHELL_USE_COMMON_TASK > 0U))
#else
            }
        } while (gUseRtos_c);
#endif

#endif

#endif
    }
}

static shell_status_t SHELL_HelpCommand(shell_handle_t shellHandle, int32_t argc, char **argv)
{
    shell_context_handle_t *shellContextHandle = (shell_context_handle_t *)shellHandle;
    shell_command_t *shellCommandContextHandle;
    list_element_handle_t p = LIST_GetHead(&shellContextHandle->commandContextListHead);

    while (p)
    {
        shellCommandContextHandle = SHEEL_COMMAND_POINTER(p);
        if (shellCommandContextHandle->pcHelpString && strlen(shellCommandContextHandle->pcHelpString))
        {
            SHELL_Write(shellContextHandle, shellCommandContextHandle->pcHelpString,
                        strlen(shellCommandContextHandle->pcHelpString));
        }

        p = LIST_GetNext(p);
    }
    return kStatus_SHELL_Success;
}

static shell_status_t SHELL_ExitCommand(shell_handle_t shellHandle, int32_t argc, char **argv)
{
    shell_context_handle_t *shellContextHandle = (shell_context_handle_t *)shellHandle;
    /* Skip warning */
    SHELL_Write(shellContextHandle, "\r\nSHELL exited\r\n", strlen("\r\nSHELL exited\r\n"));
    shellContextHandle->exit = true;
    return kStatus_SHELL_Success;
}

static void SHELL_ProcessCommand(shell_context_handle_t *shellContextHandle, const char *cmd)
{
    shell_command_t *tmpCommand = NULL;
    const char *tmpCommandString;
    int32_t argc;
    char *argv[SHELL_BUFFER_SIZE];
    list_element_handle_t p;
    uint8_t flag = 1;
    uint8_t tmpCommandLen;
    uint8_t tmpLen;
    uint8_t i = 0;

    tmpLen = strlen(cmd);
    argc = SHELL_ParseLine(cmd, tmpLen, argv);

    if ((tmpCommand == NULL) && (argc > 0))
    {
        p = LIST_GetHead(&shellContextHandle->commandContextListHead);
        while (p)
        {
            tmpCommand = SHEEL_COMMAND_POINTER(p);
            tmpCommandString = tmpCommand->pcCommand;
            tmpCommandLen = strlen(tmpCommandString);
            /* Compare with space or end of string */
            if ((cmd[tmpCommandLen] == ' ') || (cmd[tmpCommandLen] == 0x00))
            {
                if (SHELL_StringCompare(tmpCommandString, argv[0], tmpCommandLen) == 0)
                {
                    /* support commands with optional number of parameters */
                    if (tmpCommand->cExpectedNumberOfParameters == SHELL_IGNORE_PARAMETER_COUNT)
                    {
                        flag = 0;
                    }
                    else if ((tmpCommand->cExpectedNumberOfParameters == 0) && (argc == 1))
                    {
                        flag = 0;
                    }
                    else if (tmpCommand->cExpectedNumberOfParameters > 0)
                    {
                        if ((argc - 1) == tmpCommand->cExpectedNumberOfParameters)
                        {
                            flag = 0;
                        }
                    }
                    else
                    {
                        flag = 1;
                    }
                    break;
                }
            }
            p = LIST_GetNext(p);
        }
    }

    if ((tmpCommand != NULL) && (flag == 1U))
    {
        SHELL_Write(
            shellContextHandle,
            "\r\nIncorrect command parameter(s).  Enter \"help\" to view a list of available commands.\r\n\r\n",
            strlen(
                "\r\nIncorrect command parameter(s).  Enter \"help\" to view a list of available commands.\r\n\r\n"));
        tmpCommand = NULL;
    }
    else if (tmpCommand != NULL)
    {
        tmpLen = strlen(cmd);
        /* Compare with last command. Push back to history buffer if different */
        if (tmpLen != SHELL_StringCompare(cmd, shellContextHandle->hist_buf[0], strlen(cmd)))
        {
            for (i = SHELL_HISTORY_COUNT - 1; i > 0; i--)
            {
                memset(shellContextHandle->hist_buf[i], '\0', SHELL_BUFFER_SIZE);
                tmpLen = strlen(shellContextHandle->hist_buf[i - 1]);
                memcpy(shellContextHandle->hist_buf[i], shellContextHandle->hist_buf[i - 1], tmpLen);
            }
            memset(shellContextHandle->hist_buf[0], '\0', SHELL_BUFFER_SIZE);
            tmpLen = strlen(cmd);
            memcpy(shellContextHandle->hist_buf[0], cmd, tmpLen);
            if (shellContextHandle->hist_count < SHELL_HISTORY_COUNT)
            {
                shellContextHandle->hist_count++;
            }
        }
        tmpCommand->pFuncCallBack(shellContextHandle, argc, argv);
        tmpCommand = NULL;
    }
    else
    {
        SHELL_Write(shellContextHandle,
                    "\r\nCommand not recognized.  Enter 'help' to view a list of available commands.\r\n\r\n",
                    strlen("\r\nCommand not recognized.  Enter 'help' to view a list of available commands.\r\n\r\n"));
        tmpCommand = NULL;
    }
}

static void SHELL_GetHistoryCommand(shell_context_handle_t *shellContextHandle, uint8_t hist_pos)
{
    uint8_t i;
    uint32_t tmp;

    if (shellContextHandle->hist_buf[0][0] == '\0')
    {
        shellContextHandle->hist_current = 0;
        return;
    }
    if (hist_pos >= SHELL_HISTORY_COUNT)
    {
        hist_pos = SHELL_HISTORY_COUNT - 1;
    }
    tmp = strlen(shellContextHandle->line);
    /* Clear current if have */
    if (tmp > 0)
    {
        memset(shellContextHandle->line, '\0', tmp);
        for (i = 0; i < tmp; i++)
        {
            SHELL_Write(shellContextHandle, "\b \b", 3);
        }
    }

    shellContextHandle->l_pos = strlen(shellContextHandle->hist_buf[hist_pos]);
    shellContextHandle->c_pos = shellContextHandle->l_pos;
    memcpy(shellContextHandle->line, shellContextHandle->hist_buf[hist_pos], shellContextHandle->l_pos);
    SHELL_Write(shellContextHandle, shellContextHandle->hist_buf[hist_pos],
                strlen(shellContextHandle->hist_buf[hist_pos]));
}

static void SHELL_AutoComplete(shell_context_handle_t *shellContextHandle)
{
    int32_t len;
    int32_t minLen;
    list_element_handle_t p;
    shell_command_t *tmpCommand = NULL;
    const char *namePtr;
    const char *cmdName;

    minLen = 0;
    namePtr = NULL;

    if (!strlen(shellContextHandle->line))
    {
        return;
    }
    SHELL_Write(shellContextHandle, "\r\n", 2);
    /* Empty tab, list all commands */
    if (shellContextHandle->line[0] == '\0')
    {
        SHELL_HelpCommand(shellContextHandle, 0, NULL);
        return;
    }
    /* Do auto complete */
    p = LIST_GetHead(&shellContextHandle->commandContextListHead);
    while (p)
    {
        tmpCommand = SHEEL_COMMAND_POINTER(p);
        cmdName = tmpCommand->pcCommand;
        if (SHELL_StringCompare(shellContextHandle->line, cmdName, strlen(shellContextHandle->line)) == 0)
        {
            if (minLen == 0)
            {
                namePtr = cmdName;
                minLen = strlen(namePtr);
                /* Show possible matches */
                SHELL_Write(shellContextHandle, (char *)cmdName, strlen(cmdName));
                SHELL_Write(shellContextHandle, "\r\n", 2);
                continue;
            }
            len = SHELL_StringCompare(namePtr, cmdName, strlen(namePtr));
            if (len < 0)
            {
                len = len * (-1);
            }
            if (len < minLen)
            {
                minLen = len;
            }
        }
        p = LIST_GetNext(p);
    }
    /* Auto complete string */
    if (namePtr)
    {
        memcpy(shellContextHandle->line, namePtr, minLen);
    }
    SHELL_Write(shellContextHandle, shellContextHandle->prompt, strlen(shellContextHandle->prompt));
    SHELL_Write(shellContextHandle, shellContextHandle->line, strlen(shellContextHandle->line));
    return;
}

static int32_t SHELL_StringCompare(const char *str1, const char *str2, int32_t count)
{
    while (count--)
    {
        if (*str1++ != *str2++)
        {
            return *(unsigned char *)(str1 - 1) - *(unsigned char *)(str2 - 1);
        }
    }
    return 0;
}

static int32_t SHELL_ParseLine(const char *cmd, uint32_t len, char *argv[])
{
    uint32_t argc;
    char *p;
    uint32_t position;

    /* Init params */
    memset(s_paramBuffer, '\0', len + 1);
    memcpy(s_paramBuffer, cmd, len);

    p = s_paramBuffer;
    position = 0;
    argc = 0;

    while (position < len)
    {
        /* Skip all blanks */
        while (((char)(*p) == ' ') && (position < len))
        {
            *p = '\0';
            p++;
            position++;
        }
        /* Process begin of a string */
        if (*p == '"')
        {
            p++;
            position++;
            argv[argc] = p;
            argc++;
            /* Skip this string */
            while ((*p != '"') && (position < len))
            {
                p++;
                position++;
            }
            /* Skip '"' */
            *p = '\0';
            p++;
            position++;
        }
        else /* Normal char */
        {
            argv[argc] = p;
            argc++;
            while (((char)*p != ' ') && ((char)*p != '\t') && (position < len))
            {
                p++;
                position++;
            }
        }
    }
    return argc;
}

static shell_status_t SHELL_GetChar(shell_context_handle_t *shellContextHandle, uint8_t *ch)
{
#if (defined(SHELL_NON_BLOCKING_MODE) && (SHELL_NON_BLOCKING_MODE > 0U))
    uint32_t length;

    if (kStatus_SerialManager_Success == SerialManager_TryRead(shellContextHandle->serialReadHandle, ch, 1, &length))
    {
        if (length > 0)
        {
            return kStatus_SHELL_Success;
        }
    }

    return kStatus_SHELL_Error;
#else
    return (shell_status_t)SerialManager_ReadBlocking(shellContextHandle->serialReadHandle, ch, 1);
#endif
}

shell_status_t SHELL_Init(shell_handle_t shellHandle, serial_handle_t serialHandle, char *prompt)
{
    shell_context_handle_t *shellContextHandle;
    assert(shellHandle);
    assert(serialHandle);
    assert(prompt);

    if (SHELL_HANDLE_SIZE < sizeof(shell_context_handle_t))
    {
        return kStatus_SHELL_Error;
    }

    shellContextHandle = (shell_context_handle_t *)shellHandle;

    /* memory set for shellHandle */
    memset(shellHandle, 0, SHELL_HANDLE_SIZE);

#if (defined(SHELL_NON_BLOCKING_MODE) && (SHELL_NON_BLOCKING_MODE > 0U))

#if defined(OSA_USED)

#if (defined(SHELL_USE_COMMON_TASK) && (SHELL_USE_COMMON_TASK > 0U))
    COMMON_TASK_init();
#else
    if (KOSA_StatusSuccess != OSA_EventCreate((osa_event_handle_t)shellContextHandle->event, true))
    {
        return kStatus_SHELL_Error;
    }

    if (KOSA_StatusSuccess !=
        OSA_TaskCreate((osa_task_handle_t)shellContextHandle->taskId, OSA_TASK(SHELL_Task), shellContextHandle))
    {
        return kStatus_SHELL_Error;
    }
#endif

#endif

#endif

    shellContextHandle->prompt = prompt;
    shellContextHandle->serialHandle = serialHandle;

    shellContextHandle->serialWriteHandle = (serial_write_handle_t)&shellContextHandle->serialWriteHandleBuffer[0];
    if (kStatus_SerialManager_Success !=
        SerialManager_OpenWriteHandle(shellContextHandle->serialHandle, shellContextHandle->serialWriteHandle))
    {
        return kStatus_SHELL_OpenWriteHandleFailed;
    }
    else
    {
#if (defined(SHELL_NON_BLOCKING_MODE) && (SHELL_NON_BLOCKING_MODE > 0U))
        SerialManager_InstallTxCallback(shellContextHandle->serialWriteHandle, SHELL_SerialManagerTxCallback,
                                        shellContextHandle);
#endif
    }

    shellContextHandle->serialReadHandle = (serial_read_handle_t)&shellContextHandle->serialReadHandleBuffer[0];
    if (kStatus_SerialManager_Success !=
        SerialManager_OpenReadHandle(shellContextHandle->serialHandle, shellContextHandle->serialReadHandle))
    {
        return kStatus_SHELL_OpenReadHandleFailed;
    }
    else
    {
#if (defined(SHELL_NON_BLOCKING_MODE) && (SHELL_NON_BLOCKING_MODE > 0U))
        SerialManager_InstallRxCallback(shellContextHandle->serialReadHandle, SHELL_SerialManagerRxCallback,
                                        shellContextHandle);
#endif
    }

    SHELL_RegisterCommand(shellContextHandle, SHELL_COMMAND(help));
    SHELL_RegisterCommand(shellContextHandle, SHELL_COMMAND(exit));

    SHELL_Write(shellContextHandle, "\r\nSHELL build: ", strlen("\r\nSHELL build: "));
    SHELL_Write(shellContextHandle, __DATE__, strlen(__DATE__));
    SHELL_Write(shellContextHandle, "\r\nCopyright (c) 2018 NXP Semiconductor\r\n",
                strlen("\r\nCopyright (c) 2018 NXP Semiconductor\r\n"));
    SHELL_Write(shellContextHandle, shellContextHandle->prompt, strlen(shellContextHandle->prompt));

    return kStatus_SHELL_Success;
}

shell_status_t SHELL_RegisterCommand(shell_handle_t shellHandle, shell_command_t *command)
{
    shell_context_handle_t *shellContextHandle = (shell_context_handle_t *)shellHandle;
    assert(shellHandle);
    assert(command);

    /* memory set for shellHandle */
    memset(&command->link, 0, sizeof(command->link));

    LIST_AddTail(&shellContextHandle->commandContextListHead, &command->link);

    return kStatus_SHELL_Success;
}

shell_status_t SHELL_UnregisterCommand(shell_command_t *command)
{
    assert(command);

    LIST_RemoveElement(&command->link);

    /* memory set for shellHandle */
    memset(&command->link, 0, sizeof(command->link));

    return kStatus_SHELL_Success;
}

shell_status_t SHELL_Write(shell_handle_t shellHandle, char *buffer, uint32_t length)
{
    shell_context_handle_t *shellContextHandle;
    uint32_t primask;

    assert(shellHandle);
    assert(buffer);

    if (!length)
    {
        return kStatus_SHELL_Success;
    }

    shellContextHandle = (shell_context_handle_t *)shellHandle;

    primask = DisableGlobalIRQ();
    if (shellContextHandle->printBusy)
    {
        EnableGlobalIRQ(primask);
        return kStatus_SHELL_Error;
    }
    shellContextHandle->printBusy = 1U;
    EnableGlobalIRQ(primask);

    if (kStatus_SerialManager_Success ==
        SerialManager_WriteBlocking(shellContextHandle->serialWriteHandle, (uint8_t *)buffer, length))
    {
        shellContextHandle->printBusy = 0U;
        return kStatus_SHELL_Success;
    }
    shellContextHandle->printBusy = 0U;

    return kStatus_SHELL_Error;
}

int SHELL_Printf(shell_handle_t shellHandle, const char *formatString, ...)
{
    shell_context_handle_t *shellContextHandle;
    uint32_t length;
    uint32_t primask;
    va_list ap;

    assert(shellHandle);
    assert(formatString);

    shellContextHandle = (shell_context_handle_t *)shellHandle;

    primask = DisableGlobalIRQ();
    if (shellContextHandle->printBusy)
    {
        EnableGlobalIRQ(primask);
        return -1;
    }
    shellContextHandle->printBusy = 1U;
    EnableGlobalIRQ(primask);

    va_start(ap, formatString);

    shellContextHandle->printLength = 0U;
    length = SHELL_Sprintf(shellHandle, formatString, ap);
    SerialManager_WriteBlocking(shellContextHandle->serialWriteHandle, (uint8_t *)shellContextHandle->printBuffer,
                                length);
    va_end(ap);

    shellContextHandle->printBusy = 0U;
    return shellContextHandle->printLength;
}
