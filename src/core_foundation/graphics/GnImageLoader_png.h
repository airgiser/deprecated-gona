/**
 * Copyright (C) 2013-2014 The Gona Project
 *
 * Contact: airgiser@gmail.com
 */

#ifndef GONA_GRAPHICS_IMAGE_LOADER_PNG_H
#define GONA_GRAPHICS_IMAGE_LOADER_PNG_H

#include "GnImageLoader.h"

/** \class GnPNGImageLoader
 *
 *  Load/Save image's pixel data from/to png files.
 */
class GnPNGImageLoader : public GnImageLoader
{
public:
  /**
   * Constructor.
   */
  GnPNGImageLoader();

  /**
   * Destructor.
   */
  virtual ~GnPNGImageLoader();

  /**
   * Load an image from the specified file.
   *
   * @param fileName name of the specified image file
   * @return a pointer to the image object
   */
  virtual GnImage* loadImage(const char *fileName);

  /**
   * Save an image to the specified file.
   *
   * @param image an image object to be saved
   * @param fileName the specified image file name
   */
  virtual void saveImage(GnImage &image, const char *fileName);
};

#endif // GONA_GRAPHICS_IMAGE_LOADER_PNG_H