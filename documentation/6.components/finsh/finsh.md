@page page_component_finsh FinSH Console

In the early days of computer development, before the advent of graphics systems, there was no mouse or even a keyboard. How did people interact with computers at the time? The earliest computers used a punched note to enter commands into the computer and write the program. Later, with the continuous development of computers, monitors and keyboards became the standard configuration of computers, but the operating system at this time did not support the graphical interface. Computer pioneers developed a software that accepts commands entered by the user, and after interpretation, passes it to The operating system and return the results of the operating system execution to the user. This program wraps around the operating system like a layer of shell, so it's called a shell.

Embedded devices usually need to connect the development board to the PC for communication. Common connections include: serial port, USB, Ethernet, Wi-Fi, etc. A flexible shell should also support working on multiple connection methods. With the shell, the developer can easily get the system running and control the operation of the system through commands. Especially in the debugging phase, with the shell, in addition to being able to locate the problem more quickly, the developer can also use the shell to call the test function, change the parameters of the test function, reduce the number of times the code is downloaded, and shorten the development time of the project.

FinSH is the command line component (shell) of RT-Thread. It is based on the above considerations. FinSH is pronounced [ˈfɪnʃ]. After reading this chapter, we will have a deeper understanding of how FinSH works and how to export your own commands to FinSH.

# Introduction of FinSH

FinSH is the command line component of RT-Thread. It provides a set of operation interfaces for users to call from the command line. It is mainly used to debug or view system information. It can communicate with a PC using serial/Ethernet/USB, etc. The hardware topology is shown below:

![FinSH Hardware connection diagram](figures/finsh-hd.png)

The user inputs a command in the control terminal, and the control terminal transmits the command to the FinSH in the device through the serial port, USB, network, etc., FinSH will read the device input command, parse and automatically scan the internal function table, find the corresponding function name, and execute the function. The response is output, the response is returned through the original path, and the result is displayed on the control terminal.

When using a serial port to connect a device to a control terminal, the execution flow of the FinSH command is as follows:

![FinSH FinSH Command execution flow chart](figures/finsh-run.png)

FinSH supports the rights verification function. After the system is started, the system will perform the rights verification. Only when the rights verification is passed, the FinSH function will be enabled. This improves the security of system input.

FinSH supports auto-completion, and viewing history commands, etc. These functions can be easily accessed through the keys on the keyboard. The keys supported by FinSH are shown in the following table:

|Keys| **Functional Description**                                   |
|----------|--------------|
| Tab key | Pressing the Tab key when no characters are entered will print all commands supported by the current system. If you press the Tab key when you have entered some characters, it will find the matching command, and will also complete the file name according to the file system's current directory, and you can continue to input, multiple completions. |
| ↑↓ key | Scroll up and down the recently entered history command      |
| Backspace key | Delete character                                             |
| ←→ key  | Move the cursor left or right |

FinSH uses the traditional command line mode, also known as MSH (module shell).

## MSH Command-Line Mode

In MSH mode, FinSH works like a traditional shell such as DOS or Bash. For example, you can switch to the root directory with the `cd /` command.

MSH can parse commands into parameters and parameters separated by spaces. Its command execution format is as follows:

```
command [arg1] [arg2] [...]
```

The command can be either a built-in command in RT-Thread or an executable file.

# FinSH Built-in Commands

Some FinSH commands are built in by default in RT-Thread. You can print all commands supported by the current system by entering help in FinSH and pressing Enter or directly pressing Tab.

In msh mode, you can list all currently supported commands by pressing the Tab key. The number of default commands is not fixed, and the various components of RT-Thread will output some commands to FinSH. For example, when the DFS component is opened, commands such as `ls`, `cp`, and `cd` are added to FinSH for developers to debug.

The following are all currently supported commands that display RT-Thread kernel status information after pressing the Tab key. The command name is on the left and the description of the command on the right:

