package com.yao.yaoplayerandroid;

import android.content.Context;
import android.opengl.GLSurfaceView;
import android.util.AttributeSet;

import java.util.jar.Attributes;

public class GLESJNIView extends GLSurfaceView {
    public GLESJNIView(Context context){
        this(context, null);
    }

    public GLESJNIView(Context context, AttributeSet attrs){
        super(context, attrs);
        init();
    }

    public void init(){
        //设置opengl es版本
        setEGLContextClientVersion(3);
        setRenderer(new GLRender());
    }
}
