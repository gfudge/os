#ifndef _GDT_H
#define _GDT_H

// Define GDT Structure for protected flat Model (Intel 3.2.2)
// Index: | Offset: | Name:       | Type: | DPL:  |
//  0     | 0x00    | null        |       |       |
//  1     | 0x08    | Kernel Code | RX    | PL0   |
//  2     | 0x10    | Kernel Data | RW    | PL0   |

typedef struct gdt_entry_s
{
  unsigned short  limit_low;
  unsigned short  base_low;
  unsigned char   base_middle;
  unsigned char   access;
  unsigned char   granularity;
  unsigned char   base_high;
} __attribute__((packed)) gdt_entry_t;

typedef struct gdt_ptr_s
{
  unsigned short  limit;
  unsigned int    base;
} __attribute__((packed)) gdt_ptr_t;

// GDT with three entries
gdt_entry_t gdt[3];
// GDT Ptr
gdt_ptr_t gdt_ptr;

// Flush the GDT
void gdt_flush();

// Install GDT
void init_gdt();

// Set GDT gate
//void gdt_set_gate(int num, unsigned long base, unsigned long limit, unsigned char access, unsigned char gran);

#endif /* _GDT_H */
