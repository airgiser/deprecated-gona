#include "GonaView.h"
#include <string.h>

#define USE_GL 1
#include "native/GnRendererFactory_win.h"
#include "GnImageLoader_png.h"

GonaView::GonaView() {
}

GonaView::~GonaView() {
  if (m_canvas)
  {
    delete m_canvas;
    m_canvas = 0;
  }
}

void GonaView::setupCanvas(HWND hwnd, unsigned int width, unsigned int height) {
#if USE_GL
  GnGLRendererFactory rendererFactory;
#else
  GnAggRendererFactory rendererFactory;
#endif
  GnRenderer *glRenderer = rendererFactory.CreateRenderer(hwnd, width, height);
  m_canvas = new GnCanvas(glRenderer);
}

void GonaView::onDraw(HDC hdc) {
  if (!m_canvas)
  {
    return;
  }

  // TODO: style file
  GnColor bkClr(120, 0, 0);
  m_canvas->clear(bkClr);

  GnPaint paint;
  paint.setColor(GnColor(229,176,69));
  paint.setLineWidth(8);
  paint.setLineCap(GnPaint::kRoundCap);
  paint.setLineJoin(GnPaint::kRoundJoin);
  paint.setTextSize(32);
  m_canvas->setPaint(paint);

  // Draw image
  GnPNGImageLoader pngLoader;
  GnImage *pImage = pngLoader.loadImage("gona.png");
  if (pImage != NULL)
  {
    m_canvas->drawImage(*pImage, 230, 0);
  }
  delete pImage;

  // Draw shapes.
  const int num = 3;
  GnPoint line1[num] = {GnPoint(10, 10), GnPoint(300, 200), GnPoint(500,330)};
  m_canvas->drawPolyLine(line1, num);
  GnPoint line2[num] = {GnPoint(200, 10), GnPoint(400, 180), GnPoint(500,330)};
  m_canvas->drawPolyLine(line2, num);
  GnPoint line3[num] = {GnPoint(400, 100), GnPoint(450, 200), GnPoint(500,330)};
  m_canvas->drawPolyLine(line3, num);

  GnPoint polygon[num] = {GnPoint(30, 300), GnPoint(330, 300), GnPoint(200,500)};
  m_canvas->drawPolygon(polygon, num);

  // draw text.
  const wchar_t *text = L"En & บบ";
  m_canvas->drawText(text, wcslen(text), 0, 200);
  m_canvas->swapBuffers();
}