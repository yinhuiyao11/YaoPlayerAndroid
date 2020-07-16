package com.yao.yaoplayerandroid.player;

import com.yao.yaoplayerandroid.base.YaoObject;

public class Player extends YaoObject {

    // AV Reader
    public static native long                   player_init                                 (String path);
    public static native int                    player_uninit                               (long player);
    public static native int                    player_open                                 (long player, double time);
    public static native int                    player_stop                                 (long player);
    public static native int                    player_play                                 (long player);
    public static native int                    player_pause                                (long player);
    public static native int                    player_seek                                 (long player, double time);
    //public static native long                   player_get_play_video_frame                 (long player);

    public Player(String path){
        nativeId = player_init(path);
        System.out.println("+++++++++++++++in Player");
    }

    public int open(double time){
        System.out.println("+++++++++++++++in open");
        return player_open(nativeId, time);
    }

    public int stop(){
        System.out.println("+++++++++++++++in stop");
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
        System.out.println("+++++++++in destory:");

        return 0;
    }
}
