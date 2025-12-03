/*
                  Linker File for Renesas FSP
*/


/* generated memory regions file - do not edit */
RAM_START = 0x22000000;
RAM_LENGTH = 0x174000;
FLASH_START = 0x02000000;
FLASH_LENGTH = 0x00100000;
DATA_FLASH_START = 0x27000000;
DATA_FLASH_LENGTH = 0x00000000;
SDRAM_START = 0x68000000;
SDRAM_LENGTH = 0x08000000;
OSPI0_CS0_START = 0x80000000;
OSPI0_CS0_LENGTH = 0x10000000;
OSPI0_CS1_START = 0x90000000;
OSPI0_CS1_LENGTH = 0x10000000;
OSPI1_CS0_START = 0x70000000;
OSPI1_CS0_LENGTH = 0x08000000;
OSPI1_CS1_START = 0x78000000;
OSPI1_CS1_LENGTH = 0x08000000;
OPTION_SETTING_OFS0_START = 0x02c9f040;
OPTION_SETTING_OFS0_LENGTH = 0x00000004;
OPTION_SETTING_OFS2_START = 0x02c9f044;
OPTION_SETTING_OFS2_LENGTH = 0x00000004;
OPTION_SETTING_SAS_START = 0x02c9f074;
OPTION_SETTING_SAS_LENGTH = 0x00000004;
OPTION_SETTING_OFS1_START = 0x12c9f4c0;
OPTION_SETTING_OFS1_LENGTH = 0x00000004;
OPTION_SETTING_OFS1_SEC_START = 0x02c9f0c0;
OPTION_SETTING_OFS1_SEC_LENGTH = 0x00000004;
OPTION_SETTING_OFS1_SEL_START = 0x02c9f120;
OPTION_SETTING_OFS1_SEL_LENGTH = 0x00000004;
OPTION_SETTING_OFS3_START = 0x12c9f4c4;
OPTION_SETTING_OFS3_LENGTH = 0x00000004;
OPTION_SETTING_OFS3_SEC_START = 0x02c9f0c4;
OPTION_SETTING_OFS3_SEC_LENGTH = 0x00000004;
OPTION_SETTING_OFS3_SEL_START = 0x02c9f124;
OPTION_SETTING_OFS3_SEL_LENGTH = 0x00000004;
OPTION_SETTING_BPS_START = 0x12c9f600;
OPTION_SETTING_BPS_LENGTH = 0x00000080;
OPTION_SETTING_BPS_SEC_START = 0x02c9f200;
OPTION_SETTING_BPS_SEC_LENGTH = 0x00000080;
OPTION_SETTING_OTP_PBPS_SEC_START = 0x02e07700;
OPTION_SETTING_OTP_PBPS_SEC_LENGTH = 0x00000080;
OPTION_SETTING_OTP_PBPS_START = 0x12e07780;
OPTION_SETTING_OTP_PBPS_LENGTH = 0x00000080;
ITCM_START = 0x00000000;
ITCM_LENGTH = 0x00020000;
DTCM_START = 0x20000000;
DTCM_LENGTH = 0x00020000;


MEMORY
{
    RAM (rwx) : ORIGIN = RAM_START, LENGTH = RAM_LENGTH
    FLASH (rx) : ORIGIN = FLASH_START, LENGTH = FLASH_LENGTH
    DATA_FLASH (rx) : ORIGIN = DATA_FLASH_START, LENGTH = DATA_FLASH_LENGTH
    SDRAM (rwx) : ORIGIN = SDRAM_START, LENGTH = SDRAM_LENGTH
    OSPI0_CS0 (rwx) : ORIGIN = OSPI0_CS0_START, LENGTH = OSPI0_CS0_LENGTH
    OSPI0_CS1 (rx) : ORIGIN = OSPI0_CS1_START, LENGTH = OSPI0_CS1_LENGTH
    OSPI1_CS0 (rwx) : ORIGIN = OSPI1_CS0_START, LENGTH = OSPI1_CS0_LENGTH
    OSPI1_CS1 (rx) : ORIGIN = OSPI1_CS1_START, LENGTH = OSPI1_CS1_LENGTH
    OPTION_SETTING_OFS0 (r) : ORIGIN = OPTION_SETTING_OFS0_START, LENGTH = OPTION_SETTING_OFS0_LENGTH
    OPTION_SETTING_OFS2 (r) : ORIGIN = OPTION_SETTING_OFS2_START, LENGTH = OPTION_SETTING_OFS2_LENGTH
    OPTION_SETTING_SAS (r) : ORIGIN = OPTION_SETTING_SAS_START, LENGTH = OPTION_SETTING_SAS_LENGTH
    OPTION_SETTING_OFS1 (r) : ORIGIN = OPTION_SETTING_OFS1_START, LENGTH = OPTION_SETTING_OFS1_LENGTH
    OPTION_SETTING_OFS1_SEC (r) : ORIGIN = OPTION_SETTING_OFS1_SEC_START, LENGTH = OPTION_SETTING_OFS1_SEC_LENGTH
    OPTION_SETTING_OFS1_SEL (r) : ORIGIN = OPTION_SETTING_OFS1_SEL_START, LENGTH = OPTION_SETTING_OFS1_SEL_LENGTH
    OPTION_SETTING_OFS3 (r) : ORIGIN = OPTION_SETTING_OFS3_START, LENGTH = OPTION_SETTING_OFS3_LENGTH
    OPTION_SETTING_OFS3_SEC (r) : ORIGIN = OPTION_SETTING_OFS3_SEC_START, LENGTH = OPTION_SETTING_OFS3_SEC_LENGTH
    OPTION_SETTING_OFS3_SEL (r) : ORIGIN = OPTION_SETTING_OFS3_SEL_START, LENGTH = OPTION_SETTING_OFS3_SEL_LENGTH
    OPTION_SETTING_BPS (r) : ORIGIN = OPTION_SETTING_BPS_START, LENGTH = OPTION_SETTING_BPS_LENGTH
    OPTION_SETTING_BPS_SEC (r) : ORIGIN = OPTION_SETTING_BPS_SEC_START, LENGTH = OPTION_SETTING_BPS_SEC_LENGTH
    OPTION_SETTING_OTP_PBPS_SEC (r) : ORIGIN = OPTION_SETTING_OTP_PBPS_SEC_START, LENGTH = OPTION_SETTING_OTP_PBPS_SEC_LENGTH
    OPTION_SETTING_OTP_PBPS (r) : ORIGIN = OPTION_SETTING_OTP_PBPS_START, LENGTH = OPTION_SETTING_OTP_PBPS_LENGTH
    ITCM (rwx) : ORIGIN = ITCM_START, LENGTH = ITCM_LENGTH
    DTCM (rwx) : ORIGIN = DTCM_START, LENGTH = DTCM_LENGTH
}

