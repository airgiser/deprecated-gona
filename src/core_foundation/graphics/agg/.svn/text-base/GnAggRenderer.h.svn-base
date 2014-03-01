/**
 * Copyright (C) 2013-2014 The Gona Project
 *
 * Contact: airgiser@gmail.com
 */

#ifndef GONA_GRAPHICS_AGG_RENDERER_H
#define GONA_GRAPHICS_AGG_RENDERER_H

#include "agg_rendering_buffer.h"
#include "agg_path_storage.h"
#include "agg_conv_curve.h"
#include "agg_conv_stroke.h"

#include "agg_scanline_p.h"
#include "agg_scanline_u.h"
#include "agg_scanline_bin.h"
#include "agg_rasterizer_scanline_aa.h"

#include "agg_renderer_base.h"
#include "agg_renderer_primitives.h"
#include "agg_renderer_scanline.h"

#include "agg_font_freetype.h"

#include "GnBitmap.h"
#include "GnImage.h"
#include "GnRenderer.h"

#include "GnAggPixelFormat.h"

/** \class GnAggRender
 *
 *  A software renderer, internally used the Anti-Grain Geometry library.
 */
class GnAggRenderer : public GnRenderer {
  // renderer
  typedef agg::renderer_base<agg_pixfmt>                  renderer_base;
  typedef agg::renderer_primitives<renderer_base>         renderer_prim;
  typedef agg::renderer_scanline_bin_solid<renderer_base> renderer_bin;
  typedef agg::renderer_scanline_aa_solid<renderer_base>  renderer_aa;

  // vertex source
  typedef agg::conv_curve<agg::path_storage>  conv_curve;
  typedef agg::conv_stroke<agg::path_storage> conv_stroke;
  typedef agg::conv_transform<conv_curve>     curve_transform;
  typedef agg::conv_transform<conv_stroke>    stroke_transform;

  // font
  typedef agg::font_engine_freetype_int32       font_engine;
  typedef agg::font_cache_manager<font_engine>  font_cache;
public:
  /**
   * Default constructor.
   */
  GnAggRenderer();

  /**
   * Construct a new renderer with a specified bitmap as its backend.
   */
  GnAggRenderer(GnBitmap *bitmap);

  /**
   * Destructor.
   */
  virtual ~GnAggRenderer();

public:
  /**
   * Erases the entire canvas to the specified color.
   *
   * @param color the specified color used to clear background
   */
  virtual void clear(GnColor color);

  /**
   * Transfer the buffer bits to device.
   */
  virtual void swapBuffers();

  /**
   * Sets the current paint which used to draw shaps, texts etc.
   *
   * @param paint a new paint
   */
  virtual void setPaint(const GnPaint &paint);

  /**
   * Draw a polyline.
   *
   * @param points the vertices of the polyline
   * @param num the num of vertices of the polyline
   */
  virtual void drawPolyLine(const GnPoint *points, int num);

  /**
   * Draw a polygon.
   *
   * @param points the vertices of the polygon
   * @param num the num of vertices of the polygon
   */
  virtual void drawPolygon(const GnPoint *points, int num);

  /**
   * Draw the specified image.
   *
   * @param image the image to be drawn
   * @param left the position of the left side of the image
   * @param top the position of the top side of the image
   */
  virtual void drawImage(const GnImage &image, int left, int top);

  /**
   * Draw the specified text.
   *
   * @param x the x-coordinate of the origin of the text
   * @param y the y-coordinate of the origin of the text
   * @param text the text to be drawn
   * @param len the length of the text
   */
  virtual void drawText(const wchar_t *text, size_t len, int x, int y);

protected:
  void renderBin(renderer_bin &renderer) {
    agg::render_scanlines(m_rasterizer, m_binSL, renderer);
  }

  void renderAA(renderer_aa &renderer) {
    agg::render_scanlines(m_rasterizer, m_packedSL, renderer);
  }

private:
  /// the backend for drawing
  GnBitmap          *m_bitmap;

  // the paint's style
  float             m_lineWidth;
  agg::line_cap_e   m_lineCap;
  agg::line_join_e  m_lineJoin;
  agg::rgba8        m_color;
  unsigned int      m_textSize;

  // vertex source
  agg::path_storage m_path;
  conv_curve        m_convCurve;
  conv_stroke       m_convStroke;

  // rendering buffer
  agg::rendering_buffer m_renBuf;
  agg_pixfmt            m_pixfmt;

  // renderer
  renderer_base         m_baseRen;
  renderer_bin          m_binRen;
  renderer_aa           m_aaRen;

  /// packed scaline container, can keep anti-alias information
  agg::scanline_p8 m_packedSL;
  /// unpacked scanline container, can keep anti-alias information
  agg::scanline_u8 m_unpackedSL;
  /// binary scanline container, can't keep anti-alias information
  agg::scanline_bin m_binSL;
  /// rasterizer, used to render filled polygons
  agg::rasterizer_scanline_aa<> m_rasterizer;

  // font
  font_engine       m_fontEngine;
  font_cache        m_fontCache;
};
#endif // GONA_GRAPHICS_AGG_RENDERER_H