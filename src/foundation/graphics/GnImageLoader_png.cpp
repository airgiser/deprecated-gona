/**
* Copyright (C) 2013-2014 The Gona Project
*
* Contact: airgiser@gmail.com
*/

#include "GnImageLoader_png.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "png.h"

GnPNGImageLoader::GnPNGImageLoader()
{
}

GnPNGImageLoader::~GnPNGImageLoader()
{
}

GnImage *GnPNGImageLoader::loadImage(const char *fileName)
{
  unsigned char *pixels = NULL;
  unsigned int width = 0;
  unsigned int height = 0;
  GnPixelFormat pixfmt = kFormatRGBA32;

  // open the image file
  FILE *fp = fopen(fileName, "rb");
  if (!fp) {
    return NULL;
  }

  // test whether it's a png
  unsigned char header[8]; // 8 is the maximum size that can be checked
  fread(header, 1, 8, fp);
  if (png_sig_cmp(header, 0, 8)) {
    fclose(fp);
    return NULL;
  }

  // initialize
  png_structp png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
  if (!png_ptr) {
    fclose(fp);
    return NULL;
  }

  png_infop info_ptr = png_create_info_struct(png_ptr);
  if (!info_ptr) {
    png_destroy_read_struct(&png_ptr, 0, 0);
    fclose(fp);
    return NULL;
  }

  if (setjmp(png_jmpbuf(png_ptr))) {
    png_destroy_read_struct(&png_ptr, &info_ptr, 0);
    fclose(fp);
    return NULL;
  }

  // read image data
  png_init_io(png_ptr, fp);
  png_set_sig_bytes(png_ptr, 8);
  png_read_png(png_ptr, info_ptr, PNG_TRANSFORM_EXPAND, 0);

  width = png_get_image_width(png_ptr, info_ptr);
  height = png_get_image_height(png_ptr, info_ptr);

  int color_type = png_get_color_type(png_ptr, info_ptr);
  if (color_type == PNG_COLOR_TYPE_RGB_ALPHA) {
    int bpp = 32;
    int stride = GnImage::calcStride(width, bpp);
    pixels = (unsigned char *)malloc(stride * height);
    pixfmt = kFormatRGBA32;

    int pos = 0;
    png_bytep* row_pointers = png_get_rows(png_ptr, info_ptr);
    for (unsigned int i = 0; i < height; i++) {
      memcpy(pixels + i*stride, row_pointers[i], stride);
    }
  }
  else if (color_type == PNG_COLOR_TYPE_RGB) {
    int bpp = 24;
    int stride = GnImage::calcStride(width, bpp);
    pixels = (unsigned char *)malloc(stride * height);
    pixfmt = kFormatRGB24;

    int pos = 0;
    png_bytep* row_pointers = png_get_rows(png_ptr, info_ptr);
    for (unsigned int i = 0; i < height; i++) {
      memcpy(pixels + i*stride, row_pointers[i], stride);
    }
  }
  else if (color_type == PNG_COLOR_TYPE_GRAY) {
    int bpp = 8;
    int stride = GnImage::calcStride(width, bpp);
    pixels = (unsigned char *)malloc(stride * height);
    pixfmt = kFormatGRAY8;

    int pos = 0;
    png_bytep* row_pointers = png_get_rows(png_ptr, info_ptr);
    for (unsigned int i = 0; i < height; i++) {
      memcpy(pixels + i*stride, row_pointers[i], stride);
    }
  }
  else {
    // currently, other formats are not supported
    png_destroy_read_struct(&png_ptr, &info_ptr, 0);
    fclose(fp);
    return NULL;
  }

  png_destroy_read_struct(&png_ptr, &info_ptr, 0);
  fclose(fp);
  return new GnImage(width, height, pixfmt, pixels);
}

void GnPNGImageLoader::saveImage(GnImage &image, const char *fileName)
{
  /* TODO: save the image to a png file */
}
