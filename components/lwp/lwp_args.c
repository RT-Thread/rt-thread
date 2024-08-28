/*
 * Copyright (c) 2006-2024, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2024-01-12     Shell        separate argv, envp, aux processing to lwp_args.c
 *                             Bugs fix for script arguments processing.
 *                             support args larger than 4k
 */
#include "lwp_args.h"
#include "lwp_internal.h"
#include "mm_page.h"

static void _strvec_init(struct lwp_string_vector *sv)
{
    #define DEFAUTL_ARGV_BUFLEN 4
    sv->strvec = rt_malloc(DEFAUTL_ARGV_BUFLEN * sizeof(char *));
    sv->strvec_buflen = DEFAUTL_ARGV_BUFLEN;
    sv->string_count = 0;
}

static void _strvec_detach(struct lwp_string_vector *sv)
{
    if (sv->strvec)
    {
        rt_free(sv->strvec);
    }
}

static rt_err_t _strvec_append(struct lwp_string_vector *sv, const char *string)
{
    if (sv->string_count == sv->strvec_buflen)
    {
        void *newptr;
        newptr = rt_realloc(sv->strvec, sv->strvec_buflen * 2 * sizeof(char *));
        if (!newptr)
            return -RT_ENOMEM;
        sv->strvec = newptr;
        sv->strvec_buflen *= 2;
    }

    sv->strvec[sv->string_count++] = string;
    return RT_EOK;
}

static rt_err_t args_append(struct lwp_args_info *ai, const char *str_addr,
                            size_t str_len, enum lwp_args_type atype)
{
    rt_err_t error;
    char *str_bufaddr;

    if (ai->strings_length + str_len + 1 > ai->str_buf_size)
    {
        /* reallocate buffer for this */
        void *newptr;
        newptr = rt_realloc(ai->str_buf, ai->str_buf_size * 2);
        if (!newptr)
            return -RT_ENOMEM;
        ai->str_buf = newptr;
        ai->str_buf_size *= 2;
    }

    /* append new string to string buffer and update strings_length */
    str_bufaddr = &ai->str_buf[ai->strings_length];
    if (atype == LWP_ARGS_TYPE_KARG || atype == LWP_ARGS_TYPE_KENVP)
    {
        strcpy(str_bufaddr, str_addr);
        ai->strings_length += str_len + 1;
    }
    else
    {
        lwp_get_from_user(str_bufaddr, (void *)str_addr, str_len);
        ai->strings_length += str_len;
        ai->str_buf[ai->strings_length++] = '\0';
    }

    /* append new argument or environment */
    switch (atype)
    {
        case LWP_ARGS_TYPE_ARG:
        case LWP_ARGS_TYPE_KARG:
            error = _strvec_append(&ai->argv, str_bufaddr);
            if (!error && ai->argv.string_count == 1)
            {
                ai->argv0_strlen = str_len;
            }
            break;
        case LWP_ARGS_TYPE_ENVP:
        case LWP_ARGS_TYPE_KENVP:
            error = _strvec_append(&ai->envp, str_bufaddr);
            break;
        default:
            break;
    }
    return error;
}


/**
 * @brief Override arguments 0 for script interpreter.
 *
 * Manual: interpreter will be invoked with the following arguments:
 *      {interpreter [optional-arg] pathname arg...}
 * where pathname is the pathname of the file specified as the first
 * argument of execve(), and arg...  is the series of words pointed
 * to by the argv argument of execve(), starting at argv[1].  Note
 * that there is no way to get the argv[0] that was passed to the
 * execve() call.
 */
