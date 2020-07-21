basepath=$(cd `dirname $0`; pwd)
echo ${basepath}

files=$(ls $NDK/toolchains/llvm/prebuilt/)
HOST_TAG=$""
for filename in $files
do
    echo $filename
    HOST_TAG=$filename
done

# HOST_TAG=linux-x86_64
# HOST_TAG=darwin-x86_64
# HOST_TAG=windows-x86_64

echo "last   HOST_TAG:"$HOST_TAG

export TOOLCHAIN=$NDK/toolchains/llvm/prebuilt/$HOST_TAG


# Only choose one of these, depending on your device...
# export TARGET=aarch64-linux-android
export TARGET=armv7a-linux-androideabi
# export TARGET=i686-linux-android
# export TARGET=x86_64-linux-android


# Set this to your minSdkVersion.
export API=18

export CC=$TOOLCHAIN/bin/$TARGET$API-clang
export CXX=$TOOLCHAIN/bin/$TARGET$API-clang++

# export AR=$TOOLCHAIN/bin/$TARGET-ar
export AR=$TOOLCHAIN/bin/arm-linux-androideabi-ar
export AS=$TOOLCHAIN/bin/arm-linux-androideabi-as
export LD=$TOOLCHAIN/bin/arm-linux-androideabi-ld
export RANLIB=$TOOLCHAIN/bin/arm-linux-androideabi-ranlib
export STRIP=$TOOLCHAIN/bin/arm-linux-androideabi-strip



cd ${basepath}/3rdpart/ffmpeg_3.2.14
./configure \
--enable-static \
--disable-shared \
--disable-ffmpeg \
--disable-ffplay \
--disable-ffprobe \
--disable-ffserver \
--disable-avdevice \
--disable-doc \
--disable-symver \
--prefix=./ffmpeg_install \
--enable-gpl \
--enable-pic \
--disable-neon \
--enable-cross-compile \
--target-os=android \
--arch=arm \
--nm=$TOOLCHAIN/bin/arm-linux-androideabi-nm \
--cc=$TOOLCHAIN/bin/$TARGET$API-clang \
--cross-prefix=$TOOLCHAIN/bin/arm-linux-androideabi-

make clean
make -j4
make install

cd ${basepath}

if [ -d ./jniLibs ];then
    rm -rf jniLibs
fi

mkdir jniLibs
cd jniLibs
mkdir armeabi-v7a
cd armeabi-v7a

cp -r ../../3rdpart/ffmpeg_3.2.14/ffmpeg_install ./ffmpeg_install
