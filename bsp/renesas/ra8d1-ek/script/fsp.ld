/*
                  Linker File for Renesas FSP
*/

INCLUDE memory_regions.ld

/* Uncomment and set XIP_SECONDARY_SLOT_IMAGE to 1 below for the secondary XIP application image.*/
/*
 XIP_SECONDARY_SLOT_IMAGE = 1;
*/

QSPI_FLASH_PRV_LENGTH = DEFINED(QSPI_FLASH_SIZE) ? ABSOLUTE(QSPI_FLASH_SIZE) : ABSOLUTE(QSPI_FLASH_LENGTH);
OSPI_DEVICE_0_PRV_LENGTH = DEFINED(OSPI_DEVICE_0_SIZE) ? ABSOLUTE(OSPI_DEVICE_0_SIZE) : ABSOLUTE(OSPI_DEVICE_0_LENGTH);
OSPI_DEVICE_1_PRV_LENGTH = DEFINED(OSPI_DEVICE_1_SIZE) ? ABSOLUTE(OSPI_DEVICE_1_SIZE) : ABSOLUTE(OSPI_DEVICE_1_LENGTH);

/* If a flat (secure) project has DEFINED RAM_NS_BUFFER_LENGTH, then emit IDAU symbols to allocate non-secure RAM. */
__RESERVE_NS_RAM = !DEFINED(PROJECT_NONSECURE) && DEFINED(RAM_NS_BUFFER_LENGTH) && (OPTION_SETTING_S_LENGTH != 0);

ITCM_START = DEFINED(ITCM_START)? ITCM_START : 0;
ITCM_LENGTH = DEFINED(ITCM_LENGTH)? ITCM_LENGTH : 0;
DTCM_START = DEFINED(DTCM_START)? DTCM_START : 0;
DTCM_LENGTH = DEFINED(DTCM_LENGTH)? DTCM_LENGTH : 0;
NS_OFFSET_START = DEFINED(NS_OFFSET_START) ? NS_OFFSET_START : 0;
NS_IMAGE_OFFSET = DEFINED(PROJECT_NONSECURE) ? NS_OFFSET_START : 0;
RAM_NS_BUFFER_BLOCK_LENGTH = DEFINED(RAM_NS_BUFFER_LENGTH) ? ALIGN(RAM_NS_BUFFER_LENGTH, 8192) : 0;
RAM_NS_BUFFER_LENGTH = DEFINED(RAM_NS_BUFFER_LENGTH) ? RAM_NS_BUFFER_LENGTH : 0;
RAM_NS_BUFFER_START = RAM_START + RAM_LENGTH - RAM_NS_BUFFER_LENGTH;
RAM_NS_BUFFER_BLOCK_START = RAM_START + RAM_LENGTH - RAM_NS_BUFFER_BLOCK_LENGTH;

OPTION_SETTING_START_NS = DEFINED(PROJECT_NONSECURE) ? OPTION_SETTING_START : OPTION_SETTING_START + 0x80;

/* This definition is used to avoid moving the counter in OPTION_SETTING regions for projects that should not configure option settings.
 * Bootloader images do not configure option settings because they are owned by the bootloader.
 * FSP_BOOTABLE_IMAGE is only defined in bootloader images. */
__bl_FSP_BOOTABLE_IMAGE = 1;
__bln_FSP_BOOTABLE_IMAGE = 1;
PROJECT_SECURE_OR_FLAT = (!DEFINED(PROJECT_NONSECURE) || DEFINED(PROJECT_SECURE)) && OPTION_SETTING_LENGTH && !DEFINED(FSP_BOOTABLE_IMAGE);
USE_OPTION_SETTING_NS = DEFINED(PROJECT_NONSECURE) && !DEFINED(FSP_BOOTABLE_IMAGE);

__bl_FLASH_IMAGE_START = !DEFINED(FLASH_BOOTLOADER_LENGTH) ? 0 :
                         FLASH_APPLICATION_IMAGE_NUMBER == 1 ? FLASH_BOOTLOADER_LENGTH + FLASH_BOOTLOADER_HEADER_LENGTH :
                         FLASH_BOOTLOADER_LENGTH + FLASH_BOOTLOADER_SCRATCH_LENGTH + FLASH_APPLICATION_S_LENGTH + FLASH_BOOTLOADER_HEADER_LENGTH;
__bl_FLASH_IMAGE_LENGTH = !DEFINED(FLASH_BOOTLOADER_LENGTH) ? 0 :
                          FLASH_APPLICATION_S_LENGTH - FLASH_BOOTLOADER_HEADER_LENGTH;
__bl_FLASH_IMAGE_END    = __bl_FLASH_IMAGE_START + __bl_FLASH_IMAGE_LENGTH;
__bl_XIP_SECONDARY_FLASH_IMAGE_START = !DEFINED(FLASH_BOOTLOADER_LENGTH) ? 0 :
                         FLASH_BOOTLOADER_LENGTH + FLASH_APPLICATION_S_LENGTH + FLASH_BOOTLOADER_HEADER_LENGTH;
__bl_XIP_SECONDARY_FLASH_IMAGE_END = __bl_XIP_SECONDARY_FLASH_IMAGE_START + __bl_FLASH_IMAGE_LENGTH;
__bl_FLASH_NS_START = !DEFINED(FLASH_BOOTLOADER_LENGTH) ? 0 :
                        FLASH_APPLICATION_NS_LENGTH == 0 ? __bl_FLASH_IMAGE_END :
                        __bl_FLASH_IMAGE_START - FLASH_BOOTLOADER_HEADER_LENGTH + FLASH_APPLICATION_S_LENGTH;
