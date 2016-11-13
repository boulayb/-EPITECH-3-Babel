#!/bin/sh

sudo cp clientBabel /usr/bin/

sudo cp ../libs/linux/libQtCore.so.4.8.7 /usr/lib64/
sudo cp ../libs/linux/libQtNetwork.so.4.8.7 /usr/lib64/
sudo cp ../libs/linux/libQtGui.so.4.8.7 /usr/lib64/
sudo cp ../libs/linux/libopus.so.0 /usr/lib64/
sudo cp ../libs/linux/libportaudio.so.2 /usr/lib64

sudo ln -s /usr/lib64/libopus.so.0 /usr/lib64/libopus.so
sudo ln -s /usr/lib64/libportaudio.so.2 /usr/lib64/libportaudio.so

sudo ln -s /usr/lib64/libQtCore.so.4.8.7 /usr/lib64/libQtCore.so
sudo ln -s /usr/lib64/libQtCore.so.4.8.7 /usr/lib64/libQtCore.so.4
sudo ln -s /usr/lib64/libQtCore.so.4.8.7 /usr/lib64/libQtCore.so.4.8

sudo ln -s /usr/lib64/libQtGui.so.4.8.7 /usr/lib64/libQtGui.so
sudo ln -s /usr/lib64/libQtGui.so.4.8.7 /usr/lib64/libQtGui.so.4
sudo ln -s /usr/lib64/libQtGui.so.4.8.7 /usr/lib64/libQtGui.so.4.8

sudo ln -s /usr/lib64/libQtNetwork.so.4.8.7 /usr/lib64/libQtNetwork.so
sudo ln -s /usr/lib64/libQtNetwork.so.4.8.7 /usr/lib64/libQtNetwork.so.4
sudo ln -s /usr/lib64/libQtNetwork.so.4.8.7 /usr/lib64/libQtNetwork.so.4.8
