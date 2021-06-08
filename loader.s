.set MAGIC, 0x1badb002  ; GRUB 魔术块
.set FLAGS, (1<<0 | 1<<1)  ; GRUB 标志块
.set CHECKSUM, -(MAGIC + FLAGS)  ; 校验块

.section .multboot
	.long MAGIC
	.long FLAGS
	.long CHECKSUM

.section .text
.extern kernelMain  ; kernelMain是外部函数
.global loader

loader:
    mov $kernel_stack, %esp
    push %eax
    push %ebx
    call kernelMain

.section .bss
.space 2*1024*1024  ; 开辟 2MB 内存空间

kernel_stack:
