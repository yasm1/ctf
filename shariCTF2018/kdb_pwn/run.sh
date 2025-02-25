#!/bin/sh

qemu-system-x86_64 -cpu kvm64,+smep -m 64M -kernel ./bzImage -initrd ./rootfs.cpio -append "root=/dev/ram rw console=ttyS0 oops=panic panic=1 quiet kaslr" -smp cores=2,threads=1,sockets=1 -monitor /dev/null -nographic 2>/dev/null
