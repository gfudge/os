#include <kernel/tty.h>
#include <kernel/ktypes.h>

static const k_uint32_t VGA_WIDTH   = 80;
static const k_uint32_t VGA_HEIGHT  = 25;
static k_uint16_t* const VGA_MEMORY = (k_uint16_t *)0xC00B8000;

static k_size_t     tty_row;
static k_size_t     tty_col;
static k_uint8_t    tty_color;
static k_uint16_t*  tty_buffer;

static inline k_uint8_t vga_entry_color(vga_color fg, vga_color bg);
static inline k_uint16_t vga_entry(k_char_t uc, k_uint8_t color);

void tty_init(void)
{
  tty_row = 0;
  tty_col = 0;
  tty_color = vga_entry_color(VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK);
  tty_buffer = VGA_MEMORY;

  for(k_size_t y = 0; y < VGA_HEIGHT; y++) {
    for(k_size_t x = 0; x < VGA_WIDTH; x++) {
      const k_size_t idx = y * VGA_WIDTH + x;
      tty_buffer[idx] = vga_entry(' ', tty_color);
    }
  }
}

static void tty_put_entry_at(k_char_t c, k_uint8_t color, k_size_t x, k_size_t y)
{
  const k_size_t idx = y * VGA_WIDTH + x;
  tty_buffer[idx] = vga_entry(c, color);
}

static inline k_uint8_t vga_entry_color(vga_color fg, vga_color bg)
{
  return fg | bg << 4;
}

static inline k_uint16_t vga_entry(k_char_t uc, k_uint8_t color)
{
  return (k_uint16_t)uc | (k_uint16_t)color << 8;
}

void tty_putchar(const k_char_t c)
{
  k_char_t uc = c;
  tty_put_entry_at(uc, tty_color, tty_col, tty_row);
  if(++tty_col == VGA_WIDTH)
  {
    tty_col = 0;
    if(++tty_row == VGA_HEIGHT)
    {
      tty_row = 0;
    }
  }
}

void tty_write(const k_char_t* data, k_size_t size)
{
  for(k_size_t i = 0; i < size; i++)
  {
    tty_putchar(data[i]);
  }
}

void tty_writestr(const k_char_t* data)
{
  k_size_t idx = 0;
  // Copy until null byte
  while(data[idx] != '\0')
  {
    tty_putchar(data[idx++]);
  }
}

void tty_writestr_color(const k_char_t* data, vga_color color)
{
  k_uint8_t old_tty_color = tty_color;
  tty_color = vga_entry_color(color, VGA_COLOR_BLACK);
  tty_writestr(data);
  tty_color = old_tty_color;
}

void tty_newline(void)
{
  if(++tty_row == VGA_HEIGHT)
  {
    tty_row = 0;
  }
  tty_col = 0;
}
