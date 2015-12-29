/**
 * Copyright (C) 2013-2014 The Gona Project
 *
 * Contact: airgiser@gmail.com
 */

#ifndef GONA_GRAPHICS_NATIVE_BITMAP_X_H
#define GONA_GRAPHICS_NATIVE_BITMAP_X_H
 
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <stdlib.h>
#include <string.h>

#include "../../GnImage.h"
#include "../GnBitmap.h"

class GnNativeBitmap : public GnBitmap {
public:
  GnNativeBitmap(Display *display, Window wnd, unsigned int width, unsigned int height) : 
    m_display(display), m_wnd(wnd), m_xImage(0), m_buf(0), m_width(width), m_height(height)
  {
    // Create a X Graphics Context
    m_gc = XCreateGC(display, wnd, 0, 0);

    int screen = XDefaultScreen(display);
    int depth = XDefaultDepth(display, screen);
    Visual *visual = XDefaultVisual(display, screen);
    switch (depth) {
      case 15:
        m_bpp = 16;
        // TODO: pixel format
        break;
      case 16:
        m_bpp = 16;
        // TODO: pixel format
        break;
      case 24:
      case 32:
        // TODO: pixel format
        m_bpp = 32;
        break;
    }

    // Allocate the image's pixel buffer.
    unsigned int stride = width * (m_bpp / 8);
    unsigned int imgSize = stride * height;
    m_buf = (unsigned char*)malloc(imgSize);
    memset(m_buf, 255, imgSize);

    // Create a image structure.
    m_xImage = XCreateImage(display, visual, depth, ZPixmap, 0, (char*)m_buf, 
        width, height, m_bpp, stride);
  }

  ~GnNativeBitmap() {
    // Frees both the image structure 
    // and the data pointed to by the image structure.
    XDestroyImage(m_xImage);

    XFreeGC(m_display, m_gc);
  }

public:
  /**
   * Transfer the bitmap bits to device.
   */
  virtual void draw() {
    if (!m_xImage) {
      return;
    }

    m_xImage->data = (char*)m_buf;
    XPutImage(m_display, m_wnd, m_gc, m_xImage, 
        0, 0, 0, 0, m_width, m_height);
  }

  /**
   * Returns the pixel buffer.
   */
  virtual unsigned char *getBuf() {
    return m_buf;
  }

  /**
   * Returns the width in pixels.
   */
  virtual unsigned int getWidth() {
    return m_width;
  }

  /**
   * Returns the height in pixels.
   */
  virtual unsigned int getHeight() {
    return m_height;
  }

  /**
   * Returns the number of bits per pixel.
   */
  virtual int getBPP() {
    return m_bpp;
  }

protected:
  GnNativeBitmap() : m_xImage(0), m_buf(0), m_width(0), m_height(0), m_bpp(0) {
  }

private:
  Display *m_display;
  Window m_wnd;

  GC m_gc;
  XImage *m_xImage;
  unsigned char *m_buf;
  unsigned int m_width;
  unsigned int m_height;
  unsigned int m_bpp;
};

#endif // GONA_GRAPHICS_NATIVE_BITMAP_X_H
