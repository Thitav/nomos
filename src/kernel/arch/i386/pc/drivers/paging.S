.text
.globl page_directory_load
page_directory_load:
pushl %ebp
movl %esp, %ebp
movl 8(%esp), %eax
movl %eax, %cr3
movl %ebp, %esp
popl %ebp
ret

.globl paging_enable
paging_enable:
pushl %ebp
movl %esp, %ebp
movl %cr0, %eax
orl $0x80000000, %eax
movl %eax, %cr0
movl %ebp, %esp
popl %ebp
ret
