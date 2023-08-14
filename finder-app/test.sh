#!/bin/bash
OUTDIR=$1
echo "${OUTDIR}/busybox"
if [ ! -d "${OUTDIR}/busybox" ]
then
    cd "$OUTDIR"
    rm -rf "${OUTDIR}/busybox"
    git clone git://busybox.net/busybox.git
    cd busybox
    git checkout ${BUSYBOX_VERSION}
    # TODO:  Configure busybox
    make distclean
    make defconfig
    make CONFIG_PREFIX=../rootfs ARCH=arm64 CROSS_COMPILE=aarch64-none-linux-gnu- install
else
    cd busybox
fi