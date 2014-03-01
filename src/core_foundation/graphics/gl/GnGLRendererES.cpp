/**
 * Copyright (C) 2013-2014 The Gona Project
 *
 * Contact: airgiser@gmail.com
 */

#include "GnGLRendererES.h"

static const char gVertexShader[] =
    "attribute vec4 position;\n"
    "attribute vec2 texture_position;\n"
    "attribute vec4 color;\n"
    "varying vec2 v_texture_position;\n"
    "varying vec4 v_color;\n"
    "uniform mat4 mvp;\n"
    "void main() {\n"
    "  gl_Position = position;\n"
    "  v_texture_position = texture_position;\n"
    "  v_color = color;\n"
    "}\n";

static const char gFragmentShader[] =
    "varying lowp vec4 v_color;\n"
    "varying lowp vec2 v_texture_position;\n"
    "uniform sampler2D texture;\n"
    "uniform bool use_texture;\n"
    "uniform bool use_alpha_texture;\n"
    "void main() {\n"
    "  if (use_texture) {\n"
    "    gl_FragColor = texture2D(texture, v_texture_position);\n"
    "    if (use_alpha_texture) {\n"
    "      gl_FragColor = vec4(v_color[0], v_color[1], v_color[2], gl_FragColor[3]);\n"
    "    } \n"
    "  } else { \n"
    "    gl_FragColor = v_color;\n"
    "  }\n"
    "}\n";

// TODO: get the pathname
#ifdef GONA_FOR_ANDROID
static const char gFontName[] = "/sdcard/Gona/res/font.TTF";
#elif GONA_FOR_IOS
static const char gFontName[] = "Documents/res/font.TTF";
#endif

// TODO: move to the logger class
#ifdef GONA_FOR_ANDROID
#include <android/log.h>
#define  LOG_INFO(...)  __android_log_print(ANDROID_LOG_INFO,"Gona_GLES",__VA_ARGS__)
#define  LOG_ERROR(...)  __android_log_print(ANDROID_LOG_ERROR,"Gona_GLES",__VA_ARGS__)
#endif

GnGLRendererES::GnGLRendererES() : m_context(0), m_program(0), m_textSize(0) {
}

GnGLRendererES::GnGLRendererES(GnGLContext *context) : m_context(context), m_program(0), m_textSize(0) {
  m_program = new GnGLShaderProgram(gVertexShader, gFragmentShader);
  if (m_program && m_program->getProgram() != 0)
  {
    glUseProgram(m_program->getProgram());
    m_vtxCoordLocation = glGetAttribLocation(m_program->getProgram(), "position");
    m_colorLocation = glGetAttribLocation(m_program->getProgram(), "color");
    m_texCoordLocation = glGetAttribLocation(m_program->getProgram(), "texture_position");

    m_textureLocation = glGetUniformLocation(m_program->getProgram(), "texture");
    glUniform1i(m_textureLocation, 0);
    m_enableTextureLocation = glGetUniformLocation(m_program->getProgram(), "use_texture");
    glUniform1i(m_enableTextureLocation, 0);
    m_enableAlphaTexLocation = glGetUniformLocation(m_program->getProgram(), "use_alpha_texture");
    glUniform1i(m_enableAlphaTexLocation, 0);
  }
}

GnGLRendererES::~GnGLRendererES() {
  if (m_context) {
    delete m_context;
    m_context = 0;
  }

  if (m_program) {
    delete m_program;
    m_program = 0;
  }
}

void GnGLRendererES::clear(GnColor color) {
  glClearColor(color.red/255.0f, color.green/255.0f, color.blue/255.0f, color.alpha/255.0f);
  glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
}

void GnGLRendererES::swapBuffers() {
  if (m_context) {
    m_context->swapBuffers();
  }
}

void GnGLRendererES::setPaint(const GnPaint &paint) {
  if (!m_context || !m_program) {
    return;
  }

  // sets the width of rasterized lines
  glLineWidth(paint.getLineWidth());

  // sets the current color
  GnColor color = paint.getColor();
  m_color[0] = color.red/255.0f;
  m_color[1] = color.green/255.0f;
  m_color[2] = color.blue/255.0f;
  m_color[3] = color.alpha/255.0f;

  // sets the text size
  m_textSize = paint.getTextSize();
}

