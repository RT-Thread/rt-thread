# RT-Thread Studio 工程导入说明

## 导入支持范围

芯片范围： STM32 系列。

工程格式：与 rt-thread/bsp/stm32 目录下格式相同。




## 如何导入

1. 更新 RT-Thread Studio 为最新版本；

2. 在项目资源管理器下，点击鼠标右键，选择导入；

   ![import_step_1](figures\import_step_1.png)

   

3. 选择 MDK/IAR 项目到工作空间， 点击下一步；

   ![import_step_2_3](figures\import_step_2_3.png)

   

4. 点击浏览， 选择工程目录下要导入的 MDK/IAR 工程，并输入工程名字；

   ![import_step_4_5_6](figures\import_step_4_5_6.png)

   

5. 点击完成， 工程导入完成。



## 导入异常处理

1. **Error : This project doesn't support import**

   请确保要导入的工程芯片型号为 STM32  系列。

2. **Error ：Can't find file: path**

    请确保 path 路径正常， 且该路径下所需文件存在。

3. **Error: get IAR version failed. Please update the IAR installation path in rtconfig.py!**

   打开工程目录下 rtconfig.py 文件 ， 修改 IAR 的 **EXEC_PATH** 。

    ```
    elif CROSS_TOOL == 'iar':
        PLATFORM    = 'iar'
        EXEC_PATH   = r'C:/Program Files (x86)/IAR Systems/Embedded 		 				       Workbench 8.0'
    ```

4. **IAR 工程导入 Studio 后， 不显示 RT-Thread Settings ？**

   与上面第 3 条处理方式一样，修改 IAR 路径，再重新导入。
   
   

## 导入后如何管理文件

### 添加文件

1. 在原 MDK/IAR 工程下添加文件
2. 删除 Studio 中已导入的工程
3. 再次导入

### 删除文件

1. 在原 MDK/IAR 工程下删除文件
2. 删除 Studio 中已导入的工程
3. 再次导入




## Studio 导入工程与创建工程的区别 

1. 导入工程在 Studio 显示的是虚拟文件， 创建的工程显示的文件为真实文件；
2. 导入工程不能直接在 Studio 下进行文件的添加，删除操作。




## 虚拟文件夹

 和一般文件夹的不同之处在于，虚拟文件夹并不是真实存在的文件夹，并没有真实的逻辑结构。显示的内容可能实际上是分散于若干个真实的文件夹中，虚拟文件夹只是起到了一个归纳和汇总的作用。

RT-Thread Sudio 的工程导入功能，就是基于虚拟文件夹的概念，所以不能直接在 Studio 中对文件进行操作， 需要在原 MDK/IAR 工程中对文件操作完成之后，再重新导入到 Studio 中。










