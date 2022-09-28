################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
Kernel/clock.obj: E:/Documents/workspace/C/rt-thread/src/clock.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccs1040/ccs/tools/compiler/ti-cgt-c2000_20.2.5.LTS/bin/cl2000" -v28 -ml -mt --cla_support=cla1 --float_support=softlib --tmu_support=tmu0 --vcu_support=vcu2 --include_path="E:/Documents/workspace/C/rt-thread/bsp/tms320f28379d" --include_path="E:/Documents/workspace/C/rt-thread/components/finsh" --include_path="E:/Documents/workspace/C/rt-thread/components/drivers/include" --include_path="E:/Documents/workspace/C/rt-thread/bsp/tms320f28379d/libraries/headers/include" --include_path="E:/Documents/workspace/C/rt-thread/bsp/tms320f28379d/libraries/common/include" --include_path="E:/Documents/workspace/C/rt-thread/include" --include_path="E:/Documents/workspace/C/rt-thread/bsp/tms320f28379d/drivers" --include_path="E:/Documents/workspace/C/rt-thread/src" --include_path="E:/Documents/workspace/C/rt-thread/components/drivers/include/drivers" --include_path="C:/ti/ccs1040/ccs/tools/compiler/ti-cgt-c2000_20.2.5.LTS/include" --advice:performance=all --define=CPU1 --define=_RAM --define=_LAUNCHXL_F28379D --define=RT_USING_LIBC -g --diag_warning=225 --diag_wrap=off --display_error_number --abi=coffabi --preproc_with_compile --preproc_dependency="Kernel/$(basename $(<F)).d_raw" --obj_directory="Kernel" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

Kernel/components.obj: E:/Documents/workspace/C/rt-thread/src/components.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccs1040/ccs/tools/compiler/ti-cgt-c2000_20.2.5.LTS/bin/cl2000" -v28 -ml -mt --cla_support=cla1 --float_support=softlib --tmu_support=tmu0 --vcu_support=vcu2 --include_path="E:/Documents/workspace/C/rt-thread/bsp/tms320f28379d" --include_path="E:/Documents/workspace/C/rt-thread/components/finsh" --include_path="E:/Documents/workspace/C/rt-thread/components/drivers/include" --include_path="E:/Documents/workspace/C/rt-thread/bsp/tms320f28379d/libraries/headers/include" --include_path="E:/Documents/workspace/C/rt-thread/bsp/tms320f28379d/libraries/common/include" --include_path="E:/Documents/workspace/C/rt-thread/include" --include_path="E:/Documents/workspace/C/rt-thread/bsp/tms320f28379d/drivers" --include_path="E:/Documents/workspace/C/rt-thread/src" --include_path="E:/Documents/workspace/C/rt-thread/components/drivers/include/drivers" --include_path="C:/ti/ccs1040/ccs/tools/compiler/ti-cgt-c2000_20.2.5.LTS/include" --advice:performance=all --define=CPU1 --define=_RAM --define=_LAUNCHXL_F28379D --define=RT_USING_LIBC -g --diag_warning=225 --diag_wrap=off --display_error_number --abi=coffabi --preproc_with_compile --preproc_dependency="Kernel/$(basename $(<F)).d_raw" --obj_directory="Kernel" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

