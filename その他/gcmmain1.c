#include "gcm.h"

/* Euclidian algorithm */
u_int gcm(u_int l, u_int s) {
  u_int r;

  if ((l == 0) || (s == 0)) return 0;
  l = ABS(l);
  s = ABS(s);
  while (s != 0) {
    r = l % s;
    l = s;
    s = r;
  }

  return l;
}

/*
cl /c gcmsub1.c
cl /c gcmmain1.c
cl /Fegcm1.exe gcmsub1.obj gcmmain1.obj
*/
