arch ?= x86_64
kernel := build/kernel-$(arch).bin
iso := build/os-$(arch).iso

cpp_source_path	:=	src/drivers	\
					src/drivers/vga \
					src/

assembly_source_path	:=	src/arch/$(arch)/boot

linker_script := src/arch/$(arch)/boot/linker.ld
grub_cfg := src/arch/$(arch)/boot/grub.cfg
assembly_source_files := $(wildcard $(addsuffix /*.asm, $(assembly_source_path)))
assembly_object_files := $(patsubst src/arch/$(arch)/boot/%.asm, \
	build/arch/$(arch)/boot/%.o, $(assembly_source_files))
cpp_source_files := $(wildcard $(addsuffix /*.cpp, $(cpp_source_path)))
cpp_object_files := $(patsubst src/%, build/%, $(patsubst %.cpp, %.o, $(cpp_source_files)))

CC := x86_64-elf-g++

CFLAGS :=	-nostdlib							\
			-fno-builtin						\
			-fno-stack-protector			\
			-W								\
			-Wall							\
			-Wextra							\
			-Winline							\
			-Wpragmas							\
			-Wuninitialized			\
			-Wno-missing-braces			\
			-ffreestanding			\
			-Wcast-align			\
			-Wwrite-strings			\
			-fno-omit-frame-pointer			\
			-mno-red-zone						\
			-nostartfiles			\
			-static							\
			-Wparentheses						\
			-Wunreachable-code				\
			-Wunused							\
			-Wmissing-field-initializers		\
			-Wswitch-enum						\
			-Wshadow							\
			-Wuninitialized					\
			-Wno-logical-not-parentheses		\
			-O2								\
			-fno-exceptions					\
			-fno-rtti						\

INCLUDES :=	-isystem $(realpath .)/inc	\


.PHONY: all clean run iso

all: $(kernel)

clean:
	@rm -r build

re: clean all

run: $(iso)
	@qemu-system-x86_64 -serial stdio -enable-kvm -m 4G -cdrom $(iso)

iso: $(iso)

$(iso): $(kernel) $(grub_cfg)
	@mkdir -p build/isofiles/boot/grub
	@cp $(kernel) build/isofiles/boot/kernel.bin
	@cp $(grub_cfg) build/isofiles/boot/grub
	@grub-mkrescue -o $(iso) build/isofiles 2> /dev/null
	@rm -r build/isofiles

$(kernel): $(assembly_object_files) $(cpp_object_files) $(linker_script)
	@x86_64-elf-ld -n -T $(linker_script) -o $(kernel) $(assembly_object_files) $(cpp_object_files)

# compile assembly files
build/arch/$(arch)/boot/%.o: src/arch/$(arch)/boot/%.asm
	@mkdir -p $(shell dirname $@)
	@nasm -felf64 $< -o $@
	@echo -e "	AS $@\n"

# compile cpp files
build/%.o: src/%.cpp
	@mkdir -p $(shell dirname $@)
	echo includes $(INCLUDES)
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@
	@echo -e "	CC $@\n"