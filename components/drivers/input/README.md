1. 启用
  将下面的宏定义写入rtconfig.h:
  #define RT_USING_INPUT
  #define INPUT_USING_TOUCH  //开启触摸功能
  
  备注：如果未开启组件自动初始化，需要手动初始化输入设备类驱动
  （如 int rt_tsdev_init(void)初始化触摸）

2. 驱动
2.1.1 注册底层驱动
  int rt_input_device_register(rt_input_t *dev, int devtype, const char *name);

  参数: devtype - 参见 input_devtype_t

2.1.2 报告事件
  触摸示例:
  /* 报告点击按下 */
  rt_input_key_report(dev, BTN_TOUCH, 1);
  rt_input_abs_report(dev, ABS_X, x); 
  rt_input_abs_report(dev, ABS_Y, y);
  rt_input_sync(dev);  //同步后驱动事件缓冲区中的内容将会提交给中间层

  /* 报告触点移动(如果有) */
  rt_input_abs_report(dev, ABS_X, x);
  rt_input_abs_report(dev, ABS_Y, y);
  rt_input_sync(dev);

  /* 报告点击抬起 */
  rt_input_key_report(dev, BTN_TOUCH, 0);
  rt_input_abs_report(dev, ABS_X, x);
  rt_input_abs_report(dev, ABS_Y, y);
  rt_input_sync(dev);

2.2 注册输入设备类驱动
  int rt_input_handler_register(struct input_handler *handler);

3. 输入系统框架图

   ----------------------
  |         应用         |
   ----------------------
  |    输入设备类驱动     |
  | ---- ----- ----- --- |
  | 触摸  键盘  鼠标 其他 |
   ---------------------
  |       核心层         |
   ---------------------
  |      底层驱动        |
   ---------------------

  对于那些应用层不用关心消息来自哪个硬件的输入设备（如 鼠标、键盘、触摸）
  ，类驱动可以只注册一个固定名称的设备（触摸为"touch"）。
  对于摇杆，类驱动可以在底层驱动注册时动态创建设备实例。

  核心层维护了两个链表：类驱动链表和底层驱动链表。当底层驱动注册时
  会在类驱动链表寻找是否有匹配的类驱动，如果找到则通知类驱动有设备接入。
  当类驱动注册时会到底层驱动链表寻找匹配的底层驱动，如果找到则通知类
  驱动有设备接入。

4. 数据结构
4.1 输入事件
  struct input_event
  {
    uint16_t type;
    uint16_t code;
    int value;
    uint32_t usec;
  };
  注：type和code的定义参见input_ev_code.h

  触摸和键盘设备会给应用报告struct input_event类型的数据。
  当type为EV_SYN code为SYN_REPORT时表示一组相关的事件报告结束。
  收到EV_SYN消息后value为本次事件的时间戳秒, usec为微秒。



注意事项：
  当用文件接口访问输入设备时可同时打开多个（
  都能读到相同的数据），用设备接口只能打开一次且只能非阻塞访问。
  