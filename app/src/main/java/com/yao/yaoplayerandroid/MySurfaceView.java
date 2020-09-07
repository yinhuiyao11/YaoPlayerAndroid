package com.yao.yaoplayerandroid;

import android.content.Context;
import android.os.Environment;
import android.util.AttributeSet;
import android.view.Surface;
import android.view.SurfaceHolder;
import android.view.SurfaceView;

import com.yao.yaoplayerandroid.codec.InputBufferThread;
import com.yao.yaoplayerandroid.codec.OutputBufferThread;
import com.yao.yaoplayerandroid.codec.YaoMediaCodec;
import com.yao.yaoplayerandroid.player.Player;

import java.io.File;

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


    //private YaoMediaCodec mediaCodec = null;
    private Player player;
    static long duration = 0;

    @Override
    public void surfaceCreated(SurfaceHolder holder) {
        Surface surface = holder.getSurface();
        holder.setKeepScreenOn(true);

        File dir = Environment.getExternalStorageDirectory();
        //String videoPath = dir.getAbsolutePath() + "/" + "ST/time_clock_1min_720x1280_30fps.mp4";
        //String videoPath = dir.getAbsolutePath() + "/" + "ST/ads.mp4";
        //String videoPath = dir.getAbsolutePath() + "/" + "ST/banfo.mp4";
        String videoPath = dir.getAbsolutePath() + "/" + "ST/mrHe.mp4";
        //String videoPath = dir.getAbsolutePath() + "/" + "ST/The_Beauty_of_Earth.mp4";
        //String videoPath = dir.getAbsolutePath() + "/" + "ST/4k_animal.mp4";
        //String videoPath = dir.getAbsolutePath() + "/" + "ST/rabbit.mp4";
        //String videoPath = "http://redknot.cn/sohu/hls/shuw.m3u8";
        System.out.println("+++++++++path:" + videoPath);

        File f = new File(videoPath);
        System.out.println("f:" + f.canRead());

        player = new Player(videoPath);
        duration = player.gl_duration();
        player.open(0, surface);

        //video_progress_bar.setMax(100);
        //bindSeekBar(player);

        player.play();


       /* mediaCodec = new YaoMediaCodec();
        mediaCodec.init(1920, 1080, holder.getSurface());
        Thread inputBufferThread = new Thread(new InputBufferThread(mediaCodec));
        inputBufferThread.start();

        Thread outputBufferThread = new Thread(new OutputBufferThread(mediaCodec));
        outputBufferThread.start();*/

    }

    @Override
    public void surfaceChanged(SurfaceHolder holder, int format, int width, int height) {

    }

    @Override
    public void surfaceDestroyed(SurfaceHolder holder) {

    }
}