void GnGLRendererES::drawPolyLine(const GnPoint *points, int num) {
  if (!m_context || !m_program || m_program->getProgram() == 0) {
    return;
  }

  const GLfloat zlevel = 1; // TODO: Z-Level
  GL_Vertex *vertices = new GL_Vertex[num]; // TODO: performance
  for (int i = 0; i < num; i++) {
    /* TODO: use matrix */
    // vertex position
    vertices[i].position[0] = (points[i].m_x * 2.0 / m_context->getWidth()) - 1; 
    vertices[i].position[1] = 1 - (points[i].m_y * 2.0 / m_context->getHeight());
    vertices[i].position[2] = zlevel;

    // vertex color
    memcpy(vertices[i].color, m_color, sizeof(GLfloat) * 4);
  }

  glEnableVertexAttribArray(m_vtxCoordLocation);
  glEnableVertexAttribArray(m_colorLocation);
  glVertexAttribPointer(m_vtxCoordLocation, 3, GL_FLOAT, GL_FALSE, sizeof(GL_Vertex), vertices[0].position);
  glVertexAttribPointer(m_colorLocation, 4, GL_FLOAT, GL_FALSE, sizeof(GL_Vertex), vertices[0].color);
  glDrawArrays(GL_LINE_STRIP, 0, num);

  glDisableVertexAttribArray(m_vtxCoordLocation);
  glDisableVertexAttribArray(m_colorLocation);

  delete []vertices;
}

void GnGLRendererES::drawPolygon(const GnPoint *points, int num) {
  if (!m_context || !m_program || m_program->getProgram() == 0) {
    return;
  }

  const GLfloat zlevel = 1; // TODO: Z-Level
  GL_Vertex *vertices = new GL_Vertex[num]; // TODO: performance
  for (int i = 0; i < num; i++) {
    /* TODO: use matrix */
    // vertex position
    vertices[i].position[0] = (points[i].m_x * 2.0 / m_context->getWidth()) - 1; 
    vertices[i].position[1] = 1 - (points[i].m_y * 2.0 / m_context->getHeight());
    vertices[i].position[2] = zlevel;

    // vertex color
    memcpy(vertices[i].color, m_color, sizeof(GLfloat) * 4);
  }

  glEnableVertexAttribArray(m_vtxCoordLocation);
  glEnableVertexAttribArray(m_colorLocation);
  glVertexAttribPointer(m_vtxCoordLocation, 3, GL_FLOAT, GL_FALSE, sizeof(GL_Vertex), vertices[0].position);
  glVertexAttribPointer(m_colorLocation, 4, GL_FLOAT, GL_FALSE, sizeof(GL_Vertex), vertices[0].color);
  glDrawArrays(GL_TRIANGLES, 0, num);

  glDisableVertexAttribArray(m_vtxCoordLocation);
  glDisableVertexAttribArray(m_colorLocation);
}

