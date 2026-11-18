/*
 * Copyright (c) 2006-2026 RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2026-09-08     CYFS         implement board demo services for storage, buses, and MQTT
 */

#include <rtconfig.h>

#if defined(PKG_USING_LVGL) && defined(BSP_USING_LVGL_BOARD_DEMO)

#include <dirent.h>
#include <dfs.h>
#include <dfs_fs.h>
#include <fcntl.h>
#include <rtdevice.h>
#include <rtthread.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

#include "board_demo_backend.h"

#if defined(BSP_USING_GD32VW553_MQTT_DEMO) && defined(PKG_USING_KAWAII_MQTT)
#include "gd32vw553_mqtt_demo.h"
#endif

#define DBG_TAG                         "app.board.backend"
#define DBG_LVL                         DBG_INFO
#include <rtdbg.h>

#define BOARD_DEMO_WORKER_STACK         8192U
#define BOARD_DEMO_WORKER_PRIORITY      17U
#define BOARD_DEMO_WORKER_TICK          10U
#define BOARD_DEMO_CAN_WORKER_STACK     2048U
#define BOARD_DEMO_CAN_WORKER_PRIORITY  18U
#define BOARD_DEMO_CAN_WORKER_TICK      10U
#define BOARD_DEMO_CAN_POLL_MS          10U
#define BOARD_DEMO_QUEUE_DEPTH          8U
#define BOARD_DEMO_CAN_DEVICE_NAME      "can1"
#define BOARD_DEMO_PWM2_DEVICE_NAME     "pwm2"
#define BOARD_DEMO_PWM2_CHANNEL         2U
#define BOARD_DEMO_PWM30_DEVICE_NAME    "pwm30"
#define BOARD_DEMO_PWM30_CHANNEL        3U
#define BOARD_DEMO_SPI_BUS_NAME         "spi3"
#define BOARD_DEMO_SPI_DEVICE_NAME      "spi3loop"
#define BOARD_DEMO_SPI_BUFFER_MAX       256U
#define BOARD_DEMO_I2C_PROBE_TIMEOUT_MS 20U
#define BOARD_DEMO_I2C_LOCK_TIMEOUT_MS  100U

enum board_demo_command_type
{
    BOARD_DEMO_CMD_FS_LIST = 0,
    BOARD_DEMO_CMD_FILE_PREVIEW,
    BOARD_DEMO_CMD_CAN_BAUD,
    BOARD_DEMO_CMD_CAN_SEND,
    BOARD_DEMO_CMD_MQTT_START,
    BOARD_DEMO_CMD_MQTT_STOP,
    BOARD_DEMO_CMD_MQTT_PUBLISH,
    BOARD_DEMO_CMD_PWM_APPLY,
    BOARD_DEMO_CMD_SPI_LOOPBACK,
    BOARD_DEMO_CMD_I2C_SCAN,
};

struct board_demo_command
{
    enum board_demo_command_type type;
    union
    {
        struct
        {
            char path[BOARD_DEMO_FS_PATH_MAX];
        } fs;
        struct
        {
            rt_uint32_t baud_rate;
        } can_baud;
        struct
        {
            rt_uint32_t id;
            rt_uint8_t data[8];
            rt_uint8_t length;
            rt_bool_t extended;
        } can_send;
        struct
        {
            char topic[BOARD_DEMO_MQTT_TOPIC_MAX];
            char payload[BOARD_DEMO_MQTT_PAYLOAD_MAX];
        } mqtt;
        struct
        {
            rt_uint32_t frequency;
            rt_uint8_t pwm2_duty;
            rt_uint8_t pwm30_duty;
            rt_bool_t pwm2_enabled;
            rt_bool_t pwm30_enabled;
        } pwm;
        struct
        {
            rt_uint32_t frequency;
            rt_uint16_t length;
        } spi;
        struct
        {
            char bus_name[RT_NAME_MAX];
        } i2c;
    } data;
};

static struct board_demo_snapshot demo_state;
static rt_mutex_t demo_state_lock;
static rt_mq_t demo_command_queue;
static rt_thread_t demo_worker_thread;

const char *const board_demo_storage_roots[BOARD_DEMO_STORAGE_COUNT] =
{
    "/flash", "/sd", "/udisk",
};

#ifdef RT_USING_CAN
static rt_device_t demo_can_device;
static rt_thread_t demo_can_thread;
#endif

#ifdef RT_USING_PWM
static struct rt_device_pwm *demo_pwm2_device;
static struct rt_device_pwm *demo_pwm30_device;
#endif

#if defined(RT_USING_SPI) && defined(BSP_USING_SPI3)
static struct rt_spi_device demo_spi_device;
static rt_bool_t demo_spi_attached;
#endif

static void board_demo_strncpy(char *destination, const char *source,
                               rt_size_t destination_size)
{
    if (destination_size == 0U)
    {
        return;
    }

    if (source == RT_NULL)
    {
        destination[0] = '\0';
        return;
    }

    rt_strncpy(destination, source, destination_size - 1U);
    destination[destination_size - 1U] = '\0';
}

static int board_demo_send_command(const struct board_demo_command *command)
{
    if ((demo_command_queue == RT_NULL) || (command == RT_NULL))
    {
        return -RT_ERROR;
    }

    return rt_mq_send(demo_command_queue, command, sizeof(*command));
}

static void board_demo_bus_log(rt_bool_t spi, const char *format, ...)
{
    char line[160];
    char *log;
    char *next;
    rt_size_t used;
    rt_size_t length;
    va_list arguments;

    va_start(arguments, format);
    rt_vsnprintf(line, sizeof(line), format, arguments);
    va_end(arguments);
    length = rt_strlen(line);

    rt_mutex_take(demo_state_lock, RT_WAITING_FOREVER);
    log = spi ? demo_state.spi_log : demo_state.i2c_log;
    used = rt_strlen(log);
    /* Keep complete recent lines when repeated progress fills the log. */
    while (used + length + 2U > BOARD_DEMO_BUS_LOG_MAX)
    {
        next = strchr(log, '\n');
        if (next == RT_NULL)
        {
            used = 0U;
            break;
        }
        used -= (rt_size_t)(next + 1 - log);
        rt_memmove(log, next + 1, used + 1U);
    }
    rt_memcpy(log + used, line, length);
    log[used + length] = '\n';
    log[used + length + 1U] = '\0';
    if (spi)
    {
        demo_state.spi_sequence++;
    }
    else
    {
        demo_state.i2c_sequence++;
    }
    rt_mutex_release(demo_state_lock);
    LOG_I("%s: %s", spi ? "SPI" : "I2C", line);
}

