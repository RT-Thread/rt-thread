/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2010-03-22     Bernard      first version
 * 2013-10-09     Bernard      fix the command line too long issue.
 */
#include <finsh.h>

#include "finsh_token.h"
#include "finsh_node.h"
#include "finsh_error.h"
#include "finsh_parser.h"
#include "finsh_var.h"

/*
 * the structure of abstract syntax tree:
 * root____________
 * |               \
 * child__        sibling__
 * |      \       |        \
 * child sibling  child   sibling
 *                          ...
 */
static enum finsh_type proc_type(struct finsh_parser* self);
static int proc_identifier(struct finsh_parser* self, char* id);
static struct finsh_node* proc_variable_decl(struct finsh_parser* self);
static struct finsh_node* proc_expr(struct finsh_parser* self);
static struct finsh_node* proc_assign_expr(struct finsh_parser* self);
static struct finsh_node* proc_inclusive_or_expr(struct finsh_parser* self);
static struct finsh_node* proc_exclusive_or_expr(struct finsh_parser* self);
static struct finsh_node* proc_and_expr(struct finsh_parser* self);
static struct finsh_node* proc_shift_expr(struct finsh_parser* self);
static struct finsh_node* proc_additive_expr(struct finsh_parser* self);
static struct finsh_node* proc_multiplicative_expr(struct finsh_parser* self);
static struct finsh_node* proc_cast_expr(struct finsh_parser* self);
static struct finsh_node* proc_unary_expr(struct finsh_parser* self);
static struct finsh_node* proc_postfix_expr(struct finsh_parser* self);
static struct finsh_node* proc_primary_expr(struct finsh_parser* self);
static struct finsh_node* proc_param_list(struct finsh_parser* self);
static struct finsh_node* proc_expr_statement(struct finsh_parser* self);
static struct finsh_node* make_sys_node(uint8_t type, struct finsh_node* node1,
    struct finsh_node* node2);

/* check token */
#define check_token(token, lex, type) if ( (token) != (type) ) \
    { \
        finsh_error_set(FINSH_ERROR_INVALID_TOKEN); \
        finsh_token_replay(lex); \
    }

/* is the token a data type? */
#define is_base_type(token) ((token) == finsh_token_type_void \
    || (token) == finsh_token_type_char \
    || (token) == finsh_token_type_short \
    || (token) == finsh_token_type_int \
    || (token) == finsh_token_type_long)

/* get the next token */
#define next_token(token, lex)  (token) = finsh_token_token(lex)

/* match a specified token */
#define match_token(token, lex, type)   next_token(token, lex); \
    check_token(token, lex, type)

/*
process for function and variable declaration.
decl_variable -> type declaration_list ';'
declarator_list -> declarator_list ',' declarator
    | declarator
declarator -> identifier
    | identifier ASSIGN expr_assign
*/
static struct finsh_node* proc_variable_decl(struct finsh_parser* self)
{
    enum finsh_token_type token;
    enum finsh_type type;
    char id[FINSH_NAME_MAX + 1];

    struct finsh_node *node;
    struct finsh_node *end;
    struct finsh_node *assign;

    node = NULL;
    end  = NULL;

    /* get type */
    type = proc_type(self);

    /*process id.*/
    if (proc_identifier(self, id) == 0)
    {
        /* if add variable failed */
        if (finsh_var_insert(id, type) < 0)
        {
            finsh_error_set(FINSH_ERROR_VARIABLE_EXIST);
        }
    }

