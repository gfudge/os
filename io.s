global outb
global inb

; outb: write byte to IO port
outb:
  mov al, [esp+8] ; data byte
  mov dx, [esp+4] ; IO port
  out dx, al
  ret

; inb: read in a byte from IO port
inb:
  mov dx, [esp+4]
  in  al, dx
  ret