static int board_demo_queue_bus_command(const struct board_demo_command *command)
{
    rt_bool_t spi = command->type == BOARD_DEMO_CMD_SPI_LOOPBACK;
    rt_bool_t *busy;
    char *status;
    char *log;
    rt_err_t result;

    if ((demo_state_lock == RT_NULL) || (demo_command_queue == RT_NULL))
    {
        return -RT_ERROR;
    }

    rt_mutex_take(demo_state_lock, RT_WAITING_FOREVER);
    busy = spi ? &demo_state.spi_busy : &demo_state.i2c_busy;
    status = spi ? demo_state.spi_status : demo_state.i2c_status;
    log = spi ? demo_state.spi_log : demo_state.i2c_log;
    if (*busy)
    {
        rt_mutex_release(demo_state_lock);
        return -RT_EBUSY;
    }

    if (spi)
    {
        demo_state.spi_frequency = command->data.spi.frequency;
        demo_state.spi_length = command->data.spi.length;
        demo_state.spi_passed = RT_FALSE;
        demo_state.spi_mismatch_index = 0xFFFFU;
        rt_snprintf(log, BOARD_DEMO_BUS_LOG_MAX,
                    "QUEUED spi3 | max %u Hz | %u bytes\n",
                    command->data.spi.frequency, command->data.spi.length);
        demo_state.spi_sequence++;
    }
    else
    {
        board_demo_strncpy(demo_state.i2c_bus_name, command->data.i2c.bus_name,
                           sizeof(demo_state.i2c_bus_name));
        demo_state.i2c_device_count = 0U;
        demo_state.i2c_result_code = RT_EOK;
        rt_memset(demo_state.i2c_addresses, BOARD_DEMO_I2C_SKIPPED,
                  sizeof(demo_state.i2c_addresses));
        rt_memset(&demo_state.i2c_addresses[0x08], BOARD_DEMO_I2C_PENDING, 112U);
        rt_snprintf(log, BOARD_DEMO_BUS_LOG_MAX, "QUEUED %s | 0x08-0x77\n",
                    command->data.i2c.bus_name);
        demo_state.i2c_sequence++;
    }

    /* Publish queued state before the worker can publish progress. */
    result = board_demo_send_command(command);
    *busy = result == RT_EOK;
    if (result == RT_EOK)
    {
        rt_snprintf(status, BOARD_DEMO_STATUS_MAX, "%s request queued",
                    spi ? "SPI" : "I2C");
    }
    else
    {
        rt_snprintf(status, BOARD_DEMO_STATUS_MAX, "Request queue failed: %d", result);
        rt_snprintf(log, BOARD_DEMO_BUS_LOG_MAX, "FAIL request queue: %d\n", result);
        if (!spi)
        {
            demo_state.i2c_result_code = result;
        }
    }
    rt_mutex_release(demo_state_lock);
    return result;
}

int board_demo_fs_source(const char *path)
{
    const char *component;
    const char *cursor;
    rt_size_t root_length;
    int index;

    if ((path == RT_NULL) || (path[0] != '/') ||
        (rt_strlen(path) >= BOARD_DEMO_FS_PATH_MAX))
    {
        return -1;
    }

    /* Reject dot components before DFS normalizes a path outside its volume. */
    for (component = path + 1; *component != '\0'; component = cursor)
    {
        for (cursor = component; (*cursor != '\0') && (*cursor != '/'); cursor++)
        {
        }
        if (((cursor - component == 1) && (component[0] == '.')) ||
            ((cursor - component == 2) && (component[0] == '.') &&
             (component[1] == '.')))
        {
            return -1;
        }
        if (*cursor == '/')
        {
            cursor++;
        }
    }

    for (index = 0; index < BOARD_DEMO_STORAGE_COUNT; index++)
    {
        root_length = rt_strlen(board_demo_storage_roots[index]);
        if ((rt_strncmp(path, board_demo_storage_roots[index], root_length) == 0) &&
            ((path[root_length] == '\0') || (path[root_length] == '/')))
        {
            return index;
        }
    }

    return -1;
}

static rt_bool_t board_demo_path_is_allowed(const char *path)
{
    return board_demo_fs_source(path) >= 0 ? RT_TRUE : RT_FALSE;
}

static rt_bool_t board_demo_path_is_mounted(const char *path)
{
    struct dfs_filesystem *filesystem;
    rt_bool_t mounted;
    int source;

    source = board_demo_fs_source(path);
    if (source < 0)
    {
        return RT_FALSE;
    }
    /* Keep the mount record valid while USB removal updates the DFS table. */
    dfs_lock();
    filesystem = dfs_filesystem_lookup(path);
    mounted = (filesystem != RT_NULL) && (filesystem->path != RT_NULL) &&
              (rt_strcmp(filesystem->path, board_demo_storage_roots[source]) == 0);
    dfs_unlock();
    return mounted;
}

rt_uint8_t board_demo_storage_mounts(void)
{
    rt_uint8_t mounts = 0U;
    int source;

    for (source = 0; source < BOARD_DEMO_STORAGE_COUNT; source++)
    {
        if (board_demo_path_is_mounted(board_demo_storage_roots[source]))
        {
            mounts |= (rt_uint8_t)(1U << source);
        }
    }
    return mounts;
}

static void board_demo_sort_entries(struct board_demo_fs_entry *entries,
                                    rt_uint8_t count)
{
    struct board_demo_fs_entry temporary;
    rt_uint8_t current;
    rt_uint8_t previous;
    rt_bool_t move;

    for (current = 1U; current < count; current++)
    {
        temporary = entries[current];
        previous = current;
        while (previous > 0U)
        {
            move = RT_FALSE;
            if (entries[previous - 1U].is_directory != temporary.is_directory)
            {
                move = temporary.is_directory;
            }
            else if (rt_strcmp(entries[previous - 1U].name, temporary.name) > 0)
            {
                move = RT_TRUE;
            }

            if (!move)
            {
                break;
            }

            entries[previous] = entries[previous - 1U];
            previous--;
        }
        entries[previous] = temporary;
    }
}

