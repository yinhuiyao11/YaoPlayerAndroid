package com.yao.yaoplayerandroid.callback;

public class PlayCallback {
    public PlayCallback(){

    }
    public static int playEndCallback() {
        //自行执行回调后的操作
        System.out.println("~~~~~~~~~~~~~in: playEndCallback\n");
        return 0;
    }

    public static int playSetProgressBar(int playSec){
        System.out.println("~~~~~~~~~~~~~playSetProgressBar playSec: " + playSec);
        return 0;
    }
}
