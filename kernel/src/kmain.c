#include <kernel/ktypes.h>
#include <kernel/logging.h>

#define NULL 0x0
#define MULTIBOOT_MAGIC 0x2badb002

int _kmain(unsigned int multiboot_info, unsigned int multiboot_magic)
{
  // Initialise TTY
  log_init();
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

  return 0;
}
