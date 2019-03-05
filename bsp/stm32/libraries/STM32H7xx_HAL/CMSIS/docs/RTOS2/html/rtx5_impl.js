var rtx5_impl =
[
    [ "Create an RTX5 Project", "cre_rtx_proj.html", [
      [ "Add support for RTX specific functions", "cre_rtx_proj.html#cre_rtx_proj_specifics", null ],
      [ "Add Event Recorder Visibility", "cre_rtx_proj.html#cre_rtx_proj_er", null ]
    ] ],
    [ "Theory of Operation", "theory_of_operation.html", [
      [ "System Startup", "theory_of_operation.html#SystemStartup", null ],
      [ "Memory Allocation", "theory_of_operation.html#MemoryAllocation", [
        [ "Global Memory Pool", "theory_of_operation.html#GlobalMemoryPool", null ],
        [ "Object-specific Memory Pools", "theory_of_operation.html#ObjectMemoryPool", null ],
        [ "Static Object Memory", "theory_of_operation.html#StaticObjectMemory", null ]
      ] ],
      [ "Thread Stack Management", "theory_of_operation.html#ThreadStack", null ],
      [ "Low-Power Operation", "theory_of_operation.html#lowPower", null ],
      [ "RTX kernel Timer Tick", "theory_of_operation.html#kernelTimer", null ],
      [ "Timeout Value", "theory_of_operation.html#CMSIS_RTOS_TimeOutValue", null ],
      [ "Calls from Interrupt Service Routines", "theory_of_operation.html#CMSIS_RTOS_ISR_Calls", null ],
      [ "Tick-less Low-Power Operation", "theory_of_operation.html#TickLess", null ],
      [ "RTX5 Header File", "theory_of_operation.html#rtx_os_h", null ]
    ] ],
    [ "Configure RTX v5", "config_rtx5.html", [
      [ "System Configuration", "config_rtx5.html#systemConfig", [
        [ "Global dynamic memory", "config_rtx5.html#systemConfig_glob_mem", null ],
        [ "Round-Robin Thread Switching", "config_rtx5.html#systemConfig_rr", null ],
        [ "ISR FIFO Queue", "config_rtx5.html#systemConfig_isr_fifo", null ]
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
      ] ]
    ] ],
    [ "Building the RTX5 Library", "creating_RTX5_LIB.html", null ],
    [ "Directory Structure and File Overview", "dirstructfiles5.html", [
      [ "RTX v5 Directory Structure", "dirstructfiles5.html#Folders", null ],
      [ "RTX v5 Library Files", "dirstructfiles5.html#libFiles", null ]
    ] ],
    [ "Technical Data", "technicalData5.html", null ],
    [ "MISRA-C Compliance Exceptions", "misraCompliance5.html", null ]
];