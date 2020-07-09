/******************************************************************************
**
** \file      gh_crypto.c
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
#ifndef SRC_INLINE
#include "gh_crypto.h"
#endif

/*----------------------------------------------------------------------------*/
/* registers                                                                  */
/*----------------------------------------------------------------------------*/
#define REG_CRYPTO_DES_KEY_REAL                             FIO_ADDRESS(CRYPTO,0x60014000) /* read/write */
#define REG_CRYPTO_DES_INPUT_REAL                           FIO_ADDRESS(CRYPTO,0x60014008) /* read/write */
#define REG_CRYPTO_DES_OPCODE_REAL                          FIO_ADDRESS(CRYPTO,0x60014010) /* read/write */
#define REG_CRYPTO_DES_OUTPUT_RDY_REAL                      FIO_ADDRESS(CRYPTO,0x60014014) /* read */
#define REG_CRYPTO_DES_OUTPUT_REAL                          FIO_ADDRESS(CRYPTO,0x60014018) /* read */
#define REG_CRYPTO_DES_INTERRUPT_REAL                       FIO_ADDRESS(CRYPTO,0x60014020) /* read/write */
#define REG_CRYPTO_AES_128_KEY_REAL                         FIO_ADDRESS(CRYPTO,0x60014024) /* read/write */
#define REG_CRYPTO_AES_192_KEY_REAL                         FIO_ADDRESS(CRYPTO,0x60014034) /* read/write */
#define REG_CRYPTO_AES_256_KEY_REAL                         FIO_ADDRESS(CRYPTO,0x6001404C) /* read/write */
#define REG_CRYPTO_AES_INPUT_REAL                           FIO_ADDRESS(CRYPTO,0x6001406C) /* read/write */
#define REG_CRYPTO_AES_OPCODE_REAL                          FIO_ADDRESS(CRYPTO,0x6001407C) /* read/write */
#define REG_CRYPTO_AES_OUTPUT_RDY_REAL                      FIO_ADDRESS(CRYPTO,0x60014080) /* read */
#define REG_CRYPTO_AES_OUTPUT_REAL                          FIO_ADDRESS(CRYPTO,0x60014084) /* read */
#define REG_CRYPTO_AES_INTERRUPT_REAL                       FIO_ADDRESS(CRYPTO,0x60014094) /* read/write */
#define REG_CRYPTO_EFUSE_BOOT_SW_DIS_REAL                   FIO_ADDRESS(CRYPTO,0x60014098) /* read/write */

/*----------------------------------------------------------------------------*/
/* bit group structures                                                       */
/*----------------------------------------------------------------------------*/
typedef union { /* CRYPTO_DES_Opcode */
    U32 all;
    struct {
        U32 mode                        : 1;
        U32                             : 31;
    } bitc;
} GH_CRYPTO_DES_OPCODE_REAL_S;

typedef union { /* CRYPTO_DES_Output_Rdy */
    U32 all;
    struct {
        U32 rdy                         : 1;
        U32                             : 31;
    } bitc;
} GH_CRYPTO_DES_OUTPUT_RDY_REAL_S;

typedef union { /* CRYPTO_DES_Interrupt */
    U32 all;
    struct {
        U32 en                          : 1;
        U32                             : 31;
    } bitc;
} GH_CRYPTO_DES_INTERRUPT_REAL_S;

typedef union { /* CRYPTO_AES_Opcode */
    U32 all;
    struct {
        U32 mode                        : 1;
        U32                             : 31;
    } bitc;
} GH_CRYPTO_AES_OPCODE_REAL_S;

typedef union { /* CRYPTO_AES_Output_Rdy */
    U32 all;
    struct {
        U32 rdy                         : 1;
        U32                             : 31;
    } bitc;
} GH_CRYPTO_AES_OUTPUT_RDY_REAL_S;

typedef union { /* CRYPTO_AES_Interrupt */
    U32 all;
    struct {
        U32 en                          : 1;
        U32                             : 31;
    } bitc;
} GH_CRYPTO_AES_INTERRUPT_REAL_S;

typedef union { /* CRYPTO_EFUSE_BOOT_SW_DIS */
    U32 all;
    struct {
        U32 efuse_boot_sw               : 1;
        U32 efuse_boot_dis              : 1;
        U32                             : 30;
    } bitc;
} GH_CRYPTO_EFUSE_BOOT_SW_DIS_REAL_S;


