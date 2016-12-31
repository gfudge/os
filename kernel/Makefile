CC=clang
CFLAGS =-m32 -nostdlib -nostdinc -fno-builtin -fno-stack-protector \
        -nodefaultlibs -Wall -Wextra -Werror -c
LD=ld
LDFLAGS =-n -T $(ARCHDIR)/link.ld -melf_i386
AS=nasm
ASFLAGS =-f elf

INCLUDEDIR=include
ARCHDIR=arch/i386
SRCDIR=src

include $(ARCHDIR)/make.config
include $(SRCDIR)/make.config

KERNEL_OBJS=\
$(KERNEL_ARCH_OBJS) \
$(KERNEL_SRC_OBJS)  \

OBJECTS=$(KERNEL_OBJS)

all: kernel.elf

kernel.elf: $(OBJECTS)
	$(LD) $(LDFLAGS) $(OBJECTS) -o kernel.elf

os.iso: kernel.elf
	cp kernel.elf iso/boot/kernel.elf
	genisoimage -R                            \
              -b boot/grub/stage2_eltorito  \
              -no-emul-boot                 \
              -boot-load-size 4             \
              -A os                         \
              -input-charset utf8           \
              -quiet                        \
              -boot-info-table              \
              -o os.iso                     \
              iso

run: os.iso
	bochs -f bochsrc.txt -q

%.o: %.c
	$(CC) -I$(INCLUDEDIR) $(CFLAGS) $< -o $@

%.o: %.s
	$(AS) $(ASFLAGS) $< -o $@

clean:
	rm -f kernel.elf os.iso
	rm -f $(OBJECTS) *.o */*.o */*/*.o
