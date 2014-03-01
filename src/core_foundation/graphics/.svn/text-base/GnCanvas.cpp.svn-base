/**
 * Copyright (C) 2013-2014 The Gona Project
 *
 * Contact: airgiser@gmail.com
 */

#include "GnCanvas.h"

GnCanvas::GnCanvas() : m_renderer(NULL) {
}

GnCanvas::GnCanvas(GnRenderer *renderer) : m_renderer(renderer) {
}

GnCanvas::~GnCanvas() {
  if (m_renderer) {
    delete m_renderer;
    m_renderer = NULL;
  }
}

void GnCanvas::translate(int dx, int dy) {
}

void GnCanvas::scale(float scaleX, float scaleY) {
}

void GnCanvas::rotate(float degrees) {
}

void GnCanvas::skew(float skewX, float skewY) {
}

void GnCanvas::resetMatrix() {
}

void GnCanvas::clear(GnColor color) {
  if (m_renderer) {
    m_renderer->clear(color);
  }
}

void GnCanvas::swapBuffers() {
  if (m_renderer) {
    m_renderer->swapBuffers();
  }
}

void GnCanvas::setPaint(const GnPaint &paint) {
  if (m_renderer) {
    m_renderer->setPaint(paint);
  }
}

void GnCanvas::drawLine(int startX, int startY, int endX, int endY) {
}

void GnCanvas::drawPolyLine(const GnPoint *points, int num) {
  if (m_renderer) {
    m_renderer->drawPolyLine(points, num);
  }
}

void GnCanvas::drawPolygon(const GnPoint *points, int num) {
  if (m_renderer) {
    m_renderer->drawPolygon(points, num);
  }
}

void GnCanvas::drawCircle(int x, int y, float radius) {
}

void GnCanvas::drawRect(int left, int top, int right, int bottom) {
}

void GnCanvas::drawRoundRect(int left, int top, int right, int bottom, int rx, int ry) {
}

void GnCanvas::drawText(const wchar_t *text, size_t len, int x, int y) {
  if (m_renderer) {
    m_renderer->drawText(text, len, x, y);
  }
}

void GnCanvas::drawImage(const GnImage &image, int left, int top) {
  if (m_renderer) {
    m_renderer->drawImage(image, left, top);
  }
}
