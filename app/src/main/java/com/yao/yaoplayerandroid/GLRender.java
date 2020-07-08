package com.yao.yaoplayerandroid;

import android.opengl.GLSurfaceView;

import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;

public class GLRender implements GLSurfaceView.Renderer {
    static {
        System.loadLibrary("YaoPlayerJni");
    }

    public native void surfaceChanged(int w, int h);
    public native void drawFrame();

    @Override
    public void onSurfaceCreated(GL10 gl, EGLConfig config) {

    }

    @Override
    public void onSurfaceChanged(GL10 gl, int width, int height) {
        surfaceChanged(width, height);
    }

    @Override
    public void onDrawFrame(GL10 gl) {
        drawFrame();
    }
}
