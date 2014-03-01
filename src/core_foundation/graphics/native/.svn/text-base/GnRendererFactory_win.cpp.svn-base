/**
 * Copyright (C) 2013-2014 The Gona Project
 *
 * Contact: airgiser@gmail.com
 */

#include "GnRendererFactory_win.h"

// For GL Renderer
#include "gl/native/GnNativeGLContext_win.h"
#include "gl/GnGLRenderer.h"

// For Agg Renderer
#include "agg/native/GnNativeBitmap_win.h"
#include "agg/GnAggRenderer.h"

GnRenderer *GnAggRendererFactory::CreateRenderer(HWND hwnd, unsigned int width, unsigned int height)
{
  // Create Agg Canvas
  unsigned int bpp = SYS_BPP; // TODO: ...
  GnBitmap *bitmap = new GnNativeBitmap(hwnd, width, height, bpp);
  GnRenderer *aggRenderer = new GnAggRenderer(bitmap);
  return aggRenderer;
}

GnRenderer *GnGLRendererFactory::CreateRenderer(HWND hwnd, unsigned int width, unsigned int height)
{
  // Create GL Canvas
  GnNativeGLContext *context = new GnNativeGLContext(hwnd, width, height);
  GnRenderer *glRenderer = new GnGLRenderer(context);
  return glRenderer;
}