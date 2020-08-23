package com.yao.yaoplayerandroid.codec;

import com.yao.yaoplayerandroid.test.Nalu;
import com.yao.yaoplayerandroid.test.ReadNalu;

public class InputBufferThread implements Runnable {
    private YaoMediaCodec mediaCodec;

    public InputBufferThread(YaoMediaCodec _mediaCodec){
        mediaCodec = _mediaCodec;
    }
    @Override
    public void run() {
        System.out.println("66in InputBufferThread");

        ReadNalu readNalu = new ReadNalu("/storage/emulated/0/ST/M_1280_720.h264");
        while (readNalu.haveReadPos < readNalu.naluStartPosList.size() - 1){
            //System.out.println("888haveReadPos "+readNalu.haveReadPos);
            Nalu nalu = readNalu.readNaluChar();
            mediaCodec.send(nalu.buffer, 0);
        }
    }
}
