/**
 * Copyright (C) 2013-2014 The Gona Project
 *
 * Contact: airgiser@gmail.com
 */

#ifndef GONA_GRAPHICS_NATIVE_GL_CONTEXT_ANDROID_H
#define GONA_GRAPHICS_NATIVE_GL_CONTEXT_ANDROID_H

#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>

#include "GnGLContext.h"

class GnNativeGLContext : public GnGLContext {
public:
  GnNativeGLContext(int width, int height)
  {
    // initialize.
    setViewport(0, 0, width, height);
  }

  virtual ~GnNativeGLContext() {
  }
public:
  /**
   * Sets this rendering context as the calling thread's current rendering context.
   */
  virtual bool makeCurrent() {
    return true;
  }

  /**
   * Exchanges the front and back buffers
   */
  virtual void swapBuffers() {
  }

  /**
   * Initialize the context.
   */
  virtual void setViewport(int x, int y, int width, int height) {
    m_width = width;
    m_height = height;

    // sets the viewport.
    glViewport(x, y, width, height);
  }

  /**
   * Gets the pixel width of the rendering device.
   */
  virtual int getWidth() {
    return m_width;
  }

  /**
   * Gets the pixel height of the rendering device.
   */
  virtual int getHeight() {
    return m_height;
  }

private:
  int m_width;
  int m_height;
};

#endif // GONA_GRAPHICS_NATIVE_GL_CONTEXT_ANDROID_H