```c
RT-Thread shell commands:
version         - show RT-Thread version information
list_thread     - list thread
list_sem        - list semaphore in system
list_event      - list event in system
list_mutex      - list mutex in system
list_mailbox    - list mail box in system
list_msgqueue   - list message queue in system
list_timer      - list timer in system
list_device     - list device in system
exit            - return to RT-Thread shell mode.
help            - RT-Thread shell help.
ps              - List threads in the system.
time            - Execute command with time.
free            - Show the memory usage in the system.
```

Here lists the field information returned after entering the common commands, so that the developer can understand the content of the returned information.

## Display Thread Status

Use the `ps` or `list_thread` command to list all thread information in the system, including thread priority, state, maximum stack usage, and more.

```c
msh />list_thread
thread   pri  status      sp     stack size max used left tick  error
-------- ---  ------- ---------- ----------  ------  ---------- ---
tshell    20  ready   0x00000118 0x00001000    29%   0x00000009 000
tidle     31  ready   0x0000005c 0x00000200    28%   0x00000005 000
timer      4  suspend 0x00000078 0x00000400    11%   0x00000009 000
```
list_thread Return field description:

|**Field**  |**Description**                  |
|------------|----------------------------|
| thread     | Thread name                                         |
| pri        | Thread priority                                     |
| status     | The current state of the thread                     |
| sp         | The current stack position of the thread            |
| stack size | Thread stack size                                   |
| max used   | The maximum stack position used in thread history   |
| left tick  | The number of remaining ticks of the thread |
| error      | Thread error code |

## Display Semaphore Status

Use the `list_sem` command to display all semaphore information in the system, including the name of the semaphore, the value of the semaphore, and the number of threads waiting for this semaphore.

```c
msh />list_sem
semaphore v   suspend thread
-------- --- --------------
shrx     000 0
e0       000 0
```

list_sem  Return field description:

|**Field**      | **Description**                                  |
|----------------|--------------------------|
| semaphore      | Semaphore name                                   |
| v              | The current value of semaphore                   |
| suspend thread | The number of threads waiting for this semaphore |

## Display Event Status

Use the `list_event` command to display all event information in the system, including the event name, the value of the event, and the number of threads waiting for this event.

```c
msh />list_event
event      set    suspend thread
-----  ---------- --------------
```

list_event Return field description:

| Field          | **Description**                                              |
|----------------|----------------------------------|
| event          | Event set name                                               |
| set            | The current event in the event set                           |
| suspend thread | The number of threads waiting for an event in this event set |

## Display Mutex Status

Use the `list_mutex` command to display all mutex information in the system, including the mutex name, the owner of the mutex, and the number of nestings the owner holds on the mutex.

```c
msh />list_mutex
mutex    owner    hold suspend thread
-------- -------- ---- --------------
fat0     (NULL)   0000 0
sal_lock (NULL)   0000 0
```

list_mutex Return field description:

| **Field**      | **Description**                                        |
|----------------|------------------------------------|
| mutxe          | Mutex name                                             |
| owner          | The thread currently holding the mutex                 |
| hold           | The number of times the holder is nested on this mutex |
| suspend thread | The number of threads waiting for this mutex |

## Display Mailbox Status

Use the `list_mailbox` command to display all mailbox information in the system, including the mailbox name, the number of messages in the mailbox, and the maximum number of messages the mailbox can hold.

```c
msh />list_mailbox
mailbox  entry size suspend thread
-------- ----  ---- --------------
etxmb    0000  0008 1:etx
erxmb    0000  0008 1:erx
```

list_mailbox Return field description:

| Field          | **Description**                                   |
|----------------|----------------------------|
| mailbox        | Mailbox name                                      |
| entry          | The number of messages included in the mailbox    |
| size           | The maximum number of messages a mailbox can hold |
| suspend thread | The number of threads waiting for this mailbox |

## Display Message Queue Status

Use the `list_msgqueue` command to display all message queue information in the system, including the name of the message queue, the number of messages it contains, and the number of threads waiting for this message queue.

