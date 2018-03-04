/*!
*******************************************************************************
**
** \file      gh_crypto.h
**
** \brief     Cryptography Engine.
**
**            Copyright:   2012 - 2016 (C) GoKe Microelectronics
**
** \attention THIS SAMPLE CODE IS PROVIDED AS IS. GOKE MICROELECTRONICS
**            ACCEPTS NO RESPONSIBILITY OR LIABILITY FOR ANY ERRORS OR
**            OMMISSIONS.
**
** \note      Do not modify this file as it is generated automatically.
**
******************************************************************************/
#ifndef _GH_CRYPTO_H
#define _GH_CRYPTO_H

#ifdef __LINUX__
#include "reg4linux.h"
#else
#define FIO_ADDRESS(block,address) (address)
#define FIO_MOFFSET(block,moffset) (moffset)
#endif

#ifndef __LINUX__
#include "gtypes.h" /* global type definitions */
#include "gh_lib_cfg.h" /* configuration */
#endif

#define GH_CRYPTO_ENABLE_DEBUG_PRINT   0
#ifdef __LINUX__
#define GH_CRYPTO_DEBUG_PRINT_FUNCTION printk
#else
#define GH_CRYPTO_DEBUG_PRINT_FUNCTION printf
#endif
#ifndef __LINUX__
#if GH_CRYPTO_ENABLE_DEBUG_PRINT
#include <stdio.h>
#endif
#endif

/*----------------------------------------------------------------------------*/
/* registers                                                                  */
/*----------------------------------------------------------------------------*/
#define REG_CRYPTO_DES_KEY                                  FIO_ADDRESS(CRYPTO,0x90014000) /* read/write */
#define REG_CRYPTO_DES_INPUT                                FIO_ADDRESS(CRYPTO,0x90014008) /* read/write */
#define REG_CRYPTO_DES_OPCODE                               FIO_ADDRESS(CRYPTO,0x90014010) /* read/write */
#define REG_CRYPTO_DES_OUTPUT_RDY                           FIO_ADDRESS(CRYPTO,0x90014014) /* read */
#define REG_CRYPTO_DES_OUTPUT                               FIO_ADDRESS(CRYPTO,0x90014018) /* read */
#define REG_CRYPTO_DES_INTERRUPT                            FIO_ADDRESS(CRYPTO,0x90014020) /* read/write */
#define REG_CRYPTO_AES_128_KEY                              FIO_ADDRESS(CRYPTO,0x90014024) /* read/write */
#define REG_CRYPTO_AES_192_KEY                              FIO_ADDRESS(CRYPTO,0x90014034) /* read/write */
#define REG_CRYPTO_AES_256_KEY                              FIO_ADDRESS(CRYPTO,0x9001404C) /* read/write */
#define REG_CRYPTO_AES_INPUT                                FIO_ADDRESS(CRYPTO,0x9001406C) /* read/write */
#define REG_CRYPTO_AES_OPCODE                               FIO_ADDRESS(CRYPTO,0x9001407C) /* read/write */
#define REG_CRYPTO_AES_OUTPUT_RDY                           FIO_ADDRESS(CRYPTO,0x90014080) /* read */
#define REG_CRYPTO_AES_OUTPUT                               FIO_ADDRESS(CRYPTO,0x90014084) /* read */
#define REG_CRYPTO_AES_INTERRUPT                            FIO_ADDRESS(CRYPTO,0x90014094) /* read/write */
#define REG_CRYPTO_EFUSE_BOOT_SW_DIS                        FIO_ADDRESS(CRYPTO,0x90014098) /* read/write */

/*----------------------------------------------------------------------------*/
/* bit group structures                                                       */
/*----------------------------------------------------------------------------*/
typedef union { /* CRYPTO_DES_Opcode */
    U32 all;
    struct {
        U32 mode                        : 1;
        U32                             : 31;
    } bitc;
} GH_CRYPTO_DES_OPCODE_S;

typedef union { /* CRYPTO_DES_Output_Rdy */
    U32 all;
    struct {
        U32 rdy                         : 1;
        U32                             : 31;
    } bitc;
} GH_CRYPTO_DES_OUTPUT_RDY_S;

typedef union { /* CRYPTO_DES_Interrupt */
    U32 all;
    struct {
        U32 en                          : 1;
        U32                             : 31;
    } bitc;
} GH_CRYPTO_DES_INTERRUPT_S;

typedef union { /* CRYPTO_AES_Opcode */
    U32 all;
    struct {
        U32 mode                        : 1;
        U32                             : 31;
    } bitc;
} GH_CRYPTO_AES_OPCODE_S;

typedef union { /* CRYPTO_AES_Output_Rdy */
    U32 all;
    struct {
        U32 rdy                         : 1;
        U32                             : 31;
    } bitc;
} GH_CRYPTO_AES_OUTPUT_RDY_S;