Kernel/cpu.obj: E:/Documents/workspace/C/rt-thread/src/cpu.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccs1040/ccs/tools/compiler/ti-cgt-c2000_20.2.5.LTS/bin/cl2000" -v28 -ml -mt --cla_support=cla1 --float_support=softlib --tmu_support=tmu0 --vcu_support=vcu2 --include_path="E:/Documents/workspace/C/rt-thread/bsp/tms320f28379d" --include_path="E:/Documents/workspace/C/rt-thread/components/finsh" --include_path="E:/Documents/workspace/C/rt-thread/components/drivers/include" --include_path="E:/Documents/workspace/C/rt-thread/bsp/tms320f28379d/libraries/headers/include" --include_path="E:/Documents/workspace/C/rt-thread/bsp/tms320f28379d/libraries/common/include" --include_path="E:/Documents/workspace/C/rt-thread/include" --include_path="E:/Documents/workspace/C/rt-thread/bsp/tms320f28379d/drivers" --include_path="E:/Documents/workspace/C/rt-thread/src" --include_path="E:/Documents/workspace/C/rt-thread/components/drivers/include/drivers" --include_path="C:/ti/ccs1040/ccs/tools/compiler/ti-cgt-c2000_20.2.5.LTS/include" --advice:performance=all --define=CPU1 --define=_RAM --define=_LAUNCHXL_F28379D --define=RT_USING_LIBC -g --diag_warning=225 --diag_wrap=off --display_error_number --abi=coffabi --preproc_with_compile --preproc_dependency="Kernel/$(basename $(<F)).d_raw" --obj_directory="Kernel" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

Kernel/device.obj: E:/Documents/workspace/C/rt-thread/src/device.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccs1040/ccs/tools/compiler/ti-cgt-c2000_20.2.5.LTS/bin/cl2000" -v28 -ml -mt --cla_support=cla1 --float_support=softlib --tmu_support=tmu0 --vcu_support=vcu2 --include_path="E:/Documents/workspace/C/rt-thread/bsp/tms320f28379d" --include_path="E:/Documents/workspace/C/rt-thread/components/finsh" --include_path="E:/Documents/workspace/C/rt-thread/components/drivers/include" --include_path="E:/Documents/workspace/C/rt-thread/bsp/tms320f28379d/libraries/headers/include" --include_path="E:/Documents/workspace/C/rt-thread/bsp/tms320f28379d/libraries/common/include" --include_path="E:/Documents/workspace/C/rt-thread/include" --include_path="E:/Documents/workspace/C/rt-thread/bsp/tms320f28379d/drivers" --include_path="E:/Documents/workspace/C/rt-thread/src" --include_path="E:/Documents/workspace/C/rt-thread/components/drivers/include/drivers" --include_path="C:/ti/ccs1040/ccs/tools/compiler/ti-cgt-c2000_20.2.5.LTS/include" --advice:performance=all --define=CPU1 --define=_RAM --define=_LAUNCHXL_F28379D --define=RT_USING_LIBC -g --diag_warning=225 --diag_wrap=off --display_error_number --abi=coffabi --preproc_with_compile --preproc_dependency="Kernel/$(basename $(<F)).d_raw" --obj_directory="Kernel" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

Kernel/idle.obj: E:/Documents/workspace/C/rt-thread/src/idle.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccs1040/ccs/tools/compiler/ti-cgt-c2000_20.2.5.LTS/bin/cl2000" -v28 -ml -mt --cla_support=cla1 --float_support=softlib --tmu_support=tmu0 --vcu_support=vcu2 --include_path="E:/Documents/workspace/C/rt-thread/bsp/tms320f28379d" --include_path="E:/Documents/workspace/C/rt-thread/components/finsh" --include_path="E:/Documents/workspace/C/rt-thread/components/drivers/include" --include_path="E:/Documents/workspace/C/rt-thread/bsp/tms320f28379d/libraries/headers/include" --include_path="E:/Documents/workspace/C/rt-thread/bsp/tms320f28379d/libraries/common/include" --include_path="E:/Documents/workspace/C/rt-thread/include" --include_path="E:/Documents/workspace/C/rt-thread/bsp/tms320f28379d/drivers" --include_path="E:/Documents/workspace/C/rt-thread/src" --include_path="E:/Documents/workspace/C/rt-thread/components/drivers/include/drivers" --include_path="C:/ti/ccs1040/ccs/tools/compiler/ti-cgt-c2000_20.2.5.LTS/include" --advice:performance=all --define=CPU1 --define=_RAM --define=_LAUNCHXL_F28379D --define=RT_USING_LIBC -g --diag_warning=225 --diag_wrap=off --display_error_number --abi=coffabi --preproc_with_compile --preproc_dependency="Kernel/$(basename $(<F)).d_raw" --obj_directory="Kernel" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

