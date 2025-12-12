/* UNCRUSTIFY-OFF */
#ifndef BSP_LINKER_H
#define BSP_LINKER_H

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

/******* Solution Definitions *************/
#define BSP_PARTITION_RAM_CPU0_S_START (0x22000000)
#define BSP_PARTITION_RAM_CPU0_S_SIZE (0x174000)
#define BSP_PARTITION_SHARED_MEM_START (0x22174000)
#define BSP_PARTITION_SHARED_MEM_SIZE (0x20000)
#define BSP_PARTITION_RAM_CPU0_C_START (0x22174000)
#define BSP_PARTITION_RAM_CPU0_C_SIZE (0x0)
#define BSP_PARTITION_RAM_CPU1_S_START (0x22194000)
#define BSP_PARTITION_RAM_CPU1_S_SIZE (0x40000)
#define BSP_PARTITION_RAM_CPU1_C_START (0x221D4000)
#define BSP_PARTITION_RAM_CPU1_C_SIZE (0x0)
#define BSP_PARTITION_FLASH_CPU0_S_START (0x02000000)
#define BSP_PARTITION_FLASH_CPU0_S_SIZE (OxCO000)
#define BSP_PARTITION_FLASH_CPU0_C_START (0x020C0000)
#define BSP_PARTITION_FLASH_CPU0_C_SIZE (0x0)
#define BSP_PARTITION_FLASH_CPU1_S_START (0x020C0000)
#define BSP_PARTITION_FLASH_CPU1_S_SIZE (0x40000)
#define BSP_PARTITION_FLASH_CPU1_C_START (0x02100000)
#define BSP_PARTITION_FLASH_CPU1_C_SIZE (0x0)
#define BSP_PARTITION_DATA_FLASH_CPU0_S_START (0x27000000)
#define BSP_PARTITION_DATA_FLASH_CPU0_S_SIZE (0x0)
#define BSP_PARTITION_DATA_FLASH_CPU1_S_START (0x27000000)
#define BSP_PARTITION_DATA_FLASH_CPU1_S_SIZE (0x0)
#define BSP_PARTITION_SDRAM_CPU0_S_START (0x68000000)
#define BSP_PARTITION_SDRAM_CPU0_S_SIZE (0x4000000)
#define BSP_PARTITION_SDRAM_CPU1_S_START (0x6C000000)
#define BSP_PARTITION_SDRAM_CPU1_S_SIZE (0x4000000)
#define BSP_PARTITION_OSPI0_CS0_CPU0_S_START (0x80000000)
#define BSP_PARTITION_OSPI0_CS0_CPU0_S_SIZE (0x8000000)
#define BSP_PARTITION_OSPI0_CS0_CPU1_S_START (0x88000000)
#define BSP_PARTITION_OSPI0_CS0_CPU1_S_SIZE (0x8000000)
#define BSP_PARTITION_OSPI0_CS1_CPU0_S_START (0x90000000)
#define BSP_PARTITION_OSPI0_CS1_CPU0_S_SIZE (0x8000000)
#define BSP_PARTITION_OSPI0_CS1_CPU1_S_START (0x98000000)
#define BSP_PARTITION_OSPI0_CS1_CPU1_S_SIZE (0x8000000)
#define BSP_PARTITION_OSPI1_CS0_CPU0_S_START (0x70000000)
#define BSP_PARTITION_OSPI1_CS0_CPU0_S_SIZE (0x4000000)
#define BSP_PARTITION_OSPI1_CS0_CPU1_S_START (0x74000000)
#define BSP_PARTITION_OSPI1_CS0_CPU1_S_SIZE (0x4000000)
#define BSP_PARTITION_OSPI1_CS1_CPU0_S_START (0x78000000)
#define BSP_PARTITION_OSPI1_CS1_CPU0_S_SIZE (0x4000000)
#define BSP_PARTITION_OSPI1_CS1_CPU1_S_START (0x7C000000)
#define BSP_PARTITION_OSPI1_CS1_CPU1_S_SIZE (0x4000000)
#define BSP_PARTITION_ITCM_CPU0_S_START (0x00000000)
#define BSP_PARTITION_ITCM_CPU0_S_SIZE (0x20000)
#define BSP_PARTITION_DTCM_CPU0_S_START (0x20000000)
#define BSP_PARTITION_DTCM_CPU0_S_SIZE (0x20000)
#define BSP_PARTITION_CTCM_CPU1_S_START (0x00000000)
#define BSP_PARTITION_CTCM_CPU1_S_SIZE (0x10000)
#define BSP_PARTITION_STCM_CPU1_S_START (0x20000000)
#define BSP_PARTITION_STCM_CPU1_S_SIZE (0x10000)

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/
/* linker generated initialization table data structures types */
typedef enum e_bsp_init_mem
{
    INIT_MEM_ZERO,
    INIT_MEM_FLASH,
    INIT_MEM_DATA_FLASH,
    INIT_MEM_RAM,
    INIT_MEM_DTCM,
    INIT_MEM_ITCM,
    INIT_MEM_CTCM,
    INIT_MEM_STCM,
    INIT_MEM_OSPI0_CS0,
    INIT_MEM_OSPI0_CS1,
    INIT_MEM_OSPI1_CS0,
    INIT_MEM_OSPI1_CS1,
    INIT_MEM_QSPI_FLASH,
    INIT_MEM_SDRAM,
    INIT_MEM_SIP_FLASH,
} bsp_init_mem_t;

