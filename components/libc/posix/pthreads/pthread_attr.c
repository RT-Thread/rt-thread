/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2010-10-26     Bernard      the first version
 */

#include <rtthread.h>
#include "pthread.h"
#include "sched.h"
#include <string.h>

#define DEFAULT_STACK_SIZE  2048
#define DEFAULT_PRIORITY    (RT_THREAD_PRIORITY_MAX/2 + RT_THREAD_PRIORITY_MAX/4)

const pthread_attr_t pthread_default_attr =
{
    0,                          /* stack base */
    DEFAULT_STACK_SIZE,         /* stack size */

    PTHREAD_INHERIT_SCHED,      /* Inherit parent prio/policy */
    SCHED_FIFO,                 /* scheduler policy */
    {
        DEFAULT_PRIORITY,       /* scheduler priority */
    },
    PTHREAD_CREATE_JOINABLE,    /* detach state */
};

/**
 * @brief    This function will initialize  thread attributes object.
 *
 * @note     The pthread_attr_t type should be treated as opaque: any access to the object other
 *           than via pthreads functions is nonportable and produces undefined results.
 *           The resulting attribute object (possibly modified by setting individual attribute values),
 *           when used by pthread_create(), defines the attributes of the thread created. A single attributes
 *           object can be used in multiple simultaneous calls to pthread_create().
 *
 * @see      pthread_create()
 *
 * @param    attr is a thread attributes object.
 *
 * @return   Upon successful completion, pthread_attr_init() return a value of 0.
 *           Otherwise, it means that the event detach failed.
 *
 * @warning  This function will fail if attr is null.
 */
int pthread_attr_init(pthread_attr_t *attr)
{
    RT_ASSERT(attr != RT_NULL);

    *attr = pthread_default_attr;

    return 0;
}
RTM_EXPORT(pthread_attr_init);

/**
 * @brief    This function will destroy thread attributes object.
 *
 * @note     When a thread attributes object is no longer required, it should be destroyed
 *           using the pthread_attr_destroy() function. Destroying a thread attributes object
 *           has no effect on threads that were created using that object.
 *           Once a thread attributes object has been destroyed, it can be reinitialized using pthread_attr_init().
 *           Any other use of a destroyed thread attributes object has undefined results.
 *
 * @see      pthread_attr_init(), pthread_attr_getdetachstate(), pthread_create()
 *
 * @param    attr is a thread attributes object.
 *
 * @return   Upon successful completion, pthread_attr_destroy() and shall return a value of 0;
 *           Otherwise, an error number shall be returned to indicate the error.
 *
 * @warning  This function will fail if attr is null.
 */
int pthread_attr_destroy(pthread_attr_t *attr)
{
    RT_ASSERT(attr != RT_NULL);

    memset(attr, 0, sizeof(pthread_attr_t));

    return 0;
}
RTM_EXPORT(pthread_attr_destroy);

/**
 * @brief    This function set detach state attribute in thread attributes object.
 *
 * @note     This function sets the detach state attribute of the thread attributes object
 *           referred to by attr to the value specified in detachstate.  The detach state
 *           attribute determines whether a thread created using the thread attributes
 *           object attr will be created in a joinable or a detached state.
 *
 * @see      pthread_attr_init(), pthread_create(), pthread_detach(), pthread_join(), pthreads()
 *
 * @param    attr is a thread attributes object.
 *
 * @param    state is attribute in the attr object.
 *           attribute controls whether the thread is created in a detached state.
 *           The detachstate can be ONE of the following values:
 *
 *              PTHREAD_CREATE_DETACHED          It causes all threads created with attr to be in the detached state.
 *
 *              PTHREAD_CREATE_JOINABLE          Default value, it causes all threads created with attr to be in the joinable state.
 *
 * @return   Upon successful completion, pthread_attr_setdetachstate() and return a value of 0.
 *           Otherwise, an error number is returned to indicate the error.
 *
 * @warning  The pthread_attr_setdetachstate() function will fail if:
 *           [EINVAL]
 *              The value of detach state was not valid
 */
int pthread_attr_setdetachstate(pthread_attr_t *attr, int state)
{
    RT_ASSERT(attr != RT_NULL);

    if (state != PTHREAD_CREATE_JOINABLE && state != PTHREAD_CREATE_DETACHED)
        return EINVAL;

    attr->detachstate = state;

    return 0;
}
RTM_EXPORT(pthread_attr_setdetachstate);

