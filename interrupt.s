; No Error Code Interrupt Handler Macro
%macro no_error_code_interrupt_handler %1
global interrupt_handler_%1
interrupt_handler_%1:
  push  dword 0   ; push 0 as error_code
  push  dword %1  ; push interrupt number
  jmp   generic_interrupt_handler
%endmacro

; Error Code Interrupt Handler Macro
%macro error_code_interrupt_handler %1
global interrupt_handler_%1
  push  dword %1
  jmp   generic_interrupt_handler
%endmacro

generic_interrupt_handler:
  ; save registers
  push  eax
  push  ebx
  push  ecx
  push  edx
  push  esp
  push  ebp
  push  esi
  push  edi

  ; call the handler
  call  interrupt_handler
  
  ;restore the registers
  pop   edi
  pop   esi
  pop   ebp
  pop   esp
  pop   edx
  pop   ecx
  pop   ebx
  pop   eax

  ; restore esp
  add   esp, 8

  ; return to interrupted code
  iret

; Interrupt Handlers
no_error_code_interrupt_handler 0
no_error_code_interrupt_handler 1
error_code_interrupt_handler    2
