# Start Guide: Simulate STM32F103 on keil simulator

Because of its particularity, the embedded operating system is often closely related to the hardware platform. Specific embedded operating system can only run on specific hardware. For those who are new to the RT-Thread operating system, it is not easy to get a hardware module that is compatible with the RT-Thread operating system. However, with the development of computer technology, we can use software to simulate a  hardware module that has the ability to run RT-Thread operating system. This is the simulation environment called MDK-ARM produced by the company ARM.

MDK-ARM (MDK-ARM Mi6hyicrocontroller Development Kit) software is a complete integrated development environment (IDE) from ARM. It includes efficient C/C++ compiler for ARM chips (ARM7, ARM9, Cortex-M series, Cortex-R series, etc.) ; project wizard and project management for various ARM devices, evaluation boards; simulator for software simulating hardware platform; and debuggers connected to simulators debugging the target board, common on-line simulators on the market are stlink jlink, etc. The simulator software in MDK-ARM uses a complete software simulation to interpret and execute  machine instructions from ARM and implement some peripheral logic to form a complete virtual hardware environment, enabling users to execute the corresponding target program on the computer without using real hardware platform.

Because of its full STM32F103 software simulation environment, the MDK-ARM integrated development environment gives us the opportunity to run object code directly on the computer without using a real hardware environment . This simulator platform can completely virtualize  the various operating modes and peripherals of the ARM Cortex-M3, such as exceptional interrupts, clock timers, serial ports, etc., which is almost identical to the real hardware environment. Practice has also proved that the RT-Thread introductory sample used in this article, after compiling into binary code, can not only run on the simulator platform, but also can run normally on the real hardware platform without modification.

Next, we will select the MDK-ARM integrated development environment as the target hardware platform to observe how the RT-Thread operating system works.

## Preparation

MDK development environment: MDK-ARM 5.24 (official or evaluation version, version 5.14 and above) needs to be installed. This version is also a relatively new version, which can provide relatively complete debugging functions. How to install can be referred to the  [Keil MDK Installation](./keil-installation/keil-installation.md).

## First acquaintance with RT-Thread

As an operating system, what is the code size of RT-Thread? Before we can figure this out, the first thing we need to do is to get an example of RT-Thread that corresponds to this manual. This example can be obtained from the following link:

[RT-Thread Simulator Sample](./rtthread_simulator_v0.1.0.zip)

This example is a zip file, unzip it. Here, we decompressed it to D:/. The directory structure after decompression is as shown below:

![rtthread_simulator_v0.1.0 Code Directory ](./figures/7.png)

Descriptions of the file types contained in each directory are shown in the following table:

Directory Name      | Description
---         |   ---
applications| RT-Thread application.
rt-thread   | Source file for RT-Thread.
- components| Respective component directories of RT-Thread.
- include   | Header file for RT-Thread kernel.
- libcpu    | Porting code for various types of chips, including porting files of STM32.
- src       | Source file for RT-Thread kernel.
- tools     | Script file of RT-Thread commanding building tool.
drivers     | Driver of RT-Thread, implementations of bottom driver of different platforms.
Libraries   | ST's STM32 firmware library file.
kernel-sample-0.1.0    | Kernel sample for RT-Thread.

In the directory, there is project.uvprojx file, which is an MDK5 project file in the sample referenced in this manual. Double-click "project.uvprojx" icon to open the project file:

![Open the project](./figures/5.png)

Under the "Project" column on the left side of the main window of the project, you can see the file list of the project. These files are stored in the following groups, respectively:

| Directory Group | Description                                                  |
| :-------------- | ------------------------------------------------------------ |
| Applications    | The corresponding directory is rtthread_simulator_v0.1.0/applications, used to store user application code. |
| Drivers         | The corresponding directory is rtthread_simulator_v0.1.0/drivers, used to store the bottom driver code for RT-Thread. |
| STM32_HAL       | The corresponding directory is rtthread_simulator_v0.1.0/Libraries/CMSIS/Device/ST/STM32F1xx, used to store the firmware library files of STM32. |
| kernel-sample   | The corresponding directory is rtthread_simulator_v0.1.0/kernel-sample-0.1.0, used to store kernel samples of RT-Thread. |
| Kernel          | The corresponding directory is rtthread_simulator_v0.1.0/src, used to store RT-Thread kernel core code. |
| CORTEX-M3       | The corresponding directory is rtthread_simulator_v0.1.0/rt-thread/libcpu, used to store ARM Cortex-M3 porting code. |
| DeviceDrivers   | The corresponding directory is rtthread_simulator_v0.1.0/rt-thread/components/drivers, used to store driver framework source code of RT-Thread. |
| finsh           | The corresponding directory is rtthread_simulator_v0.1.0/rt-thread/components/finsh, used to store command line of RT-Thread finsh command line component. |

