
#define START_POINT(funcname)               \
    .type _thread_start, %function;	        \
    .global funcname;                       \
    funcname:                               \
    .cfi_sections .debug_frame, .eh_frame;  \
    .cfi_startproc;                         \
    .cfi_undefined lr

#define START_POINT_END(name)   \
    .cfi_endproc;               \
    .size name, .-name;
