package com.yao.yaoplayerandroid.callback;

import android.widget.ProgressBar;

import androidx.appcompat.app.AppCompatActivity;

import com.yao.yaoplayerandroid.R;

public class PlayCallback extends AppCompatActivity {
    public PlayCallback(){

    }
    public int playEndCallback() {
        //自行执行回调后的操作
        System.out.println("~~~~~~~~~~~~~in: playEndCallback\n");
        return 0;
    }

    public int playSetProgressBar(int playSec){
        System.out.println("~~~~~~~~~~~~~playSetProgressBar playSec: " + playSec);
        ProgressBar video_progress_bar = findViewById(R.id.video_progress_bar);
        if(video_progress_bar == null){
            System.out.println("~~~~~~~~~~~~~playSetProgressBar video_progress_bar is null ");

        }
        video_progress_bar.setProgress(playSec);
        return 0;
    }
}