Kernel/ipc.obj: E:/Documents/workspace/C/rt-thread/src/ipc.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccs1040/ccs/tools/compiler/ti-cgt-c2000_20.2.5.LTS/bin/cl2000" -v28 -ml -mt --cla_support=cla1 --float_support=softlib --tmu_support=tmu0 --vcu_support=vcu2 --include_path="E:/Documents/workspace/C/rt-thread/bsp/tms320f28379d" --include_path="E:/Documents/workspace/C/rt-thread/components/finsh" --include_path="E:/Documents/workspace/C/rt-thread/components/drivers/include" --include_path="E:/Documents/workspace/C/rt-thread/bsp/tms320f28379d/libraries/headers/include" --include_path="E:/Documents/workspace/C/rt-thread/bsp/tms320f28379d/libraries/common/include" --include_path="E:/Documents/workspace/C/rt-thread/include" --include_path="E:/Documents/workspace/C/rt-thread/bsp/tms320f28379d/drivers" --include_path="E:/Documents/workspace/C/rt-thread/src" --include_path="E:/Documents/workspace/C/rt-thread/components/drivers/include/drivers" --include_path="C:/ti/ccs1040/ccs/tools/compiler/ti-cgt-c2000_20.2.5.LTS/include" --advice:performance=all --define=CPU1 --define=_RAM --define=_LAUNCHXL_F28379D --define=RT_USING_LIBC -g --diag_warning=225 --diag_wrap=off --display_error_number --abi=coffabi --preproc_with_compile --preproc_dependency="Kernel/$(basename $(<F)).d_raw" --obj_directory="Kernel" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

Kernel/irq.obj: E:/Documents/workspace/C/rt-thread/src/irq.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccs1040/ccs/tools/compiler/ti-cgt-c2000_20.2.5.LTS/bin/cl2000" -v28 -ml -mt --cla_support=cla1 --float_support=softlib --tmu_support=tmu0 --vcu_support=vcu2 --include_path="E:/Documents/workspace/C/rt-thread/bsp/tms320f28379d" --include_path="E:/Documents/workspace/C/rt-thread/components/finsh" --include_path="E:/Documents/workspace/C/rt-thread/components/drivers/include" --include_path="E:/Documents/workspace/C/rt-thread/bsp/tms320f28379d/libraries/headers/include" --include_path="E:/Documents/workspace/C/rt-thread/bsp/tms320f28379d/libraries/common/include" --include_path="E:/Documents/workspace/C/rt-thread/include" --include_path="E:/Documents/workspace/C/rt-thread/bsp/tms320f28379d/drivers" --include_path="E:/Documents/workspace/C/rt-thread/src" --include_path="E:/Documents/workspace/C/rt-thread/components/drivers/include/drivers" --include_path="C:/ti/ccs1040/ccs/tools/compiler/ti-cgt-c2000_20.2.5.LTS/include" --advice:performance=all --define=CPU1 --define=_RAM --define=_LAUNCHXL_F28379D --define=RT_USING_LIBC -g --diag_warning=225 --diag_wrap=off --display_error_number --abi=coffabi --preproc_with_compile --preproc_dependency="Kernel/$(basename $(<F)).d_raw" --obj_directory="Kernel" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

