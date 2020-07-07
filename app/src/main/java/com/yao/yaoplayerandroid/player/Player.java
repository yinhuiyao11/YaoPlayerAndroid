package com.yao.yaoplayerandroid.player;

import com.yao.yaoplayerandroid.base.YaoObject;

public class Player extends YaoObject {
    static {
        System.loadLibrary("native-lib");
    }
    // AV Reader
    public static native long                   player_init                                 (String path);
    public static native int                    player_uninit                               (long player);
    public static native int                    player_open                                 (long player, double time);
    public static native int                    player_stop                                 (long player);
    public static native int                    player_play                                 (long player);
    public static native int                    player_pause                                (long player);
    public static native int                    player_seek                                 (long player, double time);

    public Player(String path){
        nativeId = player_init(path);
    }

    public int open(double time){
        return player_open(nativeId, time);
    }

    public int stop(){
        return player_stop(nativeId);
    }

    public int pause(){
        return player_pause(nativeId);
    }

    public int play(){
        return player_play(nativeId);
    }

    public int seek(double time){
        return player_seek(nativeId, time);
    }

    @Override
    public int destory() {
        if(nativeId != 0L){
            player_uninit(nativeId);
            nativeId = 0L;
        }
        return 0;
    }
}