    next_token(token, &(self->token));
    switch ( token )
    {
    case finsh_token_type_comma:/*',', it's a variable_list declaration.*/
        if (proc_identifier(self, id) == 0)
        {
            /* if add variable failed */
            if (finsh_var_insert(id, type) < 0)
            {
                finsh_error_set(FINSH_ERROR_VARIABLE_EXIST);
            }
        }

        next_token(token, &(self->token));
        if ( token == finsh_token_type_assign )
        {
            /* get the right side of assign expression */
            assign = proc_assign_expr(self);

            if (assign != NULL)
            {
                struct finsh_node* idnode;

                idnode = finsh_node_new_id(id);
                end = make_sys_node(FINSH_NODE_SYS_ASSIGN, idnode, assign);
                node = end;

                next_token(token, &(self->token));
            }
        }

        while ( token == finsh_token_type_comma )
        {
            if (proc_identifier(self, id) == 0)
            {
                /* if add variable failed */
                if (finsh_var_insert(id, type) < 0)
                {
                    finsh_error_set(FINSH_ERROR_VARIABLE_EXIST);
                }
            }

            next_token(token, &(self->token));
            if ( token == finsh_token_type_assign )
            {
                /* get the right side of assign expression */
                assign = proc_assign_expr(self);

                if (assign != NULL)
                {
                    struct finsh_node* idnode;

                    idnode = finsh_node_new_id(id);

                    /* make assign expression node */
                    if (node != NULL)
                    {
                        finsh_node_sibling(end) = make_sys_node(FINSH_NODE_SYS_ASSIGN, idnode, assign);
                        end = finsh_node_sibling(end);
                    }
                    else
                    {
                        end = make_sys_node(FINSH_NODE_SYS_ASSIGN, idnode, assign);
                        node = end;
                    }

                    next_token(token, &(self->token));
                }
            }
        }

        check_token(token, &(self->token), finsh_token_type_semicolon);
        return node;

    case finsh_token_type_assign:/*'=', it's a variable with assign declaration.*/
    {
        struct finsh_node *idnode;

        assign = proc_assign_expr(self);
        if (assign != NULL)
        {
            idnode = finsh_node_new_id(id);

            /* make assign expression node */
            end = make_sys_node(FINSH_NODE_SYS_ASSIGN, idnode, assign);
            node = end;

            next_token(token, &(self->token));
        }

        while ( token == finsh_token_type_comma )
        {
            if (proc_identifier(self, id) == 0)
            {
                /* if add variable failed */
                if (finsh_var_insert(id, type) < 0)
                {
                    finsh_error_set(FINSH_ERROR_VARIABLE_EXIST);
                }
            }

            next_token(token, &(self->token));
            if (token == finsh_token_type_assign)
            {
                /* get the right side of assign expression */
                assign = proc_assign_expr(self);

                if (assign != NULL)
                {
                    idnode = finsh_node_new_id(id);

                    /* make assign expression node */
                    if (node != NULL)
                    {
                        finsh_node_sibling(end) = make_sys_node(FINSH_NODE_SYS_ASSIGN, idnode, assign);
                        end = finsh_node_sibling(end);
                    }
                    else
                    {
                        end = make_sys_node(FINSH_NODE_SYS_ASSIGN, idnode, assign);
                        node = end;
                    }

                    next_token(token, &(self->token));
                }
            }
        }

        check_token(token, &(self->token), finsh_token_type_semicolon);
        return node;
    }

    case finsh_token_type_semicolon:/*';', it's a variable declaration.*/
        return node;

    default:
        finsh_error_set(FINSH_ERROR_EXPECT_TYPE);

        return NULL;
    }
}

/*
type -> type_prefix type_basic | type_basic
type_prefix -> UNSIGNED
type_basic -> VOID
    | CHAR
    | SHORT
    | INT
    | STRING
*/
static enum finsh_type proc_type(struct finsh_parser* self)
{
    enum finsh_type type;
    enum finsh_token_type token;

    /* set init type */
    type = finsh_type_unknown;

    next_token(token, &(self->token));
    if ( is_base_type(token) ) /* base_type */
    {
        switch (token)
        {
        case finsh_token_type_void:
            type = finsh_type_void;
            break;

        case finsh_token_type_char:
            type = finsh_type_char;
            break;

        case finsh_token_type_short:
            type = finsh_type_short;
            break;

        case finsh_token_type_int:
            type = finsh_type_int;
            break;

        case finsh_token_type_long:
            type = finsh_type_long;
            break;

        default:
            goto __return;
        }
    }
    else if ( token == finsh_token_type_unsigned ) /* unsigned base_type */
    {
        next_token(token, &(self->token));
        if ( is_base_type(token) )
        {
            switch (token)
            {
            case finsh_token_type_char:
                type = finsh_type_uchar;
                break;

            case finsh_token_type_short:
                type = finsh_type_ushort;
                break;

            case finsh_token_type_int:
                type = finsh_type_uint;
                break;

            case finsh_token_type_long:
                type = finsh_type_ulong;
                break;

            default:
                goto __return;
            }
        }
        else
        {
            finsh_token_replay(&(self->token));
            finsh_error_set(FINSH_ERROR_EXPECT_TYPE);
        }
    }
    else
    {
        goto __return;
    }

