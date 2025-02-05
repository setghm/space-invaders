#!/bin/bash
#
# This file generates an AppImage file for Linux.
#

APPNAME=SpaceInvaders
LINUXDEPLOY=/opt/linuxdeploy
APPIMAGETOOL=/opt/appimagetool

# Clean previous build.

rm -rf installed dist cmake-build-release

mkdir dist
mkdir installed
mkdir cmake-build-release

# Compile.

cmake -S . -B cmake-build-release \
	-DCMAKE_BUILD_TYPE=Release \
	-DCMAKE_C_COMPILER=clang

# Uncomment this to debug the AppImage file:
#cmake -S . -B cmake-build-release -DCMAKE_BUILD_TYPE=Debug -DCMAKE_C_COMPILER=clang -DCMAKE_C_FLAGS='-DBUILD_APPIMAGE'

cmake --build cmake-build-release

cmake --install cmake-build-release

# Create AppDir.

APPDIR=installed/$APPNAME.AppDir

mkdir $APPDIR

# Copy resources into AppDir.

RESDIR=res/linux
ICONSDIR=$APPDIR/usr/share/icons/hicolor

mkdir -p $ICONSDIR
mkdir -p $APPDIR/usr/share/applications
mkdir -p $APPDIR/usr/bin

cp -r installed/assets $APPDIR/usr/share
cp installed/$APPNAME $APPDIR/usr/bin/$APPNAME
ln -s usr/bin/$APPNAME $APPDIR/AppRun
cp $RESDIR/$APPNAME.desktop $APPDIR/usr/share/applications
ln -s usr/share/applications/$APPNAME.desktop $APPDIR/$APPNAME.desktop
cp $RESDIR/icon256.png $APPDIR/$APPNAME.png

for size in 256 128 64 32 16; do
	mkdir -p $ICONSDIR/${size}x${size}/apps
	cp $RESDIR/icon${size}.png $ICONSDIR/${size}x${size}/apps/$APPNAME.png
done

# Get dependencies with linux deploy.

$LINUXDEPLOY --appdir $APPDIR \
	--desktop-file $APPDIR/$APPNAME.desktop \
	--icon-file $APPDIR/$APPNAME.png

# Create AppImage file.

$APPIMAGETOOL $APPDIR dist/$APPNAME.AppImage

