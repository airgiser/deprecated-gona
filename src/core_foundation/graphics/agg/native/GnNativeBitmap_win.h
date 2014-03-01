/**
 * Copyright (C) 2013-2014 The Gona Project
 *
 * Contact: airgiser@gmail.com
 */

#ifndef GONA_GRAPHICS_NATIVE_BITMAP_WIN_H
#define GONA_GRAPHICS_NATIVE_BITMAP_WIN_H

#include <windows.h>
#include "../GnBitmap.h"

class GnNativeBitmap : public GnBitmap {
public:
  GnNativeBitmap(HWND hwnd, unsigned int width, unsigned int height, unsigned int bpp) {
    m_hwnd = hwnd;
    m_dc = GetDC(hwnd);

    unsigned int stride = calcStride(width, bpp);
    unsigned int imgSize = stride * height;
    unsigned int paletteSize = 0; // TODO: pixformat dependent
    unsigned int fullSize = sizeof(BITMAPINFOHEADER) + paletteSize + imgSize;

    m_bmp = (BITMAPINFO *) new unsigned char[fullSize];
    m_bmp->bmiHeader.biSize   = sizeof(BITMAPINFOHEADER);
    m_bmp->bmiHeader.biWidth  = width;
    m_bmp->bmiHeader.biHeight = height;
    m_bmp->bmiHeader.biPlanes = 1;
    m_bmp->bmiHeader.biBitCount = (unsigned short)bpp;
    m_bmp->bmiHeader.biCompression = 0;
    m_bmp->bmiHeader.biSizeImage = imgSize;
    m_bmp->bmiHeader.biXPelsPerMeter = 0;
    m_bmp->bmiHeader.biYPelsPerMeter = 0;
    m_bmp->bmiHeader.biClrUsed = 0;
    m_bmp->bmiHeader.biClrImportant = 0;

    m_buf = (unsigned char *)m_bmp + sizeof(BITMAPINFOHEADER) + paletteSize;
  }

  ~GnNativeBitmap() {
    ReleaseDC(m_hwnd, m_dc);
    delete []m_bmp;
  }

public:
  virtual void draw() {
    unsigned int width  = m_bmp->bmiHeader.biWidth;
    unsigned int height = m_bmp->bmiHeader.biHeight;
    ::SetDIBitsToDevice(
      m_dc,                // handle to device context
      0,                  // x-coordinate of upper-left corner of 
      0,                  // y-coordinate of upper-left corner of 
      width,              // source rectangle width
      height,             // source rectangle height
      0,                  // x-coordinate of lower-left corner of 
      0,                  // y-coordinate of lower-left corner of 
      0,                  // first scan line in array
      height,             // number of scan lines
      m_buf,              // address of array with DIB bits
      m_bmp, // address of structure with bitmap info.
      DIB_RGB_COLORS      // RGB or palette indexes
      );
  }

  virtual unsigned char *getBuf() {
    return m_buf;
  }

  /**
   * Returns the width in pixels.
   */
  virtual unsigned int getWidth() {
    return m_bmp->bmiHeader.biWidth;
  }

  /**
   * Returns the height in pixels.
   */
  virtual unsigned int getHeight() {
    return m_bmp->bmiHeader.biHeight;
  }

  /**
   * Returns the number of bits per pixel.
   */
  virtual int getBPP() {
    return m_bmp->bmiHeader.biBitCount;
  }
protected:
  GnNativeBitmap() : m_bmp(0), m_buf(0) {
  }

private:
  HWND m_hwnd;
  HDC m_dc;
  BITMAPINFO *m_bmp;
  unsigned char *m_buf;
};

#endif // GONA_GRAPHICS_NATIVE_BITMAP_WIN_H