    /* parse for pointer */
    next_token(token, &(self->token));
    if (token == finsh_token_type_mul)
    {
        switch (type)
        {
        case finsh_type_void:
            type = finsh_type_voidp;
            break;

        case finsh_type_char:
        case finsh_type_uchar:
            type = finsh_type_charp;
            break;

        case finsh_type_short:
        case finsh_type_ushort:
            type = finsh_type_shortp;
            break;

        case finsh_type_int:
        case finsh_type_uint:
            type = finsh_type_intp;
            break;

        case finsh_type_long:
        case finsh_type_ulong:
            type = finsh_type_longp;
            break;

        default:
            type = finsh_type_voidp;
            break;
        }
    }
    else finsh_token_replay(&(self->token));

    return type;

__return:
    finsh_token_replay(&(self->token));
    finsh_error_set(FINSH_ERROR_UNKNOWN_TYPE);

    return type;
}

/*
identifier -> IDENTIFIER
*/
static int proc_identifier(struct finsh_parser* self, char* id)
{
    enum finsh_token_type token;

    match_token(token, &(self->token), finsh_token_type_identifier);

    strncpy(id, (char*)self->token.string, FINSH_NAME_MAX);

    return 0;
}

/*
statement_expr -> ';'
    | expr ';'
*/
static struct finsh_node* proc_expr_statement(struct finsh_parser* self)
{
    enum finsh_token_type token;
    struct finsh_node* expr;

    expr = NULL;
    next_token(token, &(self->token));
    if ( token != finsh_token_type_semicolon )
    {
        finsh_token_replay(&(self->token));
        expr = proc_expr(self);

        match_token(token, &(self->token), finsh_token_type_semicolon);
    }

    return expr;
}

/*
expr -> expr_assign
*/
static struct finsh_node* proc_expr(struct finsh_parser* self)
{
    return proc_assign_expr(self);
}

/*
expr_assign -> expr_inclusive_or
    | expr_unary ASSIGN expr_assign
*/
static struct finsh_node* proc_assign_expr(struct finsh_parser* self)
{
    enum finsh_token_type token;
    struct finsh_node* or;
    struct finsh_node* assign;

    or = proc_inclusive_or_expr(self);

    next_token(token, &(self->token));

    if (token == finsh_token_type_assign)
    {
        assign = proc_assign_expr(self);

        return make_sys_node(FINSH_NODE_SYS_ASSIGN, or, assign);
    }
    else finsh_token_replay(&(self->token));

    return or;
}

/*
expr_inclusive_or -> expr_exclusive_or
    | expr_inclusive_or '|' expr_exclusive_or
*/
static struct finsh_node* proc_inclusive_or_expr(struct finsh_parser* self)
{
    enum finsh_token_type token;
    struct finsh_node* xor;
    struct finsh_node* xor_new;

    xor = proc_exclusive_or_expr(self);

    next_token(token, &(self->token));
    while ( token == finsh_token_type_or )
    {
        xor_new = proc_exclusive_or_expr(self);

        if (xor_new == NULL) finsh_error_set(FINSH_ERROR_EXPECT_OPERATOR);
        else xor = make_sys_node(FINSH_NODE_SYS_OR, xor, xor_new);

        next_token(token, &(self->token));
    }

    finsh_token_replay(&(self->token));
    return xor;
}

/*
expr_exclusive_or -> expr_and
    | expr_exclusive '^' expr_and
*/
static struct finsh_node* proc_exclusive_or_expr(struct finsh_parser* self)
{
    enum finsh_token_type token;
    struct finsh_node* and;
    struct finsh_node* and_new;

    and = proc_and_expr(self);
    next_token(token, &(self->token));
    while ( token == finsh_token_type_xor )
    {
        and_new = proc_and_expr(self);
        if (and_new == NULL) finsh_error_set(FINSH_ERROR_EXPECT_OPERATOR);
        else and = make_sys_node(FINSH_NODE_SYS_XOR, and, and_new);

        next_token(token, &(self->token));
    }

    finsh_token_replay(&(self->token));
    return and;
}

/*
expr_and -> expr_shift
    | expr_and '&' expr_shift
*/
static struct finsh_node* proc_and_expr(struct finsh_parser* self)
{
    enum finsh_token_type token;
    struct finsh_node* shift;
    struct finsh_node* shift_new;

