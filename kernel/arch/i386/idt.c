#include <arch/i386/idt.h>
#include <arch/i386/traps.h>

#include <libk/string.h>
#include <kernel/logging.h>

// IDT - table of 256 IDT entries
idt_entry_t idt[256];
// Pointer to IDT table
idt_ptr_t   idtp;

extern void interrupt_handler_0();
extern void interrupt_handler_1();
extern void interrupt_handler_2();

// Initialise IDT
void init_idt(void)
{
  logk("Initialisng IDT...", DEBUG);

  // Setup the IDT ptr
  idtp.limit  = (sizeof(idt_entry_t) * 256) - 1;
  idtp.base   = (unsigned int)&idt;

  // Zero out the IDT
  memset(&idt, 0, sizeof(idt_entry_t) * 256);
  
  // Setup new ISRs
  logk("Setting up ISRs", DEBUG);
  set_idt_gate(TRAP_DZ, (unsigned)interrupt_handler_0, 0x8, 0x8E);
  set_idt_gate(TRAP_ST, (unsigned)interrupt_handler_1, 0x8, 0x8E);
  set_idt_gate(TRAP_NM, (unsigned)interrupt_handler_2, 0x8, 0x8E);

  // Load the IDT to processor's IDTR
  logk("Loading Interrupt Descriptor Table into Processor", DEBUG);
  load_idt(&idtp);

  logk("Completed IDT initialisation", DEBUG);
}

// Setup an ISR
void set_idt_gate(unsigned char num, unsigned long base, unsigned short sel, unsigned char flags)
{
  // Set the base address
  idt[num].base_lo = (base & 0x0000ffff);
  idt[num].base_hi = (base >> 16);

  // Set the other fields
  idt[num].sel = sel;
  idt[num].flags = flags;
}
