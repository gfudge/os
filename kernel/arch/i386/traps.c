#include <arch/i386/traps.h>
#include <kernel/logging.h>

// Fault handler 
void fault_handler(registers_t *registers)
{
  logk("Fault Handler Triggered", DEBUG);
  // Check the interrupt is going to be handled
  if(registers->interrupt < TRAP_MAX)
  {
    logk("Interrupt number exceeds TRAP_MAX", CRITICAL);
    return;
  }
  
  switch(registers->interrupt)
  {
    // Divide by zero error
    case TRAP_DZ:
      logk("DIV0 EXCEPTION", ERROR);
      for(;;) {}
      break;

    // Single step
    case TRAP_ST:
      break;

    // Non-maskable interrupt
    case TRAP_NM:
      break;

    // Breakpoint
    case TRAP_BP:
      break;

    // Overflow
    case TRAP_OF:
      break;

    // Bound range exceeded
    case TRAP_BR:
      break;

    // Invalid Opcode
    case TRAP_IV:
      break;

    // Coprocessor not available
    case TRAP_CN:
      break;

    // Double Fault
    case TRAP_DF:
      break;

    // Coprocessor segment overrun
    case TRAP_CO:
      break;

    // Invalid Task State Segment
    case TRAP_TS:
      break;

    // Segment not present
    case TRAP_NP:
      break;

    // Stack Segment Missing
    case TRAP_SS:
      break;

    // General protection fault
    case TRAP_GP:
      break;

    // Page Fault
    case TRAP_PF:
      break;
    
    // Unknown Interrupt
    case TRAP_UN:
      break;

    // Coprocessor Error
    case TRAP_MF:
      break;

    // Alignment Check Error
    case TRAP_AL:
      break;

    // Machine Check Error
    case TRAP_MA:
      break;
    
    // Handle other cases
    default:
      // theres not a lot we can do :(
      logk("Unhandled fault!", PANIC);
      break;
  }

  // Infinite loop
  for(;;) {}
}
