#ifndef _LOGGING_H
#define _LOGGING_H

#include "ktypes.h"

typedef enum loglevel_e
{
  PANIC   = 1,
  CRITICAL= 2,
  ERROR   = 3,
  WARNING = 4,
  INFO    = 5,
  DEBUG   = 6
} loglevel;

void log_init(loglevel level);
void logk(const k_char_t *data, loglevel level);

#endif /* _LOGGING_H */