__bl_FLASH_NSC_START = !DEFINED(FLASH_BOOTLOADER_LENGTH) ? 0 :
                        FLASH_APPLICATION_NS_LENGTH == 0 ? __bl_FLASH_IMAGE_END :
                        __bl_FLASH_NS_START - FLASH_APPLICATION_NSC_LENGTH;
__bl_RAM_NS_START    = !DEFINED(FLASH_BOOTLOADER_LENGTH) ? 0 :
                       FLASH_APPLICATION_NS_LENGTH == 0 ? RAM_START + RAM_LENGTH :
                       RAM_START + RAM_LENGTH - RAM_APPLICATION_NS_LENGTH;
__bl_RAM_NSC_START   = !DEFINED(FLASH_BOOTLOADER_LENGTH) ? 0 :
                       FLASH_APPLICATION_NS_LENGTH == 0 ? RAM_START + RAM_LENGTH :
                       __bl_RAM_NS_START - RAM_APPLICATION_NSC_LENGTH;
__bl_FLASH_NS_IMAGE_START = !DEFINED(FLASH_BOOTLOADER_LENGTH) ? 0 :
                            FLASH_APPLICATION_NS_LENGTH == 0 ? __bl_FLASH_IMAGE_END :
                            __bl_FLASH_NS_START + FLASH_BOOTLOADER_HEADER_LENGTH_2;
__bln_FLASH_IMAGE_START = __bl_FLASH_NS_IMAGE_START;
__bln_FLASH_IMAGE_LENGTH = !DEFINED(FLASH_BOOTLOADER_LENGTH) ? 0 :
                           FLASH_APPLICATION_NS_LENGTH == 0 ? __bl_FLASH_IMAGE_END :
                           FLASH_APPLICATION_NS_LENGTH - FLASH_BOOTLOADER_HEADER_LENGTH_2;

XIP_SECONDARY_SLOT_IMAGE = DEFINED(XIP_SECONDARY_SLOT_IMAGE) ? XIP_SECONDARY_SLOT_IMAGE : 0;
FLASH_ORIGIN = !DEFINED(FLASH_IMAGE_START) ? FLASH_START :
                XIP_SECONDARY_SLOT_IMAGE == 1 ? XIP_SECONDARY_FLASH_IMAGE_START :
                FLASH_IMAGE_START;
LIMITED_FLASH_LENGTH = DEFINED(FLASH_IMAGE_LENGTH) ? FLASH_IMAGE_LENGTH :
                       DEFINED(FLASH_BOOTLOADER_LENGTH) ? FLASH_BOOTLOADER_LENGTH :
                       FLASH_LENGTH;

/* Define memory regions. */
MEMORY
{
  ITCM (rx)               : ORIGIN = ITCM_START + NS_IMAGE_OFFSET, LENGTH = ITCM_LENGTH
  DTCM (rwx)              : ORIGIN = DTCM_START + NS_IMAGE_OFFSET, LENGTH = DTCM_LENGTH
  FLASH (rx)              : ORIGIN = FLASH_ORIGIN + NS_IMAGE_OFFSET, LENGTH = LIMITED_FLASH_LENGTH
  RAM (rwx)               : ORIGIN = RAM_START + NS_IMAGE_OFFSET, LENGTH = RAM_LENGTH
  DATA_FLASH (rx)         : ORIGIN = DATA_FLASH_START + NS_IMAGE_OFFSET, LENGTH = DATA_FLASH_LENGTH
  QSPI_FLASH (rx)         : ORIGIN = QSPI_FLASH_START, LENGTH = QSPI_FLASH_PRV_LENGTH
  OSPI_DEVICE_0 (rx)      : ORIGIN = OSPI_DEVICE_0_START, LENGTH = OSPI_DEVICE_0_PRV_LENGTH
  OSPI_DEVICE_1 (rx)      : ORIGIN = OSPI_DEVICE_1_START, LENGTH = OSPI_DEVICE_1_PRV_LENGTH
  OSPI_DEVICE_0_RAM (rwx) : ORIGIN = OSPI_DEVICE_0_START, LENGTH = OSPI_DEVICE_0_PRV_LENGTH
  OSPI_DEVICE_1_RAM (rwx) : ORIGIN = OSPI_DEVICE_1_START, LENGTH = OSPI_DEVICE_1_PRV_LENGTH
  SDRAM (rwx)             : ORIGIN = SDRAM_START, LENGTH = SDRAM_LENGTH
  OPTION_SETTING (r)      : ORIGIN = OPTION_SETTING_START + NS_IMAGE_OFFSET, LENGTH = OPTION_SETTING_LENGTH
  OPTION_SETTING_OFS (r)  : ORIGIN = OPTION_SETTING_START + NS_IMAGE_OFFSET, LENGTH = 0x18
  OPTION_SETTING_SAS (r)  : ORIGIN = OPTION_SETTING_START + NS_IMAGE_OFFSET + 0x34, LENGTH = OPTION_SETTING_LENGTH - 0x34
  OPTION_SETTING_S (r)    : ORIGIN = OPTION_SETTING_S_START + NS_IMAGE_OFFSET, LENGTH = OPTION_SETTING_S_LENGTH
  ID_CODE (rx)            : ORIGIN = ID_CODE_START, LENGTH = ID_CODE_LENGTH
}

/* Library configurations */
GROUP(libc.a libm.a libnosys.a)