typedef struct st_bsp_init_type
{
    uint32_t copy_64 :8; /* if 1, must use 64 bit copy operation (to keep ecc happy) */
    uint32_t external :8; /* =1 if either source or destination is external, else 0  */
    uint32_t source_type :8;
    uint32_t destination_type :8;
} bsp_init_type_t;

typedef struct st_bsp_init_zero_info
{
    uint32_t *const p_base;
    uint32_t *const p_limit;
    bsp_init_type_t type;
} bsp_init_zero_info_t;

typedef struct st_bsp_init_copy_info
{
    uint32_t *const p_base;
    uint32_t *const p_limit;
    uint32_t *const p_load;
    bsp_init_type_t type;
} bsp_init_copy_info_t;
typedef struct st_bsp_init_nocache_info
{
    uint32_t *const p_base;
    uint32_t *const p_limit;
} bsp_mpu_nocache_info_t;

typedef struct st_bsp_init_info
{
    uint32_t zero_count;
    bsp_init_zero_info_t const *const p_zero_list;
    uint32_t copy_count;
    bsp_init_copy_info_t const *const p_copy_list;
    uint32_t nocache_count;
    bsp_mpu_nocache_info_t const *const p_nocache_list;
} bsp_init_info_t;

/***********************************************************************************************************************
 * Exported global variables
 **********************************************************************************************************************/

extern bsp_init_info_t const g_init_info;
/* These symbols are used for sau/idau configuration in a secure project */

/***********************************************************************************************************************
 * Exported global functions (to be accessed by other files)
 **********************************************************************************************************************/
#endif   // BSP_LINKER_H
#ifdef BSP_LINKER_C
/***********************************************************************************************************************
 * Objects allocated by bsp_linker.c
 **********************************************************************************************************************/