static void board_demo_fs_list(const char *path)
{
    struct board_demo_fs_entry entries[BOARD_DEMO_FS_ENTRY_MAX];
    struct dirent *directory_entry;
    struct stat file_status;
    DIR *directory;
    char full_path[BOARD_DEMO_FS_PATH_MAX];
    char status[BOARD_DEMO_STATUS_MAX];
    rt_uint8_t count = 0U;
    rt_bool_t limited = RT_FALSE;
    int result;

    if (!board_demo_path_is_allowed(path))
    {
        rt_snprintf(status, sizeof(status), "Path is outside demo storage roots");
        goto _update_failure;
    }
    if (!board_demo_path_is_mounted(path))
    {
        if (rt_strncmp(path, "/flash", 6U) == 0)
        {
            rt_snprintf(status, sizeof(status),
                        "Flash is not mounted or formatted");
        }
        else if (board_demo_fs_source(path) == BOARD_DEMO_STORAGE_SD)
        {
            rt_snprintf(status, sizeof(status), "SD card not mounted");
        }
        else
        {
            rt_snprintf(status, sizeof(status),
                        "USB Host: no FAT/FAT32 volume mounted");
        }
        LOG_W("storage path is not mounted: %s", path);
        goto _update_failure;
    }

    directory = opendir(path);
    if (directory == RT_NULL)
    {
        rt_snprintf(status, sizeof(status), "Cannot open %s", path);
        LOG_E("cannot open storage directory: %s", path);
        goto _update_failure;
    }

    rt_memset(entries, 0, sizeof(entries));
    while ((directory_entry = readdir(directory)) != RT_NULL)
    {
        if ((rt_strcmp(directory_entry->d_name, ".") == 0) ||
            (rt_strcmp(directory_entry->d_name, "..") == 0))
        {
            continue;
        }
        if (count >= BOARD_DEMO_FS_ENTRY_MAX)
        {
            limited = RT_TRUE;
            break;
        }

        result = rt_snprintf(full_path, sizeof(full_path), "%s/%s",
                             path, directory_entry->d_name);
        if ((result <= 0) || ((rt_size_t)result >= sizeof(full_path)))
        {
            limited = RT_TRUE;
            continue;
        }

        board_demo_strncpy(entries[count].name, directory_entry->d_name,
                           sizeof(entries[count].name));
        if (directory_entry->d_type == DT_DIR)
        {
            entries[count].is_directory = RT_TRUE;
            entries[count].size = 0U;
        }
        else
        {
            entries[count].is_directory = RT_FALSE;
            entries[count].size = 0U;
            if (stat(full_path, &file_status) == 0)
            {
                entries[count].is_directory = S_ISDIR(file_status.st_mode) ?
                                              RT_TRUE : RT_FALSE;
                entries[count].size = entries[count].is_directory ? 0U :
                                      (rt_uint32_t)file_status.st_size;
            }
        }
        count++;
    }
    closedir(directory);

    board_demo_sort_entries(entries, count);
    if (limited)
    {
        rt_snprintf(status, sizeof(status), "%u entries | Listing limit reached", count);
    }
    else if (count == 0U)
    {
        board_demo_strncpy(status, "Mounted, empty", sizeof(status));
    }
    else
    {
        rt_snprintf(status, sizeof(status), "%u entries", count);
    }
    LOG_I("listed %u entries from %s", count, path);

    rt_mutex_take(demo_state_lock, RT_WAITING_FOREVER);
    board_demo_strncpy(demo_state.fs_path, path, sizeof(demo_state.fs_path));
    board_demo_strncpy(demo_state.fs_status, status,
                       sizeof(demo_state.fs_status));
    rt_memcpy(demo_state.fs_entries, entries, sizeof(entries));
    demo_state.fs_entry_count = count;
    demo_state.fs_sequence++;
    demo_state.file_name[0] = '\0';
    demo_state.file_preview[0] = '\0';
    demo_state.file_sequence++;
    rt_mutex_release(demo_state_lock);
    return;

_update_failure:
    rt_mutex_take(demo_state_lock, RT_WAITING_FOREVER);
    board_demo_strncpy(demo_state.fs_path, path, sizeof(demo_state.fs_path));
    board_demo_strncpy(demo_state.fs_status, status,
                       sizeof(demo_state.fs_status));
    rt_memset(demo_state.fs_entries, 0, sizeof(demo_state.fs_entries));
    demo_state.fs_entry_count = 0U;
    demo_state.fs_sequence++;
    demo_state.file_name[0] = '\0';
    demo_state.file_preview[0] = '\0';
    demo_state.file_sequence++;
    rt_mutex_release(demo_state_lock);
}

static void board_demo_preview_append(char *buffer, rt_size_t buffer_size,
                                      rt_size_t *used, const char *format, ...)
{
    va_list arguments;
    int length;

    if (*used >= buffer_size - 1U)
    {
        return;
    }

    va_start(arguments, format);
    length = rt_vsnprintf(buffer + *used, buffer_size - *used, format, arguments);
    va_end(arguments);
    if (length <= 0)
    {
        return;
    }

    if ((rt_size_t)length >= buffer_size - *used)
    {
        *used = buffer_size - 1U;
    }
    else
    {
        *used += (rt_size_t)length;
    }
}

static void board_demo_file_preview(const char *path)
{
    rt_uint8_t raw_data[384];
    char preview[BOARD_DEMO_FILE_PREVIEW_MAX];
    rt_size_t printable = 0U;
    rt_size_t used = 0U;
    rt_size_t index;
    int descriptor;
    int length;

    rt_memset(preview, 0, sizeof(preview));
    if (!board_demo_path_is_allowed(path))
    {
        rt_snprintf(preview, sizeof(preview), "Path is outside demo storage roots");
        goto _update;
    }
    if (!board_demo_path_is_mounted(path))
    {
        rt_snprintf(preview, sizeof(preview), "Storage disconnected or not mounted");
        goto _update;
    }

    descriptor = open(path, O_RDONLY, 0);
    if (descriptor < 0)
    {
        rt_snprintf(preview, sizeof(preview), "Cannot open %s", path);
        goto _update;
    }

    length = read(descriptor, raw_data, sizeof(raw_data));
    close(descriptor);
    if (length < 0)
    {
        rt_snprintf(preview, sizeof(preview), "Cannot read %s", path);
        goto _update;
    }
    if (length == 0)
    {
        rt_snprintf(preview, sizeof(preview), "Empty file");
        goto _update;
    }

    for (index = 0U; index < (rt_size_t)length; index++)
    {
        if (((raw_data[index] >= 0x20U) && (raw_data[index] <= 0x7EU)) ||
            (raw_data[index] == '\r') || (raw_data[index] == '\n') ||
            (raw_data[index] == '\t'))
        {
            printable++;
        }
    }

    if (printable * 100U >= (rt_size_t)length * 85U)
    {
        for (index = 0U;
             (index < (rt_size_t)length) && (used < sizeof(preview) - 1U);
             index++)
        {
            preview[used++] = (char)raw_data[index];
        }
        preview[used] = '\0';
    }
    else
    {
        board_demo_preview_append(preview, sizeof(preview), &used,
                                  "Binary preview (%d bytes shown)\n", length);
        for (index = 0U; index < (rt_size_t)length; index++)
        {
            if ((index % 16U) == 0U)
            {
                board_demo_preview_append(preview, sizeof(preview), &used,
                                          "%04X: ", (unsigned int)index);
            }
            board_demo_preview_append(preview, sizeof(preview), &used,
                                      "%02X ", raw_data[index]);
            if (((index % 16U) == 15U) || (index + 1U == (rt_size_t)length))
            {
                board_demo_preview_append(preview, sizeof(preview), &used, "\n");
            }
        }
    }

_update:
    rt_mutex_take(demo_state_lock, RT_WAITING_FOREVER);
    board_demo_strncpy(demo_state.file_name, path,
                       sizeof(demo_state.file_name));
    board_demo_strncpy(demo_state.file_preview, preview,
                       sizeof(demo_state.file_preview));
    demo_state.file_sequence++;
    rt_mutex_release(demo_state_lock);
}

#ifdef RT_USING_CAN
static void board_demo_can_add_frame(const struct rt_can_msg *message,
                                     rt_bool_t transmitted)
{
    struct board_demo_can_frame *frame;
    rt_uint8_t length;

    rt_mutex_take(demo_state_lock, RT_WAITING_FOREVER);
    if (demo_state.can_frame_count < BOARD_DEMO_CAN_LOG_MAX)
    {
        demo_state.can_frame_count++;
    }
    if (demo_state.can_frame_count > 1U)
    {
        rt_memmove(&demo_state.can_frames[1], &demo_state.can_frames[0],
                   (demo_state.can_frame_count - 1U) *
                   sizeof(demo_state.can_frames[0]));
    }

    frame = &demo_state.can_frames[0];
    rt_memset(frame, 0, sizeof(*frame));
    frame->id = message->id;
    frame->tick = rt_tick_get();
    frame->extended = (message->ide == RT_CAN_EXTID) ? RT_TRUE : RT_FALSE;
    frame->transmitted = transmitted;
    length = message->len > 8U ? 8U : message->len;
    frame->length = length;
    rt_memcpy(frame->data, message->data, length);
    if (transmitted)
    {
        demo_state.can_tx_count++;
    }
    else
    {
        demo_state.can_rx_count++;
    }
    demo_state.can_sequence++;
    rt_mutex_release(demo_state_lock);
}