```c
msh />list_msgqueue
msgqueue entry suspend thread
-------- ----  --------------
```

list_msgqueue Return field description:

| Field          | **Description**                                              |
|----------------|----------------------------|
| msgqueue       | Message queue name                                           |
| entry          | The number of messages currently included in the message queue |
| suspend thread | Number of threads waiting for this message queue |

## Display Memory Pool Status

Use the `list_mempool` command to display all the memory pool information in the system, including the name of the memory pool, the size of the memory pool, and the maximum memory size used.

```c
msh />list_mempool
mempool block total free suspend thread
------- ----  ----  ---- --------------
signal  0012  0032  0032 0
```

list_mempool Return field description:

| Field          | **Description**                                    |
|----------------|--------------------|
| mempool        | Memory pool name                                   |
| block      | Memory block size                                  |
| total  | Total memory block                                 |
| free | Free memory block                                  |
| suspend thread | The number of threads waiting for this memory pool |

## Display Timer Status

Use the `list_timer` command to display all the timer information in the system, including the name of the timer, whether it is the periodic timer, and the number of beats of the timer timeout.

```c
msh />list_timer
timer     periodic   timeout       flag
-------- ---------- ---------- -----------
tshell   0x00000000 0x00000000 deactivated
tidle    0x00000000 0x00000000 deactivated
timer    0x00000000 0x00000000 deactivated
```

list_timer Return field description:

| Field    | **Description**                                              |
|----------|--------------------------------|
| timer    | Timer name                                                   |
| periodic | Whether the timer is periodic                                |
| timeout  | The number of beats when the timer expires                   |
| flag     | The state of the timer, activated indicates active, and deactivated indicates inactive |

## Display Device Status

Use the `list_device` command to display all device information in the system, including the device name, device type, and the number of times the device was opened.

```c
msh />list_device
device         type      ref count
------ ----------------- ----------
e0     Network Interface 0
uart0  Character Device  2
```

list_device Return field description:

| Field     | Description                               |
|-----------|----------------|
| device    | Device name                               |
| type      | Device type                               |
| ref count | The number of times the device was opened |

## Display Dynamic Memory Status

Use the `free` command to display all memory information in the system.

```c
msh />free
total memory: 7669836
used memory : 15240
maximum allocated memory: 18520
```

free Return field description:

| Field                | Description            |
|--------------------------|------------------|
| total memory             | Total memory size        |
| used memory              | Used memory size         |
| maximum allocated memory | Maximum allocated memory |

# Custom FinSH Command

In addition to the commands that come with FinSH, FinSH also provides multiple macro interfaces to export custom commands. The exported commands can be executed directly in FinSH.

## Custom msh Command

The custom msh command can be run in msh mode. To export a command to msh mode, you can use the following macro interface：

```
MSH_CMD_EXPORT(name, desc);
```

|**Parameter**|**Description**      |
|----------|----------------|
| name     | The command to export             |
| desc     | Description of the export command |

This command can export commands with parameters, or export commands without parameters. When exporting a parameterless command, the input parameter of the function is void. The example is as follows：

```c
void hello(void)
{
    rt_kprintf("hello RT-Thread!\n");
}

MSH_CMD_EXPORT(hello , say hello to RT-Thread);
```

When exporting a command with parameters, the function's input parameters are `int argc` and `char**argv`. Argc represents the number of arguments, and argv represents a pointer to a command-line argument string pointer array. An example of exporting a parameter command is as follows:

```c
static void atcmd(int argc, char**argv)
{
    ……
}

MSH_CMD_EXPORT(atcmd, atcmd sample: atcmd <server|client>);
```

## Access Variables from an MSH Command

The C-Style interpreter and `FINSH_VAR_EXPORT` were removed from RT-Thread. There is no direct replacement for exporting a variable to the shell. To inspect or change a variable at runtime, expose a small MSH command that reads or updates it.

The following example exports a `dummy` command. Run `dummy` to read the value or `dummy <value>` to change it:

