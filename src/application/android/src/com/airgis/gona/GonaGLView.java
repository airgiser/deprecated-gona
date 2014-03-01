/**
 * Copyright 2013 The Gona project.
 */
package com.airgis.gona;

import javax.microedition.khronos.egl.EGL10;
import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.egl.EGLContext;
import javax.microedition.khronos.egl.EGLDisplay;
import javax.microedition.khronos.opengles.GL10;

import android.content.Context;
import android.graphics.PixelFormat;
import android.opengl.GLSurfaceView;

/**
 * A simple GLSurfaceView sub-class
 */
public class GonaGLView extends GLSurfaceView {
	public GonaGLView(Context context) {
		super(context);
		init(false, 0, 0);
	}
	
	public GonaGLView(Context context, boolean translucent, int depth, int stencil) {
		super(context);
		init(translucent, depth, stencil);
	}

	private void init(boolean translucent, int depth, int stencil) {
		/* Set the surface's format */
		if (translucent) {
            this.getHolder().setFormat(PixelFormat.TRANSLUCENT);
        }
        
        /* Setup the context factory for 2.0 rendering. */
        setEGLContextFactory(new ContextFactory());
        
        /* Choose an EGLConfig that matches the format of the current surface exactly. */
        if (translucent) {
        	setEGLConfigChooser(new ConfigChooser(8, 8, 8, 8, depth, stencil));
        } else {
        	setEGLConfigChooser(new ConfigChooser(5, 6, 5, 0, depth, stencil));
        }
        
        /* Set the renderer */
        setRenderer(new Renderer());
	}
	
	/**
	 * Implements a context factory to create/destroy EGLContext
	 */
    private static class ContextFactory implements GLSurfaceView.EGLContextFactory {
        private static int EGL_CONTEXT_CLIENT_VERSION = 0x3098;
        public EGLContext createContext(EGL10 egl, EGLDisplay display, EGLConfig eglConfig) {
            int[] attrs = {EGL_CONTEXT_CLIENT_VERSION, 2, EGL10.EGL_NONE };
            EGLContext context = egl.eglCreateContext(display, eglConfig, EGL10.EGL_NO_CONTEXT, attrs);
            return context;
        }

        public void destroyContext(EGL10 egl, EGLDisplay display, EGLContext context) {
            egl.eglDestroyContext(display, context);
        }
    }
    
    /**
     * Implements an EGLConfigChooser
     */
    private static class ConfigChooser implements GLSurfaceView.EGLConfigChooser {
    	
        public ConfigChooser(int r, int g, int b, int a, int depth, int stencil) {
            mRedSize = r;
            mGreenSize = g;
            mBlueSize = b;
            mAlphaSize = a;
            mDepthSize = depth;
            mStencilSize = stencil;
        }
        
		public EGLConfig chooseConfig(EGL10 egl, EGLDisplay display) {
			
			/* Try to find a normal multisample configuration first */
			int EGL_OPENGL_ES2_BIT = 4;
			int[] configNum = new int[1];
			int[] configAttribsES2 = {
					EGL10.EGL_RED_SIZE, 4,
					EGL10.EGL_GREEN_SIZE, 4,
					EGL10.EGL_BLUE_SIZE, 4,
					EGL10.EGL_RENDERABLE_TYPE, EGL_OPENGL_ES2_BIT,
					EGL10.EGL_SAMPLE_BUFFERS, 1,
					EGL10.EGL_SAMPLES, 2,
					EGL10.EGL_NONE
			};
			egl.eglChooseConfig(display, configAttribsES2, null, 0, configNum);
			
			/* No normal multisampling configuration was found. */
			if (configNum[0] <= 0) {
				/* for the nVidia Tegra2 */
				final int EGL_COVERAGE_BUFFERS_NV = 0x30E0;
				final int EGL_COVERAGE_SAMPLES_NV = 0x30E1;
				configAttribsES2 = new int[] {
						EGL10.EGL_RED_SIZE, 4,
						EGL10.EGL_GREEN_SIZE, 4,
						EGL10.EGL_BLUE_SIZE, 4,
						EGL10.EGL_RENDERABLE_TYPE, EGL_OPENGL_ES2_BIT,
						EGL_COVERAGE_BUFFERS_NV, 1,
						EGL_COVERAGE_SAMPLES_NV, 2,
						EGL10.EGL_NONE
				};
				egl.eglChooseConfig(display, configAttribsES2, null, 0, configNum);
				
				if (configNum[0] <= 0) {
					/* without multisampling */
					configAttribsES2 = new int[] {
							EGL10.EGL_RED_SIZE, 4,
							EGL10.EGL_GREEN_SIZE, 4,
							EGL10.EGL_BLUE_SIZE, 4,
							EGL10.EGL_RENDERABLE_TYPE, EGL_OPENGL_ES2_BIT,
							EGL10.EGL_NONE
					};
					egl.eglChooseConfig(display, configAttribsES2, null, 0, configNum);
					
					if (configNum[0] <= 0) {
						return null;
					}
				}
			}
			
			/* Get the array of matching EGL configurations */
			EGLConfig[] configs = new EGLConfig[configNum[0]];
			egl.eglChooseConfig(display, configAttribsES2, configs, configNum[0], configNum);
			
			return chooseConfig(egl, display, configs);
		}
		
		public EGLConfig chooseConfig(EGL10 egl, EGLDisplay display, EGLConfig[] configs) {
			for (EGLConfig config : configs) {
				int[] value = new int[1];
				
				int depth = 0;
				if (egl.eglGetConfigAttrib(display, config, EGL10.EGL_DEPTH_SIZE, value)) {
					depth = value[0];
				}
				int stencil = 0;
				if (egl.eglGetConfigAttrib(display, config, EGL10.EGL_STENCIL_SIZE, value)) {
					stencil = value[0];
				}
				
				/* Check depth and stencil */
				if (depth < mDepthSize || stencil < mStencilSize) {
					continue;
				}
				
				int redSize = 0;
				if (egl.eglGetConfigAttrib(display, config, EGL10.EGL_RED_SIZE, value)) {
					redSize = value[0];
				}
				int greenSize = 0;
				if (egl.eglGetConfigAttrib(display, config, EGL10.EGL_GREEN_SIZE, value)) {
					greenSize = value[0];
				}
				int blueSize = 0;
				if (egl.eglGetConfigAttrib(display, config, EGL10.EGL_BLUE_SIZE, value)) {
					blueSize = value[0];
				}
				int alphaSize = 0;
				if (egl.eglGetConfigAttrib(display, config, EGL10.EGL_ALPHA_SIZE, value)) {
					alphaSize = value[0];
				}
				
				/* Check color format */
				if (redSize == mRedSize && greenSize == mGreenSize && blueSize == mBlueSize && alphaSize == mAlphaSize) {
					return config;
				}
			}
			return null;
		}
		
        protected int mRedSize;
        protected int mGreenSize;
        protected int mBlueSize;
        protected int mAlphaSize;
        protected int mDepthSize;
        protected int mStencilSize;
    }
    
    /**
     * Implements a renderer for frame rendering
     */
    private static class Renderer implements GLSurfaceView.Renderer {
        public void onDrawFrame(GL10 gl) {
        	GonaJNILib.drawFrame();
        }

        public void onSurfaceChanged(GL10 gl, int width, int height) {
        	GonaJNILib.init(width, height);
        }

        public void onSurfaceCreated(GL10 gl, EGLConfig config) {
        }
    }
}
