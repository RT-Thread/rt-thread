.section .stack, "aw"
.stack_size = 0x200
.stack_space: .space .stack_size

.section .heap, "aw"
.heap_size = 0x200
.heap_space: .space .heap_size

.section .vectors, "a"
.global __Vectors
.global __Vectors_End
.global __Vectors_Size

.type __Vectors, %function
__Vectors:
    .word .stack_space + .stack_size      // Stack Pointer
    .word Reset_Handler                    // Reset
    .word NMI_Handler                      // NMI
    .word HardFault_Handler                // Hard Fault
    .word 0                                 // Reserved
    .word 0                                 // Reserved
    .word 0                                 // Reserved
    .word 0                                 // Reserved
    .word 0                                 // Reserved
    .word 0                                 // Reserved
    .word 0                                 // Reserved
    .word SVC_Handler                      // SVCall
    .word 0                                 // Reserved
    .word 0                                 // Reserved
    .word PendSV_Handler                   // PendSV
    .word SysTick_Handler                  // SysTick

    // 中断处理函数
    .word IRQ000_Handler
    .word IRQ001_Handler
    .word IRQ002_Handler
    .word IRQ003_Handler
    .word IRQ004_Handler
    .word IRQ005_Handler
    .word IRQ006_Handler
    .word IRQ007_Handler
    .word IRQ008_Handler
    .word IRQ009_Handler
    .word IRQ010_Handler
    .word IRQ011_Handler
    .word IRQ012_Handler
    .word IRQ013_Handler
    .word IRQ014_Handler
    .word IRQ015_Handler
    .word IRQ016_Handler
    .word IRQ017_Handler
    .word IRQ018_Handler
    .word IRQ019_Handler
    .word IRQ020_Handler
    .word IRQ021_Handler
    .word IRQ022_Handler
    .word IRQ023_Handler
    .word IRQ024_Handler
    .word IRQ025_Handler
    .word IRQ026_Handler
    .word IRQ027_Handler
    .word IRQ028_Handler
    .word IRQ029_Handler
    .word IRQ030_Handler
    .word IRQ031_Handler

.global __Vectors_End
__Vectors_End:
.global __Vectors_Size
__Vectors_Size = __Vectors_End - __Vectors

.section .text
.global Reset_Handler
.type Reset_Handler, %function
Reset_Handler:
    // 重置处理
    ldr r0, =0xE000ED08
    ldr r1, =.stack_space
    str r1, [r0]                     // 设置堆栈指针

    bl SystemInit                    // 调用系统初始化
    bl entry                        // 调用主函数
    b .                              // 无限循环

// 异常处理程序
.type NMI_Handler, %function
NMI_Handler:
    b .

.type HardFault_Handler, %function
HardFault_Handler:
    b .

.type SVC_Handler, %function
SVC_Handler:
    b .

.type PendSV_Handler, %function
PendSV_Handler:
    b .

.type SysTick_Handler, %function
SysTick_Handler:
    b .

.type Default_Handler, %function
Default_Handler:
    b .

// 中断处理函数的默认实现
.weak IRQ000_Handler
.thumb_set IRQ000_Handler, Default_Handler

.weak IRQ001_Handler
.thumb_set IRQ001_Handler, Default_Handler

.weak IRQ002_Handler
.thumb_set IRQ002_Handler, Default_Handler

.weak IRQ003_Handler
.thumb_set IRQ003_Handler, Default_Handler

.weak IRQ004_Handler
.thumb_set IRQ004_Handler, Default_Handler

.weak IRQ005_Handler
.thumb_set IRQ005_Handler, Default_Handler

.weak IRQ006_Handler
.thumb_set IRQ006_Handler, Default_Handler

.weak IRQ007_Handler
.thumb_set IRQ007_Handler, Default_Handler

.weak IRQ008_Handler
.thumb_set IRQ008_Handler, Default_Handler

.weak IRQ009_Handler
.thumb_set IRQ009_Handler, Default_Handler

.weak IRQ010_Handler
.thumb_set IRQ010_Handler, Default_Handler

.weak IRQ011_Handler
.thumb_set IRQ011_Handler, Default_Handler

.weak IRQ012_Handler
.thumb_set IRQ012_Handler, Default_Handler

.weak IRQ013_Handler
.thumb_set IRQ013_Handler, Default_Handler

.weak IRQ014_Handler
.thumb_set IRQ014_Handler, Default_Handler

.weak IRQ015_Handler
.thumb_set IRQ015_Handler, Default_Handler

.weak IRQ016_Handler
.thumb_set IRQ016_Handler, Default_Handler

.weak IRQ017_Handler
.thumb_set IRQ017_Handler, Default_Handler

.weak IRQ018_Handler
.thumb_set IRQ018_Handler, Default_Handler

.weak IRQ019_Handler
.thumb_set IRQ019_Handler, Default_Handler

.weak IRQ020_Handler
.thumb_set IRQ020_Handler, Default_Handler

.weak IRQ021_Handler
.thumb_set IRQ021_Handler, Default_Handler

.weak IRQ022_Handler
.thumb_set IRQ022_Handler, Default_Handler

.weak IRQ023_Handler
.thumb_set IRQ023_Handler, Default_Handler

.weak IRQ024_Handler
.thumb_set IRQ024_Handler, Default_Handler

.weak IRQ025_Handler
.thumb_set IRQ025_Handler, Default_Handler

.weak IRQ026_Handler
.thumb_set IRQ026_Handler, Default_Handler

.weak IRQ027_Handler
.thumb_set IRQ027_Handler, Default_Handler

.weak IRQ028_Handler
.thumb_set IRQ028_Handler, Default_Handler

.weak IRQ029_Handler
.thumb_set IRQ029_Handler, Default_Handler

.weak IRQ030_Handler
.thumb_set IRQ030_Handler, Default_Handler

.weak IRQ031_Handler
.thumb_set IRQ031_Handler, Default_Handler

.end
