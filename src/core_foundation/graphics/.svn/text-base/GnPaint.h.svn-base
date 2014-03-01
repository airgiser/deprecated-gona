/**
 * Copyright (C) 2013-2014 The Gona Project
 *
 * Contact: airgiser@gmail.com
 */

#ifndef GONA_GRAPHICS_PAINT_H
#define GONA_GRAPHICS_PAINT_H

#include "GnColor.h"

/** \struct GnPaint
 *
 *  Specify the style and color for drawing.
 */
struct GnPaint {
  GnPaint() : m_antialias(kAntialiasNormal), m_lineWidth(0), 
    m_lineCap(kButtCap), m_lineJoin(kMiterJoin), m_textSize(16) {
  }

  /**
   * Specifies the type of antialiasing.
   */
  enum GnAntialiasType {
    /// Disable antialiasing
    kAntialiasNone,
    /// Prefer performance over quality
    kAntialiasFast,
    /// Balance quality against performance
    kAntialiasNormal,
    /// Render at the highest quality
    kAntialiasBest,
  };

  /**
   * Set the shape antialias mode.
   * @param antialias the new antialias mode
   */
  void setAntialias(GnAntialiasType antialias) {
    m_antialias = antialias;
  }
  
  /**
   * Get the current shape antialias mode.
   * @return the current antialias mode.
   */
  GnAntialiasType getAntialias() const {
    return m_antialias;
  }

  /**
   * Set the paint's color.
   * @param color the new color value
   */
  void setColor(GnColor color) {
    m_color = color;
  }

  /**
   * Get the paint's color.
   * @return the paint's color
   */
  GnColor getColor() const {
    return m_color;
  }

  /**
   * Set the current line width for stroking.
   * @param lineWidth a line width
   */
  void setLineWidth(float lineWidth) {
    m_lineWidth = lineWidth;
  }

  /**
   * Get the current line width for stroking.
   * @return the current line width
   */
  float getLineWidth() const {
    return m_lineWidth;
  }

  /**
   * Specifies how to render the endpoints of the path when stroking.
   */
  enum GnLineCap {
    /// begin/end with no extension
    kButtCap,
    /// begin/end with a semi-circle extension
    kRoundCap,
    /// begin/end with a half square extension
    kSquareCap,
  };

  /**
   * Set the current line cap style.
   * @param lineCap a line cap style
   */
  void setLineCap(GnLineCap lineCap) {
    m_lineCap = lineCap;
  }

  /**
   * Get the current line cap style.
   * @return the current line cap style
   */
  GnLineCap getLineCap() const {
    return m_lineCap;
  }

  /**
   * Specifies how to render the junction of two lines when stroking.
   */
  enum GnLineJoin {
    /// connect path segments with a sharp join
    kMiterJoin,
    /// connect path segments with a round join
    kRoundJoin,
    /// connect path segments with a bevel join
    kBevelJoin,
  };

  /**
   * Set the current line join style.
   * @param lineJoin a line join style
   */
  void setLineJoin(GnLineJoin lineJoin) {
    m_lineJoin = lineJoin;
  }

  /**
   * Get the current line join style.
   * @return the current line join style
   */
  GnLineJoin getLineJoin() const {
    return m_lineJoin;
  }

  /**
   * Set the paint's text size.
   * @param textSize a text size, this value must be > 0.
   */
  void setTextSize(unsigned int textSize) {
    m_textSize = textSize;
  }

  /**
   * Get the paint's text size.
   * @return the paint's text size
   */
  unsigned int getTextSize() const {
    return m_textSize;
  }

  GnAntialiasType m_antialias;
  GnColor         m_color;

  float           m_lineWidth;
  GnLineCap       m_lineCap;
  GnLineJoin      m_lineJoin;

  unsigned int    m_textSize;
};

#endif // GONA_GRAPHICS_PAINT_H