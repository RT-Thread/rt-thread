/*
 * Copyright (c) 2006-2025 RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include "syscall_internal.h"

#if defined(RT_USING_SAL) && defined(SAL_USING_POSIX)
struct musl_addrinfo
{
    int ai_flags;
    int ai_family;
    int ai_socktype;
    int ai_protocol;
    socklen_t ai_addrlen;

    struct musl_sockaddr *ai_addr;
    char *ai_canonname;

    struct musl_addrinfo *ai_next;
};

/**
 * @brief Resolves network addresses and service names into a list of address structures.
 *
 * This function provides a mechanism for resolving a host name and service name (or port number)
 * into a list of address structures suitable for use with socket-based communication. The function
 * can handle both IPv4 and IPv6 addresses and provides a flexible way to specify different types
 * of address and service resolution options.
 *
 * @param[in] nodename  The host name to be resolved. This can be a DNS name or an IP address in string format.
 *                      If `nodename` is `NULL`, the function will resolve the local host.
 * @param[in] servname  The service name (e.g., "http") or port number to be resolved. If `servname` is `NULL`,
 *                      the function will resolve the port number or address without any service association.
 * @param[in] hints     A pointer to a `struct musl_addrinfo` that provides hints for the address resolution.
 *                      It can be used to specify criteria such as the desired address family (IPv4 or IPv6),
 *                      socket type, protocol, and flags for resolution.
 * @param[out] res      A pointer to a `struct musl_addrinfo` that will be filled with the resolved address
 *                      information. The resulting linked list will contain one or more `struct musl_sockaddr`
 *                      structures, each representing a different address that can be used for communication.
 *
 * @return sysret_t     Returns `0` on success, indicating that the address resolution was successful.
 *                       On failure, returns a negative error code.
 *
 * @note The `res` parameter points to a linked list of resolved address structures. Each node in the list
 *       contains a different resolved address and can be used for socket connection purposes.
 *       It is important to free the memory allocated for the list after it is no longer needed, using `freeaddrinfo()`.
 *
 * @warning The `hints` structure allows you to specify various options for the resolution. However, incorrect
 *          hints may lead to unexpected or incorrect results. For example, if you request IPv6 addresses but
 *          the host only supports IPv4, the function may not return the expected results.
 *
 * @see freeaddrinfo(), sys_socket(), sys_connect(), sys_gethostbyname(), sys_gethostbyaddr()
 */
sysret_t sys_getaddrinfo(const char *nodename,
                         const char *servname,
                         const struct musl_addrinfo *hints,
                         struct musl_addrinfo *res)
{
    int ret = -1;
    struct addrinfo *k_res = NULL;
    char *k_nodename = NULL;
    char *k_servname = NULL;
    struct addrinfo *k_hints = NULL;
#ifdef ARCH_MM_MMU
    int len = 0;
#endif

#ifdef ARCH_MM_MMU
    if (!lwp_user_accessable((void *)res, sizeof(*res)))
    {
        SET_ERRNO(EFAULT);
        goto exit;
    }
#endif
    if (nodename)
    {
#ifdef ARCH_MM_MMU
        len = lwp_user_strlen(nodename);
        if (len <= 0)
        {
            SET_ERRNO(EFAULT);
            goto exit;
        }

        k_nodename = (char *)kmem_get(len + 1);
        if (!k_nodename)
        {
            SET_ERRNO(ENOMEM);
            goto exit;
        }

        if (lwp_get_from_user(k_nodename, (void *)nodename, len + 1) != len + 1)
        {
            SET_ERRNO(EFAULT);
            goto exit;
        }
#else
        k_nodename = rt_strdup(nodename);
        if (!k_nodename)
        {
            SET_ERRNO(ENOMEM);
            goto exit;
        }
#endif
    }
    if (servname)
    {
#ifdef ARCH_MM_MMU
        len = lwp_user_strlen(servname);
        if (len <= 0)
        {
            SET_ERRNO(EFAULT);
            goto exit;
        }

        k_servname = (char *)kmem_get(len + 1);
        if (!k_servname)
        {
            SET_ERRNO(ENOMEM);
            goto exit;
        }

        if (lwp_get_from_user(k_servname, (void *)servname, len + 1) < 0)
        {
            SET_ERRNO(EFAULT);
            goto exit;
        }
#else
        k_servname = rt_strdup(servname);
        if (!k_servname)
        {
            SET_ERRNO(ENOMEM);
            goto exit;
        }
#endif
    }

