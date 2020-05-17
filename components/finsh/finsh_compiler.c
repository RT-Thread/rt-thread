/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2010-03-22     Bernard      first version
 */
#include <finsh.h>

#include "finsh_node.h"
#include "finsh_error.h"
#include "finsh_var.h"
#include "finsh_ops.h"

union finsh_value*  finsh_compile_sp;       /* stack pointer */
uint8_t*            finsh_compile_pc;       /* PC */

#define finsh_code_byte(x)  do { *finsh_compile_pc = (x); finsh_compile_pc ++; } while(0)
#define finsh_code_word(x)  do { FINSH_SET16(finsh_compile_pc, x); finsh_compile_pc +=2; } while(0)
#define finsh_code_dword(x) do { FINSH_SET32(finsh_compile_pc, x); finsh_compile_pc +=4; } while(0)

static int finsh_compile(struct finsh_node* node)
{
    if (node != NULL)
    {
        /* compile child node */
        if (finsh_node_child(node) != NULL)
            finsh_compile(finsh_node_child(node));

        /* compile current node */
        switch (node->node_type)
        {
        case FINSH_NODE_ID:
            {
                /* identifier::syscall */
                if (node->idtype & FINSH_IDTYPE_SYSCALL)
                {
                    /* load address */
                    finsh_code_byte(FINSH_OP_LD_DWORD);
                    finsh_code_dword((long)node->id.syscall->func);
                }
                /* identifier::sysvar */
                else if (node->idtype & FINSH_IDTYPE_SYSVAR)
                {
                    struct finsh_sysvar* sysvar;

                    sysvar = node->id.sysvar;
                    if (sysvar != NULL)
                    {
                        switch (sysvar->type)
                        {
                        case finsh_type_char:
                        case finsh_type_uchar:
                            if (node->idtype & FINSH_IDTYPE_ADDRESS)
                            {
                                /* load address */
                                finsh_code_byte(FINSH_OP_LD_DWORD);
                            }
                            else
                            {
                                /* load value */
                                finsh_code_byte(FINSH_OP_LD_VALUE_BYTE);
                            }

                            finsh_code_dword((long)(sysvar->var));
                            break;

                        case finsh_type_short:
                        case finsh_type_ushort:
                            if (node->idtype & FINSH_IDTYPE_ADDRESS)
                            {
                                /* load address */
                                finsh_code_byte(FINSH_OP_LD_DWORD);
                            }
                            else
                            {
                                /* load value */
                                finsh_code_byte(FINSH_OP_LD_VALUE_WORD);
                            }

                            finsh_code_dword((long)(sysvar->var));
                            break;

                        case finsh_type_int:
                        case finsh_type_uint:
                        case finsh_type_long:
                        case finsh_type_ulong:
                        case finsh_type_charp:
                        case finsh_type_shortp:
                        case finsh_type_intp:
                        case finsh_type_longp:
                            if (node->idtype & FINSH_IDTYPE_ADDRESS)
                            {
                                /* load address */
                                finsh_code_byte(FINSH_OP_LD_DWORD);
                            }
                            else
                            {
                                /* load value */
                                finsh_code_byte(FINSH_OP_LD_VALUE_DWORD);
                            }

                            finsh_code_dword((long)(sysvar->var));
                            break;
                        }
                    }
                }
                /* identifier::var */
                else
                {
                    struct finsh_var* var;

                    var = node->id.var;
                    if (var != NULL)
                    {
                        switch (var->type)
                        {
                        case finsh_type_char:
                        case finsh_type_uchar:
                            if (node->idtype & FINSH_IDTYPE_ADDRESS)
                            {
                                /* load address */
                                finsh_code_byte(FINSH_OP_LD_DWORD);
                            }
                            else
                            {
                                /* load value */
                                finsh_code_byte(FINSH_OP_LD_VALUE_BYTE);
                            }

                            finsh_code_dword((long)&(var->value.char_value));
                            break;

                        case finsh_type_short:
                        case finsh_type_ushort:
                            if (node->idtype & FINSH_IDTYPE_ADDRESS)
                            {
                                /* load address */
                                finsh_code_byte(FINSH_OP_LD_DWORD);
                            }
                            else
                            {
                                /* load value */
                                finsh_code_byte(FINSH_OP_LD_VALUE_WORD);
                            }

                            finsh_code_dword((long)&(var->value.short_value));
                            break;

                        case finsh_type_int:
                        case finsh_type_uint:
                        case finsh_type_long:
                        case finsh_type_ulong:
                        case finsh_type_charp:
                        case finsh_type_shortp:
                        case finsh_type_intp:
                        case finsh_type_longp:
                            if (node->idtype & FINSH_IDTYPE_ADDRESS)
                            {
                                /* load address */
                                finsh_code_byte(FINSH_OP_LD_DWORD);
                            }
                            else
                            {
                                /* load value */
                                finsh_code_byte(FINSH_OP_LD_VALUE_DWORD);
                            }

                            finsh_code_dword((long)&(var->value.long_value));
                            break;
                        }
                    }
                }
            }
            break;

        /* load const */
        case FINSH_NODE_VALUE_CHAR:
            finsh_code_byte(FINSH_OP_LD_BYTE);
            finsh_code_byte(node->value.char_value);
            break;

        case FINSH_NODE_VALUE_INT:
        case FINSH_NODE_VALUE_LONG:
            finsh_code_byte(FINSH_OP_LD_DWORD);
            finsh_code_dword(node->value.long_value);
            break;

        case FINSH_NODE_VALUE_NULL:
        case FINSH_NODE_VALUE_STRING:
            finsh_code_byte(FINSH_OP_LD_DWORD);
            finsh_code_dword((rt_ubase_t)node->value.ptr);
            break;

        /* arithmetic operation */
        case FINSH_NODE_SYS_ADD:
            if (node->data_type == FINSH_DATA_TYPE_BYTE) finsh_code_byte(FINSH_OP_ADD_BYTE);
            else if (node->data_type == FINSH_DATA_TYPE_WORD) finsh_code_byte(FINSH_OP_ADD_WORD);
            else if (node->data_type == FINSH_DATA_TYPE_DWORD) finsh_code_byte(FINSH_OP_ADD_DWORD);
            break;

        case FINSH_NODE_SYS_SUB:
            if (node->data_type == FINSH_DATA_TYPE_BYTE) finsh_code_byte(FINSH_OP_SUB_BYTE);
            else if (node->data_type == FINSH_DATA_TYPE_WORD) finsh_code_byte(FINSH_OP_SUB_WORD);
            else if (node->data_type == FINSH_DATA_TYPE_DWORD) finsh_code_byte(FINSH_OP_SUB_DWORD);
            break;

        case FINSH_NODE_SYS_MUL:
            if (node->data_type == FINSH_DATA_TYPE_BYTE) finsh_code_byte(FINSH_OP_MUL_BYTE);
            else if (node->data_type == FINSH_DATA_TYPE_WORD) finsh_code_byte(FINSH_OP_MUL_WORD);
            else if (node->data_type == FINSH_DATA_TYPE_DWORD) finsh_code_byte(FINSH_OP_MUL_DWORD);
            break;

        case FINSH_NODE_SYS_DIV:
            if (node->data_type == FINSH_DATA_TYPE_BYTE) finsh_code_byte(FINSH_OP_DIV_BYTE);
            else if (node->data_type == FINSH_DATA_TYPE_WORD) finsh_code_byte(FINSH_OP_DIV_WORD);
            else if (node->data_type == FINSH_DATA_TYPE_DWORD) finsh_code_byte(FINSH_OP_DIV_DWORD);
            break;

        case FINSH_NODE_SYS_MOD:
            if (node->data_type == FINSH_DATA_TYPE_BYTE) finsh_code_byte(FINSH_OP_MOD_BYTE);
            else if (node->data_type == FINSH_DATA_TYPE_WORD) finsh_code_byte(FINSH_OP_MOD_WORD);
            else if (node->data_type == FINSH_DATA_TYPE_DWORD) finsh_code_byte(FINSH_OP_MOD_DWORD);
            break;

        /* bit operation */
        case FINSH_NODE_SYS_AND:
            if (node->data_type == FINSH_DATA_TYPE_BYTE) finsh_code_byte(FINSH_OP_AND_BYTE);
            else if (node->data_type == FINSH_DATA_TYPE_WORD) finsh_code_byte(FINSH_OP_AND_WORD);
            else if (node->data_type == FINSH_DATA_TYPE_DWORD) finsh_code_byte(FINSH_OP_AND_DWORD);
            break;

        case FINSH_NODE_SYS_OR:
            if (node->data_type == FINSH_DATA_TYPE_BYTE) finsh_code_byte(FINSH_OP_OR_BYTE);
            else if (node->data_type == FINSH_DATA_TYPE_WORD) finsh_code_byte(FINSH_OP_OR_WORD);
            else if (node->data_type == FINSH_DATA_TYPE_DWORD) finsh_code_byte(FINSH_OP_OR_DWORD);
            break;

        case FINSH_NODE_SYS_XOR:
            if (node->data_type == FINSH_DATA_TYPE_BYTE) finsh_code_byte(FINSH_OP_XOR_BYTE);
            else if (node->data_type == FINSH_DATA_TYPE_WORD) finsh_code_byte(FINSH_OP_XOR_WORD);
            else if (node->data_type == FINSH_DATA_TYPE_DWORD) finsh_code_byte(FINSH_OP_XOR_DWORD);
            break;

        case FINSH_NODE_SYS_BITWISE:
            if (node->data_type == FINSH_DATA_TYPE_BYTE) finsh_code_byte(FINSH_OP_BITWISE_BYTE);
            else if (node->data_type == FINSH_DATA_TYPE_WORD) finsh_code_byte(FINSH_OP_BITWISE_WORD);
            else if (node->data_type == FINSH_DATA_TYPE_DWORD) finsh_code_byte(FINSH_OP_BITWISE_DWORD);
            break;

        case FINSH_NODE_SYS_SHL:
            if (node->data_type == FINSH_DATA_TYPE_BYTE) finsh_code_byte(FINSH_OP_SHL_BYTE);
            else if (node->data_type == FINSH_DATA_TYPE_WORD) finsh_code_byte(FINSH_OP_SHL_WORD);
            else if (node->data_type == FINSH_DATA_TYPE_DWORD) finsh_code_byte(FINSH_OP_SHL_DWORD);
            break;

        case FINSH_NODE_SYS_SHR:
            if (node->data_type == FINSH_DATA_TYPE_BYTE) finsh_code_byte(FINSH_OP_SHR_BYTE);
            else if (node->data_type == FINSH_DATA_TYPE_WORD) finsh_code_byte(FINSH_OP_SHR_WORD);
            else if (node->data_type == FINSH_DATA_TYPE_DWORD) finsh_code_byte(FINSH_OP_SHR_DWORD);
            break;

        /* syscall */
        case FINSH_NODE_SYS_FUNC:
            {
                int parameters;
                struct finsh_node* sibling;

                parameters = 0;
                if (finsh_node_child(node) != NULL)
                {
                    sibling = finsh_node_sibling(finsh_node_child(node));
                    while (sibling != NULL)
                    {
                        parameters ++;
                        sibling = finsh_node_sibling(sibling);
                    }

                    /* load address of function */
                    // finsh_code_dword((long)&(node->var->value.ptr));

                    /* syscall parameters */
                    finsh_code_byte(FINSH_OP_SYSCALL);
                    finsh_code_byte(parameters);
                }
            }
            break;

        /* assign expression */
        case FINSH_NODE_SYS_ASSIGN:
            if (finsh_node_child(node) && finsh_node_child(node)->node_type == FINSH_NODE_ID)
            {
                switch (finsh_node_child(node)->data_type)
                {
                case FINSH_DATA_TYPE_BYTE:
                    finsh_code_byte(FINSH_OP_ST_BYTE);

                    /* load value again */
                    finsh_code_byte(FINSH_OP_LD_VALUE_BYTE_STACK);
                    break;

                case FINSH_DATA_TYPE_WORD:
                    finsh_code_byte(FINSH_OP_ST_WORD);

                    /* load value again */
                    finsh_code_byte(FINSH_OP_LD_VALUE_WORD_STACK);
                    break;

                case FINSH_DATA_TYPE_DWORD:
                    finsh_code_byte(FINSH_OP_ST_DWORD);

                    /* load value again */
                    finsh_code_byte(FINSH_OP_LD_VALUE_DWORD_STACK);
                    break;

                default:
                    finsh_error_set(FINSH_ERROR_UNKNOWN_TYPE);
                }
            }
            else if (finsh_node_child(node)->node_type == FINSH_NODE_SYS_GETVALUE)
            {
                switch ((finsh_node_child(node)->data_type) & 0x0F)
                {
                case FINSH_DATA_TYPE_BYTE:
                    finsh_code_byte(FINSH_OP_ST_BYTE);

                    /* load value again */
                    finsh_code_byte(FINSH_OP_LD_VALUE_BYTE_STACK);
                    break;

                case FINSH_DATA_TYPE_WORD:
                    finsh_code_byte(FINSH_OP_ST_WORD);

                    /* load value again */
                    finsh_code_byte(FINSH_OP_LD_VALUE_WORD_STACK);
                    break;

                case FINSH_DATA_TYPE_DWORD:
                    finsh_code_byte(FINSH_OP_ST_DWORD);

                    /* load value again */
                    finsh_code_byte(FINSH_OP_LD_VALUE_DWORD_STACK);
                    break;

                default:
                    finsh_error_set(FINSH_ERROR_UNKNOWN_TYPE);
                }
            }
            break;

        /* pre-increase */
        case FINSH_NODE_SYS_PREINC:
            if (finsh_node_child(node) && finsh_node_child(node)->node_type == FINSH_NODE_ID)
            {
                struct finsh_var* var;
                var = finsh_node_child(node)->id.var;

                /* ld_dword &id */
                // finsh_code_byte(FINSH_OP_LD_DWORD);

                switch (node->data_type)
                {
                case FINSH_DATA_TYPE_BYTE:
                    /* address */
                    // finsh_code_dword((long)&(var->value.char_value));

                    /* ld_value_byte &id */
                    finsh_code_byte(FINSH_OP_LD_VALUE_BYTE);
                    finsh_code_dword((long)&(var->value.char_value));

                    /* ld_byte 1 */
                    finsh_code_byte(FINSH_OP_LD_BYTE);
                    finsh_code_byte(1);

                    /* add_byte */
                    finsh_code_byte(FINSH_OP_ADD_BYTE);
                    /* st_byte */
                    finsh_code_byte(FINSH_OP_ST_BYTE);

                    /* load value again */
                    finsh_code_byte(FINSH_OP_LD_VALUE_DWORD_STACK);

                    break;

                case FINSH_DATA_TYPE_WORD:
                    /* address */
                    // finsh_code_dword((long)&(var->value.short_value));

                    /* ld_value_word &id */
                    finsh_code_byte(FINSH_OP_LD_VALUE_WORD);
                    finsh_code_dword((long)&(var->value.short_value));

                    /* ld_word 1 */
                    finsh_code_byte(FINSH_OP_LD_WORD);
                    finsh_code_word(1);

                    /* add_word */
                    finsh_code_byte(FINSH_OP_ADD_WORD);
                    /* st_word */
                    finsh_code_byte(FINSH_OP_ST_WORD);

                    /* load value again */
                    finsh_code_byte(FINSH_OP_LD_VALUE_DWORD_STACK);

                    break;

                case FINSH_DATA_TYPE_DWORD:
                    /* address */
                    // finsh_code_dword((long)&(var->value.long_value));

                    /* ld_dword &id */
                    finsh_code_byte(FINSH_OP_LD_VALUE_DWORD);
                    finsh_code_dword((long)&(var->value.long_value));

                    /* ld_dword 1 */
                    finsh_code_byte(FINSH_OP_LD_DWORD);
                    finsh_code_dword(1);

                    /* add_dword */
                    finsh_code_byte(FINSH_OP_ADD_DWORD);
                    /* st_dword */
                    finsh_code_byte(FINSH_OP_ST_DWORD);

                    /* load value again */
                    finsh_code_byte(FINSH_OP_LD_VALUE_DWORD_STACK);

                    break;
                }
            }
            break;

        /* pre-decrease */
        case FINSH_NODE_SYS_PREDEC:
            if (finsh_node_child(node) && finsh_node_child(node)->node_type == FINSH_NODE_ID)
            {
                struct finsh_var* var;
                var = finsh_node_child(node)->id.var;

                /* ld_dword &id */
                // finsh_code_byte(FINSH_OP_LD_DWORD);

                switch (node->data_type)
                {
                case FINSH_DATA_TYPE_BYTE:
                    /* address */
                    // finsh_code_dword((long)&(var->value.char_value));

                    /* ld_value_byte &id */
                    finsh_code_byte(FINSH_OP_LD_VALUE_BYTE);
                    finsh_code_dword((long)&(var->value.char_value));

                    /* ld_byte 1 */
                    finsh_code_byte(FINSH_OP_LD_BYTE);
                    finsh_code_byte(1);

                    /* add_byte */
                    finsh_code_byte(FINSH_OP_SUB_BYTE);
                    /* st_byte */
                    finsh_code_byte(FINSH_OP_ST_BYTE);

                    /* load value again */
                    finsh_code_byte(FINSH_OP_LD_VALUE_DWORD_STACK);

                    break;

                case FINSH_DATA_TYPE_WORD:
                    /* address */
                    // finsh_code_dword((long)&(var->value.short_value));

                    /* ld_value_word &id */
                    finsh_code_byte(FINSH_OP_LD_VALUE_WORD);
                    finsh_code_dword((long)&(var->value.short_value));

                    /* ld_word 1 */
                    finsh_code_byte(FINSH_OP_LD_WORD);
                    finsh_code_word(1);

                    /* add_word */
                    finsh_code_byte(FINSH_OP_SUB_WORD);
                    /* st_word */
                    finsh_code_byte(FINSH_OP_ST_WORD);

                    /* load value again */
                    finsh_code_byte(FINSH_OP_LD_VALUE_DWORD_STACK);

                    break;

                case FINSH_DATA_TYPE_DWORD:
                    /* address */
                    // finsh_code_dword((long)&(var->value.long_value));

                    /* ld_dword &id */
                    finsh_code_byte(FINSH_OP_LD_VALUE_DWORD);
                    finsh_code_dword((long)&(var->value.long_value));

                    /* ld_dword 1 */
                    finsh_code_byte(FINSH_OP_LD_DWORD);
                    finsh_code_dword(1);

                    /* add_dword */
                    finsh_code_byte(FINSH_OP_SUB_DWORD);
                    /* st_dword */
                    finsh_code_byte(FINSH_OP_ST_DWORD);

                    /* load value again */
                    finsh_code_byte(FINSH_OP_LD_VALUE_DWORD_STACK);

                    break;
                }
            }
            break;

        /* increase */
        case FINSH_NODE_SYS_INC:
            if (finsh_node_child(node) && finsh_node_child(node)->node_type == FINSH_NODE_ID)
            {
                struct finsh_var* var;
                var = finsh_node_child(node)->id.var;

                switch (node->data_type)
                {
                case FINSH_DATA_TYPE_BYTE:
                    /* ld_value_byte &id */
                    // finsh_code_byte(FINSH_OP_LD_VALUE_BYTE);
                    // finsh_code_dword((long)&(var->value.char_value));

                    /* ld_dword &id */
                    finsh_code_byte(FINSH_OP_LD_DWORD);
                    finsh_code_dword((long)&(var->value.char_value));

                    /* ld_value_byte &id */
                    finsh_code_byte(FINSH_OP_LD_VALUE_BYTE);
                    finsh_code_dword((long)&(var->value.char_value));

                    /* ld_byte 1 */
                    finsh_code_byte(FINSH_OP_LD_BYTE);
                    finsh_code_byte(1);

                    /* add_byte */
                    finsh_code_byte(FINSH_OP_ADD_BYTE);
                    /* get byte */
                    finsh_code_byte(FINSH_OP_ST_BYTE);

                    /* pop */
                    finsh_code_byte(FINSH_OP_POP);
                    break;

                case FINSH_DATA_TYPE_WORD:
                    /* ld_value_word &id */
                    // finsh_code_byte(FINSH_OP_LD_VALUE_WORD);
                    // finsh_code_dword((long)&(var->value.short_value));

                    /* ld_dword &id */
                    finsh_code_byte(FINSH_OP_LD_DWORD);
                    finsh_code_dword((long)&(var->value.short_value));

                    /* ld_value_word &id */
                    finsh_code_byte(FINSH_OP_LD_VALUE_WORD);
                    finsh_code_dword((long)&(var->value.short_value));

                    /* ld_word 1 */
                    finsh_code_byte(FINSH_OP_LD_WORD);
                    finsh_code_word(1);

                    /* add_byte */
                    finsh_code_byte(FINSH_OP_ADD_WORD);
                    /* get byte */
                    finsh_code_byte(FINSH_OP_ST_WORD);

                    /* pop */
                    finsh_code_byte(FINSH_OP_POP);
                    break;

                case FINSH_DATA_TYPE_DWORD:
                    /* ld_value_dword &id */
                    // finsh_code_byte(FINSH_OP_LD_VALUE_DWORD);
                    // finsh_code_dword((long)&(var->value.long_value));

                    /* ld_dword &id */
                    finsh_code_byte(FINSH_OP_LD_DWORD);
                    finsh_code_dword((long)&(var->value.long_value));

                    /* ld_value_dword &id */
                    finsh_code_byte(FINSH_OP_LD_VALUE_DWORD);
                    finsh_code_dword((long)&(var->value.long_value));

                    /* ld_dword 1 */
                    finsh_code_byte(FINSH_OP_LD_DWORD);
                    finsh_code_dword(1);

                    /* add_byte */
                    finsh_code_byte(FINSH_OP_ADD_DWORD);
                    /* get byte */
                    finsh_code_byte(FINSH_OP_ST_DWORD);

                    /* pop */
                    finsh_code_byte(FINSH_OP_POP);
                    break;
                }
            }
            break;

        /* decrease */
        case FINSH_NODE_SYS_DEC:
            if (finsh_node_child(node) && finsh_node_child(node)->node_type == FINSH_NODE_ID)
            {
                struct finsh_var* var;
                var = finsh_node_child(node)->id.var;

                switch (node->data_type)
                {
                case FINSH_DATA_TYPE_BYTE:
                    /* ld_value_byte &id */
                    // finsh_code_byte(FINSH_OP_LD_VALUE_BYTE);
                    // finsh_code_dword((long)&(var->value.char_value));

                    /* ld_dword &id */
                    finsh_code_byte(FINSH_OP_LD_DWORD);
                    finsh_code_dword((long)&(var->value.char_value));

                    /* ld_value_byte &id */
                    finsh_code_byte(FINSH_OP_LD_VALUE_BYTE);
                    finsh_code_dword((long)&(var->value.char_value));

                    /* ld_byte 1 */
                    finsh_code_byte(FINSH_OP_LD_BYTE);
                    finsh_code_byte(1);

                    /* add_byte */
                    finsh_code_byte(FINSH_OP_SUB_BYTE);
                    /* get byte */
                    finsh_code_byte(FINSH_OP_ST_BYTE);

                    /* pop */
                    finsh_code_byte(FINSH_OP_POP);
                    break;

                case FINSH_DATA_TYPE_WORD:
                    /* ld_value_word &id */
                    // finsh_code_byte(FINSH_OP_LD_VALUE_WORD);
                    // finsh_code_dword((long)&(var->value.short_value));

                    /* ld_dword &id */
                    finsh_code_byte(FINSH_OP_LD_DWORD);
                    finsh_code_dword((long)&(var->value.short_value));

                    /* ld_value_word &id */
                    finsh_code_byte(FINSH_OP_LD_VALUE_WORD);
                    finsh_code_dword((long)&(var->value.short_value));

                    /* ld_word 1 */
                    finsh_code_byte(FINSH_OP_LD_WORD);
                    finsh_code_word(1);

                    /* add_byte */
                    finsh_code_byte(FINSH_OP_SUB_WORD);
                    /* get byte */
                    finsh_code_byte(FINSH_OP_ST_WORD);

                    /* pop */
                    finsh_code_byte(FINSH_OP_POP);
                    break;

                case FINSH_DATA_TYPE_DWORD:
                    /* ld_value_dword &id */
                    // finsh_code_byte(FINSH_OP_LD_VALUE_DWORD);
                    // finsh_code_dword((long)&(var->value.long_value));

                    /* ld_dword &id */
                    finsh_code_byte(FINSH_OP_LD_DWORD);
                    finsh_code_dword((long)&(var->value.long_value));

                    /* ld_value_dword &id */
                    finsh_code_byte(FINSH_OP_LD_VALUE_DWORD);
                    finsh_code_dword((long)&(var->value.long_value));

                    /* ld_dword 1 */
                    finsh_code_byte(FINSH_OP_LD_DWORD);
                    finsh_code_dword(1);

                    /* add_byte */
                    finsh_code_byte(FINSH_OP_SUB_DWORD);
                    /* get byte */
                    finsh_code_byte(FINSH_OP_ST_DWORD);

                    /* pop */
                    finsh_code_byte(FINSH_OP_POP);
                    break;
                }
            }
            break;

        case FINSH_NODE_SYS_NULL:
            finsh_code_dword(0);
            break;

        case FINSH_NODE_SYS_GETVALUE:
            if (node->idtype & FINSH_IDTYPE_ADDRESS)
            {
                /* nothing will be generated */
            }
            else
            {
                switch (node->data_type)
                {
                case FINSH_DATA_TYPE_BYTE:
                    finsh_code_byte(FINSH_OP_LD_VALUE_BYTE_STACK);
                    break;
                case FINSH_DATA_TYPE_WORD:
                    finsh_code_byte(FINSH_OP_LD_VALUE_WORD_STACK);
                    break;
                case FINSH_DATA_TYPE_DWORD:
                    finsh_code_byte(FINSH_OP_LD_VALUE_DWORD_STACK);
                    break;
                default:
                    break;
                }
            }
            break;

        case FINSH_NODE_SYS_GETADDR:
            /* nothing will be generated */
            break;

        default:
            finsh_error_set(FINSH_ERROR_UNKNOWN_NODE);
            break;
        }

        /* compile sibling node */
        if (finsh_node_sibling(node) != NULL)
            finsh_compile(finsh_node_sibling(node));
    }

    return 0;
}

