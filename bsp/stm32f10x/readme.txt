-- cn --
按需要生成工程文件:
1. 修改当前文件夹内 rtconfig.py :
CROSS_TOOL='keil'           #使用的工具链.
STM32_TYPE = 'STM32F10X_HD' #STM32对应的型号.
EXEC_PATH 	= 'C:/Keil' #Keil安装路径.
IAR_PATH 	= 'C:/Program Files/IAR Systems/Embedded Workbench 6.0 Evaluation' #IAR安装路径.
2. 修改当前文件夹内 rtconfig.h 配置需要的功能.
3. MDK：在当前文件夹内执行 scons --target=mdk  或 scons --target=mdk4 生成MDK 4工程文件 project.uvproj
        或在当前文件夹内执行 scons --target=mdk5 生成MDK 5工程文件 project.uvprojx
   IAR：在当前文件夹内执行 scons --target=iar 生成IAR工程 project.eww.
4. 将bsp\stm32f10x\drivers内board.h中STM32_SRAM_SIZE的值修改为与芯片SRAM大小一致.

note: 需要安装 python 2.7,scons.
      更多介绍请参考http://www.rt-thread.org/book/13.html
                  和http://www.rt-thread.org/dokuwiki/doku.php?id=%E9%85%8D%E7%BD%AErt-thread%E5%BC%80%E5%8F%91%E7%8E%AF%E5%A2%83

-- en --
Generate project files as needed:
1. Modify the files in the current folder:
CROSS_TOOL='keil'           #The tool chain in use.
STM32_TYPE = 'STM32F10X_HD' #The type of stm32.
EXEC_PATH 	= 'C:/Keil' #The installation path of the Keil.
IAR_PATH 	= 'C:/Program Files/IAR Systems/Embedded Workbench 6.0 Evaluation' #The installation path of the IAR.
2. Configure the required functionality by modifying rtconfig.h in the current folder.
3. MDK:Execute the scons --target=mdk or scons --target=mdk4 in the current folder to generate the MDK4 project project.uvproj.
       Or execute the scons --target=mdk5 in the current folder to generate the MDK5 project project.uvprojx.
   IAR:Execute the scons --target=iar in the current folder to generate the IAR project project.eww.
4. Change the value of STM32_SRAM_SIZE in board.h(bsp\stm32f10x\drivers) to match the chip SRAM size.

note:Need to install python 2.7 and scons.
     For more information, please refer to the website http://www.rt-thread.org/book/13.html
                                               and     http://www.rt-thread.org/dokuwiki/doku.php?id=%E9%85%8D%E7%BD%AErt-thread%E5%BC%80%E5%8F%91%E7%8E%AF%E5%A2%83


