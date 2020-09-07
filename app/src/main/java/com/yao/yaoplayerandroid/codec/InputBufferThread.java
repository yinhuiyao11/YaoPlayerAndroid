package com.yao.yaoplayerandroid.codec;

import com.yao.yaoplayerandroid.test.Nalu;
import com.yao.yaoplayerandroid.test.ReadNalu;

import java.io.BufferedOutputStream;
import java.io.ByteArrayOutputStream;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.IOException;

public class InputBufferThread implements Runnable {
    private YaoMediaCodec mediaCodec;

    public InputBufferThread(YaoMediaCodec _mediaCodec){
        mediaCodec = _mediaCodec;
    }
    @Override
    public void run() {
        System.out.println("66in InputBufferThread");

        ReadNalu readNalu = new ReadNalu("/storage/emulated/0/ST/M_1280_720.h264");

        /*BufferedOutputStream output = null;
        try {
            output = new BufferedOutputStream(new FileOutputStream("/storage/emulated/0/ST/M_1280_720_rewrite.h264"));
        } catch (FileNotFoundException e) {
            e.printStackTrace();
        }*/

        while (readNalu.haveReadPos < readNalu.naluStartPosList.size() - 1){
            //System.out.println("888haveReadPos "+readNalu.haveReadPos);
            Nalu nalu = readNalu.readNaluChar();
            //System.out.println("1111111readNalu.haveReadPos"+readNalu.haveReadPos);

            /*try {
                output.write(nalu.buffer, 0, nalu.lenth);

            } catch (FileNotFoundException e) {
                e.printStackTrace();
            } catch (IOException e) {
                e.printStackTrace();
            }*/
            int inputIndex = mediaCodec.dequeueInputBuffer(1000 * 100);
            if(inputIndex >= 0){
                mediaCodec.send(inputIndex, nalu.buffer);
                mediaCodec.queueInputBuffer(inputIndex, 0, nalu.lenth, 1000,0);
            }

        }

        /*try {
            output.close();
        } catch (IOException e) {
            e.printStackTrace();
        }*/
    }
}
