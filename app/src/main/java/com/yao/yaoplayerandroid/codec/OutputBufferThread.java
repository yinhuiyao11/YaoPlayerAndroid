package com.yao.yaoplayerandroid.codec;

public class OutputBufferThread implements Runnable {
    private YaoMediaCodec mediaCodec;

    public OutputBufferThread(YaoMediaCodec _mediaCodec){
        mediaCodec = _mediaCodec;
    }
    @Override
    public void run() {
        System.out.println("66in OutputBufferThread");
        while(true){
            mediaCodec.recvAndRender();
        }
    }
}
