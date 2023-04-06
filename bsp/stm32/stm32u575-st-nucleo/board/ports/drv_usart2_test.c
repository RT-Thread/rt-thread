/*
* 程序清单：这是⼀个 串⼝ 设备使⽤例程
* 例程导出了 uart_sample 命令到控制终端
* 命令调⽤格式：uart_sample uart2
* 命令解释：命令第⼆个参数是要使⽤的串⼝设备名称，为空则使⽤默认的串⼝设备
* 程序功能：通过串⼝输出字符串"hello RT-Thread!"，然后错位输出输⼊的字符
*/
#include <rtthread.h>
#define SAMPLE_UART_NAME  "uart2"
/* ⽤于接收消息的信号量 */
static struct rt_semaphore rx_sem;
static rt_device_t serial;
/* 接收数据回调函数 */
static rt_err_t uart_input(rt_device_t dev, rt_size_t size)
{
		/* 串⼝接收到数据后产⽣中断，调⽤此回调函数，然后发送接收信号量 */
		rt_sem_release(&rx_sem);
		return RT_EOK;
}
static void serial_thread_entry(void *parameter)
{
			char ch;
			while (1)
			{
				/* 从串⼝读取⼀个字节的数据，没有读取到则等待接收信号量 */
				while (rt_device_read(serial, -1, &ch, 1) != 1)
				{
				/* 阻塞等待接收信号量，等到信号量后再次读取数据 */
					rt_sem_take(&rx_sem, RT_WAITING_FOREVER);
				}
				/* 读取到的数据通过串⼝错位输出 */
				ch = ch + 1;
				rt_device_write(serial, 0, &ch, 1);
				}
}
static int uart_sample()
{
		 rt_err_t ret = RT_EOK;
		 char uart_name[RT_NAME_MAX];
		 char str[] = "hello RT-Thread!\r\n";
		 
		 rt_strncpy(uart_name, SAMPLE_UART_NAME, RT_NAME_MAX);
		 /* 查找系统中的串⼝设备 */
		 serial = rt_device_find(SAMPLE_UART_NAME);
		 if (!serial)
		 {
		 rt_kprintf("find %s failed!\n", uart_name);
		 return RT_ERROR;
		 }
		 /* 初始化信号量 */
		 rt_sem_init(&rx_sem, "rx_sem", 0, RT_IPC_FLAG_FIFO);
		 /* 以中断接收及轮询发送模式打开串⼝设备 */
		 rt_device_open(serial, RT_DEVICE_FLAG_INT_RX);
		 /* 设置接收回调函数 */
		 rt_device_set_rx_indicate(serial, uart_input);
		 /* 发送字符串 */
		 rt_device_write(serial, 0, str, (sizeof(str) - 1));
		 /* 创建 serial 线程 */
		 rt_thread_t thread = rt_thread_create("serial", serial_thread_entry, RT_NULL, 1024, 25, 10);
		 /* 创建成功则启动线程 */
		 if (thread != RT_NULL)
		 {
				rt_thread_startup(thread);
		 }
		 else
		 {
		 ret = RT_ERROR;
		 }
		 return ret;
}
INIT_APP_EXPORT(uart_sample);

