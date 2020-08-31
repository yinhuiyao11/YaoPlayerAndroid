package com.yao.yaoplayerandroid.codec;

public class OutputBufferThread implements Runnable {
    private YaoMediaCodec mediaCodec;

    public OutputBufferThread(YaoMediaCodec _mediaCodec){
        mediaCodec = _mediaCodec;
    }
    @Override
    public void run() {
        while(true){
            int outindex = mediaCodec.dequeueOutputBuffer(1000);
            if(outindex >= 0){
                mediaCodec.renderFrame(outindex, true);
            }
        }
    }
}
