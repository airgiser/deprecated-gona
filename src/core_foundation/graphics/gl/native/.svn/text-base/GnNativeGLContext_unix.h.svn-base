/**
 * Copyright (C) 2013-2014 The Gona Project
 *
 * Contact: airgiser@gmail.com
 */

#ifndef GONA_GRAPHICS_NATIVE_GL_CONTEXT_UNIX_H
#define GONA_GRAPHICS_NATIVE_GL_CONTEXT_UNIX_H

#include <X11/Xlib.h>
#include <GL/glx.h>

#include "../GnGLContext.h"

class GnNativeGLContext : public GnGLContext {
public:
  GnNativeGLContext(Display *display, Window wnd, unsigned int width, unsigned int height) 
  {
    if (display == NULL) {
      return;
    }
    m_display = display;
    m_wnd = wnd;
    
    // Choose an visual
    static int attrs[] = { GLX_RGBA, None };
    XVisualInfo *visualInfo = glXChooseVisual(m_display, DefaultScreen(m_display), attrs);
    if (!visualInfo) {
      return;
    }

    // creates a rendering context.
    m_glxContext = glXCreateContext(m_display, visualInfo, 0, GL_FALSE);
    XFree(visualInfo);
    if (!m_glxContext) {
      this->destroyContext();
      return;
    }

    // makes the context as the current rendering context.
    if (!makeCurrent()) {
      this->destroyContext();
      return;
    }

    // initialize.
    init(width, height);
  }

  virtual ~GnNativeGLContext() {
    this->destroyContext();
  }

public:
  /**
   * Sets this rendering context as the calling thread's current rendering context.
   */
  virtual bool makeCurrent() {
    return glXMakeCurrent(m_display, m_wnd, m_glxContext);
  }

  /**
   * Exchanges the front and back buffers
   */
  virtual void swapBuffers() {
    glXSwapBuffers(m_display, m_wnd);
  }

  /**
   * Initialize the context.
   */
  virtual void init(int width, int height) {
    // sets the viewport.
    m_width = width;
    m_height = height;
    glViewport(0, 0, width, height);

    // sets the matrix.
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0, width, height, 0.0, 1.0, -1.0);
  }

  /**
   * Gets the pixel width of the rendering device.
   */
  virtual int getWidth() { return m_width; }

  /**
   * Gets the pixel height of the rendering device.
   */
  virtual int getHeight() { return m_height; }

private:
  XVisualInfo *getBestVisualInfo() {
    XVisualInfo *visualInfo = NULL;
    return visualInfo;
  }

  void destroyContext() {
    if (m_display) {
      if (m_glxContext) {
        glXDestroyContext(m_display, m_glxContext);
        m_glxContext = NULL;
      }

      m_display = NULL;
    }
  }
private:
  Display* m_display;
  Window m_wnd;
  GLXContext m_glxContext;

  int m_width;
  int m_height;
};

#endif // GONA_GRAPHICS_NATIVE_GL_CONTEXT_UNIX_H
