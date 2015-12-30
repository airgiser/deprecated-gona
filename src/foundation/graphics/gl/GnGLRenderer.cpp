/**
 * Copyright (C) 2013-2014 The Gona Project
 *
 * Contact: airgiser@gmail.com
 */

#include "GnGLRenderer.h"
#include <math.h>
#include "../GnImageLoader_png.h"

#define VTX_BUF_INIT_SIZE 256
#define VTX_BUF_GROW_SIZE 128

static const char gFontName[] = "font.ttf";
static const char gCircleImg[] = "circle.png";

GnGLRenderer::GnGLRenderer() : 
m_context(NULL), 
m_textSize(0), 
m_vtxBufSize(VTX_BUF_INIT_SIZE), 
m_vtxBuf(NULL),
m_aaLineTexture(0) {
  m_vtxBuf = (GL_Vertex*)malloc(m_vtxBufSize * sizeof(GL_Vertex));
}

GnGLRenderer::GnGLRenderer(GnGLContext *context) : 
m_context(context), 
m_textSize(0), 
m_vtxBufSize(VTX_BUF_INIT_SIZE), 
m_vtxBuf(NULL),
m_aaLineTexture(0) {
  m_vtxBuf = (GL_Vertex*)malloc(m_vtxBufSize * sizeof(GL_Vertex));
}

GnGLRenderer::~GnGLRenderer() {
  if (m_context) {
    delete m_context;
    m_context = NULL;
  }

  if (m_vtxBuf) {
    free(m_vtxBuf);
    m_vtxBuf = NULL;
  }

  if (m_aaLineTexture) {
    glDeleteTextures(1, &m_aaLineTexture);
  }
}

void GnGLRenderer::inflateVtxBuf(unsigned int newSize) {
  if (newSize <= m_vtxBufSize) {
    return;
  }

  unsigned int growSize = newSize - m_vtxBufSize;
  growSize = VTX_BUF_GROW_SIZE * (growSize / VTX_BUF_GROW_SIZE + 1);
  m_vtxBufSize += growSize;
  m_vtxBuf = (GL_Vertex*)realloc(m_vtxBuf, m_vtxBufSize);
}

void GnGLRenderer::clear(GnColor color) {
  glClearColor(color.red/255.0f, color.green/255.0f, color.blue/255.0f, color.alpha/255.0f);
  glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
}

void GnGLRenderer::swapBuffers() {
  if (m_context) {
    m_context->swapBuffers();
  }
}

void GnGLRenderer::setPaint(const GnPaint &paint) {
  m_paint = paint;

  // sets the width of rasterized lines
  glLineWidth(paint.getLineWidth());

  // sets point size
  glPointSize(paint.getLineWidth());

  // sets the current color
  GnColor clr = paint.getColor();
  glColor4f(clr.red/255.0f, clr.green/255.0f, clr.blue/255.0f, clr.alpha/255.0f);

  // sets the text's size
  m_textSize = paint.getTextSize();
}

void GnGLRenderer::genAALineTexture() {
  // load a circle image
  GnPNGImageLoader imageLoader;
  GnImage *pCircleImg = imageLoader.loadImage(gCircleImg);
  if (pCircleImg == NULL) {
    return;
  }

  // generate aa texture
  size_t texWidth = 0;
  size_t texHeight = 0;
  m_aaLineTexture = loadTexture(*pCircleImg, texWidth, texHeight);
  delete pCircleImg;
}

