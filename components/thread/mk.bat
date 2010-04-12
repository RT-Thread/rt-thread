set PATH="E:\Program Files\CodeSourcery\Sourcery G++ Lite\bin";%PATH%
arm-none-eabi-gcc -c module_thread_dynamic.c -o module_thread_dynamic.o -DRT_MODULE "-I..\..\include" "-I..\..\bsp\mini2440"
arm-none-eabi-gcc -o dynamic.mo -r -d -e rtm_main -nostdlib module_thread_dynamic.o