package com.yao.yaoplayerandroid;

import android.content.Context;
import android.util.AttributeSet;
import android.view.SurfaceHolder;
import android.view.SurfaceView;

import com.yao.yaoplayerandroid.codec.InputBufferThread;
import com.yao.yaoplayerandroid.codec.OutputBufferThread;
import com.yao.yaoplayerandroid.codec.YaoMediaCodec;

public class MySurfaceView extends SurfaceView implements SurfaceHolder.Callback {
    public MySurfaceView(Context context) {
        super(context);
        init();
    }

    public MySurfaceView(Context context, AttributeSet attrs) {
        super(context, attrs);
        init();
    }

    public MySurfaceView(Context context, AttributeSet attrs, int defStyleAttr) {
        super(context, attrs, defStyleAttr);
        init();
    }

    private int init(){
        getHolder().addCallback(this);
        return 0;
    }


    private YaoMediaCodec mediaCodec = null;

    @Override
    public void surfaceCreated(SurfaceHolder holder) {
        mediaCodec = new YaoMediaCodec();
        mediaCodec.init(1920, 1080, holder.getSurface());
        Thread inputBufferThread = new Thread(new InputBufferThread(mediaCodec));
        inputBufferThread.start();

        Thread outputBufferThread = new Thread(new OutputBufferThread(mediaCodec));
        outputBufferThread.start();

    }

    @Override
    public void surfaceChanged(SurfaceHolder holder, int format, int width, int height) {

    }

    @Override
    public void surfaceDestroyed(SurfaceHolder holder) {
        mediaCodec.uninit();
    }
}