void GnGLRenderer::drawPolyLine(const GnPoint *points, int num) {
  if (m_context == NULL) {
    return;
  }

#if 1
  if (num > m_vtxBufSize) {
    inflateVtxBuf(num);
  }

  // sets the vertices
  GL_Vertex *vertices = m_vtxBuf;
  for (int i = 0; i < num; i++) {
    vertices[i].position[0] = (float)points[i].m_x;
    vertices[i].position[1] = (float)points[i].m_y;
  }
  glVertexPointer(2, GL_FLOAT, sizeof(GL_Vertex), vertices[0].position);

  // draw line strip
  glEnable(GL_LINE_SMOOTH);
  glEnable(GL_POINT_SMOOTH);
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glEnableClientState(GL_VERTEX_ARRAY);
  glDrawArrays(GL_LINE_STRIP, 0, num); // TODO: performance
  glDrawArrays(GL_POINTS, 0, num);
  glDisableClientState(GL_VERTEX_ARRAY);
  glDisable(GL_BLEND);
  glDisable(GL_LINE_SMOOTH);
  glDisable(GL_POINT_SMOOTH);
#else 
  if (m_aaLineTexture == 0) {
    genAALineTexture();
  } else {
    glBindTexture(GL_TEXTURE_2D, m_aaLineTexture);
  }

  int vtxSize = (num - 1) * 10;
  if (vtxSize > m_vtxBufSize) {
    inflateVtxBuf(num);
  }

  // extrude line to polygon
  GL_Vertex *vertices = m_vtxBuf;
  for (int i = 0; i < num - 1; i++) {
    float sx = (float)points[i].m_x;
    float sy = (float)points[i].m_y;
    float ex = (float)points[i+1].m_x;
    float ey = (float)points[i+1].m_y;

    float dx = sx - ex;
    float dy = sy - ey;
    float factor = dx * dx + dy * dy;
    if (factor == 0) {
      dx = 0;
      dy = 1;
    } else {
      // normalize
      factor = 1 / sqrt(factor);
      dx *= factor;
      dy *= factor;
    }

    float width = m_paint.getLineWidth() / 2;
    dx *= width;
    dy *= width;
    float ddx = dy;
    float ddy = -dx;

    vertices[i*10 + 0].position[0] = ex - ddx - dx;  vertices[i*10 + 0].position[1] = ey - ddy - dy;
    vertices[i*10 + 0].texCoord[0] = 0;              vertices[i*10 + 0].texCoord[1] = 0;
    vertices[i*10 + 1].position[0] = ex - ddx - dx;  vertices[i*10 + 1].position[1] = ey - ddy - dy;
    vertices[i*10 + 1].texCoord[0] = 0;              vertices[i*10 + 1].texCoord[1] = 0;
    vertices[i*10 + 2].position[0] = ex + ddx - dx;  vertices[i*10 + 2].position[1] = ey + ddy - dy;
    vertices[i*10 + 2].texCoord[0] = 0;              vertices[i*10 + 2].texCoord[1] = 1;

    vertices[i*10 + 3].position[0] = ex - ddx;       vertices[i*10 + 3].position[1] = ey - ddy;
    vertices[i*10 + 3].texCoord[0] = 0.5;            vertices[i*10 + 3].texCoord[1] = 0;
    vertices[i*10 + 4].position[0] = ex + ddx;       vertices[i*10 + 4].position[1] = ey + ddy;
    vertices[i*10 + 4].texCoord[0] = 0.5;            vertices[i*10 + 4].texCoord[1] = 1;
    vertices[i*10 + 5].position[0] = sx - ddx;       vertices[i*10 + 5].position[1] = sy - ddy;
    vertices[i*10 + 5].texCoord[0] = 0.5;            vertices[i*10 + 5].texCoord[1] = 0;
    vertices[i*10 + 6].position[0] = sx + ddx;       vertices[i*10 + 6].position[1] = sy + ddy;
    vertices[i*10 + 6].texCoord[0] = 0.5;            vertices[i*10 + 6].texCoord[1] = 1;

    vertices[i*10 + 7].position[0] = sx - ddx + dx;  vertices[i*10 + 7].position[1] = sy - ddy + dy;
    vertices[i*10 + 7].texCoord[0] = 1;              vertices[i*10 + 7].texCoord[1] = 0;
    vertices[i*10 + 8].position[0] = sx + ddx + dx;  vertices[i*10 + 8].position[1] = sy + ddy + dy;
    vertices[i*10 + 8].texCoord[0] = 1;              vertices[i*10 + 8].texCoord[1] = 1;
    vertices[i*10 + 9].position[0] = sx + ddx + dx;  vertices[i*10 + 9].position[1] = sy + ddy + dy;
    vertices[i*10 + 9].texCoord[0] = 1;              vertices[i*10 + 9].texCoord[1] = 1;
  }
  glVertexPointer(2, GL_FLOAT, sizeof(GL_Vertex), vertices[0].position);
  glTexCoordPointer(2, GL_FLOAT, sizeof(GL_Vertex), vertices[0].texCoord);

  glEnableClientState(GL_TEXTURE_COORD_ARRAY);
  glEnableClientState(GL_VERTEX_ARRAY);
  glEnable(GL_TEXTURE_2D);
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glDrawArrays(GL_TRIANGLE_STRIP, 0, vtxSize);
  glDisableClientState(GL_TEXTURE_COORD_ARRAY);
  glDisableClientState(GL_VERTEX_ARRAY);
  glDisable(GL_TEXTURE_2D);
  glDisable(GL_BLEND);
#endif
}

void GnGLRenderer::drawPolygon(const GnPoint *points, int num) {
  if (m_context == NULL) {
    return;
  }

  glEnableClientState(GL_VERTEX_ARRAY);

  if (num > m_vtxBufSize) {
    inflateVtxBuf(num);
  }
  GL_Vertex *vertices = m_vtxBuf;
  for (int i = 0; i < num; i++) {
    vertices[i].position[0] = (float)points[i].m_x;
    vertices[i].position[1] = (float)points[i].m_y;
  }
  glVertexPointer(2, GL_FLOAT, sizeof(GL_Vertex), vertices[0].position);
  glDrawArrays(GL_TRIANGLES, 0, num);

  glDisableClientState(GL_VERTEX_ARRAY);
}

