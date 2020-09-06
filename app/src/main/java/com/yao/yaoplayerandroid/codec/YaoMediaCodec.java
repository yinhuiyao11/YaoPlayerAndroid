package com.yao.yaoplayerandroid.codec;

import android.media.MediaCodec;
import android.media.MediaCodecInfo;
import android.media.MediaCodecList;
import android.media.MediaFormat;
import android.util.Log;
import android.view.Surface;

import java.io.IOException;
import java.nio.ByteBuffer;
import java.util.ArrayList;
import java.util.List;

import static android.media.MediaCodec.BUFFER_FLAG_END_OF_STREAM;

public class YaoMediaCodec {
    private MediaCodec mediaCodec = null;
    private MediaCodec.BufferInfo bufferInfo = new MediaCodec.BufferInfo();
    private int initStatus = -1;
    public int getInitStatus(){
        return initStatus;
    }

    public int init(int width, int height, Surface surface){
        displayDecoders();
        Log.e("EyerMediaCodec", "width: " + width + " height: " + height);
        System.out.println("EyerMediaCodec width: " + width + " height: " + height);

        try {
            mediaCodec = MediaCodec.createDecoderByType(MediaFormat.MIMETYPE_VIDEO_AVC);
        } catch (IOException e) {
            e.printStackTrace();
        }

        MediaFormat mediaFormat = MediaFormat.createVideoFormat(MediaFormat.MIMETYPE_VIDEO_AVC, width, height);
        mediaCodec.configure(mediaFormat, surface, null, 0);
        mediaCodec.start();
        initStatus = 0;
        return 0;
    }

    public int uninit(){
        if(mediaCodec == null){
            return -1;
        }

        mediaCodec.stop();
        mediaCodec.release();

        return 0;
    }

    private void displayDecoders() {
        MediaCodecList list = null;
        if (android.os.Build.VERSION.SDK_INT >= android.os.Build.VERSION_CODES.LOLLIPOP) {
            list = new MediaCodecList(MediaCodecList.REGULAR_CODECS);
        }
        MediaCodecInfo[] codecs = new MediaCodecInfo[0];
        if (android.os.Build.VERSION.SDK_INT >= android.os.Build.VERSION_CODES.LOLLIPOP) {
            codecs = list.getCodecInfos();
        }
        if(list != null) {
            for (MediaCodecInfo codec : codecs) {
                if (codec.isEncoder())
                    continue;
                Log.e("EyerMediaCodec", "Decoder Name: " + codec.getName());
            }
        }
    }

    public int dequeueInputBuffer(long timeoutUs){
        return mediaCodec.dequeueInputBuffer(timeoutUs);
    }
    public int send(int inputBufIndex, byte[] data){
        if (inputBufIndex >= 0) {
            ByteBuffer inputBuf = mediaCodec.getInputBuffers()[inputBufIndex];
            inputBuf.clear();
            inputBuf.put(data);
            return 0;

        }
        return -1;
    }

    public void queueInputBuffer(int inputBufIndex, int offset, int size, long presentationTimeUs, int flags){
        mediaCodec.queueInputBuffer(inputBufIndex, offset, size, presentationTimeUs, flags);
    }

    public int recvAndRender(){
        MediaCodec.BufferInfo bufferInfo = new MediaCodec.BufferInfo();
        int outindex = mediaCodec.dequeueOutputBuffer(bufferInfo, -1);
        System.out.println("java recvAndRender outindex: " + outindex);

        if (outindex >= 0) {
            ByteBuffer outputBuffer = mediaCodec.getOutputBuffers()[outindex];
            mediaCodec.releaseOutputBuffer(outindex, true);
            return 0;
        }

        return -1;
    }

    public int dequeueOutputBuffer(long timeoutUs){
        if(mediaCodec == null) {
            System.out.println("in dequeueOutputBuffer:mediaCodec is null");
            return -1;
        }else {
            //System.out.println("in dequeueOutputBuffer:mediaCodec is not null");

        }
        int outindex = mediaCodec.dequeueOutputBuffer(bufferInfo, timeoutUs);
        return outindex;
    }

    public long getOutTime(){
        return bufferInfo.presentationTimeUs;
    }


    public int renderFrame(int outindex, boolean isRender){
        if(mediaCodec == null) {
            System.out.println("in renderFrame:mediaCodec is null");
            return -1;
        }else {
            //System.out.println("in renderFrame:mediaCodec is not null");

        }

        ByteBuffer outputBuffer = mediaCodec.getOutputBuffers()[outindex];
        mediaCodec.releaseOutputBuffer(outindex, isRender);

        return 0;
    }

    public int flush(){
        mediaCodec.flush();
        return 0;
    }

    public void sendEndOfStream(int index){
        mediaCodec.queueInputBuffer(index,0,0,0, BUFFER_FLAG_END_OF_STREAM);
    }
}
