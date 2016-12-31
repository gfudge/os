ENTRY(loader)

SECTIONS {
  
  . = 0xC0000000;
  _vm_reserve_start = .;
  . += 1M;
  _vm_reserve_end = .;

  .boot : AT( ADDR(.boot) - 0xC0000000 )
  {
    *(.multiboot*)
  }

  _kernel_virt_start = .;
  _kernel_phys_start = . - 0xC0000000;

  .text ALIGN(0x1000) : AT( ADDR(.text) - 0xC0000000 )
  {
    *(.text)
  }

  .rodata ALIGN(0x1000) : AT( ADDR(.rodata) - 0xC0000000 )
  {
    *(.rodata*)
  }

  .data ALIGN(0x1000) : AT( ADDR(.data) - 0xC0000000 )
  {
    *(.data)
  }

  .bss ALIGN(0x1000) : AT( ADDR(.bss)-0xC0000000 )
  { 
    sbss = .;
    *(COMMON)
    *(.bss)
    ebss = .;
  }

  . = ALIGN(0x1000);
  _kernel_virt_end = .;
  _kernel_phys_end = . - 0xC0000000;
  end = .;
  
  /DISCARD/ : {
    *(.comment)
    *(.eh_frame)
  }
}
