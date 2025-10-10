/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 * Copyright (c) 2006-2025 RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
@@ -60,6 +60,18 @@
extern char working_directory[];
#endif

/**
 * @brief Initializes the LWP (Light-Weight Process) component
 *
 * @return int Returns RT_EOK if all initializations succeed, otherwise returns
 *         the error code from the first failed initialization
 *
 * @note This function performs initialization of various LWP subsystems in sequence:
 *       1. Thread ID (TID) initialization
 *       2. Process ID (PID) initialization
 *       3. Channel component initialization
 *       4. Futex (Fast Userspace Mutex) initialization
 */
static int lwp_component_init(void)
{
    int rc;
@@ -83,6 +95,15 @@ static int lwp_component_init(void)
}
INIT_COMPONENT_EXPORT(lwp_component_init);

/**
 * @brief Sets the current working directory for the calling LWP or system
 *
 * @param[in] buf Pointer to the path string to set as working directory
 *
 * @note This function handles both LWP-specific and system-wide working directories:
 * - For LWPs, sets the working_directory in the LWP structure
 * - For non-LWP threads, sets the global working_directory variable
 */
void lwp_setcwd(char *buf)
{
    struct rt_lwp *lwp = RT_NULL;
@@ -106,6 +127,15 @@ void lwp_setcwd(char *buf)
    return ;
}

/**
 * @brief Get the current working directory for the light-weight process
 *
 * @return char* Pointer to the current working directory string
 *
 * @note The function returns either:
 *          - LWP's working directory (if valid and absolute path)
 *          - System default working directory (if no LWP or invalid path)
 */
char *lwp_getcwd(void)
{
    char *dir_buf = RT_NULL;
@@ -135,13 +165,28 @@ char *lwp_getcwd(void)
}

/**
 * RT-Thread light-weight process
 * @brief Set the kernel stack pointer for the current thread
 *
 * @param[in] sp Pointer to the new kernel stack location
 *
 * @note It's typically used during context switching or thread initialization.
 */
void lwp_set_kernel_sp(uint32_t *sp)
{
    rt_thread_self()->kernel_sp = (rt_uint32_t *)sp;
}

/**
 * @brief Get the kernel stack pointer for the current thread
 *
 * @return uint32_t* Pointer to the kernel stack
 *
 * @note Architecture-specific behavior:
 * 1. With MMU: Simply returns the current thread's stack pointer
 * 2. Without MMU: Checks interrupt context and returns either:
 *    - Interrupted thread's kernel_sp (if in interrupt)
 *    - Current thread's kernel_sp (if not in interrupt)
 */
uint32_t *lwp_get_kernel_sp(void)
{
#ifdef ARCH_MM_MMU
@@ -162,8 +207,15 @@ uint32_t *lwp_get_kernel_sp(void)
#endif
}


/* lwp-thread clean up routine */
/**
 * @brief Clean up resources associated with a light-weight process thread
 *
 * @param[in] tid Pointer to the thread control block to be cleaned up
 *
 * @note This function performs cleanup operations for a thread associated with a light-weight process (LWP).
 *       It handles signal detachment and reference count decrement for the LWP structure.
 *
 */
void lwp_cleanup(struct rt_thread *tid)
{
    struct rt_lwp *lwp;
@@ -191,6 +243,15 @@ void lwp_cleanup(struct rt_thread *tid)
    return;
}

/**
 * @brief Set up standard I/O for a light-weight process
 *
 * @param[in] lwp Pointer to the light-weight process structure
 *
 * @note This function initializes the standard input, output, and error streams
 *       for a light-weight process by opening the console device and associating
 *       it with file descriptors 0, 1, and 2.
 */
static void lwp_execve_setup_stdio(struct rt_lwp *lwp)
{
    struct dfs_fdtable *lwp_fdt;
@@ -223,6 +284,14 @@ static void lwp_execve_setup_stdio(struct rt_lwp *lwp)
    return;
}

