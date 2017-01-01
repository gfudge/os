#ifndef _IDT_H
#define _IDT_H

typedef struct idt_entry_s
{
  unsigned short  base_lo;
  unsigned short  sel;
  unsigned char   zero;
  unsigned char   flags;
  unsigned short  base_hi; 
} __attribute__((packed)) idt_entry_t;

typedef struct idt_ptr_s
{
  unsigned short  limit;
  unsigned int    base;
} __attribute__((packed)) idt_ptr_t;

void init_idt(void);
void load_idt(idt_ptr_t *idt_ptr);
void set_idt_gate(unsigned char num, unsigned long base, unsigned short sel, unsigned char flags);

#endif /* _IDT_H */
