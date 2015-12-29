/**
 * Copyright (C) 2013-2014 The Gona Project
 *
 * Contact: airgiser@gmail.com
 */

#ifndef GONA_GRAPHICS_GL_SHADER_PROGRAM_H
#define GONA_GRAPHICS_GL_SHADER_PROGRAM_H

#include <stdlib.h>

#if GONA_FOR_IOS
#include <OpenGLES/ES2/gl.h>
#include <OpenGLES/ES2/glext.h>
#elif GONA_FOR_ANDROID
#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>
#endif

/** \class GnGLShaderProgram
 *
 *  An OpenGL Shader program.
 */
class GnGLShaderProgram {
public:
  GnGLShaderProgram(const char* pVertexSource, const char *pFragmentSource) : m_program(0) {
    m_vertexShader = loadShader(GL_VERTEX_SHADER, pVertexSource);
    if (!m_vertexShader) {
      return;
    }

    m_pixelShader = loadShader(GL_FRAGMENT_SHADER, pFragmentSource);
    if (!m_pixelShader) {
      return;
    }

    m_program = createProgram(m_vertexShader, m_pixelShader);
    if (!m_program) {
      return;
    }
  }

  virtual ~GnGLShaderProgram() {
  }

  GLuint getProgram() {
    return m_program;
  }

protected:
  GLuint loadShader(GLenum shaderType, const char* pSource) {
    GLuint shader = glCreateShader(shaderType);
    if (shader) {
      glShaderSource(shader, 1, &pSource, NULL);
      glCompileShader(shader);

      // Exception.
      GLint compiled = 0;
      glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);
      if (!compiled) {
        GLint infoLen = 0;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLen);
        if (infoLen) {
          char* buf = (char*) malloc(infoLen);
          if (buf) {
            // TODO: output log
            glGetShaderInfoLog(shader, infoLen, NULL, buf);
            free(buf);
          }
          glDeleteShader(shader);
          shader = 0;
        }
      }
    }

    return shader;
  }

  GLuint createProgram(GLuint vertexShader, GLuint pixelShader) {
    GLuint program = glCreateProgram();
    if (program) {
      glAttachShader(program, vertexShader);
      glAttachShader(program, pixelShader);
      glLinkProgram(program);

      // Exception.
      GLint linkStatus = GL_FALSE;
      glGetProgramiv(program, GL_LINK_STATUS, &linkStatus);
      if (linkStatus != GL_TRUE) {
        GLint bufLength = 0;
        glGetProgramiv(program, GL_INFO_LOG_LENGTH, &bufLength);
        if (bufLength) {
          char* buf = (char*) malloc(bufLength);
          if (buf) {
            // TODO: output log
            glGetProgramInfoLog(program, bufLength, NULL, buf);
            free(buf);
          }
        }
        glDeleteProgram(program);
        program = 0;
      }
    }

    return program;
  }
private:
  GLuint m_program;
  GLuint m_vertexShader;
  GLuint m_pixelShader;
};

#endif // GONA_GRAPHICS_GL_SHADER_PROGRAM_H