# Kernel Basics

This chapter gives a brief introduction to the software architecture of the RT-Thread kernel, beginning with its composition and implementation.  While also introducing RT-Thread kernel-related concepts for beginners.
After understanding this chapter, readers will have an elementary understanding of the RT Thread kernel and will be able to answer questions such as -

- What are the constituents of the kernel?
- How does the system startup?
- How is the memory distributed?
- What are the methods of kernel configuration?

In the nutshell, this is only a brief introduction to software architecture decomposition and implementation of the real-time kernel. This will give understanding and concepts of how RT-Thread kernel works togther. After learning from this chapter, readers will have basic knowledge of each kernel components, system booting up proccesses, memory allocation and distrubtion, and methods of kernel configuration.

## **Table of Contents**

1. [Introduction to RT-Thread Kernel](#introduction-to-rt-thread-kernel)
2. [RT-Thread Startup Process](#rt-thread-startup-process)
3. [RT-Thread Program Memory Distribution](#rt-thread-program-memory-distribution)
4. [RT-Thread Automatic Initialization Mechanism](#rt-thread-automatic-initialization-mechanism)
5. [RT-Thread Kernel Object Model](#rt-thread-kernel-object-model)

## Introduction to RT-Thread Kernel

Kernel is the most basic and fundenmental part of an Operating System. Kernel service library and RT-Thread kernel libraries are interfacing between hardware and components/service layer. This includes the implementation of real-time kernel service library (rtservice.h/kservice.c) and other RT-Thread kernel libraries such as object management, thread management and scheduler, inter-thread communication management, clock management and memory management respectively. Below diagram is the core architecture diagram of the core kernel.

![RT-Thread Kernel and its Substructure](figures/03kernel_Framework.png)

Implementation of core kernel libraries are similar to a small set of standard C runtime library and it can run independently. For example, Standard C library (C runtime library) provides "strcpy", "memcpy", "printf", "scanf" and other function implementations. RT-Thread kernel libraries also provide the function implementations which are mainly used by Core Kernel. However, to avoid name conflicts, specifically functions' names are preceded with rt_.


The built of the Kernel will be vary depending on the complier. For example, using GNU GCC compiler, it will use more implementation from the standard C library. Last but not least, the minimum resource requirements of the Kernel is 3KB ROM and 1.2KB RAM.


### Thread Scheduling

Thread is the smallest scheduling unit in the RT-Thread operating system. The thread scheduling algorithm is a **Priority-based Full Preemptive Multi-Thread** scheduling algorithm.
The system can support up to 256(0 - 255) thread priorities. For systems with tight resources, configurations with 8 or 32 thread priorities can be chosen(For example, STM32 has 32 thread priorities as per the default configuration). Lower numbers have a higher priority where 0 represents the highest priority furthermore the lowest priority(highest number) is reserved for idle threads.
RT-Thread supports the creation of multiple threads with the same priority. Threads having the same priority are scheduled with a Time Slice Rotation Scheduling algorithm so that each thread runs for the same amount of time.
The number of threads is bounded by the memory of the hardware platform and not the system.

Thread management will be covered in detail in the "Thread Management" chapter.

### Clock Management

RT-Thread's Clock management is based upon a **clock beat**, which is the smallest clock unit in the RT-Thread operating system.
The RT-Thread timer provides two types of timer mechanisms:
- **One-Shot Timer** - Triggers only one timer event after startup and then stops automatically.
- **Periodic Trigger Timer** - Periodically triggers timer events until the user manually stops the timer or it will continue to operate.

The RT-Thread timer can be set to the `HARD_TIMER` or the `SOFT_TIMER` mode depending on the context in which the timeout function is executed.

The timer service is concluded using a timer timing callback i.e. a timeout function. The user can select the appropriate type of timer according to their real-time requirements for timing processing.

Timer will be explained further in the "Clock Management" chapter.

### Synchronization between Threads

RT-Thread uses thread semaphores, mutexes, and event sets to achieve inter-thread synchronization.
Thread synchronizations happen through the acquisition and release of semaphore and mutexes.
The mutex uses priority inheritance to solve the common priority inversion problem in the real-time system. The thread synchronization mechanism allows threads to wait according to priorities or to acquire semaphores/mutexes following the First In First Out(FIFO) method.
Event sets are primarily used for synchronization between threads, they can achieve one-to-many and many-to-many synchronization. It allows "**OR** trigger"(*independent synchronization*) and "**AND** trigger"(*associative synchronization*) suitable for situations where threads are waiting for multiple events.

The concepts of semaphores, mutexes, and event sets are detailed in the "Inter-Thread Synchronization" chapter.

### Inter-Thread Communication

RT-Thread supports communication mechanisms such as mailbox, message queue, etc. The mailbox's message length is fixed to 4 bytes. Whereas, message queue can receive messages in variable size and cache the messages in its own memory space.  
Compared to a message queue, a mailbox is more efficient. The sending action of the mailbox and message queue can be safely used in an ISR (Interrupt Service Routine). The communication mechanism allows threads to wait by priority or to acquire by the First In First Out (FIFO) method.  
The concept of mailbox and message queue will be explained in detail in the "Inter-Thread Communication" chapter.

### Memory Management

RT-Thread allows:
1. Static Memory Pool
2. Dynamic Memory Pool  

When the static memory pool has available memory, the time allocated to the memory block will be constant. 
When the static memory pool is empty, the system will then request for suspending or blocking the thread of the memory block. The thread will abandon the request and return if the memory block is not obtained after waiting for a while, or the thread will abandon and return immediately. The waiting time depends on the waiting time parameter set when the memory block is applied. When other threads release the memory block to the memory pool, the system will wake up the thread if there are suspended threads waiting to be allocated of memory blocks.

Under circumstances of different system resources, the dynamic memory heap management module respectively provides memory management algorithms for small memory systems and SLAB memory management algorithms for large memory systems.

There is also a dynamic memory heap management called memheap, suitable for memory heaps in systems with multiple addresses that can be discontinuous. Using memheap, the user can "paste" multiple memory heaps together, letting them operate as if operating a memory heap.

The concept of memory management will be explained in the "Memory Management" chapter.

### I/O Device Management

RT-Thread uses I2C, SPI, USB, UART, etc., as peripheral devices and is uniformly registered through the device. It realized a device management subsystem accessed by the name, and it can access hardware devices according to a unified API interface. On the device driver interface, depending on the characteristics of the embedded system, corresponding events can be attached to different devices. The driver notifies the upper application program when the device event is triggered.

The concept of I/O device management will be explained in the "Device Model" and "General Equipment" chapters.

## RT-Thread Startup Process

The understanding of most codes usually starts from learning the startup process. We will firstly look for the source of the startup. Taking MDK-ARM as an example, the user program entry for MDK-ARM is the main() function located in the main.c file. The launching of the system starts from the assembly code startup_stm32f103xe.s, jumps to the C code, initializes the RT-Thread system function, and finally enters the user program entry main().

To complete the RT-Thread system function initialization before entering main(), we used the MDK extensions  `$Sub$$` and  `$Super$$`. Users can add the prefix of `$Sub$$` to main to make it a new function `$Sub$$main`.  
`$Sub$$main` can call some functions to be added before main (here, RT-Thread system initialization function is added). Then, call `$Super$$main` to the main() function so that the user does not have to manage the system initialization before main(). 

For more information on the use of the `$Sub$$` and `$Super$$`extensions, see the ARM® Compiler v5.06 for μVision®armlink User Guide.

Let's take a look at this code defined in components.c:

```c
/* $Sub$$main Function */
int $Sub$$main(void)
{
  rtthread_startup();
  return 0;
}
```

Here, the `$Sub$$main` function simply calls the rtthread_startup() function. RT-Thread allows multiple platforms and multiple compilers, and the rtthread_startup() function is a uniform entry point specified by RT-Thread, so the `$Sub$$main` function only needs to call the rtthread_startup() function (RT-Thread compiled using compiler GNU GCC is an example where it jumps directly from the assembly startup code section to the rtthread_startup() function and starts the execution of the first C code).  
The rtthread_startup() function can be found in the code of components.c, the startup process of RT-Thread is as shown below:

![System startup process](figures/03Startup_process.png)

Code for the rtthread_startup() function is as follows:

```c
int rtthread_startup(void)
{
    rt_hw_interrupt_disable();

    /* Board level initialization: system heap initialization is required inside the function */
    rt_hw_board_init();

    /* Print RT-Thread version information */
    rt_show_version();

    /* Timer initialization */
    rt_system_timer_init();

    /* Scheduler initialization */
    rt_system_scheduler_init();

#ifdef RT_USING_SIGNALS
    /* Signal initialization */
    rt_system_signal_init();
#endif

    /* Create a user main() thread here */
    rt_application_init();

    /* Timer thread initialization */
    rt_system_timer_thread_init();

    /* Idle thread initialization */
    rt_thread_idle_init();

    /* Start scheduler */
    rt_system_scheduler_start();

    /* Will not execute till here */
    return 0;
}
```

This part of the startup code can be roughly divided into four parts:

1. Initialize hardware related to the system.
2. Initialize system kernel objects, such as timers, schedulers, and signals.
3. Create the main thread initialize various modules in the main thread one by one.
4. Initialize the timer thread, idle thread, and start the scheduler.

Set the system clock in rt_hw_board_init() to provide heartbeat and serial port initialization for the system, bound to the system's input and output terminals to this serial port. Subsequent system operation information will be printed out from the serial port later.  
The main() function is the user code entry for RT-Thread, and users can add their own applications to the main() function.

```c
int main(void)
{
  /* user app entry */
  return 0;
}
```

## RT-Thread Program Memory Distribution

The general MCU contains storage space that includes the on-chip Flash and the on-chip RAM. RAM is equivalent to memory, and Flash is comparable to a hard disk. The compiler classifies a program into several parts stored in different memory areas of the MCU.

After the Keil project is compiled, there will be a prompt stating the occupied space by the corresponding program, for example:

```
linking...
Program Size: Code=48008 RO-data=5660 RW-data=604 ZI-data=2124
After Build - User command \#1: fromelf --bin.\\build\\rtthread-stm32.axf--output rtthread.bin
".\\build\\rtthread-stm32.axf" - 0 Error(s), 0 Warning(s).
Build Time Elapsed: 00:00:07
```

The Program Size mentioned above contains the following sections:

1. **Code**: Code Segment, section of code that stores the program
2. **RO-data**: Read-Only data segment, stores the constants defined in the program
3. **RW-data**: Read and Write data segment, stores global variables initialized to non-zero values
4. **ZI-data**: 0 data segment, stores uninitialized global variables and initialized-to-0 variables

After compiling the project, there will be a generated .map file that describes the size and address of each function. The last few lines of the file also illustrate the relationship between the above fields:

```
Total RO Size (Code + RO Data) 53668 ( 52.41kB)
Total RW Size (RW Data + ZI Data) 2728 ( 2.66kB)
Total ROM Size (Code + RO Data + RW Data) 53780 ( 52.52kB)
```

1. RO Size contains Code and RO-data, indicating the size of the Flash occupied by the program
2. RW Size contains RW-data and ZI-data, indicating the size of the RAM occupied when operating
3. ROM Size contains Code, RO Data, and RW Data. Indicating the size of the Flash occupied by the programming system;

Before the program runs, the file entity needs to be flashed into the STM32 Flash, usually a bin or hex file. The burned file is called an executable image file. The left part in the figure below shows the memory distribution after the executable image file is flashed into STM32 which includes the RO and RW segments. The RO segment stores data of Code and RO-data, and the RW segment holds the data of RW-data. Since ZI-data is 0, it is not included in the image file.

STM32 is launched from Flash by default after power-on. After launching, RW-data (initialized global variable) the RW segment is transferred to RAM, but the RO segment is not transferred. Meaning the execution code of the CPU is read from the Flash. The ZI segment is allocated according to the ZI address and size is given by the compiler, and the RAM area is cleared.

![RT-Thread Memory Distribution](figures/03Memory_distribution.png)

The dynamic memory heap is unused RAM space, and the memory blocks requested and released by the application come from this space.

Like the following example:

```c
rt_uint8_t* msg_ptr;
msg_ptr = (rt_uint8_t*) rt_malloc (128);
rt_memset(msg_ptr, 0, 128);
```

The 128-byte memory space pointed by the `msg_ptr` pointer in the code is in the dynamic memory heap space.

Some global variables are stored in the RW segment and the ZI segment. The RW segment holds the global variable with the initial value (the global variable in the constant form is placed in the RO segment, which is a read-only property), and uninitialized global variable is stored in the ZI segment, as in the following example:

```c
#include <rtthread.h>

const static rt_uint32_t sensor_enable = 0x000000FE;
rt_uint32_t sensor_value;
rt_bool_t sensor_inited = RT_FALSE;

void sensor_init()
{
     /* ... */
}
```
The `sensor_value` is stored in the ZI segment and is automatically initialized to zero after system startup (some library functions provided by the user program or compiler are initialized to zero). The sensor_inited variable is stored in the RW segment, and the sensor_enable is stored in the RO segment.

## RT-Thread Automatic Initialization Mechanism

The automatic initialization mechanism means that the initialization function does not need to be called by explicit function. It only needs to be declared by macro definition at the function definition, and it will be executed during system startup.

For example, calling a macro definition in the serial port driver to inform the function that needs to be called to initialize the system. The code is as follows:

```c
int rt_hw_usart_init(void)  /* Serial port initialization function */
{
     ... ...
     /* Register serial port 1 device */
     rt_hw_serial_register(&serial1, "uart1",
                        RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_INT_RX,
                        uart);
     return 0;
}
INIT_BOARD_EXPORT(rt_hw_usart_init);    /* Use component auto-initialization mechanism */
```

The last part of the sample code INIT_BOARD_EXPORT(rt_hw_usart_init) indicates that the automatic initialization function is used. In this way, rt_hw_usart_init() function is automatically called by the system, so where is it called?

In the system startup flowchart, there are two functions: rt_components_board_init() and rt_components_init(), subsequent functions inside the box with the underlying color represent functions that are automatically initialized, where:

1.  “board init functions” are all initialization functions declared by INIT_BOARD_EXPORT(fn).
2.  “pre-initialization functions” are all initialization functions declared by INIT_PREV_EXPORT(fn).
3.  “device init functions” are all initialization functions declared by INIT_DEVICE_EXPORT(fn).
4.  “components init functions” are all initialization functions declared by INIT_COMPONENT_EXPORT(fn).
5.  “enviroment init functions” are all initialization functions declared by INIT_ENV_EXPORT(fn).
6.  “application init functions” are all initialization functions declared by INIT_APP_EXPORT(fn).

The rt_components_board_init() function executes earlier, mainly to initialize the relevant hardware environment. When this function is executed, it will traverse the initialization function table declared by INIT_BOARD_EXPORT(fn) and call each function.

The rt_components_init() function is called and executed in the main thread created after the operating system is running. At this time, the hardware environment and the operating system have been initialized and the application-related code can be executed. The rt_components_init() function will transverse through the remaining few initialization function tables declared by macros.

RT-Thread's automatic initialization mechanism uses a custom RTI symbol segment, it puts the function pointer that needs to be initialized at startup into this segment and forms an initialization function table which will be traversed during system startup. It calls the functions in the table to achieve the purpose of automatic initialization.

The macro interface definitions used to implement the automatic initialization function are described in the following table:

|Initialization sequence|Macro Interface               |Description                                    |
|----------------|------------------------------------|----------------------------------------------|
| 1              | INIT_BOARD_EXPORT(fn)     | Very early initialization, the scheduler has not started yet. |
| 2              | INIT_PREV_EXPORT(fn)      | Mainly used for pure software initialization, functions without too many dependencies |
| 3              | INIT_DEVICE_EXPORT(fn)    | Peripheral driver initialization related, such as network card devices |
| 4             | INIT_COMPONENT_EXPORT(fn) | Component initialization, such as file system or LWIP |
| 5              | INIT_ENV_EXPORT(fn)       | System environment initialization, such as mounting file systems |
| 6              | INIT_APP_EXPORT(fn)       | Application initialization, such as application GUI |

Initialization function actively declares through these macro interfaces, such as INIT_BOARD_EXPORT (rt_hw_usart_init), the linker will automatically collect all the declared initialization functions, placed in the RTI symbol segment, the symbol segment is located in the RO segment of the memory distribution. All functions in this RTI symbol segment are automatically called when the system is initialized.

RT-Thread Kernel Object Model
---------------------

### Static and Dynamic Objects

The RT-Thread kernel is designed with object-oriented method. The system-level infrastructures are all kernel objects such as threads, semaphores, mutexes, timers, and more. Kernel objects fall into two categories: static kernel objects and dynamic kernel objects. Static kernel objects are usually placed in RW and ZI segments, initialized in the program after system startup; dynamic kernel objects are created from the memory heap and then manually initialized.

The following code is an example of static threads and dynamic threads:


```c
/* Thread 1 object and stack used while running */
static struct rt_thread thread1;
static rt_uint8_t thread1_stack[512];

/* Thread 1 entry */
void thread1_entry(void* parameter)
{
     int i;

    while (1)
    {
        for (i = 0; i < 10; i ++)
        {
            rt_kprintf("%d\n", i);

            /* Delay 100ms */
            rt_thread_mdelay(100);
        }
    }
}

/* Thread 2 entry */
void thread2_entry(void* parameter)
{
     int count = 0;
     while (1)
     {
         rt_kprintf("Thread2 count:%d\n", ++count);

        /* Delay 50ms */
        rt_thread_mdelay(50);
    }
}

/* Thread routine initialization */
int thread_sample_init()
{
     rt_thread_t thread2_ptr;
     rt_err_t result;

    /* Initialize thread 1 */
    /* The thread entry is thread1_entry and the parameter is RT_NULL
     * Thread stack is thread1_stack
     * Priority is 200 and time slice is 10 OS Tick
     */
    result = rt_thread_init(&thread1,
                            "thread1",
                            thread1_entry, RT_NULL,
                            &thread1_stack[0], sizeof(thread1_stack),
                            200, 10);

    /* Start thread */
    if (result == RT_EOK) rt_thread_startup(&thread1);

    /* Create thread 2 */
    /* The thread entry is thread2_entry and the parameter is RT_NULL
     *  Stack space is 512, priority is 250, and time slice is 25 OS Tick
     */
    thread2_ptr = rt_thread_create("thread2",
                                thread2_entry, RT_NULL,
                                512, 250, 25);

    /* Start thread */
    if (thread2_ptr != RT_NULL) rt_thread_startup(thread2_ptr);

    return 0;
}
```

In this example, thread1 is a static thread object and thread2 is a dynamic thread object. The memory space of the thread1 object, including the thread control block thread1 and the stack space thread1_stack are all determined while compiling, because there is no initial value in the code and they are uniformly placed in the uninitialized data segment. The space used by thread2 is dynamically allocated includes the thread control block (the content pointed to by thread2_ptr) and the stack space.

Static objects take up RAM space and is not depend on the memory heap manager. When allocating static objects, the time needed is determined. Dynamic objects depend on the memory heap manager. It requests RAM space while running. When the object is deleted, the occupied RAM space is released. These two methods have their own advantages and disadvantages, and can be selected according to actual needs.

### Kernel Object Management Structure

RT-Thread uses the kernel object management system to access/manage all kernel objects. Kernel objects contain most of the facilities in the kernel. These kernel objects can be statically allocated static objects and dynamic objects allocated from the system memory heap. .

Because of this design for kernel object, RT-Thread is able to not depend on the specific memory allocation method, and the flexibility of the system is greatly improved.

RT-Thread kernel objects include: threads, semaphores, mutexes, events, mailboxes, message queues and timers, memory pools, device drivers, and more. The object container contains information about each type of kernel object, including object type, size, and so on. The object container assigns a linked list to each type of kernel object. All kernel objects are linked to the linked list. The kernel object container and linked list of RT-Thread are shown in the following figure:

![RT-Thread Kernel Object Container and Linked List](figures/03kernel_object.png)

The following figure shows the derivation and inheritance relationships of various kernel objects in RT-Thread. For each specific kernel object and object control block, in addition to the basic structure, they have  their own extended attributes (private attributes). Take thread control block for an example, the base object is extended, attributes like thread state, precedence and so on are added. These attributes are not used in the operation of the base class object and are only used in operations related to a specific thread. Therefore, from the object-oriented point of view, each concrete object can be considered as a derivative of an abstract object, inheriting the attributes of the base object and extending the attributes related to itself.

![RT-Thread Kernel Object Inheritance Relationship](figures/03kernel_object2.png)

In the object management module, a common data structure is defined to store the common attributes of various objects. Each specific object only needs to add some special attributes of its own and its own feature will be clearly expressed.

The advantages of this design approach are:

(1) Improve the reusability and scalability of the system. It is easy to add new object categories. It only needs to inherit the attributes of the general object and add a small amount of extension.

(2) Provide a unified object operation mode, simplify the operation of various specific objects, and improve the reliability of the system.

Derivations from object control block rt_object in the above figure includes: thread object, memory pool object, timer object, device object and IPC object (IPC: Inter-Process Communication. In RT-Thread real-time operating system, IPC objects is used for synchronization and communicate between threads); derivations from IPC objects includes: semaphores, mutexes, events, mailboxes, message queues, signals, etc.

### Object Control Block

Data structure of kernel object control block:

```c
struct rt_object
{
     /* Kernel object name     */
     char      name[RT_NAME_MAX];
     /* Kernel object type     */
     rt_uint8_t  type;
     /* Parameters to the kernel object   */
     rt_uint8_t  flag;
     /* Kernel object management linked list */
     rt_list_t   list;
};
```

Types currently supported by kernel objects are as follows:

```c
enum rt_object_class_type
{
     RT_Object_Class_Thread = 0,             /* Object is thread type      */
#ifdef RT_USING_SEMAPHORE
    RT_Object_Class_Semaphore,              /* Object is semaphore type    */
#endif
#ifdef RT_USING_MUTEX
    RT_Object_Class_Mutex,                  /* Object is mutex type    */
#endif
#ifdef RT_USING_EVENT
    RT_Object_Class_Event,                  /* Object is event type      */
#endif
#ifdef RT_USING_MAILBOX
    RT_Object_Class_MailBox,                /* Object is mailbox type      */
#endif
#ifdef RT_USING_MESSAGEQUEUE
    RT_Object_Class_MessageQueue,           /* Object is message queue type   */
#endif
#ifdef RT_USING_MEMPOOL
    RT_Object_Class_MemPool,                /* Object is memory pool type     */
#endif
#ifdef RT_USING_DEVICE
    RT_Object_Class_Device,                 /* Object is device type       */
#endif
    RT_Object_Class_Timer,                  /* Object is timer type     */
#ifdef RT_USING_MODULE
    RT_Object_Class_Module,                 /* Object is module         */
#endif
    RT_Object_Class_Unknown,                /* Object is unknown        */
    RT_Object_Class_Static = 0x80           /* Object is a static object      */
};
```

From the above type specification, we can see that if it is a static object, the highest bit of the object type will be 1 (which is the OR operation of RT_Object_Class_Static and other object types and operations).  Otherwise it will be dynamic object, and the maximum number of object classes that the system can accommodate is 127.

### Kernel Object Management

Data structure of kernel object container:

```c
struct rt_object_information
{
     /* Object type */
     enum rt_object_class_type type;
     /* Object linked list */
     rt_list_t object_list;
     /* Object size */
     rt_size_t object_size;
};
```

A class of objects is managed by an rt_object_information structure, and each practical instance of such type of object is mounted to the object_list in the form of a linked list. The memory block size of this type of object is identified by object_size (the memory block each practical instance of each type of object is the same size).

#### Initialization Object

An uninitialized static object must be initialized before it can be used. The initialization object uses the following interfaces:

```c
void rt_object_init(struct  rt_object*  object ,
                    enum rt_object_class_type  type ,
                    const char* name)
```

When this function is called to initialize the object, the system will place the object into the object container for management, that is, initialize some parameters of the object, and then insert the object node into the object linked list of the object container. Input parameters of the function is described in the following table:


|Parameters|Description                                                    |
| -------- | ------------------------------------------------------------ |
| object   | The object pointer that needs to be initialized must point to a specific object memory block, not a null pointer or a wild pointer. |
| type     | The type of the object must be a enumeration type listed in rt_object_class_type, RT_Object_Class_Static excluded. (For static objects, or objects initialized with the rt_object_init interface, the system identifies it as an RT_Object_Class_Static type) |
| name     | Name of the object. Each object can be set to a name, and the maximum length for the name is specified by RT_NAME_MAX. The system does not care if it uses ’`\0`’as a terminal symbol. |

#### Detach Object

Detach an object from the kernel object manager. The following interfaces are used to detach objects:

```c
void rt_object_detach(rt_object_t object);
```

Calling this interface makes a static kernel object to be detached from the kernel object container, meaning the corresponding object node is deleted from the kernel object container linked list. After the object is detached, the memory occupied by the object will not be released.

#### Allocate object

The above descriptions are interfaces of objects initialization and detachment, both of which are under circumstances that object-oriented memory blocks already exist. But dynamic objects can be requested when needed. The memory space is freed for other applications when not needed. To request assigning new objects, you can use the following interfaces:

```c
rt_object_t rt_object_allocate(enum  rt_object_class_typetype ,
                               const  char*  name)
```

When calling the above interface, the system first needs to obtain object information according to the object type (especially the size information of the object type for the system to allocate the correct size of the memory data block), and then allocate memory space corresponding to the size of the object from the memory heap. Next, to start necessary initialization for the object, and finally insert it into the object container linked list in which it is located. The input parameters for this function are described in the following table:


|Parameters          |Description                                                    |
| ------------------ | ------------------------------------------------------------ |
| type               | The type of the allocated object can only be of type rt_object_class_type other than RT_Object_Class_Static. In addition, the type of object allocated through this interface is dynamic, not static. |
| name               | Name of the object. Each object can be set to a name, and the maximum length for the name is specified by RT_NAME_MAX. The system does not care if it uses ’`\0`’as a terminal symbol. |
|**Return**          | ——                                                           |
| object handle allocated successfully | Allocate successfully |
| RT_NULL            | Fail to allocate               |

#### Delete Object

For a dynamic object, when it is no longer used, you can call the following interface to delete the object and release the corresponding system resources:

```c
void rt_object_delete(rt_object_t object);
```

When the above interface is called, the object is first detached from the object container linked list, and then the memory occupied by the object is released. The following table describes the input parameters of the function:


|Parameter|Description  |
|----------|------------|
| object   | object handle |

#### Identify objects

Identify whether the specified object is a system object (static kernel object). The following interface is used to identify the object:

```c
rt_err_t rt_object_is_systemobject(rt_object_t object);
```

Calling the rt_object_is_systemobject interface can help to identify whether an object is a system object. In RT-Thread operating system, a system object is also a static object, RT_Object_Class_Static bit is set to 1 on the object type identifier. Usually, objects that are initialized using the rt_object_init() method are system objects. The input parameters for this function are described in the following table:

Input parameter of rt_object_is_systemobject()

|**Parameter**|Description  |
|----------|------------|
| object   | Object handle |

RT-Thread Kernel Configuration Example
----------------------

An important feature of RT-Thread is its high degree of tailorability, which allows for fine-tuning of the kernel and flexible removal of components.

Configuration is mainly done by modifying the file under project directory - rtconfig.h. User can conditionally compile the code by opening/closing the macro definition in the file, and finally achieve the purpos e of system configuration and cropping, as follows:

（1）RT-Thread Kernel part

```c
/* Indicates the maximum length of the name of the kernel object. If the maximum length of the name of the object in the code is greater than the length of the macro definition,
 * the extra part will be cut off. */
#define RT_NAME_MAX 8

/* Set the number of aligned bytes when bytes are aligned. Usually use ALIGN(RT_ALIGN_SIZE) for byte alignment.*/
#define RT_ALIGN_SIZE 8

/* Define the number of system thread priorities; usually define the priority of idle threads with RT_THREAD_PRIORITY_MAX-1 */
#define RT_THREAD_PRIORITY_MAX 32

/* Define the clock beat. When it is 100, it means 100 tick per second, and a tick is 10ms. */
#define RT_TICK_PER_SECOND 100

/* Check if the stack overflows, if not defined, close. */
#define RT_USING_OVERFLOW_CHECK

/* Define this macro to enable debug mode, if not defined, close.  */
#define RT_USING_DEBUG
/* When debug mode is enabled: Define this macro to enable the print component initialization information, if not defined, close.  */
#define RT_DEBUGING_AUTO_INIT

/* Defining this macro means the use of the hook function is started, if not defined, close. */
#define RT_USING_HOOK

/* Defines the stack size of idle threads. */
#define IDLE_THREAD_STACK_SIZE 256
```

（2）Inter-thread synchronization and communication part, the objects that will be used in this part are semaphores, mutexes, events, mailboxes, message queues, signals, and so on.

```c
/* Define this macro to enable the use of semaphores, if not defined, close. */
#define RT_USING_SEMAPHORE

/* Define this macro to enable the use of mutexes, if not defined, close. */
#define RT_USING_MUTEX

/* Define this macro to enable the use of events, if not defined, close. */
#define RT_USING_EVENT

/* Define this macro to enable the use of mailboxes, if not defined, close. */
#define RT_USING_MAILBOX

/* Define this macro to enable the use of message queues, if not defined, close. */
#define RT_USING_MESSAGEQUEUE

/* Define this macro to enable the use of signals, if not defined, close. */
#define RT_USING_SIGNALS
```

（3）Memory Management Part

```c
/* Start the use of static memory pool */
#define RT_USING_MEMPOOL

/* Define this macro to start the concatenation of two or more memory heap , if not defined, close. */
#define RT_USING_MEMHEAP

/* Start algorithm for small memory management */
#define RT_USING_SMALL_MEM

/* Turn off SLAB memory management algorithm */
/* #define RT_USING_SLAB */

/* Start the use of heap */
#define RT_USING_HEAP
```

（4）Kernel Device Object

```c
/* Indicates the start of useing system devices */
#define RT_USING_DEVICE

/* Define this macro to start the use of system console devices, if not defined, close. */
#define RT_USING_CONSOLE
/* Define the buffer size of the console device. */
#define RT_CONSOLEBUF_SIZE 128
/* Name of the console device. */
#define RT_CONSOLE_DEVICE_NAME "uart1"
```

（5）Automatic Initialization Method

```c
/* Define this macro to enable automatic initialization mechanism, if not defined, close. */
#define RT_USING_COMPONENTS_INIT

/* Define this macro to set application entry as main function */
#define RT_USING_USER_MAIN
/* Define the stack size of the main thread */
#define RT_MAIN_THREAD_STACK_SIZE 2048
```

（6）FinSH

```c
/* Define this macro to start the use of the system FinSH debugging tool, if not defined, close. */
#define RT_USING_FINSH

/* While starting the system FinSH: the thread name is defined as tshell */
#define FINSH_THREAD_NAME "tshell"

/* While turning the system FinSH: use history commands. */
#define FINSH_USING_HISTORY
/* While turning the system FinSH: define the number of historical command lines. */
#define FINSH_HISTORY_LINES 5

/* While turning the system FinSH: define this macro to use symbol table in Finsh, if not defined, close. */
#define FINSH_USING_SYMTAB

/* While turning the system FinSH: define the priority of the thread. */
#define FINSH_THREAD_PRIORITY 20
/* While turning the system FinSH：define the stack size of the thread. */
#define FINSH_THREAD_STACK_SIZE 4096
/* While turning the system FinSH：define the length of command character. */
#define FINSH_CMD_SIZE 80

/* While turning the system FinSH: define this macro to enable the MSH function. */
#define FINSH_USING_MSH
/* While turning the system FinSH：when MSH function is enabled, macro is defined to use the MSH function by default. */
#define FINSH_USING_MSH_DEFAULT
/* While turning the system FinSH：define this macro to use only the MSH function. */
#define FINSH_USING_MSH_ONLY
```

（7）About MCU

```c
/* Define the MCU used in this project is STM32F103ZE; the system defines the chip pins by defining the chip type. */
#define STM32F103ZE

/* Define the clock source frequency. */
#define RT_HSE_VALUE 8000000

/* Define this macro to enable the use of UART1. */
#define RT_USING_UART1
```

>In practice, the system configuration file rtconfig.h is automatically generated by configuration tools and does not need to be changed manually.

Common Macro Definition Description
--------------

Macro definitions are often used in RT-Thread. For example, some common macro definitions in the Keil compilation environment:

1）rt_inline, definition is as follows, static keyword is to make the function only available for use in the current file; inline means inline, after modification using static, the compiler is recommended to perform inline expansion when calling the function.

```c
#define rt_inline                   static __inline
```

2）rt_used，definition is as follows, the purpose of this macro is to explain to the compiler that this code is useful, compilation needs to be saved even if it is not called in the function. For example, RT-Thread auto-initialization uses custom segments, using rt_used will retain custom code snippets.

```c
#define rt_used                     __attribute__((used))
```

3）RT_UNUSED，definition is as follows, indicates that a function or variable may not be used. This attribute prevents the compiler from generating warnings.

```c
#define RT_UNUSED                   __attribute__((unused))
```

4）rt_weak，definition is as follows, often used to define functions, when linking the function, the compiler will link the function without the keyword prefix first and link the function modified by weak if it can't find those functions.

```c
#define rt_weak                     __weak
```

5）ALIGN(n)，definition is as follows, is used to align its stored address with n bytes when allocating an address space to an object. Here, n can be the power of 2. Byte alignment not only facilitates quick CPU access, but also save memory space if byte alignment  is properly used.

```c
#define ALIGN(n)                    __attribute__((aligned(n)))
```

6）RT_ALIGN(size,align)，definition is as follows, to increase size to a multiple of an integer defined by align. For example, RT_ALIGN(13,4) will return to 16.

```c
#define RT_ALIGN(size, align)      (((size) + (align) - 1) & ~((align) - 1))
```