/*----------------------------------------------------------------------------*/
/* mirror variables                                                           */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
/* register CRYPTO_DES_Key (read/write)                                       */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_CRYPTO_set_DES_Key(U8 index, U32 data)
{
    *(volatile U32 *)(REG_CRYPTO_DES_KEY_REAL + index * FIO_MOFFSET(CRYPTO,0x00000004)) = data;
}
GH_INLINE U32  GH_CRYPTO_get_DES_Key(U8 index)
{
    U32 value = (*(volatile U32 *)(REG_CRYPTO_DES_KEY_REAL + index * FIO_MOFFSET(CRYPTO,0x00000004)));

    return value;
}

/*----------------------------------------------------------------------------*/
/* register CRYPTO_DES_Input (read/write)                                     */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_CRYPTO_set_DES_Input(U8 index, U32 data)
{
    *(volatile U32 *)(REG_CRYPTO_DES_INPUT_REAL + index * FIO_MOFFSET(CRYPTO,0x00000004)) = data;
}
GH_INLINE U32  GH_CRYPTO_get_DES_Input(U8 index)
{
    U32 value = (*(volatile U32 *)(REG_CRYPTO_DES_INPUT_REAL + index * FIO_MOFFSET(CRYPTO,0x00000004)));

    return value;
}

/*----------------------------------------------------------------------------*/
/* register CRYPTO_DES_Opcode (read/write)                                    */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_CRYPTO_set_DES_Opcode(U32 data)
{
    GH_CRYPTO_DES_OPCODE_REAL_S real;
    GH_CRYPTO_DES_OPCODE_S dummy;
    dummy.all = data ;
    real.bitc.mode = dummy.bitc.mode;
    *(volatile U32 *)REG_CRYPTO_DES_OPCODE_REAL = real.all;
}
GH_INLINE U32  GH_CRYPTO_get_DES_Opcode(void)
{
    GH_CRYPTO_DES_OPCODE_REAL_S real;
    GH_CRYPTO_DES_OPCODE_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U32 *)REG_CRYPTO_DES_OPCODE_REAL);

    dummy.bitc.mode = real.bitc.mode;
    return dummy.all;
}
GH_INLINE void GH_CRYPTO_set_DES_Opcode_mode(U8 data)
{
    GH_CRYPTO_DES_OPCODE_REAL_S d;
    d.all = *(volatile U32 *)REG_CRYPTO_DES_OPCODE_REAL;
    d.bitc.mode = data;
    *(volatile U32 *)REG_CRYPTO_DES_OPCODE_REAL = d.all;
}
GH_INLINE U8   GH_CRYPTO_get_DES_Opcode_mode(void)
{
    GH_CRYPTO_DES_OPCODE_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_CRYPTO_DES_OPCODE_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.mode;
}

/*----------------------------------------------------------------------------*/
/* register CRYPTO_DES_Output_Rdy (read)                                      */
/*----------------------------------------------------------------------------*/
GH_INLINE U32  GH_CRYPTO_get_DES_Output_Rdy(void)
{
    GH_CRYPTO_DES_OUTPUT_RDY_REAL_S real;
    GH_CRYPTO_DES_OUTPUT_RDY_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U32 *)REG_CRYPTO_DES_OUTPUT_RDY_REAL);

    dummy.bitc.rdy = real.bitc.rdy;
    return dummy.all;
}
GH_INLINE U8   GH_CRYPTO_get_DES_Output_Rdy_Rdy(void)
{
    GH_CRYPTO_DES_OUTPUT_RDY_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_CRYPTO_DES_OUTPUT_RDY_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.rdy;
}

/*----------------------------------------------------------------------------*/
/* register CRYPTO_DES_Output (read)                                          */
/*----------------------------------------------------------------------------*/
GH_INLINE U32  GH_CRYPTO_get_DES_Output(U8 index)
{
    U32 value = (*(volatile U32 *)(REG_CRYPTO_DES_OUTPUT_REAL + index * FIO_MOFFSET(CRYPTO,0x00000004)));

    return value;
}