Now let's click the button from the toolbar on the top the window,![img](./figures/compile.jpg), compiling the project as shown:

![compiling](./figures/9.png)

The result of the compilation is displayed in the "Build Output" bar at the bottom of the window. If nothing else, it will say "0 Error(s), * Warning(s)." on the last line, that is, there are no errors or warnings.

After compiling RT-Thread/STM32, we can simulate running RT-Thread through the MDK-ARM simulator. Click ![img](./figures/debug.jpg)at the top right of the window or directly hit Ctrl+F5 to enter the simulation interface and hit F5 to start, then click the button in the toolbar shown in the screen shot or select “View→Serial Windows→UART#1” in the menu bar to open the serial port 1 window. You can see that the output of the serial port only shows the LOGO of RT-Thread. This is because the user code is empty and the result of its simulation is as shown:

![simulate RT-Thread1](./figures/10.png)

>We can output all the commands supported by the current system by inputting the Tab key or `help + enter ` , as shown in the following figure.

![simulate RT-Thread2](./figures/6.png)


## User Entry Code

The above startup code is basically related to the RT-Thread system, so how do users add initialization code for their own applications? RT-Thread uses main function as the user code entry, all you need to do is just add your own code to the main function.

```c
int main(void)
{
  /* user app entry */
  return 0;
}
```

>Note: In order to complete the initialization for the system functions before entering the main program, you can use the `$sub$$` and `$super$$` function identifiers to call another sample before entering the main program, this was, users can ignore the initialization operations before the main() function. See [ARM® Compiler v5.06 for µVision® armlink User Guide](http://infocenter.arm.com/help/index.jsp?topic=/com.arm.doc.dui0377g/pge1362065967698.html) for details.

## Example of a Marquee

For technical engineers working on electronics, marquee is probably the simplest example, it is like the first program Hello World in every programming language that programmers learned. So we will start with a marquee in the following example, to make it periodically update (turn on or off) the LED.

Under UART#1, input msh command: led and then click Enter to run it, as shown:

![run led](./figures/11.png)

**Example of a Marquee**

```c
/*
 * Manifest of programs: Marquee sample
 *
 * marquee is probably the simplest example, it is like the first program
 * Hello World in every programming language that programmers learned. So we will start with a marquee in the following example, start a thread to make it periodically
 * update (turn on or off) the LED.
 */

int led(void)
{
    rt_uint8_t count;

    rt_pin_mode(LED_PIN, PIN_MODE_OUTPUT);

    for(count = 0 ; count < 10 ;count++)
    {
        rt_pin_write(LED_PIN, PIN_HIGH);
        rt_kprintf("led on, count : %d\r\n", count);
        rt_thread_mdelay(500);

        rt_pin_write(LED_PIN, PIN_LOW);
        rt_kprintf("led off\r\n");
        rt_thread_mdelay(500);
    }
    return 0;
}
MSH_CMD_EXPORT(led, RT-Thread first led sample);
```

## Other Examples

Additional kernel examples can be found in the kernel-sample-0.1.0 directory.

![more kernel samples](./figures/14.png)

## Frequently Asked Question

* Compilation error occurred as following:

```
rt-thread\src\kservice.c(823): error: #929: incorrect use of vaarg fieldwidth = aarg(args, int);
rt-thread\src\kservice.c(842): error: #929: incorrect use of vaarg precision = aarg(args, int);
………
```

Cause: This type of problem is usually caused by installation of ADS, when ADS and keil coexist, the header file of va_start points to the ADS folder.

Solution:

- Delete ADS environment variables
- Uninstall ADS and keil, restart the computer, reload keil



