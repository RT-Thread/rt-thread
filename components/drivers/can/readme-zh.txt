说明: 
本驱动完成了can控制器硬件抽象
一 CAN Driver 注册
	Can driver注册需要填充以下几个数据结构：
	1、struct can_configure
	{
		rt_uint32_t baud_rate;
		rt_uint32_t msgboxsz;
		rt_uint32_t sndboxnumber;
		rt_uint32_t mode      :8;
		rt_uint32_t privmode  :8;
		rt_uint32_t reserved  :16;
		#ifdef RT_CAN_USING_LED
		const struct rt_can_led* rcvled;
		const struct rt_can_led* sndled;
		const struct rt_can_led* errled;
		#endif  /*RT_CAN_USING_LED*/
		rt_uint32_t ticks;
	#ifdef RT_CAN_USING_HDR
		rt_uint32_t maxhdr;
	#endif
	};
	struct can_configure 为can驱动的基本配置信息:
	baud_rate :
		enum CANBAUD
		{
			CAN1MBaud=0,    // 1 MBit/sec
			CAN800kBaud,    // 800 kBit/sec
			CAN500kBaud,    // 500 kBit/sec
			CAN250kBaud,    // 250 kBit/sec
			CAN125kBaud,    // 125 kBit/sec
			CAN100kBaud,    // 100 kBit/sec
			CAN50kBaud,     // 50 kBit/sec
			CAN20kBaud,     // 20 kBit/sec
			CAN10kBaud      // 10 kBit/sec
		};
		配置Can的波特率。
	msgboxsz : Can接收邮箱缓冲数量，本驱动在软件层开辟msgboxsz个接收邮箱。
	sndboxnumber : can 发送通道数量，该配置为Can控制器实际的发送通道数量。 
	mode ：
		#define RT_CAN_MODE_NORMAL 0		正常模式
		#define RT_CAN_MODE_LISEN 1		只听模式
		#define RT_CAN_MODE_LOOPBACK 2		自发自收模式
		#define RT_CAN_MODE_LOOPBACKANLISEN 3	自发自收只听模式
		配置Can 的工作状态。
	privmode :
		#define RT_CAN_MODE_PRIV 0x01 		处于优先级模式，高优先级的消息优先发送。
		#define RT_CAN_MODE_NOPRIV 0x00
		配置Can driver的优先级模式。
	#ifdef RT_CAN_USING_LED
	const struct rt_can_led* rcvled;
	const struct rt_can_led* sndled;
	const struct rt_can_led* errled;
	#endif  /*RT_CAN_USING_LED*/
	配置can led信息, 当前can驱动的led使用了 pin驱动，
	开启RT_CAN_USING_LED时要确保当前系统已实现pin驱动。
	rt_uint32_t ticks : 配置Can driver timer周期。
	#ifdef RT_CAN_USING_HDR
		rt_uint32_t maxhdr;
	#endif
	如果使用硬件过滤，则开启RT_CAN_USING_HDR, maxhdr 为Can控制器过滤表的数量。
	2、struct rt_can_ops
	{
		rt_err_t (*configure)(struct rt_can_device *can, struct can_configure *cfg);
		rt_err_t (*control)(struct rt_can_device *can, int cmd, void *arg);
		int (*sendmsg)(struct rt_can_device *can, const void* buf, rt_uint32_t boxno);
		int (*recvmsg)(struct rt_can_device *can,void* buf, rt_uint32_t boxno);
	};
	struct rt_can_ops 为要实现的特定的can控制器操作。
	rt_err_t (*configure)(struct rt_can_device *can, struct can_configure *cfg);
	configure根据配置信息初始化Can控制器工作模式。
	rt_err_t (*control)(struct rt_can_device *can, int cmd, void *arg);
	control 当前接受以下cmd参数：
		#define RT_CAN_CMD_SET_FILTER      0x13
		#define RT_CAN_CMD_SET_BAUD        0x14
		#define RT_CAN_CMD_SET_MODE        0x15
		#define RT_CAN_CMD_SET_PRIV        0x16
		#define RT_CAN_CMD_GET_STATUS      0x17
		#define RT_CAN_CMD_SET_STATUS_IND  0x18
	int (*sendmsg)(struct rt_can_device *can, const void* buf, rt_uint32_t boxno);
	sendmsg向Can控制器发送数，boxno为发送通道号。
	int (*recvmsg)(struct rt_can_device *can,void* buf, rt_uint32_t boxno);
	recvmsg从Can控制器接收数据，boxno为接收通道号。
	struct rt_can_device
	{
		struct rt_device          parent;

		const struct rt_can_ops *ops;
		struct can_configure   config;
		struct rt_can_status   status;
		rt_uint32_t timerinitflag;
		struct rt_timer timer;
		struct rt_can_status_ind_type status_indicate;
	#ifdef RT_CAN_USING_HDR
		struct rt_can_hdr* hdr;
	#endif
		void *can_rx;
		void *can_tx;
	};
	填充完成后，便可调用rt_hw_can_register完成can驱动的注册。
二、 CAN Driver 的添加：
	要添加一个新的Can驱动，至少要完成以下接口。
	1、struct rt_can_ops
	{
		rt_err_t (*configure)(struct rt_can_device *can, struct can_configure *cfg);
		rt_err_t (*control)(struct rt_can_device *can, int cmd, void *arg);
		int (*sendmsg)(struct rt_can_device *can, const void* buf, rt_uint32_t boxno);
		int (*recvmsg)(struct rt_can_device *can,void* buf, rt_uint32_t boxno);
	};
	2、 rt_err_t (*control)(struct rt_can_device *can, int cmd, void *arg);
	接口的
		#define RT_CAN_CMD_SET_FILTER      0x13
		#define RT_CAN_CMD_SET_BAUD        0x14
		#define RT_CAN_CMD_SET_MODE        0x15
		#define RT_CAN_CMD_SET_PRIV        0x16
		#define RT_CAN_CMD_GET_STATUS      0x17
		#define RT_CAN_CMD_SET_STATUS_IND  0x18
	若干命令。
	3、can口中断，要完接收，发送结束，以及错误中断。
		#define RT_CAN_EVENT_RX_IND          0x01    /* Rx indication */
		#define RT_CAN_EVENT_TX_DONE         0x02    /* Tx complete   */
		#define RT_CAN_EVENT_TX_FAIL         0x03    /* Tx complete   */
		#define RT_CAN_EVENT_RX_TIMEOUT      0x05    /* Rx timeout    */
		#define RT_CAN_EVENT_RXOF_IND        0x06    /* Rx overflow */
		中断产生后，调用rt_hw_can_isr(struct rt_can_device *can, int event)
		进入相应的操作，其中接收发送中断的event，最低8位为上面的事件，16到24位为通信通道号。
	一个作为一个例子，参见bsp/stm32f10x/driver下的bxcan.c 。
三、CAN Driver的使用：
	一个使用的例子，参数bsp/stm32f10x/applications下的canapp.c
四、当前Can驱动，没有实现轮模式，采用中断模式，bxcan驱动工作在loopback模式下的时候不能读数据。

五、当前Can驱动，在stm32f105上测试，暂无问题。
