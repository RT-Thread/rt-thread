var rtx5_impl =
[
    [ "Create an RTX5 Project", "cre_rtx_proj.html", [
      [ "Additional requirements for RTX on Cortex-A", "cre_rtx_proj.html#cre_rtx_cortexa", null ],
      [ "Using Interrupts on Cortex-M", "cre_rtx_proj.html#cre_UsingIRQs", null ],
      [ "Add support for RTX specific functions", "cre_rtx_proj.html#cre_rtx_proj_specifics", null ],
      [ "Add Event Recorder Visibility", "cre_rtx_proj.html#cre_rtx_proj_er", null ]
    ] ],
    [ "Theory of Operation", "theory_of_operation.html", [
      [ "System Startup", "theory_of_operation.html#SystemStartup", null ],
      [ "Scheduler", "theory_of_operation.html#Scheduler", null ],
      [ "Memory Allocation", "theory_of_operation.html#MemoryAllocation", [
        [ "Global Memory Pool", "theory_of_operation.html#GlobalMemoryPool", null ],
        [ "Object-specific Memory Pools", "theory_of_operation.html#ObjectMemoryPool", null ],
        [ "Static Object Memory", "theory_of_operation.html#StaticObjectMemory", null ]
      ] ],
      [ "Thread Stack Management", "theory_of_operation.html#ThreadStack", null ],
      [ "Low-Power Operation", "theory_of_operation.html#lowPower", null ],
      [ "RTX Kernel Timer Tick", "theory_of_operation.html#kernelTimer", [
        [ "Tick-less Low-Power Operation", "theory_of_operation.html#TickLess", null ]
      ] ],
      [ "RTX5 Header File", "theory_of_operation.html#rtx_os_h", null ],
      [ "Timeout Value", "theory_of_operation.html#CMSIS_RTOS_TimeOutValue", null ],
      [ "Calls from Interrupt Service Routines", "theory_of_operation.html#CMSIS_RTOS_ISR_Calls", null ]
    ] ],
    [ "Configure RTX v5", "config_rtx5.html", [
      [ "System Configuration", "config_rtx5.html#systemConfig", [
        [ "Global dynamic memory", "config_rtx5.html#systemConfig_glob_mem", null ],
        [ "Round-Robin Thread Switching", "config_rtx5.html#systemConfig_rr", null ],
        [ "ISR FIFO Queue", "config_rtx5.html#systemConfig_isr_fifo", null ],
        [ "Object Memory Usage Counters", "config_rtx5.html#systemConfig_usage_counters", null ]
      ] ],
      [ "Thread Configuration", "config_rtx5.html#threadConfig", [
        [ "Configuration of Thread Count and Stack Space", "config_rtx5.html#threadConfig_countstack", null ],
        [ "Stack Overflow Checking", "config_rtx5.html#threadConfig_ovfcheck", null ],
        [ "Stack Usage Watermark", "config_rtx5.html#threadConfig_watermark", null ],
        [ "Processor Mode for Thread Execution", "config_rtx5.html#threadConfig_procmode", null ]
      ] ],
      [ "Timer Configuration", "config_rtx5.html#timerConfig", [
        [ "Object-specific memory allocation", "config_rtx5.html#timerConfig_obj", null ],
        [ "User Timer Thread", "config_rtx5.html#timerConfig_user", null ]
      ] ],
      [ "Event Flags Configuration", "config_rtx5.html#eventFlagsConfig", [
        [ "Object-specific memory allocation", "config_rtx5.html#eventFlagsConfig_obj", null ]
      ] ],
      [ "Mutex Configuration", "config_rtx5.html#mutexConfig", [
        [ "Object-specific Memory Allocation", "config_rtx5.html#mutexConfig_obj", null ]
      ] ],
      [ "Semaphore Configuration", "config_rtx5.html#semaphoreConfig", [
        [ "Object-specific memory allocation", "config_rtx5.html#semaphoreConfig_obj", null ]
      ] ],
      [ "Memory Pool Configuration", "config_rtx5.html#memPoolConfig", [
        [ "Object-specific memory allocation", "config_rtx5.html#memPoolConfig_obj", null ]
      ] ],
      [ "Message Queue Configuration", "config_rtx5.html#msgQueueConfig", [
        [ "Object-specific memory allocation", "config_rtx5.html#msgQueueConfig_obj", null ]
      ] ],
      [ "Event Recorder Configuration", "config_rtx5.html#evtrecConfig", [
        [ "Global Configuration", "config_rtx5.html#evtrecConfigGlobIni", null ],
        [ "RTOS Event Generation", "config_rtx5.html#evtrecConfigEvtGen", null ],
        [ "Manual event configuration", "config_rtx5.html#systemConfig_event_recording", null ]
      ] ]
    ] ],
    [ "Building the RTX5 Library", "creating_RTX5_LIB.html", null ],
    [ "Technical Data", "technicalData5.html", "technicalData5" ],
    [ "MISRA C:2012 Compliance", "misraCompliance5.html", [
      [ "[MISRA Note 1]: Return statements for parameter checking", "misraCompliance5.html#MISRA_1", null ],
      [ "[MISRA Note 2]: Object identifiers are void pointers", "misraCompliance5.html#MISRA_2", null ],
      [ "[MISRA Note 3]: Conversion to unified object control blocks", "misraCompliance5.html#MISRA_3", null ],
      [ "[MISRA Note 4]: Conversion from unified object control blocks", "misraCompliance5.html#MISRA_4", null ],
      [ "[MISRA Note 5]: Conversion to object types", "misraCompliance5.html#MISRA_5", null ],
      [ "[MISRA Note 6]: Conversion from user provided storage", "misraCompliance5.html#MISRA_6", null ],
      [ "[MISRA Note 7]: Check for proper pointer alignment", "misraCompliance5.html#MISRA_7", null ],
      [ "[MISRA Note 8]: Memory allocation management", "misraCompliance5.html#MISRA_8", null ],
      [ "[MISRA Note 9]: Pointer conversions for register access", "misraCompliance5.html#MISRA_9", null ],
      [ "[MISRA Note 10]: SVC calls use function-like macros", "misraCompliance5.html#MISRA_10", null ],
      [ "[MISRA Note 11]: SVC calls use assembly code", "misraCompliance5.html#MISRA_11", null ],
      [ "[MISRA Note 12]: Usage of exclusive access instructions", "misraCompliance5.html#MISRA_12", null ],
      [ "[MISRA Note 13]: Usage of Event Recorder", "misraCompliance5.html#MISRA_13", null ]
    ] ]
];