/**
 * Copyright (C) 2013-2014 The Gona Project
 *
 * Contact: airgiser@gmail.com
 */

#ifndef GONA_GRAPHICS_IMAGE_H
#define GONA_GRAPHICS_IMAGE_H

#include "GnPixelFormat.h"

/** \class GnImage
 *
 *  The Gona's Image class. an image object holds the image's pixel data.
 */
class GnImage {
public:
  /**
   * Construct an image with the specified size and pixel data.
   */
  GnImage(unsigned int width, unsigned int height, GnPixelFormat pixfmt, unsigned char *pixels);

  /**
   * Destructor.
   */
  virtual ~GnImage();
public:
  /**
   * Returns the image's width(in pixels).
   */
  unsigned int getWidth() const { return m_width; }

  /**
   * Returns the image's height(in pixels).
   */
  unsigned int getHeight() const { return m_height; }

  /**
   * Returns the number of bytes per row of the image.
   */
  unsigned int getStride() const { return m_stride; }

  /**
   * Returns the number of bits per pixel of the image.
   */
  unsigned char getBPP() const { return m_bpp; }

  /**
   * Returns the pixel format of the image.
   */
  GnPixelFormat getPixelFormat() const { return m_pixelFormat; }

  /**
   * Returns the raw pixels data of the image.
   */
  unsigned char *getRawData() const { return m_pixels; }

  /**
   * Calculate the image's stride by the width and bits per pixel of the image.
   */
  static unsigned int calcStride(unsigned int width, unsigned int bpp);

  /**
   * Gets the bits per pixel of the image by the pixel format.
   */
  static unsigned int calcBpp(unsigned char pixfmt);

protected:
  /** Default constructor. */
  GnImage();

  /** Copy constructor. */
  GnImage(const GnImage &image);

  /** Assignment operator */
  GnImage &operator = (const GnImage &other);
private:
  /// the image's width
  unsigned int m_width;

  /// the image's height
  unsigned int m_height;

  /// the number of bytes per row of the image
  unsigned int m_stride;

  /// the number of bits per pixel
  unsigned char m_bpp;

  /// the pixel format of the image
  GnPixelFormat m_pixelFormat;

  /// the pixel data of the image
  unsigned char *m_pixels;
};

#endif // GONA_GRAPHICS_IMAGE_H