/*
 * Copyright (C) 2013-2014 The Gona Project
 * 
 * Contact: airgiser@gmail.com
 */

#include <X11/Xlib.h>
#include <X11/Xatom.h>
#include <wchar.h>

#define USE_GL 1
#if USE_GL
#include "gl/native/GnNativeGLContext_unix.h"
#include "gl/GnGLRenderer.h"
#else
#include "agg/native/GnNativeBitmap_unix.h"
#include "agg/GnAggRenderer.h"
#endif


#include "GnCanvas.h"

void onDraw(GnCanvas *canvas);

int main()
{
  // Open a connection to the X server
  Display *display = XOpenDisplay(0);
  if (display == 0)
  {
    // Unable to open Display!
    return -1;
  }

  // Get a black color
  int blackColor = BlackPixel(display, DefaultScreen(display));

  // Create the window
  int width = 1024;
  int height = 512;
  int borderWidth = 0;
  Window wnd = XCreateSimpleWindow(display, 
      DefaultRootWindow(display),
      0, 0, width, height, borderWidth,
      blackColor, blackColor);

  // Tell the X server that we want to get the events 
  // associated with the specified mask
  long eventMask =
    PointerMotionMask |
    ButtonPressMask |
    ButtonReleaseMask |
    ExposureMask |
    KeyPressMask |
    StructureNotifyMask;
  XSelectInput(display, wnd, eventMask);

  // Make the window appear on the screen
  XMapWindow(display, wnd);

  // Generate a atom identifier
  Atom closeAtom = XInternAtom(display, "WM_DELETE_WINDOW", false);

  // Set the WM_PROTOCOLS property
  XSetWMProtocols(display, wnd, &closeAtom, 1);

#if USE_GL 
  // Create a OpenGL context
  GnGLContext *context = new GnNativeGLContext(display, wnd, 
      width, height);

  // Create a renderer
  GnGLRenderer *renderer = new GnGLRenderer(context);
#else
  // Create a native bitmap backend
  GnNativeBitmap *bitmap = new GnNativeBitmap(display, wnd, 
      width, height);

  // Create a renderer
  GnAggRenderer *renderer = new GnAggRenderer(bitmap);
#endif
  // Create canvas
  GnCanvas *canvas = new GnCanvas(renderer);

  // Send request to the X server
  XFlush(display);

  // Waiting
  bool updateFlag = true;
  bool running = true;
  XEvent event;
  while (running) {
    if (updateFlag) {
      onDraw(canvas);
      XSync(display, true);
      updateFlag = false;
    }

    // Get events
    XNextEvent(display, &event);
    switch (event.type) {
      case Expose:
        canvas->swapBuffers();
        XFlush(display);
        XSync(display, false);
        break;
      case ClientMessage:
        if (event.xclient.format == 32 &&
            event.xclient.data.l[0] == closeAtom ) {
          running = false;
        }
        break;
      default:
        break;
    }
  }

  // Release the resources
  delete canvas;
  XDestroyWindow(display, wnd);
  XCloseDisplay(display);

  return 0;
}

void onDraw(GnCanvas *canvas) {
  // Clear background
  canvas->clear(GnColor(150, 0, 0)); 

  // Sets the paint
  GnPaint paint;
  paint.setColor(GnColor(229,176, 69));
  paint.setLineWidth(8);
  paint.setLineCap(GnPaint::kRoundCap);
  paint.setLineJoin(GnPaint::kRoundJoin);
  paint.setTextSize(32);
  canvas->setPaint(paint);

  // Draws some shapes
  const int num = 3;
  GnPoint line1[num] = {
    GnPoint(10, 10), GnPoint(300, 200), GnPoint(500, 330) };
  canvas->drawPolyLine(line1, num);
  GnPoint line2[num] = {
    GnPoint(200, 10), GnPoint(400, 180), GnPoint(500, 330) };
  canvas->drawPolyLine(line2, num);
  GnPoint line3[num] = {
    GnPoint(400, 100), GnPoint(450, 200), GnPoint(500, 330) };
  canvas->drawPolyLine(line3, num);

  GnPoint polygon[num] = {
    GnPoint(30, 300), GnPoint(330, 300), GnPoint(200, 500)};
  canvas->drawPolygon(polygon, num);

  const wchar_t *text = L"En & 汉";
  canvas->drawText(text, wcslen(text), 0, 200);

  // Update to the window
  canvas->swapBuffers();
}
