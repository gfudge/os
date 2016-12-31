#ifndef _LOGGING_H
#define _LOGGING_H

#include "ktypes.h"

typedef enum loglevel_e
{
  DEBUG,
  INFO,
  WARNING,
  ERROR,
  CRITICAL,
  PANIC
} loglevel;

void log_init(void);
void logk(const k_char_t *data, loglevel level);

#endif /* _LOGGING_H */
