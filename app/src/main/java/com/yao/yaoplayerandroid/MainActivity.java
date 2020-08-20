package com.yao.yaoplayerandroid;

import androidx.appcompat.app.AppCompatActivity;
import androidx.core.app.ActivityCompat;

import android.app.Activity;
import android.content.pm.ActivityInfo;
import android.content.pm.PackageManager;
import android.os.Bundle;
import android.os.Environment;
import android.os.Handler;
import android.os.Looper;
import android.os.Message;
import android.util.DisplayMetrics;
import android.view.View;
import android.widget.Button;
import android.widget.ProgressBar;
import android.widget.RelativeLayout;
import android.widget.SeekBar;
import android.widget.TextView;
import android.opengl.GLSurfaceView;
import android.widget.Toast;

import com.yao.yaoplayerandroid.player.Player;

import java.io.File;

public class MainActivity extends AppCompatActivity {
    static {
        System.loadLibrary("YaoPlayerJni");
    }
    private GLSurfaceView gLSurfaceView;
    private Button btn_start;
    private SeekBar video_progress_bar;
    private RelativeLayout mParent;
    private Player player;
    private int started = 0;

    private int screenHeight;
    private int screenWidth;
    private int isplay = 1;

    public int progress = 0;
    MyHandler myHandler;
    static MyHandler mHandler;
    static long duration = 0;

    private static String[] PERMISSIONS_STORAGE = {
            "android.permission.READ_EXTERNAL_STORAGE",
            "android.permission.WRITE_EXTERNAL_STORAGE" };

    private static final int REQUEST_EXTERNAL_STORAGE = 1;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        verifyStoragePermissions(this);

