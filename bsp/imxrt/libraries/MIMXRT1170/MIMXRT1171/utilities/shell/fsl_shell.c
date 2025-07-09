/*
 * Copyright (c) 2015, Freescale Semiconductor, Inc.
 * Copyright 2016-2024 NXP
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
#include <stdio.h>

#include "fsl_common.h"
#include "fsl_str.h"

#include "fsl_component_generic_list.h"
#include "fsl_component_serial_manager.h"

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
#include "fsl_component_common_task.h"
#else
#include "fsl_os_abstraction.h"
#endif

#endif

/*******************************************************************************
 * Definitions
 ******************************************************************************/
#if defined(OSA_USED)
#define SHELL_WRITEX SHELL_WriteSynchronization
#else
#define SHELL_WRITEX SHELL_Write
#endif

/* Weak function. */
#if defined(__GNUC__)
#define __WEAK_FUNC __attribute__((weak))
#elif defined(__ICCARM__)
#define __WEAK_FUNC __weak
#elif defined(__CC_ARM) || defined(__ARMCC_VERSION)
#define __WEAK_FUNC __attribute__((weak))
#elif defined(__DSC__) || defined(__CW__)
#define __WEAK_FUNC __attribute__((weak))
#endif

#if (!defined(GCOV_DO_COVERAGE) || (GCOV_DO_COVERAGE == 0))
#define SHELL_STATIC static
#else
#define SHELL_STATIC __WEAK_FUNC
#endif

#if defined(OSA_USED)
#if (defined(USE_RTOS) && (USE_RTOS > 0U))
static OSA_MUTEX_HANDLE_DEFINE(s_shellMutex);
#define SHELL_MUTEX_CREATE()   (void)OSA_MutexCreate(s_shellMutex)
#define SHELL_ENTER_CRITICAL() (void)OSA_MutexLock(s_shellMutex, osaWaitForever_c)
#define SHELL_EXIT_CRITICAL()  (void)OSA_MutexUnlock(s_shellMutex)
#else
#define SHELL_MUTEX_CREATE()
#define SHELL_ENTER_CRITICAL()
#define SHELL_EXIT_CRITICAL()
#endif
#else
#ifdef SDK_OS_FREE_RTOS
#include "FreeRTOS.h"
#include "queue.h"
#include "semphr.h"
static QueueHandle_t s_shellMutex;

#define SHELL_MUTEX_CREATE()   s_shellMutex = xSemaphoreCreateMutex()
#define SHELL_ENTER_CRITICAL() (void)xSemaphoreTakeRecursive(s_shellMutex, portMAX_DELAY)
#define SHELL_EXIT_CRITICAL()  (void)xSemaphoreGiveRecursive(s_shellMutex)
#else /* BM case*/
#define SHELL_MUTEX_CREATE()
#define SHELL_ENTER_CRITICAL()
#define SHELL_EXIT_CRITICAL()
#endif
#endif

#define KEY_ESC (0x1BU)
#define KET_DEL (0x7FU)

#define SHELL_EVENT_DATA_ARRIVED (1U << 0)
#define SHELL_EVENT_DATA_SENT    (1U << 1)

#define SHELL_SPRINTF_BUFFER_SIZE (64U)

/*! @brief A type for the handle special key. */
typedef enum _fun_key_status
{
    kSHELL_Normal   = 0U, /*!< Normal key */
    kSHELL_Special  = 1U, /*!< Special key */
    kSHELL_Function = 2U, /*!< Function key */
} fun_key_status_t;

/*! @brief Data structure for Shell environment. */
typedef struct _shell_context_handle
{
    list_label_t commandContextListHead; /*!< Command shellContextHandle list queue head */
    serial_handle_t serialHandle;        /*!< Serial manager handle */
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
    uint8_t printBusy : 1;                                 /*!< Print is busy */
    uint8_t taskBusy : 1;                                  /*!< Task is busy */
} shell_context_handle_t;

#if 0
#define SHELL_STRUCT_OFFSET(type, field) ((size_t) & (((type *)0)->field))
#define SHEEL_COMMAND_POINTER(node) \
    ((shell_command_t *)(((uint32_t)(node)) - SHELL_STRUCT_OFFSET(shell_command_t, link)))
#else
#define SHEEL_COMMAND_POINTER(node) \
    ((shell_command_t *)(((uint32_t)(node)) - (sizeof(shell_command_t) - sizeof(list_element_t))))
#endif
/*******************************************************************************
 * Prototypes
 ******************************************************************************/
static shell_status_t SHELL_HelpCommand(shell_handle_t shellHandle, int32_t argc, char **argv); /*!< help command */

static shell_status_t SHELL_ExitCommand(shell_handle_t shellHandle, int32_t argc, char **argv); /*!< exit command */

static int32_t SHELL_ParseLine(const char *cmd, uint32_t len, char *argv[]); /*!< parse line command */