void GnGLRendererES::drawImage(const GnImage &image, int left, int top) {
  unsigned int width = 0;
  unsigned int height = 0;
  GLuint texture = loadTexture(image, width, height);

  glEnable(GL_TEXTURE_2D);
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  glUniform1i(m_enableTextureLocation, 1);
  glUniform1i(m_enableAlphaTexLocation, 1);
  glEnableVertexAttribArray(m_vtxCoordLocation);
  glEnableVertexAttribArray(m_texCoordLocation);
  glEnableVertexAttribArray(m_colorLocation);

  // sets the texture coordinate
  GLfloat texCoords[] = {
    1, 0,
    1, 1,
    0, 0,
    0, 1
  };
  glVertexAttribPointer(m_texCoordLocation, 2, GL_FLOAT, GL_FALSE, 0, texCoords);

  // render an rectangle with the specified texture image
  GnPoint points[4] = {
    GnPoint(left+width, top),
    GnPoint(left+width, top+height),
    GnPoint(left, top),
    GnPoint(left, top+height)
  };
  GLfloat vtx[4*3];
  const GLfloat zlevel = 1; // TODO: Z-Level
  for (int i = 0; i < 4; i++)
  {
    /* TODO: use matrix */
    vtx[i*3] = (points[i].m_x * 2.0 / m_context->getWidth()) - 1; 
    vtx[i*3+1] = 1 - (points[i].m_y * 2.0 / m_context->getHeight());
    vtx[i*3+2] = zlevel;
  }
  glVertexAttribPointer(m_vtxCoordLocation, 3, GL_FLOAT, GL_FALSE, 0, vtx);

  GLfloat clr[] = {
    m_color[0], m_color[1], m_color[2], m_color[3],
    m_color[0], m_color[1], m_color[2], m_color[3],
    m_color[0], m_color[1], m_color[2], m_color[3],
    m_color[0], m_color[1], m_color[2], m_color[3]
  };
  glVertexAttribPointer(m_colorLocation, 4, GL_FLOAT, GL_FALSE, 0, clr);
  
  glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

  glDisableVertexAttribArray(m_vtxCoordLocation);
  glDisableVertexAttribArray(m_texCoordLocation);
  glDisableVertexAttribArray(m_colorLocation);
  glUniform1i(m_enableTextureLocation, 0);
  glUniform1i(m_enableAlphaTexLocation, 0);

  glDisable(GL_TEXTURE_2D);
  glDisable(GL_BLEND);

  // TODO: cache textures
  glDeleteTextures(1, &texture);
}

void GnGLRendererES::drawText(const wchar_t *text, size_t len, int x, int y) {
  // load font
  // TODO: cache font faces
  if (!m_fontMgr.loadFont(gFontName))
  {
    return;
  }
  m_fontMgr.setFontSize(m_textSize, m_textSize);

  // render each of charactor in the string
  for (int i = 0; i < len; i++) {
    GnImage *glyph = m_fontMgr.getGlyph(text[i]);
    if (glyph)
    {
      // TODO: positon of the text
      drawImage(*glyph, x, y-glyph->getHeight());
      x += glyph->getWidth();

      // TODO: cache glyph in font manager
      delete glyph;
    }
    else
    {
      // may be a space
      x += m_textSize/2;
    }
  }
}

GLuint GnGLRendererES::loadTexture(const GnImage &image, size_t &textureWidth, size_t &textureHeight) {
  unsigned int imgWidth = image.getWidth();
  unsigned int imgHeight = image.getHeight();
  GLint format = getGLPixelFormat(image.getPixelFormat());
  unsigned char *pixels = image.getRawData();

  // Notes: the width and height of texture image must be power of 2 in some version of OpenGL.
  // one of solution was like the The following codes;
  // another solution: pack textures into a large texture and 
  // access each individual texture region using a texture atlas.
  unsigned char *tempBuf = NULL;
  textureWidth = nextPower2(imgWidth);
  textureHeight = nextPower2(imgHeight);
  if (textureWidth != imgWidth || textureHeight != imgHeight) {
    // create pixels buffer with new size
    unsigned char bytesPerPixel = image.getBPP() / 8;
    size_t imgSize = textureWidth * textureHeight * bytesPerPixel;
    unsigned char *tempBuf = (unsigned char*)malloc(imgSize);
    memset(tempBuf, 0, imgSize);

    // copy the image pixels
    for (int line = 0; line < imgHeight; line++) {
      unsigned char *dst = tempBuf + line * textureWidth * bytesPerPixel;
      unsigned char *src = pixels + line * image.getStride();
      memcpy(dst, src, image.getStride());
    }
    pixels = tempBuf;
  }

  // create an OpenGL texture
  GLuint texture;
  glGenTextures(1, &texture);

  // bind the texture: all the future texture commands will modify this texture
  glBindTexture(GL_TEXTURE_2D, texture);

  // specify a two-dimensional texture image
  glTexImage2D(GL_TEXTURE_2D, 0, format, textureWidth, textureHeight, 0, format, GL_UNSIGNED_BYTE, pixels);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

  free(tempBuf);
  return texture;
}

GLint GnGLRendererES::getGLPixelFormat(GnPixelFormat pixfmt) {
  GLint internalFormat = 0;
  switch(pixfmt)
  {
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

int GnGLRendererES::nextPower2(int value)
{
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