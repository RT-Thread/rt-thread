/*
 * Copyright (c) 2006-2025 RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include "syscall_internal.h"

/* device interfaces */

/**
 * @brief Initializes a device.
 *
 * This system call initializes the specified device, preparing it for use. Device initialization
 * typically involves setting up necessary hardware configurations, registering device drivers,
 * and ensuring that the device is in a ready state for further operations. This function should
 * be called before interacting with the device.
 *
 * @param[in] dev  A pointer to the device structure that represents the device to be initialized.
 *                 This structure contains device-specific configuration and state information.
 *
 * @return sysret_t  Returns a status code:
 *                   - `0`: The device was successfully initialized.
 *                   - Other error codes may indicate issues with the device initialization process.
 *
 * @note This function is typically called once during system startup or when a device is
 *       first accessed. It ensures that all necessary setup steps are completed before
 *       the device can be used.
 *
 * @warning Ensure that the device passed to this function is valid and properly configured
 *          before initialization. Initializing an invalid or improperly configured device
 *          may result in unpredictable behavior.
 */
sysret_t sys_device_init(rt_device_t dev)
{
    return rt_device_init(dev);
}

/**
 * @brief Registers a device with the system.
 *
 * This system call registers a device with the system, making it available for interaction
 * by the operating system or other components. Registration typically involves associating
 * the device with a name and setting up the necessary flags for the device's behavior.
 *
 * @param[in] dev     A pointer to the device structure that represents the device to be registered.
 *                    This structure contains the device's configuration, capabilities, and state.
 * @param[in] name    A string representing the name by which the device will be identified in the system.
 *                    This name is used for device lookup and reference.
 * @param[in] flags   A set of flags that configure the behavior of the device, such as enabling
 *                    or disabling certain features, or specifying the device's mode of operation.
 *
 * @return sysret_t   Returns a status code:
 *                    - `0`: The device was successfully registered.
 *                    - Other error codes may indicate issues with the device registration process.
 *
 * @note This function should be called after the device has been initialized (via `sys_device_init`)
 *       and before the device is used by the system or other components.
 *
 * @warning Ensure that the `name` provided is unique and not already in use by another device in the system.
 *          Passing invalid `dev` or `flags` may result in unexpected behavior or failure of device registration.
 */
sysret_t sys_device_register(rt_device_t dev, const char *name, rt_uint16_t flags)
{
    return rt_device_register(dev, name, flags);
}

/**
 * @brief Controls a device by sending a command.
 *
 * This system call sends a control command to the specified device, allowing the system or other
 * components to modify the device's behavior or state. The command is specified by the `cmd`
 * parameter, and the arguments for the command are passed via the `arg` parameter.
 *
 * @param[in] dev   A pointer to the device structure representing the device to be controlled.
 *                  The device must have been previously registered and initialized.
 * @param[in] cmd   The control command to be sent to the device. The meaning and behavior of the
 *                  command are device-specific and depend on the device type.
 * @param[in] arg   A pointer to the arguments required by the command. The type and content of
 *                  the arguments are determined by the command. Some commands may not require
 *                  arguments, in which case `arg` can be `NULL`.
 *
 * @return sysret_t Returns a status code:
 *                   - `0`: The command was successfully executed on the device.
 *                   - Other error codes may indicate issues with the command execution or device control.
 *
 * @note The set of available commands (`cmd`) and the expected argument types (`arg`) are specific
 *       to each device. Refer to the device documentation for the supported commands and argument
 *       formats.
 *
 * @warning Ensure that the `dev` pointer is valid and points to a correctly initialized device.
 *          Providing an invalid device or incorrect command may result in undefined behavior.
 */
sysret_t sys_device_control(rt_device_t dev, int cmd, void *arg)
{
    return rt_device_control(dev, cmd, arg);
}

/**
 * @brief Finds a device by its name.
 *
 * This system call searches for a device that has been registered with the system using the
 * specified name. If the device exists, a pointer to the device structure is returned,
 * allowing further interaction with the device. If no device with the specified name is found,
 * a `NULL` pointer is returned.
 *
 * @param[in] name  The name of the device to search for. This name must match the name used
 *                  during device registration (e.g., via `sys_device_register`).
 *
 * @return rt_device_t  Returns a pointer to the device structure if the device is found.
 *                      Returns `NULL` if no device with the specified name exists.
 *
 * @note The device must have been previously registered with the system using `sys_device_register`.
 *
 * @warning Ensure that the provided `name` is a valid string and corresponds to a registered device.
 *          Passing an invalid or non-registered name will result in `NULL` being returned.
 */
rt_device_t sys_device_find(const char *name)
{
    return rt_device_find(name);
}

