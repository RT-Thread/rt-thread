/*
* Copyright (c) 2020 - 2026 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

/***********************************************************************************************************************
 *
 * Includes
 **********************************************************************************************************************/
#include <stdint.h>
#include <stdarg.h>

#include "bsp_dump_mem.h"
#include "sdk_defs.h"

#if CFG_WIFI
#include "rm_wifi_config.h"
#endif /* CFG_WIFI */

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/
#define COLOR_LEN    10
#define MAX_FAULT    5

#if !defined(ARRAY_SIZE)
 #define ARRAY_SIZE(x)    (long) (sizeof(x) / sizeof(x)[0])
#endif

/* Retention Macro definitions */
#define OOPS_STACK_SIZE                97
#define OOPS_STACK_STRING_CODE         0XABBADEAD
#define OOPS_STACK_STRING_CHAR_SIZE    80
#define OOPS_STACK_STRING_UINT_SIZE    (OOPS_STACK_STRING_CHAR_SIZE / sizeof(uint32_t))
#define OOPS_THREAD_SIZE               43
#define OOPS_FAIL_MARK                 0xCAFEBABA
#define OOPS_INIT_MARK                 0xDEADBEEF
#define OOPS_STACK_PICS                19
#define OOPS_STACK_SICS                (7 + 6)

typedef struct  st_oops_tag_info
{
    uint32_t tag;

    /* Application Mark */
    uint16_t mark;

    /* Dump Length */
    uint16_t length;

    /* Fault type */
    uint32_t mode;

    /* RTC Time Stamp */
    uint32_t rtc[2];
} oops_tag_type_t;

typedef struct st_monitor_info
{
    uint32_t fault_PC;
    uint8_t  fault_CNT;
    uint8_t  autoRebootStopFlag;
    uint8_t  reserved_26;
    uint8_t  reserved_27;
} monitor_info_t;

oops_tag_type_t g_bsp_mem_dump_oops_tag BSP_PLACE_IN_SECTION(BSP_SECTION_NOINIT);

uint32_t g_bsp_mem_dump_oops_stack_ctxt[OOPS_STACK_SIZE + 1 + OOPS_STACK_STRING_UINT_SIZE] BSP_PLACE_IN_SECTION(
    BSP_SECTION_NOINIT);
uint32_t g_bsp_mem_dump_oops_thread_ctxt[OOPS_THREAD_SIZE] BSP_PLACE_IN_SECTION(BSP_SECTION_NOINIT);
volatile monitor_info_t g_bsp_mem_dump_continuous_fault_info BSP_PLACE_IN_SECTION(BSP_SECTION_NOINIT);

volatile monitor_info_t * g_bsp_mem_dump_monitor_info_ptr = &g_bsp_mem_dump_continuous_fault_info;

char g_bsp_mem_dump_halt_color[COLOR_LEN];
char g_bsp_mem_dump_halt_color[COLOR_LEN];
char g_bsp_mem_dump_clear_color[COLOR_LEN];

/***********************************************************************************************************************
 * Private function prototypes
 **********************************************************************************************************************/

static void bsp_save_assert_string(const char * format, ...);
static void bsp_set_stop_auto_reboot(void);
static void bsp_clear_stop_auto_reboot(void);
static void bsp_increase_fault_count(void);
static void bsp_check_fault_pc(uint32_t faultPC);
static void bsp_display_oops_dump_thread_info(void);
static void bsp_print_fault_pc(void);

/***********************************************************************************************************************
 * Private global variables and functions
 **********************************************************************************************************************/

BSP_WEAK_REFERENCE uint16_t BSP_SaveOopsDumpThreadInfo (void) // freeRTOS port
{
    uint16_t info_length = 0;

    return info_length;
}

/*******************************************************************************************************************//**
 * Default implementation of assert for GCC.
 **********************************************************************************************************************/

void __assert_func (const char * file, int line, const char * func, const char * expr)
{
    const char * filename = strrchr(file, '/') ? strrchr(file, '/') + 1 : file;

    bsp_save_assert_string("%s:%d ASSERT(%s) @%s\n", filename, line, expr, func);

    __BKPT(0);
    while (1)
    {
        /* Do nothing. */
    }
}