/* Linker script to place sections and symbol values. Should be used together
 * with other linker script that defines memory regions FLASH and RAM.
 * It references following symbols, which must be DEFINED in code:
 *   Reset_Handler : Entry of reset handler
 *
 * It defines following symbols, which code can use without definition:
 *   __exidx_start
 *   __exidx_end
 *   __copy_table_start__
 *   __copy_table_end__
 *   __zero_table_start__
 *   __zero_table_end__
 *   __etext
 *   __data_start__
 *   __preinit_array_start
 *   __preinit_array_end
 *   __init_array_start
 *   __init_array_end
 *   __fini_array_start
 *   __fini_array_end
 *   __data_end__
 *   __bss_start__
 *   __bss_end__
 *   __HeapLimit
 *   __StackLimit
 *   __StackTop
 *   __stack
 *   __Vectors_End
 *   __Vectors_Size
 *   __qspi_flash_start__
 *   __qspi_flash_end__
 *   __qspi_flash_code_size__
 *   __qspi_region_max_size__
 *   __qspi_region_start_address__
 *   __qspi_region_end_address__
 *   __ospi_device_0_start__
 *   __ospi_device_0_end__
 *   __ospi_device_0_code_size__
 *   __ospi_device_0_region_max_size__
 *   __ospi_device_0_region_start_address__
 *   __ospi_device_0_region_end_address__
 *   __ospi_device_1_start__
 *   __ospi_device_1_end__
 *   __ospi_device_1_code_size__
 *   __ospi_device_1_region_max_size__
 *   __ospi_device_1_region_start_address__
 *   __ospi_device_1_region_end_address__
 */
ENTRY(Reset_Handler)

