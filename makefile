KERNEL_DIR=kernel
BOOT_DIR=iso/boot
GRUB_DIR=$(BOOT_DIR)/grub

os.iso: $(BOOT_DIR)/kernel.elf $(GRUB_DIR)/menu.lst $(GRUB_DIR)/stage2_eltorito
	genisoimage -R -b boot/grub/stage2_eltorito \
		-no-emul-boot -boot-load-size 4 \
		-A os                           \
        -input-charset utf8             \
        -quiet                          \
        -boot-info-table                \
        -o os.iso                       \
        iso

$(GRUB_DIR)/stage2_eltorito:
	cd $(GRUB_DIR) && wget http://littleosbook.github.com/files/stage2_eltorito

$(BOOT_DIR)/kernel.elf: $(KERNEL_DIR)/kernel.elf
	cp $(KERNEL_DIR)/kernel.elf iso/boot/

$(KERNEL_DIR)/kernel.elf:
	cd $(KERNEL_DIR) && $(MAKE)

.PHONY: clean
clean:
	rm $(GRUB_DIR)/stage2_eltorito iso/boot/kernel.elf os.iso
	cd kernel && $(MAKE) clean