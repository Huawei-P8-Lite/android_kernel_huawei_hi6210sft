#!/bin/bash

LOCAL_DIR=`pwd`
export PATH="$PATH:/home/haky86/roms/aosp-5.0/prebuilts/gcc/linux-x86/aarch64/aarch64-linux-android-4.9/bin/"
export CROSS_COMPILE="aarch64-linux-android-"
mkdir -p out
make ARCH=arm64 O=out hisi_hi6210sft_defconfig
make ARCH=arm64 O=out -j3
