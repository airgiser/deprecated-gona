/**
 * Copyright (C) 2013-2014 The Gona Project
 *
 * Contact: airgiser@gmail.com
 */

#ifndef GONA_GRAPHICS_BITMAP_H
#define GONA_GRAPHICS_BITMAP_H

/** \class GnBitmap
 *
 *  A pixel map.
 */
class GnBitmap {
public:
  /**
   * Default constructor.
   */
  GnBitmap() {}

  /**
   * Destructor.
   */
  virtual ~GnBitmap() {}
public:
  /**
   * Returns the width in pixels.
   */
  virtual unsigned int getWidth() = 0;

  /**
   * Returns the height in pixels.
   */
  virtual unsigned int getHeight() = 0;

  /**
   * Returns the number of bits per pixel.
   */
  virtual int getBPP() = 0;

  /**
   * Returns the pointer to the pixel buffer.
   */
  virtual unsigned char *getBuf() = 0;

  /**
   * Sets the pixels to the device context.
   */
  virtual void draw() = 0;

  /**
   * Calculate stride by the width and bits per pixel of the bitmap.
   */
  static unsigned int calcStride(unsigned int width, unsigned int bpp);
};

#endif // GONA_GRAPHICS_BITMAP_H