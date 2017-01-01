; flush GDT
global gdt_flush
extern gdt_ptr
gdt_flush:
  lgdt  [gdt_ptr] ; load GDT
  mov ax, 0x10    ; set data segment
  mov ds, ax
  mov es, ax
  mov fs, ax
  mov gs, ax
  mov ss, ax
  jmp 0x08:flush2 ; far jump to flush CS
flush2:
  ret
