## Independent Interrupts Management

### Introduction
Calling `rt_hw_interrupt_disable` in multiple places on `rt-thread` may cause interruption delays when the application requires accurate interrupt responses. This is because the system cannot generate any interrupts except abnormal interrupts after disabling interrupts. This is a common problem in the interrupt management of the operating system. The independent interrupt management module is designed to solve this problem.

The independent interrupt management module is designed to solve the problem of interrupt delays caused by calling `rt_hw_interrupt_disable` in multiple places on `rt-thread`. The module is implemented by rewrite the `rt_hw_interrupt_disable` and `rt_hw_interrupt_enable` functions in the `libcpu` library. 


### Usage
- Add the following code to the project's `board.c` file.
```
#ifdef RT_USING_INDEPENDENT_INTERRUPT_MANAGEMENT
#define RT_NVIC_PRO_BITS    __NVIC_PRIO_BITS

rt_base_t rt_hw_interrupt_disable(void)
{
    rt_base_t level = __get_BASEPRI();
    __set_BASEPRI(RT_MAX_SYSCALL_INTERRUPT_PRIORITY << (8 - RT_NVIC_PRO_BITS));

    __ISB();
    __DSB();

    return level;
}

void rt_hw_interrupt_enable(rt_base_t level)
{
    __set_BASEPRI(level);
}

#endif /* RT_USING_INDEPENDENT_INTERRUPT_MANAGEMENT */
```
- Add the following configuration to the `Kconfig` file in the `board` directory.
```
    menuconfig RT_USING_INDEPENDENT_INTERRUPT_MANAGEMENT
        bool "Enable independent interrupt management"
        default n

        if RT_USING_INDEPENDENT_INTERRUPT_MANAGEMENT
            config RT_MAX_SYSCALL_INTERRUPT_PRIORITY
                int "Set max syscall interrupt priority"
                range 0 7
                default 2
        endif
```
- Select `RT_USING_INDEPENDENT_INTERRUPT_MANAGEMENT` to enable this feature.
- Select `RT_MAX_SYSCALL_INTERRUPT_PRIORITY` to set the maximum priority of the interrupt that can be called by the system call. The default value is 2.

### Description
- The [basepri](https://developer.arm.com/documentation/107706/0100/Exceptions-and-interrupts-overview/Special-registers-for-exception-masking/BASEPRI) register is used in the functions to complete the interrupt management.
- For example, if `RT_MAX_SYSCALL_INTERRUPT_PRIORITY` is set to 0x01, the system masking only interrupts with a priority of `0x01-0xFF`.
- Interrupts with a priority of 0 are not managed by the system and can continue to respond to interrupts after `rt_hw_interrupt_disable` is called.
- When using the [basepri](https://developer.arm.com/documentation/107706/0100/Exceptions-and-interrupts-overview/Special-registers-for-exception-masking/BASEPRI) register for independent interrupt management, note that interrupts with a priority value lower than `RT_MAX_SYSCALL_INTERRUPT_PRIORITY` cannot call any `system API`.
