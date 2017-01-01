#include <arch/i386/idt.h>
#include <libk/string.h>
#include <kernel/logging.h>

// IDT - table of 256 IDT entries
idt_entry_t idt[256];
// Pointer to IDT table
idt_ptr_t   idtp;

// Dummy IDT
void dummy_handler(void)
{
  return;
}

// Initialise IDT
void init_idt(void)
{
  logk("Initialisng IDT...", DEBUG);

  // Setup the IDT ptr
  idtp.limit  = (sizeof(idt_entry_t) * 256) - 1;
  idtp.base   = idt[0];

  // Zero out the IDT
  memset(&idt, 0, sizeof(idt_entry_t) * 256);
  
  // Setup new ISRs
  logk("Setting up ISRs", DEBUG);
  set_idt_gate(0, *(unsigned long *)&dummy_handler, 0, 0);
  set_idt_gate(1, *(unsigned long *)&dummy_handler, 0, 0);
  set_idt_gate(2, *(unsigned long *)&dummy_handler, 0, 0);

  // Load the IDT to processor's IDTR
  logk("Loading Interrupt Descriptor Table into Processor", DEBUG);
  load_idt(&idtp);

  logk("Completed IDT initialisation", DEBUG);
}

// Setup an ISR
void set_idt_gate(unsigned char num, unsigned long base, unsigned short sel, unsigned char flags)
{
  // Cast an idt_entry object to point to relevant IDT entry
  idt_entry_t new_entry = (const idt_entry_t)idt[num];
  
  // Set the base address
  new_entry.base_lo = (unsigned short)(base & 0x0000ffff);
  new_entry.base_hi = (unsigned short)(base >> 16);

  // Set the other fields
  new_entry.sel = sel;
  new_entry.flags = flags;
}
