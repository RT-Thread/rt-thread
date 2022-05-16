/*******************************************************************************
*
* Copyright 2013 - 2016, Freescale Semiconductor, Inc.
* Copyright 2016-2019 NXP
*
* This software is owned or controlled by NXP and may only be used
* strictly in accordance with the applicable license terms.  By expressly
* accepting such terms or by downloading, installing, activating and/or
* otherwise using the software, you are agreeing that you have read, and
* that you agree to comply with and are bound by, such license terms.  If
* you do not agree to be bound by the applicable license terms, then you
* may not retain, install, activate or otherwise use the software.
*
*
*******************************************************************************/

#include "safety_config.h"

extern unsigned int __data_section_table;
extern unsigned int __data_section_table_end;   //before BSS
extern unsigned int __safety_ram_section_table;
extern unsigned int __safety_ram_section_table_end;
extern unsigned int __bss_section_table;
extern unsigned int __bss_section_table_end;

/*******************************************************************************
* Prototypes
******************************************************************************/
void common_startup(void);
void write_vtor(int);

/*******************************************************************************
* Variables
*******************************************************************************/

/*******************************************************************************
* Code
******************************************************************************/
/*!
* @brief Initialization of RAM sections.
*
* @param void
*
* @return None
*/
void common_startup(void)
{
    /* Set the IVT address in SCB */
    extern uint32_t __VECTOR_TABLE[];
    write_vtor((uint32_t)__VECTOR_TABLE);

#if (__FPU_PRESENT)
    SCB->CPACR |= ((3UL << 10*2) | (3UL << 11*2));    /* set CP10, CP11 Full Access */
#endif

    /* Declare a counter we'll use in all of the copy loops */
    uint32_t  SectionLen;
    uint32_t *data_ram;
    uint32_t *data_rom;

    uint32_t *SectionTableAddr;
    /* Load base address of Global Section Table*/
    SectionTableAddr = &__data_section_table; /*This variables point to   Global Section Table defined in Safety_common_XX_Debug.ld, due to this, we will increment this pointer alter*/
    /* This different approach is due to linker. We know only start, load  and end address of each section in linker. See "Safety_common_XX_Debug.ld  On lines 26 - 40.
    * This is different from IAR linker, where we know start and end address of whole DATA section. in GCC linker we have for each region own section DATA and BSS, as you can see in files **_Debug.ld*/

    /* Copy the data sections from flash to SRAM.*/
    while (SectionTableAddr < &__data_section_table_end)
    {
        data_rom = (uint32_t*) *SectionTableAddr++; /*Load address*/
        data_ram = (uint32_t*) *SectionTableAddr++; /*Address*/
        SectionLen = *SectionTableAddr++; /* Length - this case in BYTES*/
        /*This wihle cycle ensures to read all region of data section, all data sections are described in **_Debug.ld file*/
        for (uint32_t loop = 0; loop < SectionLen; loop = loop + 4)
        {
            *data_ram++ = *data_rom++;
#ifdef WATCHDOG_ON
            Watchdog_refresh;
#endif
        }
    }

    /* At this point, SectionTableAddr = &__safety_ram_section_table;*/
    /* Copy the safety_ram section from flash to SRAM.*/
    while (SectionTableAddr < &__safety_ram_section_table_end)
    {
        data_rom = (uint32_t*) *SectionTableAddr++; /*Load address*/
        data_ram = (uint32_t*) *SectionTableAddr++; /*Address*/
        SectionLen = *SectionTableAddr++; /* Length - this case in BYTES*/
        /*This wihle cycle ensures to read all region of data section, all data sections are described in **_Debug.ld file*/
        for (uint32_t loop = 0; loop < SectionLen; loop = loop + 4)
        {
            *data_ram++ = *data_rom++;
#ifdef WATCHDOG_ON
            Watchdog_refresh;
#endif
        }
    }

    /* Get the addresses for the .bss section (zero-initialized data) */
    uint32_t *bss_start;

    /* At this point, SectionTableAddr = &__bss_section_table;*/
    /* This different approach due to linker. We know only start and end adress of each section in linker. See "Safety_common_XX_Debug.ld */
    /* Zero fill the bss segment*/
    while (SectionTableAddr < &__bss_section_table_end) {
        bss_start = (uint32_t*) *SectionTableAddr++;
        SectionLen = *SectionTableAddr++;
        for (uint32_t loop = 0; loop < SectionLen; loop = loop + 4)
        {   *bss_start++ = 0;
#ifdef WATCHDOG_ON
        Watchdog_refresh;
#endif
        }
    }

#ifdef WATCHDOG_ON
    Watchdog_refresh;
#endif
}

/*!
* @brief write to VTOR register
*
* @param void
*
* @return None
*/
void write_vtor(int vtor)
{
    unsigned long *pVTOR = (unsigned long*)0xE000ED08;
    *pVTOR = vtor;
}