void GnGLRenderer::drawImage(const GnImage &image, int left, int top) {
  size_t width = 0;
  size_t height = 0;
  GLuint texture = loadTexture(image, width, height);

  glEnableClientState(GL_TEXTURE_COORD_ARRAY);
  glEnableClientState(GL_VERTEX_ARRAY);
  glEnable(GL_TEXTURE_2D);
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  // sets the texture coordinate
  GLfloat x[] = {
    1, 0,
    1, 1,
    0, 0,
    0, 1
  };
  glTexCoordPointer(2, GL_FLOAT, 0, x);

  // render an rectangle with the specified texture image
  GLfloat vtx[] = {
    GLfloat(left + width), GLfloat(top),
    GLfloat(left + width), GLfloat(top + height),
    GLfloat(left), GLfloat(top),
    GLfloat(left), GLfloat(top + height)
  };
  glVertexPointer(2, GL_FLOAT, 0, vtx);
  glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

  glDisableClientState(GL_TEXTURE_COORD_ARRAY);
  glDisableClientState(GL_VERTEX_ARRAY);
  glDisable(GL_TEXTURE_2D);
  glDisable(GL_BLEND);

  // TODO: cache textures
  glDeleteTextures(1, &texture);
}

void GnGLRenderer::drawText(const wchar_t *text, size_t len, int x, int y) {
  // load font
  // TODO: cache font faces
  m_fontMgr.loadFont(gFontName);
  m_fontMgr.setFontSize(m_textSize, m_textSize);

  // render each of charactor in the string
  for (size_t i = 0; i < len; i++) {
    GnImage *glyph = m_fontMgr.getGlyph(text[i]);
    if (glyph) {
      // TODO: positon of the text
      drawImage(*glyph, x, y-glyph->getHeight());
      x += glyph->getWidth();

      // TODO: cache glyph in font manager
      delete glyph;
    }
    else {
      // may be a space
      x += m_textSize/2;
    }
  }
}

GLuint GnGLRenderer::loadTexture(const GnImage &image, size_t &textureWidth, size_t &textureHeight) {
  unsigned int imgWidth = image.getWidth();
  unsigned int imgHeight = image.getHeight();
  GLint format = getGLPixelFormat(image.getPixelFormat());
  unsigned char *pixels = image.getRawData();

  // Notes: the width and height of texture image must be power of 2 in some version of OpenGL.
  // one of solution was like the downward commented codes;
  // another solution: pack textures into a large texture and 
  // access each individual texture region using a texture atlas.
  unsigned char *tempBuf = NULL;
  textureWidth = /*nextPower2*/(imgWidth);
  textureHeight = /*nextPower2*/(imgHeight);
  //if (textureWidth != imgWidth || textureHeight != imgHeight) {
  //  // create pixels buffer with new size
  //  unsigned char bytesPerPixel = image.getBPP() / 8;
  //  size_t imgSize = textureWidth * textureHeight * bytesPerPixel;
  //  unsigned char *tempBuf = (unsigned char*)malloc(imgSize);
  //  memset(tempBuf, 0, imgSize);

  //  // copy the image pixels
  //  for (int line = 0; line < imgHeight; line++) {
  //    unsigned char *dst = tempBuf + line * textureWidth * bytesPerPixel;
  //    unsigned char *src = pixels + line * imgWidth * bytesPerPixel;
  //    memcpy(dst, src, imgWidth * bytesPerPixel);
  //  }
  //  pixels = tempBuf;
  //}

  // create an OpenGL texture
  GLuint texture;
  glGenTextures(1, &texture);

  // bind the texture: all the future texture commands will modify this texture
  glBindTexture(GL_TEXTURE_2D, texture);

  // specify a two-dimensional texture image
  glTexImage2D(GL_TEXTURE_2D, 0, format, (GLsizei)textureWidth, (GLsizei)textureHeight, 0, format, GL_UNSIGNED_BYTE, pixels);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

  free(tempBuf);
  return texture;
}

GLint GnGLRenderer::getGLPixelFormat(GnPixelFormat pixfmt) {
  GLint internalFormat = 0;
  switch(pixfmt) {
  case kFormatRGBA32:
    internalFormat = GL_RGBA;
    break;
  case kFormatRGB24:
    internalFormat = GL_RGB;
    break;
  case kFormatGRAY8:
    internalFormat = GL_ALPHA;
    break;
  default:
    break;
  }

  return internalFormat;
}

int GnGLRenderer::nextPower2(int value) {
  int n = value;

  // n is already power of two
  if (n > 0 && (n & (n-1)) == 0) {
    return n;
  }

  // gets the smallest power of two that is greater than the value
  --n;
  n |= n >> 1;  // now the higher 2 bits are 1(001xxxxx... to 0011xxxx...)
  n |= n >> 2;  // now the higher 4 bits are 1(0011xxxx... to 001111xx...)
  n |= n >> 4;  // now the higher 8 bits are 1
  n |= n >> 8;  // now the higher 16 bits are 1
  n |= n >> 16; // now the higher 32 bits are 1
  n++;

  // 
  if (n < 16) {
    n = 16;
  }

  return n;
}