static int32_t SHELL_StringCompare(const char *str1, const char *str2, int32_t count); /*!< compare string command */

static void SHELL_ProcessCommand(shell_context_handle_t *shellContextHandle, const char *cmd); /*!< process a command */

static void SHELL_GetHistoryCommand(shell_context_handle_t *shellContextHandle,
                                    uint8_t hist_pos); /*!< get commands history */

static void SHELL_AutoComplete(shell_context_handle_t *shellContextHandle); /*!< auto complete command */

static shell_status_t SHELL_GetChar(shell_context_handle_t *shellContextHandle,
                                    uint8_t *ch); /*!< get a char from communication interface */

#if (defined(SHELL_NON_BLOCKING_MODE) && (SHELL_NON_BLOCKING_MODE > 0U))
SHELL_STATIC void SHELL_Task(void *param); /*!<  Shell task*/
#endif

/*******************************************************************************
 * Variables
 ******************************************************************************/

static SHELL_COMMAND_DEFINE(help, "\r\n\"help\": List all the registered commands\r\n", SHELL_HelpCommand, 0);
static SHELL_COMMAND_DEFINE(exit, "\r\n\"exit\": Exit program\r\n", SHELL_ExitCommand, 0);

static char s_paramBuffer[SHELL_BUFFER_SIZE];

#if (defined(SHELL_NON_BLOCKING_MODE) && (SHELL_NON_BLOCKING_MODE > 0U))
#if defined(OSA_USED)
#if (defined(SHELL_USE_COMMON_TASK) && (SHELL_USE_COMMON_TASK > 0U))
#else
/*
 * \brief Defines the serial manager task's stack
 */
static OSA_TASK_DEFINE(SHELL_Task, SHELL_TASK_PRIORITY, 1, SHELL_TASK_STACK_SIZE, false);
#endif
#endif /* OSA_USED */
#endif /* SHELL_NON_BLOCKING_MODE */
/*******************************************************************************
 * Code
 ******************************************************************************/

#if (defined(SHELL_NON_BLOCKING_MODE) && (SHELL_NON_BLOCKING_MODE > 0U))
SHELL_STATIC void SHELL_SerialManagerRxCallback(void *callbackParam,
                                                serial_manager_callback_message_t *message,
                                                serial_manager_status_t status)
{
    shell_context_handle_t *shellHandle;

    assert(callbackParam);
    assert(message);

    shellHandle = (shell_context_handle_t *)callbackParam;

    if (0U == shellHandle->notificationPost)
    {
        shellHandle->notificationPost = 1U;
#if defined(OSA_USED)

#if (defined(SHELL_USE_COMMON_TASK) && (SHELL_USE_COMMON_TASK > 0U))
        shellHandle->commontaskMsg.callback      = SHELL_Task;
        shellHandle->commontaskMsg.callbackParam = shellHandle;
        (void)COMMON_TASK_post_message(&shellHandle->commontaskMsg);
#else
        (void)OSA_EventSet((osa_event_handle_t)shellHandle->event, SHELL_EVENT_DATA_ARRIVED);
#endif

#else
        SHELL_Task(shellHandle);
#endif
    }
}
#endif

