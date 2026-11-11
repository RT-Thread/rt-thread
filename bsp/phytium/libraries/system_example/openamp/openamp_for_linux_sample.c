#include "rtconfig.h"

#ifdef BSP_USING_SYSTEM_EXAMPLE

#include <openamp/open_amp.h>
#include <openamp/version.h>
#include <metal/alloc.h>
#include <metal/version.h>
#include <metal/sleep.h>
#include "platform_info.h"
#include "rpmsg_service.h"
#include "rsc_table.h"
#include "helper.h"
#include "fpsci.h"
#include "openamp_configs.h"
#include "libmetal_configs.h"
#include "fdrivers_port.h"
#include "openamp_for_linux_sample.h"

#define OPENAMP_SLAVE_DEBUG_TAG "OPENAMP_SLAVE"
#define OPENAMP_SLAVE_ERROR(format, ...) FT_DEBUG_PRINT_E(OPENAMP_SLAVE_DEBUG_TAG, format, ##__VA_ARGS__)
#define OPENAMP_SLAVE_WARN(format, ...)  FT_DEBUG_PRINT_W(OPENAMP_SLAVE_DEBUG_TAG, format, ##__VA_ARGS__)
#define OPENAMP_SLAVE_INFO(format, ...)  FT_DEBUG_PRINT_I(OPENAMP_SLAVE_DEBUG_TAG, format, ##__VA_ARGS__)
#define OPENAMP_SLAVE_DEBUG(format, ...) FT_DEBUG_PRINT_D(OPENAMP_SLAVE_DEBUG_TAG, format, ##__VA_ARGS__)

#define OPENAMP_THREAD_STACK_SIZE   2048
#define OPENAMP_THREAD_PRIORITY     5
#define OPENAMP_THREAD_TIMESLICE    10

#define MAX_DATA_LENGTH       (RPMSG_BUFFER_SIZE / 2)

#define DEVICE_CORE_START     0x0001U /* 开始任务 */
#define DEVICE_CORE_SHUTDOWN  0x0002U /* 关闭核心 */
#define DEVICE_CORE_CHECK     0x0003U /* 检查消息 */

/************************** Variable Definitions *****************************/
static volatile int shutdown_req = 0;

/*******************例程全局变量***********************************************/
struct remoteproc remoteproc_slave_00;
static struct rpmsg_device *rpdev_slave_00 = NULL;

/* 协议数据结构 */
typedef struct {
    uint32_t command; /* 命令字，占4个字节 */
    uint16_t length;  /* 数据长度，占2个字节 */
    char data[MAX_DATA_LENGTH];       /* 数据内容，动态长度 */
} ProtocolData;

static ProtocolData protocol_data;

/************************** 资源表定义，与linux协商一致 **********/
static struct remote_resource_table __resource resources __attribute__((used)) = {
    /* Version */
    1,

    /* NUmber of table entries */
    NUM_TABLE_ENTRIES,
    /* reserved fields */
    {0, 0,},

    /* Offsets of rsc entries */
    {
     offsetof(struct remote_resource_table, rpmsg_vdev),
    },

    /* Virtio device entry */
    {
     RSC_VDEV, VIRTIO_ID_RPMSG_, VDEV_NOTIFYID, RPMSG_IPU_C0_FEATURES, 0, 0, 0,
     NUM_VRINGS, {0, 0},
    },

    /* Vring rsc entry - part of vdev rsc entry */
    {SLAVE00_TX_VRING_ADDR, VRING_ALIGN, SLAVE00_VRING_NUM, 1, 0},
    {SLAVE00_RX_VRING_ADDR, VRING_ALIGN, SLAVE00_VRING_NUM, 2, 0},
};

/********** 共享内存定义，与linux协商一致 **********/
static metal_phys_addr_t poll_phys_addr = SLAVE00_KICK_IO_ADDR;
struct metal_device kick_driver_00 = {
    .name = SLAVE_00_KICK_DEV_NAME,
    .bus = NULL,
    .num_regions = 1,
    .regions = {
        {
            .virt = (void *)SLAVE00_KICK_IO_ADDR,
            .physmap = &poll_phys_addr,
            .size = 0x1000,
            .page_shift = -1UL,
            .page_mask = -1UL,
            .mem_flags = SLAVE00_SOURCE_TABLE_ATTRIBUTE,
            .ops = {NULL},
        }
    },
    .irq_num = 1,/* Number of IRQs per device */
    .irq_info = (void *)SLAVE_00_SGI,
};