static rt_err_t _args_override_argv0(struct lwp_args_info *ai, struct lwp_args_info *ow_ai)
{
    rt_err_t error = 0;
    int i, new_argc, new_strbuf_size, ai_bytes_tobe_copied;
    char **new_argv, *new_strbuf, *base;
    rt_base_t off;

    if (ow_ai == 0 || ow_ai->argv.string_count == 0)
    {
        return -RT_EINVAL;
    }

    /* for new argument vector */
    new_argc = ai->argv.string_count - 1 + ow_ai->argv.string_count;
    new_argv = rt_malloc(new_argc * sizeof(char *));
    if (!new_argv)
    {
        return -RT_ENOMEM;
    }

    /* for new string buffer */
    ai_bytes_tobe_copied = ai->strings_length - (ai->argv0_strlen + 1);
    new_strbuf_size = ai_bytes_tobe_copied + ow_ai->strings_length;
    new_strbuf = rt_malloc(new_strbuf_size);
    if (!new_argv)
    {
        rt_free(new_argv);
        return -RT_ENOMEM;
    }

    base = new_strbuf;
    off = base - ow_ai->str_buf;
    /* copy overriding argument strings and argv */
    memcpy(base, ow_ai->str_buf, ow_ai->strings_length);
    for (i = 0; i < ow_ai->argv.string_count; i++)
    {
        /* base + ow_ai->argv.strvec[i] - ow_ai->str_buf */
        new_argv[i] = (char *)ow_ai->argv.strvec[i] + off;
    }

    base += ow_ai->strings_length;
    off = base - (ai->str_buf + ai->argv0_strlen + 1);
    /* copy old argument strings starting from argv[1] and setup new_argv */
    memcpy(base, ai->str_buf + ai->argv0_strlen + 1, ai_bytes_tobe_copied);
    for (size_t j = 1; j < ai->argv.string_count; i++, j++)
    {
        /* base + ai->argv->strvec[j] - ai->str_buf */
        new_argv[i] = (char *)ai->argv.strvec[j] + off;
    }

    /* setup envp for ai */
    for (i = 0; i < ai->envp.string_count; i++)
    {
        /* base + ai->envp->strvec[i] - ai->str_buf */
        ai->envp.strvec[i] += off;
    }

    /* replace strings buffer and argv buffer */
    ai->str_buf = new_strbuf;
    ai->strings_length = new_strbuf_size;
    ai->str_buf_size = new_strbuf_size;
    ai->argv.string_count = new_argc;
    ai->argv.strvec = (void *)new_argv;
    ai->argv.strvec_buflen = new_argc;

    ai->argv0_strlen = ow_ai->argv0_strlen;
    return error;
}

const char *lwp_args_get_argv_0(struct lwp_args_info *ai)
{
    return ai->str_buf;
}

static rt_err_t args_init(struct lwp_args_info *ai, size_t str_buf_size)
{
    void *str_buf;
    str_buf = rt_malloc(str_buf_size);
    if (!str_buf)
        return -RT_ENOMEM;

    memset(ai, 0, sizeof(*ai));

    _strvec_init(&ai->argv);
    if (!ai->argv.strvec)
    {
        rt_free(str_buf);
        return -RT_ENOMEM;
    }
    _strvec_init(&ai->envp);
    if (!ai->envp.strvec)
    {
        rt_free(str_buf);
        _strvec_detach(&ai->argv);
        return -RT_ENOMEM;
    }

    ai->str_buf_size = str_buf_size;
    ai->str_buf = str_buf;
    return RT_EOK;
}

#define STR_BUF_DEFAULT_SIZE 2048
rt_err_t lwp_args_init(struct lwp_args_info *ai)
{
    return args_init(ai, STR_BUF_DEFAULT_SIZE);
}

void lwp_args_detach(struct lwp_args_info *ai)
{
    _strvec_detach(&ai->argv);
    _strvec_detach(&ai->envp);
    rt_free(ai->str_buf);
}

#ifdef ARCH_MM_MMU
struct process_aux *lwp_argscopy(struct rt_lwp *lwp, struct lwp_args_info *ai)
{
    int size = sizeof(rt_base_t) * 4; /* store argc, argv_NULL, envp_NULL, aux_NULL */
    char *str_ua;
    const char **args_ua;
    const char **iter;
    rt_base_t off;
    struct process_aux_item pa_item;
    struct process_aux *aux_ua;
    size_t prot = PROT_READ | PROT_WRITE;
    size_t flags = MAP_FIXED | MAP_PRIVATE;
    rt_base_t argc = ai->argv.string_count;
    rt_base_t envc = ai->envp.string_count;

    /**
     * counts the bytes to storage the args
     */
    size += argc * sizeof(char *) + envc * sizeof(char *)
        + ai->strings_length + sizeof(struct process_aux);

    args_ua = lwp_mmap2(lwp, (void *)(USER_STACK_VEND), size, prot, flags, -1, 0);
    if (args_ua == RT_NULL)
    {
        return RT_NULL;
    }

    /**
     * @brief Put data from args info to user space
     * argc, argv[], NULL, envp[], NULL, aux[], NULL, strings
     */
    iter = args_ua;

    /* argc */
    lwp_data_put(lwp, iter++, &argc, sizeof(char *));

    /* strings */
    str_ua = (char *)((rt_ubase_t)args_ua +
        (1 + argc + 1 + envc + 1 + AUX_ARRAY_ITEMS_NR * 2 + 1) * sizeof(rt_base_t));
    lwp_data_put(lwp, str_ua, ai->str_buf, ai->strings_length);