/**
 * @brief    This function get detach state attribute in thread attributes object.
 *
 * @note     The detachstate attribute controls whether the thread is created in a detached state.
 *           If the thread is created detached, then use of the ID of the newly created thread by
 *           the pthread_detach() or pthread_join() function is an error.
 *
 * @see      pthread_attr_destroy(), pthread_attr_getstackaddr(), pthread_attr_getstacksize(), pthread_create()
 *
 * @param    attr is a thread attributes object.
 *
 * @param    state is attribute in the attr object.
 *           attribute controls whether the thread is created in a detached state.
 *           The detachstate can be ONE of the following values:
 *
 *              PTHREAD_CREATE_DETACHED          It causes all threads created with attr to be in the detached state.
 *
 *              PTHREAD_CREATE_JOINABLE          Default value, it causes all threads created with attr to be in the joinable state.
 *
 * @return   Upon successful completion, pthread_attr_getdetachstate() and shall return a value of 0;
 *           otherwise, an error number shall be returned to indicate the error.
 *
 *           The pthread_attr_getdetachstate() function stores the value of the detachstate
 *           attribute in detachstate if successful.
 */
int pthread_attr_getdetachstate(pthread_attr_t const *attr, int *state)
{
    RT_ASSERT(attr != RT_NULL);

    *state = (int)attr->detachstate;

    return 0;
}
RTM_EXPORT(pthread_attr_getdetachstate);

/**
 * @brief    This function sets schedpolicy attribute.
 *
 * @note     The function function sets the scheduling policy attribute of the thread
 *           attributes object referred to by attr to the value specified in policy.
 *
 * @see      pthread_attr_init(), pthread_attr_setscope(), pthread_attr_setinheritsched(), pthread_attr_setschedparam(), pthread_create()
 *
 * @param    attr is a thread attributes object.
 *
 * @param    policy is attribute in the attr object.
 *           The policy can be ONE of the following values:
 *
 *              SCHED_FIFO         First in-first out scheduling.
 *
 *              SCHED_RR           Round-robin scheduling.
 *
 *              SCHED_OTHER        Default Linux time-sharing scheduling.
 *
 * @return   On success, these functions return 0.
 */
int pthread_attr_setschedpolicy(pthread_attr_t *attr, int policy)
{
    RT_ASSERT(attr != RT_NULL);

    attr->schedpolicy = policy;

    return 0;
}
RTM_EXPORT(pthread_attr_setschedpolicy);

/**
 * @brief    This function gets schedpolicy attribute.
 *
 * @note     The function gets the schedpolicy attribute in the attr argument.
 *
 * @see      pthread_attr_destroy(), pthread_attr_getscope(), pthread_attr_getinheritsched(), pthread_attr_getschedparam(), pthread_create()
 *
 * @param    attr is a thread attributes object.
 *
 * @param    policy is attribute in the attr object.
 *           The policy can be ONE of the following values:
 *
 *              SCHED_FIFO         First in-first out scheduling.
 *
 *              SCHED_RR           Round-robin scheduling.
 *
 *              SCHED_OTHER        Default Linux time-sharing scheduling.
 *
 * @return   On success, these functions return 0.
 */
int pthread_attr_getschedpolicy(pthread_attr_t const *attr, int *policy)
{
    RT_ASSERT(attr != RT_NULL);

    *policy = (int)attr->schedpolicy;

    return 0;
}
RTM_EXPORT(pthread_attr_getschedpolicy);

/**
 * @brief    This function set the scheduling parameter attributes in the attr argument.

 * @see      pthread_attr_init(), pthread_attr_setscope(), pthread_attr_setinheritsched(), pthread_attr_setschedpolicy()
 *
 * @param    attr is a thread attributes object.
 *
 * @param    param is scheduling parameter attributes in the attr argument.
 *           The contents of the param structure are defined in <pthread.h>.
 *           For the SCHED_FIFO and SCHED_RR policies, the only required member of param is sched_priority.
 *
 * @return   On success, these functions return 0.
 */
int pthread_attr_setschedparam(pthread_attr_t           *attr,
                               struct sched_param const *param)
{
    RT_ASSERT(attr != RT_NULL);
    RT_ASSERT(param != RT_NULL);

    attr->schedparam.sched_priority = param->sched_priority;

    return 0;
}
RTM_EXPORT(pthread_attr_setschedparam);

/**
 * @brief    This function get the scheduling parameter attributes in the attr argument.

 * @see      pthread_attr_init(), pthread_attr_setscope(), pthread_attr_setinheritsched(), pthread_attr_setschedpolicy()
 *
 * @param    attr is a thread attributes object.
 *
 * @param    param is scheduling parameter attributes in the attr argument.
 *           The contents of the param structure are defined in <pthread.h>.
 *           For the SCHED_FIFO and SCHED_RR policies, the only required member of param is sched_priority.
 *
 * @return   On success, these functions return 0.
 */