```c
#include <stdlib.h>
#include <rtthread.h>
#include <finsh.h>

static int dummy = 0;

static void dummy_cmd(int argc, char **argv)
{
    if (argc == 1)
    {
        rt_kprintf("dummy = %d\n", dummy);
        return;
    }

    if (argc == 2)
    {
        dummy = atoi(argv[1]);
        rt_kprintf("dummy = %d\n", dummy);
        return;
    }

    rt_kprintf("Usage: dummy [value]\n");
}

MSH_CMD_EXPORT_ALIAS(dummy_cmd, dummy, show or set the dummy value);
```

## Custom MSH Command Name

Use `MSH_CMD_EXPORT_ALIAS` to expose a function under a different command name:

```
MSH_CMD_EXPORT_ALIAS(name, alias, desc);
```

| Parameter | Description                                        |
|----------|-------------------------|
| name     | The function to export                              |
| alias    | The command name displayed in MSH                   |
| desc     | Description of the exported command                 |

The following example exports the `hello` function under the command name `ho`:

```c
void hello(void)
{
    rt_kprintf("hello RT-Thread!\n");
}

MSH_CMD_EXPORT_ALIAS(hello, ho, say hello to RT-Thread);
```

# FinSH Function Configuration

The FinSH function can be cropped, and the macro configuration options are defined in the rtconfig.h file. The specific configuration items are shown in the following table.

| **Macro Definition**              | **Value Type** | Description                                                | Default |
|-----------------------------------|----------------|------------------------------------------------------------|---------|
| `#define RT_USING_MSH`            | None           | Enable the MSH command shell                               | on      |
| `#define RT_USING_FINSH`          | None           | Enable FinSH support (selected by `RT_USING_MSH`)           | on      |
| `#define FINSH_THREAD_NAME`       | String         | FinSH thread name                                          | "tshell"|
| `#define FINSH_USING_HISTORY`     | None           | Turn on historical traceback                               | on      |
| `#define FINSH_HISTORY_LINES`     | Integer type   | Number of historical command lines that can be traced back | 5       |
| `#define FINSH_USING_SYMTAB`      | None           | Symbol table can be used in FinSH                          | on      |
| `#define FINSH_USING_DESCRIPTION` | None           | Add a description to each FinSH symbol                     | on      |
| `#define FINSH_USING_MSH`         | None           | Enable the MSH implementation (selected by `RT_USING_MSH`)  | on      |
| `#define FINSH_ARG_MAX`           | Integer type   | Maximum number of input parameters                         | 10      |
| `#define FINSH_USING_AUTH`        | None           | Enable permission verification                             | off     |
| `#define FINSH_DEFAULT_PASSWORD`  | String         | Authority verification password                            | off     |

The reference configuration example in rtconfig.h is as follows, and can be configured according to actual functional requirements.

```c
/* Enable the MSH command shell */
#define RT_USING_MSH

/* Symbols selected by RT_USING_MSH */
#define RT_USING_FINSH
#define FINSH_USING_MSH

/* Define the thread name as tshell */
#define FINSH_THREAD_NAME "tshell"

/* Open history command */
#define FINSH_USING_HISTORY
/* Record 5 lines of history commands */
#define FINSH_HISTORY_LINES 5

/* Enable the use of symbol table */
#define FINSH_USING_SYMTAB
/* Turn on description */
#define FINSH_USING_DESCRIPTION

/* Define FinSH thread priority to 20 */
#define FINSH_THREAD_PRIORITY 20
/* Define the stack size of the FinSH thread to be 4KB */
#define FINSH_THREAD_STACK_SIZE 4096
/* Define the command character length to 80 bytes */
#define FINSH_CMD_SIZE 80

/* The maximum number of input parameters is 10 */
#define FINSH_ARG_MAX 10
```

# FinSH Application Examples

## Examples of msh Command without Arguments