    /* argv */
    off = str_ua - ai->str_buf;
    for (size_t i = 0; i < argc; i++)
    {
        /* str_ua + ai->argv.strvec[i] - ai->str_buf */
        ai->argv.strvec[i] += off;
    }
    lwp_data_put(lwp, iter, ai->argv.strvec, sizeof(char *) * ai->argv.string_count);
    iter += ai->argv.string_count;

    /* NULL */
    lwp_data_set(lwp, iter++, 0, sizeof(char *));

    /* envp */
    for (size_t i = 0; i < envc; i++)
    {
        /* str_ua + ai->envp.strvec[i] - ai->str_buf */
        ai->envp.strvec[i] += off;
    }
    lwp_data_put(lwp, iter, ai->envp.strvec, sizeof(char *) * ai->envp.string_count);
    iter += ai->envp.string_count;

    /* NULL */
    lwp_data_set(lwp, iter++, 0, sizeof(char *));

    /* aux */
    aux_ua = (struct process_aux *)iter;
    pa_item.key = AT_EXECFN;
    pa_item.value = (size_t)str_ua;
    lwp_data_put(lwp, iter, &pa_item, sizeof(pa_item));
    iter += AUX_ARRAY_ITEMS_NR * 2;

    /* NULL */
    lwp_data_set(lwp, iter++, 0, sizeof(char *));

    lwp->args = args_ua;

    return aux_ua;
}
#else
static struct process_aux *lwp_argscopy(struct rt_lwp *lwp, int argc, char **argv, char **envp)
{
#ifdef ARCH_MM_MMU
    int size = sizeof(int) * 5; /* store argc, argv, envp, aux, NULL */
    struct process_aux *aux;
#else
    int size = sizeof(int) * 4; /* store argc, argv, envp, NULL */
#endif /* ARCH_MM_MMU */
    int *args;
    char *str;
    char **new_argve;
    int i;
    int len;

    for (i = 0; i < argc; i++)
    {
        size += (rt_strlen(argv[i]) + 1);
    }
    size += (sizeof(int) * argc);

    i = 0;
    if (envp)
    {
        while (envp[i] != 0)
        {
            size += (rt_strlen(envp[i]) + 1);
            size += sizeof(int);
            i++;
        }
    }

#ifdef ARCH_MM_MMU
    /* for aux */
    size += sizeof(struct process_aux);

    args = (int *)rt_malloc(size);
    if (args == RT_NULL)
    {
        return RT_NULL;
    }

    /* argc, argv[], 0, envp[], 0 */
    str = (char *)((size_t)args + (argc + 2 + i + 1 + AUX_ARRAY_ITEMS_NR * 2 + 1) * sizeof(int));
#else
    args = (int *)rt_malloc(size);
    if (args == RT_NULL)
    {
        return RT_NULL;
    }
    str = (char*)((int)args + (argc + 2 + i + 1) * sizeof(int));
#endif /* ARCH_MM_MMU */

    new_argve = (char **)&args[1];
    args[0] = argc;

    for (i = 0; i < argc; i++)
    {
        len = rt_strlen(argv[i]) + 1;
        new_argve[i] = str;
        lwp_memcpy(str, argv[i], len);
        str += len;
    }
    new_argve[i] = 0;
    i++;

    new_argve[i] = 0;
    if (envp)
    {
        int j;
        for (j = 0; envp[j] != 0; j++)
        {
            len = rt_strlen(envp[j]) + 1;
            new_argve[i] = str;
            lwp_memcpy(str, envp[j], len);
            str += len;
            i++;
        }
        new_argve[i] = 0;
    }
#ifdef ARCH_MM_MMU
    /* aux */
    aux = (struct process_aux *)(new_argve + i);
    aux->item[0].key = AT_EXECFN;
    aux->item[0].value = (uint32_t)(size_t)new_argve[0];
    i += AUX_ARRAY_ITEMS_NR * 2;
    new_argve[i] = 0;

    lwp->args = args;

    return aux;
#else
    lwp->args = args;
    lwp->args_length = size;

    return (struct process_aux *)(new_argve + i);
#endif /* ARCH_MM_MMU */
}
#endif

rt_err_t lwp_args_put(struct lwp_args_info *args, const char **strv_addr, enum lwp_args_type atype)
{
    rt_err_t error;
    int iter = 0;
    int len;
    const char *arg_ptr;

    while (1)
    {
        if (atype == LWP_ARGS_TYPE_ARG || atype == LWP_ARGS_TYPE_ENVP)
        {
            len = lwp_get_from_user(&arg_ptr, strv_addr + iter++, sizeof(char *));
            if (len != sizeof(char *))
            {
                return -EFAULT;
            }
            if (arg_ptr == NULL)
            {
                break;
            }
            len = lwp_user_strlen(arg_ptr);
            if (len < 0)
            {
                return -EFAULT;
            }
        }
        else
        {
            arg_ptr = strv_addr[iter++];
            if (arg_ptr == NULL)
            {
                break;
            }
            len = strlen(arg_ptr);
        }

        error = args_append(args, arg_ptr, len, atype);
        if (error)
        {
            return error;
        }
    }
    return 0;
}

