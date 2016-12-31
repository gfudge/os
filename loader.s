; Loader Entry Point
global loader
loader equ (_loader - 0xC0000000)

extern _kmain

MAGIC_NUMBER  equ 0x1BADB002
ALIGN_MODULES equ 0x00000001
CHECKSUM      equ -(MAGIC_NUMBER + ALIGN_MODULES)

; Kernel Virtual Base = 3GB
KERNEL_VIRTUAL_BASE equ 0xC0000000
KERNEL_PAGE_NUMBER  equ (KERNEL_VIRTUAL_BASE >> 22)

; Kernel stack siz = 4K
KERNEL_STACK_SIZE   equ 4096

; Multiboot Section
section .multiboot:
align 4
  dd MAGIC_NUMBER
  dd ALIGN_MODULES
  dd CHECKSUM

; Data section
section .data:
align 0x1000
; Map first 4MB
BootPageDir:
  dd  0x00000083
  times (KERNEL_PAGE_NUMBER - 1) dd 0
  dd 0x000000083
  times (1024 - KERNEL_PAGE_NUMBER - 1) dd 0

section .text:
align 4

_loader:
  ; Initialise paging
  mov ecx, (BootPageDir - KERNEL_VIRTUAL_BASE)
  mov cr3, ecx  ; Load Page Directory Base

  ; Set PSE bit on CR4
  mov ecx, cr4
  or  ecx, 0x00000010
  mov cr4, ecx

  ; Set PG bit on CR0
  mov ecx, cr0
  or  ecx, 0x80000000
  mov cr0, ecx
  
  ; Jump to kernel space now VM is set up
  lea ecx,  [_StartInHigherHalf]
  jmp ecx

_StartInHigherHalf:
  ; Unmap first 4MB physical address space
  mov dword [BootPageDir], 0
  ; Invalidate TLB
  invlpg  [0]

  ; Initialise the kernel stack
  mov esp, kernel_stack + KERNEL_STACK_SIZE
  
  ; Pass GRUB Multiboot magic number
  push eax
  
  ; Pass GRUB Multiboot info structure
  push ebx

  ; Call the main kernel
  call _kmain
  
  ; Halt system if kernel returns
  cli
  hlt

; Allocated Kernel Stack
section .bss:
align 32
kernel_stack:
  resb KERNEL_STACK_SIZE  
