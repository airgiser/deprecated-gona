/**
 * Copyright (C) 2013-2014 The Gona Project
 *
 * Contact: airgiser@gmail.com
 */

#ifndef GONA_GRAPHICS_GL_FONT_MANAGER_H
#define GONA_GRAPHICS_GL_FONT_MANAGER_H

// the freetype headers
#include "ft2build.h"
#include "freetype/freetype.h"
#include "freetype/ftglyph.h"
#include "freetype/ftstroke.h"
#include "freetype/ftcache.h"

#include "GnImage.h"

/** \class GnGLFontManager
 *
 *  A Font engine which contains a raster glyph cache, 
 *  internally used the freetype library.
 */
class GnGLFontManager
{
public:
  GnGLFontManager();

  ~GnGLFontManager();

  /**
   * Load a specified font.
   *
   * @param fontName a full path to the font file
   */
  bool loadFont(const char *fontName);

  /**
   * Set size of the text to be rendered.
   *
   * @param width the width in pixels
   * @param height the height in pixels
   */
  void setFontSize(unsigned int width, unsigned int height);

  /**
   * Gets a raster glyph image
   *
   * @param ch the specified charactor
   */
  GnImage* getGlyph(wchar_t ch);

protected:
  /* Gets a raster glyph image */
  static GnImage* getGlyph(FT_Face face, wchar_t ch);

private:
  bool        m_initialized;
  FT_Library  m_fontLib;

  // TODO: cache font faces(currently support one face only)
  FT_Face     m_face;
};

#endif // GONA_GRAPHICS_GL_FONT_MANAGER_H