/**
 * @brief Entry point for light-weight process threads
 *
 * @param[in] parameter Thread parameter (unused)
 *
 * @note This function is the main entry point for threads created within a light-weight process.
 *       It handles thread initialization, debug mode setup, and transitions to user mode.
 */
static void _lwp_thread_entry(void *parameter)
{
    rt_thread_t tid;
@@ -262,6 +331,15 @@ static void _lwp_thread_entry(void *parameter)
#endif /* ARCH_MM_MMU */
}

/**
 * @brief Get the current light-weight process
 *
 * @return Pointer to the current light-weight process structure
 *         RT_NULL if no process is associated with current thread
 *
 * @note This function retrieves the light-weight process associated with the
 *       currently running thread.
 */
struct rt_lwp *lwp_self(void)
{
    rt_thread_t tid;
@@ -275,6 +353,17 @@ struct rt_lwp *lwp_self(void)
    return RT_NULL;
}

/**
 * @brief Register a child process with its parent
 *
 * @param[in] parent Pointer to the parent process structure
 * @param[in] child  Pointer to the child process structure to register
 *
 * @return RT_EOK on success
 *
 * @note This function adds a child process to its parent's children list and
 *       increases reference counts for both processes.
 */
rt_err_t lwp_children_register(struct rt_lwp *parent, struct rt_lwp *child)
{
    /* lwp add to children link */
@@ -293,6 +382,17 @@ rt_err_t lwp_children_register(struct rt_lwp *parent, struct rt_lwp *child)
    return 0;
}

/**
 * @brief Unregister a child process from its parent
 *
 * @param[in] parent Pointer to the parent process structure
 * @param[in] child  Pointer to the child process structure to unregister
 *
 * @return RT_EOK on success
 *
 * @note This function removes a child process from its parent's children list and
 *       decreases reference counts for both processes.
 */
rt_err_t lwp_children_unregister(struct rt_lwp *parent, struct rt_lwp *child)
{
    struct rt_lwp **lwp_node;
@@ -316,6 +416,23 @@ rt_err_t lwp_children_unregister(struct rt_lwp *parent, struct rt_lwp *child)
    return 0;
}

/**
 * @brief Copy process arguments and environment variables from kernel space to user space.
 *
 * @param[in] lwp  Pointer to the light-weight process structure
 * @param[in] argc Argument count
 * @param[in] argv Argument vector
 * @param[in] envp Environment variables
 *
 * @return Pointer to the process auxiliary structure on success
 *         RT_NULL if memory allocation fails or arguments initialization fails
 *
 * @note This function performs the following operations:
 *       1. Initializes argument information structure
 *       2. Copies command line arguments to user space
 *       3. Copies environment variables to user space
 *       4. Returns the auxiliary structure containing copied data
 */
