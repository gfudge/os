#include <kernel/logging.h>
#include <arch/i386/tty.h>

static loglevel current;

void log_init(loglevel level)
{
  current = level; 
  tty_init();
}

void logk(const char *data, loglevel level)
{ 
  // Ignore the message if below the
  // current loglevel
  if(current < level)
  {
    return;
  }
  
  // Print out at valid log level
  switch(level)
  {
    case DEBUG:
      tty_writestr_color("[DEBUG]:", VGA_COLOR_WHITE);
      tty_writestr_color(data, VGA_COLOR_BLUE);
      tty_newline();
      break;

    case INFO:
      tty_writestr_color("[INFO]:", VGA_COLOR_WHITE);
      tty_writestr_color(data, VGA_COLOR_GREEN);
      tty_newline();
      break;

    case WARNING:
      tty_writestr_color("[WARNING]:", VGA_COLOR_WHITE);
      tty_writestr_color(data, VGA_COLOR_LIGHT_MAGENTA);
      tty_newline();
      break;

    case ERROR:
      tty_writestr_color("[ERROR]:", VGA_COLOR_WHITE);
      tty_writestr_color(data, VGA_COLOR_MAGENTA);
      tty_newline();
      break;

    case CRITICAL:
      tty_writestr_color("[CRITICAL]:", VGA_COLOR_WHITE);
      tty_writestr_color(data, VGA_COLOR_LIGHT_RED);
      tty_newline();
      break;

    case PANIC:
      tty_writestr_color("[PANIC]:", VGA_COLOR_WHITE);
      tty_writestr_color(data, VGA_COLOR_RED);
      tty_newline();
      break;

    default:
      tty_writestr(data);
      tty_newline();
      break;
  }
}
