/**
 * Copyright (C) 2013-2014 The Gona Project
 *
 * Contact: airgiser@gmail.com
 */

#ifndef GONA_GRAPHICS_RENDERER_FACTORY_H
#define GONA_GRAPHICS_RENDERER_FACTORY_H

#include "GnRenderer.h"
#include <windows.h>

/** \class GnRendererFactory
 *
 *  Provide method for creating an instance of GnRenderer.
 */
class GnRendererFactory
{
public:
  GnRendererFactory() {}

  virtual ~GnRendererFactory() {}

  virtual GnRenderer *CreateRenderer(HWND hwnd, unsigned int width, unsigned int height) = 0;
};

/** \class GnAggRendererFactory
 *
 *  Provide method for creating an instance of GnRenderer(AGG).
 */
class GnAggRendererFactory
{
public:
  GnAggRendererFactory() {}

  virtual ~GnAggRendererFactory() {}

  virtual GnRenderer *CreateRenderer(HWND hwnd, unsigned int width, unsigned int height);
};

/** \class GnGLRendererFactory
 *
 *  Provide method for creating an instance of GnRenderer(OpenGL).
 */
class GnGLRendererFactory
{
public:
  GnGLRendererFactory() {}

  virtual ~GnGLRendererFactory() {}

  virtual GnRenderer *CreateRenderer(HWND hwnd, unsigned int width, unsigned int height);
};

#endif // GONA_GRAPHICS_RENDERER_FACTORY_H