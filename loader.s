.set MAGIC, 0x1badb002
.set FLAGS, (1<<0 | 1<<1)
.set CHECKSUM, -(MAGIC + FLAGS)

.section .multboot
	.long MAGIC
	.long FLAGS
	.long CHECKSUM

.section .text
.extern _kernelMain
.global loader

loader:
    mov $kernel_stack, %esp
    push %eax
    push %ebx
    call _kernelMain

.section .bss
.space 2*1024*1024

kernel_stack:
