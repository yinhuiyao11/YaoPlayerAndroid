package com.yao.yaoplayerandroid.player;

public class PlayEndCallback {
    public PlayEndCallback(){

    }
    public static int onEndCallBack() {
        //自行执行回调后的操作
        System.out.println("~~~~~~~~~~~~~total: callback\n");
        return 0;
    }
}