static void SHELL_WriteBuffer(char *buffer, int32_t *indicator, char val, int len)
{
    shell_context_handle_t *shellContextHandle;
    int i              = 0;
    shellContextHandle = (shell_context_handle_t *)(void *)buffer;

    for (i = 0; i < len; i++)
    {
        if ((*indicator + 1) >= (int32_t)SHELL_SPRINTF_BUFFER_SIZE)
        {
#if (!defined(SDK_DEBUGCONSOLE_UART) && (defined(SDK_DEBUGCONSOLE) && (SDK_DEBUGCONSOLE != 1)))
            if (NULL == shellContextHandle->serialHandle)
            {
                for (uint32_t index = 0; index < ((uint32_t)*indicator); index++)
                {
                    (void)putchar(shellContextHandle->printBuffer[index]);
                }
            }
            else
#endif
            {
                (void)SerialManager_WriteBlocking(shellContextHandle->serialWriteHandle,
                                                  (uint8_t *)shellContextHandle->printBuffer, (uint32_t)*indicator);
            }

            shellContextHandle->printLength += (uint32_t)*indicator;
            *indicator = 0;
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

    length = (uint32_t)StrFormatPrintf(formatString, ap, (char *)buffer, SHELL_WriteBuffer);
    shellContextHandle->printLength += length;
    return (int32_t)length;
}

static void SHELL_hisOperation(uint8_t ch, shell_context_handle_t *shellContextHandle)
{
    switch ((char)ch)
    {
        /* History operation here */
        case 'A': /* Up key */
            SHELL_GetHistoryCommand(shellContextHandle, (uint8_t)shellContextHandle->hist_current);
            if (shellContextHandle->hist_current < (shellContextHandle->hist_count - 1U))
            {
                shellContextHandle->hist_current++;
            }
            break;
        case 'B': /* Down key */
            SHELL_GetHistoryCommand(shellContextHandle, (uint8_t)shellContextHandle->hist_current);
            if (shellContextHandle->hist_current > 0U)
            {
                shellContextHandle->hist_current--;
            }
            break;
        case 'D': /* Left key */
            if ((bool)shellContextHandle->c_pos)
            {
                (void)SHELL_WRITEX(shellContextHandle, "\b", 1);
                shellContextHandle->c_pos--;
            }
            break;
        case 'C': /* Right key */
            if (shellContextHandle->c_pos < shellContextHandle->l_pos)
            {
                (void)SHELL_WRITEX(shellContextHandle, &shellContextHandle->line[shellContextHandle->c_pos], 1);
                shellContextHandle->c_pos++;
            }
            break;
        default:
            /* MISRA C-2012 Rule 16.4 */
            break;
    }
}

static void SHELL_SerialManagerHandle(shell_context_handle_t *shellContextHandle)
{
    if (shellContextHandle->serialReadHandle != NULL)
    {
        (void)SerialManager_CloseReadHandle(shellContextHandle->serialReadHandle);
        shellContextHandle->serialReadHandle = NULL;
    }
    if (shellContextHandle->serialWriteHandle != NULL)
    {
        (void)SerialManager_CloseWriteHandle(shellContextHandle->serialWriteHandle);
        shellContextHandle->serialWriteHandle = NULL;
    }
}

#if SHELL_AUTO_COMPLETE
/* Move the cursor to the beginning of line */
static void SHELL_MoveCursorToBeginningLine(shell_context_handle_t *shellContextHandle)
{
    uint32_t i;
    for (i = 0; i < (uint32_t)shellContextHandle->c_pos; i++)
    {
        (void)SHELL_WRITEX(shellContextHandle, "\b", 1);
    }
    /* Do auto complete */
    SHELL_AutoComplete(shellContextHandle);
    /* Move position to end */
    shellContextHandle->l_pos = (uint8_t)strlen(shellContextHandle->line);
    shellContextHandle->c_pos = shellContextHandle->l_pos;
}
#endif

/* There must be at last one char */
static void SHELL_HandleBackspaceKey(shell_context_handle_t *shellContextHandle)
{
    shellContextHandle->l_pos--;
    shellContextHandle->c_pos--;

    if (shellContextHandle->l_pos > shellContextHandle->c_pos)
    {
        (void)memmove(&shellContextHandle->line[shellContextHandle->c_pos],
                      &shellContextHandle->line[shellContextHandle->c_pos + 1U],
                      (uint32_t)shellContextHandle->l_pos - (uint32_t)shellContextHandle->c_pos);
        shellContextHandle->line[shellContextHandle->l_pos] = '\0';
        (void)SHELL_WRITEX(shellContextHandle, "\b", 1);
        (void)SHELL_WRITEX(shellContextHandle, &shellContextHandle->line[shellContextHandle->c_pos],
                           strlen(&shellContextHandle->line[shellContextHandle->c_pos]));
        (void)SHELL_WRITEX(shellContextHandle, "  \b", 3);

        /* Reset position */
        uint32_t i;
        for (i = (uint32_t)shellContextHandle->c_pos; i <= (uint32_t)shellContextHandle->l_pos; i++)
        {
            (void)SHELL_WRITEX(shellContextHandle, "\b", 1);
        }
    }
    else /* Normal backspace operation */
    {
        (void)SHELL_WRITEX(shellContextHandle, "\b \b", 3);
        shellContextHandle->line[shellContextHandle->l_pos] = '\0';
    }
}
/* Normal character */
static void SHELL_HandleNormalChar(shell_context_handle_t *shellContextHandle, uint8_t ch)
{
    if (shellContextHandle->c_pos < shellContextHandle->l_pos)
    {
        uint32_t i;
        (void)memmove(&shellContextHandle->line[shellContextHandle->c_pos + 1U],
                      &shellContextHandle->line[shellContextHandle->c_pos],
                      (uint32_t)shellContextHandle->l_pos - (uint32_t)shellContextHandle->c_pos);
        shellContextHandle->line[shellContextHandle->c_pos] = (char)ch;
        (void)SHELL_WRITEX(shellContextHandle, &shellContextHandle->line[shellContextHandle->c_pos],
                           strlen(&shellContextHandle->line[shellContextHandle->c_pos]));

        for (i = (uint32_t)shellContextHandle->c_pos; i < (uint32_t)shellContextHandle->l_pos; i++)
        {
            (void)SHELL_WRITEX(shellContextHandle, "\b", 1);
        }
    }
    else
    {
        shellContextHandle->line[shellContextHandle->l_pos] = (char)ch;
        (void)SHELL_WRITEX(shellContextHandle, &shellContextHandle->line[shellContextHandle->l_pos], 1);
    }
}

/* Case of Input too long */
static void SHELL_HandleInputTooLong(shell_context_handle_t *shellContextHandle)
{
    if (shellContextHandle->l_pos >= (SHELL_BUFFER_SIZE - 1U))
    {
        shellContextHandle->l_pos = 0U;
    }
}

#if (defined(SHELL_NON_BLOCKING_MODE) && (SHELL_NON_BLOCKING_MODE > 0U))
SHELL_STATIC void SHELL_Task(void *param)
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
        uint32_t osaCurrentSr = 0U;

        osaCurrentSr                         = DisableGlobalIRQ();
        shellContextHandle->notificationPost = 0U;
        if (shellContextHandle->taskBusy > 0U)
        {
            EnableGlobalIRQ(osaCurrentSr);
            return;
        }
        shellContextHandle->taskBusy = 1U;
        EnableGlobalIRQ(osaCurrentSr);
#if (defined(SHELL_NON_BLOCKING_MODE) && (SHELL_NON_BLOCKING_MODE > 0U))

#if defined(OSA_USED)

#if (defined(SHELL_USE_COMMON_TASK) && (SHELL_USE_COMMON_TASK > 0U))
#else
        osa_event_flags_t ev = 0;

        do
        {
            if (KOSA_StatusSuccess == OSA_EventWait((osa_event_handle_t)shellContextHandle->event, osaEventFlagsAll_c,
                                                    0U, osaWaitForever_c, &ev))
            {
                if (0U != (ev & SHELL_EVENT_DATA_ARRIVED))
#endif

#endif

#endif
        {
            shellContextHandle->notificationPost = 0U;
            do
            {
                if ((bool)shellContextHandle->exit)
                {
                    SHELL_SerialManagerHandle(shellContextHandle);
                    break;
                }
                if (kStatus_SHELL_Success != (shell_status_t)SHELL_GetChar(shellContextHandle, &ch))
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
                    if ((char)ch == '[')
                    {
                        shellContextHandle->stat = kSHELL_Function;
                        continue;
                    }
                    shellContextHandle->stat = kSHELL_Normal;
                }
                else if (shellContextHandle->stat == kSHELL_Function)
                {
                    shellContextHandle->stat = kSHELL_Normal;
                    SHELL_hisOperation(ch, shellContextHandle);
                    continue;
                }
                /* Handle tab key */
                else if ((char)ch == '\t')
                {
#if SHELL_AUTO_COMPLETE

                    SHELL_MoveCursorToBeginningLine(shellContextHandle);
#endif
                    continue;
                }
                /* Handle backspace key */
                else if ((ch == KET_DEL) || ((char)ch == '\b'))
                {
                    /* There must be at last one char */
                    if ((shellContextHandle->c_pos == 0U) || (shellContextHandle->l_pos == 0U))
                    {
                        continue;
                    }
                    SHELL_HandleBackspaceKey(shellContextHandle);
                    continue;
                }
                else
                {
                    /* MISRA C-2012 Rule 15.7 */
                }

                /* Input too long */
                SHELL_HandleInputTooLong(shellContextHandle);

                /* Handle end of line, break */
                if (((char)ch == '\r') || ((char)ch == '\n'))
                {
                    static char endoflinechar = '\0';

                    if (((uint8_t)endoflinechar != 0U) && ((uint8_t)endoflinechar != ch))
                    {
                        continue;
                    }
                    else
                    {
                        endoflinechar = (char)ch;
                        /* Print new line. */
                        (void)SHELL_WRITEX(shellContextHandle, "\r\n", 2U);
                        /* If command line is not NULL, will start process it. */
                        if (0U != strlen(shellContextHandle->line))
                        {
                            SHELL_ProcessCommand(shellContextHandle, shellContextHandle->line);
                        }
                        /* Print prompt. */
                        (void)SHELL_WRITEX(shellContextHandle, shellContextHandle->prompt,
                                           strlen(shellContextHandle->prompt));
                        /* Reset all params */
                        shellContextHandle->c_pos = shellContextHandle->l_pos = 0;
                        shellContextHandle->hist_current                      = 0;
                        (void)memset(shellContextHandle->line, 0, sizeof(shellContextHandle->line));
                        continue;
                    }
                }

                /* Normal character */
                SHELL_HandleNormalChar(shellContextHandle, ch);

                ch = 0;
                shellContextHandle->l_pos++;
                shellContextHandle->c_pos++;
            } while (0U == shellContextHandle->exit);
        }
#if (defined(SHELL_NON_BLOCKING_MODE) && (SHELL_NON_BLOCKING_MODE > 0U))

#if defined(OSA_USED)

#if (defined(SHELL_USE_COMMON_TASK) && (SHELL_USE_COMMON_TASK > 0U))
#else
            }
        } while (1U == gUseRtos_c); /* USE_RTOS = 0 for BareMetal and 1 for OS */
#endif

#endif

#endif
        osaCurrentSr                 = DisableGlobalIRQ();
        shellContextHandle->taskBusy = 0U;
        EnableGlobalIRQ(osaCurrentSr);
    }
}

