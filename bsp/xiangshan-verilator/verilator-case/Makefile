VERILATOR ?= verilator
TOP       := dut_150
TB        := tb_150.cpp
SRC       := $(TOP).v
APP_DIR   := ../applications
OUT_DIR   := $(APP_DIR)/verilated_$(TOP)

# Keep the generated model strictly single-threaded and avoid features
# that pull in timing/coroutine support which we trimmed from the runtime.
VERILATOR_FLAGS := --no-timing --no-trace --threads 1
# Propagate our RT-Thread specific switches into generated code.
VERILATOR_CFLAGS := -DVL_RT_THREAD -DVL_MT_DISABLED

.PHONY: all clean

all: $(OUT_DIR)/V$(TOP).cpp

$(OUT_DIR)/V$(TOP).cpp: $(SRC) $(TB) Makefile
	@mkdir -p $(OUT_DIR)
	$(VERILATOR) -Wall --cc $(SRC) --exe $(TB) -Mdir $(OUT_DIR) \
		$(VERILATOR_FLAGS) --CFLAGS "$(VERILATOR_CFLAGS)"

clean:
	@rm -rf $(OUT_DIR)
