package com.yao.yaoplayerandroid;

import androidx.appcompat.app.AppCompatActivity;
import androidx.core.app.ActivityCompat;

import android.app.Activity;
import android.content.pm.PackageManager;
import android.os.Bundle;
import android.os.Environment;
import android.view.View;
import android.widget.Button;
import android.widget.ProgressBar;
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
        btn_start = findViewById(R.id.btn_start);
        btn_stop = findViewById(R.id.btn_stop);

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
            String videoPath = dir.getAbsolutePath() + "/" + "ST/4k_animal.mp4";
            System.out.println("+++++++++path:" + videoPath);

            File f = new File(videoPath);
            System.out.println("f:" + f.canRead());

            player = new Player(videoPath);
            player.open(0);

            gLSurfaceView.setEGLContextClientVersion(3);
            gLSurfaceView.setRenderer(new GLRender(player));
            //gLESJNIView = new GLESJNIView(this, player);

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
