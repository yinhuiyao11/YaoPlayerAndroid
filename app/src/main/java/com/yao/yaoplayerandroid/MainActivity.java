package com.yao.yaoplayerandroid;

import androidx.appcompat.app.AppCompatActivity;
import androidx.core.app.ActivityCompat;

import android.app.Activity;
import android.content.pm.ActivityInfo;
import android.content.pm.PackageManager;
import android.os.Bundle;
import android.os.Environment;
import android.util.DisplayMetrics;
import android.view.View;
import android.widget.Button;
import android.widget.ProgressBar;
import android.widget.RelativeLayout;
import android.widget.TextView;
import android.opengl.GLSurfaceView;

import com.yao.yaoplayerandroid.player.Player;

import java.io.File;

public class MainActivity extends AppCompatActivity {
    static {
        System.loadLibrary("YaoPlayerJni");
    }
    private GLSurfaceView gLSurfaceView;
    private Button btn_start;
    private Button btn_stop;
    private ProgressBar video_progress_bar;
    private RelativeLayout mParent;

    private Player player;
    private int started = 0;

    private static String[] PERMISSIONS_STORAGE = {
            "android.permission.READ_EXTERNAL_STORAGE",
            "android.permission.WRITE_EXTERNAL_STORAGE" };

    private static final int REQUEST_EXTERNAL_STORAGE = 1;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        initView();
        /*setContentView(R.layout.activity_main);
        // Example of a call to a native method
        TextView tv = (TextView) findViewById(R.id.sample_text);
        tv.setText(stringFromJNI());*/


        verifyStoragePermissions(this);

    }

    private void initView(){
        gLSurfaceView = findViewById(R.id.gLSurfaceView);
        System.out.println("------initView surfaceWidth:" + gLSurfaceView.getWidth() + "  height:" + gLSurfaceView.getHeight());

        btn_start = findViewById(R.id.btn_start);
        btn_stop = findViewById(R.id.btn_stop);
        mParent = findViewById(R.id.test_parent_play);
        btn_start.setOnClickListener(new View.OnClickListener(){
            @Override
            public void onClick(View v) {

            }
        });

        btn_stop.setOnClickListener(new View.OnClickListener(){
            @Override
            public void onClick(View v) {

            }
        });
    }

    //改变视频的尺寸自适应。
    public void changeVideoSize() {
        //todo 获取视频长宽
        int videoWidth = 4096;
        int videoHeight = 2160;

        DisplayMetrics dm = new DisplayMetrics();
        dm = getResources().getDisplayMetrics();

        int surfaceWidth = dm.widthPixels;
        int surfaceHeight = dm.heightPixels;

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
            new Thread() {
                public void run() {
                    //audio
                    player.sl_play();
                }
            }.start();
        }
        if(started == 0) {
            File dir = Environment.getExternalStorageDirectory();
            //String videoPath = dir.getAbsolutePath() + "/" + "ST/time_clock_1min_720x1280_30fps.mp4";
            //String videoPath = dir.getAbsolutePath() + "/" + "ST/The_Beauty_of_Earth.mp4";
            //String videoPath = dir.getAbsolutePath() + "/" + "ST/4k_animal.mp4";
            String videoPath = dir.getAbsolutePath() + "/" + "ST/rabbit.mp4";
            System.out.println("+++++++++path:" + videoPath);

            File f = new File(videoPath);
            System.out.println("f:" + f.canRead());

            player = new Player(videoPath);
            player.open(0);

            gLSurfaceView.setEGLContextClientVersion(3);
            gLSurfaceView.setRenderer(new GLRender(player));
            //gLESJNIView = new GLESJNIView(this, player);
            changeVideoSize();

            new Thread() {
                public void run() {
                    //audio
                    player.sl_play();
                }
            }.start();

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


    public static void verifyStoragePermissions(Activity activity) {
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
    /**
     * A native method that is implemented by the 'native-lib' native library,
     * which is packaged with this application.
     */
    public native String stringFromJNI();
}
