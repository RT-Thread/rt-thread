/*
 * This file is only used for doxygen document generation.
 */

/**
 * @defgroup finsh finsh shell
 *
 * @brief finsh shell is a user command shell in RT-Thread RTOS.
 *
 * finsh shell is a user command shell in RT-Thread RTOS, which is a shell can
 * accept C-expression like syntax in command. From finsh shell, user can access
 * system area, such as memory, variables and function by input C-expression in
 * command.
 *
 * @image html finsh.png "Figure 3: finsh shell architecture"
 * There is a shell thread, which named as "tshell", in the finsh shell, it read
 * user command from console device, and then invokes system function or access
 * system variable to output result (by rt_kprintf).
 */
