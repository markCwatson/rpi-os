BUILDDIR = build
SRCDIR = src

CFILES = $(wildcard $(SRCDIR)/*.c)
ASMFILES = $(wildcard $(SRCDIR)/*.S)
OFILES = $(CFILES:$(SRCDIR)/%.c=$(BUILDDIR)/%_c.o)
OFILES += $(ASMFILES:$(SRCDIR)/%.S=$(BUILDDIR)/%_s.o)

GNUFLAGS = -mcpu=cortex-a72 -Iinclude -Wall -O2 -ffreestanding -nostdinc -nostdlib -nostartfiles -mgeneral-regs-only
GNUTOOL ?= aarch64-none-elf

all: kernel8.img

clean:
	/bin/rm -rf $(BUILDDIR) *.elf *.o *.img *.d

$(BUILDDIR)/%_c.o: $(SRCDIR)/%.c
	mkdir -p $(@D)
	$(GNUTOOL)-gcc $(GNUFLAGS) -MMD -c $< -o $@

$(BUILDDIR)/%_s.o: $(SRCDIR)/%.S
	$(GNUTOOL)-gcc -Iinclude -MMD -c $< -o $@

DEPFILES = $(OFILES:%.o=%.d)
-include $(DEPFILES)

kernel8.img: $(SRCDIR)/linker.ld $(OFILES)
	$(GNUTOOL)-ld -T $(SRCDIR)/linker.ld -o $(BUILDDIR)/kernel8.elf $(OFILES)
	$(GNUTOOL)-objcopy $(BUILDDIR)/kernel8.elf -O binary $(BUILDDIR)/kernel8.img