/**
 * @brief Put argument vector to args object
 */
rt_err_t lwp_args_put_argv(struct lwp_args_info *args, const char **argv_uaddr)
{
    return lwp_args_put(args, argv_uaddr, LWP_ARGS_TYPE_ARG);
}

/**
 * @brief Put argument vector to args object
 */
rt_err_t lwp_args_put_envp(struct lwp_args_info *args, const char **envp_uaddr)
{
    return lwp_args_put(args, envp_uaddr, LWP_ARGS_TYPE_ENVP);
}

/**
 * read words until reach nextline or EOF.
 * words copied into buffer is never truncated.
 */
#define READFILE_STAT_EOF_REACHED           0
#define READFILE_STAT_NEXTLINE_REACHED      0
#define READFILE_STAT_TRUNCATED             1
#define READFILE_STAT_CAN_READMORE(stat)    (stat)
static int _readfile(int fd, size_t maxbytes, char *buffer, int *p_readlen)
{
    int readlen;
    int stat;
    char *nlp;

    readlen = read(fd, buffer, maxbytes - 1);
    if (readlen <= 0)
    {
        /* eof, failed */
        stat = READFILE_STAT_EOF_REACHED;
        buffer[0] = '\0';
    }
    else
    {
        if ((nlp = strchr(buffer, '\n')) == NULL)
        {
            if (readlen == maxbytes - 1)
            {
                int tailing_wordlen = 0;
                char *cp = buffer + readlen - 1;
                for (; *cp && *cp != ' ' && *cp != '\t'; cp--, tailing_wordlen++)
                    ;
                if (tailing_wordlen)
                {
                    lseek(fd, -tailing_wordlen, SEEK_CUR);
                    readlen -= tailing_wordlen;
                    stat = READFILE_STAT_TRUNCATED;
                }
                else
                {
                    stat = READFILE_STAT_EOF_REACHED;
                }
            }
            else
            {
                stat = READFILE_STAT_EOF_REACHED;
            }
        }
        else
        {
            stat = READFILE_STAT_NEXTLINE_REACHED;
            readlen = nlp - buffer;
        }
        buffer[readlen] = '\0';
    }

    if (p_readlen)
        *p_readlen = readlen;
    return stat;
}

static char *_find_word(char *cp)
{
    for (; (*cp == ' ') || (*cp == '\t'); cp++)
        ;
    return cp;
}

static char *_seperate_and_get_nextword(char *cp)
{
    /* find next whitespace */
    for (; *cp && (*cp != ' ') && (*cp != '\t'); cp++)
        ;
    /* seperate words */
    while ((*cp == ' ') || (*cp == '\t'))
    {
        *cp++ = '\0';
    }
    return cp;
}

#define INTERP_BUF_SIZE 128
rt_err_t lwp_args_load_script(struct lwp_args_info *ai, const char *filename)
{
    rt_err_t error = -1;
    int fd = -RT_ERROR;
    int len;
    int rf_stat;
    char interp[INTERP_BUF_SIZE];
    char *cp, *nextword;
    char script_magic[2];
    struct lwp_args_info ow_ai = {0};

    fd = open(filename, O_BINARY | O_RDONLY, 0);
    if (fd < 0)
    {
        goto quit;
    }

    /**
     * verify an interpreter script by matching script file magic
     * eg: #!/bin/sh
     */
    len = read(fd, script_magic, sizeof(script_magic));
    if (len != 2 || memcmp(script_magic, "#!", sizeof(script_magic)))
    {
        goto quit;
    }

    /* setup a new args struct to save script arguments */
    if (args_init(&ow_ai, INTERP_BUF_SIZE))
    {
        goto quit;
    }

    while (1)
    {
        /* read file to buffer (avoid any truncated words in buffer) */
        rf_stat = _readfile(fd, INTERP_BUF_SIZE, interp, &len);
        if (len <= 0)
        {
            goto quit;
        }

        /* find first word until reaching nil */
        cp = _find_word(interp);
        if (*cp == '\0')
        {
            if (READFILE_STAT_CAN_READMORE(rf_stat))
                continue;
            else
                break;
        }

        do
        {
            nextword = _seperate_and_get_nextword(cp);
            args_append(&ow_ai, cp, strlen(cp), LWP_ARGS_TYPE_KARG);
            cp = nextword;
        }
        while (*cp);

        if (READFILE_STAT_CAN_READMORE(rf_stat))
            continue;
        else
            break;
    }

    if (ow_ai.argv.string_count == 0)
    {
        goto quit; /* No interpreter name found */
    }

    args_append(&ow_ai, filename, strlen(filename), LWP_ARGS_TYPE_KARG);
    error = _args_override_argv0(ai, &ow_ai);
    if (error)
    {
        goto quit;
    }

quit:
    lwp_args_detach(&ow_ai);
    if (fd >= 0)
    {
        close(fd);
    }
    return error;
}

