
# Lwip Port

## 1. 概述

Lwip Port为开发者提供了一系列接口，驱动开发者在完成GMAC/XMAC 驱动之后，只需根据lwip要求的接口，将驱动内容填入，即可完成lwip port适配层功能。lwip port 会在初始化阶段，初始化协议栈，并且会根据用户传入的配置参数，并初始化netif参数。

## 2. 功能

1. 为开发者提供lwip功能与mac控制驱动耦合的相关接口
2. 统一后续mac控制器接入lwip 协议栈的方式
3. 简化mac 控制器适配lwip 的难度
4. 统一不同mac 控制器下应用程序
5. 提供上层用户配置mac 控制器的统一接口
6. 管理mac 控制器的状态（phy link status）
7. 管理lwip 中link up/down 状态
8. 提供多网卡检索功能

相关源文件为：
```
lwip_port
    ├── lwip_port.c
    └── lwip_port.h
```


## 3. 配置方法

默认配置已经保存在config中，用户可根据实际需要自行扩展，该部分操作参考readme即可

## 4. 应用示例

### [lwip port](../../../baremetal/example/network/lwip_startup/)

## 5. API参考

### 5.1. 用户数据结构

- lwip_port.h

```c
typedef struct
{
	u32 magic_code;		/* LWIP_PORT_CONFIG_MAGIC_CODE */
	char name[2];		/* Used to name netif */
	u32 driver_type;	/* driver type */
	u32 mac_instance;	/* mac controler id */
	u32 mii_interface;  /* LWIP_PORT_INTERFACE_XXX */
    u32 autonegotiation; /* 1 is autonegotiation ,0 is manually set */
    u32 phy_speed;  /* LWIP_PORT_SPEED_XXX */
    u32 phy_duplex; /* 1 is LWIP_PORT_FULL_DUPLEX,0 is LWIP_PORT_HALF_DUPLE*/
} UserConfig; /*用户初始化配置数据 */

typedef struct
{
	void (*eth_input)(struct netif *netif);
	enum lwip_port_link_status (*eth_detect)(struct netif *netif);
	void (*eth_deinit)(struct netif *netif);
	void (*eth_start)(struct netif *netif);
} LwipPortOps; /*  lwip port 网卡注册函数*/

struct LwipPort {
	void *state; /* mac controler */
	LwipPortOps ops;
}; /*lwip port控制数据 */
```

### 5.2  错误码定义
无
### 5.3. 用户API接口

#### LwipPortAdd
- 作为 lwip 的netif_add 的一个封装，开发者可以通过此接口对不同mac 控制器进行初始化

```c
struct netif * LwipPortAdd(struct netif *netif,
ip_addr_t *ipaddr, ip_addr_t *netmask, ip_addr_t *gw,
unsigned char *mac_ethernet_address,
UserConfig *user_config, u32 dhcp_en);
```

Note:

- begin_addr end_addr 指向为内存池指定的缓冲区的起止地址

Input:

- {struct netif } *netif, 需要初始化的网卡对象
- {ip_addr_t} *ipaddr, 分配给网卡的IP初始地址
- {ip_addr_t} *netmask, 分配给掩码的IP初始地址
- {ip_addr_t} *gw, 分配给网关的IP初始地址
- {unsigned char } *mac_ethernet_address, 分配给网卡的mac初始地址
- {UserConfig} *user_config, 网卡初始化所需要的用户配置数据
- {u32} dhcp_en, 网卡是否使用dhcp服务控制数据
Return:

- {struct netif *} 返回初始化成功的netif网卡对象，返回NULL表示初始化失败

#### LwipPortInput

-  lwip协议栈获取驱动数据包的接口，客户可以使用此接口在裸跑中运行lwip 协议栈

```c
void LwipPortInput(struct netif *netif)
```

Note:

- 需要初始化后才能调用，调用此函数后，lwip会获取网卡收到的数据包并进行处理

Input:

- {struct netif } *netif 已经实例化的网卡netif  

Return:

- 无

#### LwipPortStop

- 使用此接口可以达到两个目标：
1. 关闭当前mac 控制器工作状态
2. 将netif 移除lwip 协议栈


```c
void LwipPortStop(struct netif *netif);
```

Note:

- 需要初始化后才能调用，调用该函数后，网卡将停止功能，若想继续工作需要重新进行网卡初始化

Input:

- {struct netif } *netif 已经实例化的网卡netif  

Return:

- 无
#### LwipPortGetByName

- 通过netif名字找到netif对象

```c
struct netif* LwipPortGetByName(const char *name);
```

Note:

- 需要初始化后才能调用，调用该函数将在已经初始化的netif链表中寻找name字段相对应的netif，并返回该netif

Input:

- {const char} *name 网卡名字

Return:

- {struct netif*} 寻找到的netif对象，如果未找到返回NULL

#### LwipPortDhcpSet

- 网卡dhcp控制

```c
void LwipPortDhcpSet(struct netif *netif, boolean is_enabled);
```

Note:

- 需要初始化后才能调用，调用该函数可以打开或关闭网卡的dhcp服务

Input:

- {struct netif} *netif 网卡对象
- {boolean} is_enabled DHCP使能控制参数


Return:

- 无

