/**
 * Copyright (C) 2013-2014 The Gona Project
 *
 * Contact: airgiser@gmail.com
 */

#include "GnImage.h"
#include "stdlib.h"

GnImage::GnImage(unsigned int width, unsigned int height, GnPixelFormat pixfmt, unsigned char *pixels) : 
m_width(width), 
m_height(height), 
m_pixelFormat(pixfmt), 
m_pixels(pixels)
{
  m_bpp = calcBpp(pixfmt);
  m_stride = calcStride(width, m_bpp);
}

GnImage::~GnImage()
{
  if (m_pixels != NULL) {
    free(m_pixels);
    m_pixels = NULL;
  }
}

unsigned int GnImage::calcStride(unsigned int width, unsigned int bpp) {
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

unsigned int GnImage::calcBpp(unsigned char pixfmt)
{
  unsigned int bpp = 0;
  switch(pixfmt)
  {
  case kFormatRGBA32:
  case kFormatBGRA32:
  case kFormatARGB32:
    bpp = 32;
    break;

  case kFormatRGB24:
  case kFormatBGR24:
    bpp = 24;
    break;

  case kFormatRGB565:
  case kFormatRGB555:
    bpp = 16;
    break;

  case kFormatGRAY8:
    bpp = 8;
    break;

  default:
    break;
  }

  return bpp;
}