static void board_demo_can_set_status(const char *format, ...)
{
    va_list arguments;
    char status[BOARD_DEMO_STATUS_MAX];

    va_start(arguments, format);
    rt_vsnprintf(status, sizeof(status), format, arguments);
    va_end(arguments);

    rt_mutex_take(demo_state_lock, RT_WAITING_FOREVER);
    board_demo_strncpy(demo_state.can_status, status,
                       sizeof(demo_state.can_status));
    demo_state.can_sequence++;
    rt_mutex_release(demo_state_lock);
}

static void board_demo_can_open(void)
{
    rt_device_t can_device;
    rt_err_t result;

    can_device = rt_device_find(BOARD_DEMO_CAN_DEVICE_NAME);
    if (can_device == RT_NULL)
    {
        board_demo_can_set_status("can1 device not found");
        return;
    }

    result = rt_device_open(can_device,
                            RT_DEVICE_FLAG_INT_RX | RT_DEVICE_FLAG_INT_TX);
    if (result != RT_EOK)
    {
        board_demo_can_set_status("can1 open failed: %d", result);
        return;
    }

    result = rt_device_control(can_device, RT_CAN_CMD_SET_BAUD,
                               (void *)(rt_ubase_t)CAN1MBaud);
    if (result != RT_EOK)
    {
        rt_device_close(can_device);
        board_demo_can_set_status("can1 baud setup failed: %d", result);
        return;
    }

    demo_can_device = can_device;
    rt_mutex_take(demo_state_lock, RT_WAITING_FOREVER);
    demo_state.can_ready = RT_TRUE;
    demo_state.can_baud_rate = CAN1MBaud;
    board_demo_strncpy(demo_state.can_status, "can1 ready at 1 Mbit/s",
                       sizeof(demo_state.can_status));
    demo_state.can_sequence++;
    rt_mutex_release(demo_state_lock);
}

static void board_demo_can_set_baud(rt_uint32_t baud_rate)
{
    rt_err_t result;

    if (demo_can_device == RT_NULL)
    {
        board_demo_can_set_status("can1 is not ready");
        return;
    }

    result = rt_device_control(demo_can_device, RT_CAN_CMD_SET_BAUD,
                               (void *)(rt_ubase_t)baud_rate);
    rt_mutex_take(demo_state_lock, RT_WAITING_FOREVER);
    if (result == RT_EOK)
    {
        demo_state.can_baud_rate = baud_rate;
        rt_snprintf(demo_state.can_status, sizeof(demo_state.can_status),
                    "can1 ready at %u kbit/s", baud_rate / 1000U);
    }
    else
    {
        demo_state.can_error_count++;
        rt_snprintf(demo_state.can_status, sizeof(demo_state.can_status),
                    "CAN baud setup failed: %d", result);
    }
    demo_state.can_sequence++;
    rt_mutex_release(demo_state_lock);
}

static void board_demo_can_send(const struct board_demo_command *command)
{
    struct rt_can_msg message;
    rt_ssize_t written;

    if (demo_can_device == RT_NULL)
    {
        board_demo_can_set_status("can1 is not ready");
        return;
    }

    rt_memset(&message, 0, sizeof(message));
    message.id = command->data.can_send.id;
    message.ide = command->data.can_send.extended ? RT_CAN_EXTID : RT_CAN_STDID;
    message.rtr = RT_CAN_DTR;
    message.len = command->data.can_send.length;
    message.nonblocking = 1U;
    rt_memcpy(message.data, command->data.can_send.data, message.len);

    written = rt_device_write(demo_can_device, 0, &message, sizeof(message));
    if (written == sizeof(message))
    {
        board_demo_can_add_frame(&message, RT_TRUE);
        board_demo_can_set_status("CAN frame sent");
    }
    else
    {
        rt_mutex_take(demo_state_lock, RT_WAITING_FOREVER);
        demo_state.can_error_count++;
        rt_snprintf(demo_state.can_status, sizeof(demo_state.can_status),
                    "CAN send failed: %d", (int)written);
        demo_state.can_sequence++;
        rt_mutex_release(demo_state_lock);
    }
}

static void board_demo_can_poll(void)
{
    struct rt_can_msg message;
    rt_ssize_t length;
    rt_uint8_t count = 0U;

    if (demo_can_device == RT_NULL)
    {
        return;
    }

    do
    {
        rt_memset(&message, 0, sizeof(message));
        length = rt_device_read(demo_can_device, 0, &message, sizeof(message));
        if (length == sizeof(message))
        {
            board_demo_can_add_frame(&message, RT_FALSE);
            count++;
        }
    }
    while ((length == sizeof(message)) && (count < 8U));
}

static void board_demo_can_worker_entry(void *parameter)
{
    RT_UNUSED(parameter);

    LOG_I("CAN worker started");
    board_demo_can_open();

    while (1)
    {
        board_demo_can_poll();
        rt_thread_mdelay(BOARD_DEMO_CAN_POLL_MS);
    }
}
#endif /* RT_USING_CAN */

#if defined(BSP_USING_GD32VW553_MQTT_DEMO) && defined(PKG_USING_KAWAII_MQTT)
static void board_demo_mqtt_receive(const char *topic, const void *payload,
                                    rt_size_t payload_length)
{
    rt_size_t copy_length;

    rt_mutex_take(demo_state_lock, RT_WAITING_FOREVER);
    board_demo_strncpy(demo_state.mqtt_rx_topic, topic,
                       sizeof(demo_state.mqtt_rx_topic));
    copy_length = payload_length;
    if (copy_length >= sizeof(demo_state.mqtt_rx_payload))
    {
        copy_length = sizeof(demo_state.mqtt_rx_payload) - 1U;
    }
    rt_memcpy(demo_state.mqtt_rx_payload, payload, copy_length);
    demo_state.mqtt_rx_payload[copy_length] = '\0';
    board_demo_strncpy(demo_state.mqtt_status, "MQTT message received",
                       sizeof(demo_state.mqtt_status));
    demo_state.mqtt_sequence++;
    rt_mutex_release(demo_state_lock);
}

static void board_demo_mqtt_status(const char *status, int result)
{
    rt_mutex_take(demo_state_lock, RT_WAITING_FOREVER);
    if (result == RT_EOK)
    {
        board_demo_strncpy(demo_state.mqtt_status, status,
                           sizeof(demo_state.mqtt_status));
    }
    else
    {
        rt_snprintf(demo_state.mqtt_status, sizeof(demo_state.mqtt_status),
                    "%s (%d)", status, result);
    }
    demo_state.mqtt_sequence++;
    rt_mutex_release(demo_state_lock);
}

static void board_demo_mqtt_update_state(void)
{
    rt_bool_t running;
    rt_bool_t connected;

    running = gd32vw553_mqtt_demo_is_running();
    connected = gd32vw553_mqtt_demo_is_connected();

    rt_mutex_take(demo_state_lock, RT_WAITING_FOREVER);
    if ((demo_state.mqtt_running != running) ||
        (demo_state.mqtt_connected != connected))
    {
        demo_state.mqtt_running = running;
        demo_state.mqtt_connected = connected;
        demo_state.mqtt_sequence++;
    }
    rt_mutex_release(demo_state_lock);
}

