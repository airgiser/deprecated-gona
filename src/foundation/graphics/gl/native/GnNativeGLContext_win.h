/**
 * Copyright (C) 2013-2014 The Gona Project
 *
 * Contact: airgiser@gmail.com
 */

#ifndef GONA_GRAPHICS_NATIVE_GL_CONTEXT_WIN_H
#define GONA_GRAPHICS_NATIVE_GL_CONTEXT_WIN_H

#include <Windows.h>
#include <GL/GL.h>

#include "../GnGLContext.h"

/** \class GnNativeGLContext
 *
 *  OpenGL rendering context on MS Windows.
 */
class GnNativeGLContext : public GnGLContext {
public:
  GnNativeGLContext(HWND hwnd, int width, int height) 
  {
    // gets a handle to the device context
    m_dc = GetDC(hwnd);
    m_hwnd = hwnd;

    // sets the pixel format of the device context.
    setPixformat(m_dc);

    // creates a rendering context.
    m_context = wglCreateContext (m_dc);
    if (!m_context) {
      GLenum  error = glGetError();
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
   * Makes this rendering context as the calling thread's current rendering context. 
   */
  virtual bool makeCurrent() {
    return wglMakeCurrent(m_dc, m_context) != FALSE;
  }

  /**
   * Swaps the front and back buffers.
   */
  virtual void swapBuffers() {
    SwapBuffers(m_dc);
  }

  /**
   * Initialize the context.
   */
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

  /**
   * Gets the pixel width of the rendering device.
   */
  virtual int getWidth() {
    return m_width;
  }

  /**
   * Gets the pixel width of the rendering device.
   */
  virtual int getHeight() {
    return m_height;
  }
protected:
  /**
   * Deletes the OpenGL rendering context.
   */
  void destroyContext() {
    // Deletes the OpenGL context.
    if (m_context) {
      wglDeleteContext(m_context);
      m_context = 0;
    }

    // Releases the device context.
    if (m_hwnd && m_dc) {
      ReleaseDC(m_hwnd, m_dc);
      m_dc = 0;
    }
  }

  /**
   * A rendering context is not the same as a device context. So we should
   * set the pixel format of the device context before creating a rendering context.
   */
  void setPixformat(HDC hdc) {
    PIXELFORMATDESCRIPTOR pfd = { 
      sizeof(PIXELFORMATDESCRIPTOR),   // size of this pfd  
      1,                     // version number  
      PFD_DRAW_TO_WINDOW |   // support window  
      PFD_SUPPORT_OPENGL |   // support OpenGL  
      PFD_DOUBLEBUFFER,      // double buffered  
      PFD_TYPE_RGBA,         // RGBA type  
      24,                    // 24-bit color depth  
      0, 0, 0, 0, 0, 0,      // color bits ignored  
      0,                     // no alpha buffer  
      0,                     // shift bit ignored  
      0,                     // no accumulation buffer  
      0, 0, 0, 0,            // accum bits ignored  
      32,                    // 32-bit z-buffer  
      0,                     // no stencil buffer  
      0,                     // no auxiliary buffer  
      PFD_MAIN_PLANE,        // main layer  
      0,                     // reserved  
      0, 0, 0                // layer masks ignored  
    }; 

    // get the best available match of pixel format for the device context   
    int iPixelFormat = ChoosePixelFormat(hdc, &pfd); 

    // make that the pixel format of the device context  
    SetPixelFormat(hdc, iPixelFormat, &pfd);
  }
private:
  HDC m_dc;
  HWND m_hwnd;
  HGLRC m_context;

  int m_width;
  int m_height;
};

#endif // GONA_GRAPHICS_NATIVE_GL_CONTEXT_WIN_H
