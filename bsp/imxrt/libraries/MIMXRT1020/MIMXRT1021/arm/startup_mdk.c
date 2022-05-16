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

#include "linker_config.h"
#include "safety_config.h"

/*******************************************************************************
* Prototypes
******************************************************************************/
void common_startup(void);
void write_vtor(int);

/*******************************************************************************
* Variables
*******************************************************************************/
extern unsigned int Load$$RW_IRAM1$$RW$$Base;
extern unsigned int Load$$RW_IRAM1$$RW$$Limit;
extern unsigned int Image$$RW_IRAM1$$RW$$Base;

extern unsigned int Image$$RW_IRAM1$$ZI$$Base;
extern unsigned int Image$$RW_IRAM1$$ZI$$Limit;

extern unsigned int Load$$SafetyRam_region$$Base;
extern unsigned int Load$$SafetyRam_region$$Limit;
extern unsigned int Image$$SafetyRam_region$$Base;

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
    write_vtor((uint32_t)__VECTOR_TABLE);

#if (__FPU_PRESENT)
    SCB->CPACR |= ((3UL << 10*2) | (3UL << 11*2));    /* set CP10, CP11 Full Access */
#endif

    volatile unsigned int ui32RW_data__address      = (uint32_t) &Load$$RW_IRAM1$$RW$$Base;    /* in IAR as __section_begin(".data_init") */
    volatile unsigned int ui32RW_data__end          = (uint32_t) &Load$$RW_IRAM1$$RW$$Limit;   /* in IAR as __section_end(".data_init")*/
    volatile unsigned int ui32RW_data__image        = (uint32_t) &Image$$RW_IRAM1$$RW$$Base;   /* in IAR as __section_begin(".data") */

    volatile unsigned int ui32ZI_data__image        = (uint32_t) &Image$$RW_IRAM1$$ZI$$Base;   /* in IAR as __section_begin(".bss") */
    volatile unsigned int ui32ZI_data__image_end    = (uint32_t) &Image$$RW_IRAM1$$ZI$$Limit;  /* in IAR as __section_end(".bss"); */

    volatile unsigned int ui32safety_ram_data__address = (uint32_t) &Load$$SafetyRam_region$$Base;    /* in IAR as __section_begin(".safety_ram_init") */
    volatile unsigned int ui32safety_ram_data__end     = (uint32_t) &Load$$SafetyRam_region$$Limit;   /* in IAR as __section_end(".safety_ram_init")*/
    volatile unsigned int ui32safety_ram_data__image   = (uint32_t) &Image$$SafetyRam_region$$Base;   /* in IAR as __section_begin(".safety_ram") */

    /* Declare a counter we'll use in all of the copy loops */
    uint32_t  SectionLen;
    uint32_t *data_ram;
    uint32_t *data_rom;
    uint32_t *data_rom_end;

    /* Get the addresses for the .data section (initialized data section) */
    data_ram = (uint32_t *)ui32RW_data__image;     /* __section_begin(".data") */
    data_rom = (uint32_t *)ui32RW_data__address;   /* __section_begin(".data_init") */
    data_rom_end = (uint32_t *)ui32RW_data__end;   /* __section_end(".data_init") */

    /* Copy initialized data from ROM to RAM */
    SectionLen = data_rom_end - data_rom; /* This case in number of adress*/
    while (SectionLen--)
    {
        *data_ram++ = *data_rom++;
#ifdef WATCHDOG_ON
        Watchdog_refresh;
#endif
    }

    /* Get the addresses for the .safety_ram section (initialized safety_ram section) */
    data_ram = (uint32_t *)ui32safety_ram_data__image;     /* __section_begin(".safety_ram") */
    data_rom = (uint32_t *)ui32safety_ram_data__address;   /* __section_begin(".safety_ram_init") */
    data_rom_end = (uint32_t *)ui32safety_ram_data__end;   /* __section_end(".safety_ram_init") */

    /* Copy initialized data from ROM to RAM */
    SectionLen = data_rom_end - data_rom; /* This case in number of adress*/
    while (SectionLen--)
    {
        *data_ram++ = *data_rom++;
#ifdef WATCHDOG_ON
        Watchdog_refresh;
#endif
    }

    /* Get the addresses for the .bss section (zero-initialized data) */
    uint32_t *bss_start, *bss_end;

    /* Get the addresses for the .bss section (zero-initialized data) */
    bss_start = (uint32_t *)ui32ZI_data__image;    /* __section_begin(".bss") */
    bss_end =   (uint32_t *)ui32ZI_data__image_end;  /* __section_end(".bss") */

    SectionLen  = bss_end - bss_start;
    while (SectionLen--)
    {
        *bss_start++ = 0;
#ifdef WATCHDOG_ON
        Watchdog_refresh;
#endif
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
