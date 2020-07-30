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
    public static native int                    player_gl_surfaceChanged                    (long player, int width, int height);
    public static native int                    player_gl_drawFrame                         (long player);

    public static native int                    player_sl                                   (long player);

    public static native int                    player_start_sl                                   (long player);

    public static native int                    player_print_queue_size                         (long player);

    public int print_queue_size(){
        //System.out.println("+++++++++++++++in print_queue_size");
        return player_print_queue_size(nativeId);
    }
    public Player(String path){
        nativeId = player_init(path);
        //System.out.println("+++++++++++++++in Player");
    }

    public int open(double time){
        //System.out.println("+++++++++++++++in open");
        return player_open(nativeId, time);
    }

    public int stop(){
        //System.out.println("+++++++++++++++in stop");
        return player_stop(nativeId);
    }

    public int pause(){
        return player_pause(nativeId);
    }

    public int play(){
        //System.out.println("+++++++++++++++in play");
        return player_play(nativeId);
    }

    public int seek(double time){
        //System.out.println("+++++++++++++++in seek");
        return player_seek(nativeId, time);
    }

    public int gl_surfaceChanged(int width, int height){
        //System.out.println("+++++++++++++++in player_gl_surfaceChanged");
        return player_gl_surfaceChanged(nativeId, width, height);
    }

    public int gl_drawFrame(){
        //System.out.println("+++++++++++++++in gl_drawFrame");
        return player_gl_drawFrame(nativeId);
    }

    public int sl_play(){
        System.out.println("+++++++++++++++in sl_play");
        return player_sl(nativeId);
    }

    public int sl_start_play(){
        System.out.println("+++++++++++++++in player_start_sl");
        return player_start_sl(nativeId);
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