    shift = proc_shift_expr(self);

    next_token(token, &(self->token));
    while ( token == finsh_token_type_and )
    {
        shift_new = proc_shift_expr(self);

        if (shift_new == NULL) finsh_error_set(FINSH_ERROR_EXPECT_OPERATOR);
        else shift = make_sys_node(FINSH_NODE_SYS_AND, shift, shift_new);

        next_token(token, &(self->token));
    }

    finsh_token_replay(&(self->token));
    return shift;
}

/*
expr_shift -> expr_additive
    | expr_shift '<<' expr_additive
    | expr_shift '>>' expr_additive
*/
static struct finsh_node* proc_shift_expr(struct finsh_parser* self)
{
    enum finsh_token_type token;
    struct finsh_node* add;
    struct finsh_node* add_new;

    add = proc_additive_expr(self);

    next_token(token, &(self->token));
    while ( token == finsh_token_type_shl || token == finsh_token_type_shr)
    {
        add_new = proc_additive_expr(self);
        if (add_new == NULL) finsh_error_set(FINSH_ERROR_EXPECT_OPERATOR);
        else
        {
            switch (token)
            {
            case finsh_token_type_shl:
                add = make_sys_node(FINSH_NODE_SYS_SHL, add, add_new);
                break;
            case finsh_token_type_shr:
                add = make_sys_node(FINSH_NODE_SYS_SHR, add, add_new);
                break;
            default:
                finsh_error_set(FINSH_ERROR_EXPECT_OPERATOR);
                break;
            }
        }
        next_token(token, &(self->token));
    }

    finsh_token_replay(&(self->token));
    return add;
}

/*
expr_additive -> expr_multiplicative
    | expr_additive SUB expr_multiplicative
    | expr_additive ADD expr_multiplicative
*/
static struct finsh_node* proc_additive_expr(struct finsh_parser* self)
{
    enum finsh_token_type token;
    struct finsh_node* mul;
    struct finsh_node* mul_new;

    mul = proc_multiplicative_expr(self);

    next_token(token, &(self->token));
    while ( token == finsh_token_type_sub || token == finsh_token_type_add )
    {
        mul_new = proc_multiplicative_expr(self);
        if (mul_new == NULL) finsh_error_set(FINSH_ERROR_EXPECT_OPERATOR);
        else
        {
            switch (token)
            {
            case finsh_token_type_sub:
                mul = make_sys_node(FINSH_NODE_SYS_SUB, mul, mul_new);
                break;
            case finsh_token_type_add:
                mul = make_sys_node(FINSH_NODE_SYS_ADD, mul, mul_new);
                break;
            default:
                finsh_error_set(FINSH_ERROR_EXPECT_OPERATOR);
                break;
            }
        }
        next_token(token, &(self->token));
    }

    finsh_token_replay(&(self->token));
    return mul;
}

/*
expr_multiplicative -> expr_cast
    | expr_multiplicative '*' expr_cast
    | expr_multiplicative '/' expr_cast
    | expr_multiplicative '%' expr_cast
*/
static struct finsh_node* proc_multiplicative_expr(struct finsh_parser* self)
{
    enum finsh_token_type token;
    struct finsh_node* cast;
    struct finsh_node* cast_new;

    cast = proc_cast_expr(self);
    next_token(token, &(self->token));
    while (token == finsh_token_type_mul ||
        token == finsh_token_type_div ||
        token == finsh_token_type_mod )
    {
        cast_new = proc_cast_expr(self);
        if (cast_new == NULL) finsh_error_set(FINSH_ERROR_EXPECT_OPERATOR);
        else
        {
            switch (token)
            {
            case finsh_token_type_mul:
                cast = make_sys_node(FINSH_NODE_SYS_MUL, cast, cast_new);
                break;

            case finsh_token_type_div:
                cast = make_sys_node(FINSH_NODE_SYS_DIV, cast, cast_new);
                break;

            case finsh_token_type_mod:
                cast = make_sys_node(FINSH_NODE_SYS_MOD, cast, cast_new);
                break;

            default:
                finsh_error_set(FINSH_ERROR_EXPECT_OPERATOR);
                break;
            }
        }
        next_token(token, &(self->token));
    }

