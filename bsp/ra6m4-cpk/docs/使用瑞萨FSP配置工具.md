## 在 MDK 中使用 FSP

1. 打开 MDK，选择 “Tools -> Customize Tools Menu…”
2. 点击 “new” 图标，添加一条自定义命令: RA Smart Configurator
3. Command 输入工具的安装路径， 点击“…”找到安装路径下的“rasc.exe”文件并选中 (setup_fsp_v3_1_0_rasc_ 安装目录下)
4. Initial Folder 输入参数: $P
5. Arguments 输入参数: --device $D --compiler ARMv6 configuration.xml
6. 点击 OK 保存命令“Tools -> RA smart Configurator”

![img](picture/customize.png)

7. 点击添加的命令打开配置工具：RA Smart Config

![image.png](picture/openrasc.png)

## UART

- 添加一个 UART 端口外设配置

![image.png](picture/rascuart.png)

![image.png](picture/rascuart1.png)