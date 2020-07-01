package com.yao.yaoplayerandroid;

public class AVReader {
    static {
        System.loadLibrary("native-lib");
    }
    // AV Reader
    public static native long                   avreader_init                               (String url);
    public static native int                    avreader_uninit                             (long avreader);
    public static native int                    avreader_open                               (long avreader);
    public static native int                    avreader_close                              (long avreader);
    public static native int                    avreader_print_info                         (long avreader);
}
