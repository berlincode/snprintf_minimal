#include "stdio.h"
#include "limits.h"
#include "snprintf_minimal.h"

int
main ()
{
  char buffer[300];
  int num;

  num = snprintf_minimal (buffer, sizeof (buffer), "string: %s", "foo");
  printf ("%s (%d chars)\n", buffer, num);
  num = snprintf_minimal (buffer, sizeof (buffer), "signed integer: %d", 12345);
  printf ("%s (%d chars)\n", buffer, num);
  num = snprintf_minimal (buffer, sizeof (buffer), "signed integer: %i", -1234);
  printf ("%s (%d chars)\n", buffer, num);

  num = snprintf_minimal (buffer, sizeof (buffer), "signed integer (INT_MIN): %i", INT_MIN);
  printf ("%s (%d chars)\n", buffer, num);
  num = snprintf_minimal (buffer, sizeof (buffer), "signed integer (INT_MAX): %i", INT_MAX);
  printf ("%s (%d chars)\n", buffer, num);

  num = snprintf_minimal (buffer, sizeof (buffer), "unsigned integer: %u", INT_MAX);
  printf ("%s (%d chars)\n", buffer, num);
  num = snprintf_minimal (buffer, sizeof (buffer), "unsigned integer; leading zeros: %04d", 25);
  printf ("%s (%d chars)\n", buffer, num);
  num = snprintf_minimal (buffer, sizeof (buffer), "unsigned integer; hexadecimal (lower case): %x", 255);
  printf ("%s (%d chars)\n", buffer, num);
  num = snprintf_minimal (buffer, sizeof (buffer), "unsigned integer; hexadecimal (upper case); leading zeros: %08X", 255);
  printf ("%s (%d chars)\n", buffer, num);
  num = snprintf_minimal (buffer, sizeof (buffer), "unsigned integer; octal: %o", 255);
  printf ("%s (%d chars)\n", buffer, num);
  num = snprintf_minimal (buffer, sizeof (buffer), "print the percentage sign %%");
  printf ("%s (%d chars)\n", buffer, num);

  return 0;
}