char **lwp_get_command_line_args(struct rt_lwp *lwp)
{
    size_t argc = 0;
    char **argv = NULL;
    int ret;
    size_t i;
    size_t len;

    if (lwp)
    {
        ret = lwp_data_get(lwp, &argc, lwp->args, sizeof(argc));
        if (ret == 0)
        {
            return RT_NULL;
        }
        argv = (char**)rt_calloc((argc + 1), sizeof(char*));

        if (argv)
        {
            for (i = 0; i < argc; i++)
            {
                char *argvp = NULL;
                ret = lwp_data_get(lwp, &argvp, &((char **)lwp->args)[1 + i], sizeof(argvp));
                if (ret == 0)
                {
                    goto error_exit;
                }

                len = lwp_user_strlen_ext(lwp, argvp);
                if (len >= 0)
                {
                    argv[i] = (char*)rt_malloc(len + 1);
                    ret = lwp_data_get(lwp, argv[i], argvp, len);
                    if (ret != len)
                    {
                        goto error_exit;
                    }
                    argv[i][len] = '\0';
                }
                else
                {
                    goto error_exit;
                }
            }
            argv[argc] = NULL;
        }
    }

    return argv;
error_exit:
    lwp_free_command_line_args(argv);
    return RT_NULL;
}

void lwp_print_envp(struct rt_lwp *lwp)
{
    rt_size_t envp_counts;
    char **kenvp_array = lwp_get_envp(lwp, &envp_counts);
    if (kenvp_array)
    {
        rt_kprintf("envp_counts: %d\n", envp_counts);
        for (size_t i = 0; i < envp_counts; i++)
        {
            rt_kprintf("envp[%d]: %s\n", i, kenvp_array[i]);
        }
    }
    lwp_free_command_line_args(kenvp_array);
    return ;
}

char** lwp_get_envp(struct rt_lwp *lwp, rt_size_t *penvp_counts)
{
    int ret, len;
    rt_base_t argc;
    char **p_kenvp = RT_NULL;
    char *envp, **p_envp;
    size_t envp_counts = 0;

    if (lwp)
    {
        ret = lwp_data_get(lwp, &argc, lwp->args, sizeof(argc));
        if (ret == 0)
        {
            return RT_NULL;
        }
        p_envp = (char **)lwp->args + 1 + argc + 1;

        /* counts envp */
        while (lwp_data_get(lwp, &envp, p_envp, sizeof(void *)) == sizeof(void *)
               && envp != NULL)
        {
            p_envp++;
            envp_counts++;
        }

        p_kenvp = (char **)rt_malloc((envp_counts + 1) * sizeof(char *));
        if (p_kenvp)
        {
            /* copy env from envp array */
            p_envp =  (char **)lwp->args + 1 + argc + 1;
            for (size_t i = 0; i < envp_counts; i++)
            {
                ret = lwp_data_get(lwp, &envp, &p_envp[i], sizeof(char *));
                if (ret != sizeof(char **))
                {
                    lwp_free_command_line_args(p_kenvp);
                    return RT_NULL;
                }

                len = lwp_user_strlen_ext(lwp, envp);
                if (len > 0)
                {
                    p_kenvp[i] = (char*)rt_malloc(len + 1);
                    ret = lwp_data_get(lwp, p_kenvp[i], envp, len + 1);
                    if (ret != len + 1)
                    {
                        lwp_free_command_line_args(p_kenvp);
                        return RT_NULL;
                    }
                }
                else
                {
                    p_kenvp[i] = NULL;
                }
            }
            if (penvp_counts)
                *penvp_counts = envp_counts;
            p_kenvp[envp_counts] = NULL;
        }
    }

    return p_kenvp;
}

void lwp_free_command_line_args(char** argv)
{
    size_t i;

    if (argv)
    {
        for (i = 0; argv[i]; i++)
        {
            rt_free(argv[i]);
        }
        rt_free(argv);
    }
}