typedef union { /* CRYPTO_AES_Interrupt */
    U32 all;
    struct {
        U32 en                          : 1;
        U32                             : 31;
    } bitc;
} GH_CRYPTO_AES_INTERRUPT_S;

typedef union { /* CRYPTO_EFUSE_BOOT_SW_DIS */
    U32 all;
    struct {
        U32 efuse_boot_sw               : 1;
        U32 efuse_boot_dis              : 1;
        U32                             : 30;
    } bitc;
} GH_CRYPTO_EFUSE_BOOT_SW_DIS_S;


/*----------------------------------------------------------------------------*/
/* mirror variables                                                           */
/*----------------------------------------------------------------------------*/

#ifdef __cplusplus
extern "C" {
#endif

/*----------------------------------------------------------------------------*/
/* register CRYPTO_DES_Key (read/write)                                       */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'CRYPTO_DES_Key'. */
void GH_CRYPTO_set_DES_Key(U8 index, U32 data);
/*! \brief Reads the register 'CRYPTO_DES_Key'. */
U32  GH_CRYPTO_get_DES_Key(U8 index);

/*----------------------------------------------------------------------------*/
/* register CRYPTO_DES_Input (read/write)                                     */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'CRYPTO_DES_Input'. */
void GH_CRYPTO_set_DES_Input(U8 index, U32 data);
/*! \brief Reads the register 'CRYPTO_DES_Input'. */
U32  GH_CRYPTO_get_DES_Input(U8 index);

/*----------------------------------------------------------------------------*/
/* register CRYPTO_DES_Opcode (read/write)                                    */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'CRYPTO_DES_Opcode'. */
void GH_CRYPTO_set_DES_Opcode(U32 data);
/*! \brief Reads the register 'CRYPTO_DES_Opcode'. */
U32  GH_CRYPTO_get_DES_Opcode(void);
/*! \brief Writes the bit group 'mode' of register 'CRYPTO_DES_Opcode'. */
void GH_CRYPTO_set_DES_Opcode_mode(U8 data);
/*! \brief Reads the bit group 'mode' of register 'CRYPTO_DES_Opcode'. */
U8   GH_CRYPTO_get_DES_Opcode_mode(void);

/*----------------------------------------------------------------------------*/
/* register CRYPTO_DES_Output_Rdy (read)                                      */
/*----------------------------------------------------------------------------*/
/*! \brief Reads the register 'CRYPTO_DES_Output_Rdy'. */
U32  GH_CRYPTO_get_DES_Output_Rdy(void);
/*! \brief Reads the bit group 'Rdy' of register 'CRYPTO_DES_Output_Rdy'. */
U8   GH_CRYPTO_get_DES_Output_Rdy_Rdy(void);

/*----------------------------------------------------------------------------*/
/* register CRYPTO_DES_Output (read)                                          */
/*----------------------------------------------------------------------------*/
/*! \brief Reads the register 'CRYPTO_DES_Output'. */
U32  GH_CRYPTO_get_DES_Output(U8 index);

/*----------------------------------------------------------------------------*/
/* register CRYPTO_DES_Interrupt (read/write)                                 */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'CRYPTO_DES_Interrupt'. */
void GH_CRYPTO_set_DES_Interrupt(U32 data);
/*! \brief Reads the register 'CRYPTO_DES_Interrupt'. */
U32  GH_CRYPTO_get_DES_Interrupt(void);
/*! \brief Writes the bit group 'En' of register 'CRYPTO_DES_Interrupt'. */
void GH_CRYPTO_set_DES_Interrupt_En(U8 data);
/*! \brief Reads the bit group 'En' of register 'CRYPTO_DES_Interrupt'. */
U8   GH_CRYPTO_get_DES_Interrupt_En(void);

/*----------------------------------------------------------------------------*/
/* register CRYPTO_AES_128_Key (read/write)                                   */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'CRYPTO_AES_128_Key'. */
void GH_CRYPTO_set_AES_128_Key(U8 index, U32 data);
/*! \brief Reads the register 'CRYPTO_AES_128_Key'. */
U32  GH_CRYPTO_get_AES_128_Key(U8 index);

/*----------------------------------------------------------------------------*/
/* register CRYPTO_AES_192_Key (read/write)                                   */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'CRYPTO_AES_192_Key'. */
void GH_CRYPTO_set_AES_192_Key(U8 index, U32 data);
/*! \brief Reads the register 'CRYPTO_AES_192_Key'. */
U32  GH_CRYPTO_get_AES_192_Key(U8 index);

/*----------------------------------------------------------------------------*/
/* register CRYPTO_AES_256_Key (read/write)                                   */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'CRYPTO_AES_256_Key'. */
void GH_CRYPTO_set_AES_256_Key(U8 index, U32 data);
/*! \brief Reads the register 'CRYPTO_AES_256_Key'. */
U32  GH_CRYPTO_get_AES_256_Key(U8 index);

/*----------------------------------------------------------------------------*/
/* register CRYPTO_AES_Input (read/write)                                     */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'CRYPTO_AES_Input'. */
void GH_CRYPTO_set_AES_Input(U8 index, U32 data);
/*! \brief Reads the register 'CRYPTO_AES_Input'. */
U32  GH_CRYPTO_get_AES_Input(U8 index);

/*----------------------------------------------------------------------------*/
/* register CRYPTO_AES_Opcode (read/write)                                    */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'CRYPTO_AES_Opcode'. */
void GH_CRYPTO_set_AES_Opcode(U32 data);
/*! \brief Reads the register 'CRYPTO_AES_Opcode'. */
U32  GH_CRYPTO_get_AES_Opcode(void);
/*! \brief Writes the bit group 'mode' of register 'CRYPTO_AES_Opcode'. */
void GH_CRYPTO_set_AES_Opcode_mode(U8 data);
/*! \brief Reads the bit group 'mode' of register 'CRYPTO_AES_Opcode'. */
U8   GH_CRYPTO_get_AES_Opcode_mode(void);

/*----------------------------------------------------------------------------*/
/* register CRYPTO_AES_Output_Rdy (read)                                      */
/*----------------------------------------------------------------------------*/
/*! \brief Reads the register 'CRYPTO_AES_Output_Rdy'. */
U32  GH_CRYPTO_get_AES_Output_Rdy(void);
/*! \brief Reads the bit group 'Rdy' of register 'CRYPTO_AES_Output_Rdy'. */
U8   GH_CRYPTO_get_AES_Output_Rdy_Rdy(void);

/*----------------------------------------------------------------------------*/
/* register CRYPTO_AES_Output (read)                                          */
/*----------------------------------------------------------------------------*/
/*! \brief Reads the register 'CRYPTO_AES_Output'. */
U32  GH_CRYPTO_get_AES_Output(U8 index);

/*----------------------------------------------------------------------------*/
/* register CRYPTO_AES_Interrupt (read/write)                                 */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'CRYPTO_AES_Interrupt'. */
void GH_CRYPTO_set_AES_Interrupt(U32 data);
/*! \brief Reads the register 'CRYPTO_AES_Interrupt'. */
U32  GH_CRYPTO_get_AES_Interrupt(void);
/*! \brief Writes the bit group 'En' of register 'CRYPTO_AES_Interrupt'. */
void GH_CRYPTO_set_AES_Interrupt_En(U8 data);
/*! \brief Reads the bit group 'En' of register 'CRYPTO_AES_Interrupt'. */
U8   GH_CRYPTO_get_AES_Interrupt_En(void);

/*----------------------------------------------------------------------------*/
/* register CRYPTO_EFUSE_BOOT_SW_DIS (read/write)                             */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'CRYPTO_EFUSE_BOOT_SW_DIS'. */
void GH_CRYPTO_set_EFUSE_BOOT_SW_DIS(U32 data);
/*! \brief Reads the register 'CRYPTO_EFUSE_BOOT_SW_DIS'. */
U32  GH_CRYPTO_get_EFUSE_BOOT_SW_DIS(void);
/*! \brief Writes the bit group 'Efuse_boot_sw' of register 'CRYPTO_EFUSE_BOOT_SW_DIS'. */
void GH_CRYPTO_set_EFUSE_BOOT_SW_DIS_Efuse_boot_sw(U8 data);
/*! \brief Reads the bit group 'Efuse_boot_sw' of register 'CRYPTO_EFUSE_BOOT_SW_DIS'. */
U8   GH_CRYPTO_get_EFUSE_BOOT_SW_DIS_Efuse_boot_sw(void);
/*! \brief Writes the bit group 'Efuse_boot_dis' of register 'CRYPTO_EFUSE_BOOT_SW_DIS'. */
void GH_CRYPTO_set_EFUSE_BOOT_SW_DIS_Efuse_boot_dis(U8 data);
/*! \brief Reads the bit group 'Efuse_boot_dis' of register 'CRYPTO_EFUSE_BOOT_SW_DIS'. */
U8   GH_CRYPTO_get_EFUSE_BOOT_SW_DIS_Efuse_boot_dis(void);

/*----------------------------------------------------------------------------*/
/* init function                                                              */
/*----------------------------------------------------------------------------*/
/*! \brief Initialises the registers and mirror variables. */
void GH_CRYPTO_init(void);

#ifdef SRC_INLINE
#define SRC_INC 1
#include "gh_crypto.c"
#undef SRC_INC
#endif

#ifdef __cplusplus
}
#endif

#endif /* _GH_CRYPTO_H */

/*----------------------------------------------------------------------------*/
/* end of file                                                                */
/*----------------------------------------------------------------------------*/

