/*
 * This file is only used for doxygen document generation.
 */

/**
 * @defgroup Kernel RT-Thread Kernel API
 *
 * The Kernel APIs are the core APIs of RT-Thread, which supports the following
 * features:
 * - Multi-thread management
 * - Synchronization mechanisms
 * - Inter-thread communication
 * - Memory management
 * - Asynchronous timer
 */

/**
 * @addtogroup Kernel
 * @{
 */

/**
 * @defgroup Thread Thread Management
 * @brief the thread management
 *
 * RT-Thread operating system supports multitask systems, which are based on thread
 * scheduling.
 * - The scheduling is a full preemptive priority-based scheduling algorithm.
 * - 8/32/256 priority levels are supported, in which 0 is the highest and 7/31/255 the lowest.
 * The 7/31/255th priority is used for idle thread.
 * - Threads running at same priority level are supported. The shared time-slice
 * round-robin scheduling is used for this case.
 * - The time of scheduler to choose the next highest ready thread is determinant.
 * - There are four status in thread management
 *	-# Initialization
 *	-# Running/Ready
 *	-# Blocked
 *	-# Closed
 * - The number of threads in the system is unlimited, only related with RAM.
 */

/**
 * @defgroup Clock Clock and Timer Management
 * @brief clock and system timer management
 *
 * RT-Thread uses clock tick to implement shared time-slice scheduling.
 *
 * The timing sensitivity of thread is implemented by timers. The timer can be set as
 * one-shot or periodic timeout.
 */

/**
 * @defgroup KernelObject Kernel Object Management
 * @brief kernel object management
 *
 * The Kernel object system can access and manage all of the kernel objects.
 *
 * Kernel objects include most of the facilities in the kernel:
 * - thread
 * - semaphore and mutex
 * - event/fast event, mailbox, messagequeue
 * - memory pool
 * - timer
 * @image html Kernel_Object.png "Figure 2: Kernel Object"
 * @image rtf  Kernel_Object.png "Figure 2: Kernel Object"
 *
 * Kernel objects can be static objects, whose memory is allocated in compiling.
 * It can be dynamic objects as well, whose memory is allocated from system heaps
 * in runtime.
 */

/**
 * @defgroup IPC Inter-Thread Communication
 * @brief inter-thread communication
 *
 * RT-Thread operating system supports the traditional semaphore and mutex.
 * - Mutex objects use inherited priority to prevent priority reversion.
 * - The semaphore release action is safe for interrupt service routine.
 *
 * Moreover, the blocked queue for thread to obtain semaphore or mutex can be sorted
 * by priority or FIFO. There are two flags to indicate this mechanism.
 * - RT_IPC_FLAG_FIFO
 *   when the resource is available, thread pended on this resource at first would get
 *   the resource.
 * - RT_IPC_FLAG_PRIO
 *   when the resource is available, thread pended on this resource who had the most high
 *   priority would get the resource.
 *
 * RT-Thread operating systems supports event/fast event, mail box and message queue.
 * - The event mechanism is used to awake a thread by setting one or more corresponding
 * bit of a binary number when an event ocurs.
 * - The fast event supports event thread queue. Once a one bit event occurs, the corresponding
 * blocked thread can be found out timing accurately, then will be waked up.
 * - In mailbox, the mail length is fixed to 4 byte, which is more effective than message queue.
 * - The send action for communication facilities is also safe for interrupt service routine.
 */

/**
 * @defgroup MM Memory Management
 * @brief memory management for memory pool and heap memory
 *
 * RT-Thread operating system supports two types memory management:
 * - Static memory pool management
 * - Dynamic memory heap management.
 *
 * The time to allocate a memory block from the memory pool is determinant. When
 * the memory pool is empty, the allocated thread can be blocked (or immediately return,
 * or waiting for sometime to return, which are determined by a timeout parameter).
 * When other thread releases memory blocks to this memory pool, the blocked thread is
 * wake up.
 *
 * There are two methods in dynamic memory heap management, one is used for small memory,
 * such as less than 1MB.  Another is a SLAB like memory management, which is suitable
 * for large memory system. All of them has no real-time character.
 */

/**
 * @defgroup Device Device System
 * @brief device I/O subsystem
 *
 * The Device System is designed as simple and minimum layer to help communication between
 * applications and drivers.
 *
 * The Device System provide five interfaces to driver:
 * - open, open a device
 * - close, close a device
 * - read, read some data from a device
 * - write, write some data to a device
 * - control, send some control command to a device
 */

/**
 * @defgroup Hook Runtime Trace and Record
 * @brief the hook function set in runtime
 *
 * In order to trace and record RT-Thread activity in runtime, a hook mechanism
 * is introduced.
 *
 * The hooks are a series of routines, which are invoked in some special checkpoints.
 * The hook routines include:
 * - object hook, invoked at object created, deleted, taken and put etc.
 * - scheduler hook, invoked at thread switch and idle thread loop.
 * - memory hook, invoked when allocate or free memory block.
 * - timer hook, invoked when timer is timeout.
 */

/**
 * @defgroup KernelService Other useful kernel service
 * @brief other useful service in the kernel
 */

/**
 * @defgroup Error Error Code
 * @brief error code
 *
 * The error code is defined to identify which kind of error occurs. When some
 * bad things happen, the current thread's errno will be set. see @ref _rt_errno
 */

/**@}*/