    finsh_token_replay(&(self->token));
    return cast;
}

/*
20060313, add recast parse
expr_cast -> expr_unary
    | '(' type ')' expr_cast
*/
static struct finsh_node* proc_cast_expr(struct finsh_parser* self)
{
    enum finsh_token_type token;
    enum finsh_type type;
    struct finsh_node* cast;

    next_token(token, &(self->token));
    if (token == finsh_token_type_left_paren)
    {
        type = proc_type(self);
        match_token(token, &(self->token), finsh_token_type_right_paren);

        cast = proc_cast_expr(self);
        if (cast != NULL)
        {
            cast->data_type = type;
            return cast;
        }
    }

    finsh_token_replay(&(self->token));
    return proc_unary_expr(self);
}

/*
20050921, add '*' and '&'
expr_unary -> expr_postfix
    | ADD expr_cast
    | INC expr_cast
    | SUB expr_cast
    | DEC expr_cast
    | '~' expr_cast
    | '*' expr_cast
    | '&' expr_cast
*/
static struct finsh_node* proc_unary_expr(struct finsh_parser* self)
{
    enum finsh_token_type token;
    struct finsh_node *cast;

    next_token(token, &(self->token));
    switch (token)
    {
    case finsh_token_type_add: /* + */
        cast = proc_cast_expr(self);
        return cast;

    case finsh_token_type_inc: /* ++ */
        cast = proc_cast_expr(self);
        return make_sys_node(FINSH_NODE_SYS_PREINC, cast, NULL);

    case finsh_token_type_sub: /* - */
        cast = proc_cast_expr(self);
        return make_sys_node(FINSH_NODE_SYS_SUB, finsh_node_new_long(0), cast);

    case finsh_token_type_dec: /* -- */
        cast = proc_cast_expr(self);
        return make_sys_node(FINSH_NODE_SYS_PREDEC, cast, NULL);

    case finsh_token_type_bitwise: /* ~ */
        cast = proc_cast_expr(self);
        return make_sys_node(FINSH_NODE_SYS_BITWISE, cast, NULL);

    case finsh_token_type_mul: /* * */
        cast = proc_cast_expr(self);
        return make_sys_node(FINSH_NODE_SYS_GETVALUE, cast, NULL);

    case finsh_token_type_and: /* & */
        cast = proc_cast_expr(self);
        return make_sys_node(FINSH_NODE_SYS_GETADDR, cast, NULL);

    default:
        finsh_token_replay(&(self->token));
        return proc_postfix_expr(self);
    }
}

/*
expr_postfix -> expr_primary
    | expr_postfix INC
    | expr_postfix DEC
    | expr_postfix '(' param_list ')'
*/
static struct finsh_node* proc_postfix_expr(struct finsh_parser* self)
{
    enum finsh_token_type token;
    struct finsh_node* postfix;

    postfix = proc_primary_expr(self);

    next_token(token, &(self->token));
    while ( token == finsh_token_type_inc   ||
        token == finsh_token_type_dec       ||
        token == finsh_token_type_left_paren )
    {
        switch (token)
        {
        case finsh_token_type_inc :/* '++' */
            postfix = make_sys_node(FINSH_NODE_SYS_INC, postfix, NULL);
            break;

        case finsh_token_type_dec :/* '--' */
            postfix = make_sys_node(FINSH_NODE_SYS_DEC, postfix, NULL);
            break;

        case finsh_token_type_left_paren :/* '(' */
            {
                struct finsh_node* param_list;

                param_list = NULL;
                next_token(token, &(self->token));
                if (token != finsh_token_type_right_paren)
                {
                    finsh_token_replay(&(self->token));
                    param_list = proc_param_list(self);

                    match_token(token, &(self->token), finsh_token_type_right_paren);
                }

                postfix = make_sys_node(FINSH_NODE_SYS_FUNC, postfix, param_list);
            }
            break;

        default:
            break;
        }

        next_token(token, &(self->token));
    }

    finsh_token_replay(&(self->token));
    return postfix;
}

/*
expr_primary -> literal
    | '(' expr ')'
    | identifier
*/
static struct finsh_node* proc_primary_expr(struct finsh_parser* self)
{
    enum finsh_token_type token;
    struct finsh_node* expr;

