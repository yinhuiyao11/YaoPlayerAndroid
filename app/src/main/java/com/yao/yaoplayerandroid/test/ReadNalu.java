package com.yao.yaoplayerandroid.test;

import java.io.BufferedInputStream;
import java.io.BufferedReader;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.Reader;
import java.util.ArrayList;

public class ReadNalu {
    public ArrayList<Long> naluStartPosList = new ArrayList<Long>();
    public int haveReadPos = 0;
    private String path;

    public ReadNalu(String _path){
        path = _path;
        getNaluStartPosList(_path);
    }

    public int isStartCode(byte[] buffer){
        if(buffer[0] == 0x00 && buffer[1] == 0x00 && buffer[2] == 0x00 && buffer[3] == 0x01){
            return 0;
        }
        return -1;
    }

    //返回读出每个nalu起始位置
    public int getNaluStartPosList(String path){
        try {
            byte[] head = new byte[4];
            long pos = 0;

            BufferedInputStream bufferedReader = new BufferedInputStream(new FileInputStream(path));
            int readLen = 0;
            while (readLen >= 0){

                readLen = bufferedReader.read(head, 0, 4);

                if(isStartCode(head) != -1){
                    System.out.println("3333333333 start pos:"+ pos);
                    naluStartPosList.add(pos);
                }
                pos = pos + 4;
            }

            bufferedReader.close();
        } catch (FileNotFoundException e) {
            e.printStackTrace();
        } catch (IOException e) {
            e.printStackTrace();
        }
        return 0;
    }

    public Nalu readNaluChar(){
        long startPos = naluStartPosList.get(haveReadPos);
        long endPos = naluStartPosList.get(haveReadPos + 1);
        int naluLen = (int)(endPos - startPos);
        byte[] naluContent = new byte[naluLen];

        try {
            BufferedInputStream bufferedReader = new BufferedInputStream(new FileInputStream(path));
            bufferedReader.read(naluContent, 0, naluLen);
            haveReadPos++;
            bufferedReader.close();
        } catch (FileNotFoundException e) {
            e.printStackTrace();
        } catch (IOException e) {
            e.printStackTrace();
        }

        Nalu nalu = new Nalu();
        nalu.buffer = naluContent;
        nalu.lenth = naluLen;
        return nalu;
    }
}
