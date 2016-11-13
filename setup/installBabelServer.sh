#!/bin/sh

sudo cp serverBabel /usr/bin/

sudo cp ../libs/linux/libboost_serialization.so.1.60.0 /usr/lib64/
sudo cp ../libs/linux/libboost_system.so.1.60.0 /usr/lib64/

sudo ln -s /usr/lib64/libboost_system.so.1.60.0 /usr/lib64/libboost_system.so
sudo ln -s /usr/lib64/libboost_serialization.so.1.60.0 /usr/lib64/libboost_serialization.so
