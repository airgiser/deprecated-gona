/**
 * Copyright (C) 2013-2014 The Gona Project
 *
 * Contact: airgiser@gmail.com
 */

#include "GnAggRenderer.h"

#include "agg_span_allocator.h"
#include "agg_span_interpolator_linear.h"
#include "agg_span_image_filter_rgb.h"
#include "agg_span_image_filter_rgba.h"
#include "agg_image_accessors.h"

GnAggRenderer::GnAggRenderer() : 
m_bitmap(NULL),
m_path(),
m_convCurve(m_path),
m_convStroke(m_path),
m_renBuf(),
m_pixfmt(m_renBuf),
m_baseRen(),
m_binRen(m_baseRen),
m_aaRen(m_baseRen),
m_packedSL(),
m_unpackedSL(),
m_binSL(),
m_rasterizer(),
m_fontEngine(),
m_fontCache(m_fontEngine)
{
}

GnAggRenderer::GnAggRenderer(GnBitmap *bitmap) :
m_bitmap(bitmap),
m_path(),
m_convCurve(m_path),
m_convStroke(m_path),
m_renBuf(),
m_pixfmt(m_renBuf),
m_baseRen(),
m_binRen(m_baseRen),
m_aaRen(m_baseRen),
m_packedSL(),
m_unpackedSL(),
m_binSL(),
m_rasterizer(),
m_fontEngine(),
m_fontCache(m_fontEngine)
{
  int stride = GnBitmap::calcStride(bitmap->getWidth(), bitmap->getBPP());
  /* TODO: platform dependent */
#ifdef GONA_FOR_WIN
  stride = -stride;
#endif

  m_renBuf.attach(bitmap->getBuf(), bitmap->getWidth(), bitmap->getHeight(), stride);
  m_baseRen.attach(m_pixfmt);
}

GnAggRenderer::~GnAggRenderer() {
  if (m_bitmap) {
    delete m_bitmap;
    m_bitmap = NULL;
  }
}

void GnAggRenderer::clear(GnColor color) {
  m_baseRen.clear(agg::rgba8(color.red, color.green, color.blue, color.alpha));
}

void GnAggRenderer::swapBuffers() {
  if (m_bitmap) {
    m_bitmap->draw();
  }
}

void GnAggRenderer::setPaint(const GnPaint &paint) {
  // sets the width of rasterized lines
  m_lineWidth = paint.getLineWidth();

  // sets the current cap style of line
  if (paint.getLineCap() == GnPaint::kButtCap) {
    m_lineCap = agg::butt_cap;
  } 
  else if (paint.getLineCap() == GnPaint::kRoundCap) {
    m_lineCap = agg::round_cap;
  }
  else if (paint.getLineCap() == GnPaint::kSquareCap) {
    m_lineCap = agg::square_cap;
  }

  // sets the current join style of line
  if (paint.getLineJoin() == GnPaint::kMiterJoin) {
    m_lineJoin = agg::miter_join;
  }
  else if (paint.getLineJoin() == GnPaint::kRoundJoin) {
    m_lineJoin = agg::round_join;
  }
  else if (paint.getLineJoin() == GnPaint::kBevelJoin) {
    m_lineJoin = agg::bevel_join;
  }

  // sets the current color
  GnColor clr = paint.getColor();
  m_color = agg::rgba8(clr.red, clr.green, clr.blue, clr.alpha);

  // sets the text's size
  m_textSize = paint.getTextSize();
}

void GnAggRenderer::drawPolyLine(const GnPoint *points, int num) {
  if ( num < 2 ) {
    return;
  }

  // sets the path
  m_path.remove_all();
  m_path.move_to(points[0].m_x, points[0].m_y);
  for (int i = 1; i < num; i++) {
    m_path.line_to(points[i].m_x, points[i].m_y);
  }

  // sets style of the polyline
  m_convStroke.width(m_lineWidth);
  m_convStroke.line_cap(m_lineCap);
  m_convStroke.line_join(m_lineJoin);

  // add the path to the rasterizer
  m_rasterizer.reset();
  m_rasterizer.add_path(m_convStroke);

  m_aaRen.color(m_color);
  renderAA(m_aaRen);
}

