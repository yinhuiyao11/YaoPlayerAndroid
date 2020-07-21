package com.yao.yaoplayerandroid.av;

import com.yao.yaoplayerandroid.base.YaoObject;

public class AVReader extends YaoObject {
    static {
        System.loadLibrary("native-lib");
    }
    // AV Reader
    public static native long                   avreader_init                               ();
    public static native int                    avreader_uninit                             (long avreader);
    public static native int                    avreader_open                               (long avreader, String url);
    public static native int                    avreader_close                              (long avreader);
    public static native int                    avreader_print_info                         (long avreader);

    public AVReader(){
        nativeId = avreader_init();
    }

    public int open(String url){
        return avreader_open(nativeId, url);
    }

    public int close(){
        return  avreader_close(nativeId);
    }

    public int uninit(){
        return avreader_uninit(nativeId);
    }

    public int printInfo(){
        return avreader_print_info(nativeId);
    }

    @Override
    public int destory() {
        if(nativeId != 0L){
            avreader_uninit(nativeId);
            nativeId = 0L;
        }
        return 0;
    }
}
