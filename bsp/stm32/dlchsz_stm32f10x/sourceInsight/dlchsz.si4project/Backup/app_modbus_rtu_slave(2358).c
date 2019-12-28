#include "app_modbus_rtu_slave.h"

#define DBG_SECTION_NAME    "app_modbus_rtu_slave"
#define DBG_LEVEL           DBG_LOG
#include <rtdbg.h>

static void __modbus_rtu_slave_init(void);
static void __modbus_rtu_slave_thread(void *para);

static void __modbus_rtu_slave_init(void) {
    rt_thread_t tid;
    
    //创建modbus_rtu_slave线程
    
    
    
}

static void test_thread(void *param)
{
//    uint16_t tab_reg[64] = {0};
//    modbus_t *ctx = RT_NULL;
//    ctx = modbus_new_rtu("/dev/uart1", 115200, 'N', 8, 1);
//    modbus_rtu_set_serial_mode(ctx, MODBUS_RTU_RS485);
//    modbus_rtu_set_rts(ctx, RS485_RE, MODBUS_RTU_RTS_UP);
//    modbus_set_slave(ctx, 3);
//    modbus_connect(ctx);
//    modbus_set_response_timeout(ctx, 0, 1000000);
//    int num = 0;
//    while (1)
//    {
//        memset(tab_reg, 0, 64 * 2);
//        int regs = modbus_read_registers(ctx, 0, 20, tab_reg);
//        printf("-------------------------------------------\n");
//        printf("[%4d][read num = %d]", num, regs);
//        num++;
//        int i;
//        for (i = 0; i < 20; i++)
//        {
//            printf("<%#x>", tab_reg[i]);
//        }
//        printf("\n");
//        printf("-------------------------------------------\n");
//        rt_thread_mdelay(5000);
//    }
//    //7-关闭modbus端口
//    modbus_close(ctx);

//    //8-释放modbus资源
//    modbus_free(ctx);
    modbus_t *ctx = NULL;
    modbus_mapping_t *mb_mapping = NULL;
    int rc;
    int use_backend;
    //初始化modbus rtu
    ctx = modbus_new_rtu("/dev/uart1", 115200, 'N', 8, 1);
    
    //设定从设备地址
    modbus_rtu_set_serial_mode(ctx, MODBUS_RTU_RS485);
    modbus_rtu_set_rts(ctx, RS485_RE, MODBUS_RTU_RTS_UP);
//    modbus_set_debug(ctx, 1);
    modbus_set_slave(ctx, 1);
    //modbus连接
    modbus_connect(ctx);
    //寄存器map初始化
    mb_mapping = modbus_mapping_new(0, 0,
                                    MODBUS_MAX_READ_REGISTERS, MODBUS_MAX_WRITE_REGISTERS);
    if (mb_mapping == NULL) {
        rt_kprintf("Failed to allocate the mapping: %s\n",
                   modbus_strerror(errno));
        modbus_free(ctx);
        return;
    }
 
   //初始几个寄存器
   p_data_rtu = (struct data_rtu *)mb_mapping->tab_registers;
//   mb_mapping->tab_registers[0] = 1;
//   mb_mapping->tab_registers[1] = 2;
//   mb_mapping->tab_registers[2] = 3;
//   mb_mapping->tab_registers[3] = 4;
//   mb_mapping->tab_registers[4] = 5;
//   mb_mapping->tab_registers[5] = 6;
//   mb_mapping->tab_registers[6] = 7;
//   mb_mapping->tab_registers[7] = 8;
//   mb_mapping->tab_registers[8] = 9;
//   mb_mapping->tab_registers[9] = 10;
//    mb_mapping->tab_input_registers[0] = 0x33;
   //循环
   while( 1 ){
        uint8_t query[MODBUS_TCP_MAX_ADU_LENGTH];
        //轮询接收数据，并做相应处理
        rc = modbus_receive(ctx, query);
        if (rc > 0) {
            modbus_reply(ctx, query, rc, mb_mapping);
        } else if (rc  == -1) {
            /* Connection closed by the client or error */
            rt_kprintf("Quit the loop: %s\n", modbus_strerror(errno));
        }
    }
 
    rt_kprintf("Quit the loop: %s\n", modbus_strerror(errno));
 
    modbus_mapping_free(mb_mapping);
    /* For RTU, skipped by TCP (no TCP connect) */
    modbus_close(ctx);
    modbus_free(ctx);

    
}

static int rtu_test_init(void)
{
    rt_pin_mode(RS485_RE, PIN_MODE_OUTPUT);
    rt_thread_t tid;
    tid = rt_thread_create("test",
                           test_thread, RT_NULL,
                           2048,
                           12, 10);
    if (tid != RT_NULL)
        rt_thread_startup(tid);
    return RT_EOK;
}
INIT_APP_EXPORT(rtu_test_init);