SECTIONS
{
    .text :
    {
        __tz_FLASH_S = ABSOLUTE(FLASH_START);
        __ROM_Start = .;

        /* Even though the vector table is not 256 entries (1KB) long, we still allocate that much
         * space because ROM registers are at address 0x400 and there is very little space
         * in between. */
        KEEP(*(.fixed_vectors*))
        KEEP(*(.application_vectors*))
        __Vectors_End = .;

        /* ROM Registers start at address 0x00000400 for devices that do not have the OPTION_SETTING region. */
        . = OPTION_SETTING_LENGTH > 0 ? . : __ROM_Start + 0x400;
        KEEP(*(.rom_registers*))

        /* Reserving 0x100 bytes of space for ROM registers. */
        . = OPTION_SETTING_LENGTH > 0 ? . : __ROM_Start + 0x500;

        /* Allocate flash write-boundary-aligned
         * space for sce9 wrapped public keys for mcuboot if the module is used.
         */
		. = ALIGN(128);
        KEEP(*(.mcuboot_sce9_key*))

        *(.text*)

        KEEP(*(.version))
        KEEP(*(.init))
        KEEP(*(.fini))

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

        /* .ctors */
        *crtbegin.o(.ctors)
        *crtbegin?.o(.ctors)
        *(EXCLUDE_FILE(*crtend?.o *crtend.o) .ctors)
        *(SORT(.ctors.*))
        *(.ctors)

        /* .dtors */
        *crtbegin.o(.dtors)
        *crtbegin?.o(.dtors)
        *(EXCLUDE_FILE(*crtend?.o *crtend.o) .dtors)
        *(SORT(.dtors.*))
        *(.dtors)

        *(.rodata*)
        __usb_dev_descriptor_start_fs = .;
        KEEP(*(.usb_device_desc_fs*))
        __usb_cfg_descriptor_start_fs = .;
        KEEP(*(.usb_config_desc_fs*))
        __usb_interface_descriptor_start_fs = .;
        KEEP(*(.usb_interface_desc_fs*))
        __usb_descriptor_end_fs = .;
        __usb_dev_descriptor_start_hs = .;
        KEEP(*(.usb_device_desc_hs*))
        __usb_cfg_descriptor_start_hs = .;
        KEEP(*(.usb_config_desc_hs*))
        __usb_interface_descriptor_start_hs = .;
        KEEP(*(.usb_interface_desc_hs*))
        __usb_descriptor_end_hs = .;

        KEEP(*(.eh_frame*))

        /* new GCC version uses .init_array */
        PROVIDE(__ctors_start__ = .);
        KEEP (*(SORT(.init_array.*)))
        KEEP (*(.init_array))
        PROVIDE(__ctors_end__ = .);

        . = ALIGN(4);

        __ROM_End = .;
    } > FLASH = 0xFF

    __Vectors_Size = __Vectors_End - __Vectors;

    . = .;
    __itcm_data_pre_location = .;

    /* Initialized ITCM data. */
    /* Aligned to FCACHE2 for RA8. */
    .itcm_data : ALIGN(16)
    {
        /* Start of ITCM Secure Trustzone region. */
        __tz_ITCM_S = ABSOLUTE(ITCM_START);

        /* All ITCM data start */
        __itcm_data_start = .;

        KEEP(*(.itcm_data*))

        /* Pad to eight byte alignment in case of ECC initialization. Fill zero. */
        . = ALIGN(8);

        /* All ITCM data end */
        __itcm_data_end = .;

        /*
         * Start of the ITCM Non-Secure Trustzone region.
         * ITCM_NS_START can be used to set a fixed address for non-secure ITCM in secure projects or flat projects.
         */
        __tz_ITCM_N = DEFINED(ITCM_NS_START) ? ABSOLUTE(ITCM_NS_START) : ALIGN(__itcm_data_end, 8192);
    } > ITCM AT > FLASH = 0x00

    /* Addresses exported for ITCM initialization. */
    __itcm_data_init_start = LOADADDR(.itcm_data);
    __itcm_data_init_end = LOADADDR(.itcm_data) + SIZEOF(.itcm_data);

    ASSERT(ORIGIN(ITCM) % 8 == 0, "ITCM memory region origin must be aligned to 8 bytes.")
    ASSERT(LENGTH(ITCM) % 8 == 0, "ITCM memory region length must be a multiple of 8 bytes.")
    ASSERT(LOADADDR(.itcm_data) % 16 == 0, ".itcm_data section must be aligned to 16 bytes.")
    ASSERT(SIZEOF(.itcm_data) % 8 == 0, ".itcm_data section size must be a multiple of 8 bytes.")

    /* Restore location counter. */
    /* If ITCM is not present, this will be the address stored in '.' before ALIGN was attempted. */
    /* If ITCM is present, this will be the absolute address that follows the ITCM ROM location. */
    . = (SIZEOF(.itcm_data) > 0) ? __itcm_data_init_end : __itcm_data_pre_location;

    .ARM.extab :
    {
        *(.ARM.extab* .gnu.linkonce.armextab.*)
    } > FLASH

    __exidx_start = .;
    .ARM.exidx :
    {
        *(.ARM.exidx* .gnu.linkonce.armexidx.*)
    } > FLASH
    __exidx_end = .;

    /* To copy multiple ROM to RAM sections,
     * uncomment .copy.table section and,
     * define __STARTUP_COPY_MULTIPLE in startup_ARMCMx.S */
    /*
    .copy.table :
    {
        . = ALIGN(4);
        __copy_table_start__ = .;
        LONG (__etext)
        LONG (__data_start__)
        LONG (__data_end__ - __data_start__)
        LONG (__etext2)
        LONG (__data2_start__)
        LONG (__data2_end__ - __data2_start__)
        __copy_table_end__ = .;
    } > FLASH
    */

    /* To clear multiple BSS sections,
     * uncomment .zero.table section and,
     * define __STARTUP_CLEAR_BSS_MULTIPLE in startup_ARMCMx.S */
    /*
    .zero.table :
    {
        . = ALIGN(4);
        __zero_table_start__ = .;
        LONG (__bss_start__)
        LONG (__bss_end__ - __bss_start__)
        LONG (__bss2_start__)
        LONG (__bss2_end__ - __bss2_start__)
        __zero_table_end__ = .;
    } > FLASH
    */

    __etext = .;

    __tz_RAM_S = ORIGIN(RAM);

    /* If DTC is used, put the DTC vector table at the start of SRAM.
       This avoids memory holes due to 1K alignment required by it. */
    .fsp_dtc_vector_table (NOLOAD) :
    {
        . = ORIGIN(RAM);
        *(.fsp_dtc_vector_table)
    } > RAM

    /* Initialized data section. */
    .data :
    {
        __data_start__ = .;
        . = ALIGN(4);

        __Code_In_RAM_Start = .;

        KEEP(*(.code_in_ram*))
        __Code_In_RAM_End = .;

        *(vtable)
        /* Don't use *(.data*) because it will place data meant for .data_flash in this section. */
        *(.data.*)
        *(.data)

        . = ALIGN(4);
        /* preinit data */
        PROVIDE_HIDDEN (__preinit_array_start = .);
        KEEP(*(.preinit_array))
        PROVIDE_HIDDEN (__preinit_array_end = .);

        . = ALIGN(4);
        /* init data */
        PROVIDE_HIDDEN (__init_array_start = .);
        KEEP(*(SORT(.init_array.*)))
        KEEP(*(.init_array))
        PROVIDE_HIDDEN (__init_array_end = .);


        . = ALIGN(4);
        /* finit data */
        PROVIDE_HIDDEN (__fini_array_start = .);
        KEEP(*(SORT(.fini_array.*)))
        KEEP(*(.fini_array))
        PROVIDE_HIDDEN (__fini_array_end = .);

        KEEP(*(.jcr*))

        . = ALIGN(4);

        /* All data end */
        __data_end__ = .;

    } > RAM AT > FLASH

    . = .;
    __dtcm_data_pre_location = LOADADDR(.data) + SIZEOF(.data);

    /* Initialized DTCM data. */
    /* Aligned to FCACHE2 for RA8. */
    .dtcm_data : ALIGN(16)
    {
        /* Start of DTCM Secure Trustzone region. */
        __tz_DTCM_S = ABSOLUTE(DTCM_START);

        /* Initialized DTCM data start */
        __dtcm_data_start = .;

        KEEP(*(.dtcm_data*))

        /* Pad to eight byte alignment in case of ECC initialization. Fill zero. */
        . = ALIGN(8);

        /* Initialized DTCM data end */
        __dtcm_data_end = .;
    } > DTCM AT > FLASH = 0x00

    . = __dtcm_data_end;
    /* Uninitialized DTCM data. */
    /* ALIGN appears on the left side of the colon because it is being used to assign the VMA directly, as opposed to a right side appearance which would control the LMA. */
    .dtcm_bss ALIGN(8) (NOLOAD) :
    {
        /* Uninitialized DTCM data start */
        __dtcm_bss_start = .;

        KEEP(*(.dtcm_bss*))

        /* Pad to eight byte alignment in case of ECC initialization. No fill because of NOLOAD. */
        . = ALIGN(8);

        /* Uninitialized DTCM data end */
        __dtcm_bss_end = .;

        /*
         * Start of the DTCM Non-Secure Trustzone region.
         * DTCM_NS_START can be used to set a fixed address for non-secure DTCM in secure projects or flat projects.
         */
        __tz_DTCM_N = DEFINED(DTCM_NS_START) ? ABSOLUTE(DTCM_NS_START) : ALIGN(__dtcm_bss_end, 8192);
    } > DTCM

    /* Addresses exported for DTCM initialization. */
    __dtcm_data_init_start = LOADADDR(.dtcm_data);
    __dtcm_data_init_end = LOADADDR(.dtcm_data) + SIZEOF(.dtcm_data);

    ASSERT(ORIGIN(DTCM) % 8 == 0, "DTCM memory region origin must be aligned to 8 bytes.")
    ASSERT(LENGTH(DTCM) % 8 == 0, "DTCM memory region length must be a multiple of 8 bytes.")
    ASSERT(LOADADDR(.dtcm_bss) == ADDR(.dtcm_bss), ".dtcm_bss has (VMA != LMA) but should be NOLOAD (VMA == LMA).")
    ASSERT(LOADADDR(.dtcm_data) % 16 == 0, ".dtcm_data section must be aligned to 16 bytes.")
    ASSERT(SIZEOF(.dtcm_data) % 8 == 0, ".dtcm_data section size must be a multiple of 8 bytes.")
    ASSERT(LOADADDR(.dtcm_bss) % 8 == 0, ".dtcm_bss section must be aligned to 8 bytes.")
    ASSERT(SIZEOF(.dtcm_bss) % 8 == 0, ".dtcm_bss section size must be a multiple of 8 bytes.")
    ASSERT(__dtcm_bss_start == __dtcm_data_end, ".dtcm_bss section is not adjacent to .dtcm_data section.")

    /* Restore location counter. */
    /* If DTCM is not present, this will be the address stored in '.' before ALIGN was attempted. */
    /* If DTCM is present, this will be the absolute address that follows the DTCM ROM location. */
    . = (SIZEOF(.dtcm_data) > 0) ? __dtcm_data_init_end : __dtcm_data_pre_location;

    /* TrustZone Secure Gateway Stubs Section */

    /* Store location counter for SPI non-retentive sections. */
    sgstubs_pre_location = .;

    /* Determine the secure gateway stubs address either by the provided linker variable or the next 1024-byte block. */
    SGSTUBS_LOC = (DEFINED(PROJECT_SECURE) && DEFINED(FLASH_NSC_START)) ? ABSOLUTE(FLASH_NSC_START) : ALIGN(1024);
    .gnu.sgstubs SGSTUBS_LOC : ALIGN(1024)
    {
        __tz_FLASH_C = DEFINED(FLASH_NSC_START) ? ABSOLUTE(FLASH_NSC_START) : __RESERVE_NS_RAM ? ABSOLUTE(FLASH_START + FLASH_LENGTH) : ALIGN(1024);
        _start_sg = .;
        *(.gnu.sgstubs*)
        . = ALIGN(32);
        _end_sg = .;
    } > FLASH

    __tz_FLASH_N = DEFINED(FLASH_NS_START) ? ABSOLUTE(FLASH_NS_START) : __RESERVE_NS_RAM ? ABSOLUTE(FLASH_START + FLASH_LENGTH) : FLASH_LENGTH < 32768 ? FLASH_LENGTH : ALIGN(32768);
    FLASH_NS_IMAGE_START = DEFINED(FLASH_NS_IMAGE_START) ? FLASH_NS_IMAGE_START : __tz_FLASH_N;

    /* Note: There are no secure/non-secure boundaries for QSPI.  These symbols are provided for the RA configuration tool. */
    __tz_QSPI_FLASH_S = ORIGIN(QSPI_FLASH);

    /* QSPI_FLASH section to be downloaded via debugger */
    .qspi_flash :
    {
        __qspi_flash_start__ = .;
        KEEP(*(.qspi_flash*))
        KEEP(*(.code_in_qspi*))
        __qspi_flash_end__ = .;
    } > QSPI_FLASH
    __qspi_flash_code_size__ = __qspi_flash_end__ - __qspi_flash_start__;

    /* QSPI_FLASH non-retentive section, creates a copy in internal flash that can be copied to QSPI */
    __qspi_flash_code_addr__ = sgstubs_pre_location;
    .qspi_non_retentive : AT(__qspi_flash_code_addr__)
    {
        __qspi_non_retentive_start__ = .;
        KEEP(*(.qspi_non_retentive*))
        __qspi_non_retentive_end__ = .;
    } > QSPI_FLASH
    __qspi_non_retentive_size__ = __qspi_non_retentive_end__ - __qspi_non_retentive_start__;

    __qspi_region_max_size__ = 0x4000000;   /* Must be the same as defined in MEMORY above */
    __qspi_region_start_address__ = __qspi_flash_start__;
    __qspi_region_end_address__ = __qspi_flash_start__ + __qspi_region_max_size__;

    /* Note: There are no secure/non-secure boundaries for QSPI.  These symbols are provided for the RA configuration tool. */
    __tz_QSPI_FLASH_N = __qspi_non_retentive_end__;

    /* Support for OctaRAM */
    .OSPI_DEVICE_0_NO_LOAD (NOLOAD):
    {
        . = ALIGN(4);
        __ospi_device_0_start__ = .;
        *(.ospi_device_0_no_load*)
        . = ALIGN(4);
        __ospi_device_0_end__ = .;
    } > OSPI_DEVICE_0_RAM

    .OSPI_DEVICE_1_NO_LOAD (NOLOAD):
    {
        . = ALIGN(4);
        __ospi_device_1_start__ = .;
        *(.ospi_device_1_no_load*)
        . = ALIGN(4);
        __ospi_device_1_end__ = .;
    } > OSPI_DEVICE_1_RAM

    /* Note: There are no secure/non-secure boundaries for QSPI.  These symbols are provided for the RA configuration tool. */
    __tz_OSPI_DEVICE_0_S = ORIGIN(OSPI_DEVICE_0);

    /* OSPI_DEVICE_0 section to be downloaded via debugger */
    .OSPI_DEVICE_0 :
    {
        __ospi_device_0_start__ = .;
        KEEP(*(.ospi_device_0*))
        KEEP(*(.code_in_ospi_device_0*))
        __ospi_device_0_end__ = .;
    } > OSPI_DEVICE_0
    __ospi_device_0_code_size__ = __ospi_device_0_end__ - __ospi_device_0_start__;

    /* OSPI_DEVICE_0 non-retentive section, creates a copy in internal flash that can be copied to OSPI */
     __ospi_device_0_code_addr__ = sgstubs_pre_location + (SIZEOF(.qspi_non_retentive));
    .ospi_device_0_non_retentive : AT(__ospi_device_0_code_addr__)
    {
        __ospi_device_0_non_retentive_start__ = .;
        KEEP(*(.ospi_device_0_non_retentive*))
        __ospi_device_0_non_retentive_end__ = .;
    } > OSPI_DEVICE_0
    __ospi_device_0_non_retentive_size__ = __ospi_device_0_non_retentive_end__ - __ospi_device_0_non_retentive_start__;

    __ospi_device_0_region_max_size__ = 0x8000000;   /* Must be the same as defined in MEMORY above */
    __ospi_device_0_region_start_address__ = __ospi_device_0_start__;
    __ospi_device_0_region_end_address__ = __ospi_device_0_start__ + __ospi_device_0_region_max_size__;

    /* Note: There are no secure/non-secure boundaries for OSPI.  These symbols are provided for the RA configuration tool. */
    __tz_OSPI_DEVICE_0_N = __ospi_device_0_non_retentive_end__;

    /* Note: There are no secure/non-secure boundaries for OSPI.  These symbols are provided for the RA configuration tool. */
    __tz_OSPI_DEVICE_1_S = ORIGIN(OSPI_DEVICE_1);

    /* OSPI_DEVICE_1 section to be downloaded via debugger */
    .OSPI_DEVICE_1 :
    {
        __ospi_device_1_start__ = .;
        KEEP(*(.ospi_device_1*))
        KEEP(*(.code_in_ospi_device_1*))
        __ospi_device_1_end__ = .;
    } > OSPI_DEVICE_1
    __ospi_device_1_code_size__ = __ospi_device_1_end__ - __ospi_device_1_start__;

    /* OSPI_DEVICE_1 non-retentive section, creates a copy in internal flash that can be copied to OSPI */
    __ospi_device_1_code_addr__ = sgstubs_pre_location + (SIZEOF(.qspi_non_retentive) + SIZEOF(.ospi_device_0_non_retentive));
    .ospi_device_1_non_retentive : AT(__ospi_device_1_code_addr__)
    {
        __ospi_device_1_non_retentive_start__ = .;
        KEEP(*(.ospi_device_1_non_retentive*))
        __ospi_device_1_non_retentive_end__ = .;
    } > OSPI_DEVICE_1
    __ospi_device_1_non_retentive_size__ = __ospi_device_1_non_retentive_end__ - __ospi_device_1_non_retentive_start__;

    __ospi_device_1_region_max_size__ = 0x10000000;   /* Must be the same as defined in MEMORY above */
    __ospi_device_1_region_start_address__ = __ospi_device_1_start__;
    __ospi_device_1_region_end_address__ = __ospi_device_1_start__ + __ospi_device_1_region_max_size__;

    /* Note: There are no secure/non-secure boundaries for OSPI.  These symbols are provided for the RA configuration tool. */
    __tz_OSPI_DEVICE_1_N = __ospi_device_1_non_retentive_end__;

    .noinit (NOLOAD):
    {
        . = ALIGN(4);
        __noinit_start = .;
        KEEP(*(.noinit*))
        . = ALIGN(8);
        /* Place the FreeRTOS heap here so that the __HeapLimit calculation does not include the freertos heap. */
        KEEP(*(.heap.*))
        __noinit_end = .;
    } > RAM

    . = .;
    __nocache_pre_location = .;
    .nocache ALIGN(32) (NOLOAD):
    {
        __nocache_start = .;

        KEEP(*(.nocache))

        . = ALIGN(32);
        __nocache_end = .;
    } > RAM
    . = (SIZEOF(.nocache) > 0) ? __nocache_end : __nocache_pre_location;

    .bss :
    {
        . = ALIGN(4);
        __bss_start__ = .;
        *(.bss*)
        *(COMMON)
        . = ALIGN(4);
        __bss_end__ = .;
    } > RAM

    .heap (NOLOAD):
    {
        . = ALIGN(8);
        __HeapBase = .;
        /* Place the STD heap here. */
        KEEP(*(.heap))
        __HeapLimit = .;
    } > RAM

    /* Stacks are stored in this section. */
    .stack_dummy (NOLOAD):
    {
        . = ALIGN(8);
        __StackLimit = .;
        /* Main stack */
        KEEP(*(.stack))
        __StackTop = .;
        /* Thread stacks */
        KEEP(*(.stack*))
        __StackTopAll = .;
    } > RAM

    PROVIDE(__stack = __StackTopAll);

    /* This symbol represents the end of user allocated RAM. The RAM after this symbol can be used
       at run time for things such as ThreadX memory pool allocations. */
    __RAM_segment_used_end__ = ALIGN(__StackTopAll , 4);

    /* RAM_NSC_START can be used to set a fixed address for non-secure callable RAM in secure projects.
     * If it is not specified, the address for NSC RAM is the end of RAM aligned to a 1K boundary.
     * In flat projects that require non-secure RAM, this variable is set to the start of non-secure RAM. */
    __tz_RAM_C = DEFINED(RAM_NSC_START) ? ABSOLUTE(RAM_NSC_START - RAM_NS_BUFFER_BLOCK_LENGTH) : __RESERVE_NS_RAM ? ABSOLUTE(RAM_NS_BUFFER_BLOCK_START) : ALIGN(__RAM_segment_used_end__, 1024);

    /* RAM_NS_START can be used to set a fixed address for non-secure RAM in secure projects or flat projects.
     * RAM_NS_BUFFER_BLOCK_LENGTH is used to allocate non-secure buffers in a flat project. If it is not
     * specified, the address for NSC RAM is the end of RAM aligned to an 8K boundary.
     * In flat projects that require non-secure RAM, this variable is set to the start of non-secure RAM. */
    __tz_RAM_N = DEFINED(RAM_NS_START) ? ABSOLUTE(RAM_NS_START - RAM_NS_BUFFER_BLOCK_LENGTH) : __RESERVE_NS_RAM ? ABSOLUTE(RAM_NS_BUFFER_BLOCK_START) : ALIGN(__tz_RAM_C, 8192);

    /* Non-secure buffers must be in non-secure RAM. This is primarily used for the EDMAC in flat projects.
     * The EDMAC is a non-secure bus master and can only access non-secure RAM. */
    .ns_buffer (NOLOAD):
    {
        /* Allocate RAM on a 32-byte boundary to help with placement of Ethernet buffers. */
        . = __RESERVE_NS_RAM ? ABSOLUTE(RAM_NS_BUFFER_START & 0xFFFFFFE0) : .;

        KEEP(*(.ns_buffer*))
    } > RAM

    /* Data flash. */
    .data_flash :
    {
        . = ORIGIN(DATA_FLASH);
        __tz_DATA_FLASH_S = .;
        __Data_Flash_Start = .;
        KEEP(*(.data_flash*))
        __Data_Flash_End = .;

        __tz_DATA_FLASH_N = DEFINED(DATA_FLASH_NS_START) ? ABSOLUTE(DATA_FLASH_NS_START) : __RESERVE_NS_RAM ? ABSOLUTE(DATA_FLASH_START + DATA_FLASH_LENGTH) : ALIGN(1024);
    } > DATA_FLASH

    /* Note: There are no secure/non-secure boundaries for SDRAM.  These symbols are provided for the RA configuration tool. */
    __tz_SDRAM_S = ORIGIN(SDRAM);

    /* SDRAM */
    .sdram (NOLOAD):
    {
        __SDRAM_Start = .;
        KEEP(*(.sdram*))
        KEEP(*(.frame*))
        __SDRAM_End = .;
    } > SDRAM

    . = .;
    __nocache_sdram_pre_location = .;
    .nocache_sdram ALIGN(32) (NOLOAD):
    {
        __nocache_sdram_start = .;

        KEEP(*(.nocache_sdram))

        . = ALIGN(32);
        __nocache_sdram_end = .;
    } > SDRAM
    . = (SIZEOF(.nocache_sdram) > 0) ? __nocache_sdram_end : __nocache_sdram_pre_location;

    /* Note: There are no secure/non-secure boundaries for SDRAM.  These symbols are provided for the RA configuration tool. */
    __tz_SDRAM_N = __SDRAM_End;

    /* Note: There are no secure/non-secure boundaries for ID_CODE.  These symbols are provided for the RA configuration tool. */
    __tz_ID_CODE_S = ORIGIN(ID_CODE);

    /* Note: There are no secure/non-secure boundaries for ID_CODE.  These symbols are provided for the RA configuration tool.
     *       Set this symbol to the same value as __tz_ID_CODE_S so the RA configuration tool does not split the ID_CODE
     *       memory region between TrustZone projects. */
    __tz_ID_CODE_N = __tz_ID_CODE_S;

    .id_code :
    {
        __ID_Code_Start = .;
        KEEP(*(.id_code*))
        __ID_Code_End = .;
    } > ID_CODE


    /* Symbol required for RA Configuration tool. */
    __tz_OPTION_SETTING_S = ORIGIN(OPTION_SETTING_OFS);

    .option_setting_ofs :
    {
        __OPTION_SETTING_OFS_Start = .;
        KEEP(*(.option_setting_ofs0))
        . = PROJECT_SECURE_OR_FLAT ? __OPTION_SETTING_OFS_Start + 0x04 : __OPTION_SETTING_OFS_Start;
        KEEP(*(.option_setting_ofs2))
        . = PROJECT_SECURE_OR_FLAT ? __OPTION_SETTING_OFS_Start + 0x10 : __OPTION_SETTING_OFS_Start;
        KEEP(*(.option_setting_dualsel))
        __OPTION_SETTING_OFS_End = .;
    } > OPTION_SETTING_OFS = 0xFF

    .option_setting_sas :
    {
        __OPTION_SETTING_SAS_Start = .;
        KEEP(*(.option_setting_sas))
        __OPTION_SETTING_SAS_End = .;
    } > OPTION_SETTING_SAS = 0xFF

    /* Symbol required for RA Configuration tool. */
    __tz_OPTION_SETTING_N = ABSOLUTE(OPTION_SETTING_START_NS);

    .option_setting_ns :
    {
        __OPTION_SETTING_NS_Start = .;
        KEEP(*(.option_setting_ofs1))
        . = USE_OPTION_SETTING_NS ? __OPTION_SETTING_NS_Start + 0x04 : __OPTION_SETTING_NS_Start;
        KEEP(*(.option_setting_ofs3))
        . = USE_OPTION_SETTING_NS ? __OPTION_SETTING_NS_Start + 0x10 : __OPTION_SETTING_NS_Start;
        KEEP(*(.option_setting_banksel))
        . = USE_OPTION_SETTING_NS ? __OPTION_SETTING_NS_Start + 0x40 : __OPTION_SETTING_NS_Start;
        KEEP(*(.option_setting_bps0))
        . = USE_OPTION_SETTING_NS ? __OPTION_SETTING_NS_Start + 0x44 : __OPTION_SETTING_NS_Start;
        KEEP(*(.option_setting_bps1))
        . = USE_OPTION_SETTING_NS ? __OPTION_SETTING_NS_Start + 0x48 : __OPTION_SETTING_NS_Start;
        KEEP(*(.option_setting_bps2))
        . = USE_OPTION_SETTING_NS ? __OPTION_SETTING_NS_Start + 0x4C : __OPTION_SETTING_NS_Start;
        KEEP(*(.option_setting_bps3))
        . = USE_OPTION_SETTING_NS ? __OPTION_SETTING_NS_Start + 0x60 : __OPTION_SETTING_NS_Start;
        KEEP(*(.option_setting_pbps0))
        . = USE_OPTION_SETTING_NS ? __OPTION_SETTING_NS_Start + 0x64 : __OPTION_SETTING_NS_Start;
        KEEP(*(.option_setting_pbps1))
        . = USE_OPTION_SETTING_NS ? __OPTION_SETTING_NS_Start + 0x68 : __OPTION_SETTING_NS_Start;
        KEEP(*(.option_setting_pbps2))
        . = USE_OPTION_SETTING_NS ? __OPTION_SETTING_NS_Start + 0x6C : __OPTION_SETTING_NS_Start;
        KEEP(*(.option_setting_pbps3))
        __OPTION_SETTING_NS_End = .;
    } > OPTION_SETTING = 0xFF

    /* Symbol required for RA Configuration tool. */
    __tz_OPTION_SETTING_S_S = ORIGIN(OPTION_SETTING_S);

    .option_setting_s :
    {
        __OPTION_SETTING_S_Start = .;
        KEEP(*(.option_setting_ofs1_sec))
        . = PROJECT_SECURE_OR_FLAT ? __OPTION_SETTING_S_Start + 0x04 : __OPTION_SETTING_S_Start;
        KEEP(*(.option_setting_ofs3_sec))
        . = PROJECT_SECURE_OR_FLAT ? __OPTION_SETTING_S_Start + 0x10 : __OPTION_SETTING_S_Start;
        KEEP(*(.option_setting_banksel_sec))
        . = PROJECT_SECURE_OR_FLAT ? __OPTION_SETTING_S_Start + 0x40 : __OPTION_SETTING_S_Start;
        KEEP(*(.option_setting_bps_sec0))
        . = PROJECT_SECURE_OR_FLAT ? __OPTION_SETTING_S_Start + 0x44 : __OPTION_SETTING_S_Start;
        KEEP(*(.option_setting_bps_sec1))
        . = PROJECT_SECURE_OR_FLAT ? __OPTION_SETTING_S_Start + 0x48 : __OPTION_SETTING_S_Start;
        KEEP(*(.option_setting_bps_sec2))
        . = PROJECT_SECURE_OR_FLAT ? __OPTION_SETTING_S_Start + 0x4C : __OPTION_SETTING_S_Start;
        KEEP(*(.option_setting_bps_sec3))
        . = PROJECT_SECURE_OR_FLAT ? __OPTION_SETTING_S_Start + 0x60 : __OPTION_SETTING_S_Start;
        KEEP(*(.option_setting_pbps_sec0))
        . = PROJECT_SECURE_OR_FLAT ? __OPTION_SETTING_S_Start + 0x64 : __OPTION_SETTING_S_Start;
        KEEP(*(.option_setting_pbps_sec1))
        . = PROJECT_SECURE_OR_FLAT ? __OPTION_SETTING_S_Start + 0x68 : __OPTION_SETTING_S_Start;
        KEEP(*(.option_setting_pbps_sec2))
        . = PROJECT_SECURE_OR_FLAT ? __OPTION_SETTING_S_Start + 0x6C : __OPTION_SETTING_S_Start;
        KEEP(*(.option_setting_pbps_sec3))
        . = PROJECT_SECURE_OR_FLAT ? __OPTION_SETTING_S_Start + 0x80 : __OPTION_SETTING_S_Start;
        KEEP(*(.option_setting_ofs1_sel))
        . = PROJECT_SECURE_OR_FLAT ? __OPTION_SETTING_S_Start + 0x84 : __OPTION_SETTING_S_Start;
        KEEP(*(.option_setting_ofs3_sel))
        . = PROJECT_SECURE_OR_FLAT ? __OPTION_SETTING_S_Start + 0x90 : __OPTION_SETTING_S_Start;
        KEEP(*(.option_setting_banksel_sel))
        . = PROJECT_SECURE_OR_FLAT ? __OPTION_SETTING_S_Start + 0xC0 : __OPTION_SETTING_S_Start;
        KEEP(*(.option_setting_bps_sel0))
        . = PROJECT_SECURE_OR_FLAT ? __OPTION_SETTING_S_Start + 0xC4 : __OPTION_SETTING_S_Start;
        KEEP(*(.option_setting_bps_sel1))
        . = PROJECT_SECURE_OR_FLAT ? __OPTION_SETTING_S_Start + 0xC8 : __OPTION_SETTING_S_Start;
        KEEP(*(.option_setting_bps_sel2))
        . = PROJECT_SECURE_OR_FLAT ? __OPTION_SETTING_S_Start + 0xCC : __OPTION_SETTING_S_Start;
        KEEP(*(.option_setting_bps_sel3))
        __OPTION_SETTING_S_End = .;
    } > OPTION_SETTING_S = 0xFF

    /* Symbol required for RA Configuration tool. */
    __tz_OPTION_SETTING_S_N = __OPTION_SETTING_S_End;
}