int pthread_attr_getschedparam(pthread_attr_t const *attr,
                               struct sched_param   *param)
{
    RT_ASSERT(attr != RT_NULL);
    RT_ASSERT(param != RT_NULL);

    param->sched_priority = attr->schedparam.sched_priority;

    return 0;
}
RTM_EXPORT(pthread_attr_getschedparam);

/**
 * @brief    This function set the thread creation stacksize attribute in the attr object.
 *
 * @see      pthread_attr_init(), pthread_attr_setstackaddr(), pthread_attr_setdetachstate()
 *
 * @param    attr is a thread attributes object.
 *
 * @param    stack_size is the minimum stack size (in bytes) allocated for the created threads stack.
 *
 * @return   Upon successful completion, This function return a value of 0.
 */
int pthread_attr_setstacksize(pthread_attr_t *attr, size_t stack_size)
{
    RT_ASSERT(attr != RT_NULL);

    attr->stacksize = stack_size;

    return 0;
}
RTM_EXPORT(pthread_attr_setstacksize);

/**
 * @brief    This function get the thread creation stacksize attribute in the attr object.
 *
 * @see      pthread_attr_init(), pthread_attr_getstackaddr(), pthread_attr_getdetachstate()
 *
 * @param    attr is a thread attributes object.
 *
 * @param    stack_size is the minimum stack size (in bytes) allocated for the created threads stack.
 *
 * @return   Upon successful completion, This function return a value of 0.
 */
int pthread_attr_getstacksize(pthread_attr_t const *attr, size_t *stack_size)
{
    RT_ASSERT(attr != RT_NULL);

    *stack_size = attr->stacksize;

    return 0;
}
RTM_EXPORT(pthread_attr_getstacksize);

/**
 * @brief    This function sets the thread creation stackaddr attribute in the attr object.
 *
 * @see      pthread_attr_init(), pthread_attr_setdetachstate(), pthread_attr_setstacksize()
 *
 * @param    attr is a thread attributes object.
 *
 * @param    The stack_addr attribute specifies the location of storage to be used for the created
 *           thread's stack.
 *
 * @return   Upon successful completion, This function return a value of 0.
 */
int pthread_attr_setstackaddr(pthread_attr_t *attr, void *stack_addr)
{
    RT_ASSERT(attr != RT_NULL);

    return EOPNOTSUPP;
}
RTM_EXPORT(pthread_attr_setstackaddr);

/**
 * @brief    This function gets the thread creation stackaddr attribute in the attr object.
 *
 * @see      pthread_attr_init(), pthread_attr_setdetachstate(), pthread_attr_setstacksize()
 *
 * @param    attr is a thread attributes object.
 *
 * @param    The stack_addr attribute specifies the location of storage to be used for the created
 *           thread's stack.
 *
 * @return   Upon successful completion, This function return a value of 0.
 */
int pthread_attr_getstackaddr(pthread_attr_t const *attr, void **stack_addr)
{
    RT_ASSERT(attr != RT_NULL);

    return EOPNOTSUPP;
}
RTM_EXPORT(pthread_attr_getstackaddr);

/**
 * @brief    This function set the thread creation stack attributes stackaddr and stacksize in the attr object.
 *
 * @note     The stack attributes specify the area of storage to be used for the created thread's stack.
 *           The base (lowest addressable byte) of the storage shall be stack_base, and the size of the storage
 *           shall be stack_size bytes.
 *           All pages within the stack described by stackaddr and stacksize shall be both readable
 *           and writable by the thread.
 *
 * @see      pthread_attr_destroy, pthread_attr_getdetachstate, pthread_attr_getstacksize, pthread_create
 *
 * @param    attr is a thread attributes object.
 *
 * @param    stack_base is the base (lowest addressable byte) of the storage.
 *
 * @param    stack_size is the size of the storage.
 *
 * @return   Upon successful completion, these functions shall return a value of 0;
 *           otherwise, an error number shall be returned to indicate the error.
 *
 * @warning  The behavior is undefined if the value specified by the attr argument to or pthread_attr_setstack()
 *           does not refer to an initialized thread attributes object.
 */
