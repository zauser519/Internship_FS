#!/bin/sh
#PBS -q sxs
#PBS --venode 1
#PBS -l elapstim_req=00:10:00

cd /uhome/a01431/FS/T1
g++ -o DLL DLL.cpp

./DLL