static void bsp_set_stop_auto_reboot (void)
{
    g_bsp_mem_dump_monitor_info_ptr->autoRebootStopFlag = 1;
}

static void bsp_clear_stop_auto_reboot (void)
{
    g_bsp_mem_dump_monitor_info_ptr->autoRebootStopFlag = 0;
}

static void bsp_increase_fault_count (void)
{
    ++g_bsp_mem_dump_monitor_info_ptr->fault_CNT;
}

static void bsp_check_fault_pc (uint32_t faultPC)
{
    bsp_increase_fault_count();

    if ((BSP_GetFaultCount() >= MAX_FAULT) && (BSP_GetFaultPc() == faultPC))
    {
        BSP_SetFaultCount(0);
        BSP_SetFaultPc(0);
        bsp_set_stop_auto_reboot();

        return;
    }

    if (BSP_GetFaultPc() != faultPC)
    {
        BSP_SetFaultCount(1);
        BSP_SetFaultPc(faultPC);
    }

    bsp_clear_stop_auto_reboot();
}

static void bsp_save_assert_string (const char * format, ...)
{
    va_list args;
    va_start(args, format);

    // Safely format into the global buffer
    vsnprintf((char *) (&g_bsp_mem_dump_oops_stack_ctxt[OOPS_STACK_SIZE + 1]), OOPS_STACK_STRING_CHAR_SIZE, format,
              args);

    va_end(args);
    g_bsp_mem_dump_oops_stack_ctxt[OOPS_STACK_SIZE] = OOPS_STACK_STRING_CODE;
}

void BSP_SaveOopsDump (uint32_t * mspfile, uint32_t * pspfile, uint32_t mode)
{
    uint32_t i, dumpaddr;

    memset(g_bsp_mem_dump_oops_stack_ctxt, 0, sizeof(int) * OOPS_STACK_SIZE);

    /* R0-R3 */
    for (i = 0; i < 4; i++)
    {
        g_bsp_mem_dump_oops_stack_ctxt[i] = mspfile[i];
    }

    /* R4-R11 */
    for (i = 4; i < 12; i++)
    {
        g_bsp_mem_dump_oops_stack_ctxt[i] = pspfile[i - 4];
    }

    /* R12 */
    g_bsp_mem_dump_oops_stack_ctxt[12] = mspfile[4];

    /* SP */
    g_bsp_mem_dump_oops_stack_ctxt[13] = (uint32_t) (&(mspfile[8]));

    /* LR */
    g_bsp_mem_dump_oops_stack_ctxt[14] = mspfile[5];

    /* PC */
    g_bsp_mem_dump_oops_stack_ctxt[15] = mspfile[6];

    bsp_check_fault_pc(mspfile[6]);

    /* PSR */
    g_bsp_mem_dump_oops_stack_ctxt[16] = mspfile[7];

    /* EXC_RETURN */
    g_bsp_mem_dump_oops_stack_ctxt[17] = pspfile[8];

    dumpaddr = g_bsp_mem_dump_oops_stack_ctxt[13];

    for (i = 0; i < 48; i++)
    {
        if (dumpaddr <= (uint32_t) (&__ddsc_RAM_END))
        {
            g_bsp_mem_dump_oops_stack_ctxt[OOPS_STACK_PICS + i] = *((uint32_t *) (dumpaddr));
            dumpaddr = dumpaddr + sizeof(uint32_t);
        }
        else
        {
            g_bsp_mem_dump_oops_stack_ctxt[OOPS_STACK_PICS + i] = 0;
            break;
        }
    }

    g_bsp_mem_dump_oops_stack_ctxt[18] = i;

    g_bsp_mem_dump_oops_stack_ctxt[OOPS_STACK_PICS + 48 + 0] = SCB->SHCSR;
    g_bsp_mem_dump_oops_stack_ctxt[OOPS_STACK_PICS + 48 + 1] = SCB->CFSR;
    g_bsp_mem_dump_oops_stack_ctxt[OOPS_STACK_PICS + 48 + 2] = SCB->HFSR;
    g_bsp_mem_dump_oops_stack_ctxt[OOPS_STACK_PICS + 48 + 3] = SCB->DFSR;

    g_bsp_mem_dump_oops_stack_ctxt[OOPS_STACK_PICS + 48 + 4] = SCB->MMFAR;
    g_bsp_mem_dump_oops_stack_ctxt[OOPS_STACK_PICS + 48 + 5] = SCB->BFAR;
    g_bsp_mem_dump_oops_stack_ctxt[OOPS_STACK_PICS + 48 + 6] = SCB->AFSR;

    g_bsp_mem_dump_oops_tag.length  = sizeof(uint32_t) * (OOPS_STACK_PICS + 48 + OOPS_STACK_SICS);
    g_bsp_mem_dump_oops_tag.length += BSP_SaveOopsDumpThreadInfo();
    g_bsp_mem_dump_oops_tag.mode    = mode;

    if (g_bsp_mem_dump_oops_tag.tag != OOPS_INIT_MARK)
    {
        g_bsp_mem_dump_oops_tag.tag = OOPS_FAIL_MARK;
        BSP_DisplayOopsDump(NULL, NULL, NULL);
    }
    else
    {
        g_bsp_mem_dump_oops_tag.tag = OOPS_FAIL_MARK;

        SWRESET;
    }

    for (i = 0; i < 0x10000; i++)
    {
        __asm__ volatile (  "nop       \n");
    }
}

