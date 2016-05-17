#include <stdint.h>
#include <stdbool.h>
#include <stdarg.h>
#include "snprintf_minimal.h"

/* 
 * snprintf() implementation (subset) 
 *
 * Copyright Ulf Bartel. Code is licensed under the new-style BSD
 * license.
 */


/* like strlcpy(), but returns pointer to last char */
static char *
copy_str (char *dst, char *src, int16_t buffer_len)
{
  while (--buffer_len > 0)
  {
    if ((*dst = *src) != '\0')
    {
      dst++;
      src++;
    }
    else
    {
      /* string is null terminated */
      return dst;
    }
  }

  *dst = '\0';

  return dst;
}

/* adds a char and returns pointer to last char */
static char *
copy_char (char *dst, char ch, int16_t buffer_len)
{
  if (buffer_len > 1)
  {
    *dst++ = ch;
  }

  *dst = '\0';

  return dst;
}

static void
reverse (char *str, int16_t length)
{
  int16_t i = 0, j = length - 1;
  char tmp;
  while (i < j)
  {
    tmp = str[i];
    str[i] = str[j];
    str[j] = tmp;
    i++;
    j--;
  }
}

static const char lower_digits[] = "0123456789abcdef";
static const char upper_digits[] = "0123456789ABCDEF";

static void
dtoa_ (unsigned int n, char *out, uint8_t base, bool uppercase, int16_t min_digits, uint16_t out_len)
{
  char const *digit;
  uint16_t i = 0;
  int16_t max_digits = out_len - 1;     // without '\0'

  if (uppercase)
    digit = &upper_digits[0];
  else
    digit = &lower_digits[0];

  if (min_digits < 1)
    min_digits = 1;             /* at least 1 digit, even if n=0 */

  if (base <= 16)               /* sanity check */
  {
    while (((n > 0) || (min_digits > 0)) && (i < max_digits))
    {
      out[i++] = digit[n % base];
      n /= base;
      min_digits--;
    }
  }

  if (i < out_len)              /* do not append '\0' if out_len=0) */
  {
    out[i] = '\0';
    reverse (out, i);
  }
}

static void
itoa_ (int n, char *out, uint8_t base, bool uppercase, int8_t min_digits, uint16_t out_len)
{
  unsigned int pos;

  if (n < 0)
  {
    /* ... and handle n as a postive number */
    pos = -n;

    if (out_len > 1)
    {
      out[0] = '-';
      out++;
      out_len--;
      if (min_digits > 1)
        min_digits--;
    }
  }
  else
  {
    pos = n;
  }

  dtoa_ (pos, out, base, uppercase, min_digits, out_len);
}

int16_t
snprintf_minimal (const char *str, uint16_t size, char *format, ...)
{
  char buffer_tmp[20];          // large enough to keep some leading zeros
  char *cur_ptr = (char *) str;
  char ch;
  int16_t min_digits;
  va_list arg_ptr;

  va_start (arg_ptr, format);

  while ((ch = *(format++)))
  {
    if (ch != '%')
    {
      cur_ptr = copy_char (cur_ptr, ch, size - (cur_ptr - str));
    }
    else
    {
      min_digits = 0;
      ch = *(format++);

      /* pad with zeros ? */
      if (ch == '0')
      {
        while (ch >= '0' && ch <= '9')
        {
          min_digits = (min_digits * 10) + (ch - '0');
          ch = *(format++);
          if (ch == '\0')
            goto end;
        }
      }

      switch (ch)
      {
        case 'u':              /* unsigned decimal */
          dtoa_ (va_arg (arg_ptr, unsigned int), buffer_tmp, 10, false, min_digits, sizeof (buffer_tmp));
          cur_ptr = copy_str (cur_ptr, buffer_tmp, size - (cur_ptr - str));
          break;

        case 'o':              /* octal */
          dtoa_ (va_arg (arg_ptr, unsigned int), buffer_tmp, 8, false, min_digits, sizeof (buffer_tmp));
          cur_ptr = copy_str (cur_ptr, buffer_tmp, size - (cur_ptr - str));
          break;

        case 'x':              /* hexadecimal (unsigned, lowercase) */
          dtoa_ (va_arg (arg_ptr, unsigned int), buffer_tmp, 16, false, min_digits, sizeof (buffer_tmp));
          cur_ptr = copy_str (cur_ptr, buffer_tmp, size - (cur_ptr - str));
          break;

        case 'X':              /* hexadecimal (unsigned, uppercase) */
          dtoa_ (va_arg (arg_ptr, unsigned int), buffer_tmp, 16, true, min_digits, sizeof (buffer_tmp));
          cur_ptr = copy_str (cur_ptr, buffer_tmp, size - (cur_ptr - str));
          break;

        case 'd':
        case 'i':              /* signed */
          itoa_ (va_arg (arg_ptr, int), buffer_tmp, 10, false, min_digits, sizeof (buffer_tmp));
          cur_ptr = copy_str (cur_ptr, buffer_tmp, size - (cur_ptr - str));
          break;

        case 'c':              /* char */
          cur_ptr = copy_char (cur_ptr, (char) (va_arg (arg_ptr, int)), size - (cur_ptr - str));
          break;

        case 's':              /* string */
          // TODO respect min_digits
          cur_ptr = copy_str (cur_ptr, va_arg (arg_ptr, char *), size - (cur_ptr - str));
          break;

        case '%':
          cur_ptr = copy_char (cur_ptr, '%', size - (cur_ptr - str));
          break;

        case 0:
          goto end;

        default:
          break;
      }
    }
  }

end:
  va_end (arg_ptr);

  return (int16_t) (cur_ptr - str);
}
