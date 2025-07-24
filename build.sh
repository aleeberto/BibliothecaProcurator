#!/bin/bash
qmake -project -after "QT += gui widgets"
mkdir -p build 
cd build
make clean
qmake ../BibliothecaProcurator.pro
make
cd build
./BibliothecaProcurator