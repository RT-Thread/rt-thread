# vconsole

当系统中存在多种通信链路时，可将控制台切换至不同的通信链路上。

## 功能

- 创建删除设备
- 切换控制台

## 使用概要

```c
dev = vconsole_create("vc0", outfunction); //创建一个设备对象，传入数据输出函数指针
old_dev = vconsole_switch(dev); //切换控制台

/* 使用控制台 */

vconsole_switch(old_dev); //切换至旧控制台
vconsole_delete(dev); //删除设备对象
```

## API 介绍

`rt_device_t vconsole_create(const char *name, vc_output_t out)`

创建一个设备对象，该对象可供控制台使用

| 参数 | 描述 | 说明 |
| ---- | ----| ---- |
| `name` |  设备名 | 与系统中其他设备不重名 |
| `out` | 输出函数 | 提供一个输出函数，用于控制台输出 |
| **返回** | **描述** | 
| `rt_device_t` | 设备对象 |

`rt_err_t vconsole_delete(rt_device_t device)`

删除设备对象，回收内存资源

| 参数 | 描述 | 说明 |
| ---- | ----| ---- |
| `device` |  设备对象 |  |
| **返回** | **描述** | 
| `rt_err_t` | RT_EOK 删除成功 |

> 只能删除未使用的，并且是 `vconsole_create` 函数创建的设备

`rt_device_t vconsole_switch(rt_device_t device)`

切换控制台到指定对象上。

| 参数 | 描述 | 说明 |
| ---- | ----| ---- |
| device | 设备对象 | |
| **返回** | **描述** | 
| `rt_device_t` | 旧的控制台设备对象 |

> 返回的旧设备对象，调用者保存，方便后续切换到旧的设备对象上。

`rt_size_t vconsole_input(rt_device_t device, const rt_uint8_t *buff, rt_size_t size)`

输出数据到设备对象上

| 参数 | 描述 | 说明 |
| ---- | ----| ---- |
| device | 设备对象 | |
| buff | 数据缓存指针 | |
| size | 数据缓存区大小 | |
| **返回** | **描述** | 
| `rt_size_t` | 实际接收的大小 |

只能将数据灌到 `vconsole_create` 创建的对象上。