static int finsh_type_check(struct finsh_node* node, uint8_t is_addr)
{
    if (node != NULL)
    {
        /* address & value */
        if (node->node_type == FINSH_NODE_SYS_ASSIGN ||
            node->node_type == FINSH_NODE_SYS_PREINC ||
            node->node_type == FINSH_NODE_SYS_PREDEC ||
            node->node_type == FINSH_NODE_SYS_GETADDR)
        {
            /* address */
            finsh_type_check(finsh_node_child(node), FINSH_IDTYPE_ADDRESS);
        }
        else if (node->node_type == FINSH_NODE_SYS_GETVALUE && is_addr)
        {
            /* change the attribute of getvalue in left expr */
            finsh_type_check(finsh_node_child(node), 0);
        }
        else
        {
            /* transfer 'av' to child node */
            finsh_type_check(finsh_node_child(node), is_addr);
        }

        /* always does not load address in sibling */
        finsh_type_check(finsh_node_sibling(node), FINSH_NODE_VALUE);

        /** set attribute of current node */

        /* make sure the current node is address or value */
        if (node->idtype != FINSH_IDTYPE_SYSCALL) node->idtype |= is_addr;

        if (finsh_node_child(node) != NULL)
        {
            node->data_type = finsh_node_child(node)->data_type;
            return 0;
        }

        if (node->node_type == FINSH_NODE_ID)
        {
            if (node->idtype & FINSH_IDTYPE_VAR)
            {
                struct finsh_var* var;

                var = node->id.var;
                if (var != NULL)
                {
                    switch (var->type)
                    {
                    case finsh_type_void:
                        node->data_type = FINSH_DATA_TYPE_VOID;
                        break;

                    case finsh_type_char:
                    case finsh_type_uchar:
                        node->data_type = FINSH_DATA_TYPE_BYTE;
                        break;

                    case finsh_type_short:
                    case finsh_type_ushort:
                        node->data_type = FINSH_DATA_TYPE_WORD;
                        break;

                    case finsh_type_int:
                    case finsh_type_uint:
                    case finsh_type_long:
                    case finsh_type_ulong:
                        node->data_type = FINSH_DATA_TYPE_DWORD;
                        break;

                    case finsh_type_charp:
                    case finsh_type_voidp:
                    case finsh_type_shortp:
                    case finsh_type_intp:
                    case finsh_type_longp:
                        node->data_type = FINSH_DATA_TYPE_DWORD;
                        break;

                    default:
                        finsh_error_set(FINSH_ERROR_UNKNOWN_TYPE);
                        break;
                    }
                }
            }
            else if (node->idtype & FINSH_IDTYPE_SYSVAR)
            {
                struct finsh_sysvar *sysvar;

                sysvar = node->id.sysvar;
                if (sysvar != NULL)
                {
                    switch (sysvar->type)
                    {
                    case finsh_type_void:
                        node->data_type = FINSH_DATA_TYPE_VOID;
                        break;

                    case finsh_type_char:
                    case finsh_type_uchar:
                        node->data_type = FINSH_DATA_TYPE_BYTE;
                        break;

                    case finsh_type_short:
                    case finsh_type_ushort:
                        node->data_type = FINSH_DATA_TYPE_WORD;
                        break;

                    case finsh_type_int:
                    case finsh_type_uint:
                    case finsh_type_long:
                    case finsh_type_ulong:
                        node->data_type = FINSH_DATA_TYPE_DWORD;
                        break;

                    case finsh_type_charp:
                    case finsh_type_voidp:
                    case finsh_type_shortp:
                    case finsh_type_intp:
                    case finsh_type_longp:
                        node->data_type = FINSH_DATA_TYPE_DWORD;
                        break;

                    default:
                        finsh_error_set(FINSH_ERROR_UNKNOWN_TYPE);
                        break;
                    }
                }
            }
        }
        else if (node->node_type == FINSH_NODE_VALUE_CHAR)
        {
            node->data_type = FINSH_DATA_TYPE_BYTE;
        }
        else if (node->node_type == FINSH_NODE_VALUE_INT ||
            node->node_type == FINSH_NODE_VALUE_LONG    ||
            node->node_type == FINSH_NODE_VALUE_STRING  ||
            node->node_type == FINSH_NODE_VALUE_NULL)
        {
            node->data_type = FINSH_DATA_TYPE_DWORD;
        }
    }
    return 0;
}

int finsh_compiler_run(struct finsh_node* node)
{
    struct finsh_node* sibling;

    /* type check */
    finsh_type_check(node, FINSH_NODE_VALUE);

    /* clean text segment and vm stack */
    memset(&text_segment[0], 0, sizeof(text_segment));
    memset(&finsh_vm_stack[0], 0, sizeof(finsh_vm_stack));

    /* reset compile stack pointer and pc */
    finsh_compile_sp = &finsh_vm_stack[0];
    finsh_compile_pc = &text_segment[0];

    /* compile node */
    sibling = node;
    while (sibling != NULL)
    {
        struct finsh_node* current_node;
        current_node = sibling;

        /* get sibling node */
        sibling = current_node->sibling;

        /* clean sibling node */
        current_node->sibling = NULL;
        finsh_compile(current_node);

        /* pop current value */
        if (sibling != NULL) finsh_code_byte(FINSH_OP_POP);
    }

    return 0;
}
