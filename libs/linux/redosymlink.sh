#!/bin/sh

rm -f libboost_system.so libboost_serialization.so libopus.so libportaudio.so libQtCore.so libQtCore.so.4 libQtCore.so.4.8 libQtGui.so libQtGui.so.4 libQtGui.so.4.8 libpng.so libpng16.so libpng16.so.16

ln -s libboost_system.so.1.60.0 libboost_system.so
ln -s libboost_serialization.so.1.60.0 libboost_serialization.so

ln -s libopus.so.0 libopus.so
ln -s libportaudio.so.2 libportaudio.so

ln -s libQtCore.so.4.8.7 libQtCore.so
ln -s libQtCore.so.4.8.7 libQtCore.so.4
ln -s libQtCore.so.4.8.7 libQtCore.so.4.8

ln -s libQtGui.so.4.8.7 libQtGui.so
ln -s libQtGui.so.4.8.7 libQtGui.so.4
ln -s libQtGui.so.4.8.7 libQtGui.so.4.8

ln -s libpng16.so.16.23.0 libpng.so
ln -s libpng16.so.16.23.0 libpng16.so
ln -s libpng16.so.16.23.0 libpng16.so.16
