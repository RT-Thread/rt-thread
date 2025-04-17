
# RA BSP 说明

RA 系列 BSP 目前支持情况如下表所示：

| **BSP 文件夹名称**                       | **开发板名称**                                   |
| :--------------------------------------- | :----------------------------------------------- |
| **RA6 系列**                             |                                                  |
| [ebf_qi_min_6m5](ebf_qi_min_6m5)         | 野火 启明6 开发板                                |
| [ra6m4-cpk](ra6m4-cpk)                   | Renesas 官方 CPK-RA6M4 开发板                    |
| [ra6m4-iot](ra6m4-iot)                   | Renesas 官方 IOT-RA6M4 开发板                    |
| [ra6m3-ek](ra6m3-ek)                     | Renesas 官方 RA6M3-EK 开发板                     |
| [ra6m3-hmi-board](ra6m3-hmi-board)       | Renesas 联合 RT-Thread RA6M3-HMI-Board 开发板    |
| **RA4 系列**                             |                                                  |
| [ra4m2-eco](ra4m2-eco)                   | Renesas 官方 RA-Eco-RA4M2 开发板                 |
| **RA2 系列**                             |                                                  |
| [ra2l1-cpk](ra2l1-cpk)                   | Renesas 官方 CPK-RA2L1 开发板                    |
| **RA8 系列**                             |                                                  |
| [ra8m1-ek](ra8m1-ek)                     | Renesas 官方 EK-RA8M1 开发板                     |
| [ra8d1-ek](ra8d1-ek)                     | Renesas 官方 EK-RA8D1 开发板                     |
| [ra8d1-vision-board](ra8d1-vision-board) | Renesas 联合 RT-Thread RA8D1-Vision-Board 开发板 |
| **RZ 系列**                             |                                                  |
| [rzt2m_rsk](rzt2m_rsk)                   | Renesas 官方 RSK-RZT2M 开发板                    |
| [rzn2l_rsk](rzn2l_rsk)                   | Renesas 官方 RSK-RZN2L 开发板                    |

可以通过阅读相应 BSP 下的 README 来快速上手，如果想要使用 BSP 更多功能可参考 docs 文件夹下提供的说明文档，如下表所示：

| **BSP 使用教程** | **简介**                                          |
|:-------------------- |:------------------------------------------------- |
| [外设驱动使用教程](docs/RA系列BSP外设驱动使用教程.md) | 讲解 BSP 上更多外设驱动的使用方法 |
| [外设驱动介绍与应用](docs/RA系列驱动介绍.md) | 讲解 RA 系列 BSP 驱动的支持情况，以及如何利用驱动框架开发应用程序 |
| [使用 FSP 配置外设驱动](docs/RA系列使用FSP配置外设驱动.md) | 介绍如何使用 FSP 工具添加和配置外设 |
| [瑞萨RA2L1开发实践指南](https://docs.qq.com/doc/DQktJWmpBZkNiTnh6) | 介绍基于 RA2L1 如何添加和配置外设 |
| [瑞萨RA6m3开发实践指南](https://docs.qq.com/doc/DQmVYUEN1dHVyd0hi) | 介绍基于 RA6M3 如何添加和配置外设 |
| **BSP 制作与提交** | **简介**                                     |
| [BSP 制作教程](docs/RA系列BSP制作教程.md) | 讲解 RA 系列 BSP 的制作方法，以及在制作 BSP 和提交 BSP 时应当遵守的规范 |
| [外设驱动添加指南](docs/RA系列外设驱动添加指南.md) | 讲解 BSP 添加更多设备驱动的方法 |

English documents：

| **BSP Tutorial** | **Introduction**                              |
|:-------------------- |:------------------------------------------------- |
| [BSP Peripheral Driver Tutorial of RA Series](docs/BSP_Peripheral_Driver_Tutorial_of_RA_Series.md) | Explains how to use more peripheral drivers on the BSP |
| [Introduction to RA Series Drives](docs/Introduction_to_RA_Series_Drives.md) | Explains the support of RA series BSP drivers and how to develop applications using the driver framework |
| [RA Series Uses FSP to Configure Peripheral Drivers](docs/RA_Series_Uses_FSP_to_Configure_Peripheral_Drivers.md) | Introduces how to add and configure peripherals using the FSP tool |
| **BSP Production and Submission** | **Introduction**                         |
| [Building a BSP for the RA Series Dev Board](docs/Building_a_BSP_for_the_RA_Series_Dev_Board.md) | Explains how the RA series BSPs are created and the specifications to be followed when creating and submitting BSPs |
| [Peripheral Driver Addition Guide of RA Series](docs/Peripheral_Driver_Addition_Guide_of_RA_Series.md) | Explains how to add more device drivers to BSP |
