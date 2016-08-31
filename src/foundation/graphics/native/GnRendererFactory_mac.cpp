/**
 * Copyright (C) 2013-2014 The Gona Project
 *
 * Contact: airgiser@gmail.com
 */

#include "GnRendererFactory_mac.h"

// For GL Renderer
#include "gl/native/GnNativeGLContext_mac.h"
#include "gl/GnGLRenderer.h"

GnRenderer *GnGLRendererFactory::CreateRenderer(int x, int y, int width, int height)
{
  // Create GL Canvas
  GnNativeGLContext *context = new GnNativeGLContext(x, y, width, height);
  GnRenderer *glRenderer = new GnGLRenderer(context);
  return glRenderer;
}