Kernel/kservice.obj: E:/Documents/workspace/C/rt-thread/src/kservice.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccs1040/ccs/tools/compiler/ti-cgt-c2000_20.2.5.LTS/bin/cl2000" -v28 -ml -mt --cla_support=cla1 --float_support=softlib --tmu_support=tmu0 --vcu_support=vcu2 --include_path="E:/Documents/workspace/C/rt-thread/bsp/tms320f28379d" --include_path="E:/Documents/workspace/C/rt-thread/components/finsh" --include_path="E:/Documents/workspace/C/rt-thread/components/drivers/include" --include_path="E:/Documents/workspace/C/rt-thread/bsp/tms320f28379d/libraries/headers/include" --include_path="E:/Documents/workspace/C/rt-thread/bsp/tms320f28379d/libraries/common/include" --include_path="E:/Documents/workspace/C/rt-thread/include" --include_path="E:/Documents/workspace/C/rt-thread/bsp/tms320f28379d/drivers" --include_path="E:/Documents/workspace/C/rt-thread/src" --include_path="E:/Documents/workspace/C/rt-thread/components/drivers/include/drivers" --include_path="C:/ti/ccs1040/ccs/tools/compiler/ti-cgt-c2000_20.2.5.LTS/include" --advice:performance=all --define=CPU1 --define=_RAM --define=_LAUNCHXL_F28379D --define=RT_USING_LIBC -g --diag_warning=225 --diag_wrap=off --display_error_number --abi=coffabi --preproc_with_compile --preproc_dependency="Kernel/$(basename $(<F)).d_raw" --obj_directory="Kernel" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

Kernel/mem.obj: E:/Documents/workspace/C/rt-thread/src/mem.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccs1040/ccs/tools/compiler/ti-cgt-c2000_20.2.5.LTS/bin/cl2000" -v28 -ml -mt --cla_support=cla1 --float_support=softlib --tmu_support=tmu0 --vcu_support=vcu2 --include_path="E:/Documents/workspace/C/rt-thread/bsp/tms320f28379d" --include_path="E:/Documents/workspace/C/rt-thread/components/finsh" --include_path="E:/Documents/workspace/C/rt-thread/components/drivers/include" --include_path="E:/Documents/workspace/C/rt-thread/bsp/tms320f28379d/libraries/headers/include" --include_path="E:/Documents/workspace/C/rt-thread/bsp/tms320f28379d/libraries/common/include" --include_path="E:/Documents/workspace/C/rt-thread/include" --include_path="E:/Documents/workspace/C/rt-thread/bsp/tms320f28379d/drivers" --include_path="E:/Documents/workspace/C/rt-thread/src" --include_path="E:/Documents/workspace/C/rt-thread/components/drivers/include/drivers" --include_path="C:/ti/ccs1040/ccs/tools/compiler/ti-cgt-c2000_20.2.5.LTS/include" --advice:performance=all --define=CPU1 --define=_RAM --define=_LAUNCHXL_F28379D --define=RT_USING_LIBC -g --diag_warning=225 --diag_wrap=off --display_error_number --abi=coffabi --preproc_with_compile --preproc_dependency="Kernel/$(basename $(<F)).d_raw" --obj_directory="Kernel" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

Kernel/memheap.obj: E:/Documents/workspace/C/rt-thread/src/memheap.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccs1040/ccs/tools/compiler/ti-cgt-c2000_20.2.5.LTS/bin/cl2000" -v28 -ml -mt --cla_support=cla1 --float_support=softlib --tmu_support=tmu0 --vcu_support=vcu2 --include_path="E:/Documents/workspace/C/rt-thread/bsp/tms320f28379d" --include_path="E:/Documents/workspace/C/rt-thread/components/finsh" --include_path="E:/Documents/workspace/C/rt-thread/components/drivers/include" --include_path="E:/Documents/workspace/C/rt-thread/bsp/tms320f28379d/libraries/headers/include" --include_path="E:/Documents/workspace/C/rt-thread/bsp/tms320f28379d/libraries/common/include" --include_path="E:/Documents/workspace/C/rt-thread/include" --include_path="E:/Documents/workspace/C/rt-thread/bsp/tms320f28379d/drivers" --include_path="E:/Documents/workspace/C/rt-thread/src" --include_path="E:/Documents/workspace/C/rt-thread/components/drivers/include/drivers" --include_path="C:/ti/ccs1040/ccs/tools/compiler/ti-cgt-c2000_20.2.5.LTS/include" --advice:performance=all --define=CPU1 --define=_RAM --define=_LAUNCHXL_F28379D --define=RT_USING_LIBC -g --diag_warning=225 --diag_wrap=off --display_error_number --abi=coffabi --preproc_with_compile --preproc_dependency="Kernel/$(basename $(<F)).d_raw" --obj_directory="Kernel" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

