#ifndef _FRAMEBUFFER_H
#define _FRAMEBUFFER_H

// Buffer
#define TERM_BUFFER           0xC00B8000

// IO Ports
#define FB_COMMAND_PORT       0x3D4
#define FB_DATA_PORT          0x3D5

// IO Port Commands
#define FB_HIGH_BYTE_COMMAND  14
#define FB_LOW_BYTE_COMMAND   15

// Write a string to the framebuffer
void fb_write(const char *buffer, const unsigned int len);

#endif /* _FRAMEBUFFER_H */