    if (hints)
    {
#ifdef ARCH_MM_MMU
        if (!lwp_user_accessable((void *)hints, sizeof(*hints)))
        {
            SET_ERRNO(EFAULT);
            goto exit;
        }
#endif
        k_hints = (struct addrinfo *)rt_malloc(sizeof *hints);
        if (!k_hints)
        {
            SET_ERRNO(ENOMEM);
            goto exit;
        }

        rt_memset(k_hints, 0x0, sizeof(struct addrinfo));
        k_hints->ai_flags = hints->ai_flags;
        k_hints->ai_family = hints->ai_family;
        k_hints->ai_socktype = hints->ai_socktype;
        k_hints->ai_protocol = hints->ai_protocol;
        k_hints->ai_addrlen = hints->ai_addrlen;
    }

    ret = sal_getaddrinfo(k_nodename, k_servname, k_hints, &k_res);
    if (ret == 0)
    {
        /* set sockaddr */
        sockaddr_tomusl(k_res->ai_addr, res->ai_addr);
        res->ai_addrlen = k_res->ai_addrlen;

        /* set up addrinfo */
        res->ai_family = k_res->ai_family;
        res->ai_flags = k_res->ai_flags;
        res->ai_next = NULL;

        if (hints != NULL)
        {
            /* copy socktype & protocol from hints if specified */
            res->ai_socktype = hints->ai_socktype;
            res->ai_protocol = hints->ai_protocol;
        }

        sal_freeaddrinfo(k_res);
        k_res = NULL;
    }

exit:
    if (ret < 0)
    {
        ret = GET_ERRNO();
    }
#ifdef ARCH_MM_MMU
    if (k_nodename)
    {
        kmem_put(k_nodename);
    }
#else
    if (k_nodename)
    {
        rt_free(k_nodename);
    }
#endif
#ifdef ARCH_MM_MMU
    if (k_servname)
    {
        kmem_put(k_servname);
    }
#else
    if (k_servname)
    {
        rt_free(k_servname);
    }
#endif
    if (k_hints)
    {
        rt_free(k_hints);
    }

    return ret;
}

#define HOSTENT_BUFSZ 512

/**
 * @brief Resolves a host name to an address, with support for specifying the address family.
 *
 * This function performs a lookup of the specified host name, and resolves it to an address,
 * while allowing the caller to specify the desired address family (e.g., IPv4 or IPv6). It is
 * a reentrant version of `gethostbyname2`, meaning it is safe for use in multi-threaded applications.
 * The results are returned in a user-provided buffer to avoid memory allocation overhead.
 *
 * @param[in] name      The host name to be resolved. This can be a DNS name or an IP address in string format.
 * @param[in] af        The address family to use for the resolution. Common values are:
 *                      - `AF_INET` for IPv4 addresses.
 *                      - `AF_INET6` for IPv6 addresses.
 * @param[out] ret      A pointer to a `struct hostent` where the resolved host information will be stored.
 *                      This includes the host name, alias names, address type, and the address itself.
 * @param[in] buf       A buffer to store additional information required for the `struct hostent` structure.
 *                      This is needed to ensure the reentrant behavior and avoid memory allocation.
 * @param[in] buflen    The size of the buffer provided.
 * @param[out] result   A pointer to a `struct hostent*` that will point to the resolved host entry.
 *                      This will be set to the value of `ret` upon success.
 * @param[out] err      A pointer to an integer where error codes will be stored. If the function fails,
 *                      `err` will contain a non-zero value corresponding to the error.
 *
 * @return sysret_t     Returns `0` on success, indicating the resolution was successful.
 *                       On failure, returns a negative error code that indicates the failure reason.
 *
 * @note This function is reentrant and thread-safe, meaning it does not use static memory or global state.
 *       It relies on the buffers provided by the caller to store the resolved data.
 *
 * @see gethostbyname2(), sys_gethostbyname(), sys_socket(), sys_connect(), sys_getaddrinfo()
 */
