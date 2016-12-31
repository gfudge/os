; setup mm
global setup_mm

setup_mm:
  ; enable paging
  mov cr3, eax

setup_paging:
  ; set page directory addr at eax
  pop eax
  mov cr3, eax

  ; enable page size extensions
  mov ebx, cr4
  or  ebx, 0x00000010
  mov cr4, ebx

  ; set page-enable
  mov ebx, cr0
  or  ebx, 0x80000000
  mov cr0, ebx