static int board_demo_mqtt_command(const struct board_demo_command *command)
{
    const char *operation;
    int result;

    if (command->type == BOARD_DEMO_CMD_MQTT_START)
    {
        operation = "start";
        result = gd32vw553_mqtt_demo_start();
    }
    else if (command->type == BOARD_DEMO_CMD_MQTT_STOP)
    {
        operation = "stop";
        result = gd32vw553_mqtt_demo_stop();
    }
    else
    {
        operation = "publish";
        result = gd32vw553_mqtt_demo_publish(command->data.mqtt.topic,
                                             command->data.mqtt.payload);
    }
    LOG_I("MQTT %s command result: %d", operation, result);

    rt_mutex_take(demo_state_lock, RT_WAITING_FOREVER);
    if (result == RT_EOK)
    {
        if (command->type == BOARD_DEMO_CMD_MQTT_PUBLISH)
        {
            board_demo_strncpy(demo_state.mqtt_tx_topic,
                               command->data.mqtt.topic,
                               sizeof(demo_state.mqtt_tx_topic));
            board_demo_strncpy(demo_state.mqtt_tx_payload,
                               command->data.mqtt.payload,
                               sizeof(demo_state.mqtt_tx_payload));
            board_demo_strncpy(demo_state.mqtt_status, "MQTT message published",
                               sizeof(demo_state.mqtt_status));
        }
        else if (command->type == BOARD_DEMO_CMD_MQTT_START)
        {
            board_demo_strncpy(demo_state.mqtt_status, "MQTT worker started",
                               sizeof(demo_state.mqtt_status));
        }
        else
        {
            board_demo_strncpy(demo_state.mqtt_status, "MQTT stopping",
                               sizeof(demo_state.mqtt_status));
        }
    }
    else
    {
        rt_snprintf(demo_state.mqtt_status, sizeof(demo_state.mqtt_status),
                    "MQTT operation failed: %d", result);
    }
    demo_state.mqtt_sequence++;
    rt_mutex_release(demo_state_lock);

    board_demo_mqtt_update_state();
    return result;
}
#endif

#ifdef RT_USING_PWM
static rt_err_t board_demo_pwm_apply_channel(struct rt_device_pwm *device,
                                             rt_uint32_t channel,
                                             rt_uint32_t period,
                                             rt_bool_t enabled,
                                             rt_uint8_t duty)
{
    rt_err_t result;
    rt_uint32_t pulse;

    pulse = (rt_uint32_t)(((rt_uint64_t)period * duty) / 100U);
    result = rt_pwm_set(device, channel, period, pulse);
    if (result != RT_EOK)
    {
        return result;
    }

    return enabled ? rt_pwm_enable(device, channel) :
                     rt_pwm_disable(device, channel);
}

static void board_demo_pwm_apply(const struct board_demo_command *command)
{
    rt_uint32_t period;
    rt_err_t result;

    if ((demo_pwm2_device == RT_NULL) || (demo_pwm30_device == RT_NULL))
    {
        demo_pwm2_device = (struct rt_device_pwm *)
                           rt_device_find(BOARD_DEMO_PWM2_DEVICE_NAME);
        demo_pwm30_device = (struct rt_device_pwm *)
                            rt_device_find(BOARD_DEMO_PWM30_DEVICE_NAME);
    }
    if ((demo_pwm2_device == RT_NULL) || (demo_pwm30_device == RT_NULL))
    {
        result = -RT_ENOSYS;
        goto _update;
    }
    if (command->data.pwm.frequency == 0U)
    {
        result = -RT_EINVAL;
        goto _update;
    }

    period = 1000000000U / command->data.pwm.frequency;
    result = board_demo_pwm_apply_channel(demo_pwm2_device,
                                          BOARD_DEMO_PWM2_CHANNEL,
                                          period,
                                          command->data.pwm.pwm2_enabled,
                                          command->data.pwm.pwm2_duty);
    if (result == RT_EOK)
    {
        result = board_demo_pwm_apply_channel(demo_pwm30_device,
                                              BOARD_DEMO_PWM30_CHANNEL,
                                              period,
                                              command->data.pwm.pwm30_enabled,
                                              command->data.pwm.pwm30_duty);
    }

_update:
    rt_mutex_take(demo_state_lock, RT_WAITING_FOREVER);
    if (result == RT_EOK)
    {
        demo_state.pwm_frequency = command->data.pwm.frequency;
        demo_state.pwm2_enabled = command->data.pwm.pwm2_enabled;
        demo_state.pwm2_duty = command->data.pwm.pwm2_duty;
        demo_state.pwm30_enabled = command->data.pwm.pwm30_enabled;
        demo_state.pwm30_duty = command->data.pwm.pwm30_duty;
        rt_snprintf(demo_state.pwm_status, sizeof(demo_state.pwm_status),
                    "PWM updated at %u Hz", command->data.pwm.frequency);
    }
    else
    {
        rt_snprintf(demo_state.pwm_status, sizeof(demo_state.pwm_status),
                    "PWM update failed: %d", result);
    }
    demo_state.pwm_sequence++;
    rt_mutex_release(demo_state_lock);
}
#endif /* RT_USING_PWM */

#if defined(RT_USING_SPI) && defined(BSP_USING_SPI3)
static void board_demo_spi_dump(const char *direction, const rt_uint8_t *data,
                                rt_uint16_t length)
{
    char line[64];
    rt_size_t used;
    rt_uint16_t offset;
    rt_uint16_t index;

    for (offset = 0U; offset < length; offset += 8U)
    {
        used = 0U;
        line[0] = '\0';
        board_demo_preview_append(line, sizeof(line), &used,
                                  "%s %03u:", direction, offset);
        for (index = offset; (index < length) && (index < offset + 8U); index++)
        {
            board_demo_preview_append(line, sizeof(line), &used, " %02X", data[index]);
        }
        board_demo_bus_log(RT_TRUE, "%s", line);
    }
}

