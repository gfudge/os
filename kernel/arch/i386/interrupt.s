; Load the IDT
global load_idt
; stack:
;   [esp + 4] <- address of first IDT entry
;   [esp    ] <- return address
load_idt:
  mov   eax, [esp+4]
  lidt  [eax]
  ret

; No Error Code Interrupt Handler Macro
%macro no_error_code_interrupt_handler 1
global interrupt_handler_%1
interrupt_handler_%1:
  cli ; clear interrupts
  push  dword 0   ; push 0 as error_code
  push  dword %1  ; push interrupt number
  ; construct generic handler
  call generic_interrupt_handler
%endmacro

; Error Code Interrupt Handler Macro
%macro error_code_interrupt_handler 1
global interrupt_handler_%1
interrupt_handler_%1:
  cli ; clear interrupts
  push  dword %1
  ; construct generic handler
  call generic_interrupt_handler
%endmacro

generic_interrupt_handler:
  ; globally define the externally 
  ; linked interrupt handler
  extern fault_handler

  ; save GP registers
  pusha

  ; push segment registers
  push ds
  push es
  push fs
  push gs
  
  ; load kernel data segment descriptor
  mov ax, 0x10
  mov ds, ax
  mov es, ax
  mov fs, ax
  mov gs, ax

  ; push up the stack
  mov eax, esp

  ; call the handler
  push  eax
  mov   eax, fault_handler
  call  eax
  
  ; restore segment registers
  pop eax
  pop gs
  pop fs
  pop es
  pop ds

  ;restore GP registers
  popa

  ; clear error_code and ISR number + pop CS, EIP, EFLAGS, SS & ESP
  add   esp, 8

  ; return to interrupted code
  ; no need for sti as interrupts reenabled with iret
  iret

; Interrupt Handlers
no_error_code_interrupt_handler 0
no_error_code_interrupt_handler 1
error_code_interrupt_handler    2
