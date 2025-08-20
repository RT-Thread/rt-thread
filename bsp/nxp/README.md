# NXP BSP 支持说明

NXP 系列 BSP 目前支持情况如下表所示：

| **BSP 文件夹名称**                                    | **开发板名称**                           |
|:------------------------------------------------ |:----------------------------------- |
| **MCXN 系列**                                     |                                     |
| [frdm-mcxn947](mcx/mcxn/frdm-mcxn947) | NXP 官方 FRDM-MCXN947 开发板 |
| [frdm-mcxn236](mcx/mcxn/frdm-mcxn236) | NXP 官方 FRDM-MCXN236 开发板 |
| **MCXA 系列** |  |
| [frdm-mcxa153](mcx/mcxa/frdm-mcxa153) | NXP 官方 FRDM-MCXA153 开发板 |
| [frdm-mcxa156](mcx/mcxa/frdm-mcxa156) | NXP 官方 FRDM-MCXA156 开发板 |
| [frdm-mcxa346](mcx/mcxa/frdm-mcxa346) | NXP 官方 FRDM-MCXA346 开发板 |
| [frdm-mcxa344](mcx/mcxa/frdm-mcxa344) | NXP 官方 FRDM-MCXA344 开发板 |
| **MCXC 系列** |  |
| [frdm-mcxc444](mcx/mcxc/frdm-mcxc444) | NXP 官方 FRDM-MCXC444 开发板 |
| **LPC 系列**                                      |                                     |
| [lpc43xx](lpc/lpc43xx)                           | NXP LPC43xx 系列开发板                   |
| [lpc55sxx](lpc/lpc55sxx)                         | NXP LPC55Sxx 系列开发板                  |
| [lpc176x](lpc/lpc176x)                           | NXP LPC176x 系列开发板                   |
| [lpc178x](lpc/lpc178x)                           | NXP LPC178x 系列开发板                   |
| [lpc408x](lpc/lpc408x)                           | NXP LPC408x 系列开发板                   |
| [lpc824](lpc/lpc824)                             | NXP LPC824 开发板                       |
| [lpc1114](lpc/lpc1114)                           | NXP LPC1114 开发板                      |
| [lpc2148](lpc/lpc2148)                           | NXP LPC2148 开发板                      |
| [lpc2478](lpc/lpc2478)                           | NXP LPC2478 开发板                      |
| [lpc5410x](lpc/lpc5410x)                         | NXP LPC5410x 系列开发板                  |
| [lpc54114-lite](lpc/lpc54114-lite)               | NXP LPC54114-Lite 开发板                |
| [lpc54608-lpcxpresso](lpc/lpc54608-lpcxpresso)   | NXP 官方 LPC54608-LPCXpresso 开发板     |

另外,我们还提供了一些热门开发板的上手说明: 

* [NXP FRDM-MCXN947上手指南](https://www.rt-thread.org/document/site/#/rt-thread-version/rt-thread-standard/tutorial/quick-start/frdm_mcxn947/quick-start)
* [NXP FRDM-MCXA156上手指南](https://www.rt-thread.org/document/site/#/rt-thread-version/rt-thread-standard/tutorial/quick-start/frdm_mcxa156/quick-start)

## 注意事项

- MCX 系列是 NXP 最新推出的 MCU 系列，具有高性能和低功耗特性
- 部分老旧系列（LPC/Kinetis/i.MX RT）正在逐步迁移和更新中
- 建议优先选择 MCX 系列进行新项目开发
- 各系列 BSP 的具体支持功能请参考对应目录下的 README 文档
