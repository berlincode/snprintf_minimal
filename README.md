snprintf-minimal
================

Small and safe snprintf() implementation (subset) for embedded projects which
should work with all c compilers that support variable argument lists. No
external dependencies.

Summary
-------
On memory constraint systems the default glibc snprintf() is often simply to
large to include. Additionally there are still some old compilers which
do not offer a snprintf() implementation. In these cases snprintf-minimal may
be suitable.

Supported formats (flag characters):
 * %u : unsigned integer
 * %o : octal (unsigned)
 * %x : hexadecimal (unsigned, lowercase)
 * %X : hexadecimal (unsigned, uppercase)
 * %d : signed integer (same as %i)
 * %i : signed integer (same as %d)
 * %c : char
 * %s : string

 * %% : '%' character

Compatibility
-------------

Only a subset of format characters and features are implemented. There is no
floating point, long integer or alignment support. No external dependencies as
stated above.

Public repository
---------------------

https://github.com/berlincode/snprintf_minimal

Copyright and license
---------------------

Code and documentation copyright Ulf Bartel. Code is licensed under the
[new-style BSD license](./LICENSE.txt).

