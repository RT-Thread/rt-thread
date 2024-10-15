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

```
export RTT_EXEC_PATH=/mnt/e/tools/riscv64gc/bin # 你自己的编译器路径

scons -j8
```
