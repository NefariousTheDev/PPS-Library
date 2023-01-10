<div align="center">
PPS Library

<p>Library for Packets-Per-Second All in C</p>
</div>

# How to use: 

Change file extension from .c to .h then put the file in your project folder and include it

### Use Example:
```
#include <stdio.h>
#include "pps.h"

int main() {
  int pps = get_pps();
   printf("Current PPS: %s", pps);
  return 0;
}
```
