/**
 * Copyright (C) 2013-2014 The Gona Project
 *
 * Contact: airgiser@gmail.com
 */

#ifndef GONA_GRAPHICS_IMAGE_LOADER_H
#define GONA_GRAPHICS_IMAGE_LOADER_H

#include "GnImage.h"

/** \class GnImageLoader
 *
 *  Load/Save image's pixel data from/to files.
 */
class GnImageLoader {
public:
  /**
   * Constructor.
   */
  GnImageLoader() {}

  /**
   * Destructor.
   */
  virtual ~GnImageLoader() {}

  /**
   * Load an image from the specified file.
   *
   * @param fileName name of the specified image file
   * @return a pointer to the image object
   */
  virtual GnImage* loadImage(const char *fileName) = 0;

  /**
   * Save an image to the specified file.
   *
   * @param image an image object to be saved
   * @param fileName the specified image file name
   */
  virtual void saveImage(GnImage &image, const char *fileName) = 0;
};

#endif // GONA_GRAPHICS_IMAGE_LOADER_H