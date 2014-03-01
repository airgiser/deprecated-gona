/**
 * Copyright (C) 2013-2014 The Gona Project
 *
 * Contact: airgiser@gmail.com
 */

#include "GnBitmap.h"

unsigned int GnBitmap::calcStride(unsigned int width, unsigned int bpp) {
  unsigned int n = width;
  unsigned int k;

  switch(bpp)
  {
  case  1:
    k = n;
    n = n >> 3;
    if(k & 7) n++; 
    break;

  case  4: 
    k = n;
    n = n >> 1;
    if(k & 3) n++; 
    break;

  case  8:
    break;

  case 16: 
    n *= 2;
    break;

  case 24: 
    n *= 3; 
    break;

  case 32: 
    n *= 4;
    break;

  case 48: 
    n *= 6; 
    break;

  case 64: 
    n *= 8; 
    break;

  default: 
    n = 0;
    break;
  }

  return ((n + 3) >> 2) << 2;
}