    next_token(token, &(self->token));
    switch ( token )
    {
    case finsh_token_type_identifier:
        {
            char id[FINSH_NAME_MAX + 1];

            finsh_token_replay(&(self->token));
            proc_identifier(self, id);
            return finsh_node_new_id(id);
        }

    case finsh_token_type_left_paren:
        expr = proc_expr(self);
        match_token(token, &(self->token), finsh_token_type_right_paren);
        return expr;

    case finsh_token_type_value_int:
        return finsh_node_new_int(self->token.value.int_value);

    case finsh_token_type_value_long:
        return finsh_node_new_long(self->token.value.long_value);

    case finsh_token_type_value_char:
        return finsh_node_new_char(self->token.value.char_value);

    case finsh_token_type_value_string:
        return finsh_node_new_string((char*)self->token.string);

    case finsh_token_type_value_null:
        return finsh_node_new_ptr(NULL);

    default:
        finsh_error_set(FINSH_ERROR_INVALID_TOKEN);
        break;
    }

    return NULL;
}

/*
param_list -> empty
    | expr_assign
    | param_list ',' expr_assign
*/
static struct finsh_node* proc_param_list(struct finsh_parser* self)
{
    enum finsh_token_type token;
    struct finsh_node *node, *assign;

    assign = proc_assign_expr(self);
    if (assign == NULL) return NULL;
    node = assign;

    next_token(token, &(self->token));
    while (token == finsh_token_type_comma )
    {
        finsh_node_sibling(assign) = proc_assign_expr(self);

        if (finsh_node_sibling(assign) != NULL) assign = finsh_node_sibling(assign);
        else finsh_error_set(FINSH_ERROR_EXPECT_OPERATOR);

        next_token(token, &(self->token));
    }

    finsh_token_replay(&(self->token));

    return node;
}

/*
make a new node as following tree:
new_node
|
node1__
       \
       node2
*/
static struct finsh_node* make_sys_node(uint8_t type, struct finsh_node* node1, struct finsh_node* node2)
{
    struct finsh_node* node;

    node = finsh_node_allocate(type);

    if ((node1 != NULL) && (node != NULL))
    {
        finsh_node_child(node) = node1;
        finsh_node_sibling(node1) = node2;
    }
    else finsh_error_set(FINSH_ERROR_NULL_NODE);

    return node;
}

/*
start -> statement_expr | decl_variable
*/
void finsh_parser_run(struct finsh_parser* self, const uint8_t* string)
{
    enum finsh_token_type token;
    struct finsh_node *node;

    node = NULL;

    /* init parser */
    self->parser_string = (uint8_t*)string;

    /* init token */
    finsh_token_init(&(self->token), self->parser_string);

    /* get next token */
    next_token(token, &(self->token));
    while (token != finsh_token_type_eof && token != finsh_token_type_bad)
    {
        switch (token)
        {
        case finsh_token_type_identifier:
            /* process expr_statement */
            finsh_token_replay(&(self->token));

            if (self->root != NULL)
            {
                finsh_node_sibling(node) = proc_expr_statement(self);
                if (finsh_node_sibling(node) != NULL)
                    node = finsh_node_sibling(node);
            }
            else
            {
                node = proc_expr_statement(self);
                self->root = node;
            }
            break;

        default:
            if (is_base_type(token) || token == finsh_token_type_unsigned)
            {
                /* variable decl */
                finsh_token_replay(&(self->token));

                if (self->root != NULL)
                {
                    finsh_node_sibling(node) = proc_variable_decl(self);
                    if (finsh_node_sibling(node) != NULL)
                        node = finsh_node_sibling(node);
                }
                else
                {
                    node = proc_variable_decl(self);
                    self->root = node;
                }
            }
            else
            {
                /* process expr_statement */
                finsh_token_replay(&(self->token));

                if (self->root != NULL)
                {
                    finsh_node_sibling(node) = proc_expr_statement(self);
                    if (finsh_node_sibling(node) != NULL)
                        node = finsh_node_sibling(node);
                    else next_token(token, &(self->token));
                }
                else
                {
                    node = proc_expr_statement(self);
                    self->root = node;
                }
            }

            break;
        }

        /* no root found, break out */
        if (self->root == NULL) break;

        /* get next token */
        next_token(token, &(self->token));
    }
}

int finsh_parser_init(struct finsh_parser* self)
{
    memset(self, 0, sizeof(struct finsh_parser));

    return 0;
}