/*----------------------------------------------------------------------------*/
/* register CRYPTO_DES_Interrupt (read/write)                                 */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_CRYPTO_set_DES_Interrupt(U32 data)
{
    GH_CRYPTO_DES_INTERRUPT_REAL_S real;
    GH_CRYPTO_DES_INTERRUPT_S dummy;
    dummy.all = data ;
    real.bitc.en = dummy.bitc.en;
    *(volatile U32 *)REG_CRYPTO_DES_INTERRUPT_REAL = real.all;
}
GH_INLINE U32  GH_CRYPTO_get_DES_Interrupt(void)
{
    GH_CRYPTO_DES_INTERRUPT_REAL_S real;
    GH_CRYPTO_DES_INTERRUPT_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U32 *)REG_CRYPTO_DES_INTERRUPT_REAL);

    dummy.bitc.en = real.bitc.en;
    return dummy.all;
}
GH_INLINE void GH_CRYPTO_set_DES_Interrupt_En(U8 data)
{
    GH_CRYPTO_DES_INTERRUPT_REAL_S d;
    d.all = *(volatile U32 *)REG_CRYPTO_DES_INTERRUPT_REAL;
    d.bitc.en = data;
    *(volatile U32 *)REG_CRYPTO_DES_INTERRUPT_REAL = d.all;
}
GH_INLINE U8   GH_CRYPTO_get_DES_Interrupt_En(void)
{
    GH_CRYPTO_DES_INTERRUPT_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_CRYPTO_DES_INTERRUPT_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.en;
}

/*----------------------------------------------------------------------------*/
/* register CRYPTO_AES_128_Key (read/write)                                   */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_CRYPTO_set_AES_128_Key(U8 index, U32 data)
{
    *(volatile U32 *)(REG_CRYPTO_AES_128_KEY_REAL + index * FIO_MOFFSET(CRYPTO,0x00000004)) = data;
}
GH_INLINE U32  GH_CRYPTO_get_AES_128_Key(U8 index)
{
    U32 value = (*(volatile U32 *)(REG_CRYPTO_AES_128_KEY_REAL + index * FIO_MOFFSET(CRYPTO,0x00000004)));

    return value;
}

/*----------------------------------------------------------------------------*/
/* register CRYPTO_AES_192_Key (read/write)                                   */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_CRYPTO_set_AES_192_Key(U8 index, U32 data)
{
    *(volatile U32 *)(REG_CRYPTO_AES_192_KEY_REAL + index * FIO_MOFFSET(CRYPTO,0x00000004)) = data;
}
GH_INLINE U32  GH_CRYPTO_get_AES_192_Key(U8 index)
{
    U32 value = (*(volatile U32 *)(REG_CRYPTO_AES_192_KEY_REAL + index * FIO_MOFFSET(CRYPTO,0x00000004)));

    return value;
}

/*----------------------------------------------------------------------------*/
/* register CRYPTO_AES_256_Key (read/write)                                   */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_CRYPTO_set_AES_256_Key(U8 index, U32 data)
{
    *(volatile U32 *)(REG_CRYPTO_AES_256_KEY_REAL + index * FIO_MOFFSET(CRYPTO,0x00000004)) = data;
}
GH_INLINE U32  GH_CRYPTO_get_AES_256_Key(U8 index)
{
    U32 value = (*(volatile U32 *)(REG_CRYPTO_AES_256_KEY_REAL + index * FIO_MOFFSET(CRYPTO,0x00000004)));

    return value;
}

/*----------------------------------------------------------------------------*/
/* register CRYPTO_AES_Input (read/write)                                     */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_CRYPTO_set_AES_Input(U8 index, U32 data)
{
    *(volatile U32 *)(REG_CRYPTO_AES_INPUT_REAL + index * FIO_MOFFSET(CRYPTO,0x00000004)) = data;
}
GH_INLINE U32  GH_CRYPTO_get_AES_Input(U8 index)
{
    U32 value = (*(volatile U32 *)(REG_CRYPTO_AES_INPUT_REAL + index * FIO_MOFFSET(CRYPTO,0x00000004)));

    return value;
}

