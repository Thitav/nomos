.section .data
gdt_descriptor:
  .word 0 # GDT size
  .long 0 # GDT start

.section .text
.globl gdt_set
gdt_set:
  pushl %ebp
  movl %esp, %ebp
  movw 4(%esp), %ax
  movw %ax, gdt_descriptor
  movl 8(%esp), %eax
  movl %eax, gdt_descriptor+2
  lgdt gdt_descriptor
  movl %ebp, %esp
  popl %ebp
  ret
