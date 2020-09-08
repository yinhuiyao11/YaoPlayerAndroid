package com.yao.yaoplayerandroid.callback;

import android.app.Activity;
import android.os.Handler;
import android.os.Looper;
import android.os.Message;
import android.widget.SeekBar;

import com.yao.yaoplayerandroid.R;

public class ProgressBarHandler extends Handler {
    Activity content;
    long duration;
    public ProgressBarHandler(Activity _content, long _duration) {
        content = _content;
        duration = _duration;
    }

    public ProgressBarHandler(Looper L) {
        super(L);
    }

    // 子类必须重写此方法，接受数据
    @Override
    public void handleMessage(Message msg) {
        super.handleMessage(msg);
        // 此处可以更新UI
        SeekBar video_progress_bar_inner = content.findViewById(R.id.video_progress_bar);
        video_progress_bar_inner.setProgress((int)((float)msg.what/(float) duration * (float)100));
    }
}
