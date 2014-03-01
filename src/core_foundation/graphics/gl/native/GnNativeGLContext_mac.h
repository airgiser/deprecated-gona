/**
 * Copyright (C) 2013-2014 The Gona Project
 *
 * Contact: airgiser@gmail.com
 */

#ifndef GONA_GRAPHICS_NATIVE_GL_CONTEXT_MAC_H
#define GONA_GRAPHICS_NATIVE_GL_CONTEXT_MAC_H

#include <OpenGL/OpenGL.h>

#include "GnGLContext.h"

class GnNativeGLContext : public GnGLContext {
public:
  GnNativeGLContext();

  virtual ~GnNativeGLContext();
public:
  virtual bool makeCurrent();

  virtual void swapBuffers();
};

#endif // GONA_GRAPHICS_NATIVE_GL_CONTEXT_MAC_H