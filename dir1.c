#include <stdio.h>
#include <stdlib.h>
int main() {
  int dx, dy, i;
  int sx[8] = {1, 1, 0, -1, -1, -1, 0, 1};
  int sy[8] = {0, 1, 1, 1, 0, -1, -1, -1};

  for (i = 0; i < 8; ++i) {
    dx = sx[i];
    dy = sy[i];
  }
}