void GnAggRenderer::drawPolygon(const GnPoint *points, int num) {
  if ( num < 3 ) {
    return;
  }

  // sets the path
  m_path.remove_all();
  m_path.move_to(points[0].m_x, points[0].m_y);
  for (int i = 1; i < num; i++) {
    m_path.line_to(points[i].m_x, points[i].m_y);
  }
  m_path.close_polygon();

  // add the path to the rasterizer
  m_rasterizer.reset();
  m_rasterizer.add_path(m_path);

  m_binRen.color(m_color);
  renderBin(m_binRen);
}

void GnAggRenderer::drawImage(const GnImage &image, int left, int top) {
  typedef agg::span_allocator<agg::rgba8> span_allocator;
  typedef agg::span_interpolator_linear<> span_interpolator;
  typedef agg::image_accessor_clone<agg::pixfmt_rgb24> image_accessor_rgb;
  typedef agg::image_accessor_clone<agg::pixfmt_rgba32> image_accessor_rgba;
  typedef agg::span_image_filter_rgb_bilinear<image_accessor_rgb, span_interpolator> span_gen_rgb;
  typedef agg::span_image_filter_rgba_bilinear<image_accessor_rgba, span_interpolator> span_gen_rgba;

  // the image buffer
  agg::rendering_buffer rbuf;
  unsigned int width = image.getWidth();
  unsigned int height = image.getHeight();
  unsigned int stride = GnBitmap::calcStride(width, image.getBPP());
  rbuf.attach(image.getRawData(), width, height, stride);

  // make a rectangle path
  m_path.remove_all();
  m_path.move_to(left, top);
  m_path.line_to(left + width, top);
  m_path.line_to(left + width, top + height);
  m_path.line_to(left, top + height);
  m_path.close_polygon();

  // add the path to the rasterizer
  m_rasterizer.reset();
  m_rasterizer.add_path(m_path);

  // construct a linear span interpolator
  double parallelogram[6] = { left, top, left + width, top, left + width, top + height };
  agg::trans_affine mtx(0, 0, width, height, parallelogram);
  mtx.invert();
  span_interpolator interpolator(mtx);

  // a rgba span allocator
  span_allocator sa;

  GnPixelFormat imgPixelFormat = image.getPixelFormat();
  if (imgPixelFormat == kFormatRGB24) {
    // construct a rgb24 image accessor
    agg::pixfmt_rgb24 pixfmt(rbuf);
    image_accessor_rgb image_accessor(pixfmt);

    // a span generator
    span_gen_rgb span_gen(image_accessor, interpolator);

    // a span renderer
    agg::renderer_scanline_aa<renderer_base, span_allocator, span_gen_rgb> renderer(m_baseRen, sa, span_gen);

    // render the path
    agg::render_scanlines(m_rasterizer, m_packedSL, renderer);
  }
  else if (imgPixelFormat == kFormatRGBA32) {
    // construct a rgba32 image accessor
    agg::pixfmt_rgba32 pixfmt(rbuf);
    image_accessor_rgba image_accessor(pixfmt);

    // a span generator
    span_gen_rgba span_gen(image_accessor, interpolator);

    // a span renderer
    agg::renderer_scanline_aa<renderer_base, span_allocator, span_gen_rgba> renderer(m_baseRen, sa, span_gen);

    // render the path
    agg::render_scanlines(m_rasterizer, m_packedSL, renderer);
  }
}

void GnAggRenderer::drawText(const wchar_t *text, size_t len, int x, int y) {
  // TODO: configurate the font file's name
  // Notes: raster cache: gray8, vector cache: outline
  m_fontEngine.load_font("font.ttf", 0, agg::glyph_ren_agg_gray8);
  m_fontEngine.hinting(true);
  m_fontEngine.flip_y(true);

  // set font size
  m_fontEngine.width(m_textSize);
  m_fontEngine.height(m_textSize);

  // render the text
  const agg::glyph_cache* glyph  = NULL;
  for (size_t i = 0; i < len ; i++) {
    // gets the glyph of the charactor
    glyph = m_fontCache.glyph(text[i]);

    // render one of the charactors
    if (glyph) {
      m_fontCache.init_embedded_adaptors(glyph, x, y);
      if(glyph->data_type == agg::glyph_data_gray8) {
        m_aaRen.color(m_color);
        agg::render_scanlines(m_fontCache.gray8_adaptor(), m_fontCache.gray8_scanline(), m_aaRen);
      }

      // update the position
      x += (int)glyph->advance_x;
      y += (int)glyph->advance_y;
    }
  }
}
