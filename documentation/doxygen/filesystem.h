/*
 * This file is only used for doxygen document generation.
 */

/**
 * @defgroup DFS Device Virtual File System
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
 * @addtogroup DFS
 */
/*@{*/

/**
 * @defgroup Fd File Descriptor
 *
 */

/**
 * @defgroup FsApi File System API
 */

/**
 * @defgroup FileApi File API
 */

/**
 * @defgroup FsPosixApi File POSIX API
 */

/*@}*/