struct remoteproc_priv slave_00_priv = {
    .kick_dev_name =           SLAVE_00_KICK_DEV_NAME  ,
    .kick_dev_bus_name =        KICK_BUS_NAME ,
    .cpu_id        =  MASTER_CORE_MASK,/* 给所有core发送中断 */

    .src_table_attribute = SLAVE00_SOURCE_TABLE_ATTRIBUTE ,

    /* |rx vring|tx vring|share buffer| */
    .share_mem_va = SLAVE00_SHARE_MEM_ADDR ,
    .share_mem_pa = SLAVE00_SHARE_MEM_ADDR ,
    .share_buffer_offset = SLAVE00_VRING_SIZE ,
    .share_mem_size = SLAVE00_SHARE_MEM_SIZE ,
    .share_mem_attribute = SLAVE00_SHARE_BUFFER_ATTRIBUTE
};

/************************** Function Prototypes ******************************/
/*协议解析接口*/
int parse_protocol_data(const char* input, size_t input_size, ProtocolData* output)
{

    if (input_size < 6) { /* 确保最小长度（命令字+数据长度）*/
        return -1; /* 数据太短 */
    }

    /* 提取命令字 */
    output->command = *((uint32_t*)input);
    input += 4;

    /* 提取数据长度 */
    output->length = *((uint16_t*)input);
    input += 2;

    /* 检查数据长度是否超出预定义最大长度 */
    if (output->length > MAX_DATA_LENGTH) {
        return -2; // 数据长度超出限制
    }

    /* 复制数据内容 */
    memcpy(output->data, input, output->length);

    return 0; /* 解析成功 */
}

/*协议组装接口*/
int assemble_protocol_data(const ProtocolData* input, char* output, size_t* output_size)
{
    /* 检查预期的输出大小是否超出最大长度 */
    if (6 + input->length > MAX_DATA_LENGTH) {
        return -1; /* 数据长度超出限制 */
    }

    *output_size = 6 + input->length; /* 命令字+长度+数据 */

    /* 组装命令字 */
    *((uint32_t*)output) = input->command;

    /* 组装数据长度 */
    *((uint16_t*)(output + 4)) = input->length;

    /* 复制数据内容 */
    memcpy(output + 6, input->data, input->length);

    return 0; /* 组装成功 */
}

/*-----------------------------------------------------------------------------*
 *  RPMSG endpoint callbacks
 *-----------------------------------------------------------------------------*/
static int rpmsg_endpoint_cb(struct rpmsg_endpoint *ept, void *data, size_t len, uint32_t src, void *priv)
{
    (void)priv;
    (void)src;

    int ret;
    (void)priv;
    printf("src:0x%x",src);
    ept->dest_addr = src;

    ret = parse_protocol_data((char *)data, len, &protocol_data);
    if(ret != 0)
    {
        OPENAMP_SLAVE_ERROR("parse protocol data error,ret:%d",ret);
        return RPMSG_SUCCESS;/* 解析失败，忽略数据 */
    }
    printf("command:0x%x,length:%d.",protocol_data.command,protocol_data.length);
    switch (protocol_data.command)
    {
        case DEVICE_CORE_START:
        {
            break;
        }
        case DEVICE_CORE_SHUTDOWN:
        {
            shutdown_req = 1;
            break;
        }
        case DEVICE_CORE_CHECK:
        {
            /* Send temp_data back to master */
            /* 请勿直接对data指针对应的内存进行写操作，操作vring中remoteproc发送通道分配的内存，引发错误的问题*/
            ret = rpmsg_send(ept, &protocol_data, len);
            if (ret < 0)
            {
                OPENAMP_SLAVE_ERROR("rpmsg_send failed.\r\n");
                return ret;
            }
            break;
        }
        default:
            break;
    }

    return RPMSG_SUCCESS;
}

static void rpmsg_service_unbind(struct rpmsg_endpoint *ept)
{
    (void)ept;
    printf("unexpected Remote endpoint destroy.");
    shutdown_req = 1;
}

/*-----------------------------------------------------------------------------*
 *  Application
 *-----------------------------------------------------------------------------*/
