/**
 * Copyright (C) 2013-2014 The Gona Project
 *
 * Contact: airgiser@gmail.com
 */

#ifndef GONA_CORE_POINT_H
#define GONA_CORE_POINT_H

#include <stdint.h>

/** \struct GnPoint
 *
 *  A pair of (x,y) coordinate, use two 32-bit interger.
 */
struct GnPoint {
  int32_t m_x;
  int32_t m_y;

  GnPoint() : m_x(0), m_y(0) {}

  GnPoint(int x, int y) : m_x(x), m_y(y) {}
};

#endif // GONA_CORE_POINT_H