/**
 * Copyright (C) 2013-2014 The Gona Project
 *
 * Contact: airgiser@gmail.com
 */

#ifndef GONA_GRAPHICS_CANVAS_H
#define GONA_GRAPHICS_CANVAS_H

#include <stdlib.h>

#include "GnPoint.h"
#include "GnPaint.h"
#include "GnImage.h"
#include "GnRenderer.h"

/** \class GnCanvas
 *
 *  A Canvas used for drawing shaps, texts or images.
 *  It holds the current state of the rendering device.
 */
class GnCanvas {
public:
  /**
   * Default constructor.
   */
  GnCanvas();

  /**
   * Construct a new Canvas with a specified renderer. 
   */
  explicit GnCanvas(GnRenderer *renderer);

  virtual ~GnCanvas();

public:
  /**
   * Modifies the current transformation matrix by translating the origin.
   *
   * @param dx the amount to translate in the X direction
   * @param dy the amount to translate in the Y direction
   */
  void translate(int dx, int dy);

  /**
   * Modifies the current transformation matrix by scaling x and y.
   *
   * @param scaleX the scale factor for the X dimension
   * @param scaleY the scale factor for the Y dimension
   */
  void scale(float scaleX, float scaleY);

  /**
   * Modifies the current transformation matrix by rotating the user-space axes.
   *
   * @param degree the angle(in degrees) by which the user-space axes will be rotated
   */
  void rotate(float degrees);

  /**
   * Modifies the current matrix by skew transformation.
   *
   * @param skewX the amount to skew in the X dimension
   * @param skewY the amount to skew in the Y dimension
   */
  void skew(float skewX, float skewY);

  /**
   * Sets the current matrix to identity.
   */
  void resetMatrix();

public:
  /**
   * Erases the entire canvas to the specified color.
   *
   * @param color the specified color used to clear background
   */
  void clear(GnColor color);

  /**
   * Transfer the buffer bits to device.
   */
  void swapBuffers();

  /**
   * Sets the current paint which used to draw shaps, texts etc.
   *
   * @param paint a new paint
   */
  void setPaint(const GnPaint &paint);

  /**
   * Draw a line segment.
   *
   * @param startX the x-coordinate of the start point of the line segment
   * @param startY the y-coordinate of the start point of the line segment
   * @param endX the x-coordinate of the end point of the line segment
   * @param endY the y-coordinate of the end point of the line segment
   */
  void drawLine(int startX, int startY, int endX, int endY);

  /**
   * Draw the specified polyline.
   *
   * @param points the vertices of the polyline
   * @param num the num of vertices of the polyline
   */
  void drawPolyLine(const GnPoint *points, int num);

  /**
   * Draw the specified polygon.
   *
   * @param points the vertices of the polygon
   * @param num the num of vertices of the polygon
   */
  void drawPolygon(const GnPoint *points, int num);

  /**
   * Draw the specified circle
   *
   * @param x the x-coordinate of the center of the circle 
   * @param y the y-coordinate of the center of the circle
   * @param radius the radius of the circle
   */
  void drawCircle(int x, int y, float radius);

  /**
   * Draw the specified rectangle
   *
   * @param left the position of the left side of the rectangle
   * @param top the position of the top side of the rectangle
   * @param right the position of the right side of the rectangle
   * @param bottom the position of the bottom side of the rectangle
   */
  void drawRect(int left, int top, int right, int bottom);

  /**
   * Draw the specified round-rect.
   *
   * @param left the position of the left side of the rectangle
   * @param top the position of the top side of the rectangle
   * @param right the position of the right side of the rectangle
   * @param bottom the position of the bottom side of the rectangle
   * @param rx the x-radius of the oval used to round the corners
   * @param ry the y-radius of the oval used to round the corners
   */
  void drawRoundRect(int left, int top, int right, int bottom, int rx, int ry);

  /**
   * Draw the specified text.
   *
   * @param x the x-coordinate of the origin of the text
   * @param y the y-coordinate of the origin of the text
   * @param text the text to be drawn
   * @param len the length of the text
   */
  void drawText(const wchar_t *text, size_t len, int x, int y);

  /**
   * Draw the specified image.
   *
   * @param image the image to be drawn
   * @param left the position of the left side of the image
   * @param top the position of the top side of the image
   */
  void drawImage(const GnImage &image, int left, int top);

private:
  GnRenderer *m_renderer;
};

#endif // GONA_GRAPHICS_CANVAS_H
