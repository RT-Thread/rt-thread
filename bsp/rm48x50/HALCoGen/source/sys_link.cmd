/*----------------------------------------------------------------------------*/
/* sys_link.cmd                                                               */
/*                                                                            */
/* (c) Texas Instruments 2009-2013, All rights reserved.                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/* USER CODE BEGIN (7) */
/* USER CODE END */


/*----------------------------------------------------------------------------*/
/* Linker Settings                                                            */

--retain="*(.intvecs)"
--retain="*(FSymTab)"
--retain="*(VSymTab)"

/* USER CODE BEGIN (8) */
/* USER CODE END */

/*----------------------------------------------------------------------------*/
/* Memory Map                                                                 */

MEMORY
{
    VECTORS (X)  : origin=0x00000000 length=0x00000020
    FLASH0  (RX) : origin=0x00000020 length=0x0017FFE0
    FLASH1  (RX) : origin=0x00180000 length=0x00180000
    STACKS  (RW) : origin=0x08000000 length=0x00001500
    RAM     (RW) : origin=0x08001500 length=0x0003eaff

/* USER CODE BEGIN (9) */
/* USER CODE END */
}

/* USER CODE BEGIN (10) */
/* USER CODE END */


/*----------------------------------------------------------------------------*/
/* Section Configuration                                                      */

SECTIONS
{
    .intvecs : {} > VECTORS
    .text    : {} > FLASH0 | FLASH1
    .const   : {} > FLASH0 | FLASH1
    .cinit   : {} > FLASH0 | FLASH1
    .pinit   : {} > FLASH0 | FLASH1
    GROUP
    {
        .bss     : {}
        .data    : {}
        .sysmem  : {}
        ._dummy  : {system_data_end = .;}
    } > RAM


/* USER CODE BEGIN (11) */
    /* place this section in the last section in RAM. The brain damaged linker
     * could only create symbols in sections. */
    ._FSymTab  : {
        __fsymtab_start = .;
        *(FSymTab)
        __fsymtab_end = .;
    } > FLASH0 | FLASH1
    ._VSymTab  : {
        __vsymtab_start = .;
        *(VSymTab)
        __vsymtab_end = .;
    } > FLASH0 | FLASH1
/* USER CODE END */
}

/* USER CODE BEGIN (12) */
/* USER CODE END */


/*----------------------------------------------------------------------------*/
/* Misc                                                                       */

/* USER CODE BEGIN (13) */
/* USER CODE END */
/*----------------------------------------------------------------------------*/

