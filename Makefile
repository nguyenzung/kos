BUILD_DIR=build/

# CPP_HEAD_FILES := $(shell find . -name *.h)
CPP_SOURCE_FILES := $(shell find . -name *.cpp)
CPP_OBJ_FILES := $(patsubst ./%.cpp, $(BUILD_DIR)%.o, $(CPP_SOURCE_FILES))

ASM_SOURCE_FILES := $(shell find . -name *.s)
ASM_OBJ_FILES := $(patsubst ./%.s, $(BUILD_DIR)%.o, $(ASM_SOURCE_FILES))

info: $(ASM_SOURCE_FILES)
	@echo $(ASM_SOURCE_FILES)

all: kernel.iso
kernel.iso: $(ASM_OBJ_FILES) $(CPP_OBJ_FILES) kernel.ld
	x86_64-elf-ld -n  -o $(BUILD_DIR)kernel.bin -T kernel.ld $(CPP_OBJ_FILES) $(ASM_OBJ_FILES) -nostdlib && \
	cp $(BUILD_DIR)kernel.bin $(BUILD_DIR)iso/boot && \
	grub-mkrescue /usr/lib/grub/i386-pc -o $(BUILD_DIR)kernel.iso $(BUILD_DIR)iso
	@echo $(shell ls -lia build/iso/boot/kernel.bin)

$(ASM_OBJ_FILES): $(BUILD_DIR)%.o : %.s
	@echo $@ $<
	nasm -f elf64 $< -o $@

$(CPP_OBJ_FILES): $(BUILD_DIR)%.o : %.cpp 
	@echo $@ $<
	x86_64-linux-gnu-g++ -I include include/kernel include/driver -fno-stack-protector -fno-exceptions -fno-rtti  -nostdlib -c $< -o $@

clean:
	rm -rf $(ASM_OBJ_FILES) $(CPP_OBJ_FILES) $(BUILD_DIR)kernel.bin $(BUILD_DIR)kernel.iso

demo: kernel.iso
	qemu-system-x86_64 -s -cdrom $(BUILD_DIR)kernel.iso