static void board_demo_spi_loopback(const struct board_demo_command *command)
{
    struct rt_spi_configuration configuration;
    rt_uint8_t transmit_buffer[BOARD_DEMO_SPI_BUFFER_MAX];
    rt_uint8_t receive_buffer[BOARD_DEMO_SPI_BUFFER_MAX];
    rt_uint16_t mismatch = 0xFFFFU;
    rt_uint16_t index;
    rt_ssize_t transferred;
    rt_err_t result;

    rt_mutex_take(demo_state_lock, RT_WAITING_FOREVER);
    board_demo_strncpy(demo_state.spi_status, "SPI loopback running...",
                       sizeof(demo_state.spi_status));
    demo_state.spi_sequence++;
    rt_mutex_release(demo_state_lock);
    board_demo_bus_log(RT_TRUE, "START spi3 | mode 0 | 8-bit | no CS");
    board_demo_bus_log(RT_TRUE, "SCK PE12 | MOSI PF1 <-> MISO PF0");

    if (!demo_spi_attached)
    {
        result = rt_spi_bus_attach_device(&demo_spi_device,
                                          BOARD_DEMO_SPI_DEVICE_NAME,
                                          BOARD_DEMO_SPI_BUS_NAME,
                                          RT_NULL);
        if (result != RT_EOK)
        {
            board_demo_bus_log(RT_TRUE, "FAIL attach %s: %d",
                               BOARD_DEMO_SPI_BUS_NAME, result);
            goto _update;
        }
        demo_spi_attached = RT_TRUE;
    }

    rt_memset(&configuration, 0, sizeof(configuration));
    configuration.data_width = 8U;
    configuration.mode = RT_SPI_MASTER | RT_SPI_MODE_0 |
                         RT_SPI_MSB | RT_SPI_NO_CS;
    configuration.max_hz = command->data.spi.frequency;
    result = rt_spi_configure(&demo_spi_device, &configuration);
    if (result != RT_EOK)
    {
        board_demo_bus_log(RT_TRUE, "FAIL configure: %d", result);
        goto _update;
    }
    board_demo_bus_log(RT_TRUE, "CONFIG max %u Hz | %u bytes",
                       command->data.spi.frequency, command->data.spi.length);

    for (index = 0U; index < command->data.spi.length; index++)
    {
        transmit_buffer[index] = (rt_uint8_t)(0x5AU ^ index ^ (index >> 3U));
    }
    rt_memset(receive_buffer, 0, command->data.spi.length);
    board_demo_spi_dump("TX", transmit_buffer, command->data.spi.length);
    board_demo_bus_log(RT_TRUE, "TRANSFER started");
    transferred = rt_spi_transfer(&demo_spi_device,
                                  transmit_buffer, receive_buffer,
                                  command->data.spi.length);
    if (transferred != command->data.spi.length)
    {
        board_demo_bus_log(RT_TRUE, "FAIL transfer: %d / %u bytes",
                           (int)transferred, command->data.spi.length);
        if ((transferred > 0) && (transferred < command->data.spi.length))
        {
            board_demo_spi_dump("RX", receive_buffer, (rt_uint16_t)transferred);
        }
        result = -RT_EIO;
        goto _update;
    }
    board_demo_spi_dump("RX", receive_buffer, command->data.spi.length);

    result = RT_EOK;
    for (index = 0U; index < command->data.spi.length; index++)
    {
        if (transmit_buffer[index] != receive_buffer[index])
        {
            mismatch = index;
            result = -RT_ERROR;
            board_demo_bus_log(RT_TRUE, "FAIL byte %u: TX %02X != RX %02X",
                               index, transmit_buffer[index], receive_buffer[index]);
            board_demo_bus_log(RT_TRUE, "Check PF1-PF0 loopback connection");
            break;
        }
    }
    if (result == RT_EOK)
    {
        board_demo_bus_log(RT_TRUE, "PASS: all %u bytes match", command->data.spi.length);
    }

_update:
    rt_mutex_take(demo_state_lock, RT_WAITING_FOREVER);
    demo_state.spi_frequency = command->data.spi.frequency;
    demo_state.spi_length = command->data.spi.length;
    demo_state.spi_mismatch_index = mismatch;
    demo_state.spi_passed = (result == RT_EOK) ? RT_TRUE : RT_FALSE;
    demo_state.spi_busy = RT_FALSE;
    if (result == RT_EOK)
    {
        rt_snprintf(demo_state.spi_status, sizeof(demo_state.spi_status),
                    "Loopback passed: %u bytes", command->data.spi.length);
    }
    else if (mismatch != 0xFFFFU)
    {
        rt_snprintf(demo_state.spi_status, sizeof(demo_state.spi_status),
                    "Mismatch at byte %u", mismatch);
    }
    else
    {
        rt_snprintf(demo_state.spi_status, sizeof(demo_state.spi_status),
                    "SPI loopback failed: %d", result);
    }
    demo_state.spi_sequence++;
    rt_mutex_release(demo_state_lock);
}
#endif

#ifdef RT_USING_I2C
static rt_ssize_t board_demo_i2c_probe(struct rt_i2c_bus_device *bus,
                                       rt_uint16_t address)
{
    struct rt_i2c_msg message;
    rt_uint32_t saved_timeout;
    rt_tick_t probe_timeout;
    rt_ssize_t result;

    rt_memset(&message, 0, sizeof(message));
    message.addr = address;
    message.flags = RT_I2C_WR;

    result = rt_i2c_bus_lock(bus,
                            rt_tick_from_millisecond(BOARD_DEMO_I2C_LOCK_TIMEOUT_MS));
    if (result != RT_EOK)
    {
        return result == -RT_ETIMEOUT ? -RT_EBUSY : result;
    }

    /* The recursive bus lock keeps this temporary timeout private to the probe. */
    saved_timeout = bus->timeout;
    probe_timeout = rt_tick_from_millisecond(BOARD_DEMO_I2C_PROBE_TIMEOUT_MS);
    if ((bus->timeout == 0U) || (bus->timeout > probe_timeout))
    {
        bus->timeout = probe_timeout;
    }
    result = rt_i2c_transfer(bus, &message, 1U);
    bus->timeout = saved_timeout;
    rt_i2c_bus_unlock(bus);
    return result;
}

static void board_demo_i2c_scan(const char *bus_name)
{
    struct rt_i2c_bus_device *bus;
    rt_tick_t start_tick = rt_tick_get();
    rt_uint32_t elapsed_ms;
    rt_uint16_t address = 0x08U;
    rt_uint16_t probed = 0U;
    rt_uint8_t count = 0U;
    rt_uint8_t state;
    rt_ssize_t transferred;
    rt_err_t result = RT_EOK;

    rt_mutex_take(demo_state_lock, RT_WAITING_FOREVER);
    board_demo_strncpy(demo_state.i2c_bus_name, bus_name,
                       sizeof(demo_state.i2c_bus_name));
    rt_snprintf(demo_state.i2c_status, sizeof(demo_state.i2c_status),
                "%s scanning...", bus_name);
    demo_state.i2c_sequence++;
    rt_mutex_release(demo_state_lock);
    board_demo_bus_log(RT_FALSE, "START %s | 7-bit addresses 0x08-0x77", bus_name);
    board_demo_bus_log(RT_FALSE, "Address-only probe | timeout %u ms",
                       BOARD_DEMO_I2C_PROBE_TIMEOUT_MS);

    bus = rt_i2c_bus_device_find(bus_name);
    if (bus == RT_NULL)
    {
        board_demo_bus_log(RT_FALSE, "FAIL: bus %s not found", bus_name);
        result = -RT_ENOENT;
        goto _update;
    }

    for (address = 0x08U; address <= 0x77U; address++)
    {
        transferred = board_demo_i2c_probe(bus, address);
        probed++;
        if (transferred == 1)
        {
            state = BOARD_DEMO_I2C_ACK;
            count++;
            board_demo_bus_log(RT_FALSE, "ACK %s address 0x%02X", bus_name, address);
        }
        else if ((transferred == 0) || (transferred == -RT_EIO))
        {
            /* The GD32 address-only transfer reports an address NACK as EIO. */
            state = BOARD_DEMO_I2C_NACK;
        }
        else
        {
            state = BOARD_DEMO_I2C_ERROR;
            result = transferred < 0 ? (rt_err_t)transferred : -RT_ERROR;
        }

        rt_mutex_take(demo_state_lock, RT_WAITING_FOREVER);
        demo_state.i2c_addresses[address] = state;
        demo_state.i2c_device_count = count;
        rt_snprintf(demo_state.i2c_status, sizeof(demo_state.i2c_status),
                    "%s | %u/112 | found %u", bus_name, probed, count);
        demo_state.i2c_sequence++;
        rt_mutex_release(demo_state_lock);
        if (result != RT_EOK)
        {
            board_demo_bus_log(RT_FALSE, "FAIL 0x%02X: %s (%d)", address,
                               result == -RT_ETIMEOUT ? "bus/probe timeout" :
                               (result == -RT_EBUSY ? "bus in use" : "transfer error"),
                               result);
            break;
        }
    }
    if ((result == RT_EOK) && (count == 0U))
    {
        board_demo_bus_log(RT_FALSE, "No response: check power, SCL/SDA and pull-ups");
    }

_update:
    elapsed_ms = (rt_uint32_t)(((rt_uint64_t)(rt_tick_get() - start_tick) * 1000U) /
                              RT_TICK_PER_SECOND);
    board_demo_bus_log(RT_FALSE, "%s %s | %u/112 | %u devices | %u ms",
                       result == RT_EOK ? "DONE" : "STOPPED", bus_name,
                       probed, count, elapsed_ms);
    rt_mutex_take(demo_state_lock, RT_WAITING_FOREVER);
    board_demo_strncpy(demo_state.i2c_bus_name, bus_name,
                       sizeof(demo_state.i2c_bus_name));
    demo_state.i2c_device_count = count;
    demo_state.i2c_result_code = result;
    demo_state.i2c_busy = RT_FALSE;
    if (result == RT_EOK)
    {
        rt_snprintf(demo_state.i2c_status, sizeof(demo_state.i2c_status),
                    "%s: %u device%s | %u ms", bus_name, count,
                    count == 1U ? "" : "s", elapsed_ms);
    }
    else if (bus == RT_NULL)
    {
        rt_snprintf(demo_state.i2c_status, sizeof(demo_state.i2c_status),
                    "%s is not available", bus_name);
    }
    else
    {
        rt_snprintf(demo_state.i2c_status, sizeof(demo_state.i2c_status),
                    "%s stopped at 0x%02X: %s (%d)", bus_name, address,
                    result == -RT_ETIMEOUT ? "timeout" :
                    (result == -RT_EBUSY ? "bus in use" : "transfer error"), result);
    }
    demo_state.i2c_sequence++;
    rt_mutex_release(demo_state_lock);
}
#endif /* RT_USING_I2C */