Kernel/mempool.obj: E:/Documents/workspace/C/rt-thread/src/mempool.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccs1040/ccs/tools/compiler/ti-cgt-c2000_20.2.5.LTS/bin/cl2000" -v28 -ml -mt --cla_support=cla1 --float_support=softlib --tmu_support=tmu0 --vcu_support=vcu2 --include_path="E:/Documents/workspace/C/rt-thread/bsp/tms320f28379d" --include_path="E:/Documents/workspace/C/rt-thread/components/finsh" --include_path="E:/Documents/workspace/C/rt-thread/components/drivers/include" --include_path="E:/Documents/workspace/C/rt-thread/bsp/tms320f28379d/libraries/headers/include" --include_path="E:/Documents/workspace/C/rt-thread/bsp/tms320f28379d/libraries/common/include" --include_path="E:/Documents/workspace/C/rt-thread/include" --include_path="E:/Documents/workspace/C/rt-thread/bsp/tms320f28379d/drivers" --include_path="E:/Documents/workspace/C/rt-thread/src" --include_path="E:/Documents/workspace/C/rt-thread/components/drivers/include/drivers" --include_path="C:/ti/ccs1040/ccs/tools/compiler/ti-cgt-c2000_20.2.5.LTS/include" --advice:performance=all --define=CPU1 --define=_RAM --define=_LAUNCHXL_F28379D --define=RT_USING_LIBC -g --diag_warning=225 --diag_wrap=off --display_error_number --abi=coffabi --preproc_with_compile --preproc_dependency="Kernel/$(basename $(<F)).d_raw" --obj_directory="Kernel" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

Kernel/object.obj: E:/Documents/workspace/C/rt-thread/src/object.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccs1040/ccs/tools/compiler/ti-cgt-c2000_20.2.5.LTS/bin/cl2000" -v28 -ml -mt --cla_support=cla1 --float_support=softlib --tmu_support=tmu0 --vcu_support=vcu2 --include_path="E:/Documents/workspace/C/rt-thread/bsp/tms320f28379d" --include_path="E:/Documents/workspace/C/rt-thread/components/finsh" --include_path="E:/Documents/workspace/C/rt-thread/components/drivers/include" --include_path="E:/Documents/workspace/C/rt-thread/bsp/tms320f28379d/libraries/headers/include" --include_path="E:/Documents/workspace/C/rt-thread/bsp/tms320f28379d/libraries/common/include" --include_path="E:/Documents/workspace/C/rt-thread/include" --include_path="E:/Documents/workspace/C/rt-thread/bsp/tms320f28379d/drivers" --include_path="E:/Documents/workspace/C/rt-thread/src" --include_path="E:/Documents/workspace/C/rt-thread/components/drivers/include/drivers" --include_path="C:/ti/ccs1040/ccs/tools/compiler/ti-cgt-c2000_20.2.5.LTS/include" --advice:performance=all --define=CPU1 --define=_RAM --define=_LAUNCHXL_F28379D --define=RT_USING_LIBC -g --diag_warning=225 --diag_wrap=off --display_error_number --abi=coffabi --preproc_with_compile --preproc_dependency="Kernel/$(basename $(<F)).d_raw" --obj_directory="Kernel" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

