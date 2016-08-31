/**
 * Copyright (C) 2013-2014 The Gona Project
 *
 * Contact: airgiser@gmail.com
 */

#ifndef GONA_GRAPHICS_RENDERER_FACTORY_H
#define GONA_GRAPHICS_RENDERER_FACTORY_H

#include "GnRenderer.h"

/** \class GnRendererFactory
 *
 *  Provide method for creating an instance of GnRenderer.
 */
class GnRendererFactory
{
public:
  GnRendererFactory() {}

  virtual ~GnRendererFactory() {}

  virtual GnRenderer *CreateRenderer(int x, int y, int width, int height) = 0;
};

/** \class GnGLRendererFactory
 *
 *  Provide method for creating an instance of GnRenderer(OpenGL).
 */
class GnGLRendererFactory : public GnRendererFactory
{
public:
  GnGLRendererFactory() {}

  virtual ~GnGLRendererFactory() {}

  virtual GnRenderer *CreateRenderer(int x, int y, int width, int height);
};

#endif // GONA_GRAPHICS_RENDERER_FACTORY_H
