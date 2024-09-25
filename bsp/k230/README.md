# rt-smart canaan porting

## 下载依赖的软件包

在软件包无需变更的情况下只须执行一次
```
source ~/.env/env.sh
pkgs --update
```

## 将根文件系统编译进内核

为了方便测试，这里将根文件系统制作成CROMFS格式转换成C代码编译进内核。

1. 在 https://github.com/RT-Thread/userapps 页面下载riscv64预编译镜像
2. 解压后将其中的ext4.img挂载到一个目录中
```
sudo mount ext4.img dir
```
3. 删除其中一些不必要的文件以减小内核体积
```
du -ha                              # 查看文件大小
sudo rm -rf dir/www dir/usr/share/fonts dir/tc

```
4. 生成cromfs文件
工具位于 https://github.com/RT-Thread/userapps/tree/main/tools/cromfs
```
sudo ./cromfs-tool-x64 dir crom.img ./            # 将生成的cromfs_data.c放入applications目录
```

## 编译

### 一步完成
```
export RTT_EXEC_PATH=/mnt/e/tools/riscv64gc/bin # 你自己的编译器路径

scons -j8 all=1
```

### 分步完成
* 1. 编译RT-Thread
```
export RTT_EXEC_PATH=/mnt/e/tools/riscv64gc/bin # 你自己的编译器路径

scons -j8

```

* 2. 编译opensbi & 生成烧录文件
```
./mkfm.sh /mnt/e/tools/riscv64gc/bin/riscv64-unknown-linux-musl- # 你自己的编译器
```
此处会把`rtthread.bin`编译进opensbi


## 烧录rtt_system.bin

1. 参照 https://github.com/kendryte/k230_sdk 烧入预编译镜像
2. 通过另一个核上运行的linux烧录rtt
```
ifconfig eth0 up;ifconfig eth0 192.168.2.2;cd /tmp;tftp -r rtt_system.bin -g 192.168.2.20;dd if=rtt_system.bin of=/dev/mmcblk1p1;reboot

```

## 用uboot从sd卡fat分区加载rtt_system.bin

在`快起`特性关闭的情况下，从小核控制台进入uboot操作界面，输入如下命令：
```
fatload mmc 1:4 $ramdisk_addr rtt_system.bin;k230_boot mem $ramdisk_addr 0x$filesize

```

`备注`: 随后RT-Thread启动界面显示在大核控制台。
