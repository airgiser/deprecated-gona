/**
 * Copyright (C) 2013-2014 The Gona Project
 *
 * Contact: airgiser@gmail.com
 */

#ifndef GONA_GRAPHICS_RENDERER_H
#define GONA_GRAPHICS_RENDERER_H

#include <stdlib.h>

#include "GnPaint.h"
#include "GnPoint.h"
#include "GnImage.h"

/** \class GnRenderer
 *
 *  Interface class for rendering device.
 *
 *  It's a base class for different types of rendering device(e.g. Software renderer, GPU).
 */
class GnRenderer {
public:
  GnRenderer() {}

  virtual ~GnRenderer() {}
public:
  /**
   * Erases the entire canvas to the specified color.
   *
   * @param color the specified color used to clear background
   */
  virtual void clear(GnColor color) = 0;

  /**
   * Transfer the buffer bits to device.
   */
  virtual void swapBuffers() = 0;

  /**
   * Sets the current paint which used to draw shaps, texts etc.
   *
   * @param paint a new paint
   */
  virtual void setPaint(const GnPaint &paint) = 0;

  /**
   * Draw a polyline.
   *
   * @param points the vertices of the polyline
   * @param num the num of vertices of the polyline
   */
  virtual void drawPolyLine(const GnPoint *points, int num) = 0;

  /**
   * Draw a polygon.
   *
   * @param points the vertices of the polygon
   * @param num the num of vertices of the polygon
   */
  virtual void drawPolygon(const GnPoint *points, int num) = 0;

  /**
   * Draw the specified image.
   *
   * @param image the image to be drawn
   * @param left the position of the left side of the image
   * @param top the position of the top side of the image
   */
  virtual void drawImage(const GnImage &image, int left, int top) = 0;

  /**
   * Draw the specified text.
   *
   * @param x the x-coordinate of the origin of the text
   * @param y the y-coordinate of the origin of the text
   * @param text the text to be drawn
   * @param len the length of the text
   */
  virtual void drawText(const wchar_t *text, size_t len, int x, int y) = 0;
};

#endif // GONA_GRAPHICS_RENDERER_H
