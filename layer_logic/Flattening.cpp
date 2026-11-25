#include "Tensor.h"
#include <iostream>
Tensor flattenData(const Tensor& i) {
    Tensor flatOut;

    int totalE = i.w * i.h * i.channels;
    flatOut.data = i.data;
    flatOut.w = totalE;
    flatOut.h = 1;
    flatOut.channels = 1;

    std::cout<<"[Flattening]: From 3D tensor grid to 1D, 1 row entity."<<std::endl;
    std::cout<<"Shape: "<<i.w<<"x"<<i.h<<"x"<<i.channels<<std::endl;
    std::cout<<"- New vector size: "<<flatOut.data.size()<<" elements."<<std::endl;
    return flatOut;
};