TARGET	= disk.iso
BUILD_DIR	= build
MAP	= $(BUILD_DIR)/kernel.map
LSS	= $(BUILD_DIR)/kernel.lss

CXX ?= x86_64-linux-gnu-g++
LD 	?= ld
AS 	= nasm # Force use nasm

CXXFLAGS = -I./include 
CXXFLAGS += -I./include/driver 
CXXFLAGS += -I./include/kernel
CXXFLAGS += -fno-stack-protector 
CXXFLAGS += -fno-exceptions 
CXXFLAGS += -fno-rtti  
CXXFLAGS += -nostdlib

ASFLAGS = -felf64 

LDFLAGS = -T kernel.ld -nostdlib -n  
LDFLAGS += -Map=$(MAP)


# CPP_HEAD_FILES := $(shell find . -name *.h)
CPP_SOURCE_FILES := $(shell find . -name *.cpp)
CPP_OBJ_FILES := $(patsubst ./%.cpp, $(BUILD_DIR)/%.o, $(CPP_SOURCE_FILES))

ASM_SOURCE_FILES := $(shell find . -name *.s)
ASM_OBJ_FILES := $(patsubst ./%.s, $(BUILD_DIR)/%.o, $(ASM_SOURCE_FILES))

.PHONY: all clean info demo

all: $(TARGET) $(BUILD_DIR)/kernel.lss

info: $(ASM_SOURCE_FILES)
	@echo $(ASM_SOURCE_FILES)

$(BUILD_DIR)/kernel.bin: $(ASM_OBJ_FILES) $(CPP_OBJ_FILES)
	@mkdir -pv $(dir $@)
	$(LD) -o $@ $(LDFLAGS) $^

$(TARGET): $(BUILD_DIR)/kernel.bin
	@mkdir -pv $(BUILD_DIR)/iso/boot/
	cp $< $(BUILD_DIR)/iso/boot/ 
	grub-mkrescue /usr/lib/grub/i386-pc/ -o $@ $(BUILD_DIR)/iso/

$(ASM_OBJ_FILES): $(BUILD_DIR)/%.o : %.s
	@mkdir -pv $(dir $@)
	@echo $@ $<
	$(AS) $(ASFLAGS) $< -o $@

$(CPP_OBJ_FILES): $(BUILD_DIR)/%.o : %.cpp 
	@mkdir -pv $(dir $@)
	@echo $@ $<
	$(CXX) $(CXXFLAGS)  -c $< -o $@

$(LSS): $(BUILD_DIR)/kernel.bin
	@echo Creating .lss ...
	@mkdir -pv $(dir $@)
	@objdump -S $< > $@

clean:
	rm -rf $(ASM_OBJ_FILES) $(CPP_OBJ_FILES) $(BUILD_DIR)/kernel.bin $(TARGET) build/ 

demo: $(TARGET)
	qemu-system-x86_64 -s -cdrom $<