This section demonstrates how to export a custom command to msh. The sample code is as follows, the hello function is created in the code, and the `hello` function can be exported to the FinSH command list via the `MSH_CMD_EXPORT` command.

```c
#include <rtthread.h>

void hello(void)
{
    rt_kprintf("hello RT-Thread!\n");
}

MSH_CMD_EXPORT(hello , say hello to RT-Thread);
```

Once the system is up and running, press the tab key in the FinSH console to see the exported command:

```c
msh />
RT-Thread shell commands:
hello             - say hello to RT-Thread
version           - show RT-Thread version information
list_thread       - list thread
……
```

Run the `hello` command and the results are as follows:

```c
msh />hello
hello RT_Thread!
msh />
```

## Example of msh Command with Parameters

This section demonstrates how to export a custom command with parameters to FinSH. The sample code is as follows, the `atcmd()` function is created in the code, and the `atcmd()` function can be exported to the msh command list via the MSH_CMD_EXPORT command.

```c
#include <rtthread.h>

static void atcmd(int argc, char**argv)
{
    if (argc < 2)
    {
        rt_kprintf("Please input'atcmd <server|client>'\n");
        return;
    }

    if (!rt_strcmp(argv[1], "server"))
    {
        rt_kprintf("AT server!\n");
    }
    else if (!rt_strcmp(argv[1], "client"))
    {
        rt_kprintf("AT client!\n");
    }
    else
    {
        rt_kprintf("Please input'atcmd <server|client>'\n");
    }
}

MSH_CMD_EXPORT(atcmd, atcmd sample: atcmd <server|client>);
```

Once the system is running, press the Tab key in the FinSH console to see the exported command:

```c
msh />
RT-Thread shell commands:
hello             - say hello to RT-Thread
atcmd             - atcmd sample: atcmd <server|client>
version           - show RT-Thread version information
list_thread       - list thread
……
```

Run the `atcmd` command and the result is as follows:

```c
msh />atcmd
Please input 'atcmd <server|client>'
msh />
```

Run the `atcmd server` command and the result is as follows:

```c
msh />atcmd server
AT server!
msh />
```

Run the `atcmd client` command and the result is as follows:

```c
msh />atcmd client
AT client!
msh />
```

# FinSH Porting

FinSH is written entirely in ANSI C and has excellent portability; it has a small memory footprint, and FinSH will not dynamically request memory if you do not use the functions described in the previous section to dynamically add symbols to FinSH. The FinSH source is located in the `components/finsh` directory. Porting FinSH requires attention to the following aspects:

* FinSH thread：

Each command execution is done in the context of a FinSH thread (that is, a tshell thread). When the RT_USING_FINSH macro is defined, the FinSH thread can be initialized by calling `finsh_system_init()` in the initialization thread. In RT-Thread 1.2.0 and later, you don't have to use the `finsh_set_device(const char* device_name)` function to explicitly specify the device to be used. Instead, the `rt_console_get_device()` function is called automatically to use the console device (The `finsh_set_device(const char* device_name)` must be used in 1.1.x and below to specify the device used by FinSH. The FinSH thread is created in the function `finsh_system_init()` function, which will wait for the rx_sem semaphore.

* FinSH output：

The output of FinSH depends on the output of the system and relies on the `rt_kprintf()` output in RT-Thread. In the startup function `rt_hw_board_init()`, the `rt_console_set_device(const char* name)` function sets the FinSH printout device.

* FinSH input：

After the rin_sem semaphore is obtained, the FinSH thread calls the `rt_device_read()` function to obtain a character from the device (select serial device) and then process it. So the migration of FinSH requires the implementation of the `rt_device_read()` function. The release of the rx_sem semaphore completes the input notification to the FinSH thread by calling the `rx_indicate()` function. The usual process is that when the serial port receive interrupt occurs (that is, the serial port has input character), the interrupt service routine calls the `rx_indicate()` function to notify the FinSH thread that there is input, and then the FinSH thread obtains the serial port input and finally performs the corresponding command processing.
