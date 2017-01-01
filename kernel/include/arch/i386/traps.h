#ifndef _i386_TRAPS_H
#define _i386_TRAPS_H

#define TRAP_MAX  0x13  // Interrupt 19 to 31 reserved

#define TRAP_DZ   0x0   // Div Zero
#define TRAP_ST   0x1   // Single step
#define TRAP_NM   0x2   // Nom-Maskable
#define TRAP_BP   0x3   // Breakpoint
#define TRAP_OF   0x4   // Overflow
#define TRAP_BR   0x5   // Bound range exceeded
#define TRAP_IV   0x6   // Invalid opcode
#define TRAP_CN   0x7   // Coprocessor not available
#define TRAP_DF   0x8   // Double Fault
#define TRAP_CO   0x9   // Coprocessor segment overrun
#define TRAP_TS   0xa   // Invalid Task State Segment
#define TRAP_NP   0xb   // Segment Not Present
#define TRAP_SS   0xc   // Stack Segment Missing
#define TRAP_GP   0xd   // General Protection
#define TRAP_PF   0xe   // Page Fault
#define TRAP_UN   0xf   // Unknown Interrupt
#define TRAP_MF   0x10  // Coprocessor Error
#define TRAP_AL   0x11  // Alignment Check
#define TRAP_MA   0x12  // Machine Check

typedef struct registers_s
{
  unsigned int gs, fs, es, ds;  /* Pushed Segment Registers */
  unsigned int edi, esi, ebp, esp, ebx, edx, ecx, eax;  /* pushed by pusha */
  unsigned int interrupt, error_code; /* pushed by pre-ISR handlers */
  unsigned int eip, cs, eflags, user_esp, ss;  /* pushed by processor automatically */
} registers_t;

// Initialise traps
void trap_init(void);

// Fault handler
void fault_handler(registers_t *registers);

#endif /* _i386_TRAPS_H */