Kernel/scheduler.obj: E:/Documents/workspace/C/rt-thread/src/scheduler.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccs1040/ccs/tools/compiler/ti-cgt-c2000_20.2.5.LTS/bin/cl2000" -v28 -ml -mt --cla_support=cla1 --float_support=softlib --tmu_support=tmu0 --vcu_support=vcu2 --include_path="E:/Documents/workspace/C/rt-thread/bsp/tms320f28379d" --include_path="E:/Documents/workspace/C/rt-thread/components/finsh" --include_path="E:/Documents/workspace/C/rt-thread/components/drivers/include" --include_path="E:/Documents/workspace/C/rt-thread/bsp/tms320f28379d/libraries/headers/include" --include_path="E:/Documents/workspace/C/rt-thread/bsp/tms320f28379d/libraries/common/include" --include_path="E:/Documents/workspace/C/rt-thread/include" --include_path="E:/Documents/workspace/C/rt-thread/bsp/tms320f28379d/drivers" --include_path="E:/Documents/workspace/C/rt-thread/src" --include_path="E:/Documents/workspace/C/rt-thread/components/drivers/include/drivers" --include_path="C:/ti/ccs1040/ccs/tools/compiler/ti-cgt-c2000_20.2.5.LTS/include" --advice:performance=all --define=CPU1 --define=_RAM --define=_LAUNCHXL_F28379D --define=RT_USING_LIBC -g --diag_warning=225 --diag_wrap=off --display_error_number --abi=coffabi --preproc_with_compile --preproc_dependency="Kernel/$(basename $(<F)).d_raw" --obj_directory="Kernel" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

Kernel/signal.obj: E:/Documents/workspace/C/rt-thread/src/signal.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccs1040/ccs/tools/compiler/ti-cgt-c2000_20.2.5.LTS/bin/cl2000" -v28 -ml -mt --cla_support=cla1 --float_support=softlib --tmu_support=tmu0 --vcu_support=vcu2 --include_path="E:/Documents/workspace/C/rt-thread/bsp/tms320f28379d" --include_path="E:/Documents/workspace/C/rt-thread/components/finsh" --include_path="E:/Documents/workspace/C/rt-thread/components/drivers/include" --include_path="E:/Documents/workspace/C/rt-thread/bsp/tms320f28379d/libraries/headers/include" --include_path="E:/Documents/workspace/C/rt-thread/bsp/tms320f28379d/libraries/common/include" --include_path="E:/Documents/workspace/C/rt-thread/include" --include_path="E:/Documents/workspace/C/rt-thread/bsp/tms320f28379d/drivers" --include_path="E:/Documents/workspace/C/rt-thread/src" --include_path="E:/Documents/workspace/C/rt-thread/components/drivers/include/drivers" --include_path="C:/ti/ccs1040/ccs/tools/compiler/ti-cgt-c2000_20.2.5.LTS/include" --advice:performance=all --define=CPU1 --define=_RAM --define=_LAUNCHXL_F28379D --define=RT_USING_LIBC -g --diag_warning=225 --diag_wrap=off --display_error_number --abi=coffabi --preproc_with_compile --preproc_dependency="Kernel/$(basename $(<F)).d_raw" --obj_directory="Kernel" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

Kernel/slab.obj: E:/Documents/workspace/C/rt-thread/src/slab.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccs1040/ccs/tools/compiler/ti-cgt-c2000_20.2.5.LTS/bin/cl2000" -v28 -ml -mt --cla_support=cla1 --float_support=softlib --tmu_support=tmu0 --vcu_support=vcu2 --include_path="E:/Documents/workspace/C/rt-thread/bsp/tms320f28379d" --include_path="E:/Documents/workspace/C/rt-thread/components/finsh" --include_path="E:/Documents/workspace/C/rt-thread/components/drivers/include" --include_path="E:/Documents/workspace/C/rt-thread/bsp/tms320f28379d/libraries/headers/include" --include_path="E:/Documents/workspace/C/rt-thread/bsp/tms320f28379d/libraries/common/include" --include_path="E:/Documents/workspace/C/rt-thread/include" --include_path="E:/Documents/workspace/C/rt-thread/bsp/tms320f28379d/drivers" --include_path="E:/Documents/workspace/C/rt-thread/src" --include_path="E:/Documents/workspace/C/rt-thread/components/drivers/include/drivers" --include_path="C:/ti/ccs1040/ccs/tools/compiler/ti-cgt-c2000_20.2.5.LTS/include" --advice:performance=all --define=CPU1 --define=_RAM --define=_LAUNCHXL_F28379D --define=RT_USING_LIBC -g --diag_warning=225 --diag_wrap=off --display_error_number --abi=coffabi --preproc_with_compile --preproc_dependency="Kernel/$(basename $(<F)).d_raw" --obj_directory="Kernel" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

