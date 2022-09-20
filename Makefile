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

#TODO: Separate these file by a makefile each directory
OBJS += $(BUILD_DIR)/driver/vga.o
OBJS += $(BUILD_DIR)/driver/timer.o
OBJS += $(BUILD_DIR)/driver/keyboard.o
OBJS += $(BUILD_DIR)/driver/basegraphicsdevice.o
OBJS += $(BUILD_DIR)/kernel/utils.o
OBJS += $(BUILD_DIR)/kernel/main.o
OBJS += $(BUILD_DIR)/kernel/basedriver.o
OBJS += $(BUILD_DIR)/kernel/devicemanager.o
OBJS += $(BUILD_DIR)/kernel/kernel.o
OBJS += $(BUILD_DIR)/kernel/interruptmanager.o
OBJS += $(BUILD_DIR)/kernel/printer.o
OBJS += $(BUILD_DIR)/kernel/iocommand.o
OBJS += $(BUILD_DIR)/kernel/interrupthandler.o
OBJS += $(BUILD_DIR)/kernel/taskmanager.o
OBJS += $(BUILD_DIR)/kernel/heapmemorymanager.o
OBJS += $(BUILD_DIR)/kernel/kernelobject.o
OBJS += $(BUILD_DIR)/kernel/task.o
OBJS += $(BUILD_DIR)/datastructure/list.o
OBJS += $(BUILD_DIR)/kernel/utils86.o
OBJS += $(BUILD_DIR)/kernel/ProtectedMode.o
OBJS += $(BUILD_DIR)/kernel/LongMode.o


.PHONY: all clean info demo

all: $(TARGET) $(BUILD_DIR)/kernel.lss

info: $(ASM_SOURCE_FILES)
	@echo $(ASM_SOURCE_FILES)

$(BUILD_DIR)/kernel.bin: $(OBJS)
	@mkdir -pv $(dir $@)
	$(LD) -o $@ $(LDFLAGS) $^

$(TARGET): $(BUILD_DIR)/kernel.bin
	@mkdir -pv $(BUILD_DIR)/iso/boot/
	cp $< $(BUILD_DIR)/iso/boot/ 
	grub-mkrescue /usr/lib/grub/i386-pc/ -o $@ $(BUILD_DIR)/iso/

$(BUILD_DIR)/%.o : %.s
	@mkdir -pv $(dir $@)
	@echo $@ $<
	$(AS) $(ASFLAGS) $< -o $@

$(BUILD_DIR)/%.o : %.cpp 
	@mkdir -pv $(dir $@)
	@echo $@ $<
	$(CXX) $(CXXFLAGS)  -c $< -o $@

$(LSS): $(BUILD_DIR)/kernel.bin
	@echo Creating .lss ...
	@mkdir -pv $(dir $@)
	@objdump -S $< > $@

clean:
	rm -rf $(OBJS) $(BUILD_DIR)/kernel.bin $(TARGET) build/ 

demo: $(TARGET)
	qemu-system-x86_64 -s -cdrom $<
test:
	@echo $(OBJS)