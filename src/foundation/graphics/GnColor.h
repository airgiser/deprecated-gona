/**
 * Copyright (C) 2013-2014 The Gona Project
 *
 * Contact: airgiser@gmail.com
 */

#ifndef GONA_GRAPHICS_COLOR_H
#define GONA_GRAPHICS_COLOR_H

/// Transparent alpha value
#define GN_ALPHA_TRANSPARENT 0x00

/// Opaque alpha value
#define GN_ALPHA_OPAQUE 0xFF

/** \struct GnColor
 *
 *  32-bit RGBA color value.
 */
struct GnColor {

  GnColor() : red(0x00), green(0x00), blue(0x00), alpha(0x00) {}

  GnColor(unsigned char r, unsigned char g, unsigned char b, unsigned char a = 0xFF)
    : red(r), green(g), blue(b), alpha(a) {}

  unsigned char red;
  unsigned char green;
  unsigned char blue;
  unsigned char alpha;
};

#define GN_COLOR_RED     GnColor(0xFF, 0x00, 0x00, 0xFF)
#define GN_COLOR_GREEN   GnColor(0x00, 0xFF, 0x00, 0xFF)
#define GN_COLOR_BLUE    GnColor(0x00, 0x00, 0xFF, 0xFF)
#define GN_COLOR_YELLOW  GnColor(0xFF, 0xFF, 0x00, 0xFF)
#define GN_COLOR_CYAN    GnColor(0x00, 0xFF, 0xFF, 0xFF)
#define GN_COLOR_MAGENTA GnColor(0xFF, 0x00, 0xFF, 0xFF)

#define GN_COLOR_BLACK      GnColor(0x00, 0x00, 0x00, 0xFF)
#define GN_COLOR_DARK_GRAY  GnColor(0x44, 0x44, 0x44, 0xFF)
#define GN_COLOR_GRAY       GnColor(0x88, 0x88, 0x88, 0xFF)
#define GN_COLOR_LIGHT_GRAY GnColor(0xCC, 0xCC, 0xCC, 0xFF)
#define GN_COLOR_WHITE      GnColor(0xFF, 0xFF, 0xFF, 0xFF)

#endif // GONA_GRAPHICS_COLOR_H