void BSP_InitOopsData (void)
{
    memset(&g_bsp_mem_dump_oops_tag, 0, sizeof(oops_tag_type_t));
    memset(g_bsp_mem_dump_oops_stack_ctxt, 0, sizeof(int) * OOPS_STACK_SIZE);
    g_bsp_mem_dump_oops_tag.tag = OOPS_INIT_MARK;
}

uint32_t BSP_GetFaultPc (void)
{
    return g_bsp_mem_dump_monitor_info_ptr->fault_PC;
}

void BSP_SetFaultPc (uint32_t pc)
{
    g_bsp_mem_dump_monitor_info_ptr->fault_PC = pc;
}

uint8_t BSP_GetFaultCount (void)
{
    return g_bsp_mem_dump_monitor_info_ptr->fault_CNT;
}

void BSP_SetFaultCount (uint8_t cnt)
{
    g_bsp_mem_dump_monitor_info_ptr->fault_CNT = cnt;
}

#ifndef TEST_HAS_OWN_EXCEPTION_HDL
void HardFault_HandlerC (unsigned long * exception_args)
{
    (void) exception_args;

    __asm("tst   lr, #4                \n"
          "ite   eq                    \n"
          "mrseq r0, msp               \n"
          "mrsne r0, psp               \n"
          "push  {r4-r11,lr}           \n"
          "mov   r1, sp                \n"
          "mov   r2, #0                \n"
          "bl    BSP_SaveOopsDump \n");
    while (1)
    {
    }
}

void MemManage_Handler (void)
{
    __asm("tst   lr, #4                \n"
          "ite   eq                    \n"
          "mrseq r0, msp               \n"
          "mrsne r0, psp               \n"
          "push  {r4-r11,lr}           \n"
          "mov   r1, sp                \n"
          "mov   r2, #1                \n"
          "bl    BSP_SaveOopsDump \n");
    while (1)
    {
    }
}

void BusFault_Handler (void)
{
    __asm("tst   lr, #4                \n"
          "ite   eq                    \n"
          "mrseq r0, msp               \n"
          "mrsne r0, psp               \n"
          "push  {r4-r11,lr}           \n"
          "mov   r1, sp                \n"
          "mov   r2, #2                \n"
          "bl    BSP_SaveOopsDump \n");
    while (1)
    {
    }
}

void UsageFault_Handler (void)
{
    __asm("tst   lr, #4                \n"
          "ite   eq                    \n"
          "mrseq r0, msp               \n"
          "mrsne r0, psp               \n"
          "push  {r4-r11,lr}           \n"
          "mov   r1, sp                \n"
          "mov   r2, #3                \n"
          "bl    BSP_SaveOopsDump \n");
    while (1)
    {
    }
}

#endif

static void bsp_print_fault_pc (void)
{
    printf(g_bsp_mem_dump_halt_color);
    printf("\n Stop auto--reboot (Fault_count:%d Fault_PC:0x%lx) \n", BSP_GetFaultCount(), BSP_GetFaultPc());
    printf(g_bsp_mem_dump_clear_color);
}

