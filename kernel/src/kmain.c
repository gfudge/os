#include <kernel/ktypes.h>
#include <kernel/logging.h>

#include <arch/i386/idt.h>
#include <arch/i386/gdt.h>

#define NULL 0x0
#define MULTIBOOT_MAGIC 0x2badb002

int _kmain(unsigned int multiboot_info, unsigned int multiboot_magic)
{
  // Initialise TTY
  log_init(DEBUG);
  logk("Logger Initialised", INFO);
  // Check the multiboot magic number is valid
  // and multiboot info struct ptr is not null
  if((multiboot_magic != MULTIBOOT_MAGIC) || (multiboot_info == NULL))
  {
    logk("Multiboot Magic number of Info Ptr invalid", CRITICAL);
    return -1;
  }
  else
  {
    logk("Multiboot booted kernel successfully", INFO);
  }
  
  // Init GDT
  init_gdt();
  logk("Initialised GDT", INFO);

  // Initialise IDT
  init_idt();
  logk("Initialised IDT", INFO);

  // Cause DIV0 error
  int a = 8;
  int b = 0;
  int c = a/b;
  c++;

  while(1) {}
  return 0;
}
