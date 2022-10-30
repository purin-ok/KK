#include <stdio.h>
#include <stdlib.h>
#define ADJ(d) ((d < 0) ? -1 : ((d > 0) ? 1 : 0))
int main() {
  int dx = 1, dy = -1, tmp, i;

  for (i = 0; i < 8; ++i) {
    tmp = dx;
    dx += dy;
    dy += tmp;
    dx = ADJ(dx);
    dy = ADJ(dy);
  }
}