Kernel/thread.obj: E:/Documents/workspace/C/rt-thread/src/thread.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccs1040/ccs/tools/compiler/ti-cgt-c2000_20.2.5.LTS/bin/cl2000" -v28 -ml -mt --cla_support=cla1 --float_support=softlib --tmu_support=tmu0 --vcu_support=vcu2 --include_path="E:/Documents/workspace/C/rt-thread/bsp/tms320f28379d" --include_path="E:/Documents/workspace/C/rt-thread/components/finsh" --include_path="E:/Documents/workspace/C/rt-thread/components/drivers/include" --include_path="E:/Documents/workspace/C/rt-thread/bsp/tms320f28379d/libraries/headers/include" --include_path="E:/Documents/workspace/C/rt-thread/bsp/tms320f28379d/libraries/common/include" --include_path="E:/Documents/workspace/C/rt-thread/include" --include_path="E:/Documents/workspace/C/rt-thread/bsp/tms320f28379d/drivers" --include_path="E:/Documents/workspace/C/rt-thread/src" --include_path="E:/Documents/workspace/C/rt-thread/components/drivers/include/drivers" --include_path="C:/ti/ccs1040/ccs/tools/compiler/ti-cgt-c2000_20.2.5.LTS/include" --advice:performance=all --define=CPU1 --define=_RAM --define=_LAUNCHXL_F28379D --define=RT_USING_LIBC -g --diag_warning=225 --diag_wrap=off --display_error_number --abi=coffabi --preproc_with_compile --preproc_dependency="Kernel/$(basename $(<F)).d_raw" --obj_directory="Kernel" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

Kernel/timer.obj: E:/Documents/workspace/C/rt-thread/src/timer.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccs1040/ccs/tools/compiler/ti-cgt-c2000_20.2.5.LTS/bin/cl2000" -v28 -ml -mt --cla_support=cla1 --float_support=softlib --tmu_support=tmu0 --vcu_support=vcu2 --include_path="E:/Documents/workspace/C/rt-thread/bsp/tms320f28379d" --include_path="E:/Documents/workspace/C/rt-thread/components/finsh" --include_path="E:/Documents/workspace/C/rt-thread/components/drivers/include" --include_path="E:/Documents/workspace/C/rt-thread/bsp/tms320f28379d/libraries/headers/include" --include_path="E:/Documents/workspace/C/rt-thread/bsp/tms320f28379d/libraries/common/include" --include_path="E:/Documents/workspace/C/rt-thread/include" --include_path="E:/Documents/workspace/C/rt-thread/bsp/tms320f28379d/drivers" --include_path="E:/Documents/workspace/C/rt-thread/src" --include_path="E:/Documents/workspace/C/rt-thread/components/drivers/include/drivers" --include_path="C:/ti/ccs1040/ccs/tools/compiler/ti-cgt-c2000_20.2.5.LTS/include" --advice:performance=all --define=CPU1 --define=_RAM --define=_LAUNCHXL_F28379D --define=RT_USING_LIBC -g --diag_warning=225 --diag_wrap=off --display_error_number --abi=coffabi --preproc_with_compile --preproc_dependency="Kernel/$(basename $(<F)).d_raw" --obj_directory="Kernel" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '


