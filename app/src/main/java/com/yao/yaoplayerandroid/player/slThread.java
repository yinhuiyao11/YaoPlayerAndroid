package com.yao.yaoplayerandroid.player;

public class slThread extends Thread {
    public volatile boolean exit = false;
    Player player;

    public slThread(Player _player)
    {
        player = _player;
    }
    @Override
    public void run(){
        //while ()
    }
}