static void board_demo_handle_command(const struct board_demo_command *command)
{
    switch (command->type)
    {
    case BOARD_DEMO_CMD_CAN_BAUD:
#ifdef RT_USING_CAN
        board_demo_can_set_baud(command->data.can_baud.baud_rate);
#endif
        break;
    case BOARD_DEMO_CMD_CAN_SEND:
#ifdef RT_USING_CAN
        board_demo_can_send(command);
#endif
        break;
    case BOARD_DEMO_CMD_MQTT_START:
    case BOARD_DEMO_CMD_MQTT_STOP:
    case BOARD_DEMO_CMD_MQTT_PUBLISH:
#if defined(BSP_USING_GD32VW553_MQTT_DEMO) && defined(PKG_USING_KAWAII_MQTT)
        board_demo_mqtt_command(command);
#endif
        break;
    case BOARD_DEMO_CMD_PWM_APPLY:
#ifdef RT_USING_PWM
        board_demo_pwm_apply(command);
#endif
        break;
    case BOARD_DEMO_CMD_SPI_LOOPBACK:
#if defined(RT_USING_SPI) && defined(BSP_USING_SPI3)
        board_demo_spi_loopback(command);
#endif
        break;
    case BOARD_DEMO_CMD_I2C_SCAN:
#ifdef RT_USING_I2C
        board_demo_i2c_scan(command->data.i2c.bus_name);
#endif
        break;
    default:
        break;
    }
}

static void board_demo_worker_entry(void *parameter)
{
    struct board_demo_command command;
    rt_ssize_t received;

    RT_UNUSED(parameter);
    LOG_I("command worker started");

    while (1)
    {
        received = rt_mq_recv(demo_command_queue, &command, sizeof(command),
                              rt_tick_from_millisecond(20U));
        /* rt_mq_recv returns the byte count on success, not RT_EOK. */
        if (received == (rt_ssize_t)sizeof(command))
        {
            LOG_I("processing command %d", command.type);
            board_demo_handle_command(&command);
        }
        else if (received != -RT_ETIMEOUT)
        {
            LOG_E("command receive returned %d, expected %u bytes",
                  (int)received, (unsigned int)sizeof(command));
        }

#if defined(BSP_USING_GD32VW553_MQTT_DEMO) && defined(PKG_USING_KAWAII_MQTT)
        board_demo_mqtt_update_state();
#endif
    }
}

int board_demo_backend_init(void)
{
    rt_err_t result;
#ifdef RT_USING_CAN
    rt_err_t can_result;
#endif

    if (demo_worker_thread != RT_NULL)
    {
        return RT_EOK;
    }

    rt_memset(&demo_state, 0, sizeof(demo_state));
    board_demo_strncpy(demo_state.fs_path, "/flash",
                       sizeof(demo_state.fs_path));
    board_demo_strncpy(demo_state.fs_status, "Storage not scanned",
                       sizeof(demo_state.fs_status));
    board_demo_strncpy(demo_state.can_status, "CAN initializing",
                       sizeof(demo_state.can_status));
    board_demo_strncpy(demo_state.mqtt_status, "MQTT stopped",
                       sizeof(demo_state.mqtt_status));
    board_demo_strncpy(demo_state.pwm_status, "PWM idle",
                       sizeof(demo_state.pwm_status));
    board_demo_strncpy(demo_state.spi_status, "SPI loopback idle",
                       sizeof(demo_state.spi_status));
    board_demo_strncpy(demo_state.i2c_status, "I2C scan idle",
                       sizeof(demo_state.i2c_status));
    demo_state.spi_mismatch_index = 0xFFFFU;

    demo_state_lock = rt_mutex_create("boardui", RT_IPC_FLAG_PRIO);
    if (demo_state_lock == RT_NULL)
    {
        return -RT_ENOMEM;
    }

    demo_command_queue = rt_mq_create("boardcmd", sizeof(struct board_demo_command),
                                      BOARD_DEMO_QUEUE_DEPTH, RT_IPC_FLAG_PRIO);
    if (demo_command_queue == RT_NULL)
    {
        rt_mutex_delete(demo_state_lock);
        demo_state_lock = RT_NULL;
        return -RT_ENOMEM;
    }

#if defined(BSP_USING_GD32VW553_MQTT_DEMO) && defined(PKG_USING_KAWAII_MQTT)
    gd32vw553_mqtt_demo_set_receive_callback(board_demo_mqtt_receive);
    gd32vw553_mqtt_demo_set_status_callback(board_demo_mqtt_status);
#endif

    demo_worker_thread = rt_thread_create("boarddemo", board_demo_worker_entry,
                                          RT_NULL, BOARD_DEMO_WORKER_STACK,
                                          BOARD_DEMO_WORKER_PRIORITY,
                                          BOARD_DEMO_WORKER_TICK);
    if (demo_worker_thread == RT_NULL)
    {
        rt_mq_delete(demo_command_queue);
        rt_mutex_delete(demo_state_lock);
        demo_command_queue = RT_NULL;
        demo_state_lock = RT_NULL;
        return -RT_ENOMEM;
    }

    result = rt_thread_startup(demo_worker_thread);
    if (result != RT_EOK)
    {
        rt_thread_delete(demo_worker_thread);
        rt_mq_delete(demo_command_queue);
        rt_mutex_delete(demo_state_lock);
        demo_worker_thread = RT_NULL;
        demo_command_queue = RT_NULL;
        demo_state_lock = RT_NULL;
        return result;
    }

#ifdef RT_USING_CAN
    demo_can_thread = rt_thread_create("bdcan", board_demo_can_worker_entry,
                                       RT_NULL, BOARD_DEMO_CAN_WORKER_STACK,
                                       BOARD_DEMO_CAN_WORKER_PRIORITY,
                                       BOARD_DEMO_CAN_WORKER_TICK);
    if (demo_can_thread == RT_NULL)
    {
        board_demo_can_set_status("CAN worker creation failed");
    }
    else
    {
        can_result = rt_thread_startup(demo_can_thread);
        if (can_result != RT_EOK)
        {
            rt_thread_delete(demo_can_thread);
            demo_can_thread = RT_NULL;
            board_demo_can_set_status("CAN worker startup failed: %d",
                                      can_result);
        }
    }
#endif

    return RT_EOK;
}

