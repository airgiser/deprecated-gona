#include <jni.h>

#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>
#include <wchar.h>

#include "native/GnNativeGLContext_android.h"
#include "GnGLRendererES.h"

extern "C" {
  JNIEXPORT void JNICALL Java_com_airgis_gona_GonaJNILib_init(JNIEnv * env, jobject obj,  jint width, jint height);
  JNIEXPORT void JNICALL Java_com_airgis_gona_GonaJNILib_drawFrame(JNIEnv *env, jobject obj);
}

GnRenderer *g_renderer = NULL;
bool initContext(int width, int height)
{
	GnGLContext *context = new GnNativeGLContext(width, height);
	g_renderer = new GnGLRendererES(context);
	return true;
}

void renderFrame()
{
	if (g_renderer) {
		static float grey = 0.0;
		grey += 0.002f;
		if (grey > 0.3f) {
			grey = 0.0f;
		}
		GnColor bkColor(grey*255, grey*255, grey*255, grey*255);
		g_renderer->clear(bkColor);

		GnPaint paint;
		paint.setColor(GnColor(229,176,69));
		paint.setLineWidth(15);
		paint.setTextSize(32);
		g_renderer->setPaint(paint);

		// Draw shapes.
		const int num = 3;
		GnPoint line1[num] = {GnPoint(10, 10), GnPoint(300, 200), GnPoint(500,330)};
		g_renderer->drawPolyLine(line1, num);
		GnPoint line2[num] = {GnPoint(200, 10), GnPoint(400, 180), GnPoint(500,330)};
		g_renderer->drawPolyLine(line2, num);
		GnPoint line3[num] = {GnPoint(400, 100), GnPoint(450, 200), GnPoint(500,330)};
		g_renderer->drawPolyLine(line3, num);

		GnPoint polygon[num] = {GnPoint(30, 300), GnPoint(330, 300), GnPoint(200,500)};
		g_renderer->drawPolygon(polygon, num);

		// draw text.
		const wchar_t *text = L"En & 汉";
		g_renderer->drawText(text, wcslen(text), 0, 200);
	}
}

JNIEXPORT void JNICALL Java_com_airgis_gona_GonaJNILib_init(JNIEnv * env, jobject obj,  jint width, jint height)
{
	initContext(width, height);
}

JNIEXPORT void JNICALL Java_com_airgis_gona_GonaJNILib_drawFrame(JNIEnv *env, jobject obj)
{
	renderFrame();
}
