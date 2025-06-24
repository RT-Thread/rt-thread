/*
 * This file is only used for doxygen document generation.
 *
 * Components
 * - Device Virtual File System
 * - Device Driver
 * - Finsh Shell
 * - Application Module
  */

/**
 * @defgroup group_kernel_components Components
 *
 * Components of RT-Thread, see @ref page_components for more details.
 */

/**
 * @addtogroup group_kernel_components
 * @{
 */

/**
 * @defgroup group_device_virtual_file_system Device Virtual File System
 *
 * @brief DFS is a virtual file system in RT-Thread RTOS.
 *
 * The DFS (Device Virtual File System) is a vfs file system of RT-Thread RTOS,
 * which is focused on embedded device. VFS is an abstraction layer on top of a
 * more concrete file system. The purpose of a VFS is to allow client applications
 * to access different types of concrete file systems in a uniform way.
 *
 * @image html dfs.png "Figure 4: Device Virtual File System Architecture"
 *
 * The DFS specifies an interface between the kernel and a concrete file system.
 * Therefore, it is easy to add support for new file system types to the kernel
 * simply by fulfilling the interface.
 */

/**
 * @defgroup group_device_driver Device Driver
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
 * @defgroup group_finsh Finsh Shell
 *
 * @brief finsh shell is a user command shell in RT-Thread RTOS.
 *
 * finsh shell is a user command shell in RT-Thread RTOS, which is a shell can
 * accept C-expression like syntax in command. From finsh shell, user can access
 * system area, such as memory, variables and function by input C-expression in
 * command.
 *
 * @image html finsh.png "Figure 3: finsh shell architecture"
 * There is a shell thread, which named as "tshell", in the finsh shell, it read
 * user command from console device, and then invokes system function or access
 * system variable to output result (by rt_kprintf).
 */

/**
 * @defgroup group_module Application Module
 *
 * @brief Application Module is a feature let user to execute application in RT-Thread RTOS.
 *
 * Application Module is implemented as dynamic object loader, but it can handle
 * the dependences relationship between application and dynamic library, moreover,
 * it also can handle the kernel object destroy and memory release issue when application
 * (abnormally) exit.
 */

/**@}*/