/*----------------------------------------------------------------------------*/
/* register CRYPTO_AES_Opcode (read/write)                                    */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_CRYPTO_set_AES_Opcode(U32 data)
{
    GH_CRYPTO_AES_OPCODE_REAL_S real;
    GH_CRYPTO_AES_OPCODE_S dummy;
    dummy.all = data ;
    real.bitc.mode = dummy.bitc.mode;
    *(volatile U32 *)REG_CRYPTO_AES_OPCODE_REAL = real.all;
}
GH_INLINE U32  GH_CRYPTO_get_AES_Opcode(void)
{
    GH_CRYPTO_AES_OPCODE_REAL_S real;
    GH_CRYPTO_AES_OPCODE_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U32 *)REG_CRYPTO_AES_OPCODE_REAL);

    dummy.bitc.mode = real.bitc.mode;
    return dummy.all;
}
GH_INLINE void GH_CRYPTO_set_AES_Opcode_mode(U8 data)
{
    GH_CRYPTO_AES_OPCODE_REAL_S d;
    d.all = *(volatile U32 *)REG_CRYPTO_AES_OPCODE_REAL;
    d.bitc.mode = data;
    *(volatile U32 *)REG_CRYPTO_AES_OPCODE_REAL = d.all;
}
GH_INLINE U8   GH_CRYPTO_get_AES_Opcode_mode(void)
{
    GH_CRYPTO_AES_OPCODE_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_CRYPTO_AES_OPCODE_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.mode;
}

/*----------------------------------------------------------------------------*/
/* register CRYPTO_AES_Output_Rdy (read)                                      */
/*----------------------------------------------------------------------------*/
GH_INLINE U32  GH_CRYPTO_get_AES_Output_Rdy(void)
{
    GH_CRYPTO_AES_OUTPUT_RDY_REAL_S real;
    GH_CRYPTO_AES_OUTPUT_RDY_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U32 *)REG_CRYPTO_AES_OUTPUT_RDY_REAL);

    dummy.bitc.rdy = real.bitc.rdy;
    return dummy.all;
}
GH_INLINE U8   GH_CRYPTO_get_AES_Output_Rdy_Rdy(void)
{
    GH_CRYPTO_AES_OUTPUT_RDY_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_CRYPTO_AES_OUTPUT_RDY_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.rdy;
}

/*----------------------------------------------------------------------------*/
/* register CRYPTO_AES_Output (read)                                          */
/*----------------------------------------------------------------------------*/
GH_INLINE U32  GH_CRYPTO_get_AES_Output(U8 index)
{
    U32 value = (*(volatile U32 *)(REG_CRYPTO_AES_OUTPUT_REAL + index * FIO_MOFFSET(CRYPTO,0x00000004)));

    return value;
}

/*----------------------------------------------------------------------------*/
/* register CRYPTO_AES_Interrupt (read/write)                                 */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_CRYPTO_set_AES_Interrupt(U32 data)
{
    GH_CRYPTO_AES_INTERRUPT_REAL_S real;
    GH_CRYPTO_AES_INTERRUPT_S dummy;
    dummy.all = data ;
    real.bitc.en = dummy.bitc.en;
    *(volatile U32 *)REG_CRYPTO_AES_INTERRUPT_REAL = real.all;
}
GH_INLINE U32  GH_CRYPTO_get_AES_Interrupt(void)
{
    GH_CRYPTO_AES_INTERRUPT_REAL_S real;
    GH_CRYPTO_AES_INTERRUPT_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U32 *)REG_CRYPTO_AES_INTERRUPT_REAL);

    dummy.bitc.en = real.bitc.en;
    return dummy.all;
}
GH_INLINE void GH_CRYPTO_set_AES_Interrupt_En(U8 data)
{
    GH_CRYPTO_AES_INTERRUPT_REAL_S d;
    d.all = *(volatile U32 *)REG_CRYPTO_AES_INTERRUPT_REAL;
    d.bitc.en = data;
    *(volatile U32 *)REG_CRYPTO_AES_INTERRUPT_REAL = d.all;
}
GH_INLINE U8   GH_CRYPTO_get_AES_Interrupt_En(void)
{
    GH_CRYPTO_AES_INTERRUPT_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_CRYPTO_AES_INTERRUPT_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.en;
}

