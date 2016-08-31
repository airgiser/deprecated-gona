/**
 * Copyright (C) 2013-2014 The Gona Project
 *
 * Contact: airgiser@gmail.com
 */

#ifndef GONA_GRAPHICS_GL_CONTEXT_H
#define GONA_GRAPHICS_GL_CONTEXT_H

/** \class GnGLContext
 *
 *  OpenGL Rendering Context.
 */
class GnGLContext {
public:
  GnGLContext() {}

  virtual ~GnGLContext() {}

public:
  /**
   * Sets this rendering context as the calling thread's current rendering context.
   */
  virtual bool makeCurrent() = 0;

  /**
   * Exchanges the front and back buffers
   */
  virtual void swapBuffers() = 0;

  /**
   * Set the viewport
   */
  virtual void setViewport(int x, int y, int width, int height) = 0;

  /**
   * Gets the pixel width of the rendering device.
   */
  virtual int getWidth() = 0;

  /**
   * Gets the pixel height of the rendering device.
   */
  virtual int getHeight() = 0;
};

#endif // GONA_GRAPHICS_GL_CONTEXT_H
