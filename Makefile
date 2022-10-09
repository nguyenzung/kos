BUILD_DIR=build
TARGET	= $(BUILD_DIR)/kos.iso

MAP	= $(BUILD_DIR)/kernel.map
LSS	= $(BUILD_DIR)/kernel.lss

CXX = x86_64-linux-gnu-g++
LD 	= x86_64-elf-ld
AS 	= nasm # Force use nasm

CXXFLAGS = -I./include 
CXXFLAGS += -fno-stack-protector 
CXXFLAGS += -fno-exceptions
CXXFLAGS += -fno-rtti  
CXXFLAGS += -nostdlib
CXXFLAGS += -mgeneral-regs-only
CXXFLAGS += -MMD
CXXFLAGS += -O0
CXXFLAGS += -mno-red-zone
CXXFLAGS += -g
CXXFLAGS += -ffreestanding

ASFLAGS = -felf64 

LDFLAGS = -T kernel.ld -nostdlib -n
LDFLAGS += -Map=$(MAP)


CPP_HEAD_FILES := $(shell find . -name *.h)
CPP_SOURCE_FILES := $(shell find . -name *.cpp)
CPP_OBJ_FILES := $(patsubst ./%.cpp, $(BUILD_DIR)/%.o, $(CPP_SOURCE_FILES))

ASM_SOURCE_FILES := $(shell find . -name *.s)
ASM_OBJ_FILES := $(patsubst ./%.s, $(BUILD_DIR)/%.o, $(ASM_SOURCE_FILES))


.PHONY: all clean info demo

info: $(ASM_SOURCE_FILES)
	@echo $(ASM_SOURCE_FILES)

all:  $(TARGET)
 $(TARGET): $(ASM_OBJ_FILES) $(CPP_OBJ_FILES) $(CPP_HEAD_FILES) kernel.ld
	$(LD) -o $(BUILD_DIR)/kernel.bin $(LDFLAGS) $(CPP_OBJ_FILES) $(ASM_OBJ_FILES) && \
	cp $(BUILD_DIR)/kernel.bin iso/boot && \
	grub-mkrescue /usr/lib/grub/x86_64-efi -o $@ iso

$(ASM_OBJ_FILES): $(BUILD_DIR)/%.o : %.s
	@echo $@ $<
	@mkdir -pv $(dir $@)
	$(AS) $(ASFLAGS) $< -o $@

$(CPP_OBJ_FILES): $(BUILD_DIR)/%.o : %.cpp 
	@echo $@ $<
	@mkdir -pv $(dir $@)
	$(CXX) $(CXXFLAGS)  -c $< -o $@

$(LSS): $(BUILD_DIR)/kernel.bin
	@echo Creating .lss ...
	@mkdir -pv $(dir $@)
	@objdump -S $< > $@

clean:
	rm -rf build

demo:  $(TARGET)
	qemu-system-x86_64 -smp 8,sockets=2,cores=2,threads=2,maxcpus=8 -cpu host -m 512M -serial file:kos_serial.log -no-reboot -no-shutdown -cdrom $< --enable-kvm 
	
