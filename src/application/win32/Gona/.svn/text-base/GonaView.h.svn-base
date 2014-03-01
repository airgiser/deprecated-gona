/**
 * Copyright 2013 The Gona Project
 */

#ifndef GONA_APP_WIN_VIEW_H
#define GONA_APP_WIN_VIEW_H

#include <windows.h>
#include <stdio.h>
#include "GnCanvas.h"

/** \class GonaView
 * the main view of the application.
 */
class GonaView {
public:
  GonaView();

  ~GonaView();
public:
  void setupCanvas(HWND hwnd, unsigned int width, unsigned int height);

  void onDraw(HDC hdc);

private:
  GnCanvas *m_canvas;
};
#endif // GONA_APP_WIN_VIEW_H