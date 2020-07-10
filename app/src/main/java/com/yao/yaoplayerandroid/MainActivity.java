package com.yao.yaoplayerandroid;

import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;
import android.os.Environment;
import android.widget.TextView;
import android.opengl.GLSurfaceView;

import com.yao.yaoplayerandroid.player.Player;

import java.io.File;

public class MainActivity extends AppCompatActivity {
    static {
        System.loadLibrary("YaoPlayerJni");
    }
    private GLESJNIView view;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        /*view = new GLESJNIView(getApplication());
        setContentView(view);*/

        setContentView(R.layout.activity_main);
        // Example of a call to a native method
        TextView tv = findViewById(R.id.sample_text);
        tv.setText(stringFromJNI());

        /*File dir = Environment.getExternalStorageDirectory();
        String videoPath = dir.getAbsolutePath() + "/" + "ST/time_clock_1min_720x1280_30fps.mp4";
        Player player = new Player(videoPath);*/
    }

    /**
     * A native method that is implemented by the 'native-lib' native library,
     * which is packaged with this application.
     */
    public native String stringFromJNI();
}