/* DDSC symbol definitions */
/* Zero initialization tables */
extern uint32_t __sdram_zero_nocache$$Base;
extern uint32_t __sdram_zero_nocache$$Limit;
extern uint32_t __sdram_zero$$Base;
extern uint32_t __sdram_zero$$Limit;
extern uint32_t __ospi0_cs0_zero_nocache$$Base;
extern uint32_t __ospi0_cs0_zero_nocache$$Limit;
extern uint32_t __ospi0_cs0_zero$$Base;
extern uint32_t __ospi0_cs0_zero$$Limit;
extern uint32_t __ospi1_cs0_zero_nocache$$Base;
extern uint32_t __ospi1_cs0_zero_nocache$$Limit;
extern uint32_t __ospi1_cs0_zero$$Base;
extern uint32_t __ospi1_cs0_zero$$Limit;
extern uint32_t __itcm_zero$$Base;
extern uint32_t __itcm_zero$$Limit;
extern uint32_t __dtcm_zero$$Base;
extern uint32_t __dtcm_zero$$Limit;
extern uint32_t __ram_zero_nocache$$Base;
extern uint32_t __ram_zero_nocache$$Limit;
extern uint32_t __ram_zero$$Base;
extern uint32_t __ram_zero$$Limit;
static const bsp_init_zero_info_t zero_list[] =
{
  {.p_base = &__sdram_zero_nocache$$Base, .p_limit = &__sdram_zero_nocache$$Limit,.type={.copy_64 = 0, .external = 1, .source_type = INIT_MEM_ZERO, .destination_type = INIT_MEM_SDRAM}},
  {.p_base = &__sdram_zero$$Base, .p_limit = &__sdram_zero$$Limit,.type={.copy_64 = 0, .external = 1, .source_type = INIT_MEM_ZERO, .destination_type = INIT_MEM_SDRAM}},
  {.p_base = &__ospi0_cs0_zero_nocache$$Base, .p_limit = &__ospi0_cs0_zero_nocache$$Limit,.type={.copy_64 = 0, .external = 1, .source_type = INIT_MEM_ZERO, .destination_type = INIT_MEM_OSPI0_CS0}},
  {.p_base = &__ospi0_cs0_zero$$Base, .p_limit = &__ospi0_cs0_zero$$Limit,.type={.copy_64 = 0, .external = 1, .source_type = INIT_MEM_ZERO, .destination_type = INIT_MEM_OSPI0_CS0}},
  {.p_base = &__ospi1_cs0_zero_nocache$$Base, .p_limit = &__ospi1_cs0_zero_nocache$$Limit,.type={.copy_64 = 0, .external = 1, .source_type = INIT_MEM_ZERO, .destination_type = INIT_MEM_OSPI1_CS0}},
  {.p_base = &__ospi1_cs0_zero$$Base, .p_limit = &__ospi1_cs0_zero$$Limit,.type={.copy_64 = 0, .external = 1, .source_type = INIT_MEM_ZERO, .destination_type = INIT_MEM_OSPI1_CS0}},
  {.p_base = &__itcm_zero$$Base, .p_limit = &__itcm_zero$$Limit,.type={.copy_64 = 1, .external = 0, .source_type = INIT_MEM_ZERO, .destination_type = INIT_MEM_ITCM}},
  {.p_base = &__dtcm_zero$$Base, .p_limit = &__dtcm_zero$$Limit,.type={.copy_64 = 1, .external = 0, .source_type = INIT_MEM_ZERO, .destination_type = INIT_MEM_DTCM}},
  {.p_base = &__ram_zero_nocache$$Base, .p_limit = &__ram_zero_nocache$$Limit,.type={.copy_64 = 0, .external = 0, .source_type = INIT_MEM_ZERO, .destination_type = INIT_MEM_RAM}},
  {.p_base = &__ram_zero$$Base, .p_limit = &__ram_zero$$Limit,.type={.copy_64 = 0, .external = 0, .source_type = INIT_MEM_ZERO, .destination_type = INIT_MEM_RAM}}
};
/* Load initialization tables */
extern uint32_t __sdram_from_ospi0_cs1$$Base;
extern uint32_t __sdram_from_ospi0_cs1$$Limit;
extern uint32_t __sdram_from_ospi0_cs1$$Load;
extern uint32_t __sdram_from_ospi1_cs1$$Base;
extern uint32_t __sdram_from_ospi1_cs1$$Limit;
extern uint32_t __sdram_from_ospi1_cs1$$Load;
extern uint32_t __sdram_from_data_flash$$Base;
extern uint32_t __sdram_from_data_flash$$Limit;
extern uint32_t __sdram_from_data_flash$$Load;
extern uint32_t __sdram_from_flash$$Base;
extern uint32_t __sdram_from_flash$$Limit;
extern uint32_t __sdram_from_flash$$Load;
extern uint32_t __ospi0_cs0_from_ospi0_cs1$$Base;
extern uint32_t __ospi0_cs0_from_ospi0_cs1$$Limit;
extern uint32_t __ospi0_cs0_from_ospi0_cs1$$Load;
extern uint32_t __ospi0_cs0_from_ospi1_cs1$$Base;
extern uint32_t __ospi0_cs0_from_ospi1_cs1$$Limit;
extern uint32_t __ospi0_cs0_from_ospi1_cs1$$Load;
extern uint32_t __ospi0_cs0_from_data_flash$$Base;
extern uint32_t __ospi0_cs0_from_data_flash$$Limit;
extern uint32_t __ospi0_cs0_from_data_flash$$Load;
extern uint32_t __ospi0_cs0_from_flash$$Base;
extern uint32_t __ospi0_cs0_from_flash$$Limit;
extern uint32_t __ospi0_cs0_from_flash$$Load;
extern uint32_t __ospi1_cs0_from_ospi0_cs1$$Base;
extern uint32_t __ospi1_cs0_from_ospi0_cs1$$Limit;
extern uint32_t __ospi1_cs0_from_ospi0_cs1$$Load;
extern uint32_t __ospi1_cs0_from_ospi1_cs1$$Base;
extern uint32_t __ospi1_cs0_from_ospi1_cs1$$Limit;
extern uint32_t __ospi1_cs0_from_ospi1_cs1$$Load;
extern uint32_t __ospi1_cs0_from_data_flash$$Base;
extern uint32_t __ospi1_cs0_from_data_flash$$Limit;
extern uint32_t __ospi1_cs0_from_data_flash$$Load;
extern uint32_t __ospi1_cs0_from_flash$$Base;
extern uint32_t __ospi1_cs0_from_flash$$Limit;
extern uint32_t __ospi1_cs0_from_flash$$Load;
extern uint32_t __itcm_from_ospi0_cs1$$Base;
extern uint32_t __itcm_from_ospi0_cs1$$Limit;
extern uint32_t __itcm_from_ospi0_cs1$$Load;
extern uint32_t __itcm_from_ospi1_cs1$$Base;
extern uint32_t __itcm_from_ospi1_cs1$$Limit;
extern uint32_t __itcm_from_ospi1_cs1$$Load;
extern uint32_t __itcm_from_data_flash$$Base;
extern uint32_t __itcm_from_data_flash$$Limit;
extern uint32_t __itcm_from_data_flash$$Load;
extern uint32_t __itcm_from_flash$$Base;
extern uint32_t __itcm_from_flash$$Limit;
extern uint32_t __itcm_from_flash$$Load;
extern uint32_t __dtcm_from_ospi0_cs1$$Base;
extern uint32_t __dtcm_from_ospi0_cs1$$Limit;
extern uint32_t __dtcm_from_ospi0_cs1$$Load;
extern uint32_t __dtcm_from_ospi1_cs1$$Base;
extern uint32_t __dtcm_from_ospi1_cs1$$Limit;
extern uint32_t __dtcm_from_ospi1_cs1$$Load;
extern uint32_t __dtcm_from_data_flash$$Base;
extern uint32_t __dtcm_from_data_flash$$Limit;
extern uint32_t __dtcm_from_data_flash$$Load;
extern uint32_t __dtcm_from_flash$$Base;
extern uint32_t __dtcm_from_flash$$Limit;
extern uint32_t __dtcm_from_flash$$Load;
extern uint32_t __ram_from_ospi0_cs1$$Base;
extern uint32_t __ram_from_ospi0_cs1$$Limit;
extern uint32_t __ram_from_ospi0_cs1$$Load;
extern uint32_t __ram_from_ospi1_cs1$$Base;
extern uint32_t __ram_from_ospi1_cs1$$Limit;
extern uint32_t __ram_from_ospi1_cs1$$Load;
extern uint32_t __ram_from_data_flash$$Base;
extern uint32_t __ram_from_data_flash$$Limit;
extern uint32_t __ram_from_data_flash$$Load;
extern uint32_t __ram_from_flash$$Base;
extern uint32_t __ram_from_flash$$Limit;
extern uint32_t __ram_from_flash$$Load;
static const bsp_init_copy_info_t copy_list[] =
{
  {.p_base = &__sdram_from_ospi0_cs1$$Base, .p_limit = &__sdram_from_ospi0_cs1$$Limit, .p_load = &__sdram_from_ospi0_cs1$$Load,.type={.copy_64 = 0, .external = 1, .source_type = INIT_MEM_OSPI0_CS1, .destination_type = INIT_MEM_SDRAM}},
  {.p_base = &__sdram_from_ospi1_cs1$$Base, .p_limit = &__sdram_from_ospi1_cs1$$Limit, .p_load = &__sdram_from_ospi1_cs1$$Load,.type={.copy_64 = 0, .external = 1, .source_type = INIT_MEM_OSPI1_CS1, .destination_type = INIT_MEM_SDRAM}},
  {.p_base = &__sdram_from_data_flash$$Base, .p_limit = &__sdram_from_data_flash$$Limit, .p_load = &__sdram_from_data_flash$$Load,.type={.copy_64 = 0, .external = 1, .source_type = INIT_MEM_DATA_FLASH, .destination_type = INIT_MEM_SDRAM}},
  {.p_base = &__sdram_from_flash$$Base, .p_limit = &__sdram_from_flash$$Limit, .p_load = &__sdram_from_flash$$Load,.type={.copy_64 = 0, .external = 1, .source_type = INIT_MEM_FLASH, .destination_type = INIT_MEM_SDRAM}},
  {.p_base = &__ospi0_cs0_from_ospi0_cs1$$Base, .p_limit = &__ospi0_cs0_from_ospi0_cs1$$Limit, .p_load = &__ospi0_cs0_from_ospi0_cs1$$Load,.type={.copy_64 = 0, .external = 1, .source_type = INIT_MEM_OSPI0_CS1, .destination_type = INIT_MEM_OSPI0_CS0}},
  {.p_base = &__ospi0_cs0_from_ospi1_cs1$$Base, .p_limit = &__ospi0_cs0_from_ospi1_cs1$$Limit, .p_load = &__ospi0_cs0_from_ospi1_cs1$$Load,.type={.copy_64 = 0, .external = 1, .source_type = INIT_MEM_OSPI1_CS1, .destination_type = INIT_MEM_OSPI0_CS0}},
  {.p_base = &__ospi0_cs0_from_data_flash$$Base, .p_limit = &__ospi0_cs0_from_data_flash$$Limit, .p_load = &__ospi0_cs0_from_data_flash$$Load,.type={.copy_64 = 0, .external = 1, .source_type = INIT_MEM_DATA_FLASH, .destination_type = INIT_MEM_OSPI0_CS0}},
  {.p_base = &__ospi0_cs0_from_flash$$Base, .p_limit = &__ospi0_cs0_from_flash$$Limit, .p_load = &__ospi0_cs0_from_flash$$Load,.type={.copy_64 = 0, .external = 1, .source_type = INIT_MEM_FLASH, .destination_type = INIT_MEM_OSPI0_CS0}},
  {.p_base = &__ospi1_cs0_from_ospi0_cs1$$Base, .p_limit = &__ospi1_cs0_from_ospi0_cs1$$Limit, .p_load = &__ospi1_cs0_from_ospi0_cs1$$Load,.type={.copy_64 = 0, .external = 1, .source_type = INIT_MEM_OSPI0_CS1, .destination_type = INIT_MEM_OSPI1_CS0}},
  {.p_base = &__ospi1_cs0_from_ospi1_cs1$$Base, .p_limit = &__ospi1_cs0_from_ospi1_cs1$$Limit, .p_load = &__ospi1_cs0_from_ospi1_cs1$$Load,.type={.copy_64 = 0, .external = 1, .source_type = INIT_MEM_OSPI1_CS1, .destination_type = INIT_MEM_OSPI1_CS0}},
  {.p_base = &__ospi1_cs0_from_data_flash$$Base, .p_limit = &__ospi1_cs0_from_data_flash$$Limit, .p_load = &__ospi1_cs0_from_data_flash$$Load,.type={.copy_64 = 0, .external = 1, .source_type = INIT_MEM_DATA_FLASH, .destination_type = INIT_MEM_OSPI1_CS0}},
  {.p_base = &__ospi1_cs0_from_flash$$Base, .p_limit = &__ospi1_cs0_from_flash$$Limit, .p_load = &__ospi1_cs0_from_flash$$Load,.type={.copy_64 = 0, .external = 1, .source_type = INIT_MEM_FLASH, .destination_type = INIT_MEM_OSPI1_CS0}},
  {.p_base = &__itcm_from_ospi0_cs1$$Base, .p_limit = &__itcm_from_ospi0_cs1$$Limit, .p_load = &__itcm_from_ospi0_cs1$$Load,.type={.copy_64 = 1, .external = 1, .source_type = INIT_MEM_OSPI0_CS1, .destination_type = INIT_MEM_ITCM}},
  {.p_base = &__itcm_from_ospi1_cs1$$Base, .p_limit = &__itcm_from_ospi1_cs1$$Limit, .p_load = &__itcm_from_ospi1_cs1$$Load,.type={.copy_64 = 1, .external = 1, .source_type = INIT_MEM_OSPI1_CS1, .destination_type = INIT_MEM_ITCM}},
  {.p_base = &__itcm_from_data_flash$$Base, .p_limit = &__itcm_from_data_flash$$Limit, .p_load = &__itcm_from_data_flash$$Load,.type={.copy_64 = 1, .external = 0, .source_type = INIT_MEM_DATA_FLASH, .destination_type = INIT_MEM_ITCM}},
  {.p_base = &__itcm_from_flash$$Base, .p_limit = &__itcm_from_flash$$Limit, .p_load = &__itcm_from_flash$$Load,.type={.copy_64 = 1, .external = 0, .source_type = INIT_MEM_FLASH, .destination_type = INIT_MEM_ITCM}},
  {.p_base = &__dtcm_from_ospi0_cs1$$Base, .p_limit = &__dtcm_from_ospi0_cs1$$Limit, .p_load = &__dtcm_from_ospi0_cs1$$Load,.type={.copy_64 = 1, .external = 1, .source_type = INIT_MEM_OSPI0_CS1, .destination_type = INIT_MEM_DTCM}},
  {.p_base = &__dtcm_from_ospi1_cs1$$Base, .p_limit = &__dtcm_from_ospi1_cs1$$Limit, .p_load = &__dtcm_from_ospi1_cs1$$Load,.type={.copy_64 = 1, .external = 1, .source_type = INIT_MEM_OSPI1_CS1, .destination_type = INIT_MEM_DTCM}},
  {.p_base = &__dtcm_from_data_flash$$Base, .p_limit = &__dtcm_from_data_flash$$Limit, .p_load = &__dtcm_from_data_flash$$Load,.type={.copy_64 = 1, .external = 0, .source_type = INIT_MEM_DATA_FLASH, .destination_type = INIT_MEM_DTCM}},
  {.p_base = &__dtcm_from_flash$$Base, .p_limit = &__dtcm_from_flash$$Limit, .p_load = &__dtcm_from_flash$$Load,.type={.copy_64 = 1, .external = 0, .source_type = INIT_MEM_FLASH, .destination_type = INIT_MEM_DTCM}},
  {.p_base = &__ram_from_ospi0_cs1$$Base, .p_limit = &__ram_from_ospi0_cs1$$Limit, .p_load = &__ram_from_ospi0_cs1$$Load,.type={.copy_64 = 0, .external = 1, .source_type = INIT_MEM_OSPI0_CS1, .destination_type = INIT_MEM_RAM}},
  {.p_base = &__ram_from_ospi1_cs1$$Base, .p_limit = &__ram_from_ospi1_cs1$$Limit, .p_load = &__ram_from_ospi1_cs1$$Load,.type={.copy_64 = 0, .external = 1, .source_type = INIT_MEM_OSPI1_CS1, .destination_type = INIT_MEM_RAM}},
  {.p_base = &__ram_from_data_flash$$Base, .p_limit = &__ram_from_data_flash$$Limit, .p_load = &__ram_from_data_flash$$Load,.type={.copy_64 = 0, .external = 0, .source_type = INIT_MEM_DATA_FLASH, .destination_type = INIT_MEM_RAM}},
  {.p_base = &__ram_from_flash$$Base, .p_limit = &__ram_from_flash$$Limit, .p_load = &__ram_from_flash$$Load,.type={.copy_64 = 0, .external = 0, .source_type = INIT_MEM_FLASH, .destination_type = INIT_MEM_RAM}}
};
/* nocache regions */
extern uint32_t __sdram_noinit_nocache$$Base;
extern uint32_t __sdram_noinit_nocache$$Limit;
extern uint32_t __sdram_zero_nocache$$Base;
extern uint32_t __sdram_zero_nocache$$Limit;
extern uint32_t __ospi0_cs0_noinit_nocache$$Base;
extern uint32_t __ospi0_cs0_noinit_nocache$$Limit;
extern uint32_t __ospi0_cs0_zero_nocache$$Base;
extern uint32_t __ospi0_cs0_zero_nocache$$Limit;
extern uint32_t __ospi1_cs0_noinit_nocache$$Base;
extern uint32_t __ospi1_cs0_noinit_nocache$$Limit;
extern uint32_t __ospi1_cs0_zero_nocache$$Base;
extern uint32_t __ospi1_cs0_zero_nocache$$Limit;
extern uint32_t __ram_noinit_nocache$$Base;
extern uint32_t __ram_noinit_nocache$$Limit;
extern uint32_t __ram_zero_nocache$$Base;
extern uint32_t __ram_zero_nocache$$Limit;
static const bsp_mpu_nocache_info_t nocache_list[] =
{
  {.p_base = &__sdram_noinit_nocache$$Base, .p_limit = &__sdram_zero_nocache$$Limit},
  {.p_base = &__ospi0_cs0_noinit_nocache$$Base, .p_limit = &__ospi0_cs0_zero_nocache$$Limit},
  {.p_base = &__ospi1_cs0_noinit_nocache$$Base, .p_limit = &__ospi1_cs0_zero_nocache$$Limit},
  {.p_base = &__ram_noinit_nocache$$Base, .p_limit = &__ram_zero_nocache$$Limit},
};

/* initialization data structure */
const bsp_init_info_t g_init_info =
{
    .zero_count  = sizeof(zero_list) / sizeof(zero_list[0]),
    .p_zero_list = zero_list,
    .copy_count  = sizeof(copy_list) / sizeof(copy_list[0]),
    .p_copy_list = copy_list,
    .nocache_count  = sizeof(nocache_list) / sizeof(nocache_list[0]),
    .p_nocache_list = nocache_list
};

#endif   // BSP_LINKER_C

/* UNCRUSTIFY-ON */
