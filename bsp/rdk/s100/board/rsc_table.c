
#include "rsc_table.h"

extern uint32_t OS_HEAP_START_ADDR;
extern uint32_t OS_HEAP_SIZE;
extern uint32_t MCU_LOG_START_ADDR;
extern uint32_t MCU_LOG_SIZE;
extern uint32_t __SCMI_IPC_START_ADDR;
extern uint32_t __SCMI_IPC_SIZE;
extern uint32_t ATCM_START_ADDR;
extern uint32_t ATCM_SIZE;
extern uint32_t CAN_START_ADDR;
extern uint32_t FLASH_SEC_ADDR;
extern uint32_t FLASH_STARTUP_LEN;

#define NUM_TABLE_ENTRIES               (7)
#define HB_SECTION_T(S)                 __attribute__((__section__(#S)))
#define HB_RESOURCE                     HB_SECTION_T(.resource_table)
#define MCU_FLASH_START_BASE_ADDR       (0x0CAA5000)
#define MCU_FLASH_BASE_ADDR             (0x0CAA5400)
#define MCU_FREERTOS_HEAP_BASE_ADDR     ((uint32_t)&OS_HEAP_START_ADDR)
#define MCU_LOG_BASE_ADDR               ((uint32_t)&MCU_LOG_START_ADDR)
#define MCU_SCMI_BASE_ADDR              ((uint32_t)&__SCMI_IPC_START_ADDR)
#define MCU_ATCM_ADDR                   ((uint32_t)&ATCM_START_ADDR)
#define MCU_FLASH_START_DDR_ADDR        (0x0CAB0000)
#define MCU_FLASH_DDR_ADDR              ((uint32_t)&FLASH_SEC_ADDR)
#define MCU_FREERTOS_HEAP_DDR_ADDR      ((uint32_t)&OS_HEAP_START_ADDR)
#define MCU_LOG_DDR_ADDR                ((uint32_t)&MCU_LOG_START_ADDR)
#define MCU_SCMI_DDR_ADDR               ((uint32_t)&__SCMI_IPC_START_ADDR)
#define MCU_BTCM_ADDR                   ((uint32_t)&CAN_START_ADDR)
#define MCU_FLASH_START_SIZE            ((uint32_t)&FLASH_STARTUP_LEN)
#define MCU_FLASH_SIZE                  (0x2AAC00)
#define MCU_RTTHREAD_HEAP_ADDR          ((uint32_t)&OS_HEAP_START_ADDR)
#define MCU_RTTHREAD_HEAP_SIZE          ((uint32_t)&OS_HEAP_SIZE)
#define MCU_LOG_SIZE                    ((uint32_t)&MCU_LOG_SIZE)
#define MCU_SCMI_SIZE                   ((uint32_t)&__SCMI_IPC_SIZE)
#define MCU_ATCM_SIZE                   ((uint32_t)&ATCM_SIZE)

const struct remote_resource_table HB_RESOURCE resources = {
    /* Version */
    1,

    /* NUmber of table entries */
    NUM_TABLE_ENTRIES,
    /* reserved fields */
    {0x0, 0x0,},

    /* Offsets of rsc entries */
    {
        /* offsetof(struct remote_resource_table, rproc_version), */
        /* offsetof(struct remote_resource_table, fw_chksum), */
        /* offsetof(struct remote_resource_table, ddr_devmem), */
        /* offsetof(struct remote_resource_table, tcm_devmem), */
        /* offsetof(struct remote_resource_table, rpmsg_vdev), */
        offsetof(struct remote_resource_table, fw_version),
        offsetof(struct remote_resource_table, startup_devmem),
        offsetof(struct remote_resource_table, flash_devmem),
        offsetof(struct remote_resource_table, freertos_heap_devmem),
        offsetof(struct remote_resource_table, log_devmem),
        offsetof(struct remote_resource_table, scmi_devmem),
        offsetof(struct remote_resource_table, atcm_devmem),
    },

    {(uint32_t)RSC_VERSION, {0}, {0}, {0}},
    /* flash_start_mem entry */
    {(uint32_t)RSC_DEVMEM, MCU_FLASH_START_DDR_ADDR, MCU_FLASH_START_DDR_ADDR, MCU_FLASH_START_SIZE, 0, 0, "startup devmem"},
    {(uint32_t)RSC_DEVMEM, MCU_FLASH_DDR_ADDR, MCU_FLASH_DDR_ADDR, MCU_FLASH_SIZE, 0, 0, "flash devmem"},
    {(uint32_t)RSC_DEVMEM, MCU_RTTHREAD_HEAP_ADDR, MCU_RTTHREAD_HEAP_ADDR, MCU_RTTHREAD_HEAP_SIZE, 0, 0, "rtthread_heap devmem"},
    {(uint32_t)RSC_DEVMEM, MCU_LOG_DDR_ADDR, MCU_LOG_DDR_ADDR, MCU_LOG_SIZE, 0, 0, "log devmem"},
    {(uint32_t)RSC_DEVMEM, MCU_SCMI_DDR_ADDR, MCU_SCMI_DDR_ADDR, MCU_SCMI_SIZE, 0, 0, "scmi devmem"},
    {(uint32_t)RSC_DEVMEM, MCU_ATCM_ADDR, MCU_BTCM_ADDR, MCU_ATCM_SIZE, 0, 0, "atcm devmem"},

};