int pthread_attr_setstack(pthread_attr_t *attr,
                          void           *stack_base,
                          size_t          stack_size)
{
    RT_ASSERT(attr != RT_NULL);

    attr->stackaddr = stack_base;
    attr->stacksize = RT_ALIGN_DOWN(stack_size, RT_ALIGN_SIZE);

    return 0;
}
RTM_EXPORT(pthread_attr_setstack);

/**
 * @brief    This function shall get the thread creation stack attributes stackaddr and stacksize in the attr object.
 *
 * @note     The stack attributes specify the area of storage to be used for the created thread's stack.
 *           The base (lowest addressable byte) of the storage shall be stack_base, and the size of the storage
 *           shall be stack_size bytes.
 *           All pages within the stack described by stack_base and stack_size shall be both readable
 *           and writable by the thread.
 *
 * @see      pthread_attr_destroy, pthread_attr_getdetachstate, pthread_attr_getstacksize, pthread_create
 *
 * @param    attr is a thread attributes object.
 *
 * @param    stack_base is the base (lowest addressable byte) of the storage.
 *
 * @param    stack_size is the size of the storage.
 *
 * @return   Upon successful completion, these functions shall return a value of 0;
 *           otherwise, an error number shall be returned to indicate the error.
 *           This function shall store the stack attribute values in stack_base and stack_size if successful.
 */
int pthread_attr_getstack(pthread_attr_t const *attr,
                          void                **stack_base,
                          size_t               *stack_size)
{
    RT_ASSERT(attr != RT_NULL);

    *stack_base = attr->stackaddr;
    *stack_size = attr->stacksize;

    return 0;
}
RTM_EXPORT(pthread_attr_getstack);

/**
 * @brief    This function shall set the guardsize attribute in the attr object.
 *
 * @note     The guardsize attribute controls the size of the guard area for the created thread's stack.
 *           The guardsize attribute provides protection against overflow of the stack pointer.
 *           If a thread's stack is created with guard protection, the implementation allocates extra
 *           memory at the overflow end of the stack as a buffer against stack overflow of the stack pointer.
 *           If an application overflows into this buffer an error shall result (possibly in a SIGSEGV signal
 *           being delivered to the thread).
 *
 * @see      <pthread.h>, <sys/mman.h>
 *
 * @param    attr is a thread attributes object.
 *
 * @param    guard_size is the size of the guard area for the created thread's stack.
 *
 * @return   Upon successful completion, these functions shall return a value of 0;
 *
 * @warning  The guardsize attribute is provided to the application for two reasons:
 *
 *              1. Overflow protection can potentially result in wasted system resources.
 *              An application that creates a large number of threads, and which knows its threads
 *              never overflow their stack, can save system resources by turning off guard areas.
 *
 *              2. When threads allocate large data structures on the stack, large guard areas may be
 *              needed to detect stack overflow.
 *
 *           The default size of the guard area is left implementation-defined since on systems
 *           supporting very large page sizes, the overhead might be substantial if at least one guard
 *           page is required by default.
 */
int pthread_attr_setguardsize(pthread_attr_t *attr, size_t guard_size)
{
    return EOPNOTSUPP;
}

/**
 * @brief    This function get the guardsize attribute in the attr object.
 *           This attribute shall be returned in the guard_size parameter.
 *
 * @note     The guardsize attribute controls the size of the guard area for the created thread's stack.
 *           The guardsize attribute provides protection against overflow of the stack pointer.
 *           If a thread's stack is created with guard protection, the implementation allocates extra
 *           memory at the overflow end of the stack as a buffer against stack overflow of the stack pointer.
 *
 * @see      <pthread.h>, <sys/mman.h>
 *
 * @param    attr is a thread attributes object.
 *
 * @param    guard_size is the size of the guard area for the created thread's stack.
 *
 * @return   Upon successful completion, these functions shall return a value of 0;
 *
 * @warning  The guardsize attribute is provided to the application for two reasons:
 *
 *              1. Overflow protection can potentially result in wasted system resources.
 *              An application that creates a large number of threads, and which knows its threads
 *              never overflow their stack, can save system resources by turning off guard areas.
 *
 *              2. When threads allocate large data structures on the stack, large guard areas may be
 *              needed to detect stack overflow.
 *
 *           The default size of the guard area is left implementation-defined since on systems
 *           supporting very large page sizes, the overhead might be substantial if at least one guard
 *           page is required by default.
 */
int pthread_attr_getguardsize(pthread_attr_t const *attr, size_t *guard_size)
{
    return EOPNOTSUPP;
}
RTM_EXPORT(pthread_attr_getguardsize);

