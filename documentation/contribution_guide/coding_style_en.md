                           RT-Thread Coding Style

This is an developing instruction for RT-Thread developers. As an open source
software, RT-Thread is done by the cooperation of different people. This
document is a guide for RT-Thread developers and please obey it if you are.
RT-Thread users could also get to know some conventions in the code through it
and thus easier to understand the implementations of RT-Thread.


1. Directory Naming

In normal conditions, please name directories in lower-case. Directories should
have descriptive names. For example, the port of a chip should be composed of
the name of the chip and the category of the chip. Directories under components/
should stand for what the component does.


2. File Naming

In normal conditions, please name files in lower-case. If the file is
referencing other places, it can have the original name. To avoid naming
collision, do not use general names or the names that are frequently used.


3. Header Files

To avoid include the same header file for multiple times, you need to define a
symbol like this:

    #ifndef __FILE_H__
    #define __FILE_H__
    /* header file content */
    #endif

The symbol should begin and end with "__" to avoid naming collision. The words
of the file name should be connected by "_".


4. Header File Comments

In every header file, there should be copyright information and Change Log
record like this:

    /*
    * Copyright (c) 2006-2020, RT-Thread Development Team
    *
    * SPDX-License-Identifier: Apache-2.0
    *
    * Change Logs:
    * Date           Author       Notes
    * 2006-03-18     Bernard      the first version
    * 2006-04-26     Bernard      add semaphore APIs
    */

5. Structure Defines

Please name structures in lower-case and connect words with "_". For example:

    struct rt_list_node
    {
        struct rt_list_node *next;
        struct rt_list_node *prev;
    };

Braces should have their own lines and the members should be defines with
indent.

The names of type defines such like structure types should be the structure name
plus "_t". For example:

    typedef struct rt_list_node rt_list_t;


In order to be easily referenced, the types of objects in kernel is pointer. For
example:

    typedef struct rt_timer* rt_timer_t;


6. Macros

In RT-Thread, please use upper-case names for macro definitions. Words are
connected by "_". Like:

    #define RT_TRUE                         1


7. Function Naming and Declaration

Please name functions in lower-case and separate words with "_". API provided to
upper application should be declared in header files. If the function don't have
parameters, it should be declared as void:

    rt_thread_t rt_thread_self(void);


8. Commenting

Please use English to comment. There shouldn't be too much comments and the
comments should describe what does the code do. And it should describe how the
complicated algorithm works. Comments to statements should be placed before them
or right of them. Anther places are illegal.


9. Indent

Please use TAB or 4 spaces to indent. It's preferred to use 4 spaces. If no
other special meanings, the indent should begin right after "{":

    if (condition)
    {
        /* others */
    }

The only one exception is switch. In switch-case statements, "case" should be
aligned with "switch":

    switch (value)
    {
    case value1:
        break;
    }

"case" is aligned with "switch", the following code block should be indented.


10. Braces and Spaces

For ease of reading, it is advised that braces should occupy the whole line
instead of following other statements. Like:

    if (condition)
    {
        /* others */
    }

When matching braces have their own lines, the reader would identify the code
blocks easily.

There should be a space before parentheses when it's not a function call. For
example:

    if (x <= y)
    {
        /* others */
    }

    for (index = 0; index < MAX_NUMBER; index ++)
    {
        /* others */
    }

In expressions, there should be a space between most binary and ternary
operators and the strings. No spaces around(inside) parentheses, like:

    if ( x <= y )
    {
        /* other */
    }

This is a bad practice.


11. trace, log Informations

In RT-Thread, rt_kprintf is a commonly used logging routine. In RT-Thread
rt_kprintf is implemented as a polling, non-interrupting string output. It is
suitable in "instant" situations such as interrupt context. The polling method
would have influence to the timing sequence of the log output.

It is not recommended to use rt_kprintf frequently. Unless you are aware of that
it's not a big deal to run slower.

Logging should be off by default and can be turned on by a switch(e.g. a
variable or a macro). When logging, it should be easy to understand and easy to
determine where the problem is.


12. Functions

Functions in kernel should be K.I.S.S. If the function is too long, you should
split it into smaller ones and make each of them simplified and easy to
understand.


13. Objects

The kernel of RT-Thread uses object-oriented tech in C. The naming convention
is: structure names are the object names, object names + verb phrases are the
method names of objects:

    struct rt_timer
    {
        struct rt_object parent;
        /* other fields */
    };
    typedef struct rt_timer* rt_timer_t;

The definition of structure rt_timer stands for the object definition of timer
object.

    rt_timer_t rt_timer_create(const char* name,
        void (*timeout)(void* parameter), void* parameter,
        rt_tick_t time, rt_uint8_t flag);
    rt_err_t rt_timer_delete(rt_timer_t timer);
    rt_err_t rt_timer_start(rt_timer_t timer);
    rt_err_t rt_timer_stop(rt_timer_t timer);

rt_timer + verb phrase stands for the method that could be used on timer object.

When creating a new object, think twice on memory allocations: whether a static
object could be created or it could only created dynamically on heap.

14. Use astyle to format the code automatically
parameters: --style=allman
            --indent=spaces=4
            --indent-preproc-block
            --pad-oper
            --pad-header
            --unpad-paren
            --suffix=none
            --align-pointer=name
            --lineend=linux
            --convert-tabs
            --verbose