struct process_aux *argscopy(struct rt_lwp *lwp, int argc, char **argv, char **envp)
{
    struct lwp_args_info ai;
@@ -344,6 +461,30 @@ struct process_aux *argscopy(struct rt_lwp *lwp, int argc, char **argv, char **e
    return ua;
}

/**
 * @brief Creates and starts a new LWP by loading and executing the specified executable file.
 *
 * @param[in] filename Path to the executable file
 * @param[in] debug     Debug flag (non-zero to enable debugging)
 * @param[in] argc      Argument count
 * @param[in] argv      Argument vector
 * @param[in] envp      Environment variables
 *
 * @return Process ID (PID) of the new LWP on success
 *         -EINVAL if filename is NULL
 *         -EACCES if file is not executable
 *         -ENOMEM if memory allocation fails
 *         -RT_ERROR on other failures
 *
 * @note This function performs the following operations:
 *       1. Validates input parameters
 *       2. Creates new LWP structure
 *       3. Initializes user space (for MMU systems)
 *       4. Copies arguments and environment
 *       5. Loads the executable
 *       6. Sets up standard I/O
 *       7. Creates and starts the main thread
 */
pid_t lwp_execve(char *filename, int debug, int argc, char **argv, char **envp)
{
    int result;
@@ -499,13 +640,38 @@ extern char **__environ;
char **__environ = 0;
#endif

/**
 * @brief Execute a new program in the current process context
 *
 * @param[in] filename Path to the executable file
 * @param[in] debug Debug flag (non-zero enables debug mode)
 * @param[in] argc Number of command line arguments
 * @param[in] argv Array of command line argument strings
 *
 * @return Process ID (PID) of the new process on success
 *         Negative error code on failure
 *
 * @note This is a wrapper function for lwp_execve.
 *
 * @see lwp_execve()
 */
pid_t exec(char *filename, int debug, int argc, char **argv)
{
    setenv("OS", "RT-Thread", 1);
    return lwp_execve(filename, debug, argc, argv, __environ);
}

#ifdef ARCH_MM_MMU
/**
 * @brief Saves thread-specific user settings (TID register)
 *
 * @param[in,out] thread Pointer to the thread control block
 *
 * @note This function stores the architecture-specific TID register
 *       into the specified thread's control block.This is typically used
 *       when switching between threads to preserve thread-specific settings
 */

void lwp_user_setting_save(rt_thread_t thread)
{
    if (thread)
@@ -514,6 +680,14 @@ void lwp_user_setting_save(rt_thread_t thread)
    }
}

/**
 * @brief Restores thread-specific user settings (TID register and debug state)
 *
 * @param[in] thread Pointer to the thread control block
 *
 * @note This function restores architecture-specific Thread ID Register (TIDR) value
 *       and debug-related settings for the specified thread.
 */
void lwp_user_setting_restore(rt_thread_t thread)
{
    if (!thread)
@@ -556,20 +730,46 @@ void lwp_user_setting_restore(rt_thread_t thread)
}
#endif /* ARCH_MM_MMU */

/**
 * @brief Saves user thread context pointer
 *
 * @param[in] ctx Pointer to user thread context structure to be saved
 *
 * @note This function stores a pointer to user thread context in the current thread's
 *       control block for later restoration. The context pointer is typically used
 *       during thread context switching.
 */
void lwp_uthread_ctx_save(void *ctx)
{
    rt_thread_t thread;
    thread = rt_thread_self();
    thread->user_ctx.ctx = ctx;
}

/**
 * @brief Restores the user thread context by clearing the context pointer
 *
 * @note Typically called during thread context switching to clean up any
 *       previously saved user context.
 */
void lwp_uthread_ctx_restore(void)
{
    rt_thread_t thread;
    thread = rt_thread_self();
    thread->user_ctx.ctx = RT_NULL;
}

/**
 * @brief Prints a backtrace of the current thread's call stack
 *
 * @param[in] uthread The thread to backtrace (must be associated with an LWP)
 * @param[in] frame Pointer to the initial stack frame
 *
 * @return RT_EOK on success, -RT_ERROR on failure
 *
 * @note This function prints a backtrace of the call stack for the specified user thread,
 *       providing addresses that can be used with addr2line to get file and line information.
 */
rt_err_t lwp_backtrace_frame(rt_thread_t uthread, struct rt_hw_backtrace_frame *frame)
{
    rt_err_t rc = -RT_ERROR;
   212 changes: 122 additions & 90 deletions212  
components/lwp/lwp.h
Viewed
Original file line number	Diff line number	Diff line change
@@ -1,5 +1,5 @@
/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 * Copyright (c) 2006-2025 RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
@@ -63,17 +63,28 @@ extern "C" {

#define LWP_ARG_MAX         8

/**
 * @brief Light-weight process memory objects structure
 */
struct rt_lwp_objs
{
    rt_aspace_t source;
    struct rt_mem_obj mem_obj;
    rt_aspace_t source;                  /**< The address space associated with this LWP */
    struct rt_mem_obj mem_obj;           /**< The memory object containing memory management information */
};

/**
 * @brief Light-weight process notification structure
 */
struct rt_lwp_notify
{
    /**
     * @brief Callback function pointer for signal notification
     * @param signalfd_queue Wait queue for signal file descriptors
     * @param signo Signal number
     */
    void (*notify)(rt_wqueue_t *signalfd_queue, int signo);
    rt_wqueue_t *signalfd_queue;
    rt_slist_t list_node;
    rt_wqueue_t *signalfd_queue;         /**< Wait queue for signal file descriptors */
    rt_slist_t list_node;                /**< List node for notification */
};

struct lwp_tty;
@@ -92,114 +103,123 @@ typedef struct rt_lwp *rt_lwp_t;
typedef struct rt_session *rt_session_t;
typedef struct rt_processgroup *rt_processgroup_t;

/**
 * @brief Session control structure for process groups
 */
struct rt_session {
    struct rt_object    object;
    rt_lwp_t            leader;
    rt_list_t           processgroup;
    pid_t               sid;
    pid_t               foreground_pgid;
    struct rt_mutex     mutex;
    struct lwp_tty      *ctty;
    rt_lwp_t            leader;          /**< Session leader process */
    rt_list_t           processgroup;    /**< List head of process groups in this session */
    pid_t               sid;             /**< Session ID */
    pid_t               foreground_pgid; /**< Foreground process group ID */
    struct rt_mutex     mutex;           /**< Mutex for session operations synchronization */
    struct lwp_tty      *ctty;           /**< Control terminal */
};

/**
 * @brief Process group control structure
 */
struct rt_processgroup {
    struct rt_object    object;
    rt_lwp_t            leader;
    rt_list_t           process;
    rt_list_t           pgrp_list_node;
    pid_t               pgid;
    pid_t               sid;
    struct rt_session   *session;
    struct rt_mutex     mutex;
    rt_lwp_t            leader;         /**< Process group leader process */
    rt_list_t           process;        /**< List head of processes in this process group */
    rt_list_t           pgrp_list_node; /**< List node for process group */
    pid_t               pgid;           /**< Process group ID */
    pid_t               sid;            /**< Session ID */
    struct rt_session   *session;       /**< Session pointer */
    struct rt_mutex     mutex;          /**< Mutex for process group operations synchronization */

    rt_atomic_t         ref;
    rt_atomic_t         ref;            /**< Reference count for process group */

    /* flags on process group */
    unsigned int is_orphaned:1;
    unsigned int is_orphaned:1;         /**< Whether the process group is orphaned */
};

/**
 * @brief Light-weight process structure
 */
struct rt_lwp
{
#ifdef ARCH_MM_MMU
    size_t end_heap;
    rt_aspace_t aspace;
    size_t end_heap;                            /**< End address of heap */
    rt_aspace_t aspace;                         /**< Address space associated with this LWP */
#else
#ifdef ARCH_MM_MPU
    struct rt_mpu_info mpu_info;
    struct rt_mpu_info mpu_info;                /**< MPU information for this LWP */
#endif /* ARCH_MM_MPU */
#endif /* ARCH_MM_MMU */

#ifdef RT_USING_SMP
    int bind_cpu;
    int bind_cpu;                               /**< CPU ID to which the LWP is bound */
#endif

    uint8_t lwp_type;
    uint8_t lwp_type;                           /**< Type of LWP */
    uint8_t reserv[3];

    /* flags */
    unsigned int terminated:1;
    unsigned int background:1;
    unsigned int term_ctrlterm:1;  /* have control terminal? */
    unsigned int did_exec:1;       /* Whether exec has been performed */
    unsigned int jobctl_stopped:1; /* job control: current proc is stopped */
    unsigned int wait_reap_stp:1;  /* job control: has wait event for parent */
    unsigned int sig_protected:1;  /* signal: protected proc cannot be killed or stopped */

    struct rt_lwp *parent;          /* parent process */
    struct rt_lwp *first_child;     /* first child process */
    struct rt_lwp *sibling;         /* sibling(child) process */

    struct rt_wqueue waitpid_waiters;
    lwp_status_t lwp_status;

    void *text_entry;
    uint32_t text_size;
    void *data_entry;
    uint32_t data_size;

    rt_atomic_t ref;
    void *args;
    uint32_t args_length;
    pid_t pid;
    pid_t sid;                      /* session ID */
    pid_t pgid;                     /* process group ID */
    struct rt_processgroup *pgrp;
    rt_list_t pgrp_node;            /* process group node */
    rt_list_t t_grp;                /* thread group */
    rt_list_t timer;                /* POSIX timer object binding to a process */

    struct dfs_fdtable fdt;
    char cmd[RT_NAME_MAX];
    char *exe_file;                 /* process file path */
    unsigned int terminated:1;                  /**< Process termination flag */
    unsigned int background:1;                  /**< Background process flag */
    unsigned int term_ctrlterm:1;               /**< have control terminal? */
    unsigned int did_exec:1;                    /**< Whether exec has been performed */
    unsigned int jobctl_stopped:1;              /**< job control: current proc is stopped */
    unsigned int wait_reap_stp:1;               /**< job control: has wait event for parent */
    unsigned int sig_protected:1;               /**< signal: protected proc cannot be killed or stopped */

    struct rt_lwp *parent;                      /**< parent process */
    struct rt_lwp *first_child;                 /**< first child process */
    struct rt_lwp *sibling;                     /**< sibling(child) process */

    struct rt_wqueue waitpid_waiters;           /**< Wait queue for waitpid system call */
    lwp_status_t lwp_status;                    /**< Status of LWP */

    void *text_entry;                           /**< Entry point of text segment */
    uint32_t text_size;                         /**< Size of text segment */
    void *data_entry;                           /**< Entry point of data segment */
    uint32_t data_size;                         /**< Size of data segment */

    rt_atomic_t ref;                            /**< Reference count for LWP */
    void *args;                                 /**< Arguments passed to LWP */
    uint32_t args_length;                       /**< Length of arguments */
    pid_t pid;                                  /**< Process ID */
    pid_t sid;                                  /**< session ID */
    pid_t pgid;                                 /**< process group ID */
    struct rt_processgroup *pgrp;               /**< process group */
    rt_list_t pgrp_node;                        /**< process group node */
    rt_list_t t_grp;                            /**< thread group */
    rt_list_t timer;                            /**< POSIX timer object binding to a process */

    struct dfs_fdtable fdt;                     /**< File descriptor table */
    char cmd[RT_NAME_MAX];                      /**< process name */
    char *exe_file;                             /**< process file path */

    /* POSIX signal */
    struct lwp_signal signal;
    struct lwp_signal signal;                   /**< Signal handling structure */

    struct lwp_avl_struct *object_root;
    struct rt_mutex object_mutex;
    struct rt_user_context user_ctx;
    struct lwp_avl_struct *object_root;         /**< AVL tree root for objects */
    struct rt_mutex object_mutex;               /**< Mutex for object operations synchronization */
    struct rt_user_context user_ctx;            /**< User context for LWP */

    struct rt_wqueue wait_queue; /* for console */
    struct tty_struct *tty; /* NULL if no tty */
    struct rt_wqueue wait_queue;                /**< wait queue for console */
    struct tty_struct *tty;                     /**< Controlling terminal, NULL if no tty */

    struct lwp_avl_struct *address_search_head; /* for addressed object fast search */
    char working_directory[DFS_PATH_MAX];
    struct lwp_avl_struct *address_search_head; /**< for saving private futexes with a user-space address key */
    char working_directory[DFS_PATH_MAX];       /**< Current working directory */

    int debug;
    rt_uint32_t bak_first_inst; /* backup of first instruction */
    int debug;                                  /**< Debug flag */
    rt_uint32_t bak_first_inst;                 /**< backup of first instruction */

    struct rt_mutex lwp_lock;
    struct rt_mutex lwp_lock;                   /**< Mutex for LWP operations synchronization */

    rt_slist_t signalfd_notify_head;
    rt_slist_t signalfd_notify_head;            /**< Signal file descriptor notification head */

#ifdef LWP_ENABLE_ASID
    uint64_t generation;
    unsigned int asid;
    uint64_t generation;                        /**< ASID generation */
    unsigned int asid;                          /**< Address space ID */
#endif
    struct rusage rt_rusage;
    struct rusage rt_rusage;                    /**< Resource usage information */

#ifdef RT_USING_VDSO
    void *vdso_vbase;
    void *vdso_vbase;                           /**< VDSO base address */
#endif
};

@@ -208,11 +228,14 @@ struct rt_lwp *lwp_self(void);
rt_err_t lwp_children_register(struct rt_lwp *parent, struct rt_lwp *child);
rt_err_t lwp_children_unregister(struct rt_lwp *parent, struct rt_lwp *child);

/**
 * @brief LWP exit request type
 */
enum lwp_exit_request_type
{
    LWP_EXIT_REQUEST_NONE = 0,
    LWP_EXIT_REQUEST_TRIGGERED,
    LWP_EXIT_REQUEST_IN_PROCESS,
    LWP_EXIT_REQUEST_NONE = 0,                  /**< No exit request */
    LWP_EXIT_REQUEST_TRIGGERED,                 /**< Exit request triggered */
    LWP_EXIT_REQUEST_IN_PROCESS,                /**< Exit request in process */
};
struct termios *get_old_termios(void);
void lwp_setcwd(char *buf);
@@ -381,28 +404,37 @@ sysret_t lwp_teardown(struct rt_lwp *lwp, void (*cb)(void));
#define AT_EXECFN 31
#define AT_SYSINFO_EHDR 33

/**
 * @brief Process auxiliary vector item
 */
struct process_aux_item
{
    size_t key;
    size_t value;
    size_t key;                            /**< Auxiliary vector key */
    size_t value;                          /**< Auxiliary vector value */
};

/**
 * @brief Process auxiliary vector
 */
struct process_aux
{
    struct process_aux_item item[AUX_ARRAY_ITEMS_NR];
    struct process_aux_item item[AUX_ARRAY_ITEMS_NR]; /**< Auxiliary vector items */
};

/**
 * @brief Debug operations structure
 */
struct dbg_ops_t
{
    int (*dbg)(int argc, char **argv);
    uint32_t (*arch_get_ins)(void);
    void (*arch_activate_step)(void);
    void (*arch_deactivate_step)(void);
    int (*check_debug_event)(struct rt_hw_exp_stack *regs, unsigned long esr);
    rt_channel_t (*gdb_get_server_channel)(void);
    int (*gdb_get_step_type)(void);
    void (*lwp_check_debug_attach_req)(void *pc);
    int (*lwp_check_debug_suspend)(void);
    int (*dbg)(int argc, char **argv);                                         /**< Debug function */
    uint32_t (*arch_get_ins)(void);                                            /**< Architecture-specific instruction getter */
    void (*arch_activate_step)(void);                                          /**< Architecture-specific step activation */
    void (*arch_deactivate_step)(void);                                        /**< Architecture-specific step deactivation */
    int (*check_debug_event)(struct rt_hw_exp_stack *regs, unsigned long esr); /**< Debug event checker */
    rt_channel_t (*gdb_get_server_channel)(void);                              /**< GDB server channel getter */
    int (*gdb_get_step_type)(void);                                            /**< GDB step type getter */
    void (*lwp_check_debug_attach_req)(void *pc);                              /**< LWP debug attach request checker */
    int (*lwp_check_debug_suspend)(void);                                      /**< LWP debug suspend checker */
};
extern struct dbg_ops_t *rt_dbg_op
