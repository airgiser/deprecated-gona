/**
 * Copyright (C) 2013-2014 The Gona Project
 *
 * Contact: airgiser@gmail.com
 */

#ifndef GONA_GRAPHICS_NATIVE_GL_CONTEXT_MAC_H
#define GONA_GRAPHICS_NATIVE_GL_CONTEXT_MAC_H

#include <OpenGL/OpenGL.h>
#include <OpenGL/gl.h>

#include <iostream>

#include "GnGLContext.h"

class GnNativeGLContext : public GnGLContext
{
public:
  GnNativeGLContext(int x, int y, int width, int height) : m_context(NULL) {
    // create context
    //createContext();

    // set the viewport
    setViewport(x, y, width, height);
  }

  virtual ~GnNativeGLContext() {
    destroyContext();
  }

public:
  virtual bool makeCurrent() {
    if (!m_context) {
      return false;
    }
    return (CGLSetCurrentContext(m_context) == kCGLNoError);
  }

  virtual void swapBuffers() {
    if (!m_context) {
      return;
    }
    CGLFlushDrawable(m_context);
  }

  virtual void setViewport(int x, int y, int width, int height) {
    // sets the viewport.
    m_width = width;
    m_height = height;
    glViewport(x, y, width, height);

    // TODO: sets the matrix.
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(x, width, height, y, 1.0, -1.0);
  }

  virtual int getWidth() { return m_width; }

  virtual int getHeight() { return m_height; }

protected:
  bool createContext() {
    // pixel format
    CGLPixelFormatAttribute attrs[] = {
      kCGLPFADoubleBuffer,
      (CGLPixelFormatAttribute)0
    };
    CGLPixelFormatObj pixelFormat;
    GLint pixels;
    CGLChoosePixelFormat(attrs, &pixelFormat, &pixels);
    if (pixelFormat == NULL) {
      return false;
    }

    // create context
    CGLCreateContext(pixelFormat, NULL, &m_context);
    CGLReleasePixelFormat(pixelFormat);
    if (m_context == NULL) {
      return false;
    }

    // makes the context as the current rendering context.
    if (!makeCurrent()) {
      destroyContext();
      return false;
    }

    return true;
  }

  void destroyContext() {
    if (m_context) {
      CGLReleaseContext(m_context);
      m_context = NULL;
    }
  }

private:
  CGLContextObj m_context;
  int m_width;
  int m_height;
};

#endif // GONA_GRAPHICS_NATIVE_GL_CONTEXT_MAC_H
