#ifndef __SNPRINTF_MINIMAL__
#define __SNPRINTF_MINIMAL__

#include <stdarg.h>
#include <stdint.h>

int16_t snprintf_minimal (const char *str, uint16_t size, char *format, ...);

#endif /* __SNPRINTF_MINIMAL__ */