static void bsp_display_oops_dump_thread_info (void)
{
    uint32_t i, dumpaddr;

    printf("\n\n Current Thread\n");

    /* TaskName */
    if (strlen((char *) &g_bsp_mem_dump_oops_thread_ctxt[0]) > 0)
    {
        printf(g_bsp_mem_dump_halt_color);
        printf("\t Thread: %s\r\n", (char *) &g_bsp_mem_dump_oops_thread_ctxt[0]);
        printf(g_bsp_mem_dump_clear_color);
        printf("\t stack ptr : 0x%lx\n", g_bsp_mem_dump_oops_thread_ctxt[5]);
        printf("\t stack base: 0x%lx\n", g_bsp_mem_dump_oops_thread_ctxt[6]);
        printf("\t stack end : 0x%lx\n", g_bsp_mem_dump_oops_thread_ctxt[7]);
        printf("\t stack high: 0x%lx\n", g_bsp_mem_dump_oops_thread_ctxt[8]);
        printf("\t max usage : 0x%lx\n", g_bsp_mem_dump_oops_thread_ctxt[7] - g_bsp_mem_dump_oops_thread_ctxt[5] + 1);
        printf("\t suspend   : %08lx\n", g_bsp_mem_dump_oops_thread_ctxt[9]);

        printf("\n Thread Stack (%ld)", g_bsp_mem_dump_oops_thread_ctxt[10]);

        dumpaddr = ((uint32_t) &(g_bsp_mem_dump_oops_thread_ctxt[11]));

        for (i = 0; i < g_bsp_mem_dump_oops_thread_ctxt[10]; i++)
        {
            if (dumpaddr <= (uint32_t) (&__ddsc_RAM_END))
            {
                if ((i % 8) == 0)
                {
                    printf("\n [0x%08lx] : ", (g_bsp_mem_dump_oops_thread_ctxt[5] + (i * sizeof(uint32_t))));
                }

                printf("%08lX ", *((uint32_t *) dumpaddr));

                dumpaddr = dumpaddr + sizeof(uint32_t);
            }
            else
            {
                break;
            }
        }
    }
}

uint32_t * BSP_GetOopsThreadPtr (void)
{
    return &g_bsp_mem_dump_oops_thread_ctxt[0];
}

uint16_t BSP_GetOopsThreadSize (void)
{
    return (uint16_t) (sizeof(uint32_t) * OOPS_THREAD_SIZE);
}

