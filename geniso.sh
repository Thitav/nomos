rm -r ./isodir
mkdir -p ./isodir/boot/grub
cp ./build/sysroot/usr/boot/kernel.bin ./isodir/boot/nomos.bin
cp ./grub.cfg ./isodir/boot/grub/grub.cfg
grub-mkrescue -o ./isodir/nomos.iso ./isodir