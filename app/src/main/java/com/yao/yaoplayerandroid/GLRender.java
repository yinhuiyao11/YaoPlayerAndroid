package com.yao.yaoplayerandroid;

import android.opengl.GLSurfaceView;

import com.yao.yaoplayerandroid.player.Player;

import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;

public class GLRender implements GLSurfaceView.Renderer {
    static {
        System.loadLibrary("YaoPlayerJni");
    }

    private Player player;

    public GLRender(){
    }

    public GLRender(Player _player){
        this.player = _player;
    }

    @Override
    public void onSurfaceCreated(GL10 gl, EGLConfig config) {

    }

    @Override
    public void onSurfaceChanged(GL10 gl, int width, int height) {

        player.gl_surfaceChanged(width, height);
    }

    @Override
    public void onDrawFrame(GL10 gl) {
        player.gl_drawFrame();
    }
}