        initView();
        /*setContentView(R.layout.activity_main);
        // Example of a call to a native method
        TextView tv = (TextView) findViewById(R.id.sample_text);
        tv.setText(stringFromJNI());*/

    }

    private void initView(){
        DisplayMetrics dm = new DisplayMetrics();
        dm = getResources().getDisplayMetrics();
        screenWidth = dm.widthPixels;
        screenHeight = dm.heightPixels;

        gLSurfaceView = findViewById(R.id.gLSurfaceView);

        btn_start = findViewById(R.id.btn_start);
        mParent = findViewById(R.id.test_parent_play);

        myHandler = new MyHandler();
        mHandler = myHandler;//重要,保存全局静态handler句柄,以便回掉的时候能找到该上下文

        video_progress_bar = findViewById(R.id.video_progress_bar);
        video_progress_bar.setMax(100);
        video_progress_bar.setProgress(progress);
        btn_start.setOnClickListener(new View.OnClickListener(){
            @Override
            public void onClick(View v) {
                if(isplay == 1){
                    player.pause();
                    isplay = 0;
                }else if(isplay == 0){
                    player.play();
                    isplay = 1;
                }
            }
        });

    }

    //改变视频的尺寸自适应。
    public void changeVideoSize(int videoWidth , int videoHeight) {
        int surfaceWidth = screenWidth;
        int surfaceHeight = screenHeight;

        //根据视频尺寸去计算->视频可以在sufaceView中放大的最大倍数。
        float max;
        if (getResources().getConfiguration().orientation == ActivityInfo.SCREEN_ORIENTATION_PORTRAIT) {
            //竖屏模式下按视频宽度计算放大倍数值
            max = Math.max((float) videoWidth / (float) surfaceWidth, (float) videoHeight / (float) surfaceHeight);
        } else {
            //横屏模式下按视频高度计算放大倍数值
            max = Math.max(((float) videoWidth / (float) surfaceHeight), (float) videoHeight / (float) surfaceWidth);
        }

        //视频宽高分别/最大倍数值 计算出放大后的视频尺寸
        videoWidth = (int) Math.ceil((float) videoWidth / max);
        videoHeight = (int) Math.ceil((float) videoHeight / max);
        System.out.println("endVideoWidth:" + videoWidth + "  endVideoHeight:" + videoHeight);

        //无法直接设置视频尺寸，将计算出的视频尺寸设置到surfaceView 让视频自动填充。
        RelativeLayout.LayoutParams params = new RelativeLayout.LayoutParams(videoWidth, videoHeight);
        params.addRule(RelativeLayout.CENTER_VERTICAL, mParent.getId());
        gLSurfaceView.setLayoutParams(params);

    }


    @Override
    protected void onStart() {
        super.onStart();
        if(started == 1){
            player.play();
            //player.sl_play();
        }
        if(started == 0) {
            File dir = Environment.getExternalStorageDirectory();
            //String videoPath = dir.getAbsolutePath() + "/" + "ST/time_clock_1min_720x1280_30fps.mp4";
            //String videoPath = dir.getAbsolutePath() + "/" + "ST/ads.mp4";
            //String videoPath = dir.getAbsolutePath() + "/" + "ST/banfo.mp4";
            //String videoPath = dir.getAbsolutePath() + "/" + "ST/The_Beauty_of_Earth.mp4";
            String videoPath = dir.getAbsolutePath() + "/" + "ST/4k_animal.mp4";
            //String videoPath = dir.getAbsolutePath() + "/" + "ST/rabbit.mp4";
            System.out.println("+++++++++path:" + videoPath);

            File f = new File(videoPath);
            System.out.println("f:" + f.canRead());

            player = new Player(videoPath);
            duration = player.gl_duration();
            player.open(0);

            video_progress_bar.setMax(100);
            bindSeekBar(player);

            gLSurfaceView.setEGLContextClientVersion(3);
            gLSurfaceView.setRenderer(new GLRender(player));

            changeVideoSize(player.gl_width(), player.gl_height());
            //System.out.println("_+_++_+_+_+_+_+++++_+gl_duration:" + player.gl_duration());

            started = 1;
            player.play();

        }
        //player.stop();
    }

    @Override
    protected void onPause() {
        super.onPause();
        player.pause();
    }


    public int playEndCallback() {
        //自行执行回调后的操作
        System.out.println("~~~~~~~~~~~~~in: playEndCallback\n");
        return 0;
    }

    class MyHandler extends Handler {
        public MyHandler() {
        }

        public MyHandler(Looper L) {
            super(L);
        }

        // 子类必须重写此方法，接受数据
        @Override
        public void handleMessage(Message msg) {
            super.handleMessage(msg);
            // 此处可以更新UI
            video_progress_bar.setProgress((int)((float)msg.what/(float) duration * (float)100));
        }
    }

    public int playSetProgressBar(int playSec){
        System.out.println("~~~~~~~playSetProgressBar:"+ playSec);

        Message meg = Message.obtain();
        meg.what = playSec;
        mHandler.sendMessage(meg);

        return 0;
    }

    public void verifyStoragePermissions(Activity activity) {
        try {
            //检测是否有写的权限
            int permission = ActivityCompat.checkSelfPermission(activity, "android.permission.WRITE_EXTERNAL_STORAGE");
            if (permission != PackageManager.PERMISSION_GRANTED) {
                // 没有写的权限，去申请写的权限，会弹出对话框
                ActivityCompat.requestPermissions(activity, PERMISSIONS_STORAGE,REQUEST_EXTERNAL_STORAGE);
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    private void bindSeekBar(final Player player) {
        video_progress_bar.setOnSeekBarChangeListener(new SeekBar.OnSeekBarChangeListener() {
            @Override
            public void onProgressChanged(SeekBar seekBar, int progress, boolean fromUser) {
                System.out.println("~~~当前进度值:" + progress);
            }

            @Override
            public void onStartTrackingTouch(SeekBar seekBar) {
                //System.out.println("~~~onStart:" + seekBar.getProgress());

            }

            @Override
            public void onStopTrackingTouch(SeekBar seekBar) {
                System.out.println("~~~onStop:" + seekBar.getProgress());
                player.seek((double) seekBar.getProgress() * 0.01 * player.gl_duration());
            }
        });
    }
}
