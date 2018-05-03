 - To test the low power mode:

 - To test the ELM FatFs:
1. copy "bsp/efm32/copy_this_file_shell.c" to "components/finsh/"
2. rename it to "shell.c" replacing the original file
3. and then compile

 - To test the lwIP:
1. You should have a ENC28J60 Ethernet controller and connect it with your board properly
2. Please turn on the following defines in "rtconfig.h":
      #define EFM32_USING_ETHERNET
      #define RT_USING_LWIP
      #RT_LWIP_*
3. please also turn on the following define to use simple http server
      #define EFM32_USING_ETH_HTTPD
   or turn on the following defines to use EFM32 Ethernet utility functions (due to memory limitation, you may not turn on both)
      #define EFM32_USING_ETH_UTILS
      #define hostName 		"onelife.dyndns.org"	/* Please change to your own host name */
      #define userPwdB64 	"dXNlcjpwYXNzd2Q="	/* Please change to your own user name and password (base 64 encoding) */
4. and then compile