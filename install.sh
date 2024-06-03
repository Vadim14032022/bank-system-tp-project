#!/bin/bash

if ! command -v clang++ &> /dev/null
then 
    echo 'Please install clang compiler'
    exit
fi

mkdir -p build
cd build
cmake -DBUILD_WITH_TESTS=OFF -DCMAKE_INSTALL_PREFIX=../BankSystemApp  ..
make install
cd ..
rm -rf build
