/**
 * Copyright (C) 2013-2014 The Gona Project
 *
 * Contact: airgiser@gmail.com
 */

#include "GnGLFontManager.h"

GnGLFontManager::GnGLFontManager() : m_face(NULL) {
  if (FT_Init_FreeType(&m_fontLib) == FT_Err_Ok) {
    m_initialized = true;
  }
}

GnGLFontManager::~GnGLFontManager() {
  if (m_initialized) {
    // TODO: cache font faces(currently support one face only)
    if (m_face != NULL) {
      FT_Done_Face(m_face);
    }
    FT_Done_FreeType(m_fontLib);
  }
}

bool GnGLFontManager::loadFont(const char *fontName) {
  if (!m_initialized) {
    return false;
  }

  // TODO: cache font faces(currently support one face only)
  if (m_face != NULL) {
    FT_Done_Face(m_face);
  }

  if (FT_New_Face(m_fontLib, fontName, 0, &m_face) != FT_Err_Ok) {
    return false;
  }

  return true;
}

void GnGLFontManager::setFontSize(unsigned int width, unsigned int height) {
  if (!m_initialized || m_face == NULL) {
    return;
  }

  // TODO: cache font faces(currently support one face only)
  FT_Set_Pixel_Sizes(m_face, width, height);
}

GnImage *GnGLFontManager::getGlyph(wchar_t ch) {
  // TODO: cache font faces(currently support one face only)
  if (!m_initialized || m_face == NULL) {
    return NULL;
  }
  
  // TODO: cache glyph image
  return getGlyph(m_face, ch);
}

GnImage *GnGLFontManager::getGlyph(FT_Face face, wchar_t ch)
{
  int error = FT_Err_Ok;

  // load glyph image
  error = FT_Load_Glyph(face, FT_Get_Char_Index(face, ch), FT_LOAD_DEFAULT);
  if (error != FT_Err_Ok) {
    return NULL;
  }

  // convert to an anti-aliased bitmap
  error = FT_Render_Glyph(face->glyph, FT_RENDER_MODE_NORMAL);
  if (error != FT_Err_Ok) {
    return NULL;
  }

  // extract the pixel data from the bitmap glyph object.
  FT_Bitmap *bitmap = &(face->glyph->bitmap);
  int width = bitmap->width;
  int height = bitmap->rows;
  if (width > 0 && height > 0) {
    int stride = ((width + 3) >> 2) << 2; // not needed when we using a rgba image
    unsigned char *buffer = (unsigned char *)malloc(stride * height);
    memset(buffer, 0, stride * height);

    // copy the pixel data
    for (int row = 0; row < height; row++) {
      memcpy(buffer + row * stride, bitmap->buffer + row * width, width);
    }

    return new GnImage(width, height, kFormatGRAY8, buffer);
  }

  return NULL;
}