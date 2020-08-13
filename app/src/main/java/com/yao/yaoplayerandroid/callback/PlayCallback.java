package com.yao.yaoplayerandroid.callback;

import android.widget.ProgressBar;

import com.yao.yaoplayerandroid.R;

public class PlayCallback {
    public PlayCallback(){

    }
    public int playEndCallback() {
        //自行执行回调后的操作
        System.out.println("~~~~~~~~~~~~~in: playEndCallback\n");
        return 0;
    }

    public int playSetProgressBar(int playSec){
        System.out.println("~~~~~~~~~~~~~playSetProgressBar playSec: " + playSec);

        return 0;
    }
}
