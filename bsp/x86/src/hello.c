
#include <stdio.h>
const char* g_str = "Hello World!";

static int a = 1234;
int b = 5678;

extern void rt_kprintf(const char* fmt,...);

int add(int a, int b)
{
    return a+b;
}

int main(int argc, char* argv[])
{
    int i;
    char str[32] = "Hello World\n";

    for(i=0; i<argc; i++)
    {
        printf("argv[%d]='%s'\n", i, argv[i]);
    }

    printf(str);

    printf("g_str address is %ph\n",g_str);
    puts(g_str);

    rt_kprintf("\nnative rt_kprintf a(%ph)=%d, b(%ph)=%d\n", &a, a, &b, b);

    printf("%d+%d=%d\n", 4, 5, add(4, 5));

    return 0xdeadbeef;
}