static int FRpmsgEchoApp(struct rpmsg_device *rdev, void *priv)
{
    int ret = 0;
    struct rpmsg_endpoint lept;
    memset(&lept, 0, sizeof(lept));
    shutdown_req = 0;
    /* Initialize RPMSG framework */
    printf("Try to create rpmsg endpoint.\r\n");

    ret = rpmsg_create_ept(&lept, rdev, RPMSG_SERVICE_NAME, 0, RPMSG_ADDR_ANY, rpmsg_endpoint_cb, rpmsg_service_unbind);
    if (ret)
    {
        OPENAMP_SLAVE_ERROR("Failed to create endpoint. %d \r\n", ret);
        return -1;
    }

    printf("Successfully created rpmsg endpoint.\r\n");

    while (1)
    {
        platform_poll(priv);
        /* we got a shutdown request, exit */
        if (shutdown_req || rproc_get_stop_flag())
        {
            rproc_clear_stop_flag();
            break;
        }
    }

    rpmsg_destroy_ept(&lept);

    return ret;
}


/*-----------------------------------------------------------------------------*
 *  Application entry point
 *-----------------------------------------------------------------------------*/
int slave_init(void)
{
    init_system();  // Initialize the system resources and environment
    //打印remoteproc_slave_00地址，slave_00_priv地址，kick_driver_00地址
    printf("remoteproc slave 00 address: 0x%x,0x%x,0x%x\r\n",&remoteproc_slave_00,&slave_00_priv,&kick_driver_00);

    if (!platform_create_proc(&remoteproc_slave_00, &slave_00_priv, &kick_driver_00))
    {
        OPENAMP_SLAVE_ERROR("Failed to create remoteproc instance for slave 00\r\n");
        return -1;  // Return with an error if creation fails
    }
    remoteproc_slave_00.rsc_table = &resources;
    printf("remoteproc slave 00 rsc_table address: 0x%x\r\n",remoteproc_slave_00.rsc_table);
    if (platform_setup_src_table(&remoteproc_slave_00,remoteproc_slave_00.rsc_table))
    {
        OPENAMP_SLAVE_ERROR("Failed to setup src table for slave 00\r\n");
        return -1;  // Return with an error if setup fails
    }

    printf("Setup resource tables for the created remoteproc instances is over \r\n");

    if (platform_setup_share_mems(&remoteproc_slave_00))
    {
        OPENAMP_SLAVE_ERROR("Failed to setup shared memory for slave 00\r\n");
        return -1;  // Return with an error if setup fails
    }

    printf("Setup shared memory regions for both remoteproc instances is over \r\n");

    rpdev_slave_00 = platform_create_rpmsg_vdev(&remoteproc_slave_00, 0, VIRTIO_DEV_DEVICE, NULL, NULL);
    if (!rpdev_slave_00)
    {
        OPENAMP_SLAVE_ERROR("Failed to create rpmsg vdev for slave 00\r\n");
        return -1;  // Return with an error if creation fails
    }
    printf("platform_create_rpmsg_vdev for slave 00 is over\r\n ");
    return 0;
}

static void RpmsgEchoTask(void * args)
{
    int ret;
    printf("openamp lib version: %s (", openamp_version());
    printf("Major: %d, ", openamp_version_major());
    printf("Minor: %d, ", openamp_version_minor());
    printf("Patch: %d)\r\n", openamp_version_patch());

    printf("libmetal lib version: %s (", metal_ver());
    printf("Major: %d, ", metal_ver_major());
    printf("Minor: %d, ", metal_ver_minor());
    printf("Patch: %d)\r\n", metal_ver_patch());

    /* Initialize platform */
    printf("start application...");
    if(!slave_init())
    {
        ret = FRpmsgEchoApp(rpdev_slave_00,&remoteproc_slave_00);
        if (ret)
        {
            OPENAMP_SLAVE_ERROR("Failed to running echoapp");
            platform_cleanup(&remoteproc_slave_00);
        }
        platform_release_rpmsg_vdev(rpdev_slave_00, &remoteproc_slave_00);
        printf("Stopping application...\r\n");
        platform_cleanup(&remoteproc_slave_00);
    }
    else
    {
        platform_cleanup(&remoteproc_slave_00);
        OPENAMP_SLAVE_ERROR("Failed to init remoteproc.\r\n");
    }
    FPsciCpuOff();

}

int creat_openamp_thread(void)
{
    rt_thread_t tid = RT_NULL;

    tid = rt_thread_create("OpenAMP",
                        RpmsgEchoTask,
                        RT_NULL,
                        OPENAMP_THREAD_STACK_SIZE,
                        OPENAMP_THREAD_PRIORITY,
                        OPENAMP_THREAD_TIMESLICE);

    if (tid == RT_NULL)
    {
        LOG_E("openamp thread create failed!");
        return -RT_ERROR;
    }

    rt_thread_startup(tid);

    return RT_EOK;
}

// INIT_PREV_EXPORT(creat_openamp_thread);

#endif
