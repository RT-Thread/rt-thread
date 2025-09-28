/* UNCRUSTIFY-OFF */
#ifndef BSP_LINKER_H
#define BSP_LINKER_H

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

/******* Solution Definitions *************/

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

typedef struct st_bsp_init_info
{
    uint32_t zero_count;
    bsp_init_zero_info_t const *const p_zero_list;
    uint32_t copy_count;
    bsp_init_copy_info_t const *const p_copy_list;
} bsp_init_info_t;

/***********************************************************************************************************************
 * Exported global variables
 **********************************************************************************************************************/

extern bsp_init_info_t const g_init_info;

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
extern uint32_t __ram_zero$$Base;
extern uint32_t __ram_zero$$Limit;
static const bsp_init_zero_info_t zero_list[] =
{
  {.p_base = &__ram_zero$$Base, .p_limit = &__ram_zero$$Limit,.type={.copy_64 = 0, .external = 0, .source_type = INIT_MEM_ZERO, .destination_type = INIT_MEM_RAM}}
};
/* Load initialization tables */
extern uint32_t __ram_from_data_flash$$Base;
extern uint32_t __ram_from_data_flash$$Limit;
extern uint32_t __ram_from_data_flash$$Load;
extern uint32_t __ram_from_flash$$Base;
extern uint32_t __ram_from_flash$$Limit;
extern uint32_t __ram_from_flash$$Load;
static const bsp_init_copy_info_t copy_list[] =
{
  {.p_base = &__ram_from_data_flash$$Base, .p_limit = &__ram_from_data_flash$$Limit, .p_load = &__ram_from_data_flash$$Load,.type={.copy_64 = 0, .external = 0, .source_type = INIT_MEM_DATA_FLASH, .destination_type = INIT_MEM_RAM}},
  {.p_base = &__ram_from_flash$$Base, .p_limit = &__ram_from_flash$$Limit, .p_load = &__ram_from_flash$$Load,.type={.copy_64 = 0, .external = 0, .source_type = INIT_MEM_FLASH, .destination_type = INIT_MEM_RAM}}
};

/* initialization data structure */
const bsp_init_info_t g_init_info =
{
    .zero_count  = sizeof(zero_list) / sizeof(zero_list[0]),
    .p_zero_list = zero_list,
    .copy_count  = sizeof(copy_list) / sizeof(copy_list[0]),
    .p_copy_list = copy_list
};

#endif   // BSP_LINKER_C

/* UNCRUSTIFY-ON */