static shell_status_t SHELL_HelpCommand(shell_handle_t shellHandle, int32_t argc, char **argv)
{
    shell_context_handle_t *shellContextHandle = (shell_context_handle_t *)shellHandle;
    shell_command_t *shellCommandContextHandle;
    list_element_handle_t p = LIST_GetHead(&shellContextHandle->commandContextListHead);

    while (p != NULL)
    {
        shellCommandContextHandle = SHEEL_COMMAND_POINTER(p);
        if ((shellCommandContextHandle->pcHelpString != NULL) && (bool)strlen(shellCommandContextHandle->pcHelpString))
        {
            (void)SHELL_WRITEX(shellContextHandle, shellCommandContextHandle->pcHelpString,
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
    (void)SHELL_WRITEX(shellContextHandle, "\r\nSHELL exited\r\n", strlen("\r\nSHELL exited\r\n"));
    shellContextHandle->exit = (uint8_t) true;
    return kStatus_SHELL_Success;
}

static void SHELL_ProcessCommand(shell_context_handle_t *shellContextHandle, const char *cmd)
{
    shell_command_t *tmpCommand = NULL;
    const char *tmpCommandString;
    int32_t argc;
    char *argv[SHELL_BUFFER_SIZE] = {0};
    list_element_handle_t p;
    uint8_t flag = 1;
    uint8_t tmpCommandLen;
    uint8_t tmpLen;
    uint8_t i = 0;

    tmpLen = (uint8_t)strlen(cmd);
    if (tmpLen >= SHELL_BUFFER_SIZE - 1U)
    {
        (void)SHELL_Printf(shellContextHandle,
                           "Command line length should not more than SHELL_BUFFER_SIZE, please input command less "
                           "(SHELL_BUFFER_SIZE - 1) characters again!\r\n");
        return;
    }
    else
    {
        argc = SHELL_ParseLine(cmd, tmpLen, argv);
    }

    if ((argc > 0))
    {
        p = LIST_GetHead(&shellContextHandle->commandContextListHead);
        while (p != NULL)
        {
            tmpCommand       = SHEEL_COMMAND_POINTER(p);
            tmpCommandString = tmpCommand->pcCommand;
            tmpCommandLen    = (uint8_t)strlen(tmpCommandString);
            /* Compare with space or end of string */
            if ((cmd[tmpCommandLen] == ' ') || (cmd[tmpCommandLen] == (char)0x00))
            {
                if (SHELL_StringCompare(tmpCommandString, argv[0], (int32_t)tmpCommandLen) == 0)
                {
                    /* support commands with optional number of parameters */
                    if (tmpCommand->cExpectedNumberOfParameters == (uint8_t)SHELL_IGNORE_PARAMETER_COUNT)
                    {
                        flag = 0;
                    }
                    else if ((tmpCommand->cExpectedNumberOfParameters == 0U) && (argc == 1))
                    {
                        flag = 0;
                    }
                    else if (tmpCommand->cExpectedNumberOfParameters > 0U)
                    {
                        if ((argc - 1) == (int32_t)tmpCommand->cExpectedNumberOfParameters)
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
        if (NULL == p)
        {
            tmpCommand = NULL;
        }
    }

    if ((tmpCommand != NULL) && (flag == 1U))
    {
        (void)SHELL_Write(
            shellContextHandle,
            "\r\nIncorrect command parameter(s).  Enter \"help\" to view a list of available commands.\r\n\r\n",
            strlen(
                "\r\nIncorrect command parameter(s).  Enter \"help\" to view a list of available commands.\r\n\r\n"));
    }
    else if (tmpCommand != NULL)
    {
        tmpLen = (uint8_t)strlen(cmd);
        /* Compare with last command. Push back to history buffer if different */
        if (tmpLen != (uint8_t)SHELL_StringCompare(cmd, shellContextHandle->hist_buf[0], (int32_t)strlen(cmd)))
        {
            for (i = SHELL_HISTORY_COUNT - 1U; i > 0U; i--)
            {
                (void)memset(shellContextHandle->hist_buf[i], (int)'\0', SHELL_BUFFER_SIZE);
                tmpLen = (uint8_t)strlen(shellContextHandle->hist_buf[i - 1U]);
                (void)memcpy(shellContextHandle->hist_buf[i], shellContextHandle->hist_buf[i - 1U], tmpLen);
            }
            (void)memset(shellContextHandle->hist_buf[0], (int)'\0', SHELL_BUFFER_SIZE);
            tmpLen = (uint8_t)strlen(cmd);
            (void)memcpy(shellContextHandle->hist_buf[0], cmd, tmpLen);
            if (shellContextHandle->hist_count < SHELL_HISTORY_COUNT)
            {
                shellContextHandle->hist_count++;
            }
        }
        if (kStatus_SHELL_RetUsage == tmpCommand->pFuncCallBack(shellContextHandle, argc, argv))
        {
            if (NULL != tmpCommand->pcHelpString)
            {
                (void)SHELL_WRITEX(shellContextHandle, tmpCommand->pcHelpString, strlen(tmpCommand->pcHelpString));
            }
            else
            {
                (void)SHELL_HelpCommand(shellContextHandle, 0, NULL);
            }
        }
    }
    else
    {
        (void)SHELL_Write(
            shellContextHandle,
            "\r\nCommand not recognized.  Enter 'help' to view a list of available commands.\r\n\r\n",
            strlen("\r\nCommand not recognized.  Enter 'help' to view a list of available commands.\r\n\r\n"));
    }
}

static void SHELL_GetHistoryCommand(shell_context_handle_t *shellContextHandle, uint8_t hist_pos)
{
    uint32_t i;
    uint32_t tmp;

    if (shellContextHandle->hist_buf[0][0] == '\0')
    {
        shellContextHandle->hist_current = 0;
        return;
    }

#if 0 /*hist_pos is passed from hist_current. And hist_current is only changed in case 'A'/'B',as hist_count is 3 \
         most, it can't be more than 3  */
    if (hist_pos >= SHELL_HISTORY_COUNT)
    {
        hist_pos = SHELL_HISTORY_COUNT - 1U;
    }
#endif

    tmp = strlen(shellContextHandle->line);
    /* Clear current if have */
    if (tmp > 0U)
    {
        (void)memset(shellContextHandle->line, (int)'\0', tmp);
        for (i = 0U; i < tmp; i++)
        {
            (void)SHELL_WRITEX(shellContextHandle, "\b \b", 3);
        }
    }

    shellContextHandle->l_pos = (uint8_t)strlen(shellContextHandle->hist_buf[hist_pos]);
    shellContextHandle->c_pos = shellContextHandle->l_pos;
    (void)memcpy(shellContextHandle->line, shellContextHandle->hist_buf[hist_pos], shellContextHandle->l_pos);
    (void)SHELL_WRITEX(shellContextHandle, shellContextHandle->hist_buf[hist_pos],
                       strlen(shellContextHandle->hist_buf[hist_pos]));
}

static void SHELL_AutoComplete(shell_context_handle_t *shellContextHandle)
{
    int32_t minLen;
    list_element_handle_t p;
    shell_command_t *tmpCommand = NULL;
    const char *namePtr;
    const char *cmdName;

    minLen  = (int32_t)SHELL_BUFFER_SIZE;
    namePtr = NULL;

    /* Empty tab, list all commands */
    if (shellContextHandle->line[0] == '\0')
    {
        (void)SHELL_HelpCommand(shellContextHandle, 0, NULL);
        return;
    }

    (void)SHELL_WRITEX(shellContextHandle, "\r\n", 2);

    /* Do auto complete */
    p = LIST_GetHead(&shellContextHandle->commandContextListHead);
    while (p != NULL)
    {
        tmpCommand = SHEEL_COMMAND_POINTER(p);
        cmdName    = tmpCommand->pcCommand;
        if (SHELL_StringCompare(shellContextHandle->line, cmdName, (int32_t)strlen(shellContextHandle->line)) == 0)
        {
            /* Show possible matches */
            (void)SHELL_Printf(shellContextHandle, "%s    ", cmdName);
            if (minLen > ((int32_t)strlen(cmdName)))
            {
                namePtr = cmdName;
                minLen  = (int32_t)strlen(namePtr);
            }
        }
        p = LIST_GetNext(p);
    }
    /* Auto complete string */
    if (namePtr != NULL)
    {
        (void)memcpy(shellContextHandle->line, namePtr, (uint32_t)minLen);
    }
    SHELL_PrintPrompt(shellContextHandle);
    (void)SHELL_WRITEX(shellContextHandle, shellContextHandle->line, strlen(shellContextHandle->line));
    return;
}

static int32_t SHELL_StringCompare(const char *str1, const char *str2, int32_t count)
{
    while ((bool)(count--))
    {
        if (*str1++ != *str2++)
        {
            return (int32_t)(*(str1 - 1) - *(str2 - 1));
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
    (void)memset(s_paramBuffer, (int)'\0', len + 1U);
    (void)memcpy(s_paramBuffer, cmd, len);

    p        = s_paramBuffer;
    position = 0;
    argc     = 0;

    while (position < len)
    {
        /* Skip all blanks */
        while ((position < len) && ((char)(*p) == ' '))
        {
            *p = '\0';
            p++;
            position++;
        }

        if (position >= len)
        {
            break;
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
            while (((char)*p != ' ') && (position < len))
            {
                p++;
                position++;
            }
        }
    }
    return (int32_t)argc;
}

static shell_status_t SHELL_GetChar(shell_context_handle_t *shellContextHandle, uint8_t *ch)
{
    shell_status_t status;

#if (!defined(SDK_DEBUGCONSOLE_UART) && (defined(SDK_DEBUGCONSOLE) && (SDK_DEBUGCONSOLE != 1)))
    if (NULL == shellContextHandle->serialHandle)
    {
        int ret;
        ret = getchar();
        if (ret > 0)
        {
            *ch    = (uint8_t)ret;
            status = kStatus_SHELL_Success;
        }
        else
        {
            status = kStatus_SHELL_Error;
        }
    }
    else
#endif
    {
#if (defined(SHELL_NON_BLOCKING_MODE) && (SHELL_NON_BLOCKING_MODE > 0U))
        uint32_t length = 0;

        (void)SerialManager_TryRead(shellContextHandle->serialReadHandle, ch, 1, &length);

        if (length > 0U)
        {
            status = kStatus_SHELL_Success;
        }
        else
        {
            status = kStatus_SHELL_Error;
        }
#else
        status = (shell_status_t)SerialManager_ReadBlocking(shellContextHandle->serialReadHandle, ch, 1);
#endif
    }

    return status;
}

shell_status_t SHELL_Init(shell_handle_t shellHandle, serial_handle_t serialHandle, char *prompt)
{
    shell_context_handle_t *shellContextHandle;
    serial_manager_status_t status = kStatus_SerialManager_Error;
    (void)status;

    assert(shellHandle);
#if !(!defined(SDK_DEBUGCONSOLE_UART) && (defined(SDK_DEBUGCONSOLE) && (SDK_DEBUGCONSOLE != 1)))
    assert(serialHandle);
#endif
    assert(prompt);
    assert(SHELL_HANDLE_SIZE >= sizeof(shell_context_handle_t));

    shellContextHandle = (shell_context_handle_t *)shellHandle;

    /* memory set for shellHandle */
    (void)memset(shellHandle, 0, SHELL_HANDLE_SIZE);

#if (!defined(SDK_DEBUGCONSOLE_UART) && (defined(SDK_DEBUGCONSOLE) && (SDK_DEBUGCONSOLE != 1)))
    if (NULL == serialHandle)
    {
    }
    else
#endif
    {
#if (defined(SHELL_NON_BLOCKING_MODE) && (SHELL_NON_BLOCKING_MODE > 0U))

#if defined(OSA_USED)

#if (defined(SHELL_USE_COMMON_TASK) && (SHELL_USE_COMMON_TASK > 0U))
        (void)COMMON_TASK_init();
#else
        if (KOSA_StatusSuccess != OSA_EventCreate((osa_event_handle_t)shellContextHandle->event, 1U))
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
    }

    shellContextHandle->prompt       = prompt;
    shellContextHandle->serialHandle = serialHandle;

#if (!defined(SDK_DEBUGCONSOLE_UART) && (defined(SDK_DEBUGCONSOLE) && (SDK_DEBUGCONSOLE != 1)))
    if (NULL == serialHandle)
    {
    }
    else
#endif
    {
        shellContextHandle->serialWriteHandle = (serial_write_handle_t)&shellContextHandle->serialWriteHandleBuffer[0];
        status = SerialManager_OpenWriteHandle(shellContextHandle->serialHandle, shellContextHandle->serialWriteHandle);
        assert(kStatus_SerialManager_Success == status);

        shellContextHandle->serialReadHandle = (serial_read_handle_t)&shellContextHandle->serialReadHandleBuffer[0];
        status = SerialManager_OpenReadHandle(shellContextHandle->serialHandle, shellContextHandle->serialReadHandle);
        assert(kStatus_SerialManager_Success == status);

#if (defined(SHELL_NON_BLOCKING_MODE) && (SHELL_NON_BLOCKING_MODE > 0U))
        status = SerialManager_InstallRxCallback(shellContextHandle->serialReadHandle, SHELL_SerialManagerRxCallback,
                                                 shellContextHandle);
        assert(kStatus_SerialManager_Success == status);
#endif
        (void)status;
    }

    (void)SHELL_RegisterCommand(shellContextHandle, SHELL_COMMAND(help));
    (void)SHELL_RegisterCommand(shellContextHandle, SHELL_COMMAND(exit));
    SHELL_MUTEX_CREATE();
#if (defined(SHELL_PRINT_COPYRIGHT) && (SHELL_PRINT_COPYRIGHT > 0U))
    (void)SHELL_Write(shellContextHandle, "\r\nCopyright  2024  NXP\r\n", strlen("\r\nCopyright  2024  NXP\r\n"));
#endif
    SHELL_PrintPrompt(shellContextHandle);

    return kStatus_SHELL_Success;
}

shell_status_t SHELL_RegisterCommand(shell_handle_t shellHandle, shell_command_t *shellCommand)
{
    shell_context_handle_t *shellContextHandle = (shell_context_handle_t *)shellHandle;
    assert(shellHandle);
    assert(shellCommand);

    /* memory set for shellHandle */
    (void)memset(&shellCommand->link, 0, sizeof(shellCommand->link));

    (void)LIST_AddTail(&shellContextHandle->commandContextListHead, &shellCommand->link);

    return kStatus_SHELL_Success;
}

shell_status_t SHELL_UnregisterCommand(shell_command_t *shellCommand)
{
    assert(shellCommand);

    (void)LIST_RemoveElement(&shellCommand->link);

    /* memory set for shellHandle */
    (void)memset(&shellCommand->link, 0, sizeof(shellCommand->link));

    return kStatus_SHELL_Success;
}

shell_status_t SHELL_Write(shell_handle_t shellHandle, const char *buffer, uint32_t length)
{
    shell_context_handle_t *shellContextHandle;
    uint32_t primask;
    shell_status_t status;

    assert(shellHandle);
    assert(buffer);

    if (!(bool)length)
    {
        return kStatus_SHELL_Success;
    }

    shellContextHandle = (shell_context_handle_t *)shellHandle;

    primask = DisableGlobalIRQ();
    if ((bool)shellContextHandle->printBusy)
    {
        EnableGlobalIRQ(primask);
        return kStatus_SHELL_Error;
    }
    shellContextHandle->printBusy = 1U;
    EnableGlobalIRQ(primask);
#if (!defined(SDK_DEBUGCONSOLE_UART) && (defined(SDK_DEBUGCONSOLE) && (SDK_DEBUGCONSOLE != 1)))
    if (NULL == shellContextHandle->serialHandle)
    {
        status = kStatus_SHELL_Success;
        for (uint32_t index = 0; index < length; index++)
        {
            (void)putchar(buffer[index]);
        }
    }
    else
#endif
    {
        status = (shell_status_t)SerialManager_WriteBlocking(shellContextHandle->serialWriteHandle, (uint8_t *)buffer,
                                                             length);
    }

    shellContextHandle->printBusy = 0U;

    return status;
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
    if ((bool)shellContextHandle->printBusy)
    {
        EnableGlobalIRQ(primask);
        return -1;
    }
    shellContextHandle->printBusy = 1U;
    EnableGlobalIRQ(primask);

    va_start(ap, formatString);

    shellContextHandle->printLength = 0U;
    length                          = (uint32_t)SHELL_Sprintf(shellHandle, formatString, ap);
#if (!defined(SDK_DEBUGCONSOLE_UART) && (defined(SDK_DEBUGCONSOLE) && (SDK_DEBUGCONSOLE != 1)))
    if (NULL == shellContextHandle->serialHandle)
    {
        for (uint32_t index = 0; index < length; index++)
        {
            (void)putchar(shellContextHandle->printBuffer[index]);
        }
    }
    else
#endif
    {
        (void)SerialManager_WriteBlocking(shellContextHandle->serialWriteHandle,
                                          (uint8_t *)shellContextHandle->printBuffer, length);
    }
    va_end(ap);

    shellContextHandle->printBusy = 0U;
    return (int32_t)shellContextHandle->printLength;
}

shell_status_t SHELL_WriteSynchronization(shell_handle_t shellHandle, const char *buffer, uint32_t length)
{
    shell_status_t status;

    assert(SHELL_checkRunningInIsr() == false);

    SHELL_ENTER_CRITICAL();
    status = SHELL_Write(shellHandle, buffer, length);

    SHELL_EXIT_CRITICAL();

    return status;
}

int SHELL_PrintfSynchronization(shell_handle_t shellHandle, const char *formatString, ...)
{
    shell_status_t status;
    shell_context_handle_t *shellContextHandle;
    va_list ap;
    uint32_t length;

    assert(SHELL_checkRunningInIsr() == false);

    shellContextHandle = (shell_context_handle_t *)shellHandle;

    SHELL_ENTER_CRITICAL();
    va_start(ap, formatString);
    length = (uint32_t)SHELL_Sprintf(shellHandle, formatString, ap);

    status = SHELL_Write(shellHandle, (const char *)shellContextHandle->printBuffer, length);
    va_end(ap);
    SHELL_EXIT_CRITICAL();

    return (status == kStatus_SHELL_Success) ? (int)length : 0;
}
void SHELL_ChangePrompt(shell_handle_t shellHandle, char *prompt)
{
    shell_context_handle_t *shellContextHandle;
    assert(shellHandle);
    assert(prompt);

    shellContextHandle = (shell_context_handle_t *)shellHandle;

    shellContextHandle->prompt = prompt;
    SHELL_PrintPrompt(shellContextHandle);
}

void SHELL_PrintPrompt(shell_handle_t shellHandle)
{
    shell_context_handle_t *shellContextHandle;
    assert(shellHandle);

    shellContextHandle = (shell_context_handle_t *)shellHandle;

    (void)SHELL_Write(shellContextHandle, "\r\n", 2U);
    (void)SHELL_Write(shellContextHandle, shellContextHandle->prompt, strlen(shellContextHandle->prompt));
}
