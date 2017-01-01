#include <arch/i386/gdt.h>

// GDT with three entries
gdt_entry_t gdt[3];

// GDT Ptr
gdt_ptr_t gdt_ptr;

void gdt_set_gate(int num, unsigned long base, unsigned long limit, unsigned char access, unsigned char gran)
{
  gdt[num].base_low = (base & 0xFFFF);
  gdt[num].base_middle = (base >> 16) & 0xFF;
  gdt[num].base_high = (base >> 24) & 0xFF;

  gdt[num].limit_low = (limit & 0xFFFF);
  gdt[num].granularity = ((limit >> 16) & 0x0F);

  gdt[num].granularity |= (gran & 0xF0);
  gdt[num].access = access;
}

void init_gdt()
{
  gdt_ptr.limit = (sizeof(gdt_entry_t) * 3) - 1;
  gdt_ptr.base = (unsigned int)&gdt;
  
  // null descriptor
  gdt_set_gate(0,0,0,0,0);
  
  // Code segment entry
  gdt_set_gate(1, 0, 0xFFFFFFFF, 0x9A, 0xCF);

  // Data segment entry
  gdt_set_gate(2, 0, 0xFFFFFFFF, 0x92, 0xCF);

  // flush gdt
  gdt_flush();
}
