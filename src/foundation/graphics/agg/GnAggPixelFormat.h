/**
 * Copyright (C) 2013-2014 The Gona Project
 *
 * Contact: airgiser@gmail.com
 */

#ifndef GONA_GRAPHICS_AGG_PIXEL_FORMAT_H
#define GONA_GRAPHICS_AGG_PIXEL_FORMAT_H

#include "agg_pixfmt_rgba.h"
#include "agg_pixfmt_rgb.h"
#include "agg_pixfmt_rgb_packed.h"
#include "agg_pixfmt_gray.h"

/* TODO: platform dependent */
#if 0
#define SYS_BPP 24
typedef agg::pixfmt_bgr24 agg_pixfmt;
#else
#define SYS_BPP 32
typedef agg::pixfmt_bgra32 agg_pixfmt;
#endif

#endif // GONA_GRAPHICS_AGG_PIXEL_FORMAT_H