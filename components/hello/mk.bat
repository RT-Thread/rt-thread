set PATH="E:\Program Files\CodeSourcery\Sourcery G++ Lite\bin";%PATH%
arm-none-eabi-gcc -c hello.c -o hello.o -DRT_MODULE "-I..\..\include" "-I..\..\bsp\mini2440"
arm-none-eabi-gcc -o hello.mo -r -d -e rtm_main -nostdlib hello.o