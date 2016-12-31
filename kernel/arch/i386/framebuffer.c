#include "framebuffer.h"
#include "io.h"

void fb_write(const char *buffer, const unsigned int size)
{
  unsigned int count = 0;
  do 
  { 
    // Move the framebuffer cursor to current position
    fb_move_cursor(0, count);
    buffer[count];
  } while(count < size);
}

static void fb_move_cursor(const unsigned int row, const unsigned int col)
{
  // calculate cursor position
  unsigned short position = (row*80) + col;
  outb(FB_COMMAND_PORT, FB_HIGH_BYTE_COMMAND);
  outb(FB_DATA_PORT, ((position >> 8) & 0x00FF));
  outb(FB_COMMAND_PORT, FB_LOW_BYTE_COMMAND);
  outb(FB_DATA_PORT, position & 0x00FF);
}