int board_demo_backend_get_snapshot(struct board_demo_snapshot *snapshot)
{
    if ((snapshot == RT_NULL) || (demo_state_lock == RT_NULL))
    {
        return -RT_EINVAL;
    }

#if defined(BSP_USING_GD32VW553_MQTT_DEMO) && defined(PKG_USING_KAWAII_MQTT)
    board_demo_mqtt_update_state();
#endif

    rt_mutex_take(demo_state_lock, RT_WAITING_FOREVER);
    rt_memcpy(snapshot, &demo_state, sizeof(*snapshot));
    rt_mutex_release(demo_state_lock);
    return RT_EOK;
}

int board_demo_request_fs_list(const char *path)
{
    if ((path == RT_NULL) || !board_demo_path_is_allowed(path))
    {
        return -RT_EINVAL;
    }

    board_demo_fs_list(path);
    return RT_EOK;
}

int board_demo_request_file_preview(const char *path)
{
    if ((path == RT_NULL) || !board_demo_path_is_allowed(path))
    {
        return -RT_EINVAL;
    }

    board_demo_file_preview(path);
    return RT_EOK;
}

int board_demo_request_can_baud(rt_uint32_t baud_rate)
{
    struct board_demo_command command;

    rt_memset(&command, 0, sizeof(command));
    command.type = BOARD_DEMO_CMD_CAN_BAUD;
    command.data.can_baud.baud_rate = baud_rate;
    return board_demo_send_command(&command);
}

int board_demo_request_can_send(rt_uint32_t id, rt_bool_t extended,
                                const rt_uint8_t *data, rt_uint8_t length)
{
    struct board_demo_command command;

    if ((data == RT_NULL) || (length > 8U) ||
        (!extended && (id > 0x7FFU)) || (extended && (id > 0x1FFFFFFFU)))
    {
        return -RT_EINVAL;
    }

    rt_memset(&command, 0, sizeof(command));
    command.type = BOARD_DEMO_CMD_CAN_SEND;
    command.data.can_send.id = id;
    command.data.can_send.extended = extended;
    command.data.can_send.length = length;
    rt_memcpy(command.data.can_send.data, data, length);
    return board_demo_send_command(&command);
}

int board_demo_request_mqtt_start(void)
{
#if defined(BSP_USING_GD32VW553_MQTT_DEMO) && defined(PKG_USING_KAWAII_MQTT)
    struct board_demo_command command;

    rt_memset(&command, 0, sizeof(command));
    command.type = BOARD_DEMO_CMD_MQTT_START;
    return board_demo_mqtt_command(&command);
#else
    return -RT_ENOSYS;
#endif
}

int board_demo_request_mqtt_stop(void)
{
#if defined(BSP_USING_GD32VW553_MQTT_DEMO) && defined(PKG_USING_KAWAII_MQTT)
    struct board_demo_command command;

    rt_memset(&command, 0, sizeof(command));
    command.type = BOARD_DEMO_CMD_MQTT_STOP;
    return board_demo_mqtt_command(&command);
#else
    return -RT_ENOSYS;
#endif
}

int board_demo_request_mqtt_publish(const char *topic, const char *payload)
{
#if defined(BSP_USING_GD32VW553_MQTT_DEMO) && defined(PKG_USING_KAWAII_MQTT)
    struct board_demo_command command;

    if ((topic == RT_NULL) || (payload == RT_NULL) ||
        (topic[0] == '\0') || (payload[0] == '\0'))
    {
        return -RT_EINVAL;
    }

    rt_memset(&command, 0, sizeof(command));
    command.type = BOARD_DEMO_CMD_MQTT_PUBLISH;
    board_demo_strncpy(command.data.mqtt.topic, topic,
                       sizeof(command.data.mqtt.topic));
    board_demo_strncpy(command.data.mqtt.payload, payload,
                       sizeof(command.data.mqtt.payload));
    return board_demo_mqtt_command(&command);
#else
    RT_UNUSED(topic);
    RT_UNUSED(payload);
    return -RT_ENOSYS;
#endif
}

int board_demo_request_pwm(rt_uint32_t frequency,
                           rt_bool_t pwm2_enabled, rt_uint8_t pwm2_duty,
                           rt_bool_t pwm30_enabled, rt_uint8_t pwm30_duty)
{
    struct board_demo_command command;

    if ((frequency == 0U) || (pwm2_duty > 100U) || (pwm30_duty > 100U))
    {
        return -RT_EINVAL;
    }

    rt_memset(&command, 0, sizeof(command));
    command.type = BOARD_DEMO_CMD_PWM_APPLY;
    command.data.pwm.frequency = frequency;
    command.data.pwm.pwm2_enabled = pwm2_enabled;
    command.data.pwm.pwm2_duty = pwm2_duty;
    command.data.pwm.pwm30_enabled = pwm30_enabled;
    command.data.pwm.pwm30_duty = pwm30_duty;
    return board_demo_send_command(&command);
}

int board_demo_request_spi_loopback(rt_uint32_t frequency, rt_uint16_t length)
{
#if defined(RT_USING_SPI) && defined(BSP_USING_SPI3)
    struct board_demo_command command;

    if ((frequency == 0U) || (length == 0U) ||
        (length > BOARD_DEMO_SPI_BUFFER_MAX))
    {
        return -RT_EINVAL;
    }

    rt_memset(&command, 0, sizeof(command));
    command.type = BOARD_DEMO_CMD_SPI_LOOPBACK;
    command.data.spi.frequency = frequency;
    command.data.spi.length = length;
    return board_demo_queue_bus_command(&command);
#else
    RT_UNUSED(frequency);
    RT_UNUSED(length);
    return -RT_ENOSYS;
#endif
}

int board_demo_request_i2c_scan(const char *bus_name)
{
#ifdef RT_USING_I2C
    struct board_demo_command command;

    if ((bus_name == RT_NULL) || (rt_strcmp(bus_name, BOARD_DEMO_I2C_BUS_NAME) != 0))
    {
        return -RT_EINVAL;
    }

    rt_memset(&command, 0, sizeof(command));
    command.type = BOARD_DEMO_CMD_I2C_SCAN;
    board_demo_strncpy(command.data.i2c.bus_name, bus_name,
                       sizeof(command.data.i2c.bus_name));
    return board_demo_queue_bus_command(&command);
#else
    RT_UNUSED(bus_name);
    return -RT_ENOSYS;
#endif
}

#endif /* PKG_USING_LVGL && BSP_USING_LVGL_BOARD_DEMO */
