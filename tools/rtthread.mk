$(if $(strip $(TARGET)),,$(error TARGET not defined))
$(if $(strip $(SRC_FILES)),,$(error No source files))
$(if $(strip $(BSP_ROOT)),,$(error BSP_ROOT not defined))

ifneq ($(MAKE_LIB),1)
BUILD_DIR := $(BSP_ROOT)/build
endif

$(if $(strip $(BUILD_DIR)),,$(error BUILD_DIR not defined))

RTT_BUILD_DIR := RT-THREAD_OBJS
BSP_BUILD_DIR := BSP_OBJS

#################

define add_c_file
$(eval COBJ := $(1:%.c=%.o)) \
$(eval COBJ := $(COBJ:$(RTT_ROOT)/%=$(RTT_BUILD_DIR)/%)) \
$(eval COBJ := $(COBJ:$(BSP_ROOT)/%=$(BSP_BUILD_DIR)/%)) \
$(eval VPATH += $(dir $1)) \
$(eval CSRCS += $1) \
$(eval LOCALC := $(addprefix $(BUILD_DIR)/,$(COBJ))) \
$(eval OBJS += $(LOCALC)) \
$(if $(strip $(LOCALC)),$(eval $(LOCALC): $1
	@if [ ! -d $$(@D) ]; then mkdir -p $$(@D); fi
	@echo cc $$@
	@$(CROSS_COMPILE)gcc $$(CFLAGS) -c $$< -o $$@))
endef

define add_cxx_file
$(eval CXXOBJ := $(1:%.cpp=%.o)) \
$(eval CXXOBJ := $(CXXOBJ:$(RTT_ROOT)/%=$(RTT_BUILD_DIR)/%)) \
$(eval CXXOBJ := $(CXXOBJ:$(BSP_ROOT)/%=$(BSP_BUILD_DIR)/%)) \
$(eval VPATH += $(dir $1)) \
$(eval CXXSRCS += $1) \
$(eval LOCALCXX := $(addprefix $(BUILD_DIR)/,$(CXXOBJ))) \
$(eval OBJS += $(LOCALCXX)) \
$(if $(strip $(LOCALCXX)),$(eval $(LOCALCXX): $1
	@if [ ! -d $$(@D) ]; then mkdir -p $$(@D); fi
	@echo cc $$@
	@$(CROSS_COMPILE)g++ $$(CXXFLAGS) -c $$< -o $$@))
endef

define add_S_file
$(eval SOBJ := $(1:%.S=%.o)) \
$(eval SOBJ := $(SOBJ:$(RTT_ROOT)/%=$(RTT_BUILD_DIR)/%)) \
$(eval SOBJ := $(SOBJ:$(BSP_ROOT)/%=$(BSP_BUILD_DIR)/%)) \
$(eval VPATH += $(dir $1)) \
$(eval SSRCS += $(1)) \
$(eval LOCALS := $(addprefix $(BUILD_DIR)/,$(SOBJ))) \
$(eval OBJS += $(LOCALS)) \
$(if $(strip $(LOCALS)),$(eval $(LOCALS): $1
	@if [ ! -d $$(@D) ]; then mkdir -p $$(@D); fi
	@echo cc $$@
	@$(CROSS_COMPILE)gcc $$(AFLAGS) -c $$< -o $$@))
endef

add_flg = $(eval CFLAGS += $1) \
          $(eval AFLAGS += $1) \
          $(eval CXXFLAGS += $1)

add_inc = $(eval CFLAGS += -I$1) \
          $(eval AFLAGS += -I$1) \
          $(eval CXXFLAGS += -I$1)

add_def = $(eval CFLAGS += -D$1) \
          $(eval AFLAGS += -D$1) \
          $(eval CXXFLAGS += -D$1)

OBJS := 
CSRCS := 
CXXSRCS := 
SSRCS := 
VPATH :=

CONFIG_FLG := $(strip $(EXTERN_FLAGS))
$(if $(CONFIG_FLG),$(foreach f,$(CONFIG_FLG),$(call add_flg,$(f))))

CONFIG_DEF := $(strip $(PROJECT_DEFS))
$(if $(CONFIG_DEF),$(foreach d,$(CONFIG_DEF),$(call add_def,$(d))))

CONFIG_INC := $(strip $(INCLUDE_PATH))
$(if $(CONFIG_INC),$(foreach i,$(CONFIG_INC),$(call add_inc,$(i))))

SRCS := $(strip $(filter %.c,$(SRC_FILES)))
$(if $(SRCS),$(foreach f,$(SRCS),$(call add_c_file,$(f))))

SRCS := $(strip $(filter %.cpp,$(SRC_FILES)))
$(if $(SRCS),$(foreach f,$(SRCS),$(call add_cxx_file,$(f))))

SRCS := $(strip $(filter %.S,$(SRC_FILES)))
$(if $(SRCS),$(foreach f,$(SRCS),$(call add_S_file,$(f))))

CFLAGS += $(CPPPATHS)
CXXFLAGS += $(CPPPATHS)
AFLAGS += $(CPPPATHS)

CFLAGS += $(DEFINES)
CXXFLAGS += $(DEFINES)
AFLAGS += $(DEFINES)

all: $(TARGET)

ifeq ($(MAKE_LIB),1)
$(TARGET): $(OBJS)
	@echo ------------------------------------------------
	@echo ar $(TARGET)
	@$(CROSS_COMPILE)ar -rv $@ $(OBJS)
else
$(TARGET): $(OBJS) $(EXTERN_LIB)
	@echo ------------------------------------------------
	@echo link $(TARGET)
	@$(CROSS_COMPILE)g++ -o $@ $(LFLAGS) $(OBJS) $(EXTERN_LIB) -lc -lm
	@echo ------------------------------------------------
	@$(CROSS_COMPILE)objcopy -O binary $@ rtthread.bin
	@$(CROSS_COMPILE)size $@
endif

phony += clean
clean:
	@echo clean
	@rm -rf $(TARGET) $(BUILD_DIR)

.PHONY: $(phony)