void BSP_DisplayOopsDump (char * halt_color_ptr, char * bold_color_ptr, char * clear_color_ptr)
{
    const char * exception_title[] = {"Hard", "MPU", "BUS", "Usage", "Stack", "Wdog"};
    const char * reg_msg_format    = "\t%s :%08x%s";
    const char * regdelimiter[]    =
    {
        "R0 ", "R1 ",
        "R2 ", "R3 ","R4 ", "R5 ", "R6 ",  "R7 ",
        "R8 ", "R9 ","R10", "R11", "R12",  "SP ",
        "LR ", "PC ","PSR", "EXC"
    };
    const char * faultdelimiter[] =
    {
        "SHCSR", "CFSR ", "HFSR ", "DFSR ", "MMFAR", "BFAR ", "AFSR "
    };

    uint32_t i, dumpaddr;

    if (halt_color_ptr)
    {
        strncpy(g_bsp_mem_dump_halt_color, halt_color_ptr, COLOR_LEN - 1);
        g_bsp_mem_dump_halt_color[COLOR_LEN - 1] = '\0';
    }
    else
    {
        g_bsp_mem_dump_halt_color[0] = '\0';
    }

    if (bold_color_ptr)
    {
        strncpy(g_bsp_mem_dump_halt_color, bold_color_ptr, COLOR_LEN - 1);
        g_bsp_mem_dump_halt_color[COLOR_LEN - 1] = '\0';
    }
    else
    {
        g_bsp_mem_dump_halt_color[0] = '\0';
    }

    if (clear_color_ptr)
    {
        strncpy(g_bsp_mem_dump_clear_color, clear_color_ptr, COLOR_LEN - 1);
        g_bsp_mem_dump_clear_color[COLOR_LEN - 1] = '\0';
    }
    else
    {
        g_bsp_mem_dump_clear_color[0] = '\0';
    }

#if WIFI_CFG_WATCHDOG_SERVICE_ENABLE
    extern volatile uint32_t g_watchdog_service_w_nmi_event_data[9];

    if (0xDEADBEEFU == g_watchdog_service_w_nmi_event_data[0])
    {
        printf(g_bsp_mem_dump_halt_color);
        printf("\n [%s Fault Exception]\n", exception_title[5]);
        printf(g_bsp_mem_dump_clear_color);
        printf("\n Register-Dump\n");
        printf("\tR0  :%08lX,  R1  :%08lX,  R2  :%08lX,  R3  :%08lX\n",
               g_watchdog_service_w_nmi_event_data[1],
               g_watchdog_service_w_nmi_event_data[2],
               g_watchdog_service_w_nmi_event_data[3],
               g_watchdog_service_w_nmi_event_data[4]);

        printf("\tR12 :%08lX,  LR  :%08lX,  PC  :%08lX,  PSR :%08lX\n",
               g_watchdog_service_w_nmi_event_data[5],
               g_watchdog_service_w_nmi_event_data[6],
               g_watchdog_service_w_nmi_event_data[7],
               g_watchdog_service_w_nmi_event_data[8]);

        bsp_display_oops_dump_thread_info();
        printf("\n");

        g_watchdog_service_w_nmi_event_data[0] = 0U;

        return;
    }
#endif

    if (g_bsp_mem_dump_oops_tag.tag == OOPS_FAIL_MARK)
    {
        g_bsp_mem_dump_oops_tag.tag = 0;
    }
    else
    {
        return;
    }

    printf(g_bsp_mem_dump_halt_color);
    printf("\n [%s Fault Exception]\n", exception_title[g_bsp_mem_dump_oops_tag.mode]);
    printf(g_bsp_mem_dump_clear_color);

    printf("\n Register-Dump\n");
    for (i = 0; i < ARRAY_SIZE(regdelimiter); i++)
    {
        printf(reg_msg_format, regdelimiter[i], g_bsp_mem_dump_oops_stack_ctxt[i], ((i % 4 == 3) ? "\n" : ","));
    }

    printf("\n Fault Status\n");
    for (i = 0; i < ARRAY_SIZE(faultdelimiter); i++)
    {
        printf(reg_msg_format, faultdelimiter[i], g_bsp_mem_dump_oops_stack_ctxt[OOPS_STACK_PICS + 48 + i],
               ((i % 3 == 2) ? "\r\n" : ","));
    }

    printf("\n Stack-Dump (%ld)", g_bsp_mem_dump_oops_stack_ctxt[18]);
    dumpaddr = ((uint32_t) &(g_bsp_mem_dump_oops_stack_ctxt[OOPS_STACK_PICS]));

    for (i = 0; i < g_bsp_mem_dump_oops_stack_ctxt[18]; i++)
    {
        if (dumpaddr <= (uint32_t) (&__ddsc_RAM_END))
        {
            if ((i % 8) == 0)
            {
                printf("\r\n [0x%08lx] : "
                       ,
                       (g_bsp_mem_dump_oops_stack_ctxt[13] + (i * sizeof(uint32_t))));
            }

            printf("%08lX ", *((uint32_t *) dumpaddr));

            dumpaddr = dumpaddr + sizeof(uint32_t);
        }
        else
        {
            break;
        }
    }

    /* Dump thread info */
    bsp_display_oops_dump_thread_info();

    printf("\n");
    bsp_print_fault_pc();
    printf("\n");

    if (OOPS_STACK_STRING_CODE == g_bsp_mem_dump_oops_stack_ctxt[OOPS_STACK_SIZE])
    {
        printf("\n Assert at\n");
        printf("\t%s\n", (char *) (&g_bsp_mem_dump_oops_stack_ctxt[OOPS_STACK_SIZE + 1]));
        g_bsp_mem_dump_oops_stack_ctxt[OOPS_STACK_SIZE] = 0;
    }
}