/**
 * @brief Opens a device for use.
 *
 * This system call opens the specified device, making it ready for interaction with the system
 * or other components. The device must have been previously registered and initialized.
 * The `oflag` parameter specifies the open mode, which may determine how the device is accessed
 * (e.g., read, write, or exclusive access).
 *
 * @param[in] dev    A pointer to the device structure representing the device to be opened.
 *                   The device must be registered and initialized before being opened.
 * @param[in] oflag  The open flags that determine the mode of access to the device. These flags
 *                   may specify read, write, or other modes of operation, depending on the device's capabilities.
 *
 * @return sysret_t  Returns a status code:
 *                    - `0`: The device was successfully opened.
 *                    - Other error codes may indicate issues with the device opening process.
 *
 * @note The open flags (`oflag`) should be set according to the device's capabilities. For example,
 *       some devices may support read or write operations, while others may only support one of them.
 *       Check the device documentation for supported flags.
 *
 * @warning Ensure that the device pointer (`dev`) is valid and that the device has been initialized
 *          properly. Incorrect flags or attempting to open a device that is already in use may result
 *          in errors or undefined behavior.
 */
sysret_t sys_device_open(rt_device_t dev, rt_uint16_t oflag)
{
    return rt_device_open(dev, oflag);
}

/**
 * @brief Closes an open device.
 *
 * This system call closes an open device, releasing any resources or locks associated with it
 * and making it unavailable for further interaction until it is opened again. The device must
 * have been previously opened using `sys_device_open`. After calling this function, any further
 * attempts to interact with the device will result in an error unless the device is opened again.
 *
 * @param[in] dev  A pointer to the device structure representing the device to be closed.
 *                 The device must be open before it can be closed.
 *
 * @return sysret_t  Returns a status code:
 *                    - `0`: The device was successfully closed.
 *                    - Other error codes may indicate issues with the device closing process.
 *
 * @note This function should be called when the device is no longer needed or before shutting
 *       down the system to release device resources properly.
 *
 * @warning Ensure that the device has been opened before calling this function. Calling this function
 *          on an uninitialized or already closed device may result in undefined behavior or errors.
 */
sysret_t sys_device_close(rt_device_t dev)
{
    return rt_device_close(dev);
}

/**
 * @brief Reads data from an open device.
 *
 * This system call reads data from the specified device, starting at the given position and
 * storing the data in the provided buffer. The device must be open before this function can be called.
 * The amount of data to read is determined by the `size` parameter.
 *
 * @param[in]  dev     A pointer to the device structure representing the device to read from.
 *                     The device must be open and ready for reading.
 * @param[in]  pos     The position within the device from which to begin reading. For devices that
 *                     support seeking, this value is used to specify the starting point.
 * @param[out] buffer  A pointer to the buffer where the read data will be stored. This buffer should
 *                     be large enough to hold the specified amount of data.
 * @param[in]  size    The number of bytes to read from the device. This value determines how much
 *                     data is read into the buffer.
 *
 * @return rt_ssize_t  Returns the number of bytes actually read from the device:
 *                      - On success: The number of bytes read, which may be less than `size` if
 *                        the end of the device is reached or other factors limit the read.
 *                      - On failure: A negative error code.
 *
 * @note The device must be open and in a readable state before calling this function.
 *       The `pos` parameter allows seeking within the device if it supports such operations.
 *
 * @warning Ensure that the buffer provided is large enough to hold the data being read.
 *          Providing an insufficient buffer may result in undefined behavior.
 */
rt_ssize_t sys_device_read(rt_device_t dev, rt_off_t pos, void *buffer, rt_size_t size)
{
    return rt_device_read(dev, pos, buffer, size);
}

/**
 * @brief Writes data to an open device.
 *
 * This system call writes data to the specified device, starting at the given position and using
 * the provided buffer. The device must be open and ready for writing. The amount of data to write
 * is determined by the `size` parameter.
 *
 * @param[in]  dev     A pointer to the device structure representing the device to write to.
 *                     The device must be open and ready for writing.
 * @param[in]  pos     The position within the device where the writing should start. For devices
 *                     that support seeking, this value specifies the location to begin writing.
 * @param[in]  buffer  A pointer to the buffer containing the data to be written to the device.
 *                     This buffer should contain the data to be written and should be large enough
 *                     to accommodate the specified size.
 * @param[in]  size    The number of bytes to write to the device. This value indicates how much
 *                     data should be written from the buffer to the device.
 *
 * @return rt_ssize_t  Returns the number of bytes actually written to the device:
 *                      - On success: The number of bytes written, which may be less than `size`
 *                        if there is an issue with the device or the data was truncated.
 *                      - On failure: A negative error code.
 *
 * @note The device must be open and in a writable state before calling this function.
 *       The `pos` parameter allows seeking within the device if it supports such operations.
 *
 * @warning Ensure that the buffer provided contains valid data and that it is large enough
 *          to fit the amount of data specified by `size`. Providing an insufficient buffer
 *          or invalid data may lead to undefined behavior.
 */
rt_ssize_t sys_device_write(rt_device_t dev, rt_off_t pos, const void *buffer, rt_size_t size)
{
    return rt_device_write(dev, pos, buffer, size);
}