/* code entry point...need to define to keep crt0 _start out */
ENTRY( Reset_Handler)
/* Library configurations */
GROUP(libgcc.a libc.a libm.a)

SECTIONS
{
	
	
    /***** OSPI0_CS1 memory section allocations ******/
    .ospi0_cs1.startof (READONLY) :
    {
        __ddsc_OSPI0_CS1_START = .;

    }> OSPI0_CS1
    /***** SDRAM memory section allocations ******/
    .sdram.startof :
    {
        __ddsc_SDRAM_START = .;

    }> SDRAM
    /* sdram initialized from ospi0_cs1 */
    __sdram_from_ospi0_cs1$$ : ALIGN(4)
    {
        __sdram_from_ospi0_cs1$$Base = .;__sdram_from_ospi0_cs1$$Load = LOADADDR(__sdram_from_ospi0_cs1$$);
        /* section.sdram.from_ospi0_cs1 */
        *(.sdram_from_ospi0_cs1)
        /* section.sdram.code_from_ospi0_cs1 */
        *(.sdram_code_from_ospi0_cs1)
        __sdram_from_ospi0_cs1$$Limit = .;
    }> SDRAM AT > OSPI0_CS1

    /***** OSPI0_CS0 memory section allocations ******/
    .ospi0_cs0.startof :
    {
        __ddsc_OSPI0_CS0_START = .;

    }> OSPI0_CS0
    /* ospi0_cs0 initialized from ospi0_cs1 */
    __ospi0_cs0_from_ospi0_cs1$$ : ALIGN(4)
    {
        __ospi0_cs0_from_ospi0_cs1$$Base = .;__ospi0_cs0_from_ospi0_cs1$$Load = LOADADDR(__ospi0_cs0_from_ospi0_cs1$$);
        /* section.ospi0_cs0.from_ospi0_cs1 */
        *(.ospi0_cs0_from_ospi0_cs1)
        /* section.ospi0_cs0.code_from_ospi0_cs1 */
        *(.ospi0_cs0_code_from_ospi0_cs1)
        __ospi0_cs0_from_ospi0_cs1$$Limit = .;
    }> OSPI0_CS0 AT > OSPI0_CS1

    /***** OSPI1_CS0 memory section allocations ******/
    .ospi1_cs0.startof :
    {
        __ddsc_OSPI1_CS0_START = .;

    }> OSPI1_CS0
    /* ospi1_cs0 initialized from ospi0_cs1 */
    __ospi1_cs0_from_ospi0_cs1$$ : ALIGN(4)
    {
        __ospi1_cs0_from_ospi0_cs1$$Base = .;__ospi1_cs0_from_ospi0_cs1$$Load = LOADADDR(__ospi1_cs0_from_ospi0_cs1$$);
        /* section.ospi1_cs0.from_ospi0_cs1 */
        *(.ospi1_cs0_from_ospi0_cs1)
        /* section.ospi1_cs0.code_from_ospi0_cs1 */
        *(.ospi1_cs0_code_from_ospi0_cs1)
        __ospi1_cs0_from_ospi0_cs1$$Limit = .;
    }> OSPI1_CS0 AT > OSPI0_CS1

    /***** ITCM memory section allocations ******/
    .itcm.startof :
    {
        __ddsc_ITCM_START = .;

    }> ITCM
    /* itcm initialized from ospi0_cs1 */
    __itcm_from_ospi0_cs1$$ : ALIGN(8)
    {
        __itcm_from_ospi0_cs1$$Base = .;__itcm_from_ospi0_cs1$$Load = LOADADDR(__itcm_from_ospi0_cs1$$);
        /* section.itcm.from_ospi0_cs1 */
        *(.itcm_from_ospi0_cs1)
        /* section.itcm.code_from_ospi0_cs1 */
        *(.itcm_code_from_ospi0_cs1)
        . = ALIGN(8);
        __itcm_from_ospi0_cs1$$Limit = .;
    }> ITCM AT > OSPI0_CS1

    /***** DTCM memory section allocations ******/
    .dtcm.startof :
    {
        __ddsc_DTCM_START = .;

    }> DTCM
    /* dtcm initialized from ospi0_cs1 */
    __dtcm_from_ospi0_cs1$$ : ALIGN(8)
    {
        __dtcm_from_ospi0_cs1$$Base = .;__dtcm_from_ospi0_cs1$$Load = LOADADDR(__dtcm_from_ospi0_cs1$$);
        /* section.dtcm.from_ospi0_cs1 */
        *(.dtcm_from_ospi0_cs1)
        /* section.dtcm.code_from_ospi0_cs1 */
        *(.dtcm_code_from_ospi0_cs1)
        . = ALIGN(8);
        __dtcm_from_ospi0_cs1$$Limit = .;
    }> DTCM AT > OSPI0_CS1

    /***** RAM memory section allocations ******/
    .ram.startof :
    {
        __ddsc_RAM_START = .;

    }> RAM
    __ram_dtc_vector$$ (NOLOAD) :
    {
        __ram_dtc_vector$$Base = .;
        *(.fsp_dtc_vector_table)
        __ram_dtc_vector$$Limit = .;
    }> RAM
    /* ram initialized from ospi0_cs1 */
    __ram_from_ospi0_cs1$$ : ALIGN(4)
    {
        __ram_from_ospi0_cs1$$Base = .;__ram_from_ospi0_cs1$$Load = LOADADDR(__ram_from_ospi0_cs1$$);
        /* section.ram.from_ospi0_cs1 */
        *(.ram_from_ospi0_cs1)
        /* section.ram.code_from_ospi0_cs1 */
        *(.ram_code_from_ospi0_cs1)
        __ram_from_ospi0_cs1$$Limit = .;
    }> RAM AT > OSPI0_CS1

    __ospi0_cs1_readonly$$ (READONLY) :
    {
        __ospi0_cs1_readonly$$Base = .;
        /* section.ospi0_cs1.readonly */
        *(.ospi0_cs1)
        /* section.ospi0_cs1.code */
        *(.ospi0_cs1_code)
        __ospi0_cs1_readonly$$Limit = .;
    }> OSPI0_CS1
    __ospi0_cs1_noinit$$ (NOLOAD) :
    {
        __ospi0_cs1_noinit$$Base = .;
        /* section.ospi0_cs1.noinit */
        *(.ospi0_cs1_noinit)
        __ospi0_cs1_noinit$$Limit = .;
    }> OSPI0_CS1
    .ospi0_cs1.endof ALIGN(.,512) (READONLY) :
    {
        __ddsc_OSPI0_CS1_END = .;

    }> OSPI0_CS1

    /***** OSPI1_CS1 memory section allocations ******/
    .ospi1_cs1.startof (READONLY) :
    {
        __ddsc_OSPI1_CS1_START = .;

    }> OSPI1_CS1
    /***** SDRAM memory section allocations ******/
    /* sdram initialized from ospi1_cs1 */
    __sdram_from_ospi1_cs1$$ : ALIGN(4)
    {
        __sdram_from_ospi1_cs1$$Base = .;__sdram_from_ospi1_cs1$$Load = LOADADDR(__sdram_from_ospi1_cs1$$);
        /* section.sdram.from_ospi1_cs1 */
        *(.sdram_from_ospi1_cs1)
        /* section.sdram.code_from_ospi1_cs1 */
        *(.sdram_code_from_ospi1_cs1)
        __sdram_from_ospi1_cs1$$Limit = .;
    }> SDRAM AT > OSPI1_CS1

    /***** OSPI0_CS0 memory section allocations ******/
    /* ospi0_cs0 initialized from ospi1_cs1 */
    __ospi0_cs0_from_ospi1_cs1$$ : ALIGN(4)
    {
        __ospi0_cs0_from_ospi1_cs1$$Base = .;__ospi0_cs0_from_ospi1_cs1$$Load = LOADADDR(__ospi0_cs0_from_ospi1_cs1$$);
        /* section.ospi0_cs0.from_ospi1_cs1 */
        *(.ospi0_cs0_from_ospi1_cs1)
        /* section.ospi0_cs0.code_from_ospi1_cs1 */
        *(.ospi0_cs0_code_from_ospi1_cs1)
        __ospi0_cs0_from_ospi1_cs1$$Limit = .;
    }> OSPI0_CS0 AT > OSPI1_CS1

    /***** OSPI1_CS0 memory section allocations ******/
    /* ospi1_cs0 initialized from ospi1_cs1 */
    __ospi1_cs0_from_ospi1_cs1$$ : ALIGN(4)
    {
        __ospi1_cs0_from_ospi1_cs1$$Base = .;__ospi1_cs0_from_ospi1_cs1$$Load = LOADADDR(__ospi1_cs0_from_ospi1_cs1$$);
        /* section.ospi1_cs0.from_ospi1_cs1 */
        *(.ospi1_cs0_from_ospi1_cs1)
        /* section.ospi1_cs0.code_from_ospi1_cs1 */
        *(.ospi1_cs0_code_from_ospi1_cs1)
        __ospi1_cs0_from_ospi1_cs1$$Limit = .;
    }> OSPI1_CS0 AT > OSPI1_CS1

    /***** ITCM memory section allocations ******/
    /* itcm initialized from ospi1_cs1 */
    __itcm_from_ospi1_cs1$$ : ALIGN(8)
    {
        __itcm_from_ospi1_cs1$$Base = .;__itcm_from_ospi1_cs1$$Load = LOADADDR(__itcm_from_ospi1_cs1$$);
        /* section.itcm.from_ospi1_cs1 */
        *(.itcm_from_ospi1_cs1)
        /* section.itcm.code_from_ospi1_cs1 */
        *(.itcm_code_from_ospi1_cs1)
        . = ALIGN(8);
        __itcm_from_ospi1_cs1$$Limit = .;
    }> ITCM AT > OSPI1_CS1

    /***** DTCM memory section allocations ******/
    /* dtcm initialized from ospi1_cs1 */
    __dtcm_from_ospi1_cs1$$ : ALIGN(8)
    {
        __dtcm_from_ospi1_cs1$$Base = .;__dtcm_from_ospi1_cs1$$Load = LOADADDR(__dtcm_from_ospi1_cs1$$);
        /* section.dtcm.from_ospi1_cs1 */
        *(.dtcm_from_ospi1_cs1)
        /* section.dtcm.code_from_ospi1_cs1 */
        *(.dtcm_code_from_ospi1_cs1)
        . = ALIGN(8);
        __dtcm_from_ospi1_cs1$$Limit = .;
    }> DTCM AT > OSPI1_CS1

    /***** RAM memory section allocations ******/
    /* ram initialized from ospi1_cs1 */
    __ram_from_ospi1_cs1$$ : ALIGN(4)
    {
        __ram_from_ospi1_cs1$$Base = .;__ram_from_ospi1_cs1$$Load = LOADADDR(__ram_from_ospi1_cs1$$);
        /* section.ram.from_ospi1_cs1 */
        *(.ram_from_ospi1_cs1)
        /* section.ram.code_from_ospi1_cs1 */
        *(.ram_code_from_ospi1_cs1)
        __ram_from_ospi1_cs1$$Limit = .;
    }> RAM AT > OSPI1_CS1

    __ospi1_cs1_readonly$$ (READONLY) :
    {
        __ospi1_cs1_readonly$$Base = .;
        /* section.ospi1_cs1.readonly */
        *(.ospi1_cs1)
        /* section.ospi1_cs1.code */
        *(.ospi1_cs1_code)
        __ospi1_cs1_readonly$$Limit = .;
    }> OSPI1_CS1
    __ospi1_cs1_noinit$$ (NOLOAD) :
    {
        __ospi1_cs1_noinit$$Base = .;
        /* section.ospi1_cs1.noinit */
        *(.ospi1_cs1_noinit)
        __ospi1_cs1_noinit$$Limit = .;
    }> OSPI1_CS1
    .ospi1_cs1.endof ALIGN(.,512) (READONLY) :
    {
        __ddsc_OSPI1_CS1_END = .;

    }> OSPI1_CS1

    /***** DATA_FLASH memory section allocations ******/
    .data_flash.startof (READONLY) :
    {
        __ddsc_DATA_FLASH_START = .;

    }> DATA_FLASH
    /***** SDRAM memory section allocations ******/
    /* sdram initialized from data_flash */
    __sdram_from_data_flash$$ : ALIGN(4)
    {
        __sdram_from_data_flash$$Base = .;__sdram_from_data_flash$$Load = LOADADDR(__sdram_from_data_flash$$);
        /* section.sdram.from_data_flash */
        *(.sdram_from_data_flash)
        /* section.sdram.code_from_data_flash */
        *(.sdram_code_from_data_flash)
        __sdram_from_data_flash$$Limit = .;
    }> SDRAM AT > DATA_FLASH

    /***** OSPI0_CS0 memory section allocations ******/
    /* ospi0_cs0 initialized from data_flash */
    __ospi0_cs0_from_data_flash$$ : ALIGN(4)
    {
        __ospi0_cs0_from_data_flash$$Base = .;__ospi0_cs0_from_data_flash$$Load = LOADADDR(__ospi0_cs0_from_data_flash$$);
        /* section.ospi0_cs0.from_data_flash */
        *(.ospi0_cs0_from_data_flash)
        /* section.ospi0_cs0.code_from_data_flash */
        *(.ospi0_cs0_code_from_data_flash)
        __ospi0_cs0_from_data_flash$$Limit = .;
    }> OSPI0_CS0 AT > DATA_FLASH

    /***** OSPI1_CS0 memory section allocations ******/
    /* ospi1_cs0 initialized from data_flash */
    __ospi1_cs0_from_data_flash$$ : ALIGN(4)
    {
        __ospi1_cs0_from_data_flash$$Base = .;__ospi1_cs0_from_data_flash$$Load = LOADADDR(__ospi1_cs0_from_data_flash$$);
        /* section.ospi1_cs0.from_data_flash */
        *(.ospi1_cs0_from_data_flash)
        /* section.ospi1_cs0.code_from_data_flash */
        *(.ospi1_cs0_code_from_data_flash)
        __ospi1_cs0_from_data_flash$$Limit = .;
    }> OSPI1_CS0 AT > DATA_FLASH

    /***** ITCM memory section allocations ******/
    /* itcm initialized from data_flash */
    __itcm_from_data_flash$$ : ALIGN(8)
    {
        __itcm_from_data_flash$$Base = .;__itcm_from_data_flash$$Load = LOADADDR(__itcm_from_data_flash$$);
        /* section.itcm.from_data_flash */
        *(.itcm_from_data_flash)
        /* section.itcm.code_from_data_flash */
        *(.itcm_code_from_data_flash)
        . = ALIGN(8);
        __itcm_from_data_flash$$Limit = .;
    }> ITCM AT > DATA_FLASH

    /***** DTCM memory section allocations ******/
    /* dtcm initialized from data_flash */
    __dtcm_from_data_flash$$ : ALIGN(8)
    {
        __dtcm_from_data_flash$$Base = .;__dtcm_from_data_flash$$Load = LOADADDR(__dtcm_from_data_flash$$);
        /* section.dtcm.from_data_flash */
        *(.dtcm_from_data_flash)
        /* section.dtcm.code_from_data_flash */
        *(.dtcm_code_from_data_flash)
        . = ALIGN(8);
        __dtcm_from_data_flash$$Limit = .;
    }> DTCM AT > DATA_FLASH

    /***** RAM memory section allocations ******/
    /* ram initialized from data_flash */
    __ram_from_data_flash$$ : ALIGN(4)
    {
        __ram_from_data_flash$$Base = .;__ram_from_data_flash$$Load = LOADADDR(__ram_from_data_flash$$);
        /* section.ram.from_data_flash */
        *(.ram_from_data_flash)
        /* section.ram.code_from_data_flash */
        *(.ram_code_from_data_flash)
        __ram_from_data_flash$$Limit = .;
    }> RAM AT > DATA_FLASH

    __data_flash_readonly$$ (READONLY) :
    {
        __data_flash_readonly$$Base = .;
        /* section.data_flash.readonly */
        *(.data_flash)
        /* section.data_flash.code */
        *(.data_flash_code)
        __data_flash_readonly$$Limit = .;
    }> DATA_FLASH
    __data_flash_noinit$$ (NOLOAD) :
    {
        __data_flash_noinit$$Base = .;
        /* section.data_flash.noinit */
        *(.data_flash_noinit)
        __data_flash_noinit$$Limit = .;
    }> DATA_FLASH
    .data_flash.endof ALIGN(.,1024) (READONLY) :
    {
        __ddsc_DATA_FLASH_END = .;

    }> DATA_FLASH

    /***** FLASH memory section allocations ******/
    .flash.startof (READONLY) :
    {
        __ddsc_FLASH_START = .;

    }> FLASH
    /* MCU vector table */
    __flash_vectors$$ (READONLY) :
    {
        __flash_vectors$$Base = .; _VECTORS = .;
        KEEP(*(.fixed_vectors))
        KEEP(*(.application_vectors))
        __flash_vectors$$Limit = .;
        
        /* section information for finsh shell */
        . = ALIGN(4);
        __fsymtab_start = .;
        KEEP(*(FSymTab))
        __fsymtab_end = .;

        . = ALIGN(4);
        __vsymtab_start = .;
        KEEP(*(VSymTab))
        __vsymtab_end = .;

        /* section information for initial. */
        . = ALIGN(4);
        __rt_init_start = .;
        KEEP(*(SORT(.rti_fn*)))
        __rt_init_end = .;

        . = ALIGN(4);
        KEEP(*(FalPartTable))
    }> FLASH
    __flash_noinit$$ (NOLOAD) :
    {
        __flash_noinit$$Base = .;
        /* section.flash.noinit */
        *(.flash_noinit)
        __flash_noinit$$Limit = .;
    }> FLASH
    /***** SDRAM memory section allocations ******/
    /* sdram initialized from flash */
    __sdram_from_flash$$ : ALIGN(4)
    {
        __sdram_from_flash$$Base = .;__sdram_from_flash$$Load = LOADADDR(__sdram_from_flash$$);
        /* section.sdram.from_flash */
        *(.sdram_from_flash)
        /* section.sdram.code_from_flash */
        *(.sdram_code_from_flash)
        __sdram_from_flash$$Limit = .;
    }> SDRAM AT > FLASH
    /* Non-initialized, non-cached sdram */
    __sdram_noinit_nocache$$ (NOLOAD) : ALIGN(32)
    {
        __sdram_noinit_nocache$$Base = .;
        /* section.sdram.noinit_nocache */
        *(.sdram_noinit_nocache)
        __sdram_noinit_nocache$$Limit = .;
    }> SDRAM
    /* Zeroed, non-cached sdram */
    __sdram_zero_nocache$$ (NOLOAD) :
    {
        __sdram_zero_nocache$$Base = .;
        /* section.sdram.zero_nocache */
        *(.sdram_nocache)
        . = ALIGN(32);
        __sdram_zero_nocache$$Limit = .;
    }> SDRAM
    /* Non-initialized sdram */
    __sdram_noinit$$ (NOLOAD) : ALIGN(4)
    {
        __sdram_noinit$$Base = .;
        /* section.sdram.noinit */
        *(.sdram_noinit)
        __sdram_noinit$$Limit = .;
    }> SDRAM
    /* Zeroed sdram */
    __sdram_zero$$ (NOLOAD) : ALIGN(4)
    {
        __sdram_zero$$Base = .;
        /* section.sdram.zero */
        *(.sdram)
        __sdram_zero$$Limit = .;
    }> SDRAM
    .sdram.endof ALIGN(.,512) :
    {
        __ddsc_SDRAM_END = .;

    }> SDRAM

    /***** OSPI0_CS0 memory section allocations ******/
    /* ospi0_cs0 initialized from flash */
    __ospi0_cs0_from_flash$$ : ALIGN(4)
    {
        __ospi0_cs0_from_flash$$Base = .;__ospi0_cs0_from_flash$$Load = LOADADDR(__ospi0_cs0_from_flash$$);
        /* section.ospi0_cs0.from_flash */
        *(.ospi0_cs0_from_flash)
        /* section.ospi0_cs0.code_from_flash */
        *(.ospi0_cs0_code_from_flash)
        __ospi0_cs0_from_flash$$Limit = .;
    }> OSPI0_CS0 AT > FLASH
    /* Non-initialized, non-cached ospi0_cs0 */
    __ospi0_cs0_noinit_nocache$$ (NOLOAD) : ALIGN(32)
    {
        __ospi0_cs0_noinit_nocache$$Base = .;
        /* section.ospi0_cs0.noinit_nocache */
        *(.ospi0_cs0_noinit_nocache)
        __ospi0_cs0_noinit_nocache$$Limit = .;
    }> OSPI0_CS0
    /* Zeroed, non-cached ospi0_cs0 */
    __ospi0_cs0_zero_nocache$$ (NOLOAD) :
    {
        __ospi0_cs0_zero_nocache$$Base = .;
        /* section.ospi0_cs0.zero_nocache */
        *(.ospi0_cs0_nocache)
        . = ALIGN(32);
        __ospi0_cs0_zero_nocache$$Limit = .;
    }> OSPI0_CS0
    /* Non-initialized ospi0_cs0 */
    __ospi0_cs0_noinit$$ (NOLOAD) : ALIGN(4)
    {
        __ospi0_cs0_noinit$$Base = .;
        /* section.ospi0_cs0.noinit */
        *(.ospi0_cs0_noinit)
        __ospi0_cs0_noinit$$Limit = .;
    }> OSPI0_CS0
    /* Zeroed ospi0_cs0 */
    __ospi0_cs0_zero$$ (NOLOAD) : ALIGN(4)
    {
        __ospi0_cs0_zero$$Base = .;
        /* section.ospi0_cs0.zero */
        *(.ospi0_cs0)
        __ospi0_cs0_zero$$Limit = .;
    }> OSPI0_CS0
    .ospi0_cs0.endof ALIGN(.,512) :
    {
        __ddsc_OSPI0_CS0_END = .;

    }> OSPI0_CS0

    /***** OSPI1_CS0 memory section allocations ******/
    /* ospi1_cs0 initialized from flash */
    __ospi1_cs0_from_flash$$ : ALIGN(4)
    {
        __ospi1_cs0_from_flash$$Base = .;__ospi1_cs0_from_flash$$Load = LOADADDR(__ospi1_cs0_from_flash$$);
        /* section.ospi1_cs0.from_flash */
        *(.ospi1_cs0_from_flash)
        /* section.ospi1_cs0.code_from_flash */
        *(.ospi1_cs0_code_from_flash)
        __ospi1_cs0_from_flash$$Limit = .;
    }> OSPI1_CS0 AT > FLASH
    /* Non-initialized, non-cached ospi1_cs0 */
    __ospi1_cs0_noinit_nocache$$ (NOLOAD) : ALIGN(32)
    {
        __ospi1_cs0_noinit_nocache$$Base = .;
        /* section.ospi1_cs0.noinit_nocache */
        *(.ospi1_cs0_noinit_nocache)
        __ospi1_cs0_noinit_nocache$$Limit = .;
    }> OSPI1_CS0
    /* Zeroed, non-cached ospi1_cs0 */
    __ospi1_cs0_zero_nocache$$ (NOLOAD) :
    {
        __ospi1_cs0_zero_nocache$$Base = .;
        /* section.ospi1_cs0.zero_nocache */
        *(.ospi1_cs0_nocache)
        . = ALIGN(32);
        __ospi1_cs0_zero_nocache$$Limit = .;
    }> OSPI1_CS0
    /* Non-initialized ospi1_cs0 */
    __ospi1_cs0_noinit$$ (NOLOAD) : ALIGN(4)
    {
        __ospi1_cs0_noinit$$Base = .;
        /* section.ospi1_cs0.noinit */
        *(.ospi1_cs0_noinit)
        __ospi1_cs0_noinit$$Limit = .;
    }> OSPI1_CS0
    /* Zeroed ospi1_cs0 */
    __ospi1_cs0_zero$$ (NOLOAD) : ALIGN(4)
    {
        __ospi1_cs0_zero$$Base = .;
        /* section.ospi1_cs0.zero */
        *(.ospi1_cs0)
        __ospi1_cs0_zero$$Limit = .;
    }> OSPI1_CS0
    .ospi1_cs0.endof ALIGN(.,512) :
    {
        __ddsc_OSPI1_CS0_END = .;

    }> OSPI1_CS0

    /***** ITCM memory section allocations ******/
    /* itcm initialized from flash */
    __itcm_from_flash$$ : ALIGN(8)
    {
        __itcm_from_flash$$Base = .;__itcm_from_flash$$Load = LOADADDR(__itcm_from_flash$$);
        /* section.itcm.from_flash */
        *(.itcm_from_flash)
        /* section.itcm.code_from_flash */
        *(.itcm_code_from_flash)
        . = ALIGN(8);
        __itcm_from_flash$$Limit = .;
    }> ITCM AT > FLASH
    /* Non-initialized itcm */
    __itcm_noinit$$ (NOLOAD) : ALIGN(8)
    {
        __itcm_noinit$$Base = .;
        /* section.itcm.noinit */
        *(.itcm_noinit)
        . = ALIGN(8);
        __itcm_noinit$$Limit = .;
    }> ITCM
    /* Zeroed itcm */
    __itcm_zero$$ (NOLOAD) : ALIGN(8)
    {
        __itcm_zero$$Base = .;
        /* section.itcm.zero */
        *(.itcm)
        . = ALIGN(8);
        __itcm_zero$$Limit = .;
    }> ITCM
    .itcm.endof ALIGN(.,8192) :
    {
        __ddsc_ITCM_END = .;

    }> ITCM

    /***** DTCM memory section allocations ******/
    /* dtcm initialized from flash */
    __dtcm_from_flash$$ : ALIGN(8)
    {
        __dtcm_from_flash$$Base = .;__dtcm_from_flash$$Load = LOADADDR(__dtcm_from_flash$$);
        /* section.dtcm.from_flash */
        *(.dtcm_from_flash)
        /* section.dtcm.code_from_flash */
        *(.dtcm_code_from_flash)
        . = ALIGN(8);
        __dtcm_from_flash$$Limit = .;
    }> DTCM AT > FLASH
    /* Non-initialized dtcm */
    __dtcm_noinit$$ (NOLOAD) : ALIGN(8)
    {
        __dtcm_noinit$$Base = .;
        /* section.dtcm.noinit */
        *(.dtcm_noinit)
        . = ALIGN(8);
        __dtcm_noinit$$Limit = .;
    }> DTCM
    /* Zeroed dtcm */
    __dtcm_zero$$ (NOLOAD) : ALIGN(8)
    {
        __dtcm_zero$$Base = .;
        /* section.dtcm.zero */
        *(.dtcm)
        . = ALIGN(8);
        __dtcm_zero$$Limit = .;
    }> DTCM
    .dtcm.endof ALIGN(.,8192) :
    {
        __ddsc_DTCM_END = .;

    }> DTCM

    /***** RAM memory section allocations ******/
    /* ram initialized from flash */
    __ram_from_flash$$ : ALIGN(4)
    {
        __ram_from_flash$$Base = .;__ram_from_flash$$Load = LOADADDR(__ram_from_flash$$);
        /* section.ram.from_flash */
        *(.ram_from_flash)
        /* section.ram.code_from_flash */
        *(.ram_code_from_flash)
        *(.data*)
        *(vtable)
        __ram_from_flash$$Limit = .;
    }> RAM AT > FLASH
    /* Non-initialized, non-cached ram */
    __ram_noinit_nocache$$ (NOLOAD) : ALIGN(32)
    {
        __ram_noinit_nocache$$Base = .;
        /* section.ram.noinit_nocache */
        *(.ram_noinit_nocache)
        __ram_noinit_nocache$$Limit = .;
    }> RAM
    /* Zeroed, non-cached ram */
    __ram_zero_nocache$$ (NOLOAD) :
    {
        __ram_zero_nocache$$Base = .;
        /* section.ram.zero_nocache */
        *(.ram_nocache)
        . = ALIGN(32);
        __ram_zero_nocache$$Limit = .;
    }> RAM
    /* Non-initialized ram */
    __ram_noinit$$ (NOLOAD) : ALIGN(4)
    {
        __ram_noinit$$Base = .;
        /* section.ram.noinit */
        *(.bss.g_heap)
        *(.bss.g_main_stack)
        *(.ram_noinit)
        *(.noinit)
        __ram_noinit$$Limit = .;
    }> RAM
    /* Zeroed ram */
    __ram_zero$$ (NOLOAD) : ALIGN(4)
    {
        __ram_zero$$Base = .;
        /* section.ram.zero */
        *(.ram)
        *(.bss*)
        __ram_zero$$Limit = .;
    }> RAM
    /* Thread Stacks */
    __ram_thread_stack$$ (NOLOAD) : ALIGN(8)
    {
        __ram_thread_stack$$Base = .;
        KEEP(*(.stack?*))
        __ram_thread_stack$$Limit = .;
    }> RAM
    .ram.endof ALIGN(.,8192) :
    {
        __ddsc_RAM_END = .;

    }> RAM
    .ram.flat_nsc :
    {
        __sau_ddsc_RAM_NSC = .;

    }> RAM
    
    /* This symbol represents the end of user allocated RAM. The RAM after this symbol can be used
       at run time for things such as ThreadX memory pool allocations. */
    __RAM_segment_used_end__ = ALIGN(__sau_ddsc_RAM_NSC , 4);

    __flash_readonly$$ (READONLY) :
    {
        __flash_readonly$$Base = .;
        /* section.flash.readonly */
        *(.flash)
        /* section.flash.code */
        *(.flash_code)
        *(.text*)
        *(.rodata*)
        KEEP(*(.mcuboot_sce9_key))
        KEEP(*(.version))
        __flash_readonly$$Limit = .;
    }> FLASH
    __flash_ctor$$ (READONLY) :
    {

        *crtbegin.o(.ctors)
        *crtbegin?.o(.ctors)
        EXCLUDE_FILE (*crtend?.o *crtend.o) *(.ctors)
        *(SORT(.ctors.*))
        *(.ctors)
        *crtbegin.o(.dtors)
        *crtbegin?.o(.dtors)
        EXCLUDE_FILE (*crtend?.o *crtend.o) *(.dtors)
        *(SORT(.dtors.*))
        *(.dtors)

    }> FLASH
    __flash_preinit_array$$ (READONLY) : ALIGN(4)
    {
        __preinit_array_start = .;
        KEEP(*(.preinit_array))
        __preinit_array_end = .;
    }> FLASH
    __flash_.got$$ (READONLY) :
    {

        *(.got.plt)
        *(.got)

    }> FLASH
    __flash_init_array$$ (READONLY) : ALIGN(4)
    {
        __init_array_start = .;
        KEEP(*(SORT(.init_array.*)))
        KEEP(*(.init_array))
        __init_array_end = .;
    }> FLASH
    __flash_fini_array$$ (READONLY) : ALIGN(4)
    {
        __fini_array_start = .;
        KEEP(*(SORT(.fini_array.*)))
        KEEP(*(.fini_array))
        __fini_array_end = .;
    }> FLASH
    /* Discard exception tables */
    /DISCARD/ (READONLY) :
    {

        *(.ARM.extab*)
        *(.gnu.linkonce.armextab.*)
        *(.ARM.exidx*)
        *(.gnu.linkonce.armexidx.*)

    }> FLASH
    /* Dummy section to hold required exidx labels */
    __flash_arm.exidx$$ (READONLY) :
    {
        __exidx_start = .;
        __exidx_end = .;
    }> FLASH
    .flash.endof ALIGN(.,32768) (READONLY) :
    {
        __ddsc_FLASH_END = .;

    }> FLASH
    .flash.flat_nsc (READONLY) :
    {
        __sau_ddsc_FLASH_NSC = .;

    }> FLASH

    /***** OPTION_SETTING_OFS0 memory section allocations ******/
    .option_setting_ofs0.startof (READONLY) :
    {
        __ddsc_OPTION_SETTING_OFS0_START = .;

    }> OPTION_SETTING_OFS0
    /* Option Function Select Register 0 */
    __option_setting_ofs0_reg$$ (READONLY) :
    {
        __option_setting_ofs0_reg$$Base = .;
        KEEP(*(.option_setting_ofs0))
        __option_setting_ofs0_reg$$Limit = .;
    }> OPTION_SETTING_OFS0
    .option_setting_ofs0.endof (READONLY) :
    {
        __ddsc_OPTION_SETTING_OFS0_END = .;

    }> OPTION_SETTING_OFS0

    /***** OPTION_SETTING_OFS2 memory section allocations ******/
    .option_setting_ofs2.startof (READONLY) :
    {
        __ddsc_OPTION_SETTING_OFS2_START = .;

    }> OPTION_SETTING_OFS2
    /* Option Function Select Register 2 */
    __option_setting_ofs2_reg$$ (READONLY) :
    {
        __option_setting_ofs2_reg$$Base = .;
        KEEP(*(.option_setting_ofs2))
        __option_setting_ofs2_reg$$Limit = .;
    }> OPTION_SETTING_OFS2
    .option_setting_ofs2.endof (READONLY) :
    {
        __ddsc_OPTION_SETTING_OFS2_END = .;

    }> OPTION_SETTING_OFS2

    /***** OPTION_SETTING_SAS memory section allocations ******/
    .option_setting_sas.startof (READONLY) :
    {
        __ddsc_OPTION_SETTING_SAS_START = .;

    }> OPTION_SETTING_SAS
    /* Startup Area Setting Register */
    __option_setting_sas_reg$$ (READONLY) :
    {
        __option_setting_sas_reg$$Base = .;
        KEEP(*(.option_setting_sas))
        __option_setting_sas_reg$$Limit = .;
    }> OPTION_SETTING_SAS
    .option_setting_sas.endof (READONLY) :
    {
        __ddsc_OPTION_SETTING_SAS_END = .;

    }> OPTION_SETTING_SAS

    /***** OPTION_SETTING_OFS1 memory section allocations ******/
    .option_setting_ofs1.startof (READONLY) :
    {
        __ddsc_OPTION_SETTING_OFS1_START = .;

    }> OPTION_SETTING_OFS1
    /* Option Function Select Register 1 */
    __option_setting_ofs1_reg$$ (READONLY) :
    {
        __option_setting_ofs1_reg$$Base = .;
        KEEP(*(.option_setting_ofs1))
        __option_setting_ofs1_reg$$Limit = .;
    }> OPTION_SETTING_OFS1
    .option_setting_ofs1.endof (READONLY) :
    {
        __ddsc_OPTION_SETTING_OFS1_END = .;

    }> OPTION_SETTING_OFS1

    /***** OPTION_SETTING_OFS1_SEC memory section allocations ******/
    .option_setting_ofs1_sec.startof (READONLY) :
    {
        __ddsc_OPTION_SETTING_OFS1_SEC_START = .;

    }> OPTION_SETTING_OFS1_SEC
    /* Option Function Select Register 1 Secure */
    __option_setting_ofs1_sec_reg$$ (READONLY) :
    {
        __option_setting_ofs1_sec_reg$$Base = .;
        KEEP(*(.option_setting_ofs1_sec))
        __option_setting_ofs1_sec_reg$$Limit = .;
    }> OPTION_SETTING_OFS1_SEC
    .option_setting_ofs1_sec.endof (READONLY) :
    {
        __ddsc_OPTION_SETTING_OFS1_SEC_END = .;

    }> OPTION_SETTING_OFS1_SEC

    /***** OPTION_SETTING_OFS1_SEL memory section allocations ******/
    .option_setting_ofs1_sel.startof (READONLY) :
    {
        __ddsc_OPTION_SETTING_OFS1_SEL_START = .;

    }> OPTION_SETTING_OFS1_SEL
    /* OFS1 Register Select */
    __option_setting_ofs1_sel_reg$$ (READONLY) :
    {
        __option_setting_ofs1_sel_reg$$Base = .;
        KEEP(*(.option_setting_ofs1_sel))
        __option_setting_ofs1_sel_reg$$Limit = .;
    }> OPTION_SETTING_OFS1_SEL
    .option_setting_ofs1_sel.endof (READONLY) :
    {
        __ddsc_OPTION_SETTING_OFS1_SEL_END = .;

    }> OPTION_SETTING_OFS1_SEL

    /***** OPTION_SETTING_OFS3 memory section allocations ******/
    .option_setting_ofs3.startof (READONLY) :
    {
        __ddsc_OPTION_SETTING_OFS3_START = .;

    }> OPTION_SETTING_OFS3
    /* Option Function Select Register 3 */
    __option_setting_ofs3_reg$$ (READONLY) :
    {
        __option_setting_ofs3_reg$$Base = .;
        KEEP(*(.option_setting_ofs3))
        __option_setting_ofs3_reg$$Limit = .;
    }> OPTION_SETTING_OFS3
    .option_setting_ofs3.endof (READONLY) :
    {
        __ddsc_OPTION_SETTING_OFS3_END = .;

    }> OPTION_SETTING_OFS3

    /***** OPTION_SETTING_OFS3_SEC memory section allocations ******/
    .option_setting_ofs3_sec.startof (READONLY) :
    {
        __ddsc_OPTION_SETTING_OFS3_SEC_START = .;

    }> OPTION_SETTING_OFS3_SEC
    /* Option Function Select Register 3 Secure */
    __option_setting_ofs3_sec_reg$$ (READONLY) :
    {
        __option_setting_ofs3_sec_reg$$Base = .;
        KEEP(*(.option_setting_ofs3_sec))
        __option_setting_ofs3_sec_reg$$Limit = .;
    }> OPTION_SETTING_OFS3_SEC
    .option_setting_ofs3_sec.endof (READONLY) :
    {
        __ddsc_OPTION_SETTING_OFS3_SEC_END = .;

    }> OPTION_SETTING_OFS3_SEC

    /***** OPTION_SETTING_OFS3_SEL memory section allocations ******/
    .option_setting_ofs3_sel.startof (READONLY) :
    {
        __ddsc_OPTION_SETTING_OFS3_SEL_START = .;

    }> OPTION_SETTING_OFS3_SEL
    /* OFS3 Register Select */
    __option_setting_ofs3_sel_reg$$ (READONLY) :
    {
        __option_setting_ofs3_sel_reg$$Base = .;
        KEEP(*(.option_setting_ofs3_sel))
        __option_setting_ofs3_sel_reg$$Limit = .;
    }> OPTION_SETTING_OFS3_SEL
    .option_setting_ofs3_sel.endof (READONLY) :
    {
        __ddsc_OPTION_SETTING_OFS3_SEL_END = .;

    }> OPTION_SETTING_OFS3_SEL

    /***** OPTION_SETTING_BPS memory section allocations ******/
    .option_setting_bps.startof (READONLY) :
    {
        __ddsc_OPTION_SETTING_BPS_START = .;

    }> OPTION_SETTING_BPS
    /* Block Protect Setting Register */
    __option_setting_bps_reg$$ (READONLY) :
    {
        __option_setting_bps_reg$$Base = .;
        KEEP(*(.option_setting_bps))
        __option_setting_bps_reg$$Limit = .;
    }> OPTION_SETTING_BPS
    .option_setting_bps.endof (READONLY) :
    {
        __ddsc_OPTION_SETTING_BPS_END = .;

    }> OPTION_SETTING_BPS

    /***** OPTION_SETTING_BPS_SEC memory section allocations ******/
    .option_setting_bps_sec.startof (READONLY) :
    {
        __ddsc_OPTION_SETTING_BPS_SEC_START = .;

    }> OPTION_SETTING_BPS_SEC
    /* Block Protect Setting Register Secure */
    __option_setting_bps_sec_reg$$ (READONLY) :
    {
        __option_setting_bps_sec_reg$$Base = .;
        KEEP(*(.option_setting_bps_sec))
        __option_setting_bps_sec_reg$$Limit = .;
    }> OPTION_SETTING_BPS_SEC
    .option_setting_bps_sec.endof (READONLY) :
    {
        __ddsc_OPTION_SETTING_BPS_SEC_END = .;

    }> OPTION_SETTING_BPS_SEC

    /***** OPTION_SETTING_OTP_PBPS_SEC memory section allocations ******/
    .option_setting_otp_pbps_sec.startof (READONLY) :
    {
        __ddsc_OPTION_SETTING_OTP_PBPS_SEC_START = .;

    }> OPTION_SETTING_OTP_PBPS_SEC
    /* Permanent Block Protect Setting Register Secure */
    __option_setting_otp_pbps_sec_reg$$ (READONLY) :
    {
        __option_setting_otp_pbps_sec_reg$$Base = .;
        KEEP(*(.option_setting_otp_pbps_sec))
        __option_setting_otp_pbps_sec_reg$$Limit = .;
    }> OPTION_SETTING_OTP_PBPS_SEC
    .option_setting_otp_pbps_sec.endof (READONLY) :
    {
        __ddsc_OPTION_SETTING_OTP_PBPS_SEC_END = .;

    }> OPTION_SETTING_OTP_PBPS_SEC

    /***** OPTION_SETTING_OTP_PBPS memory section allocations ******/
    .option_setting_otp_pbps.startof (READONLY) :
    {
        __ddsc_OPTION_SETTING_OTP_PBPS_START = .;

    }> OPTION_SETTING_OTP_PBPS
    /* Permanent Block Protect Setting Register */
    __option_setting_otp_pbps_reg$$ (READONLY) :
    {
        __option_setting_otp_pbps_reg$$Base = .;
        KEEP(*(.option_setting_otp_pbps))
        __option_setting_otp_pbps_reg$$Limit = .;
    }> OPTION_SETTING_OTP_PBPS
    .option_setting_otp_pbps.endof (READONLY) :
    {
        __ddsc_OPTION_SETTING_OTP_PBPS_END = .;

    }> OPTION_SETTING_OTP_PBPS

}