/*----------------------------------------------------------------------------*/
/* register CRYPTO_EFUSE_BOOT_SW_DIS (read/write)                             */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_CRYPTO_set_EFUSE_BOOT_SW_DIS(U32 data)
{
    GH_CRYPTO_EFUSE_BOOT_SW_DIS_REAL_S real;
    GH_CRYPTO_EFUSE_BOOT_SW_DIS_S dummy;
    dummy.all = data ;
    real.bitc.efuse_boot_sw = dummy.bitc.efuse_boot_sw;
    real.bitc.efuse_boot_dis = dummy.bitc.efuse_boot_dis;
    *(volatile U32 *)REG_CRYPTO_EFUSE_BOOT_SW_DIS_REAL = real.all;
}
GH_INLINE U32  GH_CRYPTO_get_EFUSE_BOOT_SW_DIS(void)
{
    GH_CRYPTO_EFUSE_BOOT_SW_DIS_REAL_S real;
    GH_CRYPTO_EFUSE_BOOT_SW_DIS_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U32 *)REG_CRYPTO_EFUSE_BOOT_SW_DIS_REAL);

    dummy.bitc.efuse_boot_sw = real.bitc.efuse_boot_sw;
    dummy.bitc.efuse_boot_dis = real.bitc.efuse_boot_dis;
    return dummy.all;
}
GH_INLINE void GH_CRYPTO_set_EFUSE_BOOT_SW_DIS_Efuse_boot_sw(U8 data)
{
    GH_CRYPTO_EFUSE_BOOT_SW_DIS_REAL_S d;
    d.all = *(volatile U32 *)REG_CRYPTO_EFUSE_BOOT_SW_DIS_REAL;
    d.bitc.efuse_boot_sw = data;
    *(volatile U32 *)REG_CRYPTO_EFUSE_BOOT_SW_DIS_REAL = d.all;
}
GH_INLINE U8   GH_CRYPTO_get_EFUSE_BOOT_SW_DIS_Efuse_boot_sw(void)
{
    GH_CRYPTO_EFUSE_BOOT_SW_DIS_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_CRYPTO_EFUSE_BOOT_SW_DIS_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.efuse_boot_sw;
}
GH_INLINE void GH_CRYPTO_set_EFUSE_BOOT_SW_DIS_Efuse_boot_dis(U8 data)
{
    GH_CRYPTO_EFUSE_BOOT_SW_DIS_REAL_S d;
    d.all = *(volatile U32 *)REG_CRYPTO_EFUSE_BOOT_SW_DIS_REAL;
    d.bitc.efuse_boot_dis = data;
    *(volatile U32 *)REG_CRYPTO_EFUSE_BOOT_SW_DIS_REAL = d.all;
}
GH_INLINE U8   GH_CRYPTO_get_EFUSE_BOOT_SW_DIS_Efuse_boot_dis(void)
{
    GH_CRYPTO_EFUSE_BOOT_SW_DIS_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_CRYPTO_EFUSE_BOOT_SW_DIS_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.efuse_boot_dis;
}

/*----------------------------------------------------------------------------*/
/* init function                                                              */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_CRYPTO_init(void)
{
    int i;

    for (i=0; i<2; i++)
    {
        GH_CRYPTO_set_DES_Key(i, (U32)0x00000000);
    }
    for (i=0; i<2; i++)
    {
        GH_CRYPTO_set_DES_Input(i, (U32)0x00000000);
    }
    GH_CRYPTO_set_DES_Opcode((U32)0x00000000);
    GH_CRYPTO_set_DES_Interrupt((U32)0x00000000);
    for (i=0; i<4; i++)
    {
        GH_CRYPTO_set_AES_128_Key(i, (U32)0x00000000);
    }
    for (i=0; i<6; i++)
    {
        GH_CRYPTO_set_AES_192_Key(i, (U32)0x00000000);
    }
    for (i=0; i<8; i++)
    {
        GH_CRYPTO_set_AES_256_Key(i, (U32)0x00000000);
    }
    for (i=0; i<4; i++)
    {
        GH_CRYPTO_set_AES_Input(i, (U32)0x00000000);
    }
    GH_CRYPTO_set_AES_Opcode((U32)0x00000000);
    GH_CRYPTO_set_AES_Interrupt((U32)0x00000000);
    GH_CRYPTO_set_EFUSE_BOOT_SW_DIS((U32)0x00000000);
    /* read read-clear registers in order to set mirror variables */
}

/*----------------------------------------------------------------------------*/
/* end of file                                                                */
/*----------------------------------------------------------------------------*/

