/**
 * Copyright 2013 The Gona project.
 */
package com.airgis.gona;

public class GonaJNILib {

	static {
		System.loadLibrary("Gona");
	}
	
	public static native void init(int width, int height);
	public static native void drawFrame();
}
