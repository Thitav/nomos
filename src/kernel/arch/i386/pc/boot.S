# Constants for the multiboot header (multiboot 1)
.set ALIGN,    1<<0                       # Align loaded modules on page boundaries
.set MEMINFO,  1<<1                       # Provide memory map
.set VIDINFO,  1<<2                       # Provide video mode table
.set FLAGS,    ALIGN | MEMINFO | VIDINFO  # Multiboot 'flag' field
.set MAGIC,    0x1BADB002                 # 'magic number' that lets bootloader find the header
.set CHECKSUM, -(MAGIC + FLAGS)           # Checksum of the above to verify that this header is in fact the multiboot header

# Multiboot header
.section .multiboot
magic:            # Magic fields (required)
  .align 4
  .long MAGIC
  .long FLAGS
  .long CHECKSUM
address_ignored:  # Address fields (ignored since flags[16] is not set)
  .long 0         # header
  .long 0         # load
  .long 0         # load end
  .long 0         # bss end	
  .long 0         # entry
graphics:         # Graphics fields (required since flags[2] is set)
  .long 0         # mode (0 for linear graphics or 1 for text)
  .long 320       # columns
  .long 200       # lines
  .long 8         # bits per pixel (VGA colors are defined using 8 bits)

# Stack for the initial thread
.section .bss
.align 16
stack_bottom:
.skip 16384 # 16 KB
stack_top:

# Kernel entry point
.section .text
.global _start
.type _start, @function
_start:
	movl $stack_top, %esp

	# Call the global constructors
	call _init

	# Transfer control to the main kernel
  pushl %ebx # multiboot info struct pointer
  pushl %eax # multiboot magic number
	call kernel_main

	# Hang if kernel_main unexpectedly returns
	cli
1:	hlt
	jmp 1b

# Set the size of the _start symbol to the current location '.' minus its start, 
#   useful for debugging or when implementing call tracing
.size _start, . - _start