/**
 * @brief    This function sets inherit-scheduler attribute in thread attributes object.
 *
 * @note     The function sets the inherit-scheduler attribute of the thread attributes object
 *           referred to by attr to the value specified in inheritsched.
 *           The inherit-scheduler attribute determines whether a thread created using the thread
 *           attributes object attr will inherit its scheduling attributes from the calling thread
 *           or whether it will take them from attr.
 *
 * @see      pthread_attr_init(), pthread_attr_setschedpolicy(), pthread_attr_setschedparam()
 *
 * @param    attr is a thread attributes object.
 *
 * @param    inheritsched the inheritsched attribute determines how the other scheduling attributes of the created thread are to be set:
 *           The policy can be ONE of the following values:
 *
 *              PTHREAD_INHERIT_SCHED          Specifies that the scheduling policy and associated attributes are
 *                                             to be inherited from the creating thread, and the scheduling attributes
 *                                             in this attr argument are to be ignored.
 *
 *              PTHREAD_EXPLICIT_SCHED         Specifies that the scheduling policy and associated attributes are to be
 *                                             set to the corresponding values from this attribute object.
 *
 * @return   Upon successful completion, these functions shall return a value of 0;
 */
int pthread_attr_setinheritsched(pthread_attr_t *attr, int inheritsched)
{
    RT_ASSERT(attr != RT_NULL);

    attr->inheritsched = inheritsched;

    return 0;
}
RTM_EXPORT(pthread_attr_setinheritsched);

/**
 * @brief    This function get and set the inheritsched attribute in the attr argument.
 *
 * @note     The function sets the inherit-scheduler attribute of the thread attributes object
 *           referred to by attr to the value specified in inheritsched.
 *           The inherit-scheduler attribute determines whether a thread created using the thread
 *           attributes object attr will inherit its scheduling attributes from the calling thread
 *           or whether it will take them from attr.
 *
 * @see      pthread_attr_init(), pthread_attr_getschedpolicy(), pthread_attr_getschedparam()
 *
 * @param    attr is a thread attributes object.
 *
 * @param    inheritsched the inheritsched attribute determines how the other scheduling attributes of the created thread are to be set:
 *           The inheritsched can be ONE of the following values:
 *
 *              PTHREAD_INHERIT_SCHED          Specifies that the scheduling policy and associated attributes are
 *                                             to be inherited from the creating thread, and the scheduling attributes
 *                                             in this attr argument are to be ignored.
 *
 *              PTHREAD_EXPLICIT_SCHED         Specifies that the scheduling policy and associated attributes are to be
 *                                             set to the corresponding values from this attribute object.
 *
 * @return   Upon successful completion, these functions shall return a value of 0;
 */
int pthread_attr_getinheritsched(const pthread_attr_t *attr, int *inheritsched)
{
    RT_ASSERT(attr != RT_NULL);

    *inheritsched = attr->inheritsched;

    return 0;
}
RTM_EXPORT(pthread_attr_getinheritsched);

/**
 * @brief    This function set contentionscope attribute.
 *
 * @note     The function are used to set the contentionscope attribute in the attr object.
 *
 * @param    attr is a thread attributes object.
 *
 * @param    scope is the value of contentionscope attribute.
 *           The scope can be ONE of the following values:
 *
 *              PTHREAD_SCOPE_SYSTEM           signifying system scheduling contention scope.
 *
 *              PTHREAD_SCOPE_PROCESS          signifying process scheduling contention scope.
 *
 * @return   Upon successful completion, these functions shall return a value of 0;
 */
int pthread_attr_setscope(pthread_attr_t *attr, int scope)
{
    if (scope == PTHREAD_SCOPE_SYSTEM)
        return 0;
    if (scope == PTHREAD_SCOPE_PROCESS)
        return EOPNOTSUPP;

    return EINVAL;
}
RTM_EXPORT(pthread_attr_setscope);

/**
 * @brief    This function get contentionscope attribute.
 *
 * @note     The function are used to get the contentionscope attribute in the attr object.
 *
 * @param    attr is a thread attributes object.
 *
 * @param    scope is the value of contentionscope attribute.
 *           The scope can be ONE of the following values:
 *
 *              PTHREAD_SCOPE_SYSTEM           signifying system scheduling contention scope.
 *
 *              PTHREAD_SCOPE_PROCESS          signifying process scheduling contention scope.
 *
 * @return   Upon successful completion, these functions shall return a value of 0;
 */
int pthread_attr_getscope(pthread_attr_t const *attr, int *scope)
{
    return PTHREAD_SCOPE_SYSTEM;
}
RTM_EXPORT(pthread_attr_getscope);
