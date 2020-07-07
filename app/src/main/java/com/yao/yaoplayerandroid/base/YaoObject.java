package com.yao.yaoplayerandroid.base;

public abstract class YaoObject {
    protected long nativeId = 0;

    public long getNativeId()
    {
        return nativeId;
    }

    public abstract int destory();
}
