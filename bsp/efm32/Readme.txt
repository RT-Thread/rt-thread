 - To test the ELM FatFs:
1. Please turn on the following defines in "rtconfig.h":
      #define EFM32_USING_SPISD
      #define RT_USING_DFS
      #define RT_USING_DFS_ELMFAT
      #define DFS_*
2. copy "bsp/efm32/copy_this_file_dfs_elm.c" to "components/dfs/filesystems/elmfat/"
3. rename it to "dfs_elm.c" replacing the original file
4. and then compile

 - To test the lwIP:
1. You should have a ENC28J60 Ethernet controller and connect it with your board properly
2. Please turn on the following defines in "rtconfig.h":
      #define EFM32_USING_ETHERNET
      #define RT_USING_LWIP
      #RT_LWIP_*
3. and then compile