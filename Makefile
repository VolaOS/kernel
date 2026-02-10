# ====== Tools ======
GCC 		:= gcc
LD 			:= ld
NASM		:= nasm
GRUB		:= grub-mkrescue
QEMU		:= qemu-system-i386

# ====== Paths ======
BUILD		:= build
OBJDIR		:= $(BUILD)/obj
ISODIR		:= $(BUILD)/iso

KERNEL_ELF	:= $(ISODIR)/boot/kernel.elf
ISO_NAME	:= $(BUILD)/vola.iso
LINKER		:= linker/linker.ld

# ====== Flags ======
GCC_FLAGS	:= -m32 -ffreestanding -fno-pic -fno-stack-protector -nostdlib -O2 -Wall -Wextra -Iinclude -Ikernel
LD_FLAGS	:= -m elf_i386 -T $(LINKER)
NASM_FLAGS	:= -f elf32

# ====== Sources ======
OBJS		:= $(OBJDIR)/boot.o $(OBJDIR)/kernel.o $(OBJDIR)/vga.o


all: $(ISO_NAME)

$(OBJDIR):
	@mkdir -p $(OBJDIR)

$(BUILD):
	@mkdir -p $(BUILD)

$(OBJDIR)/boot.o: boot/boot.asm | $(OBJDIR)
	$(NASM) $(NASM_FLAGS) $< -o $@

$(OBJDIR)/kernel.o: kernel/kernel.c | $(OBJDIR)
	$(GCC) $(GCC_FLAGS) -c $< -o $@

$(OBJDIR)/vga.o: kernel/vga.c | $(OBJDIR)
	$(GCC) $(GCC_FLAGS) -c $< -o $@

$(KERNEL_ELF): $(OBJS) $(LINKER) | $(BUILD)
	@mkdir -p $(ISODIR)/boot
	$(LD) $(LD_FLAGS) -o $@ $(OBJS)

$(ISO_NAME): $(KERNEL_ELF) grub/grub.cfg | $(BUILD)
	@mkdir -p $(ISODIR)/boot/grub
	@cp grub/grub.cfg $(ISODIR)/boot/grub/grub.cfg
	$(GRUB) -o $@ $(ISODIR)

run: $(ISO_NAME)
	$(QEMU) -cdrom $(ISO_NAME)

clean:
	@rm -rf $(BUILD)
