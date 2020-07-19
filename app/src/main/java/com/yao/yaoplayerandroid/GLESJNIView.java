package com.yao.yaoplayerandroid;

import android.content.Context;
import android.opengl.GLSurfaceView;
import android.util.AttributeSet;

import com.yao.yaoplayerandroid.player.Player;

import java.util.jar.Attributes;

public class GLESJNIView extends GLSurfaceView {
    private Player player;
    public GLESJNIView(Context context){
        this(context, (AttributeSet)null);
    }

    public GLESJNIView(Context context, Player _player){
        super(context, null);
        player = _player;
        init();
    }

    public GLESJNIView(Context context, AttributeSet attrs){
        super(context, attrs);
        init();
    }

    public void init(){
        //设置opengl es版本
        setEGLContextClientVersion(3);
        setRenderer(new GLRender(player));
    }
}