sysret_t sys_gethostbyname2_r(const char *name, int af, struct hostent *ret,
                              char *buf, size_t buflen,
                              struct hostent **result, int *err)
{
    int ret_val = -1;
    int sal_ret = -1, sal_err = -1;
    struct hostent sal_he, sal_tmp;
    struct hostent *sal_result = NULL;
    char *sal_buf = NULL;
    char *k_name = NULL;
    int len = 0;

#ifdef ARCH_MM_MMU
    if (!lwp_user_accessable((void *)err, sizeof(*err)))
    {
        SET_ERRNO(EFAULT);
        goto __exit;
    }

    if (!lwp_user_accessable((void *)result, sizeof(*result)) || !lwp_user_accessable((void *)ret, sizeof(*ret)) || !lwp_user_accessable((void *)buf, buflen))
    {
        /* not all arguments given */
        *err = EFAULT;
        SET_ERRNO(EFAULT);
        goto __exit;
    }

    len = lwp_user_strlen(name);
    if (len <= 0)
    {
        *err = EFAULT;
        SET_ERRNO(EFAULT);
        goto __exit;
    }

    k_name = (char *)kmem_get(len + 1);
    if (!k_name)
    {
        SET_ERRNO(ENOMEM);
        goto __exit;
    }

    if (lwp_get_from_user(k_name, (void *)name, len + 1) < 0)
    {
        SET_ERRNO(EFAULT);
        goto __exit;
    }
#else
    k_name = rt_strdup(name);
    if (k_name == NULL)
    {
        SET_ERRNO(ENOMEM);
        goto __exit;
    }
#endif

    *result = ret;
    sal_buf = (char *)malloc(HOSTENT_BUFSZ);
    if (sal_buf == NULL)
    {
        SET_ERRNO(ENOMEM);
        goto __exit;
    }

    /* get host by name in SAL */
    sal_ret = sal_gethostbyname_r(k_name, &sal_he, sal_buf, HOSTENT_BUFSZ, &sal_result, &sal_err);
    if (sal_ret == 0)
    {
        int index = 0, cnt = 0;
        char *ptr = buf;

        /* get counter */
        index = 0;
        while (sal_he.h_addr_list[index] != NULL)
        {
            index++;
        }
        cnt = index + 1;

#ifdef ARCH_MM_MMU
        /* update user space hostent */
        lwp_put_to_user(buf, k_name, buflen - (ptr - buf));
        lwp_memcpy(&sal_tmp, &sal_he, sizeof(sal_he));
        sal_tmp.h_name = ptr;
        ptr += rt_strlen(k_name);

        sal_tmp.h_addr_list = (char **)ptr;
        ptr += cnt * sizeof(char *);

        index = 0;
        while (sal_he.h_addr_list[index] != NULL)
        {
            sal_tmp.h_addr_list[index] = ptr;
            lwp_memcpy(ptr, sal_he.h_addr_list[index], sal_he.h_length);

            ptr += sal_he.h_length;
            index++;
        }
        sal_tmp.h_addr_list[index] = NULL;
        lwp_put_to_user(ret, &sal_tmp, sizeof(sal_tmp));
#else
        /* update user space hostent */
        ret->h_addrtype = sal_he.h_addrtype;
        ret->h_length = sal_he.h_length;

        rt_strncpy(ptr, k_name, buflen - (ptr - buf));
        ret->h_name = ptr;
        ptr += strlen(k_name);

        ret->h_addr_list = (char **)ptr;
        ptr += cnt * sizeof(char *);

        index = 0;
        while (sal_he.h_addr_list[index] != NULL)
        {
            ret->h_addr_list[index] = ptr;
            lwp_memcpy(ptr, sal_he.h_addr_list[index], sal_he.h_length);

            ptr += sal_he.h_length;
            index++;
        }
        ret->h_addr_list[index] = NULL;
#endif
        ret_val = 0;
    }
    else
    {
        SET_ERRNO(EINVAL);
    }

__exit:
    if (ret_val < 0)
    {
        ret_val = GET_ERRNO();
    }

    /* release buffer */
    if (sal_buf)
    {
        free(sal_buf);
    }
#ifdef ARCH_MM_MMU
    if (k_name)
    {
        kmem_put(k_name);
    }
#else
    if (k_name)
    {
        free(k_name);
    }
#endif

    return ret_val;
}
#endif
